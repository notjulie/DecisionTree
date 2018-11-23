// =========================================================================
//    DecisionFeature.cpp
//    Author: Randy Rasmussen
//    Copyright: none, use at your own risk and to your heart's content
//
//		Contains the non-templated implementation of decision tree features.
// =========================================================================


#include "DecisionFeature.h"


/// <summary>
/// In order for the FeatureSetInfo class to sniff a structure to determine what decision
/// features it contains, it is allowed to hook our constructor.  A specific instance of
/// FeatureSetInfo only does this temporarily, once, during its own construction.
/// </summary>
thread_local std::function<void(AbstractDecisionFeature *)> AbstractDecisionFeature::constructorCallback
   = [](AbstractDecisionFeature *) {};


/// <sumary>
/// Initializes a new instance of class AbstractDecisionFeature
/// </sumary>
AbstractDecisionFeature::AbstractDecisionFeature(void)
{
   // notify the callback that a new object is being constructed... we allow this callback
   // so that datasets can sniff the elements of a structure to find features that it contains
   constructorCallback(this);
}


/// <sumary>
/// Inequality operator
/// </sumary>
bool AbstractDecisionFeature::operator!=(const AbstractDecisionFeature &f) const
{
   return Compare(f) != 0;
}


/// <sumary>
/// Less than operator
/// </sumary>
bool AbstractDecisionFeature::operator<(const AbstractDecisionFeature &f) const
{
   return Compare(f) < 0;
}


