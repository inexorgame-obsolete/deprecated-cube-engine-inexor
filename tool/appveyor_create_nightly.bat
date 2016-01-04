@echo off
setlocal EnableDelayedExpansion

:: This will be the name of the nightly build.
if "%platform%"=="Win32" set "arch=win32"
if "%platform%"=="x64"   set "arch=win64"
set "branch_name=%APPVEYOR_REPO_BRANCH:/=-%"

if "%APPVEYOR_REPO_TAG%" == "true" (
    set "nightly_name=Inexor-%APPVEYOR_REPO_TAG_NAME%-%arch%"
) else (
    set "nightly_name=%branch_name%-%APPVEYOR_BUILD_VERSION%-vs_%arch%"
)


set master=false
if "%APPVEYOR_REPO_BRANCH%"=="master" set master=true

:: set master to false if it is a pull request, bc then the target branch name is used.
if DEFINED APPVEYOR_PULL_REQUEST_NUMBER (
    if NOT "%APPVEYOR_PULL_REQUEST_NUMBER%"=="" set master=false
)

echo master is %master%

:: put stuff into this folder
mkdir %nightly_name%

:: Now we want to include our node files as well:
tool\node_windows_update_npm.bat

set ignored=(%nightly_name% .gitignore build cmake CMakeLists.txt appveyor.yml doxygen.conf .git .gitignore .gitmodules tool inexor platform vendor .travis.yml)
for /f "tokens=*" %%G in ('dir /b "%cd%"') do (
    set "isignored=false"
    for %%i in %ignored% do (
        if "%%G"=="%%i" set "isignored=true"
    )
    :: Seriously dos batch is fucking dumbshit
    if "!isignored!"=="false" (
        echo copying %cd%\%%G into %nightly_name%
        :: we have to treat folders and files differently when copying..
        if exist %cd%\%%G\NUL (
            robocopy "%cd%\%%G" "%cd%\%nightly_name%\%%G" *.* /E /MOV > Nul
        ) else (
            robocopy "%cd%" "%cd%\%nightly_name%" %%G /MOV > Nul 
        )
    )
)

:: only bundle the data repo files in masterbranch
if "%master%"=="true" (
    cd %nightly_name%
    mkdir media
    cd media
    git clone --depth 1 https://github.com/inexor-game/data.git core

    rd /s /q core\.git
    del core\.gitignore

:: We temporarily use another repo for additional game files we (currently) bundle
    git clone --depth 1 https://github.com/inexor-game/data-additional.git additional

    rd /s /q additional\.git
    del additional\.gitignore

    cd ..\..
)

:: zip this thing
set "zip_name=%nightly_name%.zip"

echo zipping %zip_name%
7z a %zip_name% %nightly_name%  > Nul
echo finished zipping

appveyor PushArtifact %zip_name%
