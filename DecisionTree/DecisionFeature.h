
#ifndef DECISIONFEATURE_H
#define DECISIONFEATURE_H

template <typename T>
   class DecisionFeature
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
