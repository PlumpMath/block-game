cmake_minimum_required(VERSION 3.0)
project("Block Game")

set(LIBRARY_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
include(CMakeParseArguments)
function(add_cmake_dependency)
  # ACD stands for add_cmake_dependency
  set(ACD_ONE_VALUE_KEYWORDS
    NAME
    URL # to TGZ
    SOURCE # name the unzipped source directory will have
    INCLUDE # path in source directory to include directory
  )
  cmake_parse_arguments(ACD "" "${ACD_ONE_VALUE_KEYWORDS}" "" ${ARGN})
  set(ACD_DIRECTORY_ABSOLUTE ${LIBRARY_DIRECTORY}/${ACD_NAME})
  set(ACD_TGZ ${ACD_NAME}.tgz)
  set(ACD_TGZ_ABSOLUTE ${ACD_DIRECTORY_ABSOLUTE}/${ACD_TGZ})
  set(ACD_SOURCE_ABSOLUTE ${ACD_DIRECTORY_ABSOLUTE}/${ACD_SOURCE})
  set(ACD_CMAKE_LISTS_ABSOLUTE ${ACD_SOURCE_ABSOLUTE}/CMakeLists.txt)
  set(ACD_INCLUDE_ABSOLUTE ${ACD_SOURCE_ABSOLUTE}/${ACD_INCLUDE})
  set(ACD_BINARY_ABSOLUTE ${ACD_DIRECTORY_ABSOLUTE}/bin)

  if(NOT EXISTS ${ACD_CMAKE_LISTS_ABSOLUTE})
    message(STATUS "Downloading ${ACD_URL}")
    file(DOWNLOAD ${ACD_URL} ${ACD_TGZ_ABSOLUTE})

    message(STATUS "Unzipping ${ACD_TGZ_ABSOLUTE}")
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E tar xzf ${ACD_TGZ}
      WORKING_DIRECTORY ${ACD_DIRECTORY_ABSOLUTE}
    )
  endif()

  include_directories(${ACD_INCLUDE_ABSOLUTE})

  # cause CMake to automatically rerun when non-CMake dependency is deleted
  file(APPEND ${ACD_CMAKE_LISTS_ABSOLUTE})

  add_subdirectory(${ACD_SOURCE_ABSOLUTE} ${ACD_BINARY_ABSOLUTE})
endfunction()

add_cmake_dependency(
  NAME glad
  URL https://github.com/Dav1dde/glad/archive/c.tar.gz
  SOURCE glad-c
  INCLUDE include
)
add_library(glad ${LIBRARY_DIRECTORY}/glad/glad-c/src/glad.c)

add_cmake_dependency(
  NAME glfw
  URL https://github.com/glfw/glfw/archive/3.1.1.tar.gz
  SOURCE glfw-3.1.1
  INCLUDE include
)

add_cmake_dependency(
  NAME jsoncpp
  URL https://github.com/open-source-parsers/jsoncpp/archive/master.tar.gz
  SOURCE jsoncpp-master
  INCLUDE include
)

include_directories(include)

add_subdirectory(res)
get_property(STRING_PATHS GLOBAL PROPERTY STRING_PATHS_PROPERTY)
foreach(STRING_PATH ${STRING_PATHS})
  add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/${STRING_PATH}.txt
    COMMAND ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${STRING_PATH} -P BuildString.cmake
    DEPENDS ${CMAKE_SOURCE_DIR}/${STRING_PATH}
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )
  list(APPEND STRINGS_DEPENDS ${CMAKE_BINARY_DIR}/${STRING_PATH}.txt)
endforeach()
add_custom_target(strings DEPENDS ${STRINGS_DEPENDS})
include_directories(${CMAKE_BINARY_DIR}/res)

add_subdirectory(src)
get_property(SOURCES GLOBAL PROPERTY SOURCES_PROPERTY)
add_library(block_game_lib ${SOURCES})
add_dependencies(block_game_lib strings)
target_link_libraries(block_game_lib
  glad
  glfw ${GLFW_LIBRARIES}
  jsoncpp_lib_static
)

add_executable(block_game src/main.cc)
target_link_libraries(block_game block_game_lib)
