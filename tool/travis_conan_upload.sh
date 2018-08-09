#! /bin/bash
# Upload all conan packages to our Bintray repository

# Login to our repository
conan user -p "${NIGHTLY_PASSWORD}" -r inexor "${NIGHTLY_USER}"

set -f
conan upload --all --force -r inexor --retry 3 --retry-wait 10 --confirm "*stable*"
set +f
