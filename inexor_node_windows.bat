@echo off

:: Start the nodejs app as the Inexor scripting backend.
:: We just call our generic node environment setting batch with the additional commands it shall execute as arguments.
:: The generic handler sets the PATHs for us.

tool\node_windows_generic_handler.bat ^
echo [STARTING NODE WITH INEXOR BINDING] & ^
echo [LEAVE THIS WINDOW OPEN WHILE INEXOR IS RUNNING] & ^
node app/app.js
