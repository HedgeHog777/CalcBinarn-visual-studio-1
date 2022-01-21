#include <iostream>

#define BASE_TYPE long int
#define BASE_SIZE 32
#define DOUBLE_TYPE long long int
#define DOUBLE_SIZE (BASE_NUM * 2)
#define NUM_SYS_TYPE unsigned short

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::size_t;

BASE_TYPE charToNumber(const char c, const NUM_SYS_TYPE num_sys) {
    BASE_TYPE result;
    if (('0' <= c) && (c <= '9')) {
        result = c - '0';
    }
    else if (('A' <= c) && (c <= 'Z')) {
        result = c - 'A' + 10;
    }
    else if (('a' <= c) && (c <= 'z')) {
        result = c - 'a' + 10;
    }
    
    if ((result >= num_sys) || (result < 0)) {
        cout << endl << "Wrong input " << c << " num_sys " << num_sys
            << " => " << result << endl;
        result = 0;
    }
    return result;
}

BASE_TYPE stringToNumber(const string& str, const NUM_SYS_TYPE num_sys) {
    BASE_TYPE sign = 2 * (str[0] != '-') - 1; // -1 or 1
    size_t start = (str[0] == '-') + (str[0] == '+'); //  1 or 0
    
    BASE_TYPE mult = 1;
    BASE_TYPE result = 0;
    for (size_t i = start; i < str.size(); i++) {
        result *= mult;
        result += charToNumber(str[i], num_sys);
        mult = num_sys;
    }
    return sign * result;
}

char numberToChar(const BASE_TYPE number)
{
    if ((0 <= number) && (number <= 9)) {
        return number + '0';
    }
    else if ((10 <= number) && (number <= 10 + ('Z' - 'A'))) {
        return number + 'A' - 10;
    }
    cout << "Wrong number to char " << number << endl;
    return 'x';
}

string numberToString(DOUBLE_TYPE number, const NUM_SYS_TYPE num_sys) {
    BASE_TYPE digit;
    string reversed, result;
    if (number < 0) {
        result = '-';
        number = -number;
    } else if (number == 0) {
        return "0";
    }
    
	while (number > 0) {
	    digit = number % num_sys;
	    reversed += numberToChar(digit);
	    number /= num_sys;
	}
	for (size_t i = reversed.size(); i > 0; i--) {
	    result += reversed[i-1];
	}
	return result;
}

BASE_TYPE readNumber() {
    string input;
    cout << endl << "Input number as string: ";
    cin >> input;
    int num_sys;
    cout << endl << "Input numeral system: ";
    cin >> num_sys;
    return stringToNumber(input, num_sys);
}

int main()
{
    BASE_TYPE a = readNumber();
    cout << endl << "a = " << a;
    BASE_TYPE b = readNumber();
    cout << endl << "b = " << b;
    
    char operation;
    cout << endl << "Choose operation from +-*/ ";
    cin >> operation;
    int num_sys;
    cout << endl << "Choose output numeral system: ";
    cin >> num_sys;
    
    DOUBLE_TYPE result;
    switch (operation) {
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
               result = a / b;
               break;
    }
    cout << endl << "Result = " << numberToString(result, num_sys);
    return 0;
}