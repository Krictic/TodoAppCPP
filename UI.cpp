//
// Created by pedro on 01/09/2023.
//

#include <sstream>
#include <iostream>
#include "TodoManager.h"
#include "JsonManager.h"
#include "Todo.h"
#include "UI.h"

void UserInterface() {
    while (true) {
        clearScreen();
        int choice;
        std::cout << "What would you like to do?\n"
                     "1. Add a todo\n"
                     "2. Remove a todo\n"
                     "3. Update a todo\n"
                     "4. Display all todos\n"
                     "5. Display a Category\n"
                     "6. Save All Todos\n"
                     "7. Load Todos\n"
                     "0. Exit\n"
                     "Input -> " ;
        std::cin >> choice;

        switch (choice) {
            case 1:
                addTodo();
                break;
            case 2:
                removeTodo();
                break;
            case 3:
                updateTodo();
                break;
            case 4:
                TodoManager::displayAllTodos();
                break;
            case 5:
                DisplayCategory();
                break;
            case 6:
                SaveTodos();
                break;
            case 7:
                LoadJsonData();
                break;
            case 0:
                return;
            default:
                std::cerr << "Invalid input.\n";
                break;

        }
    }
}

void LoadJsonData() {
    try {
        std::vector<nlohmann::json> todoOBJ = JsonManager::loadJson("./todos.json");
        std::vector<nlohmann::json> categoriesOBJ = JsonManager::loadJson("./allcategories.json");

        TodoManager::JsonListParse(todoOBJ, "todoList");
        TodoManager::JsonListParse(categoriesOBJ, "categories");
    }
    catch(const std::exception& e) {
        std::cerr << "An error occurred while loading Todos and Categories from todos.json and allcategories.json: " << e.what() << std::endl;
        HaltUntilInput();
    }
}

void SaveTodos() {
    try {
        TodoManager::TodoListToJson();
        std::cout << "Todos and Categories saved to todos.json and allcategories.json." << std::endl;
        HaltUntilInput();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while saving Todos and Categories to todos.json and allcategories.json: " << e.what() << std::endl;
        HaltUntilInput();
    } catch (...) {
        std::cerr << "An unknown error occurred while saving Todos and Categories to todos.json and allcategories.json." << std::endl;
        HaltUntilInput();
    }
}

void DisplayCategory() {
    std::cout << "Select a category among the available ones below: " << std::endl;
    TodoManager::DisplayAllCategories();
    std::string categoryChoice;
    std::cout << "Input -> ";
    std::cin >> categoryChoice;
    TodoManager::DisplayCategory(categoryChoice);
    HaltUntilInput();
}



void addTodo() {
    str title, description, category;
    std::cout << "Enter the title: ";
    std::cin >> title;
    std::cout << "Enter the description: ";
    std::cin >> description;
    std::cout << "Enter the category(ies): ";
    std::cin >> category;
    std::istringstream iss(category);
    std::vector<std::string> result;

    for(std::string s; iss >> s; ) {
        result.push_back(s);
    }


    Todo todo = Todo(title, description, category);
    TodoManager::addTodoToList(todo);
    HaltUntilInput();
}

void removeTodo() {
    int id;
    std::cout << "Enter the id of the todo you want to remove:\n";
    std::cin >> id;
    std::optional<Todo> t = TodoManager::findTodo(id);
    if (t.has_value())
        TodoManager::removeTodo(t.value());
    else
        std::cout << "Todo with given id not found.\n";

    HaltUntilInput();
}

void updateTodo() {
    int id;
    std::cout << "Enter the id of the todo you want to update:\n";
    std::cin >> id;
    std::optional<int> todoIndex = TodoManager::findTodoIndex(id);
    if (todoIndex.has_value())
        TodoManager::updateTodo(TodoManager::TodoList[id]);
    else
        std::cout << "Todo with given id not found.\n";

    HaltUntilInput();
}

void clearScreen() {
    #ifdef _WIN32
        std::system ("cls");
    #else
        std::system ("clear");
    #endif
}

void HaltUntilInput() {
    std::string placeholder;
    std::cout << "Type anything and press enter to continue: ";
    std::cin >> placeholder;
}