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
    libboost-system1.55-dev

  (
    cd /tmp;
    git clone https://github.com/chriskohlhoff/asio.git;
    cd asio;
    git checkout asio-1-10-4
    cp -vr asio/include/asio* /usr/include
  )
}

target_before_install() {
  sudo "$script" root_install
}

target_script() {
  (
    mkcd cmakebuild
    cmake $CMAKE_FLAGS ..
    make -kj 5 install
  )
  run_tests
}

# Call the desired function
"$@"
