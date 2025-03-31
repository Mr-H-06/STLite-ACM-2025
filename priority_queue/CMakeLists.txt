include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/data)
add_executable(priority_queue_one ${CMAKE_CURRENT_SOURCE_DIR}/data/one/code.cpp)
add_executable(priority_queue_two ${CMAKE_CURRENT_SOURCE_DIR}/data/two/code.cpp)
add_executable(priority_queue_three ${CMAKE_CURRENT_SOURCE_DIR}/data/three/code.cpp)
add_executable(priority_queue_four ${CMAKE_CURRENT_SOURCE_DIR}/data/four/code.cpp)
add_executable(priority_queue_five ${CMAKE_CURRENT_SOURCE_DIR}/data/five/code.cpp)
add_executable(priority_queue_six ${CMAKE_CURRENT_SOURCE_DIR}/data/six/code.cpp)
add_test(NAME priority_queue_one COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/priority_queue_one >/tmp/one_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/data/one/answer.txt /tmp/one_out.txt>/tmp/one_diff.txt")
add_test(NAME priority_queue_two COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/priority_queue_two >/tmp/two_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/data/two/answer.txt /tmp/two_out.txt>/tmp/two_diff.txt")
add_test(NAME priority_queue_three COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/priority_queue_three >/tmp/three_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/data/three/answer.txt /tmp/three_out.txt>/tmp/three_diff.txt")
add_test(NAME priority_queue_four COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/priority_queue_four >/tmp/four_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/data/four/answer.txt /tmp/four_out.txt>/tmp/four_diff.txt")
add_test(NAME priority_queue_five COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/priority_queue_five >/tmp/five_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/data/five/answer.txt /tmp/five_out.txt>/tmp/five_diff.txt")
add_test(NAME priority_queue_six COMMAND sh -c "${CMAKE_CURRENT_BINARY_DIR}/priority_queue_six >/tmp/six_out.txt\
        && diff -u ${CMAKE_CURRENT_SOURCE_DIR}/data/six/answer.txt /tmp/six_out.txt>/tmp/six_diff.txt")