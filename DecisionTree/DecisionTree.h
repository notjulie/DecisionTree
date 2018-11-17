
#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "DecisionDataSet.h"
#include "DecisionTreeException.h"
#include "DecisionTreeNode.h"
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
      throw DecisionTreeException("DecisionTree::EvaluatePoint not implemented");
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
      result = BranchOnFeature(dataSet, 0);
      for (unsigned i = 1; i < featureCount; ++i)
      {
         std::unique_ptr<TreeNode> tree = BranchOnFeature(dataSet, i);
         if (tree->GetDepth() < result->GetDepth())
            result = std::move(tree);
         else if (tree->GetDepth() == result->GetDepth() && tree->GetTotalNodeCount() < result->GetTotalNodeCount())
            result = std::move(tree);
      }

      return result;
   }

   static std::unique_ptr<TreeNode> BranchOnFeature(const DataSet &dataSet, unsigned featureIndex) {
      throw DecisionTreeException("DecisionTree::BranchOnFeature: not implemented");
   }

private:
   std::unique_ptr<DecisionTreeNode<TFeatureSet, TOutcome>> rootNode;
};


#endif
