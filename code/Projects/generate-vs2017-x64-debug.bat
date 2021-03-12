@cd ..
@rmdir /Q /S vs2017-x64
@rmdir /Q /S lib
@rmdir /Q /S bin
@mkdir vs2017-x64 && cd vs2017-x64
@cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=Debug ../

@if %ERRORLEVEL% == 0 (
    @devenv Tiny3D.sln
    @cd ../Projects
) else (
    @cd ../Projects
    @pause
)
