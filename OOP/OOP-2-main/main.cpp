#include <iostream>
#include "octal.hpp"
 
int main()
{
    try
    {
        std::string value1, value2;
        char op;
        std::cout << "Enter an expression like: <value operator value> (separated by a space)" << std::endl;
        std::cin >> value1 >> op >> value2; 
        Octal number1 = Octal(value1), number2 = Octal(value2);
        switch (op)
        {
            case '+':
                std::cout << (number1 + number2).to_string() << std::endl;
                break;
            case '-':
                std::cout << (number1 - number2).to_string() << std::endl;
                break; 
            case '>':
                std::cout << (number1 > number2) << std::endl;
                break;
            case '<':
                std::cout << (number1 < number2) << std::endl;
                break;
            case '=':
                std::cout << (number1 == number2) << std::endl;
                break;
            default:
                std::cout << "Incorrect expression" << std::endl;
                break;
        }
    }
    catch (const std::invalid_argument& error) // what() - вывод ошибки в виде строки
    {
        std::cout << "Invalid argument: " << error.what() << std::endl;
    }
    catch(const std::underflow_error& error)
    {
        std::cout << "Underflow error: " << error.what() << std::endl;
    }
 
    return 0;
}