project (240510_robot CXX)

set(SOURCES main.cpp)
ADD_CLASS(SOURCES Literal)
ADD_HEADER(SOURCES commands)
ADD_CPP(SOURCES tools)
ADD_CPP(SOURCES declare)
ADD_CPP(SOURCES print)
ADD_CLASS(SOURCES Robot)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
	# ncurses
)

