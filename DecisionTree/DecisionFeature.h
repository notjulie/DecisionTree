
#ifndef DECISIONFEATURE_H
#define DECISIONFEATURE_H

#include <functional>
#include "DecisionTreeException.h"

class AbstractDecisionFeature {
public:
   AbstractDecisionFeature(void);

   bool operator!=(const AbstractDecisionFeature &f) const {
      throw DecisionTreeException("AbstractDecisionFeature::operator!=: not implemented");
   }

   std::function<bool(const AbstractDecisionFeature &)>GetLessThanComparator(void) const {
      throw DecisionTreeException("AbstractDecisionFeature::GetLessThanComparator: not implemented");
   }

public:
   static void RegisterConstructorNotification(const std::function<void(AbstractDecisionFeature *)> &hook);

private:
   static thread_local std::function<void(AbstractDecisionFeature *)> constructorCallback;
};

template <typename T>
   class DecisionFeature : public AbstractDecisionFeature
{
public:
   DecisionFeature & operator=(const T &newValue) {
      value = newValue;
      return *this;
   }

   T operator*(void) { return value; }

private:
   T  value;
};

#endif
