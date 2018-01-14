add_library(sseq_core STATIC graph.cpp)

target_include_directories(sseq_core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(sseq_core PRIVATE cryptominisat5)
