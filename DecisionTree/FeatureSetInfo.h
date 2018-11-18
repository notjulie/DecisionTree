
#ifndef FEATURESETINFO_H
#define FEATURESETINFO_H

#include "DecisionFeature.h"

template <typename T> class FeatureSetInfo {
public:
   size_t GetFeatureCount(void) const { return featureOffsets.size(); }

   const AbstractDecisionFeature *GetFeatureValue(const T &featureSet, int featureIndex) const {
      int offset = featureOffsets[featureIndex];
      return (const AbstractDecisionFeature *)(((char *)&featureSet) + offset);
   }

   bool IsFeatureLessThan(unsigned featureIndex, const T &a, const T &b) const {
      return *GetFeatureValue(a, featureIndex) < *GetFeatureValue(b, featureIndex);
   }

private:
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

public:
   static const FeatureSetInfo &GetInstance(void) {
      if (instance == nullptr)
         instance = new FeatureSetInfo();
      return *instance;
   }

private:
   std::vector<int> featureOffsets;

private:
   static thread_local FeatureSetInfo *instance;
};

template <class T>  thread_local FeatureSetInfo<T> *FeatureSetInfo<T>::instance = nullptr;

#endif
