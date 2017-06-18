
cd %~dp0..
mkdir build
cd build
conan remote add inexor https://api.bintray.com/conan/inexorgame/inexor-conan --insert
conan install .. --build=missing -s compiler="Visual Studio" -s compiler.version=14 -s compiler.runtime=MTd -s build_type=Debug
conan build ..
