#include "Todo.h"

#include <string>
#include <vector>
#include <optional>

#ifndef TODOAPP_TODOMANAGER_H
#define TODOAPP_TODOMANAGER_H


class TodoManager {
public:
    static std::vector<Todo> TodoList;
    static std::vector<std::string> AllCategories;

    static void addTodoToList(const Todo &todo);

    static void removeTodo(const Todo &todo);

    static void updateTodo(Todo &todo);

    static std::string retrieveUserInput(std::string choice);

    static void performActionsBasedOnChoice(std::string &choice, Todo &todo);

    static void updateCategory(Todo &todo);

    static void updateDescription(Todo &todo);

    static void updateTitle(Todo &todo);

    static std::optional<Todo> findTodo(int id);

    static bool is_null_or_whitespace(const std::string &input);

    static std::optional<size_t> findCategoryIndex(std::string &value);

    static void displayAllTodos();

    static std::optional<int> findTodoIndex(int id);

    static void DisplayCategory(const str& categoryName);

    static void DisplayAllCategories();

    static void SearchTodoByTitle(const std::string &TodoName);

    static void TodoListToJson();

    static void JsonListParse(const std::vector<nlohmann::json>& jsonObj, const std::string& typeOfList);

    static void JsonToInstance(const nlohmann::basic_json<> &todoObj);
};


#endif //TODOAPP_TODOMANAGER_H
