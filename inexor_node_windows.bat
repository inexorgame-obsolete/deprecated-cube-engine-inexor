@echo off

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
    set "PATH=%PATH%;%cd%\node\portable\windows\%INEXOR_ARCH%;%cd%\node\portable"
    set "NODE_PATH=%cd%\node\portable;%cd%\node\lib"
    set "NPM_EXECUTEABLE=portable\npm"
    echo using shipped node
) else (
    set "NODE_PATH=%NODE_PATH%;%cd%\node\portable;%cd%\node\lib"
    set "NPM_EXECUTEABLE=npm"
    echo found node
)

for %%X in (git.exe) do (set "FOUND_GIT=%%~$PATH:X")

if not defined FOUND_GIT (
    :: no installed git found, go for our really shrinked portable one
    set "PATH=%PATH%;%cd%\node\portable\windows\git\cmd"
    echo using shipped git
) else (
    echo found git
)

cd node

echo [RECEIVING NODE MODULES]

call %NPM_EXECUTEABLE% install

echo [STARTING NODE WITH INEXOR BINDING]
echo [LEAVE THIS WINDOW OPEN WHILE INEXOR IS RUNNING]
:: when deploying we can make this a start
node bin\serve
