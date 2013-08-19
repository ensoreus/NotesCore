cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR NotesCore)
project(NotesCore)
aux_source_directory(. SRC_LIST)


add_definitions(-Wall -ansi -Wno-deprecated -pthread -std=c++11)


set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)
set(LINK_DIRECTORIES ${EXT_PROJECTS_DIR})
add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

#add_executable(${PROJECT_NAME} ${SRC_LIST})

#-------------------
# Test
#-------------------
#add_definitions(${MSVC_COMPILER_DEFS})

enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
link_directories(${EXT_PROJECTS_DIR})
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})

target_link_libraries(${PROJECT_TEST_NAME} pthread)
target_link_libraries(${PROJECT_TEST_NAME} gmock)
target_link_libraries(${PROJECT_TEST_NAME} gtest)

add_test(test1 ${PROJECT_TEST_NAME})

