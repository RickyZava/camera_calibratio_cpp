cmake_minimum_required(VERSION 3.14)
project(camera_calibration)

set(CMAKE_CXX_STANDARD 17)

# Trova i pacchetti
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

include(FetchContent)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.13.0
)
FetchContent_MakeAvailable(spdlog)

# Crea l'eseguibile
add_executable(calibrate src/main.cpp src/show.cpp src/homographies.cpp)

# Collega OpenCV e imposta gli include di Eigen3 in un solo passaggio
target_link_libraries(calibrate ${OpenCV_LIBS} Eigen3::Eigen spdlog::spdlog)
target_include_directories(calibrate PRIVATE include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
