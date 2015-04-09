#! /bin/bash

set -e

script="$0"
tool="`dirname "$0"`"
code="${tool}/.."
bin="${code}/bin"

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

run_tests() {
  if contains "$TARGET" linux; then
    "${bin}/linux/`uname -m`/testcmd"
  elif contains "$TARGET" win; then
    echo >&2 "Sorry, win is not supported for testing yet."
    exit 0
  else
    echo >&2 "ERROR: UNKNOWN TRAVIS TARGET: ${TARGET}"
    exit 23
  fi
}

install_tool() {
  apt-get -y install ncftp
}

install_utopic_repo() {
  echo -e "\ndeb http://archive.ubuntu.com/ubuntu utopic "{main,multiverse,universe,restricted} >> /etc/apt/sources.list
}

install_linux() {
  install_utopic_repo
  add-apt-repository -y "deb http://ppa.launchpad.net/zoogie/sdl2-snapshots/ubuntu precise main"

  sudo apt-get update

  install_tool

  apt-get -y install zlib1g-dev libsdl2-dev         \
    libsdl2-image-dev libsdl2-mixer-dev libenet-dev \
    libprotobuf-dev protobuf-compiler               \
    libboost-system1.55-dev ncftp
  apt-get -y -t utopic install build-essential

  (
    cd /tmp;
    git clone https://github.com/chriskohlhoff/asio.git;
    cd asio;
    git checkout asio-1-10-4
    cp -vr asio/include/asio* /usr/include
  )
}

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
  apt-get -y -t utopic install clang-3.5
}
install_linux_gcc() {
  install_linux
  apt-get -y -t utopic install gcc-4.9 g++-4.9
}
install_apidoc() {
  install_tool
  apt-get install -y doxygen
}

upload() {
  ncftpput -R -v -u "$FTP_USER" -p "$FTP_PASSWORD" \
    inexor.org "$@"
}

upload_apidoc() {
  (
    cd "$gitroot" -v
    doxygen doxygen.conf 2>&1 | grep -vF 'sqlite3_step " \
      "failed: memberdef.id_file may not be NULL'
    cp -r doc/ "/tmp/$build"
    upload / "/tmp/$build"
  )
}

nigthly_build() {
  local outd="/tmp/${build}.d/"
  local zipf="/tmp/${build}.zip"
  local descf="/tmp/${build}.txt"
  local docd="/tmp/${build}-apidoc"

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
    doxygen.conf
    .git
    .gitignore
    .gitmodules
    src
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

  return 0
}

build() {
  (
    mkcd "/tmp/inexor-build-${build}"
    cmake $CMAKE_FLAGS "$gitroot"
    make -kj 5 install
  )
}

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
