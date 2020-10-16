#Required lines
cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{DOLCESDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{DOLCESDK}/share/dolce.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define DOLCESDK to point to your SDK path!")
  endif()
endif()


project(RCHooker) #This is the name of your project. Note that "LANGUAGES C" is optional
include("${DOLCESDK}/share/dolce.cmake" REQUIRED) #Including the SDK's .cmake script is required

#Settings for the compilers, this will output an optimized C binary while displaying all warnings
#(-Wno-unknown-pragmas is for the "#pragma region" used in Visual Studio Code)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -O3 -Wno-unknown-pragmas -fno-lto -nostdlib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")

#If you have any headers you use, make sure to put the directory here.
#Note that the PSP2, VitaSDK/DolceSDK and taiHEN headers are already included by default.
include_directories()

#This is equivalent to placing "#define DEBUG" somewhere in your code.
#Useful for testing purposes.
add_definitions(-DDEBUG)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

#All the .c files used by the project.
add_executable(${PROJECT_NAME}
    main.c
)

#Libraries the project will be linked against. VitaSDK docs can help you find most of them.
target_link_libraries(${PROJECT_NAME}
	SceCtrl_stub
	SceTouch_stub
	SceLibKernel_stub
  SceDisplay_stub
	SceAppMgr_stub
  SceKernelModulemgr_stub
  SceKernelThreadMgr_stub
	taihen_stub
)

#Creates a signed elf (EBOOT.BIN)
dolce_create_self(${PROJECT_NAME}.suprx ${PROJECT_NAME}
    CONFIG ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}.yml
)