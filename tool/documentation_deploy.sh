#!/bin/bash
set -e # Exit with nonzero exit code if anything fails

SOURCE_BRANCH="master"
TARGET_BRANCH="${DOCUMENTATION_REPOSITORY_BRANCH}"
TARGET_REPOSITORY="${DOCUMENTATION_REPOSITORY}"

if [[ "${TRAVIS_REPO_SLUG}" == "inexorgame/inexor-flex" ]]; then
  TARGET="flex"
else
  TARGET="core"
fi

# Pull requests shouldn't try to deploy, just build to verify
if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
    echo "Skipping deploy; just doing a build."
    bash ./tool/documentation_create.sh
    exit 0
fi

if [ -z "${TRAVIS_TAG}" ]; then
    echo "Only deploy documentation on a tag; just doing a build"
    bash ./tool/documentation_create.sh
    exit 0;
fi

export last_tag=`git describe --tags $(git rev-list --tags --max-count=1)`
export INEXOR_MAJOR_VERSION=`echo -e "${last_tag}" | sed "s/^\(.*\)\\.[0-9]\+\.[0-9]\+.*$/\1/"`
export INEXOR_MINOR_VERSION=`echo -e "${last_tag}" | sed "s/^[0-9]\+\.\(.*\)\.[0-9]\+.*$/\1/"`
export INEXOR_PATCH_VERSION=`echo -e "${last_tag}" | sed "s/^[0-9]\+\.[0-9]\+\.\(.[0-9]*\).*$/\1/"`
export DOCUMENTATION_TAG_NAME=${TARGET}-${INEXOR_MAJOR_VERSION}.${INEXOR_MINOR_VERSION}.${INEXOR_PATCH_VERSION}
export DOCUMENTATION_TARGET_VERSION="${INEXOR_MAJOR_VERSION}-${INEXOR_MINOR_VERSION}"
export DOCUMENTATION_TARGET_DIRECTORY="${TARGET}/${DOCUMENTATION_TARGET_VERSION}/"
export DOCUMENTATION_TARGET_DIRECTORY_LATEST="${TARGET}/master/"

# Save some useful information
# REPO=`git config remote.origin.url`
TOKEN_REPO=${TARGET_REPOSITORY/github.com/$GITHUB_BOT_NAME:$GITHUB_TOKEN@github.com}
SHA=`git rev-parse --verify HEAD`

# Clone the existing gh-pages for this repo into out/
# Create a new empty branch if gh-pages doesn't exist yet (should only happen on first deply)
git clone ${TARGET_REPOSITORY} out
cd out
git checkout $TARGET_BRANCH || git checkout --orphan $TARGET_BRANCH
mkdir -p ${DOCUMENTATION_TARGET_VERSION}
mkdir -p ${DOCUMENTATION_TARGET_DIRECTORY_LATEST}
cd ..

# Clean out existing contents
rm -rf out/${DOCUMENTATION_TARGET_DIRECTORY}/**/* || exit 0
rm -rf out/${DOCUMENTATION_TARGET_DIRECTORY_LATEST}/**/* || exit 0

# Run our compile script; all files go to doc/; see .jsdoc.json
bash ./tool/documentation_create.sh

cp -R  "doc/." "out/${DOCUMENTATION_TARGET_DIRECTORY}"
cp -R  "doc/." "out/${DOCUMENTATION_TARGET_DIRECTORY_LATEST}"

# Now let's go have some fun with the cloned repo
cd out
git config user.name ${GITHUB_BOT_NAME}
git config user.email ${GITHUB_BOT_EMAIL}
git tag -a -m "Documentation update for ${DOCUMENTATION_TAG_NAME}" "${DOCUMENTATION_TAG_NAME}"

# Use a shadow commit to add differences in previously uncommited files
git add -A --intent-to-add .

# If there are no changes to the compiled out (e.g. this is a README update) then just bail.
if git diff --quiet; then
    echo "No changes to the output on this push; exiting."
    exit 0
fi

# Commit the "changes", i.e. the new version.
# The delta will show diffs between new and old versions.
git add -A .
git commit -m "Update ${TARGET} documentation ${DOCUMENTATION_TAG_NAME} : ${SHA}"

# Now that we're all set up, we can push.
git push $TOKEN_REPO --follow-tags
