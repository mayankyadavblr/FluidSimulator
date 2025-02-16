cmake_minimum_required(VERSION 3.28.0)
project(FluidSim VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(FluidSim 
src/frame.cpp 
src/main.cpp 
src/particle.cpp 
src/vector.cpp
src/sfml_test.cpp)

target_compile_features(FluidSim PRIVATE cxx_std_17)
target_link_libraries(FluidSim PRIVATE SFML::Graphics)
include(CTest)
enable_testing()

