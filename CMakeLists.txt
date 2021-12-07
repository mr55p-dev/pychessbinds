cmake_minimum_required(VERSION 3.15)

set(PROJ pychessbinds)
set(SRCS
	${PROJ}/test.cpp 
	${PROJ}/log.cpp 
	${PROJ}/test.hpp 
	${PROJ}/log.hpp 
	${PROJ}/piece.cpp 
	${PROJ}/piece.hpp
	${PROJ}/position.cpp
	${PROJ}/position.hpp
)
	

project(${PROJ})

include_directories(${PROJ})

add_executable(${PROJ} "${SRCS}") 
