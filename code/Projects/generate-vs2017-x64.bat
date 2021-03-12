@cd ..
@rmdir /Q /S vs2017-x64
@rmdir /Q /S lib
@rmdir /Q /S bin
@mkdir vs2017-x64 && cd vs2017-x64
@cmake -G "Visual Studio 15 2017 Win64" ../

@if %ERRORLEVEL% == 0 (
    @rem @devenv Tiny3D.sln
    @cmake --open ../vs2017-x64
    @cd ../Projects
) else (
    @cd ../Projects
    @pause
)
