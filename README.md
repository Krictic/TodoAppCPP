# TodoApp - Command Line Interface

TodoApp is a simple command-line based application developed as a learning project to gain a hands-on experience on C++. 
This is the user's second C++ project. The application allows a user to manage their everyday tasks with the basic CRUD 
functionality (Create, Read, Update, Delete).

## Technology Stack

1. C++
2. CLion 2023.2.1
3. Vcpkg (for package management)
4. nlohmann::json (for JSON handling)
5. CMake (build tool)

## Project Structure

The application is segregated into multiple components, namely the main driver program, a User Interface (U/I) handler, 
a "Todo" object handler, a manager to handle all the "Todo" objects, and a JSON handler module.

### Main.cpp

The main file drives the whole application. It has the primary entry point, the `main` function.

### UI.cpp

This file manages interactions with the user. It handles all user input and output.

### Todo.cpp

This piece of code defines the 'Todo' structure. Each Todo has a title, description, category/ies, and a completion 
status. It also has the functionality to convert an instance of the object to a JSON object.

### TodoManager.cpp

This asset performs the primary operations for the application, including:
- Adding a Todo
- Removing a Todo
- Updating a Todo
- Displaying All Todos
- Saving All Todos
- Loading Pre-existing Todos from a JSON file

In addition, some utility functions are declared and defined within this file to 
aid in the management of the "Todo" structure.

### JsonManager.cpp

This module has the responsibility of converting JSON objects to the 'Todo' structure and vice versa. 
It can read from and write to JSON files.

## Usage

The application provides a simple text-based menu to interact with the application. 
Follow the on-screen prompts to perform desired operations. The application will guide the user through each step of the process.

## Notes

As this is a learning project, feedback and suggestions are welcome. The aim is to constantly update and improve the code as the user continues to learn more about C++ and software development in general.