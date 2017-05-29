const process = require('process')
const fs = require('fs')
const path = require('path')
const url = require('url')
const os = require('os')
const unzip = require('unzip')
const https = require('follow-redirects').https

const releaseURL = 'https://api.github.com/repos/inexor-game/code/releases'
const userAgent = 'Mozilla/4.0 (compatible; MSIE 5.0b1; Mac_PowerPC)' // It won't let us use a custom API agent, take IE5 than

/**
 * @function determinePlatform
 * Determines the current platform, which can be one of the current supported ones (below):
 * - win32
 * - win64
 * - linux32
 * - linux64
 * @throws 'Unsupported platform'
 * @return {string}
 * NOTE: This definition will change
 */
function determinePlatform() {
  platform = ''

  if (os.platform() == 'win32') {
    platform += 'win'
  } else if (os.platform() == 'linux') {
    platform += 'linux'
  } else {
    throw('Unsupported platform ' + os.platform())
  }

  if (['ia32', 'arm', 'x32', 'x86'].contains(os.arch())) {
    platform += '32'
  } else if (['arm64', 'x64'].contains(os.arch())) {
    platform += '64'
  } else {
    throw('Unsupported platform ' + platform + os.arch())
  }

  return platform
}

/**
 * @function getLatestRelease
 * Returns the latest release
 * NOTE: The name is a bit ambigious
 * @return {Promise<Object>} - a GitHub Release API response
 */
function getLatestRelease() {
  return new Promise((resolve, reject) => {
    let URL = url.parse(releaseURL)

    https.get({
      host: URL.host,
      path: URL.path,
      headers: {
        'User-Agent': userAgent
      }
    }, (response) => {
      let body = ''
      response.on('data', (d) => body += d)

      response.on('end', () => {
        let parsed = JSON.parse(body)
        resolve(parsed[0])
      })
    })
  })
}

/**
 * @function downloadArchive
 * Downloads an archive to a given destination
 * @param  {string} archiveURL
 * @param  {string} fileName
 * @param  {string} destinationPath [destinationPath=process.cwd(] - where the file should go
 * @return {Promise<fs.ReadStream>}
 */
function downloadArchive(archiveURL, fileName, destinationPath = process.cwd()) {
  return new Promise((resolve, reject) => {
    let URL = url.parse(archiveURL)
    let filePath = path.resolve(destinationPath, fileName)
    let file = fs.createWriteStream(filePath)

    https.get({
      host: URL.host,
      path: URL.path,
      headers: {
        'User-Agent': userAgent
      }
    }, (response) => {
      response.pipe(file)

      response.on('end', () => {
        file.close()
        resolve(fs.createReadStream(filePath))
      })
    })

  })
}

try {
  getLatestRelease().then((release) => {
    let platform = determinePlatform()
    let asset = release.assets.filter((a) => a.name.includes(platform))

    if (asset) {
      downloadArchive(asset[0].browser_download_url, asset[0].name).then((archiveStream) => {
        archiveStream.pipe(unzip.Extract({path: path.resolve(process.cwd(), 'bin')})) // Always unzip the new releases to bin
      })
    } else {
      throw('No bundle was found for the platform ' + platform)
    }
  })
} catch (e) {
  console.log(e)
}


module.exports = {
  determinePlatform: determinePlatform,
  getLatestRelease: getLatestRelease,
  downloadArchive: downloadArchive,
}
