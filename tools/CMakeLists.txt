add_executable(main main.cpp)
target_link_libraries(main PRIVATE sseq_core)
target_link_libraries(main PRIVATE boost_program_options)
