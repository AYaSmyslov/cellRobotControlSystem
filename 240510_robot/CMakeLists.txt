project (240510_robot CXX)

set(SOURCES main.cpp)
ADD_CLASS(SOURCES Variable)
ADD_CLASS(SOURCES Robot)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
	# ncurses
)

