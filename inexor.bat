@ECHO OFF
Setlocal EnableDelayedExpansion

:: Clear variable
set "DATA_DIRS="
:: Find all data repos in media
for /f "delims=" %%a in ('dir "./media" /on /ad /b') do @set "DATA_DIRS=!DATA_DIRS! -kmedia/%%a/"

start bin\inexor.exe "-q$HOME\My Games\Inexor" %DATA_DIRS% -glog.txt %*
start /B inexor_node_windows.bat
