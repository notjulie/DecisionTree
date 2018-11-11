
#ifndef DECISIONDATASET_H
#define DECISIONDATASET_H

#include <vector>

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

private:
   struct Pair {
      TFeatureSet featureSet;
      TOutcome outcome;
   };

private:
   std::vector<Pair> points;
};

#endif
