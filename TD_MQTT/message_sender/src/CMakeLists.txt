# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
# Unfortunately, we have to put each source file here because CMake does not like globbing.
# The list of files can be obtained by running the following command:
# ls -lart $(find . -type f -name "*.cpp") $(find . -type f -name "*.c") | grep -v ./build/ | rev | cut -d ' ' -f 1 | rev | sort | sed 's/^/"/g' | sed 's/$/"/g'
cmake_minimum_required(VERSION 3.5)
add_executable(main.cpp)


