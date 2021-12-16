# /* I, Ellis Lunnon, have read and understood the School's Academic Integrity Policy, as well as guidance relating to this  */
# /* module, and confirm that this submission complies with the policy. The content of this file is my own original work,  */
# /* with any significant material copied or adapted from other sources clearly indicated and attributed. */


cmake_minimum_required(VERSION 3.15)

set(PROJ PyChessBinds)
set(ALLSRCS
	${PROJ}/log.cpp 
	${PROJ}/log.hpp 
	${PROJ}/piece.cpp 
	${PROJ}/piece.hpp
	${PROJ}/position.cpp
	${PROJ}/position.hpp
	${PROJ}/move_analyser.cpp
	${PROJ}/move_analyser.hpp
)
set(LIBSRCS
	${PROJ}/bindings.cpp
	${PROJ}/bindings.hpp
    ${PROJ}/move_analyser.cpp
    ${PROJ}/move_analyser.hpp
	${PROJ}/piece.cpp 
	${PROJ}/piece.hpp
	${PROJ}/position.cpp
	${PROJ}/position.hpp
)
set(TESTSRCS
	${PROJ}/test.cpp
	${PROJ}/test.hpp
)
project(${PROJ} LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")


include_directories(${PROJ})

add_subdirectory(lib/pybind11)
pybind11_add_module(libpychess MODULE ${LIBSRCS})

add_executable(${PROJ} "${ALLSRCS}" "${TESTSRCS}")
set_property(TARGET ${PROJ} PROPERTY CXX_STANDARD 17)
