
#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "DecisionDataSet.h"
#include "DecisionTreeException.h"
#include "DecisionTreeNode.h"

template <typename TFeatureSet, typename TOutcome>
   class DecisionTree
{
public:
   DecisionTree(const DecisionDataSet<TFeatureSet, TOutcome> &dataSet) {
      rootNode = DecisionTreeNode<TFeatureSet,TOutcome>::CreateTree(dataSet);
   }

   TOutcome EvaluatePoint(const TFeatureSet &pointFeatures) {
      throw DecisionTreeException("DecisionTree::EvaluatePoint not implemented");
   }

private:
   std::unique_ptr<DecisionTreeNode<TFeatureSet, TOutcome>> rootNode;
};


#endif
