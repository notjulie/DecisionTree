
#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H

#include <memory>

template <typename TFeatureSet, typename TOutcome>
   class DecisionTreeNode
{
public:
   virtual ~DecisionTreeNode(void) {}

   virtual unsigned GetDepth(void) const = 0;
   virtual unsigned GetTotalLeafCount(void) const = 0;
   virtual TOutcome EvaluatePoint(const TFeatureSet &pointFeatures) = 0;
};

#endif
