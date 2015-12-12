@echo off

:: This is a wrapper over the node stuff, we set our node environment settings here and
:: just pass the specific tasks as arguments (when calling this bat)

:: %~dp0 is the place of the current script, since %cd% wont work then.
set "MAINDIR=%~dp0.."
set INEXOR_ARCH=win32

if /I "%PROCESSOR_ARCHITECTURE%" == "amd64" (
    set INEXOR_ARCH=win64
)
if /I "%PROCESSOR_ARCHITEW6432%" == "amd64" (
    set INEXOR_ARCH=win64
)

for %%X in (node.exe) do (set "FOUND_NODE=%%~$PATH:X")

if not defined FOUND_NODE (
    :: no installed node found, go for the shipped portable one
    :: which is in the normal bin dir
    :: + go for the shipped npm which is in the platform submodule since we ship it for developers
    set "PATH=%PATH%;%MAINDIR%\bin\windows\%INEXOR_ARCH%;%MAINDIR%\platform\bin\windows\all\npm"
    set "NODE_PATH=%MAINDIR%\platform\bin\windows\all\npm;%MAINDIR%\node;%MAINDIR%\node\lib;%MAINDIR%\node\webserver"
    set "NPM_EXECUTEABLE=%MAINDIR%\platform\bin\windows\all\npm\npm"
    echo using shipped node
) else (
    set "NODE_PATH=%MAINDIR%\node;%MAINDIR%\node\lib;%MAINDIR%\node\webserver"
    set "NPM_EXECUTEABLE=npm"
    echo found node
)

for %%X in (git.exe) do (set "FOUND_GIT=%%~$PATH:X")

if not defined FOUND_GIT (
    :: no installed git found, go for our really shrinked portable one
    set "PATH=%PATH%;%MAINDIR%\platform\bin\windows\all\npm\git\cmd"
    echo using shipped git
) else (
    echo found git
)

cd "%MAINDIR%\node"

:: Execute the passed arguments:
%*

cd "%MAINDIR%"
