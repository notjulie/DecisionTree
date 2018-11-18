
#ifndef DECISIONNODE_H
#define DECISIONNODE_H

#include <functional>
#include "DecisionTreeNode.h"

template <typename TFeatureSet, typename TOutcome>
   class DecisionNode : public DecisionTreeNode<TFeatureSet, TOutcome>
{
public:
   using Node = DecisionTreeNode<TFeatureSet, TOutcome>;

public:
   DecisionNode(const std::unique_ptr<Node> &belowNode, const std::unique_ptr<Node> &aboveNode, const std::function<bool(const AbstractDecisionFeature &feature)> &comparator) {
   }
};


#endif
