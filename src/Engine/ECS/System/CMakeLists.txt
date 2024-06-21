add_subdirectory(Implementation)

target_sources(ECS
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/BaseSystem.hpp
    ${CMAKE_CURRENT_LIST_DIR}/System.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MonoSystem.hpp
)