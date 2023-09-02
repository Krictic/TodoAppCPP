#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#include "TodoManager.h"
#include "JsonManager.h"
#include <iostream>
#include <algorithm>

using str = std::string;
using std::cout;
using std::cin;

const auto TITLE = "title";
const auto DESCRIPTION = "description";
const auto CATEGORY = "categoryList";
const auto STATUS = "status";

str separator(40, '=');

std::vector<Todo> TodoManager::TodoList;
std::vector<std::string> TodoManager::AllCategories;


void TodoManager::addTodoToList(const Todo &todo) {
    TodoList.push_back(todo);
    for (auto & todoCategory : todo.categoryList) {
        bool categoryExists = false;
        for (const auto & category : AllCategories) {
            if (todoCategory == category) {
                categoryExists = true;
                break;
            }
        }
        if (!categoryExists) {
            AllCategories.push_back(todoCategory);
        }
    }
}

void TodoManager::removeTodo(const Todo &todo) {
    TodoList.erase(std::remove_if(TodoList.begin(),
                                  TodoList.end(),
                                  [&todo](const Todo &t) { return t.id == todo.id; }), TodoList.end());
    cout << "Todo " << todo.title << " removed." << std::endl;
}

void TodoManager::updateTodo(Todo &todo) {
    todo.displayTodo();
    cout << "What do you wish to change?" << std::endl;
    str choice;
    choice = retrieveUserInput(choice);
    performActionsBasedOnChoice(choice, todo);
}

str TodoManager::retrieveUserInput(str choice) {
    while (true) {
        cin >> choice;
        if (choice != TITLE && choice != DESCRIPTION && choice != CATEGORY && choice != STATUS) {
            cout << "Choose one of the following options: "
                    "'title', 'description', 'categoryList', 'status'" << std::endl;
            cin.clear();
        } else {
            return choice;
        }
    }
}

void TodoManager::performActionsBasedOnChoice(str &choice, Todo &todo) {
    if (choice == TITLE) {
        updateTitle(todo);
    }
    if (choice == DESCRIPTION) {
        updateDescription(todo);
    }
    if (choice == CATEGORY) {
        updateCategory(todo);
    }
    if (choice == STATUS) {
        todo.completionStatus = !todo.completionStatus;
    }
}

void TodoManager::updateCategory(Todo &todo) {
    str categoryChoice;
    cout << "Do you wish to (add) a new categoryList to this todo or to (replace) it?";
    while (true){
        cin >> categoryChoice;
        if (categoryChoice != "add" && categoryChoice != "replace"){
            cout << "Choose one of the following options: "
                    "'add', 'replace'" << std::endl;
        } else {
            break;
        }
    }
    str categoryName;

    if (categoryChoice == "add") {
        cout << "Please type the name of this new category: ";
        cin >> categoryName;
        todo.categoryList.push_back(categoryName);
    } if (categoryChoice == "replace") {
        cout << "Please type the name of the chosen category among those on the list below: " << std::endl;
        DisplayAllCategories();
        cout << "Input -> ";
        while (true) {
            while (true) {
                cout << "Enter the category name you wish to replace: ";
                cin >> categoryName;
                if (is_null_or_whitespace(categoryName)) {
                    cout << "Invalid Input: is null or white-space";
                } else {
                    break;
                }
            }

            std::optional<size_t> index = findCategoryIndex(categoryName);
            if (index.has_value() && index.value() < AllCategories.size()) {
                cout << "Index is: " << index.value() << std::endl;
                cout << "Enter the new category name: ";
                str newCategoryName;
                cin >> newCategoryName;
                AllCategories[index.value()] = newCategoryName;
                todo.categoryList[index.value()] = newCategoryName;
                cout << "New value (allCategory): " << AllCategories[index.value()] << std::endl;
                break;
            } else {
                cout << "Category not found, please check if the category exists." << std::endl;
            }
        }
    }
}

void TodoManager::DisplayAllCategories() {
    cout << separator << std::endl;
    for (auto &category: AllCategories) {
        cout << category << std::endl;
    }
    cout << separator << std::endl;
}

void TodoManager::updateDescription(Todo &todo) {
    cout << "Enter the new description: ";
    str newDescription;
    cin.ignore();
    getline(cin, newDescription);
    todo.description = newDescription;
}

void TodoManager::updateTitle(Todo &todo) {
    cout << "Enter the new title: ";
    str newTitle;
    cin.ignore();
    getline(cin, newTitle);
    todo.title = newTitle;
}

std::optional<Todo> TodoManager::findTodo(int id) {
    for (auto &todo : TodoList) {
        if (todo.id == id) {
            return todo;
        }
    }

    return std::nullopt;
}

bool TodoManager::is_null_or_whitespace(const str &input) {
    return std::all_of(input.begin(), input.end(), [](unsigned char c){ return ::isspace(c); });
}

std::optional<size_t> TodoManager::findCategoryIndex(str &value) {
    auto it = std::find(AllCategories.begin(), AllCategories.end(), value);

    if (it != AllCategories.end()) {
        int index = std::distance(AllCategories.begin(), it);
        return index;
    }
    else {
        return std::nullopt;
    }
}

void TodoManager::displayAllTodos() {
    for (auto &todo : TodoList) {
        todo.displayTodo();
    }
    std::string placeholder;
    std::cout << "Type anything and press enter to continue: ";
    cin >> placeholder;
}

std::optional<int> TodoManager::findTodoIndex(int id) {
    for (size_t i = 0; i < TodoList.size(); ++i) {
        if (TodoList[i].id == id) {
            return i;
        }
    }

    return std::nullopt;
}

void TodoManager::DisplayCategory(const std::string& categoryName) {
    for (const Todo & todo : TodoList) {
        for (const auto &category: todo.categoryList) {
            if (categoryName == category) {
                std::cout << todo.title << std::endl;
            }
        }
    }
}

void TodoManager::SearchTodoByTitle(const std::string& TodoName) {
    for (const Todo & todo : TodoList) {
        if (TodoName == todo.title) {
            std::cout << todo.title << std::endl;
            return;
        }
    }
}

void TodoManager::TodoListToJson() {
    std::vector<nlohmann::json> todoJsonList;
    std::vector<nlohmann::json> allCategoriesList;
    for (auto & todo : TodoList) {
        nlohmann::json jsonObj = todo.instanceToJson();
        todoJsonList.push_back(jsonObj);
    }

    for (auto & category : AllCategories) {
        nlohmann::json jsonObj = category;
        allCategoriesList.push_back(jsonObj);
    }

    JsonManager::saveJSon(todoJsonList, "./todos.json");
    JsonManager::saveJSon(allCategoriesList, "./allcategories.json");
}

void TodoManager::JsonListParse(const std::vector<nlohmann::json> &jsonObj, const std::string &typeOfList) {
    if (typeOfList == "todoList") {
        TodoList.clear();
        for (const nlohmann::basic_json<>& todoObj : jsonObj) {
            JsonToInstance(todoObj);
        }
    }

    if (typeOfList == "categories") {
        AllCategories.clear();
        for (const nlohmann::basic_json<>& categoryObj : jsonObj) {
            AllCategories.push_back(categoryObj.dump());
        }
    }
}

void TodoManager::JsonToInstance(const nlohmann::basic_json<> &todoObj) {
    if (todoObj.contains("title") and todoObj.contains("description") and
        todoObj.contains("categoryList") and todoObj.contains("completionStatus") and
        todoObj.contains("id")) {
        Todo todo;
        todoObj.at("title").get_to(todo.title);
        todoObj.at("description").get_to(todo.description);
        todoObj.at("categoryList").get_to(todo.categoryList);
        todoObj.at("completionStatus").get_to(todo.completionStatus);
        todoObj.at("id").get_to(todo.id);
        TodoList.push_back(todo);
    } else {
        // Throw an error if the JSON object does not contain the expected keys
        throw std::invalid_argument("Invalid format for Todo JSON object");
    }
}

#pragma clang diagnostic pop