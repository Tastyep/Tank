cmake_minimum_required (VERSION 2.8.1)
cmake_policy(SET CMP0042 NEW)

set(NAME "Tank")
set(CLIENT_DIR client)
set(COMMON_DIR common)

project (${NAME} CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

find_package(SFML 2.1 REQUIRED system window graphics audio)
find_package(Protobuf)
find_package(ENet)


set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g")
set(CMAKE_EXE_LINKER_FLAGS  "-g")

include_directories (${PROJECT_SOURCE_DIR}/${CLIENT_DIR}/inc
                     ${PROJECT_SOURCE_DIR}/${COMMON_DIR}/inc)

file (GLOB headers "*.hh")
file (GLOB headers "*.hpp")
file (GLOB sources "*.cpp")

set (DIRS ${PROJECT_SOURCE_DIR}/${CLIENT_DIR}/inc
          ${PROJECT_SOURCE_DIR}/${COMMON_DIR}/inc
          ${PROJECT_SOURCE_DIR}/${CLIENT_DIR}/src
          ${PROJECT_SOURCE_DIR}/${COMMON_DIR}/src
         ${PROJECT_SOURCE_DIR}/${COMMON_DIR}/src/Entities)

foreach (dir ${DIRS})
   file (GLOB h_${dir} "${dir}/*.h")
   file (GLOB s_${dir} "${dir}/*.cpp")
   source_group (${dir} FILES ${s_${dir}} ${h_${dir}})
   set (sources ${sources} ${s_${dir}})
   set (header ${headers} ${h_${dir}})
endforeach ()

add_executable(${NAME} ${sources})

target_link_libraries (${NAME} ${SFML_LIBRARIES})
set_target_properties(${NAME}
    PROPERTIES
   LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
