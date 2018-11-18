
#ifndef DECISIONFEATURE_H
#define DECISIONFEATURE_H

#include <functional>
#include "DecisionTreeException.h"

class AbstractDecisionFeature {
public:
   using MidCompare = std::function<bool(const AbstractDecisionFeature &low, const AbstractDecisionFeature &high, const AbstractDecisionFeature &value)>;

public:
   AbstractDecisionFeature(void);

   bool operator!=(const AbstractDecisionFeature &f) const;
   bool operator<(const AbstractDecisionFeature &f) const;

   virtual MidCompare GetLessThanMidpointComparator(void) const = 0;

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

   virtual MidCompare GetLessThanMidpointComparator(void) const {
      return [](const AbstractDecisionFeature &_low, const AbstractDecisionFeature &_high, const AbstractDecisionFeature &_compareValue) {
         // all values must be of our same type
         auto low = dynamic_cast<const DecisionFeature *>(&_low);
         auto high = dynamic_cast<const DecisionFeature *>(&_high);
         auto compareValue = dynamic_cast<const DecisionFeature *>(&_compareValue);
         if (low == nullptr || high == nullptr || compareValue == nullptr)
            throw DecisionTreeException("DecisionFeature::GetLessThanMidpointComparator: invalid parameter");

         // this will fail for features that don't support arithmetic... deal with that later
         return (2 * compareValue->value) < (low->value + high->value);
      };
   }

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
