add_subdirectory(Components)
add_subdirectory(Systems)

target_sources(
    ECS
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Archetype.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ArchetypeGraph.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ECS.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Engine.hpp
    ${CMAKE_CURRENT_LIST_DIR}/HeterogeneousContainer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/System.hpp
    ${CMAKE_CURRENT_LIST_DIR}/TextureManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TypeId.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Types.cpp
)