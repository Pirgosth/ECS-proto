add_subdirectory(Implementation)

target_sources(ECS
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/BaseSystem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/System.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MonoSystem.hpp
)