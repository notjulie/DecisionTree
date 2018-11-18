
#ifndef DECISIONFEATURE_H
#define DECISIONFEATURE_H

#include <functional>
#include "DecisionTreeException.h"

class AbstractDecisionFeature {
public:
   AbstractDecisionFeature(void);

   bool operator!=(const AbstractDecisionFeature &f) const {
      return Compare(f) != 0;
   }

   bool operator<(const AbstractDecisionFeature &f) const {
      return Compare(f) < 0;
   }

   std::function<bool(const AbstractDecisionFeature &)>GetLessThanComparator(void) const {
      throw DecisionTreeException("AbstractDecisionFeature::GetLessThanComparator: not implemented");
   }

public:
   static void RegisterConstructorNotification(const std::function<void(AbstractDecisionFeature *)> &hook);

protected:
   virtual int Compare(const AbstractDecisionFeature &f) const = 0;

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

protected:
   virtual int Compare(const AbstractDecisionFeature &_f) const {
      // cast it to one of our own
      auto f = dynamic_cast<const DecisionFeature *>(&_f);

      // if it's not one of our own that probably has to be an error until I come up with a
      // reason that it's not
      if (f == nullptr)
         throw DecisionTreeException("DecisionFeature::Compare: not same type");

      // same type, it gets simple
      if (value < f->value)
         return -1;
      else if (value > f->value)
         return 1;
      else
         return 0;
   }

private:
   T  value;
};

#endif
