#!/bin/bash
set -ev

cd $TRAVIS_BUILD_DIR

# Travis does a rather bad job detecting the branch :/
branch="$TRAVIS_BRANCH"
jobno="$TRAVIS_JOB_NUMBER"
build="$(echo "${branch}-${jobno}" | sed 's#/#-#g')-${TARGET}"

outd="${build}.d/"
zipf="${build}.zip"

"${branch}"  == "master" && media="true" || media="false"

echo "
---------------------------------------
  Exporting Nightly build
  
  commit: ${TRAVIS_COMMIT}
  branch: ${branch}
  job:    ${jobno}
  build:  ${build}

  zip: ${zipf}
  dir: ${outd}

  data export: $media
"

mkdir "$outd"

test "$media" = true && {
  git clone --depth 1 https://github.com/inexor-game/data.git "$outd"
  rm -rf "./${outd}/.git"*
} || true

cp -rv ./bin_* ./inexor_unix ./inexor_cipc_unix ./inexor.bat ./server.bat ./readme.md ./license.md ${outd}
zip -r "$zipf" "$outd"

echo "Commit: ${TRAVIS_COMMIT}" >> ${build}.txt
echo "SHA 512: " >> ${build}.txt
sha512sum "$zipf" >> ${build}.txt

echo "sending ${zipf}"
curl --connect-timeout 1800 --ftp-create-dirs -T "$zipf" -u $FTP_USER:$FTP_PASSWORD ftp://inexor.org/
curl --ftp-create-dirs -T "${build}.txt" -u $FTP_USER:$FTP_PASSWORD ftp://inexor.org/

exit 0
