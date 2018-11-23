
#ifndef RANDOMBRANCHINGDECISIONTREE_H
#define RANDOMBRANCHINGDECISIONTREE_H

#include "DecisionDataSet.h"
#include "DecisionNode.h"
#include "DecisionTree.h"
#include "DecisionTreeException.h"
#include "LeafNode.h"

template <typename TFeatureSet, typename TOutcome>
   class RandomBranchingDecisionTree : public DecisionTree<TFeatureSet, TOutcome>
{
public:
   using DataSet = DecisionDataSet<TFeatureSet, TOutcome>;
   using TreeNode = DecisionTreeNode<TFeatureSet, TOutcome>;

public:
   RandomBranchingDecisionTree(const DataSet &dataSet) 
      :
         DecisionTree<TFeatureSet, TOutcome>(CreateTree(dataSet))
   {
   }

   TOutcome EvaluatePoint(const TFeatureSet &pointFeatures) {
      return rootNode->EvaluatePoint(pointFeatures);
   }

private:
   static std::unique_ptr<TreeNode> CreateTree(const DataSet &dataSet) {
      std::unique_ptr<TreeNode> result;

      // if the dataset is empty we have a problem... we can't make a decision with sample data
      auto pointCount = dataSet.GetCount();
      if (pointCount == 0)
         throw DecisionTreeException("RandomBranchingDecisionTree::CreateTree: empty data set");

      // if all the outcomes are the same we can just return a leaf node
      auto outcome0 = dataSet.GetOutcome(0);
      bool isLeafNode = true;
      for (unsigned i = 1; i < pointCount; ++i)
      {
         if (dataSet.GetOutcome(i) != outcome0)
         {
            isLeafNode = false;
            break;
         }
      }
      if (isLeafNode)
      {
         result.reset(new LeafNode<TFeatureSet, TOutcome>(outcome0));
         return result;
      }

      // sanity check our feature set
      auto featureCount = dataSet.GetFeatureCount();
      if (featureCount <= 0)
         throw DecisionTreeException("DecisionTreeNode::CreateTree: invalid feature set");

      // choose a feature at random and use it to create a branch
      return BranchOnFeature(dataSet, rand() % featureCount);
   }

   static std::unique_ptr<TreeNode> BranchOnFeature(const DataSet &_dataSet, unsigned featureIndex) {
      // make a copy of the data set sorted on our feature
      DataSet dataSet = _dataSet;
      dataSet.SortByFeature(featureIndex);

      // pick a random spot in the data set for branching it
      int belowCount = 1 + (rand() % (dataSet.GetCount() - 1));
      std::unique_ptr<TreeNode> belowTree = CreateTree(dataSet.GetSubset(0, belowCount));
      std::unique_ptr<TreeNode> aboveTree = CreateTree(dataSet.GetSubset(belowCount, dataSet.GetCount() - belowCount));

      // branch
      std::unique_ptr<TreeNode> result;
      result.reset(new DecisionNode<TFeatureSet, TOutcome>(
         belowTree,
         dataSet.GetFeatureSet(belowCount-1),
         aboveTree,
         dataSet.GetFeatureSet(belowCount),
         featureIndex
         ));
      return result;
   }
};

#endif
