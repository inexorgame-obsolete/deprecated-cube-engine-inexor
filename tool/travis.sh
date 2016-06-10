#! /bin/bash
#
# Structure
# * Utility functions
# * Installation target implementations
# * Nightly build/APIDOC uploading
# * Compiling and testing
# * Targets as called by .travis.yml
# * Main routine

# ATTENTION:
# Please USE the following naming format for any files uploaded to our distribution server (nightly.inexor.org):
# ...-BUILDNUMBER-<PACKAGENAME>.EXTENSION
# where <PACKAGENAME> is NOT CONTAINING any -
# correct: master-oldbranch-olddirty-1043.2-linux_gcc.txt
# correct: ...-992.2-apidoc.hip
# wrong: ...-1043.2-linux-gcc.zip
# wrong: ...-linux_gcc-1043.2.zip

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
  ncftpput -R -v -u "$FTP_USER" -p "$FTP_PASSWORD" inexor.org / "$@"
}

## INSTALLATION ROUTINES ###################################

install_additional_repos() {
  echo -e "\ndeb http://archive.ubuntu.com/ubuntu vivid "{main,universe} >> /etc/apt/sources.list
  echo -e "\ndeb http://archive.ubuntu.com/ubuntu wily "{main,universe} >> /etc/apt/sources.list
  echo -e "\ndeb http://archive.ubuntu.com/ubuntu xenial "{main,universe} >> /etc/apt/sources.list
}

install_tool() {
  apt-get -y -t trusty install ncftp
}

install_linux() {
  apt-key adv --keyserver keyserver.ubuntu.com --recv-keys FB1BF5BF09FA0AB7
  
  add-apt-repository -y "deb http://ppa.launchpad.net/zoogie/sdl2-snapshots/ubuntu trusty main"
  install_additional_repos
  apt-get update
  
  
  install_tool

  apt-get -y -t wily install --only-upgrade libfontconfig1
  # Not using the more recent ones because https://llvm.org/bugs/show_bug.cgi?id=23529
  # (failure in clang)

  apt-get -y install zlib1g-dev libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev 

  apt-get -y -t trusty install libenet-dev libprotobuf-dev protobuf-compiler libgconf2-dev

  apt-get -y -t vivid install libudev-dev
  
  apt-get -y -t wily install libboost-all-dev build-essential
  
  # Manually workaround http://askubuntu.com/questions/288821/how-do-i-resolve-a-cannot-open-shared-object-file-libudev-so-0-error
  ln -sf /lib/$(arch)-linux-gnu/libudev.so.1 /lib/$(arch)-linux-gnu/libudev.so.0
}

# Install routines for each target

install_win64() {
  #install_additional_repos
  #apt-get update
  #install_tool
  install_linux
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
  apt-get update
  apt-get -y -t wily install gcc-5 g++-5
  apt-get -y -t vivid install binutils
}

install_apidoc() {
  apt-get update
  install_tool
  apt-get install -y -t trusty doxygen
}

install_osx() {
  # if you need sudo for some stuff here, you need to adjust travis.yml and target_before_install()
  # homebrew packages see http://braumeister.org
  brew update > /dev/null
  # don't upgrade everything, it's time expensive and unnecessary
  # check first if it's outdated to prevent a missleading error message
  brew outdated lzlib || brew upgrade lzlib
  brew outdated boost || brew upgrade boost
  brew outdated cmake || brew upgrade cmake
  brew install cmake llvm35 sdl2 sdl2_image sdl2_mixer asio enet protobuf
  # brew ls -v sdl2
  # brew ls -v sdl2_mixer
  # brew ls -v sdl2_image
  # ls /usr/local/lib/
  # ls /usr/lib/
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
    cmake $CMAKE_FLAGS "$gitroot"
    make -kj 5 install
  )
}

run_tests() {
  if contains "$TARGET" linux; then
    "${bin}/linux/`uname -m`/unit_tests"
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
}

target_script() {
  if test "$TARGET" = apidoc; then
    upload_apidoc
  else
    build
    run_tests
  fi
}

# Upload nightly
target_after_success() {
  if test "$TARGET" != apidoc; then
    external_pull_request || nigthly_build || true
  fi
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
