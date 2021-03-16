======================================
DirectXShaderCompiler on Linux & macOS
======================================

.. contents::
   :local:
   :depth: 3

Introduction
============

DirectXShaderCompiler (DXC) is based on LLVM/Clang, which is originally
cross-platform. However, to support HLSL, certain Windows specific techniques
(like COM, SAL, etc.) are introduced to solve technical issues on the Windows
platform, which also makes DXC not compilable/runnable on non-Windows platforms.

Upon `several <https://github.com/Microsoft/DirectXShaderCompiler/issues/1082>`_
`requests <https://github.com/Microsoft/DirectXShaderCompiler/issues/1236>`_
from the community, we have started the effort to enable compilation and running
of DXC on non-Windows platforms (Linux and macOS).

Current Status
==============

Up and Running
--------------
We have currently reached the point where we can successfully build and run DXC
on Linux and macOS. Code generation works for both DXIL and SPIR-V, and we are
also able to run the whole SPIR-V and a large portion of DXIL CodeGen test suite
on these platforms.

*Note: This work is currently in experimental phase. How we implement certain
things for Unix platforms may change without considering backward portability.*

Known Limitations
-----------------

The following targets are currently disabled for non-Windows platforms and this
is an area where further contributions can be made:

* d3dcomp
* dxa
* dxopt
* dxl
* dxr
* dxv
* dxlib-sample

Moreover, since the HLSL CodeGen tests were originally written with Windows in
mind, they require the Windows-specific `TAEF Framework <https://docs.microsoft.com/en-us/windows-hardware/drivers/taef/>`_
to run. Besides, some tests also require DirectX to execute. Therefore we are
not able to compile/run all these tests on non-Windows platforms. Note that
it is only the testing infrastructure that has this limitation, and DXIL CodeGen
works as expected by running the DXC executable.

Known Issues
------------
- Running the SPIR-V CodeGen tests results in opening a large number of file
  descriptors, and if the OS limitation on the number of FDs allowed to be opened
  by a process is low, it will cause test failures. We have not seen this as an
  issue on Windows and Linux. On macOS we currently increase the allowed limit to
  get around the problem for the time being.

- The version number of the shared library is currently stuck at 3.7. We need to
  fix this once a certain versioning scheme is in place.

Building and Using
==================

Build Requirements
------------------
Please make sure you have the following resources before building:

- `Git <https://git-scm.com/downloads>`_
- `Python <https://www.python.org/downloads/>`_. Version 3.x is required.
- `Ninja <https://github.com/ninja-build/ninja/releases>`_ (*Optional* CMake generator)
- Either of gcc/g++ or clang/clang++ compilers. Minimum supported version:

  - `GCC <https://gcc.gnu.org/releases.html>`_ version 5.5 or higher.
  - `Clang <http://releases.llvm.org/>`_ version 3.8 or higher.


Building DXC
------------
You can follow these steps to build DXC on Linux/macOS:

.. code:: sh

  cd <dxc-build-dir>
  cmake <dxc-src-dir> -GNinja -DCMAKE_BUILD_TYPE=Release $(cat <dxc-src-dir>/utils/cmake-predefined-config-params)
  ninja

Note that ``cmake-predefined-config-params`` file contains several cmake
configurations that are needed for successful compilation. You can further
customize your build by adding configurations at the end of the cmake command
above.

For instance, you can use

``-DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++``

or

``-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++``

to choose your desired C/C++ compiler.

You should now have the dxc executable located at ``<dxc-build-dir>/bin/dxc``.
And you should be able to successfully run commands as you would on Windows, e.g:

.. code:: sh

  ./bin/dxc -help
  ./bin/dxc -T <target> -E <entry-point-name> <input-hlsl-file>

Note that you cannot use slashes (``/``) for specifying command line options as
you would on Windows. You should use dashes as per usual Unix style.

Building and Running Tests
--------------------------

The tests are run using the GoogleTest framework.

You can follow these steps to build and run the tests:

.. code:: sh

  cd <dxc-build-dir>
  # Use SPIRV_BUILD_TESTS flag to enable building these tests.
  cmake <dxc-src-dir> \
    $(cat <dxc-src-dir>/utils/cmake-predefined-config-params) \
    -DCMAKE_BUILD_TYPE=Release -DSPIRV_BUILD_TESTS=ON \
    -GNinja
  # Build all targets. Includes 'dxc' and tests.
  ninja
  # Run all tests
  ctest


As described in the `Known Issues`_ section above, you currently need to
increase the maximum per-process open files on macOS using
``ulimit -Sn 1024`` before running the tests on that platform.

TODO: Add more information about Linux implementation details.

