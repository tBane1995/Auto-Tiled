cmake_minimum_required(VERSION 3.10)
project(Auto-Tiled VERSION 1.0)

add_executable(${PROJECT_NAME} Auto-Tiled/main.cpp)

target_sources(${PROJECT_NAME} PRIVATE
    Auto-Tiled/window.hpp
    Auto-Tiled/SFML_intro.hpp
    Auto-Tiled/mouse.hpp
    Auto-Tiled/elementGUI.hpp
    Auto-Tiled/palette.hpp
    Auto-Tiled/map.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# set the SFML lib
set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML")

# set the packages SFML
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# set the working directory (assets)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Auto-Tiled"
)

# set the path for SFML bin
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;C:\\SFML-2.6.2\\bin"
)