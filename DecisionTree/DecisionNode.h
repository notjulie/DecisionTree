
#ifndef DECISIONNODE_H
#define DECISIONNODE_H

#include <functional>
#include "DecisionTreeNode.h"

template <typename TFeatureSet, typename TOutcome>
   class DecisionNode : public DecisionTreeNode<TFeatureSet, TOutcome>
{
public:
   using Node = DecisionTreeNode<TFeatureSet, TOutcome>;
   using FeatureInfo = FeatureSetInfo<TFeatureSet>;

public:
   DecisionNode(
      std::unique_ptr<Node> &belowNode,
      TFeatureSet belowFeatures,
      std::unique_ptr<Node> &aboveNode,
      TFeatureSet aboveFeatures,
      int featureIndex
      )
   {
      this->belowNode = std::move(belowNode);
      this->belowFeatures = belowFeatures;
      this->aboveNode = std::move(aboveNode);
      this->aboveFeatures = aboveFeatures;
      this->featureIndex = featureIndex;
   }

   virtual unsigned GetDepth(void) const { return 1 + belowNode->GetDepth() + aboveNode->GetDepth(); }
   virtual unsigned GetTotalNodeCount(void) const { return 1 + belowNode->GetTotalNodeCount() + aboveNode->GetTotalNodeCount(); }
   virtual TOutcome EvaluatePoint(const TFeatureSet &pointFeatures) {
      auto featureInfo = FeatureInfo::GetInstance();
      auto featureValue = featureInfo.GetFeatureValue(pointFeatures, featureIndex);
      auto below = featureInfo.GetFeatureValue(belowFeatures, featureIndex);
      auto above = featureInfo.GetFeatureValue(aboveFeatures, featureIndex);
      return featureValue->IsLessThanMidpoint(*below, *above) ?
         belowNode->EvaluatePoint(pointFeatures) :
         aboveNode->EvaluatePoint(pointFeatures);
   }

private:
   std::unique_ptr<Node> belowNode;
   TFeatureSet belowFeatures;
   std::unique_ptr<Node> aboveNode;
   TFeatureSet aboveFeatures;
   int featureIndex;
};


#endif
