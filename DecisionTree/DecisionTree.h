
#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "DecisionDataSet.h"
#include "DecisionTreeException.h"

template <typename TFeatureSet, typename TOutcome>
   class DecisionTree
{
public:
   DecisionTree(const DecisionDataSet<TFeatureSet, TOutcome> &dataSet) {
      throw DecisionTreeException("DecisionTree::DecisionTree not implemented");
   }

   TOutcome EvaluatePoint(const TFeatureSet &pointFeatures) {
      throw DecisionTreeException("DecisionTree::EvaluatePoint not implemented");
   }
};


#endif
