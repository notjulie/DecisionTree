
#ifndef DECISIONDATASET_H
#define DECISIONDATASET_H

#include <vector>
#include "DecisionTreeException.h"
#include "FeatureSetInfo.h"

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

   size_t GetFeatureCount(void) const {
      return featureInfo.GetFeatureCount();
   }

   DecisionDataSet GetSubset(unsigned startIndex, unsigned length) {
      throw DecisionTreeException("DecisionDataSet::GetSubset: not implemented");
   }

   void SortByFeature(unsigned featureIndex) {
      throw DecisionTreeException("DecisionDataSet::SortByFeature: not implemented");
   }

   const AbstractDecisionFeature *GetFeature(unsigned featureIndex, unsigned pointIndex) {
      throw DecisionTreeException("DecisionDataSet::GetFeature: not implemented");
   }

private:
   struct Pair {
      TFeatureSet featureSet;
      TOutcome outcome;
   };

private:
   FeatureSetInfo<TFeatureSet> featureInfo;
   std::vector<Pair> points;
};

#endif
