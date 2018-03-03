#! /bin/bash
#
## UTILITY FUNCTIONS #######################################

mkcd() {
  mkdir -pv "$1"
  cd "$1"
}

# Check whether this build is either triggered by a tag or whether
# there already is a tag on the specified commit.
need_new_tag() {
  export current_tag=`git tag --contains`
  if test -n "$current_tag"; then
    false
  else
    true
  fi
}

## INSTALLATION ROUTINES ###################################

build() {
  (
    mkcd "/tmp/inexor-build"

    conan --version

    conan remote add inexor https://api.bintray.com/conan/inexorgame/inexor-conan --insert
    ## https://bintray.com/conan/conan-center is second, https://bintray.com/conan/conan-transit/ third
    conan remote add bincrafers https://api.bintray.com/conan/bincrafters/public-conan --insert 3
    conan remote add community https://api.bintray.com/conan/conan-community/conan --insert 4

    conan remote list

    ## conan info "$gitroot"

    if test "$NIGHTLY" = conan; then
      if test "$TARGET" = "conanforcerebuild"; then
        buildstrategy=""
      else
        buildstrategy="=outdated"
      fi

      execute="conan install "$gitroot" --env build_all=1 --build${buildstrategy} -s compiler="$COMPILER" -s compiler.version="$COMPILER_VERSION" -s compiler.libcxx="libstdc++11" -s build_type=${COMPILER_CONFIGURATION} -e CC="$CC" -e CXX="$CXX""
    else
      if test "$NIGHTLY" = true; then
        execute="conan install "$gitroot" --env build_all=1 --env create_package=1 --build=missing -s compiler="$COMPILER" -s compiler.version="$COMPILER_VERSION" -s compiler.libcxx="libstdc++11" -s build_type=${COMPILER_CONFIGURATION} -e CC="$CC" -e CXX="$CXX""
      else
        execute="conan install "$gitroot" --env build_test=1 --env build_server=1 --build=missing -s compiler="$COMPILER" -s compiler.version="$COMPILER_VERSION" -s compiler.libcxx="libstdc++11" -s build_type=${COMPILER_CONFIGURATION} -e CC="$CC" -e CXX="$CXX""
      fi
    fi

    echo "execute ${execute}";
    eval ${execute}

    conan build "$gitroot"

    if test "$NIGHTLY" = true; then
      # Moving the CPack package to the /inexor directory, so we are able to access it from outside of Docker
      local tempdir="/tmp/inexor-build/"
      local zipname="inexor-core-${INEXOR_VERSION}-Linux64.zip"
      local outputdir="/inexor/build/cpack/"
      mkdir -pv ${outputdir}
      mv -f -v -u "${tempdir}${zipname}" "${outputdir}"
    fi
  )
}


run_tests() {
    "${bin}/unit_tests.exe"
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
  ncftpput -R -v -u "$FTP_USER" -p "$FTP_PASSWORD" "$FTP_DOMAIN" /linux/ "$@" || true
}

## Automatic Creation of tags and generation of the doxygen documentation #################
create_apidoc() {
  (
    local zipname="Inexor-${INEXOR_VERSION}-doc.zip"
    local zipfolder="/tmp/inexor-build"
    cd "$gitroot" -v
    doxygen doxygen.conf 2>&1 | grep -vF 'sqlite3_step " \
      "failed: memberdef.id_file may not be NULL'
    mkdir -pv "${zipfolder}"
    zip -r "${zipfolder}/${zipname}" "doc"
    echo >&2 "Succesfully created ${zipfolder}/${zipname}"
    # upload "${zipfolder}/${zipname}"
  )
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

# increment version and create a tag on GitHub
# each time we push to master, check are in travis.yml
create_tag() {
  need_new_tag || {
    echo >&2 -e "===============\n" \
      "Skipping tag creation, because this build\n" \
      "got triggered by a tag\n" \
      "or because there is already a tag.\n" \
      "===============\n"
    exit 0
  }

  if [ "$branch" = "master" -a "$TRAVIS_PULL_REQUEST" = "false" ]; then
    # direct push to master

    export new_version=$(incremented_version)
    echo >&2 -e $new_version

    git config --global user.email "ci@inexor.org"
    git config --global user.name "InexorBot"

    git tag -a -m "Rolling release: automatic tag creation on push to master branch" "${new_version}"
    git push -q https://$GITHUB_TOKEN@github.com/inexorgame/inexor-core --tags

  else
    echo >&2 -e "\n===============\n" \
    "Skipping tag creation, because this is \n" \
    "not a direct commit to master.\n" \
    "===============\n"
    export new_version=$(incremented_version)
  fi
}

# Upload nightly
upload_nightlies() {
  if test "$TARGET" != apidoc; then
    if test "$NIGHTLY" = conan; then
        # Upload all conan packages to our Bintray repository
        conan user -p "${NIGHTLY_PASSWORD}" -r inexor "${NIGHTLY_USER}"
        set -f
        conan upload --all --force -r inexor --retry 3 --retry-wait 10 --confirm "*stable*"
        set +f
    fi
  fi
}


## MAIN ####################################################

# this makes the entire script fail if one commands fail
set -e

script="$0"
tool="`dirname "$0"`"
code="${tool}/.."
bin="${code}/bin"
TARGET="${1}"
COMPILER="${2}"
COMPILER_VERSION="${3}"
COMPILER_CONFIGURATION="${4}" # Debug or Release
NIGHTLY="${5}" # Nightly is either true, false or conan
NIGHTLY_USER="${6}"
NIGHTLY_PASSWORD="${7}"
FTP_DOMAIN="${8}"

export branch=`git rev-parse --abbrev-ref HEAD` # The branch we're on
export commit_date=`git show -s --format=%cd --date=format:%Y-%m-%d-%H-%m-%S`

# Name of this build
export build="$(echo "${branch}-${commit_date}" | sed 's#/#-#g')-${TARGET}"
export main_repo="inexorgame/inexor-core"

# Workaround Boost.Build problem to not be able to found Clang
if [[ $COMPILER == clang ]]; then
  export CC="clang-$COMPILER_VERSION"
  export CXX="clang++-$COMPILER_VERSION"
  sudo ln -sf /usr/bin/${CC} /usr/bin/clang
  sudo ln -sf /usr/bin/${CXX} /usr/bin/clang++
fi

# Just to make sure that no package uses the wrong GCC version...
if [[ $COMPILER == gcc ]]; then
  export CC="gcc-$COMPILER_VERSION"
  export CXX="g++-$COMPILER_VERSION"
  sudo ln -sf /usr/bin/${CC} /usr/bin/gcc
  sudo ln -sf /usr/bin/${CXX} /usr/bin/gcc++
fi


if [[ $TARGET == new_version_tagger ]]; then
  # we don't run this target within a docker container
  # i.e. we don't need to switch the directory
  # to be within our git repository clone
  export gitroot="."
else
  export gitroot=${code}
fi


cd "$gitroot"

# Tags do not get fetched from travis usually.
git fetch origin 'refs/tags/*:refs/tags/*'
export last_tag=`git describe --tags $(git rev-list --tags --max-count=1)`

# The queue is:
# a tag gets created on push to the master branch (using travis), then we push the
# tag to github and that push triggers travis again (which uploads the release packages)

# We use the last tag as version for the package creation
export INEXOR_VERSION=${last_tag}
need_new_tag && {
  # If we want a new tag
  # We use the last tag of the master branch + 1.
  export INEXOR_VERSION=$(incremented_version)
}


# main entry point
if test "$TARGET" = apidoc; then
  create_apidoc
elif test "$TARGET" = new_version_tagger; then
  create_tag
else
  build
  run_tests
  upload_nightlies
fi

exit 0
