# Allow for relative headers import
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(
    ECS
    main.cpp
)

target_compile_features(ECS INTERFACE cxx_std_17)

add_subdirectory(Engine)

find_package(SFML COMPONENTS system graphics audio REQUIRED)

target_link_libraries(ECS sfml-system sfml-window sfml-graphics sfml-audio)

add_custom_command(TARGET ECS PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:ECS>/assets)