@echo off

:: This is a wrapper over the node stuff, we set our node environment settings here and
:: just pass the specific tasks as arguments (when calling this bat)

:: We work on env vars in here, but want to restore them lateron:
Setlocal

:: %~dp0 is the place of the current script, since %cd% wont work then.
set "MAINDIR=%~dp0.."

:: go for the shipped node+npm which is in the platform submodule since we ship it for developers
:: + use a really shrinked portable git version
set "INEXOR_BIN_DIRS=%MAINDIR%\bin\windows\32;%MAINDIR%\bin\windows\64"
set "PATH=%INEXOR_BIN_DIRS%;%MAINDIR%\platform\bin\windows\all\npm;%MAINDIR%\platform\bin\windows\all\npm\git\cmd"
set "NODE_PATH=%MAINDIR%\platform\bin\windows\all\npm;%MAINDIR%\node;%MAINDIR%\node\lib"
set "NPM_EXECUTEABLE=%MAINDIR%\platform\bin\windows\all\npm\npm.cmd"

echo Using shipped node.js, npm and git (git needed as npm backend)


echo node version:
call node -v
:: echo npm version:
:: call %NPM_EXECUTEABLE% -v


cd "%MAINDIR%\node"

if "%inexor_update_npm%"=="true" call %NPM_EXECUTEABLE% install
if "%inexor_start_nodeapp%"=="true" call %NPM_EXECUTEABLE% start


call cd "%MAINDIR%"

:: restore envvars
Endlocal
