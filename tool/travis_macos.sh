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

build() {
  (
    ## mkcd "/tmp/inexor-build"

    conan --version

    conan remote add inexor https://api.bintray.com/conan/inexorgame/inexor-conan --insert
    ## https://bintray.com/conan/conan-center is second

    conan remote list

    pwd
    ls

    conan user -p "${CONAN_PASSWORD}" -r inexor "${CONAN_USER}"

    conan info .

    if test "$NIGHTLY" = conan; then
      if test "$TARGET" = "conanforcerebuild"; then
        buildstrategy=""
      else
        buildstrategy="=outdated"
      fi

      execute="conan install . --env build_all=1 --build${buildstrategy} -s compiler="${COMPILER}" -s compiler.libcxx="libc++" -s build_type=${COMPILER_CONFIGURATION}"
    else
      execute="conan install . --env build_all=1 --env create_package=1 --build=outdated -s compiler="${COMPILER}" -s compiler.libcxx="libc++" -s build_type=${COMPILER_CONFIGURATION}"
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
    source ./travis_conan_upload.sh
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

export gitroot="./"


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
