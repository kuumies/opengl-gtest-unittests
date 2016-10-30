# opengl-gtest-unittests
An example how to run OpenGL unit tests with GTest and QOpenGLWidget

This is handy when writing wrapper-classes around of OpenGL functions. The example tests a Mesh class that is wrapper of OpenGL vertex buffer objects and vertex array object functions.

## Building

This example requires c++11 support from the compiler. It is assumed that Qt 5.4 or later and Cmake 3.0.0 or later are installed.

### OSX

```
# Clone the source
git clone https://github.com/kuumies/opengl-gtest-unittests.git
# Create build directory
cd opengl-gtest-unittests
mkdir build
cd build
# Run cmake, note that you need to tell cmake were to 
# find the Qt (building from Qt Creator seems to auto-
# matically fix this). Below I have set my Qt install 
# path.
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/users/kuumies/Qt5.7.0/5.7/clang_64/ -DCMAKE_INSTALL_PREFIX=install ../.
# Build and install. The output binary can be found 
# from build/install/bin directory.
make install
```
Tested with:

```
OS X Yosemite 10.10.5
Clang 64 bit 600.0.51
Qt 5.7.0
Cmake 3.4.1
```
