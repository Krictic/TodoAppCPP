cmake_minimum_required(VERSION 3.26)
project(TodoApp)

set(CMAKE_CXX_STANDARD 20)

add_executable(TodoApp main.cpp
        Todo.cpp
        Todo.h
        TodoManager.cpp
        TodoManager.h
        UI.cpp
        JsonManager.cpp
)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(TodoApp PRIVATE nlohmann_json::nlohmann_json)