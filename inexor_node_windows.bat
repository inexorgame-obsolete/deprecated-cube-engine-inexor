@echo off

set "THISDIR=%~dp0.."

tool\node_windows_generic_handler.bat ^
echo [STARTING NODE WITH INEXOR BINDING] & ^
echo [LEAVE THIS WINDOW OPEN WHILE INEXOR IS RUNNING] & ^
node.exe app/app.js
