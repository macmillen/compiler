cmake_minimum_required(VERSION 3.8)
project(puck)

find_package(Boost COMPONENTS program_options system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(puck ${SOURCE_FILES})
TARGET_LINK_LIBRARIES( puck LINK_PUBLIC ${Boost_LIBRARIES} )
