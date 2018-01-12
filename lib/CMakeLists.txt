add_executable(slit_logic STATIC field.cpp sat.cpp ccc.cpp)

target_include_directories(slit_logic PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(slit_logic PUBLIC ${SFML_INCLUDE})
add_dependencies(slit_logic sfml)
target_link_libraries(slit_logic PUBLIC slit_entity)
