#!/bin/bash
set -ev

echo "branch: ${TRAVIS_BRANCH}, Job No: ${TRAVIS_JOB_NUMBER}" #e.g. "branch: master, Job No: 251.4"

if [ "${TRAVIS_BRANCH}" != "master" ]; then 
    exit 0 #it actually errors but we dont want to display a failure every time we are not in master
fi

if [[ ${TRAVIS_JOB_NUMBER} != *1 && ${TRAVIS_JOB_NUMBER} != *5 ]]; then #just deploy one build for windows and one for linux
    exit 0
fi

cd $TRAVIS_BUILD_DIR
export BUILD_NAME=$(echo "${TRAVIS_BRANCH}-${TRAVIS_JOB_NUMBER}-${TRAVIS_COMMIT}" | sed 's#/#-#')
git clone --depth 1 https://github.com/sauerbraten-fork/sauerbraten-fork-data.git nightly
rm -rf ./nightly/.git*
cp -r ./bin_* nightly
cp ./sauerbraten_unix nightly
cp ./sauerbraten.bat nightly
zip -r ${BUILD_NAME}.zip nightly
echo "sending ${BUILD_NAME}.zip"
curl --ftp-create-dirs -T "${BUILD_NAME}.zip" -u $FTP_USER:$FTP_PASSWORD ftp://37.59.98.138/

exit 0