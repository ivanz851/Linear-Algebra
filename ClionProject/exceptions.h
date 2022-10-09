#pragma "once"

/*
#include <exception>
#include <iostream>
#include <string>

class MyException : public std::exception {
public:
    explicit MyException(const std::string& error_message);
    const char* what();
private:
    std::string message = "Error: ";
};

void ThrowMyException(const std::string& s);
void ReportError(const std::string& error_message);

*/

#include <iostream>
#include <string>

void ReportError(const std::string& error_message);
