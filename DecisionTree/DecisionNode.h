
#ifndef DECISIONNODE_H
#define DECISIONNODE_H

#include <functional>
#include "DecisionTreeNode.h"

template <typename TFeatureSet, typename TOutcome>
   class DecisionNode : public DecisionTreeNode<TFeatureSet, TOutcome>
{
public:
   using Node = DecisionTreeNode<TFeatureSet, TOutcome>;
   using Compare = std::function<bool(const AbstractDecisionFeature &low, const AbstractDecisionFeature &high, const AbstractDecisionFeature &compareValue)>;

public:
   DecisionNode(std::unique_ptr<Node> &belowNode, std::unique_ptr<Node> &aboveNode, const Compare &comparator) {
      this->belowNode = std::move(belowNode);
      this->aboveNode = std::move(aboveNode);
      this->comparator = comparator;
   }

   virtual unsigned GetDepth(void) const { return 1 + belowNode->GetDepth() + aboveNode->GetDepth(); }
   virtual unsigned GetTotalNodeCount(void) const { return 1 + belowNode->GetTotalNodeCount() + aboveNode->GetTotalNodeCount(); }
   virtual TOutcome EvaluatePoint(const TFeatureSet &pointFeatures) {
      throw DecisionTreeException("DecisionNode::EvaluatePoint: not implemented");
   }

private:
   std::unique_ptr<Node> belowNode;
   std::unique_ptr<Node> aboveNode;
   Compare comparator;
};


#endif
