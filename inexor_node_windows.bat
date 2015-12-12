@echo off

tool\node_windows_generic_handler.bat ^
echo [STARTING NODE WITH INEXOR BINDING] & ^
echo [LEAVE THIS WINDOW OPEN WHILE INEXOR IS RUNNING] & ^
%cd%\node\node_modules\.bin\coffee.cmd bin\serve

