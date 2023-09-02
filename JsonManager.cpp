#include "JsonManager.h"

nlohmann::json JsonManager::loadJson(const std::string& filePath) {
    std::ifstream input(filePath);
    if (!input.is_open()) {
        throw std::runtime_error("Could not open file for reading");
    }

    std::string strJson((std::istreambuf_iterator<char>(input)),
                        std::istreambuf_iterator<char>());

    nlohmann::json jsonObjArray = nlohmann::json::parse(strJson);

    std::vector<nlohmann::json> jsonObjList = jsonObjArray;

    return jsonObjList;
}

void JsonManager::saveJSon(const std::vector<nlohmann::json> &jsonObjList, const std::string& filePath) {
    std::ofstream output(filePath);
    if (!output.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }
    nlohmann::json json(jsonObjList);
    output << json.dump(4);
}