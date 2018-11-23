
#ifndef DECISIONFOREST_H
#define DECISIONFOREST_H

#include "OutcomeDistribution.h"

template <typename TFeatureSet, typename TOutcome>
   class DecisionForest
{
public:
   using Tree = DecisionTree<TFeatureSet, TOutcome>;

public:
   DecisionForest(void) {
   }

   void AddTree(std::unique_ptr<Tree> tree)
   {
      trees.push_back(std::move(tree));
   }

   OutcomeDistribution<TOutcome> EvaluatePoint(const TFeatureSet &pointFeatures) const {
      OutcomeDistribution<TOutcome> result;
      for (unsigned i = 0; i < trees.size(); ++i)
         result.AddOutcome(trees[i]->EvaluatePoint(pointFeatures));
      return result;
   }

private:
   std::vector<std::unique_ptr<Tree>> trees;
};

#endif
