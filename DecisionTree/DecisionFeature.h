// =========================================================================
//    DecisionFeature.h
//    Author: Randy Rasmussen
//    Copyright: none, use at your own risk and to your heart's content
//
//		Contains the definition of class DecisionFeature.
// =========================================================================

#ifndef DECISIONFEATURE_H
#define DECISIONFEATURE_H

#include <functional>
#include "DecisionTreeException.h"

class AbstractDecisionFeature {
public:
   AbstractDecisionFeature(void);

   bool operator!=(const AbstractDecisionFeature &f) const;
   bool operator<(const AbstractDecisionFeature &f) const;

   virtual bool IsLessThanMidpoint(const AbstractDecisionFeature &a, const AbstractDecisionFeature &b) const = 0;

protected:
   virtual int Compare(const AbstractDecisionFeature &f) const = 0;

private:
   // delare our static member that allows FeatureSetInfo types to hook our constructor so
   // that it can sniff a structure for instances of this class
   friend class AbstractFeatureSetInfo;
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

   virtual bool IsLessThanMidpoint(const AbstractDecisionFeature &_a, const AbstractDecisionFeature &_b) const {
      // this only makes sense if everyone is of the same type
      auto a = dynamic_cast<const DecisionFeature *>(&_a);
      auto b = dynamic_cast<const DecisionFeature *>(&_b);
      if (a == nullptr || b == nullptr)
         throw DecisionTreeException("DecisionFeature::IsLessThanMidpoint: invalid parameters");

      // this will only work for types that handle arithmetic... will deal with other types later
      return 2 * value < (a->value + b->value);
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
