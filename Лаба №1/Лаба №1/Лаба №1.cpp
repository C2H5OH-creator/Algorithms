#include <iostream>

//#include "CustomList.h"
#include "CustomVector.h"
#include "CustomVector.cpp"
#include "CustomStack.h"

// Типы элементов в строке
enum ElementType { NUMBER, OPERATOR, FUNCTION, OPEN_PAREN, CLOSE_PAREN };

// Структура для сопоставления элемента с его типом
struct Element {
    std::string value;
    ElementType type;
};

// Функция для определения приоритета операторов
int GetOperatorPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3; 
    return 0;
}

// Функция для разбиения строки на элементы
CustomVector<Element> Tokenize(const std::string& expression) {
    CustomVector<Element> elements;
    std::string currentToken;

    for (size_t i = 0; i < expression.size(); i++) {
        char c = expression[i];

        if (isspace(c)) continue; // Пропускаем пробелы

        // Если число (поддерживаем десятичные дроби)
        if (isdigit(c) || (c == '.' && !currentToken.empty() && isdigit(currentToken.back()))) {
            currentToken += c;
        }
        else {
            if (!currentToken.empty()) {
                elements.PushBack({ currentToken, NUMBER });
                currentToken.clear();
            }

            //sin, cos
            if (isalpha(c)) {
                std::string func;
                while (isalpha(expression[i])) {
                    func += expression[i++];
                }
                i--; 
                elements.PushBack({ func, FUNCTION });
            }

            // Операторы и скобки
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                elements.PushBack({ std::string(1, c), OPERATOR });
            }
            else if (c == '(') {
                elements.PushBack({ std::string(1, c), OPEN_PAREN });
            }
            else if (c == ')') {
                elements.PushBack({ std::string(1, c), CLOSE_PAREN });
            }
        }
    }

    if (!currentToken.empty()) {
        elements.PushBack({ currentToken, NUMBER });
    }

    return elements;
}

// Отладочная печать разобранных элементов
void PrintTokens(const CustomVector<Element>& elements) {
    for (const auto& element : elements) {
        std::cout << "Token: " << element.value << " Type: "
            << (element.type == NUMBER ? "Number" :
                element.type == OPERATOR ? "Operator" :
                element.type == FUNCTION ? "Function" :
                element.type == OPEN_PAREN ? "Open Parenthesis" : "Close Parenthesis")
            << std::endl;
    }
}

CustomVector<Element> ToPostfix(const CustomVector<Element>& elements) {
    CustomStack<Element> operatorStack; // Стек для операторов
    CustomVector<Element> output; // Вектор для результата

    for (const auto& element : elements) {
        if (element.type == NUMBER || element.type == FUNCTION) {
            // Если это число или функция, добавляем его в output
            output.PushBack(element);
        }
        else if (element.type == OPERATOR) {
            // Обрабатываем оператор
            while (!operatorStack.Empty() &&
                GetOperatorPriority(operatorStack.Top().value[0]) 
                >= GetOperatorPriority(element.value[0])) {
                output.PushBack(operatorStack.Top());
                operatorStack.Pop();
            }
            operatorStack.Push(element); // Добавляем текущий оператор в стек
        }
        else if (element.type == OPEN_PAREN) {
            //Добавляем в стек открывающуюся скобку
            operatorStack.Push(element);
        }
        else if (element.type == CLOSE_PAREN) {
            // Обрабатываем закрывающую скобку
            while (!operatorStack.Empty() && operatorStack.Top().type != OPEN_PAREN) {
                output.PushBack(operatorStack.Top());
                operatorStack.Pop();
            }
            operatorStack.Pop(); // Удаляем открывающуюся скобку из стека
        }
    }

    // Переносим оставшиеся операторы в выходной вектор
    while (!operatorStack.Empty()) {
        output.PushBack(operatorStack.Top());
        operatorStack.Pop();
    }

    return output;
}

int main() {
    std::string equation;
    std::cout << "Введите строку для преобзования в обратную польскую запись: ";
    std::cin >> equation;

    CustomVector<Element> postfix = ToPostfix(Tokenize(equation));

    // Печать результата
    std::cout << "Обратная польская нотация: ";
    for (const auto& elem : postfix) {
        std::cout << elem.value << " ";
    }
    std::cout << std::endl;
}