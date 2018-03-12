cmake_minimum_required (VERSION 2.6)
project (scefig)
include(ExternalProject)
ExternalProject_Add(eigen
  PREFIX toto
  GIT_REPOSITORY https://github.com/eigenteam/eigen-git-mirror
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/contrib/eigen_install
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/contrib/eigen_install
  UPDATE_COMMAND "" # prevents updating eigen in order to prevent eigen reconfigure and build at every build
)

#  GIT_TAG "master"
#  URL ...project_a.tar.gz
#  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/project_a
#  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>

#include(${CMAKE_CURRENT_BINARY_DIR}/lib/project_a/project_a-targets.cmake)


ExternalProject_Get_Property(eigen install_dir)
include_directories(${install_dir}/include/eigen3)
message("install_dir=${install_dir}")

# target_link_libraries(project_b_exe ${install_dir}/lib/alib.lib)

macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

use_cxx11()


add_library(libscefig scene3d.cpp polyline.cpp plane.cpp asymptoterenderer.cpp geom.cpp)
add_dependencies(libscefig eigen)

add_executable(unittest1 unittest1.cpp)
add_dependencies(unittest1 eigen)
target_link_libraries(unittest1 libscefig)


