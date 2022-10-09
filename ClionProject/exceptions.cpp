#include "exceptions.h"

/*
MyException::MyException(const std::string& error_message) {
    this->message += error_message;
}

const char* MyException::what() {
    return (this->message).c_str();
}

void ThrowMyException(const std::string& error_message) {
    throw MyException(error_message);
}

void ReportError(const std::string& error_message) {
    try {
        ThrowMyException(error_message);
    } catch (MyException& my_exception) {
        std::cout << my_exception.what() << "\n";
    }
}
*/

void ReportError(const std::string& error_message) {
    std::cout << "Error: " << error_message << "\n";
}
