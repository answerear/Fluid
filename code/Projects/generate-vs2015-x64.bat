@cd ..
@rmdir /Q /S vs2015-x64
@rmdir /Q /S lib
@rmdir /Q /S bin
@mkdir vs2015-x64 && cd vs2015-x64
@cmake -G "Visual Studio 14 2015 Win64" ../

@if %ERRORLEVEL% == 0 (
    @devenv Tiny3D.sln
    @cd ../Projects
) else (
    @cd ../Projects
    @pause
)
