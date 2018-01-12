file(
  DOWNLOAD https://raw.githubusercontent.com/catchorg/Catch2/7d0db6b8e9f0069c34fca820c70d7e318ddc25ef/single_include/catch.hpp 
  ${CMAKE_CURRENT_BINARY_DIR}/catch.hpp 
  EXPECTED_HASH SHA256=6988c82def026a0b862f43ab122bbbd6051b0b7648bfe04c8a150ef62ca5a0a2)

add_executable(test_all main.cpp graph.cpp)

target_include_directories(test_all PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(test_all PRIVATE sseq_core)
cotire(test_all)

enable_testing()
add_test(AllTests test_all)
