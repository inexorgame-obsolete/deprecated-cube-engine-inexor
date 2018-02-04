#! /bin/bash
#
## UTILITY FUNCTIONS #######################################

mkcd() {
  mkdir -pv "$1"
  cd "$1"
}

install_dependencies() {
  brew update &> /dev/null
  brew install conan
  brew install nasm
}

## INSTALLATION ROUTINES ###################################

build_conan() {
  conan install "$1" --build=missing -s compiler.libcxx="libc++" -s build_type=${COMPILER_CONFIGURATION}
}

build_conan_and_upload() {
  build_conan "$1"
  set -f
  if [[ "$1" == *"stable"* ]]; then
    conan upload --all --force -r inexor --retry 3 --retry-wait 10 --confirm "$1"
  fi
  set +f
}

rebuild_conan_and_upload() {
  conan install "$1" --build -s compiler.libcxx="libc++" -s build_type=${COMPILER_CONFIGURATION}
  set -f
  if [[ "$1" == *"stable"* ]]; then
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

    pwd
    ls

    conan user -p "${CONAN_PASSWORD}" -r inexor "${CONAN_USER}"

    build_conan_and_upload "Kainjow_Mustache/2.0@inexorgame/stable"
    build_conan_and_upload "bzip2/1.0.6@lasote/stable"
    build_conan_and_upload "pugixml/1.7@inexorgame/stable"
    build_conan_and_upload "gtest/1.8.0@lasote/stable"
    rebuild_conan_and_upload "spdlog/0.14.0@bincrafters/stable"
    rebuild_conan_and_upload "fmt/4.1.0@bincrafters/stable"
    build_conan_and_upload "zlib/1.2.11@conan/stable"
    build_conan_and_upload "ENet/1.3.13@inexorgame/stable"
    build_conan_and_upload "Protobuf/3.5.1@inexorgame/stable"
    build_conan_and_upload "gRPC/1.1.0@inexorgame/stable"
    build_conan_and_upload "libpng/1.6.34@bincrafters/stable"
    build_conan_and_upload "Boost/1.66.0@conan/stable"

    build_conan_and_upload "InexorGlueGen/0.6.6@inexorgame/stable"

    build_conan_and_upload "libjpeg-turbo/1.5.2@bincrafters/stable"
    rebuild_conan_and_upload "OpenSSL/1.1.0g@conan/stable"
    rebuild_conan "SDL2/2.0.5@lasote/testing"
    rebuild_conan "SDL2_image/2.0.1@lasote/stable"

    build_conan "cmake-findboost/0.2.0@bincrafters/stable"
    build_conan "boost_filesystem/1.66.0@bincrafters/stable"
    build_conan "boost_program_options/1.66.0@bincrafters/stable"
    build_conan "boost_random/1.66.0@bincrafters/stable"
    build_conan "boost_regex/1.66.0@bincrafters/stable"
    build_conan "boost_thread/1.66.0@bincrafters/stable"

    build_conan "doxygen/1.8.14@inexorgame/stable"
    build_conan "CEF/3.3239.1709.g093cae4@inexorgame/testing"

    conan info .

    if test "$NIGHTLY" = conan; then
      if test "$TARGET" = "conanforcerebuild"; then
        buildstrategy=""
      else
        buildstrategy="=missing"
      fi

      execute="conan install . --env build_all=1 --build${buildstrategy} -s compiler="${COMPILER}" -s compiler.libcxx="libc++" -s build_type=${COMPILER_CONFIGURATION}"
    else
      execute="conan install . --env build_all=1 --env create_package=1 --build=missing -s compiler="${COMPILER}" -s compiler.libcxx="libc++" -s build_type=${COMPILER_CONFIGURATION}"
    fi

    echo "execute ${execute}";
    eval ${execute}

    conan build "$gitroot"

    if test "$NIGHTLY" != conan; then
      # Moving the CPack package to the /inexor directory, so we are able to access it from outside of Docker
      local tempdir="/tmp/inexor-build/"
      local zipname="inexor-core-${INEXOR_VERSION}-macOS64.zip"
      local outputdir="/inexor/build/cpack/"
      mkdir -pv ${outputdir}
      mv -f -v -u "${tempdir}${zipname}" "${outputdir}"
    fi
  )
}

run_tests() {
    "${bin}/unit_tests.exe"
}



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
upload_nightlies() {
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

# export commit=TRAVIS_COMMIT # we don't use that right now
export branch=TRAVIS_BRANCH # The branch we're on
export jobno=TRAVIS_JOB_NUMBER # The job number
export commit_date=`git show -s --format=%cd --date=format:%Y-%m-%d-%H-%m-%S`

# Name of this build
export build="$(echo "${branch}-${commit_date}" | sed 's#/#-#g')-${TARGET}"
export main_repo="inexorgame/inexor-core"


# this makes it possible to run this script successfull
# even if doesn't get called from the root directory
# of THIS repository
# required to make inexor-game/ci-prebuilds working
export gitroot="./${RELATIVE_PATH}"


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
upload_nightlies
