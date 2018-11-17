
#ifndef DECISIONFEATURE_H
#define DECISIONFEATURE_H

#include <functional>

class AbstractDecisionFeature {
public:
   AbstractDecisionFeature(void);

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
