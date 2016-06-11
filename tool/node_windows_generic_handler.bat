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


:: go for the shipped node+npm which is in the platform submodule since we ship it for developers
:: + use a really shrinked portable git version
set "INEXOR_ARCH_DIR=%MAINDIR%\bin\windows\%INEXOR_ARCH%"
set "PATH=%PATH%;%INEXOR_ARCH_DIR%;%MAINDIR%\platform\bin\windows\all\npm;%MAINDIR%\platform\bin\windows\all\npm\git\cmd"
set "NODE_PATH=%MAINDIR%\platform\bin\windows\all\npm;%MAINDIR%\node;%MAINDIR%\node\lib"
set "NPM_EXECUTEABLE=%MAINDIR%\platform\bin\windows\all\npm\npm.cmd"

echo Using shipped node.js (v6.2.1), npm (v3.9.1) and git (git needed as npm backend)


cd "%MAINDIR%\node"

:: Execute the passed arguments:
Setlocal EnableDelayedExpansion

%*

Setlocal DisableDelayedExpansion

call cd "%MAINDIR%"
