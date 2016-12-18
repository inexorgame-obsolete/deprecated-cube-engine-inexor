@echo off

:: Start the nodejs app as the Inexor scripting backend.

:: setting the PATHS.
set "MAINDIR=%~dp0"
set "NODE_PATH=%MAINDIR%\node;%MAINDIR%\node\lib"

:: Change the dir for one command only
pushd node && (npm start & popd)
