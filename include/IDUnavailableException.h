#include <exception>
#include <string>
class IDUnavailableException : std::exception {
  std::string message;

public:
  IDUnavailableException(std::string message);
  virtual const char *what() const noexcept override;
};
