add_executable(benchmark main.cpp whole.cpp)

add_dependencies(benchmark googlebench)
target_include_directories(benchmark PRIVATE ${GOOGLEBENCH_INCLUDE})
target_link_libraries(benchmark libbenchmark.a pthread)
target_link_libraries(benchmark sseq_core)
