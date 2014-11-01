cmake_minimum_required(VERSION 2.8.3)
project(youbot_windows_demo)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
find_package(youbotDriver REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread date_time filesystem system regex)

add_definitions(-DYOUBOT_CONFIGURATIONS_DIR=\"${youbotDriver_CONFIG_DIR}\")
add_definitions(-DWIN32_LEAN_AND_MEAN)

include_directories(${youbotDriver_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(youbot_windows_demo src/main.cpp)

target_link_libraries(youbot_windows_demo ${youbotDriver_LIBRARIES} ${Boost_LIBRARIES})