#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdint>

using BaseType = std::int64_t;
using ResultType = std::int64_t;
using NumeralSystem = std::uint16_t;

BaseType charToNumber(char c, NumeralSystem base);
BaseType stringToNumber(const std::string& str, NumeralSystem base);

char numberToChar(BaseType value);
std::string numberToString(ResultType value, NumeralSystem base);

BaseType readNumber();

BaseType charToNumber(char c, NumeralSystem base)
{
    BaseType result = -1;

    if (c >= '0' && c <= '9')
        result = c - '0';
    else if (c >= 'A' && c <= 'Z')
        result = c - 'A' + 10;
    else if (c >= 'a' && c <= 'z')
        result = c - 'a' + 10;

    if (result < 0 || result >= base)
        throw std::invalid_argument("Invalid digit for selected numeral system.");

    return result;
}


BaseType stringToNumber(const std::string& str, NumeralSystem base)
{
    BaseType sign = (str[0] == '-') ? -1 : 1;
    std::size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;

    BaseType result = 0;

    for (std::size_t i = start; i < str.size(); ++i)
    {
        result *= base;
        result += charToNumber(str[i], base);
    }

    return sign * result;
}

char numberToChar(BaseType number)
{
    if (number >= 0 && number <= 9)
        return static_cast<char>('0' + number);

    if (number >= 10 && number < 36)
        return static_cast<char>('A' + number - 10);

    throw std::invalid_argument("Cannot convert number to character.");
}

std::string numberToString(ResultType number, NumeralSystem base)
{
    BaseType digit;
    std::string reversed;
    std::string result;

    if (number < 0)
    {
        result = '-';
        number = -number;
    }
    else if (number == 0)
    {
        return "0";
    }

    while (number > 0)
    {
        digit = number % base;
        reversed += numberToChar(digit);
        number /= base;
    }

    for (std::size_t i = reversed.size(); i > 0; --i)
        result += reversed[i - 1];

    return result;
}

BaseType readNumber()
{
    std::string input;

    std::cout << "\nInput number: ";
    std::cin >> input;

    NumeralSystem base;

    std::cout << "Input numeral system (2-36): ";
    std::cin >> base;

    if (base < 2 || base > 36)
        throw std::invalid_argument("Numeral system must be between 2 and 36.");

    return stringToNumber(input, base);
}
int main()
{
    try
    {
        BaseType a = readNumber();
        BaseType b = readNumber();

        char operation;

        std::cout << "\nChoose operation (+ - * /): ";
        std::cin >> operation;

        NumeralSystem outputBase;

        std::cout << "\nOutput numeral system: ";
        std::cin >> outputBase;

        ResultType result = 0;

        switch (operation)
        {
            case '+':
                result = a + b;
                break;

            case '-':
                result = a - b;
                break;

            case '*':
                result = a * b;
                break;

            case '/':
                if (b == 0)
                    throw std::runtime_error("Division by zero.");

                result = a / b;
                break;

            default:
                throw std::runtime_error("Unknown operation.");
        }

        std::cout << "\nResult = "
                  << numberToString(result, outputBase)
                  << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << "\nError: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
