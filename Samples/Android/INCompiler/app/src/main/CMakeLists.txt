
cmake_minimum_required(VERSION 3.4.1)

aux_source_directory(../../../../../../Source/compiler sourceList)
aux_source_directory(../../../../../../Source/lib_math libMath)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})

add_library( # Sets the name of the library.
             indicator

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp
             ${sourceList}
             ${libMath}
            )

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -s" )
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -s" )

target_link_libraries( # Specifies the target library.
                indicator

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )