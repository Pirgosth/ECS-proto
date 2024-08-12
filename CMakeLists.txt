cmake_minimum_required(VERSION 3.12)

include(GNUInstallDirs)
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

if(WIN32)
    set (BUILD_SHARED_LIBS OFF)
endif()    

project(ECS VERSION 0.0.1 DESCRIPTION "Simple ECS build in C++" LANGUAGES CXX)

find_package(SFML COMPONENTS system graphics audio REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

if (WIN32)
    unset(CMAKE_INSTALL_PREFIX CACHE)
endif()

add_library(${CMAKE_PROJECT_NAME})

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

configure_file(ECS.pc.in ECS.pc @ONLY)

# Allow for relative headers import
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/ECS)

add_subdirectory(src)

target_compile_features(ECS INTERFACE cxx_std_17)
target_compile_options(ECS PRIVATE -Wall -Wextra -Wpedantic)

if(WIN32)
    target_link_libraries(ECS sfml-system-s sfml-window-s sfml-graphics-s sfml-audio-s nlohmann_json::nlohmann_json)
else()
    target_link_libraries(ECS sfml-system sfml-window sfml-graphics sfml-audio nlohmann_json::nlohmann_json)
endif()

install(TARGETS ${CMAKE_PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/" # source directory
    DESTINATION "include" # target directory
    FILES_MATCHING # install only matched files
    PATTERN "*.hpp" # select header files
)

install(FILES ${CMAKE_BINARY_DIR}/ECS.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

# add_custom_command(TARGET ECS PRE_BUILD
#                    COMMAND ${CMAKE_COMMAND} -E copy_directory
#                        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:ECS>/assets)