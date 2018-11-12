
#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H

#include <memory>

template <typename TFeatureSet, typename TOutcome>
   class DecisionTreeNode
{
public:
   static std::unique_ptr<DecisionTreeNode> CreateTree(const DecisionDataSet<TFeatureSet, TOutcome> &dataSet) {
      throw DecisionTreeException("DecisionTreeNode::CreateTree: not implemented");
   }
};

#endif
