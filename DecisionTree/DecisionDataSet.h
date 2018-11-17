
#ifndef DECISIONDATASET_H
#define DECISIONDATASET_H

#include <vector>
#include "DecisionTreeException.h"

template <typename TFeatureSet, typename TOutcome>
   class DecisionDataSet
{
public:
   void AddPoint(const TFeatureSet &pointFeatures, const TOutcome &pointOutcome) {
      Pair pair;
      pair.featureSet = pointFeatures;
      pair.outcome = pointOutcome;
      points.push_back(pair);
   }

   size_t GetCount(void) const {
      return points.size();
   }

   TOutcome GetOutcome(unsigned index) const {
      return points[index].outcome;
   }

   unsigned GetFeatureCount(void) const {
      throw DecisionTreeException("DecisionDataSet::GetFeatureCount not implemented");
   }

private:
   struct Pair {
      TFeatureSet featureSet;
      TOutcome outcome;
   };

private:
   std::vector<Pair> points;
};

#endif
