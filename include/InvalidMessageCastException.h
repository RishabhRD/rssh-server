#include <exception>
#include <string>
class InvalidMessageCastException : public std::exception{
  std::string message;
  public:
  InvalidMessageCastException(std::string);
  virtual const char* what() const noexcept override;
};
