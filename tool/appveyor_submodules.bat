:: This entire file is a workaround. No joke.
:: AppVeyor doesn't seem to allow to modify the initalite git clone of the repository
:: and therefore doesn't allow to shallow clone the submodules in a sophisticated way.
:: This only works with GitHub repositories, since git doesn't allow shallow clones of a specific commit.

for /f %%i in ('git rev-parse HEAD') do set CURRENT_COMMIT=%%i
echo %CURRENT_COMMIT%

:: get the name of each submodule
for /f "tokens=2 delims=." %%n in ('git config --file .gitmodules --get-regexp path') do (
    echo %%n

    :: fetch the path to each submodule
    for /f %%p in ('git config --file .gitmodules --get submodule.%%n.path') do set SUBMODULE_PATH=%%p
    for /f %%u in ('git config --file .gitmodules --get submodule.%%n.url') do set SUBMODULE_URL=%%u
   
    :: get the specific commit we want to download of each submodule
    for /f "tokens=3" %%c in ('git ls-tree %CURRENT_COMMIT% %SUBMODULE_PATH%') do ( 
       echo %%c 
       set SUBMODULE_WEB=%SUBMODULE_URL:.git=%
       set "SUBMODULE_DOWNLOAD=%SUBMODULE_WEB%/archive/%%c.zip"
       echo %SUBMODULE_DOWNLOAD% 
       powershell -Command "Invoke-WebRequest %SUBMODULE_DOWNLOAD% -OutFile build/%%c.zip"
       7z e build/%%c.zip -o %SUBMODULE_PATH%
    )
)
