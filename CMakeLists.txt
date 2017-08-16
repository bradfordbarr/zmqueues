#-----------------------------------------------------------------------------
# Preamble
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0)
project(zmqueues VERSION 0.0.1)

#-----------------------------------------------------------------------------
# Compiler flags
#-----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_INIT "-Werror -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-fprofile-arcs -ftest-coverage")

#-----------------------------------------------------------------------------
# Executables
#-----------------------------------------------------------------------------
add_executable(push src/push.cc src/utils.cc)
add_executable(pull src/pull.cc src/utils.cc)
add_executable(reactor src/reactor.cc src/utils.cc)
add_executable(pub src/pub.cc src/utils.cc)
add_executable(sub src/sub.cc src/utils.cc)

#-----------------------------------------------------------------------------
# Special headers
#-----------------------------------------------------------------------------
include_directories("${PROJECT_SOURCE_DIR}/src")

#-----------------------------------------------------------------------------
# Special libraries
#-----------------------------------------------------------------------------
find_library(ZMQPP NAMES zmqpp zmqpp4)
target_link_libraries(push ${ZMQPP})
target_link_libraries(pull ${ZMQPP})
target_link_libraries(reactor ${ZMQPP})
target_link_libraries(pub ${ZMQPP})
target_link_libraries(sub ${ZMQPP})

find_library(LIBZMQ NAMES zmq)
target_link_libraries(push ${LIBZMQ})
target_link_libraries(pull ${LIBZMQ})
target_link_libraries(reactor ${LIBZMQ})
target_link_libraries(pub ${LIBZMQ})
target_link_libraries(sub ${LIBZMQ})
