// =========================================================================
//    DecisionDataSet.h
//    Author: Randy Rasmussen
//    Copyright: none, use at your own risk and to your heart's content
//
//		Contains the implementation of DecisionDataSet template class
//    
// =========================================================================


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
   using FeatureInfo = FeatureSetInfo<TFeatureSet>;
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
      return FeatureInfo::GetInstance().GetFeatureCount();
   }

   DecisionDataSet GetSubset(unsigned startIndex, unsigned length) {
      DecisionDataSet result;
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
            return FeatureInfo::GetInstance().IsFeatureLessThan(featureIndex, a.featureSet, b.featureSet);
         }
      );
   }

   const AbstractDecisionFeature *GetFeature(unsigned featureIndex, unsigned pointIndex) {
      return FeatureInfo::GetInstance().GetFeatureValue(points[pointIndex].featureSet, featureIndex);
   }

   TFeatureSet GetFeatureSet(unsigned index) const {
      return points[index].featureSet;
   }

private:
   std::vector<Point> points;
};

#endif
