cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(RBTree)
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(project_sources mainwindow.cpp tree.cpp main.cpp)
set(project_headers mainwindow.h tree.h)
set(project_ui mainwindow.ui)

qt5_wrap_ui(ui_wrap ${project_ui})
qt5_wrap_cpp(moc_sources ${project_headers})
add_executable(RBTree 
	${project_sources} 
	${project_headers}
	${ui_wrap} 
	${moc_sources})
target_link_libraries(RBTree 
	PUBLIC
	Qt5::Core
	Qt5::Gui 
	Qt5::Widgets)

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)
