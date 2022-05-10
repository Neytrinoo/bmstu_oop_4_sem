#ifndef LAB_02_EXCEPTIONS_H
#define LAB_02_EXCEPTIONS_H

#include <exception>
#include <string>

class ListBaseError : public std::exception
{
public:
    explicit ListBaseError(
            std::string filename,
            std::string classname,
            int line,
            const char *time,
            std::string info)
    {
        message = "\nIn " + filename +
                  "\nInside " + classname + " class" +
                  "\nAt line " + std::to_string(line) +
                  "\nAt time " + time +
                  "\nInfo: " + info;
    }

    virtual const char *what() const noexcept override
    {
        return message.c_str();
    }

    virtual ~ListBaseError() {}

protected:
    std::string message;
};

class ListEmptyError : public ListBaseError {
public:
    ListEmptyError(
            std::string filename,
            std::string classname,
            int line,
            const char *time,
            std::string info = "List is empty") : ListBaseError(filename, classname, line, time, info) {}
};

class ListMemoryError : public ListBaseError {
public:
    ListMemoryError(
            std::string filename,
            std::string classname,
            int line,
            const char *time,
            std::string info = "Memory allocation error") : ListBaseError(filename, classname, line, time, info) {}
};

class ListIteratorError : public ListBaseError {
public:
    ListIteratorError(
            std::string filename,
            std::string classname,
            int line,
            const char *time,
            std::string info = "Invalid iterator") : ListBaseError(filename, classname, line, time, info) {}
};

#endif //LAB_02_EXCEPTIONS_H
