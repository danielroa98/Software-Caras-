#
# This is a CMake makefile.  You can find the cmake utility and
# information about it at http://www.cmake.org
#

cmake_minimum_required (VERSION 3.1)
project(fr)

set (CMAKE_CXX_STANDARD 11)

 set(SOURCE 	classification/svm.cpp
				common/common.cpp
				test_svm.cpp
    )

 set(HEADERS	classification/svm.h
				common/common.h
				test_svm.h
    )

# automatic OpenCV finding
# find_package(OpenCV REQUIRED)

# if not, use manual specification of the OpenCVConfig.cmake path
# and comment previous line of automatic finding
find_package(OpenCV REQUIRED PATHS C:/OpenCV-4.1.1/opencv/user_build NO_DEFAULT_PATH)


if(OpenCV_FOUND)
	message("-- Opencv Found")
endif()


set(fr_include 	C:/OpenCV-4.1.1/opencv/user_build/include
	)

set(fr_libraries 	C:/OpenCV-4.1.1/opencv/user_build/win-install/x64/vc15/lib C:/OpenCV-4.1.1/opencv/user_build/lib/Release
	)


include_directories(${fr_include})
link_directories(${fr_libraries})

add_executable(fr main.cpp)
target_link_libraries(fr opencv_highgui411.lib opencv_imgproc411.lib opencv_objdetect411.lib)
#target_link_libraries(fr ${OpenCV_LIBS})
