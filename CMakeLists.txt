cmake_minimum_required(VERSION 2.8.8)
project(NotesCore)
set(PROJECT_NAME_STR NotesCore)
aux_source_directory(src SRC_LIST)

add_definitions(-Wall -ansi -Wno-deprecated -pthread -Wunknown-pragmas)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)
set(ODB_HEADERS ${COMMON_INCLUDES}/NoteEntity.hpp)

include_directories(${COMMON_INCLUDES})
include_directories(SYSTEM /opt/local/include)
add_library(${PROJECT_NAME} STATIC ${SRC_LIST})

#-------------------
# Test
#-------------------

enable_testing()
#set(GTEST_USE_OWN_TR1_TUPLE 1)
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
add_definitions(-Wall -ansi -Wno-deprecated -pthread -static -Wunknown-pragmas)
file(GLOB TEST_SRC_FILES  ${PROJECT_SOURCE_DIR}/test/*.cpp)

find_library(ODB_LIB odb ${EXT_PROJECTS_DIR})
find_library(ODB_SQLITE_LIB odb-sqlite ${EXT_PROJECTS_DIR} )
find_library(GMOCK_LIB gmock ${EXT_PROJECTS_DIR})
find_library(GTEST_LIB gtest ${EXT_PROJECTS_DIR})

add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES} ${SRC_LIST})

target_link_libraries(${PROJECT_TEST_NAME} pthread)
target_link_libraries(${PROJECT_TEST_NAME} ${ODB_SQLITE_LIB})
target_link_libraries(${PROJECT_TEST_NAME} ${ODB_LIB})
target_link_libraries(${PROJECT_TEST_NAME} ${SQLITE_LIB})
target_link_libraries(${PROJECT_TEST_NAME} ${GMOCK_LIB})
target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_LIB})

add_test( AuthLayerTest ${PROJECT_TEST_NAME} )

