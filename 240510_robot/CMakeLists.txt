project (240510_robot CXX)

set(SOURCES main.cpp
	declare.cpp
	print.cpp
	Robot.cpp
	tools.cpp
	Variable.cpp
)

set(HEADERS
	Variable.h
	commands.h
	Robot.h
)


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
)

