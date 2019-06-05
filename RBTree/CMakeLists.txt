cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(RBTree)
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)
add_executable(RBTree main.cpp mainwindow.cpp tree.cpp mainwindow.h tree.h mainwindow.ui)