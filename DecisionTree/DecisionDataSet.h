
#ifndef DECISIONDATASET_H
#define DECISIONDATASET_H

#include <algorithm>
#include <vector>
#include "DecisionTreeException.h"
#include "FeatureSetInfo.h"


template <typename TFeatureSet, typename TOutcome>
   struct DecisionPoint
{
   TFeatureSet featureSet;
   TOutcome outcome;
};

template <typename TFeatureSet, typename TOutcome>
   class DecisionDataSet
{
public:
   using Point = DecisionPoint<TFeatureSet, TOutcome>;

public:
   void AddPoint(const TFeatureSet &pointFeatures, const TOutcome &pointOutcome) {
      Point pair;
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
      DecisionDataSet result;
      result.featureInfo = this->featureInfo;
      result.points.insert(
         result.points.begin(),
         this->points.begin() + startIndex,
         this->points.begin() + startIndex + length
         );
      return result;
   }

   void SortByFeature(unsigned featureIndex) {
      std::sort(
         points.begin(),
         points.end(),
         [this, featureIndex](const Point &a, const Point &b) {
            return featureInfo.IsFeatureLessThan(featureIndex, a.featureSet, b.featureSet);
         }
      );
   }

   const AbstractDecisionFeature *GetFeature(unsigned featureIndex, unsigned pointIndex) {
      return featureInfo.GetFeatureValue(points[pointIndex].featureSet, featureIndex);
   }

private:
   FeatureSetInfo<TFeatureSet> featureInfo;
   std::vector<Point> points;
};

#endif
