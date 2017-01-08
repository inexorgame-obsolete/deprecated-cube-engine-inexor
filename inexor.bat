@echo off

:: Start Inexor Flex

:: Setting the PATHS.
set "MAINDIR=%~dp0"
set "NODE_PATH=%MAINDIR%\flex"

:: Change the dir for one command only
pushd flex && (npm start & popd)
