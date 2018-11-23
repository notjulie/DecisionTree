
#ifndef OUTCOMEDISTRIBUTION_H
#define OUTCOMEDISTRIBUTION_H

#include <map>

template <typename T> class OutcomeDistribution {
public:
   void AddOutcome(const T &outcome) {
      auto it = outcomes.find(outcome);
      if (it == outcomes.end())
         outcomes[outcome] = 1;
      else
         ++(*it).second;
   }

   T GetMostCommon(void) const {
      int highestFrequency = 0;
      T mostCommon;

      for (auto it = outcomes.begin(); it != outcomes.end(); ++it)
      {
         if ((*it).second > highestFrequency)
         {
            highestFrequency = (*it).second;
            mostCommon = (*it).first;
         }
      }

      return mostCommon;
   }

private:
   std::map<T, int> outcomes;
};

#endif
