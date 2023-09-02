#include "Todo.h"
#include <iostream>

using str = std::string;
using std::cout;
using std::cin;
int Todo::todoNum = 0;

Todo::Todo(const str& title, const str& description, const str& category) {
    this->id = todoNum++;
    this->title = title;
    this->description = description;
    this->categoryList.push_back(category);
    this->completionStatus = false;

}

Todo::Todo() {
    this->id = todoNum++;
    this->title = "";
    this->description = "";
    this->categoryList.emplace_back("");
    this->completionStatus = false;
}



void Todo::displayTodo() {
    str separator(40, '=');
    std::string statusString = this->completionStatus ? "Complete" : "Incomplete";
    cout << separator << std::endl;
    cout << "Id: " << this->id << std::endl;
    cout << "Title: " << this->title << std::endl;
    cout << "Description: " << this->description << std::endl;
    cout << "Categories: " << std::endl;
    for (const auto &category : this->categoryList) {
        cout << "    " << category << std::endl;
    }
    cout << "Status: " << statusString << std::endl;
    cout << separator << std::endl;
}

nlohmann::json Todo::instanceToJson() const {
    nlohmann::json jsonObj;
    jsonObj["title"] = this->title;
    jsonObj["description"] = this->description;
    jsonObj["categoryList"] = this->categoryList;
    jsonObj["completionStatus"] = this->completionStatus;
    jsonObj["id"] = this->id;

    return jsonObj;
}




