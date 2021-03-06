#pragma once
#include <exception>
#include <string>
class MessageParsingException : public std::exception{
  std::string message;
  public:
    const char *what() const noexcept override;
    MessageParsingException(std::string msg = "Message Parsing Exception");
};
