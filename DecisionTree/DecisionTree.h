
#ifndef DECISIONTREE_H
#define DECISIONTREE_H

template <typename TFeatureSet, typename TOutcome>
   class DecisionTree
{
public:
   using Node = DecisionTreeNode<TFeatureSet, TOutcome>;

public:
   DecisionTree(std::unique_ptr<Node> rootNode) {
      this->rootNode = std::move(rootNode);
   }

   TOutcome EvaluatePoint(const TFeatureSet &pointFeatures) const {
      return rootNode->EvaluatePoint(pointFeatures);
   }

   unsigned GetDepth(void) const {
      return rootNode->GetDepth();
   }

private:
   std::unique_ptr<Node> rootNode;
};


#endif
