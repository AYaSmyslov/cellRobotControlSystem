project (240510_robot CXX)

set(SOURCES main.cpp
	declare.cpp
	print.cpp
	Robot.cpp
	Platform.cpp
	tools.cpp
	Variable.cpp
	Parser.cpp
	Expression.cpp
	Func.cpp
)

set(HEADERS
	Variable.h
	Parser.h
	commands.h
	Robot.h
	Platform.h
	Expression.h
	Func.h
)


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
)

