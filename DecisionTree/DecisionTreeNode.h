
#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H

#include <memory>

template <typename TFeatureSet, typename TOutcome>
   class DecisionTreeNode
{
public:
   virtual ~DecisionTreeNode(void) {}

   virtual unsigned GetDepth(void) const {
      throw DecisionTreeException("DecisionTreeNode::GetDepth: not implemented");
   }

   virtual unsigned GetTotalNodeCount(void) const {
      throw DecisionTreeException("DecisionTreeNode::GetTotalNodeCount: not implemented");
   }
};

#endif
