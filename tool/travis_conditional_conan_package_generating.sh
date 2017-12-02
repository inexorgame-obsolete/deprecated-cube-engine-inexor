#! /bin/bash
# This file checks if we change files, which are important for mass building for Conan packages
# If they changed we are going to trigger a mass building
# We are doing this by updating the submodule in inexor-game/ci-prebuilds invoking thereby Travis/AppVeyor processes
# We also commit possible changes in appveyor.yml and .travis.yml
# In both, appveyor.yml and .travis.yml, lines with #CI (followed by a space) are getting un-comment
# In both, appveyor.yml and .travis.yml, lines with #CIDELETE are getting completely removed


# TODO: support for branches with conan- instead of only master to test mass building of packages easily (maybe)

# this makes the entire script fail if one commands fail
set -e

# Making sure we NEVER execute anything of this for pull requests as this could be a huge security risk
if [[ "${TRAVIS_PULL_REQUEST}" != false ]]; then
    echo "We don't build Conan packages for pull requests for security reasons."
    exit 0
fi


if ! [[ "${TRAVIS_BRANCH}" == "master" ]]; then
    echo "This isn't the master branch"
    exit 0
fi

# Check if important files did change in the last commit (the commit we are checking out)
echo "Filtered git diff output:"
echo "$(git diff --name-only ${TRAVIS_COMMIT}^ -- dependencies.py)"

if [[ "$(git diff --name-only ${TRAVIS_COMMIT}^ -- dependencies.py)" == "" ]]; then
    echo "No changes found in Conan dependencies!"
    exit 0
fi

echo "Changes found in Conan dependencies!"
echo "Configure git"

cd ..
git clone --recursive https://github.com/inexorgame/ci-prebuilds.git "ci-prebuilds"
cd "ci-prebuilds"

git checkout master

git config user.name ${GITHUB_BOT_NAME}
git config user.email ${GITHUB_BOT_EMAIL}


echo "Update submodule in ci-prebuilds"
cd inexor

git fetch --all
git checkout master
git reset --hard origin/master
cd ../


echo "Get possible updates of appveyor.yml"
sed 's/#CI //' inexor/appveyor.yml > appveyor.yml
sed --in-place '/#CIDELETE/d' appveyor.yml

echo "Get possible updates of .travis.yml"
sed 's/#CI //' inexor/.travis.yml > .travis.yml
sed --in-place '/#CIDELETE/d' .travis.yml

echo "Create a commit"
git add -A
git commit -am '[bot] Building and uploading Conan dependencies!
Triggered by: https://github.com/inexorgame/inexor-core/commit/'${TRAVIS_COMMIT}



git config credential.helper "store --file=.git/credentials"
echo "https://${GITHUB_TOKEN}:@github.com" > .git/credentials


echo "Push commit"
git push


echo "Mass building of Conan packages is on its way!"
exit 0
