#include "Visualization.h"

// Функция для рендеринга графа в изображение
void Visualization::renderGraph(const std::string& dotFile, const std::string& outputFile) {
    //std::string command = "dot -Tpng " + dotFile + " -o " + outputFile;
    std::string command = "dot -Tsvg " + dotFile + " -o " + outputFile;
   
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Ошибка: не удалось выполнить команду Graphviz\n";
    }
    else {
        std::cout << "Граф сохранён в " << outputFile << "\n";
    }
}