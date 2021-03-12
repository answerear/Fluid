cd ../
rm -rf codeblocks-linux
rm -rf bin
rm -rf lib
mkdir -p codeblocks-linux && cd codeblocks-linux
CC=clang CXX=clang++ cmake -G "CodeBlocks - Unix Makefiles" ../
codeblocks Tiny3D.cbp

