add_subdirectory(Archetype)
add_subdirectory(System)

target_sources(ECS
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Component.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ComponentManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Engine.cpp
)