
cd %~dp0..
mkdir build
cd build
conan install .. --build=missing --scope create_package=1 -s compiler="Visual Studio" -s compiler.version=14 -s compiler.runtime=MTd -s build_type=Debug
conan build ..
