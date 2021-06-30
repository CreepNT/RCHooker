cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{DOLCESDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{DOLCESDK}/share/dolce.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define DOLCESDK to point to your SDK path!")
  endif()
endif()


project(RCHooker)
include("${DOLCESDK}/share/dolce.cmake" REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -O3 -fno-lto -nostdlib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")

include_directories()

add_definitions(-DDEBUG)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(${PROJECT_NAME}
    main.c
    log.c
    common.c
    custom_routines.c
)

target_link_libraries(${PROJECT_NAME}
	SceCtrl_stub
	SceTouch_stub
	SceLibKernel_stub
  SceDisplay_stub
	SceAppMgrUser_stub
  SceModulemgr_stub
  SceThreadmgr_stub
	taihen_stub
)

dolce_create_self(${PROJECT_NAME}.suprx ${PROJECT_NAME}
    CONFIG ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}.yml
)