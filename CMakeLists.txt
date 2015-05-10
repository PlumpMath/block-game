cmake_minimum_required(VERSION 3.0)
project("Block Game")
set(LIBRARY_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include (CMakeParseArguments)

function(add_cmake_dependency)
  set(ACD_OPTIONS
    MANUAL
  )
  set(ACD_ONE_VALUE_KEYWORDS
    NAME
    URL
    SOURCE
    INCLUDE
  )
  cmake_parse_arguments(ACD "${ACD_OPTIONS}" "${ACD_ONE_VALUE_KEYWORDS}" "" ${ARGN})

  set(ACD_DIRECTORY ${LIBRARY_DIRECTORY}/${ACD_NAME})
  set(ACD_TGZ ${ACD_NAME}.tgz)
  set(ACD_TGZ_ABSOLUTE ${ACD_DIRECTORY}/${ACD_TGZ})
  set(ACD_SOURCE_ABSOLUTE ${ACD_DIRECTORY}/${ACD_SOURCE})
  set(ACD_CMAKE_LISTS ${ACD_SOURCE_ABSOLUTE}/CMakeLists.txt)
  set(ACD_INCLUDE_ABSOLUTE ${ACD_SOURCE_ABSOLUTE}/${ACD_INCLUDE})
  set(ACD_BINARY ${ACD_DIRECTORY}/bin)

  if(NOT EXISTS ${ACD_CMAKE_LISTS})
    message(STATUS "Downloading ${ACD_URL}")
    file(DOWNLOAD ${ACD_URL} ${ACD_TGZ_ABSOLUTE})
    message(STATUS "Opening ${ACD_TGZ_ABSOLUTE}")
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E tar xzf ${ACD_TGZ}
      WORKING_DIRECTORY ${ACD_DIRECTORY}
    )
  endif()

  if(${ACD_MANUAL})
    file(APPEND ${ACD_CMAKE_LISTS})
  endif()
  add_subdirectory(${ACD_SOURCE_ABSOLUTE} ${ACD_BINARY})
  include_directories(${ACD_INCLUDE_ABSOLUTE})
endfunction()

add_cmake_dependency(MANUAL
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

function(add_sources)
  foreach(SOURCE ${ARGN})
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}.cpp")
  endforeach()
  set_property(GLOBAL APPEND PROPERTY SOURCES_PROPERTY ${SOURCES})
endfunction()

add_subdirectory(src)
include_directories(src)

get_property(SOURCES GLOBAL PROPERTY SOURCES_PROPERTY)
add_executable(block_game ${SOURCES})
target_link_libraries(block_game glad glfw ${GLFW_LIBRARIES})
