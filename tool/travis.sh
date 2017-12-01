#! /bin/bash
#
# Structure
# * Utility functions
# * Compiling and testing
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

# Check whether this travis job runs for the main repository (inexorgame/inexor-core)
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

# Check whether this build is either triggered by a tag or whether
# there already is a tag on the specified commit.
need_new_tag() {
  if test -n "$TRAVIS_TAG"; then
    false
  else
    export current_tag=`git tag --contains`
    if test -n "$current_tag"; then
        false
      else
        true
      fi
  fi
}

## INSTALLATION ROUTINES ###################################

build() {
  (
    mkcd "/tmp/inexor-build"

    conan --version

    conan remote add inexor https://api.bintray.com/conan/inexorgame/inexor-conan --insert
    conan remote add community https://api.bintray.com/conan/conan-community/conan --insert 3

    if test "$NIGHTLY" = conan; then
      echo "executed conan install "$gitroot" --scope build_all=1 --build -s compiler=$CONAN_COMPILER -s compiler.version=$CONAN_COMPILER_VERSION -s compiler.libcxx=libstdc++11 -e CC=$CC -e CXX=$CXX"
      conan install "$gitroot" --scope build_all=1 --build -s compiler="$CONAN_COMPILER" -s compiler.version="$CONAN_COMPILER_VERSION" -s compiler.libcxx="libstdc++11" -e CC="$CC" -e CXX="$CXX"
    else
      echo "executed conan install "$gitroot" --scope build_all=1 --scope create_package=1 --build=missing -s compiler=$CONAN_COMPILER -s compiler.version=$CONAN_COMPILER_VERSION -s compiler.libcxx=libstdc++11 -e CC=$CC -e CXX=$CXX"
      conan install "$gitroot" --scope build_all=1 --scope create_package=1 --build=missing -s compiler="$CONAN_COMPILER" -s compiler.version="$CONAN_COMPILER_VERSION" -s compiler.libcxx="libstdc++11" -e CC="$CC" -e CXX="$CXX"
    fi

    conan build "$gitroot"

    # workaround that CPack sometimes fails on linux to copy the file to the final directory from the intermediate dir..
    local tempdir="/tmp/inexor-build/_CPack_Packages/Linux/ZIP/"
    local zipname="Inexor-${last_tag}-Linux.zip"
    local outputdir="/tmp/inexor-build/"
    mv -f -v -u "${tempdir}${zipname}" "${outputdir}" || true
  )
}


install_new_version_tagger() {
  return 0
}


run_tests() {
  if contains "$TARGET" linux; then
    "${bin}/unit_tests.exe"
  else
    echo >&2 "ERROR: UNKNOWN TRAVIS TARGET: ${TARGET}"
    exit 23
  fi
}


# ATTENTION:
# Please USE the following naming format for any files uploaded to our distribution server
# <BRANCHNAME>-<BUILDNUMBER>-<TARGET_NAME>.EXTENSION
# where <PACKAGENAME> is NOT CONTAINING any -
# correct: master-1043.2-linux_gcc.txt
# correct: refactor-992.2-apidoc.hip
# exception: master-latest-<TARGET_NAME>.zip
# wrong: ...-linux_gcc-1043.2.zip

## UPLOADING BUILDS AND THE APIDOC #################

# upload remote_path local_path [local_paths]...
#
# Upload one or more files to our nightly or dependencies server
# Variables are defined on the Travis website
upload() {
  # Fix an issue where upload directory gets specified by subsequent upload() calls
  ncftpput -R -v -u "$FTP_USER" -p "$FTP_PASSWORD" "$FTP_DOMAIN" /linux/ "$@" || true
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
  local major_version=`echo -e "${last_tag}" | sed "s/^\(.*\)\\.[0-9]\+\.[0-9]\+.*$/\1/"`
  local minor_version=`echo -e "${last_tag}" | sed "s/^[0-9]\+\.\(.*\)\.[0-9]\+.*$/\1/"`
  local patch_version=`echo -e "${last_tag}" | sed "s/^[0-9]\+\.[0-9]\+\.\(.[0-9]*\).*$/\1/"`

  local new_patch_version=$((patch_version+1))
  local new_version="$major_version.$minor_version.$new_patch_version@alpha"
  echo $new_version
}

# increment version and create a tag on GitHub
# each time we push to master, check are in travis.yml
create_tag() {
  need_new_tag || {
    echo >&2 -e "===============\n" \
      "Skipping tag creation, because this build\n" \
      "got triggered by a tag\n" \
      "or because there is already a tag.\n" \
      "===============\n"
    exit 0
  }
  if [ "$TRAVIS_BRANCH" = "master" -a "$TRAVIS_PULL_REQUEST" = "false" ]; then
    # direct push to master

    export new_version=$(incremented_version)

    git config --global user.email "travis@travis-ci.org"
    git config --global user.name "InexorBot"

    git tag -a -m "Rolling release: automatic tag creation on push to master branch" "${new_version}"
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

# Upload nightly
target_after_success() {
  if test "$TARGET" != apidoc; then
    if test "$NIGHTLY" = conan; then
        # Upload all conan packages to our Bintray repository
        conan user -p "${NIGHTLY_PASSWORD}" -r inexor "${NIGHTLY_USER}"
        set -f
        conan upload --all --force -r inexor --retry 3 --retry_wait 10 --confirm "*stable*"
        set +f
    fi
  fi
}

target_script() {
  if test "$TARGET" = apidoc; then
    create_apidoc
  elif test "$TARGET" = new_version_tagger; then
    create_tag
  else
    build
    run_tests
    target_after_success
  fi
  exit 0
}

## MAIN ####################################################

# this makes the entire script fail if one commands fail
set -e

script="$0"
tool="`dirname "$0"`"
code="${tool}/.."
bin="${code}/bin"
TARGET="$3"
#CMAKE_FLAGS="$4"
CONAN_COMPILER="$4"
CONAN_COMPILER_VERSION="$5"
export CC="$6"
export CXX="$7"

export commit="$8"
export branch="$9" # The branch we're on
export jobno="${10}" # The job number
# Nightly is either true, false or conan
NIGHTLY="${11}"
NIGHTLY_USER="${12}"
NIGHTLY_PASSWORD="${13}"
FTP_DOMAIN="${14}"
if test "${15}" != NO_TAG; then
  TRAVIS_TAG=${15}
fi
TRAVIS_PULL_REQUEST="${16}"
TRAVIS_REPO_SLUG="${17}"


# Name of this build
export build="$(echo "${branch}-${jobno}" | sed 's#/#-#g')-${TARGET}"
export main_repo="inexorgame/inexor-core"

# Workaround Boost.Build problem to not be able to found Clang
if [[ $CC == clang* ]]; then
  sudo ln -sf /usr/bin/${CC} /usr/bin/clang
  sudo ln -sf /usr/bin/${CXX} /usr/bin/clang++
fi

# Just to make sure that no package uses the wrong GCC version...
if [[ $CC == gcc* ]]; then
  sudo ln -sf /usr/bin/${CC} /usr/bin/gcc
  sudo ln -sf /usr/bin/${CXX} /usr/bin/gcc++
fi


if [ -z "$2" ]; then
  export gitroot="/inexor"
else
  # this makes it possible to run this script successfull
  # even if doesn't get called from the root directory
  # of THIS repository
  # required to make inexor-game/ci-prebuilds working
  export gitroot="/inexor/$2"
fi

self_pull_request && {
  echo >&2 -e "Skipping build, because this is a pull " \
    "request with a branch in the main repo.\n"         \
    "This means, there should already be a CI job for " \
    "this branch. No need to do things twice."
  exit 0
}

cd "$gitroot"

# Tags do not get fetched from travis usually.
git fetch origin 'refs/tags/*:refs/tags/*'
export last_tag=`git describe --tags $(git rev-list --tags --max-count=1)`

# The queue is:
# a tag gets created on push to the master branch (using travis), then we push the
# tag to github and that push triggers travis again (which uploads the release packages)

# We use the last tag as version for the package creation
export INEXOR_VERSION=${last_tag}
need_new_tag && {
  # If we want a new tag
  # We use the last tag of the master branch + 1.
  export INEXOR_VERSION=$(incremented_version)
}

"$@"  # Call the desired function
