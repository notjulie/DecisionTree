
#include "DecisionFeature.h"

thread_local std::function<void(AbstractDecisionFeature *)> AbstractDecisionFeature::constructorCallback
   = [](AbstractDecisionFeature *) {};

AbstractDecisionFeature::AbstractDecisionFeature(void)
{
   // notify the callback that a new object is being constructed... we allow this callback
   // so that datasets can sniff the elements of a structure to find features that it contains
   constructorCallback(this);
}

bool AbstractDecisionFeature::operator!=(const AbstractDecisionFeature &f) const
{
   return Compare(f) != 0;
}

bool AbstractDecisionFeature::operator<(const AbstractDecisionFeature &f) const
{
   return Compare(f) < 0;
}

void AbstractDecisionFeature::RegisterConstructorNotification(const std::function<void(AbstractDecisionFeature *)> &hook)
{
   constructorCallback = hook;
}
