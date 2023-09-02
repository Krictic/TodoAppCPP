//
// Created by pedro on 01/09/2023.
//

#ifndef TODOAPP_JSONMANAGER_H
#define TODOAPP_JSONMANAGER_H
#include <nlohmann/json.hpp>
#include <fstream>

class JsonManager {
public:
    static nlohmann::json loadJson(const std::string& filePath);
    static void saveJSon(const std::vector<nlohmann::json> &jsonObjList, const std::string& filePath);
};


#endif //TODOAPP_JSONMANAGER_H
