
#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "DecisionDataSet.h"
#include "DecisionNode.h"
#include "DecisionTreeException.h"
#include "LeafNode.h"

template <typename TFeatureSet, typename TOutcome>
   class DecisionTree
{
public:
   virtual TOutcome EvaluatePoint(const TFeatureSet &pointFeatures) = 0;
};


#endif
