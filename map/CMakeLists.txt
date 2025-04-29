include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/data)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/corner_data)

add_executable(test ${CMAKE_CURRENT_SOURCE_DIR}/data/test/code.cpp)
add_executable(map_one ${CMAKE_CURRENT_SOURCE_DIR}/data/one/code.cpp)
add_executable(map_two ${CMAKE_CURRENT_SOURCE_DIR}/data/two/code.cpp)
add_executable(map_three ${CMAKE_CURRENT_SOURCE_DIR}/data/three/code.cpp)
add_executable(map_four ${CMAKE_CURRENT_SOURCE_DIR}/data/four/code.cpp)
add_executable(map_five ${CMAKE_CURRENT_SOURCE_DIR}/data/five/code.cpp)
add_executable(corner_one ${CMAKE_CURRENT_SOURCE_DIR}/corner_data/1.cpp)
add_executable(corner_two ${CMAKE_CURRENT_SOURCE_DIR}/corner_data/2.cpp)
add_executable(corner_three ${CMAKE_CURRENT_SOURCE_DIR}/corner_data/3.cpp)

add_test(NAME map_one COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/map_one >/tmp/one_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/data/one/answer.txt /tmp/one_out.txt>/tmp/one_diff.txt")
add_test(NAME map_two COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/map_two >/tmp/two_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/data/two/answer.txt /tmp/two_out.txt>/tmp/two_diff.txt")
add_test(NAME map_three COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/map_three >/tmp/three_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/data/three/answer.txt /tmp/three_out.txt>/tmp/three_diff.txt")
add_test(NAME map_four COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/map_four >/tmp/four_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/data/four/answer.txt /tmp/four_out.txt>/tmp/four_diff.txt")
add_test(NAME map_five COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/map_five >/tmp/five_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/data/five/answer.txt /tmp/five_out.txt>/tmp/five_diff.txt")

add_test(NAME corner_one COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/corner_one >/tmp/1_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/corner_data/1.txt /tmp/1_out.txt>/tmp/1_diff.txt")
add_test(NAME corner_two COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/corner_two >/tmp/2_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/corner_data/2.txt /tmp/2_out.txt>/tmp/2_diff.txt")
add_test(NAME corner_three COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/corner_three >/tmp/3_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/corner_data/3.txt /tmp/3_out.txt>/tmp/3_diff.txt")
