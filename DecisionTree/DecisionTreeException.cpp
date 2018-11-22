// =========================================================================
//    DecisionTreeException.cpp
//    Author: Randy Rasmussen
//    Copyright: none, use at your own risk and to your heart's content
//
//		DecisionTreeException class... no surprises.
// =========================================================================


#include "DecisionTreeException.h"

/// <summary>
/// Initializes a new instance of class DecisionTreeException
/// <summary>
DecisionTreeException::DecisionTreeException(const std::string &message)
   : std::runtime_error(message)
{
}
