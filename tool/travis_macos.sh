#! /bin/bash
#
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

install_dependencies() {
  ## install Conan 0.29.2 as we are not yet compatible with Conan >= 0.30.0
  # cd "$(brew --repo homebrew/core)"
  # cd "$(brew --repo homebrew/core)" && git checkout 971a4ec25f6835874379a2850d8c5fedc4690746
  # HOMEBREW_NO_AUTO_UPDATE=1 brew install conan
  brew install conan
}

## INSTALLATION ROUTINES ###################################

build_conan() {
  conan install "$1" --build=missing -s compiler.libcxx="libc++"
}

build_conan_and_upload() {
  build_conan "$1"
  set -f
  if contains "$1" stable; then
    conan upload --all --force -r inexor --retry 3 --retry-wait 10 --confirm "$1"
  fi
  set +f
}

build() {
  (
    ## mkcd "/tmp/inexor-build"

    conan --version

    conan remote add inexor https://api.bintray.com/conan/inexorgame/inexor-conan --insert
    ## https://bintray.com/conan/conan-center is second, https://bintray.com/conan/conan-transit/ third
    conan remote add bincrafers https://api.bintray.com/conan/bincrafters/public-conan --insert 3
    conan remote add community https://api.bintray.com/conan/conan-community/conan --insert 4

    conan remote list

    echo "$pwd"
    ls

    conan user -p "${CONAN_PASSWORD}" -r inexor "${CONAN_USER}"

    build_conan_and_upload "Kainjow_Mustache/2.0@inexorgame/stable"
    build_conan_and_upload "bzip2/1.0.6@lasote/stable"
    build_conan_and_upload "pugixml/1.7@inexorgame/stable"
    build_conan_and_upload "RapidJSON/1.1.0@inexorgame/stable"
    build_conan_and_upload "gtest/1.8.0@lasote/stable"
    build_conan_and_upload "spdlog/0.14.0@bincrafters/stable"
    build_conan_and_upload "fmt/4.1.0@bincrafters/stable"
    build_conan_and_upload "zlib/1.2.11@conan/stable"
    build_conan_and_upload "ENet/1.3.13@inexorgame/stable"
    build_conan_and_upload "Protobuf/3.5.1@inexorgame/stable"
    build_conan_and_upload "gRPC/1.8.3@inexorgame/stable"
    build_conan_and_upload "libpng/1.6.34@bincrafters/stable"
    build_conan_and_upload "Boost/1.66.0@conan/stable"
    build_conan_and_upload "fmt/4.1.0@bincrafters/stable"
    build_conan_and_upload "spdlog/0.14.0@bincrafters/stable"

    # build_conan_and_upload "cmake-findboost/0.2.0@bincrafters/stable"
    # build_conan_and_upload "boost_filesystem/1.66.0@bincrafters/testing"
    # build_conan_and_upload "boost_program_options/1.66.0@bincrafters/testing"
    # build_conan_and_upload "boost_random/1.66.0@bincrafters/testing"
    # build_conan_and_upload "boost_regex/1.66.0@bincrafters/testing"
    # build_conan_and_upload "boost_thread/1.66.0@bincrafters/testing"

    build_conan_and_upload "InexorGlueGen/0.6.3@inexorgame/stable"

    build_conan_and_upload "libjpeg-turbo/1.5.2@bincrafters/stable"
    build_conan "SDL2/2.0.5@lasote/testing"
    build_conan "SDL2_image/2.0.1@lasote/stable"

    build_conan "doxygen/1.8.13@inexorgame/stable"
    build_conan "CEF/3.3239.1709.g093cae4@inexorgame/testing"

    conan info .

    if test "$NIGHTLY" = conan; then
      echo "execut conan install . --env build_all=1 --build -s compiler.libcxx=libc++"
      conan install . --env build_all=1 --build -s compiler.libcxx="libc++"
    else
      echo "execut conan install . --env build_all=1 --env create_package=1 --build=missing -s compiler.libcxx=libc++"
      conan install . --env build_all=1 --env create_package=1 --build=missing -s compiler.libcxx="libc++"
    fi

    conan build "$gitroot"

    # Moving the CPack package to the /inexor directory, so we are able to access it from outside of Docker
    local tempdir="/tmp/inexor-build/"
    local zipname="inexor-core-${last_tag}-Linux64.zip"
    local outputdir="/inexor/build/cpack/"
    mkdir -pv ${outputdir}
    mv -f -v -u "${tempdir}${zipname}" "${outputdir}"
  )
}

run_tests() {
  if contains "$TARGET" macos; then
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
  ncftpput -R -v -u "$FTP_USER" -p "$FTP_PASSWORD" "$FTP_DOMAIN" /macos/ "$@" || true
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

# Upload nightly
target_after_success() {
  if test "$NIGHTLY" = conan; then
    # Upload all conan packages to our Bintray repository
    conan user -p "${NIGHTLY_PASSWORD}" -r inexor "${NIGHTLY_USER}"
    set -f
    conan upload --all --force -r inexor --retry 3 --retry-wait 10 --confirm "*stable*"
    set +f
  fi
}

## MAIN ####################################################

# this makes the entire script fail if one commands fail
set -e

script="$0"
tool="`dirname "$0"`"
code="${tool}/.."
bin="${code}/bin"

export commit=TRAVIS_COMMIT
export branch=TRAVIS_BRANCH # The branch we're on
export jobno=TRAVIS_JOB_NUMBER # The job number

# Name of this build
export build="$(echo "${branch}-${jobno}" | sed 's#/#-#g')-${TARGET}"
export main_repo="inexorgame/inexor-core"


# this makes it possible to run this script successfull
# even if doesn't get called from the root directory
# of THIS repository
# required to make inexor-game/ci-prebuilds working
export gitroot="./${RELATIVE_PATH}"

self_pull_request && {
  echo >&2 -e "Skipping build, because this is a pull " \
    "request with a branch in the main repo.\n"         \
    "This means, there should already be a CI job for " \
    "this branch. No need to do things twice."
  exit 0
}

echo "$pwd"
echo "$gitroot"
cd "$gitroot"

# Tags do not get fetched from travis usually.
git fetch origin 'refs/tags/*:refs/tags/*'
export last_tag=`git describe --tags $(git rev-list --tags --max-count=1)`

# The queue is:
# a tag gets created on push to the master branch (using travis), then we push the
# tag to github and that push triggers travis again (which uploads the release packages)

# We use the last tag as version for the package creation
export INEXOR_VERSION=${last_tag}
# need_new_tag && {
  # If we want a new tag
  # We use the last tag of the master branch + 1.
  # export INEXOR_VERSION=$(incremented_version) // FIXME: If we want to upload packages one day directly #544
# }

# main entry point
install_dependencies
build
run_tests
target_after_success
