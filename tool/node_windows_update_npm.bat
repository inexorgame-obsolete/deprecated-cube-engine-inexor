@echo off
:: Install any needed files if necessary.


:: setting the PATHS.
set "MAINDIR=%~dp0.."
set "NODE_PATH=%MAINDIR%\node;%MAINDIR%\node\lib"

:: Change the dir for one command only
pushd %MAINDIR%\node && (npm update & popd)
