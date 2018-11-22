
#ifndef LEAFNODE_H
#define LEAFNODE_H

template <typename TFeatureSet, typename TOutcome>
   class LeafNode : public DecisionTreeNode<TFeatureSet, TOutcome>
{
public:
   LeafNode(TOutcome outcome) {
      this->outcome = outcome;
   }

   virtual unsigned GetDepth(void) const { return 1; }
   virtual unsigned GetTotalLeafCount(void) const { return 1; }
   virtual TOutcome EvaluatePoint(const TFeatureSet &pointFeatures) { return outcome; }

private:
   TOutcome outcome;
};


#endif
