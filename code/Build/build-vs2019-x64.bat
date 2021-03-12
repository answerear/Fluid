@cd ..
@rmdir /Q /S vs2019-x64
@rmdir /Q /S lib
@rmdir /Q /S bin
@mkdir vs2019-x64 && cd vs2019-x64
@cmake -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release ../
@cd ../Build

@if %ERRORLEVEL% == 0 (
    @cmake --build ../vs2019-x64 --config Release -v -j 4
    @pause
) else (
    @pause
)

