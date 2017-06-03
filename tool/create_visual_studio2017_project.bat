
cd %~dp0..
mkdir build
cd build
conan install .. --build=missing -s compiler="Visual Studio" -s compiler.version=15 -s compiler.runtime=MTd -s build_type=Debug
conan build ..
