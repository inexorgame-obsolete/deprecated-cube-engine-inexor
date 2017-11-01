#! /bin/bash
#
# Structure
# * Utility functions
# * Installation target implementations
# * Nightly build/APIDOC uploading
# * Compiling and testing
# * Targets as called by .travis.yml
# * Main routine

## UTILITY FUNCTIONS #######################################

# Check if a string contains something
contains() {
  test "`subrm "$1" "$2"`" != "$1"
}

# Remove a substring by name
subrm() {
  echo "${1#*$2}"
}

mkcd() {
  mkdir -pv "$1"
  cd "$1"
}

# Check whether this travis job runs for the main repository
# that is inexor-game/code
is_main_repo() {
  test "${TRAVIS_REPO_SLUG}" = "${main_repo}"
}

# Check whether this build is for a pull request
is_pull_request() {
  test "${TRAVIS_PULL_REQUEST}" != false
}

# Check whether this is a pull request, wants to merge a
# branch within the main repo into the main repo.
#
# E.g. Merge inexor-game/code: karo/unittesting
#      into  inexor-game/code: master
self_pull_request() {
  is_pull_request && is_main_repo
}

# Check whether this is a pull request, that pulls a branch
# from a different repo.
external_pull_request() {
  if is_main_repo; then
    false
  else
    is_pull_request
  fi
}

# upload remote_path local_path [local_paths]...
#
# Upload one or more files to nightly.inexor.org
upload() {
  # Fix an issue where upload directory gets specified by subsequent upload() calls
  ncftpput -R -v -u "$FTP_USER" -p "$FTP_PASSWORD" nightly.inexor.org /linux/ "$@" || true
}

## INSTALLATION ROUTINES ###################################

install_additional_repos() {
  echo -e "\ndeb http://archive.ubuntu.com/ubuntu zesty "{main,multiverse,universe,restricted} >> /etc/apt/sources.list
}

install_tool() {
  apt-get -y -t trusty install ncftp
}

install_linux() {
  apt-key adv --keyserver keyserver.ubuntu.com --recv-keys FB1BF5BF09FA0AB7

  install_additional_repos
  apt-get update


  install_tool

  apt-get -y -t zesty install --only-upgrade libfontconfig1
  apt-get -y -t zesty install build-essential binutils nasm
  python -m pip install conan

  # upgrade cmake
  mkdir $HOME/usr
  export PATH="$HOME/usr/bin:$PATH"
  wget https://cmake.org/files/v3.8/cmake-3.8.2-Linux-x86_64.sh
  chmod +x cmake-3.8.2-Linux-x86_64.sh
  ./cmake-3.8.2-Linux-x86_64.sh --prefix=$HOME/usr --exclude-subdir --skip-license
}

# Install routines for each target

install_win64() {
  install_additional_repos
  apt-get update
  install_tool
  apt-get -y -t zesty install mingw-w64
}
install_win32() {
  install_win64
}
install_linux_clang() {
  install_linux
  apt-get -y -t zesty install clang-3.9 binutils
}
install_linux_gcc() {
  install_linux
  apt-get -y -t zesty install gcc-6 g++-6
}
install_apidoc() {
  apt-get update
  install_tool
  apt-get install -y -t trusty doxygen
}

install_new_version_tagger() {
  return 0
}

install_osx() {
  # if you need sudo for some stuff here, you need to adjust travis.yml and target_before_install()
  #brew install sdl2
  exit 0
}

## Automatic Creation of tags and generation of the doxygen documentation #################

create_apidoc() {
  (
    local zipname="Inexor-${last_tag}-doc.zip"
    local zipfolder="/tmp/inexor-build"
    cd "$gitroot" -v
    doxygen doxygen.conf 2>&1 | grep -vF 'sqlite3_step " \
      "failed: memberdef.id_file may not be NULL'
    mkdir -pv "${zipfolder}"
    zip -r "${zipfolder}/${zipname}" "doc"
    echo >&2 "Succesfully created ${zipfolder}/${zipname}"
    # upload "${zipfolder}/${zipname}"
  )
}

## increment the version number based on the last tag.
incremented_version()
{
  local major_version=`echo -e "${last_tag}" | sed "s/^\(.*\)\\.[0-9]\+\.[0-9]\+-alpha$/\1/"`
  local minor_version=`echo -e "${last_tag}" | sed "s/^[0-9]\+\.\(.*\)\.[0-9]\+-alpha$/\1/"`
  local patch_version=`echo -e "${last_tag}" | sed "s/^[0-9]\+\.[0-9]\+\.\(.*\)-alpha$/\1/"`


  local new_patch_version=$((patch_version+1))
  local new_version="$major_version.$minor_version.$new_patch_version-alpha"
  echo $new_version
}

# increment version and create a tag on github.
# (each time we push to master)
create_tag() {
  if test -n "$TRAVIS_TAG"; then
    echo >&2 -e "===============\n" \
      "Skipping tag creation, because this build\n" \
      "got triggered by a tag.\n" \
      "===============\n"
  elif [ "$TRAVIS_BRANCH" = "master" -a "$TRAVIS_PULL_REQUEST" = "false" ]; then
    # direct push to master

    export new_version=$(incremented_version)

    git config --global user.email "travis@travis-ci.org"
    git config --global user.name "Travis"

    git tag -a -m "automatic tag creation on push to master branch" "${new_version}"
    git push -q https://$GITHUB_TOKEN@github.com/inexorgame/inexor-core --tags

  else
    echo >&2 -e "===============\n" \
      "Skipping tag creation, because this is \n" \
      "not a direct commit to master.\n" \
      "===============\n"
      export new_version=$(incremented_version)
      echo >&2 -e $new_version
  fi
}

# ACTUALLY COMPILING AND TESTING INEXOR ####################

build() {
  (
    mkcd "/tmp/inexor-build"
    conan
    conan remote add inexor https://api.bintray.com/conan/inexorgame/inexor-conan --insert
    echo "executed conan install "$gitroot" --scope build_all=1 --scope create_package=1 --build=missing -s compiler=$CONAN_COMPILER -s compiler.version=$CONAN_COMPILER_VERSION -s compiler.libcxx=libstdc++11"
    conan install "$gitroot" --scope build_all=1 --scope create_package=1  --build=missing -s compiler="$CONAN_COMPILER" -s compiler.version="$CONAN_COMPILER_VERSION" -s compiler.libcxx="libstdc++11"
    conan build "$gitroot"

    # workaround that CPack sometimes fails on linux to copy the file to the final directory from the intermediate dir..
    local tempdir="/tmp/inexor-build/_CPack_Packages/Linux/ZIP/"
    local zipname="Inexor-${last_tag}-Linux.zip"
    local outputdir="/tmp/inexor-build/"
    mv -f -v -u "${tempdir}${zipname}" "${outputdir}" || true
  )
}

run_tests() {
  if contains "$TARGET" linux; then
    "${bin}/unit_tests.exe"
  elif contains "$TARGET" win; then
    echo >&2 "Sorry, win is not supported for testing yet."
    exit 0
  else
    echo >&2 "ERROR: UNKNOWN TRAVIS TARGET: ${TARGET}"
    exit 23
  fi
}

## TARGETS CALLED BY TRAVIS ################################

target_before_install() {
  sudo "$script" install_"$TARGET"
  exit 0
}

target_script() {
  if test "$TARGET" = apidoc; then
    create_apidoc
  elif test "$TARGET" = new_version_tagger; then
    create_tag
  else
    build
    run_tests
  fi
  exit 0
}

# Upload nightly
target_after_success() {
 # if test "$TARGET" != apidoc; then
 #   external_pull_request || true
 # fi
  exit 0
}

## MAIN ####################################################

set -e

script="$0"
tool="`dirname "$0"`"
code="${tool}/.."
bin="${code}/bin"

export main_repo="inexor-game/code"
export branch="$TRAVIS_BRANCH" # The branch we're on
export jobno="$TRAVIS_JOB_NUMBER" # The job number
export commit="${TRAVIS_COMMIT}"

# Tags do not get fetched from travis usually.
git fetch origin 'refs/tags/*:refs/tags/*'
export last_tag=`git describe --tags $(git rev-list --tags --max-count=1)`


# The tag gets created on push to the master branch, then we push the tag to github and that push triggers travis.
if test -n "$TRAVIS_TAG"; then
  # We use the last tag as version for the package creation if this job got triggered by a tag-push.
  export INEXOR_VERSION=${last_tag}
else
  # Otherwise we want a new version, not the last tag of the master branch, but the last one + 1.
  export INEXOR_VERSION=$(incremented_version)
fi

# Name of this build
export build="$(echo "${branch}-${jobno}" | sed 's#/#-#g')-${TARGET}"
export gitroot="$TRAVIS_BUILD_DIR"

self_pull_request && {
  echo >&2 -e "Skipping build, because this is a pull " \
    "request with a branch in the main repo.\n"         \
    "This means, there should already be a ci job for " \
    "this branch. No need to do things twice."
  exit 0
}

cd "$gitroot"
"$@"  # Call the desired function
