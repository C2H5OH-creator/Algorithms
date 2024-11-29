#pragma once

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>


class Visualization
{
public:
    // Рекурсивная функция для создания дерева с цветами
    void createBinaryTreeDot(std::ofstream& file, 
            const std::string& parentName, 
            int depth, const std::string& nodeLabel, 
            int& counter, 
            const std::string& internalColor, 
            const std::string& leafColor);
     
    // Функция для создания DOT файла с цветам
    void createDotFile(const std::string & filename, 
                        int depth, 
                        const std::string & nodeLabel,
                        const std::string & internalColor, 
                        const std::string & leafColor);
    
    // Функция для рендеринга графа в изображение
        void renderGraph(const std::string & dotFile, 
                         const std::string & outputFile);
   

};

