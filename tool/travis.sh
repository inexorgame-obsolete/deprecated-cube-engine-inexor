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

# This needs to be called as root!
root_install() {
  add-apt-repository -y "deb http://ppa.launchpad.net/zoogie/sdl2-snapshots/ubuntu precise main"
  echo -e "\ndeb http://archive.ubuntu.com/ubuntu utopic "{main,multiverse,universe,restricted} >> /etc/apt/sources.list

  sudo apt-get update

  apt-get -y -t utopic install mingw-w64 gcc-4.9 g++-4.9 \
      clang-3.5 build-essential
  apt-get -y install zlib1g-dev libsdl2-dev         \
    libsdl2-image-dev libsdl2-mixer-dev libenet-dev \
    libprotobuf-dev protobuf-compiler wget          \
    libboost-system1.55-dev doxygen ncftp

  (
    cd /tmp;
    git clone https://github.com/chriskohlhoff/asio.git;
    cd asio;
    git checkout asio-1-10-4
    cp -vr asio/include/asio* /usr/include
  )
}

upload() {
  ncftpput -R -v -u "$FTP_USER" -p "$FTP_PASSWORD" \
    inexor.org "$@"
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
    docd: ${docd}

    data export: $media
  "

  mkdir "$outd"

  if test "$media" = true; then (
    cd "$outd"
    git clone --depth 1 https://github.com/inexor-game/data.git data
    rm -rf data/.git/
  ) fi

  (
    cd "$gitroot" -v
    doxygen doxygen.conf
    cp -rv "doc/html/" "$outd"
    cp -rv "doc/html/" "$docd"
  )

  local ignore="$(<<< '
    .
    ..
    .gitignore
    build
    doc
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

  upload / "$zipf" "$descf" "$docd"

  return 0
}

target_before_install() {
  sudo "$script" root_install
}

target_script() {
  (
    mkcd "/tmp/inexor-build-${build}"
    cmake $CMAKE_FLAGS "$gitroot"
    make -kj 5 install
  )
  run_tests
}

# Upload nightly
target_after_success() {
  nigthly_build || true
}

## MAIN ####################################################

export branch="$TRAVIS_BRANCH" # The branch we're on
export jobno="$TRAVIS_JOB_NUMBER" # The job number
export comitt="${TRAVIS_COMMIT}"
# Name of this build
export build="$(echo "${branch}-${jobno}" | sed 's#/#-#g')-${TARGET}"
export gitroot="$TRAVIS_BUILD_DIR"

cd "$gitroot"

# Call the desired function
"$@"
