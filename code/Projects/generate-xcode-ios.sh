echo -- Combining libfreeimage.a ...
currentpath=$(pwd)
cd ../../../dependencies/FreeImage/prebuilt/iOS/
lipo -create libfreeimage-arm64.a libfreeimage-armv7.a libfreeimage-armv7s.a libfreeimage-i386.a libfreeimage-x86_64.a -o libfreeimage.a
cd $currentpath
echo -- Combining libfreeimage.a - done
cd ../
rm -rf xcode-ios
rm -rf bin
rm -rf lib
mkdir -p xcode-ios && cd xcode-ios
cmake -GXcode -DCMAKE_TOOLCHAIN_FILE=../CMake/Toolchains/iOS.cmake -DIOS_PLATFORM=OS -DCMAKE_OSX_ARCHITECTURES=arm64 ../
open Tiny3D.xcodeproj
cd ..
# cmake --build build_ios --config Release