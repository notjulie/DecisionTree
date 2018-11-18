
#ifndef FEATURESETINFO_H
#define FEATURESETINFO_H

#include "DecisionFeature.h"

template <typename T> class FeatureSetInfo {
public:
   FeatureSetInfo(void) {
      std::vector<AbstractDecisionFeature *> features;

      // register our function to be called whenever a new feature is constructed
      AbstractDecisionFeature::RegisterConstructorNotification(
         [&](AbstractDecisionFeature *feature) {
            features.push_back(feature);
         }
      );

      try {
         // instantiate a feature set... our callback will record pointers to all the features that
         // get created
         std::unique_ptr<T> featureSet;
         featureSet.reset(new T);

         // make a permanent record of the offsets within the feature set to each feature
         for (int i = 0; i < features.size(); ++i)
         {
            int offset = (int)((char *)features[i] - (char *)featureSet.get());
            if (offset >= 0 && offset < sizeof(T))
               featureOffsets.push_back(offset);
         }

         // clear the callback
         AbstractDecisionFeature::RegisterConstructorNotification([](AbstractDecisionFeature *feature) {});
      }
      catch (...) {
         // clear the callback and rethrow
         AbstractDecisionFeature::RegisterConstructorNotification([](AbstractDecisionFeature *feature) {});
         throw;
      }
   }

   size_t GetFeatureCount(void) const { return featureOffsets.size(); }

   bool IsFeatureLessThan(unsigned featureIndex, const T &a, const T &b) {
      int offset = featureOffsets[featureIndex];
      auto featureA = (const AbstractDecisionFeature *)(((char *)&a) + offset);
      auto featureB = (const AbstractDecisionFeature *)(((char *)&b) + offset);
      return *featureA < *featureB;
   }

private:
   std::vector<int> featureOffsets;
};

#endif
