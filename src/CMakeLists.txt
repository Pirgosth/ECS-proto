# Allow for relative headers import
include_directories(${CMAKE_SOURCE_DIR}/src)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(
    ECS
    main.cpp
    Archetype.cpp
    ArchetypeGraph.cpp
    TypeId.hpp
    Types.cpp
    HeterogeneousContainer.cpp
)

target_compile_features(ECS INTERFACE cxx_std_17)

# add_subdirectory(Engine)

find_package(SFML COMPONENTS system graphics audio REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(ECS sfml-system sfml-window sfml-graphics sfml-audio nlohmann_json::nlohmann_json)

# add_custom_command(TARGET ECS PRE_BUILD
                #    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    #    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:ECS>/assets)