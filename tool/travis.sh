#! /bin/bash
#
# Structure
# * Utility functions
# * Installation target implementations
# * Nightly build/APIDOC uploading
# * Compiling and testing
# * Targets as called by .travis.conf
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
  ncftpput -R -v -u "$FTP_USER" -p "$FTP_PASSWORD" ftp.adrive.com nightly "$@"
}

## INSTALLATION ROUTINES ###################################

install_utopic_repo() {
  echo -e "\ndeb http://archive.ubuntu.com/ubuntu utopic "{main,multiverse,universe,restricted} >> /etc/apt/sources.list
}

install_tool() {
  apt-get -y install ncftp
}

install_linux() {
  install_utopic_repo
  add-apt-repository -y "deb http://ppa.launchpad.net/zoogie/sdl2-snapshots/ubuntu precise main"

  apt-get update

  install_tool

  apt-get -y install zlib1g-dev libsdl2-dev           \
    libsdl2-image-dev libsdl2-mixer-dev libenet-dev

  apt-get -y -t utopic install libprotobuf-dev         \
    protobuf-compiler build-essential libboost-all-dev \
    libasio-dev binutils libudev-dev

  # Manually workaround http://askubuntu.com/questions/288821/how-do-i-resolve-a-cannot-open-shared-object-file-libudev-so-0-error
  ln -sf /lib/$(arch)-linux-gnu/libudev.so.1 /lib/$(arch)-linux-gnu/libudev.so.0
}

# We have a slightly different install routine for each target

install_win64() {
  install_utopic_repo
  sudo apt-get update
  install_tool
  apt-get -y -t utopic install mingw-w64
}
install_win32() {
  install_win64
}
install_linux_clang() {
  install_linux
  apt-get -y -t utopic install clang-3.5 binutils
}
install_linux_gcc() {
  install_linux
  apt-get -y -t utopic install gcc-4.9 g++-4.9 binutils
}
install_apidoc() {
  install_tool
  apt-get install -y doxygen
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
    upload / "$zipp.zip"
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
    cd "$outd"
    git clone --depth 1 https://github.com/inexor-game/data.git data
    rm -rf data/.git/
  ) fi

  local ignore="$(<<< '
    .
    ..
    .gitignore
    build
    CMakeLists.txt
    appveyor.yml
    doxygen.conf
    .git
    .gitignore
    .gitmodules
    inexor
    tool
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
    echo "Commit: ${comitt}"
    echo -n "SHA 512: "
    sha512sum "$zipf"
  ) > "$descf"

  upload / "$zipf" "$descf"

  if test "$branch" = master; then (
    ln -s "$zipf" "master-latest-$TARGET.zip"
    ln -s "$descf" "master-latest-$TARGET.txt"
    upload / "master-latest-$TARGET.zip" "master-latest-$TARGET.txt"
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
export comitt="${TRAVIS_COMMIT}"
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
