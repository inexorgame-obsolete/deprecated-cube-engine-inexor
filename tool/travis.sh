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

upload() {
  local dest="ftp://inexor.org/$2/$1"
  echo >&2 "Uploading: `readlink -f "$1"` to $dest"
  curl --connect-timeout 1800 --ftp-create-dirs \
    -u "$FTP_USER:$FTP_PASSWORD" "$dest" -T "$1"
}

upload_file() {
  (
    local d="`dirname $1`" n="`basename "$1"`"
    cd "$d"
    upload "$n" "$2"
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

  cp -rv ./bin_* ./inexor_unix ./inexor_cipc_unix ./inexor.bat ./server.bat ./readme.md ./license.md "${outd}"

  (
    cd "`dirname "$outd"`"
    zip -r "$zipf" "`basename $outd`"
  )

  (
    echo "Commit: ${comitt}"
    echo -n "SHA 512: "
    sha512sum "$zipf"
  ) > "$descf"

  echo "Uploading: ${zipf} and $descf"
  upload_file "$zipf" &
  upload_file "$descf"

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
