@cd ..
@rmdir /Q /S vs2019-x64
@rmdir /Q /S lib
@rmdir /Q /S bin
@mkdir vs2019-x64 && cd vs2019-x64
@cmake -G "Visual Studio 16 2019" ../

@if %ERRORLEVEL% == 0 (
    @rem @devenv Tiny3D.sln
    @cmake --open ../vs2019-x64
    @cd ../Projects
) else (
    @cd ../Projects
    @pause
)
