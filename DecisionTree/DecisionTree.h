
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
   using DataSet = DecisionDataSet<TFeatureSet, TOutcome>;
   using TreeNode = DecisionTreeNode<TFeatureSet, TOutcome>;

public:
   DecisionTree(const DataSet &dataSet) {
      rootNode = CreateTree(dataSet);
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
         throw DecisionTreeException("DecisionTreeNode::CreateTree: empty data set");

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

      // else we branch on whichever feature gives us the smallest tree
      for (unsigned i = 0; i < featureCount; ++i)
      {
         std::unique_ptr<TreeNode> tree = BranchOnFeature(dataSet, i);
         if (result.get() == nullptr)
         {
            result = std::move(tree);
         }
         else if (tree.get() != nullptr)
         {
            if (tree->GetDepth() < result->GetDepth())
               result = std::move(tree);
            else if (tree->GetDepth() == result->GetDepth() && tree->GetTotalNodeCount() < result->GetTotalNodeCount())
               result = std::move(tree);
         }
      }

      if (result.get() == nullptr)
         throw DecisionTreeException("DecisionTree::CreateTree: ambiguous data set");

      return result;
   }

   static std::unique_ptr<TreeNode> BranchOnFeature(const DataSet &_dataSet, unsigned featureIndex) {
      // make a copy of the data set sorted on our feature
      DataSet dataSet = _dataSet;
      dataSet.SortByFeature(featureIndex);

      // for now, just split on the middle, as long as we can find two consecutive feature
      // values that are different
      int middle = (int)dataSet.GetCount() / 2;
      int below, above;
      int distanceFromMiddle = 0;
      for (;;)
      {
         bool triedSomething = false;
         
         below = middle + distanceFromMiddle;
         above = middle + distanceFromMiddle + 1;
         if (above < dataSet.GetCount())
         {
            if (*dataSet.GetFeature(featureIndex, below) != *dataSet.GetFeature(featureIndex, above))
               break;
            triedSomething = true;
         }

         below = middle - distanceFromMiddle - 1;
         above = middle - distanceFromMiddle;
         if (below >= 0)
         {
            if (*dataSet.GetFeature(featureIndex, below) != *dataSet.GetFeature(featureIndex, above))
               break;
            triedSomething = true;
         }

         // if we were out of bounds for both our tests above, that means all feature values are the same,
         // so we can't make a decision... just return nullptr
         if (!triedSomething)
            return std::unique_ptr<TreeNode>();

         ++distanceFromMiddle;
      }

      // we have found two consecutive samples whose feature values are different;
      // their indices are "below" and "above"; use them to create a decision node
      std::unique_ptr<TreeNode> belowTree = CreateTree(dataSet.GetSubset(0, below + 1));
      std::unique_ptr<TreeNode> aboveTree = CreateTree(dataSet.GetSubset(above, (unsigned)(dataSet.GetCount() - above)));

      std::unique_ptr<TreeNode> result;
      result.reset(new DecisionNode<TFeatureSet,TOutcome>(
         belowTree,
         dataSet.GetFeatureSet(below),
         aboveTree,
         dataSet.GetFeatureSet(above),
         featureIndex
         ));
      return result;
   }

private:
   std::unique_ptr<DecisionTreeNode<TFeatureSet, TOutcome>> rootNode;
};


#endif
