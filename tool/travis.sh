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

install_wily_repo() {
  echo -e "\ndeb http://archive.ubuntu.com/ubuntu wily "{main,multiverse,universe,restricted} >> /etc/apt/sources.list
}

install_tool() {
  apt-get -y -t trusty install ncftp
}

install_linux() {
  apt-key adv --keyserver keyserver.ubuntu.com --recv-keys FB1BF5BF09FA0AB7
  
  add-apt-repository -y "deb http://ppa.launchpad.net/zoogie/sdl2-snapshots/ubuntu trusty main"
  install_wily_repo
  apt-get update
  

  install_tool

  apt-get -y -t wily install --only-upgrade libfontconfig1
  apt-get -y -t wily install build-essential binutils doxygen nasm
  python -m pip install conan
}

# Install routines for each target

install_win64() {
  install_wily_repo
  apt-get update
  install_tool
  apt-get -y -t wily install mingw-w64
}
install_win32() {
  install_win64
}
install_linux_clang() {
  install_linux
  apt-get -y -t wily install clang-3.7 binutils
}
install_linux_gcc() {
  install_linux
  apt-get -y -t wily install gcc-5 g++-5
}
install_apidoc() {
  apt-get update
  install_tool
  apt-get install -y -t trusty doxygen
}
install_osx() {
  # if you need sudo for some stuff here, you need to adjust travis.yml and target_before_install()
  #brew install sdl2
  exit 0
}

## UPLOADING NIGHTLY BUILDS AND THE APIDOC #################

upload_apidoc() {
  (
    local zipp="/tmp/$build"
    cd "$gitroot" -v
    doxygen doxygen.conf 2>&1 | grep -vF 'sqlite3_step " \
      "failed: memberdef.id_file may not be NULL'
    mv doc "$zipp"
    zip -r "${zipp}.zip" "$zipp"
    upload "$zipp.zip"
  )
}

nigthly_build() {
  local outd="/tmp/${build}.d/"
  local zipf="/tmp/${build}.zip"
  local descf="/tmp/${build}.txt"

  # Include the media files
  local media="${media}"
  test -n "${media}" || test "$branch" = master && media=true

  echo "
  ---------------------------------------
    Exporting Nightly build

    commit: ${commit}
    branch: ${branch}
    job:    ${jobno}
    build:  ${build}
    commit amount: ${GIT_REV_COUNT}

    gitroot: ${gitroot}
    zip: ${zipf}
    dir: ${outd}

    data export: $media
  "

  mkdir "$outd"

  if test "$media" = true; then (
    cd "$gitroot"
    curl -LOk https://github.com/inexor-game/data/archive/master.zip
    unzip "master.zip" -d "$outd"
    rm "master.zip"
    cd "$outd"
    mv "data-master" "media/data"
  ) fi

  local ignore="$(<<< '
    .
    ..
    .gitignore
    build
    cmake
    CMakeLists.txt
    appveyor.yml
    doxygen.conf
    .git
    .gitignore
    .gitmodules
    inexor
    platform
    tool
    vendor
    .travis.yml
  ' tr -d " " | grep -v '^\s*$')"

  (
    cd "$gitroot"
    ls -a | grep -Fivx "$ignore" | xargs -t cp -rvt "$outd"
  )

  (
    cd "`dirname "$outd"`"
    zip -r "$zipf" "`basename $outd`"
  )

  (
    echo "Commit: ${commit}"
    echo -n "SHA 512: "
    sha512sum "$zipf"
  ) > "$descf"

  upload "$zipf" "$descf"

  if test "$branch" = master; then (
    ln -s "$zipf" "master-latest-$TARGET.zip"
    ln -s "$descf" "master-latest-$TARGET.txt"
    upload "master-latest-$TARGET.zip" "master-latest-$TARGET.txt"
  ) fi

  return 0
}

# ACTUALLY COMPILING AND TESTING INEXOR ####################

build() {
  (
    mkcd "/tmp/inexor-build-${build}"
    conan
    echo "executed conan install "$gitroot" --scope build_all=1 --scope create_package=1 --build=missing -s compiler=$CONAN_COMPILER -s compiler.version=$CONAN_COMPILER_VERSION -s compiler.libcxx=libstdc++11"
    conan install "$gitroot" --scope build_all=1 --scope create_package=1  --build=missing -s compiler="$CONAN_COMPILER" -s compiler.version="$CONAN_COMPILER_VERSION" -s compiler.libcxx="libstdc++11"
    conan build "$gitroot"
  )
}

run_tests() {
  if contains "$TARGET" linux; then
    "${bin}/unit_tests"
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
    upload_apidoc
  else
    build
    run_tests
  fi
  exit 0
}

# Upload nightly
target_after_success() {
  if test "$TARGET" != apidoc; then
    external_pull_request || nigthly_build || true
  fi
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
export GIT_REV_COUNT=`git rev-list --all --count` # We use the commit amount of the branch as version number.
export INEXOR_MINOR_VERSION="${GIT_REV_COUNT}"

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
