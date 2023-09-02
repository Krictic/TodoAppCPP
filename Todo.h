#ifndef TODOAPP_TODO_H
#define TODOAPP_TODO_H
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using str = std::string;

class Todo {
public:
    // Static Fields
    static int todoNum;

    // Instance methods
    Todo(const str& title,
         const str& description,
         const str& category);

    Todo();

    void displayTodo();
    [[nodiscard]] nlohmann::json instanceToJson() const;

    // Instance fields
    int id;
    std::string title;
    std::string description;
    std::vector<std::string> categoryList;
    bool completionStatus;
};


#endif //TODOAPP_TODO_H
