
#ifndef DECISIONTREEEXCEPTION_H
#define DECISIONTREEEXCEPTION_H

#include <stdexcept>

class DecisionTreeException : public std::runtime_error {
public:
   DecisionTreeException(const std::string &message)
      : std::runtime_error(message)
   {
   }
};

#endif
