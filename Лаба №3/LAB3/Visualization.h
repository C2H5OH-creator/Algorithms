#pragma once

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>


class Visualization
{
public: 
    // Функция для рендеринга графа в изображение
        void renderGraph(const std::string & dotFile, 
                         const std::string & outputFile);
};

