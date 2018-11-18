// =========================================================================
//    DecisionTreeException.cpp
//    Author: Randy Rasmussen
//    Copyright: none, use at your own risk and to your heart's content
//
//		DecisionTreeException class... no surprises.
// =========================================================================


#include "DecisionTreeException.h"

DecisionTreeException::DecisionTreeException(const std::string &message)
   : std::runtime_error(message)
{
}
