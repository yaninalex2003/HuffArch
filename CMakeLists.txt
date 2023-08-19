project(hw-02_huffman)

set(CMAKE_CXX_STANDARD 20)
set(FLAGS -Wall -Wextra -Werror)
include_directories(include test)

set(SRC_LIST src/archiver.cpp src/reader.cpp src/writer.cpp src/tree.cpp src/node.cpp src/tree.cpp src/letterstable.cpp src/argparser.cpp src/exceptions.cpp)
add_executable(${PROJECT_NAME} src/main.cpp ${SRC_LIST})
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
add_executable(hw-02_huffman-test test/test.cpp ${SRC_LIST})
target_compile_options(hw-02_huffman-test PRIVATE ${FLAGS})
