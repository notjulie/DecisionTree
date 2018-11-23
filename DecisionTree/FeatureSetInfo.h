// =========================================================================
//    FeatureSetInfo.h
//    Author: Randy Rasmussen
//    Copyright: none, use at your own risk and to your heart's content
//
//		Contains the implementation of FeatureSetInfo template class
//    
// =========================================================================

#ifndef FEATURESETINFO_H
#define FEATURESETINFO_H

#include "DecisionFeature.h"

/// <summary>
/// Abstract base class for FeatureSetInfo
/// </summary>
class AbstractFeatureSetInfo {
protected:
   void SetFeatureHook(const std::function<void(AbstractDecisionFeature *)> &hook) {
      // this is a private member of AbstractDecisionFeature, but we are a friend class for
      // the sole purpose of allowing us to do this
      AbstractDecisionFeature::constructorCallback = hook;
   }
};

/// <summary>
/// FeatureSetInfo template class... this sniffs a structure containing members that
/// inherit AbstractDecisionFeature and accumulates information about their location
/// with the structure so that they may be accessed dynamically.
/// </summary>
template <typename T> class FeatureSetInfo : private AbstractFeatureSetInfo {
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
      SetFeatureHook(
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
         SetFeatureHook([](AbstractDecisionFeature *feature) {});
      }
      catch (...) {
         // clear the callback and rethrow
         SetFeatureHook([](AbstractDecisionFeature *feature) {});
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


/// <summary>
/// Our global instance for each templated type
/// </summary>
template <class T>  thread_local FeatureSetInfo<T> *FeatureSetInfo<T>::instance = nullptr;

#endif
