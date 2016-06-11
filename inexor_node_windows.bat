@echo off

:: Start the nodejs app as the Inexor scripting backend.
:: We just call our generic node environment setting batch with the additional commands it shall execute as arguments.
:: The generic handler sets the PATHs for us.
setlocal DisableDelayedExpansion


call %~dp0tool\node_windows_generic_handler.bat ^
!NPM_EXECUTEABLE! update & ^
echo [starting node.js as Inexor scripting backend] & ^
node app/app.js
