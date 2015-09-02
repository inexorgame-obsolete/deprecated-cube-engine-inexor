@echo off
echo i started

setlocal EnableDelayedExpansion

set master=false
if "%APPVEYOR_REPO_BRANCH%"=="master" set master=true

:: set master to false if it is a pull request, bc then the target branch name is used.
if DEFINED APPVEYOR_PULL_REQUEST_NUMBER (
    if NOT "%APPVEYOR_PULL_REQUEST_NUMBER%"=="" set master=false
)

:: always put stuff into data, but only bundle the data repo files in masterbranch
mkdir data
if "%master%"=="true" (
    git clone --depth 1 https://github.com/inexor-game/data.git data
    rd /s /q data\.git
)


set ignored=(.gitignore build CMakeLists.txt appveyor.yml doxygen.conf .git .gitignore .gitmodules tool data inexor .travis.yml)
for /f "tokens=*" %%G in ('dir /b "%cd%"') do (
    set "isignored=false"
    for %%i in %ignored% do (
        if "%%G"=="%%i" set "isignored=true"
    )
    :: Seriously dos batch is fucking dumbshit
    if "!isignored!"=="false" (
        echo copying %cd%\%%G
        :: we have to treat folders and files differently when copying..
        if exist %cd%\%%G\NUL (
            robocopy "%cd%\%%G" "%cd%\data\%%G" *.* /E > Nul
        ) else (
            robocopy "%cd%" "%cd%\data" %%G > Nul
        )
    )
)

:: zip this thing
if "%platform%"=="Win32" set "arch=win32"
if "%platform%"=="x64"   set "arch=win64"
set "branch_name=%APPVEYOR_REPO_BRANCH:/=-%"
set "zip_name=%branch_name%-%APPVEYOR_BUILD_VERSION%-vs_%arch%.zip"
7z a %zip_name% data\*

appveyor PushArtifact %zip_name%
