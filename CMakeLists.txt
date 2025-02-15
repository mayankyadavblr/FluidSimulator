cmake_minimum_required(VERSION 3.28.0)
project(Fluid_Simulator VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Fluid_Simulator 
    src/window_sfml.cpp
    src/frame.cpp 
    src/main.cpp 
    src/particle.cpp 
    src/vector.cpp
    )

target_compile_features(Fluid_Simulator PRIVATE cxx_std_17)
target_link_libraries(Fluid_Simulator PRIVATE SFML::Graphics)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
