// =========================================================================
//    DecisionTreeException.cpp
//    Author: Randy Rasmussen
//    Copyright: none, use at your own risk and to your heart's content
//
//		DecisionTreeException class... no surprises.
// =========================================================================

#ifndef DECISIONTREEEXCEPTION_H
#define DECISIONTREEEXCEPTION_H

#include <stdexcept>

/// <summary>
/// Base class for decision tree exceptions
/// <summary>
class DecisionTreeException : public std::runtime_error {
public:
   DecisionTreeException(const std::string &message);
};

#endif
