
#ifndef LEAFNODE_H
#define LEAFNODE_H

template <typename TFeatureSet, typename TOutcome>
   class LeafNode : public DecisionTreeNode<TFeatureSet, TOutcome>
{
public:
   LeafNode(TOutcome outcome) {
   }
};


#endif
