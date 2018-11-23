// TreeTest.cpp : Defines the entry point for the console application.
//

#include <cstdlib>
#include <stdio.h>
#include "DecisionDataSet.h"
#include "DecisionFeature.h"
#include "CompactedBinaryDecisionTree.h"

struct DataPoint
{
   DataPoint(double x = 0, double y = 0) {
      X = x;
      Y = y;
   }

   DecisionFeature<double> X;
   DecisionFeature<double> Y;
};

int main()
{
   try
   {
      // create a data set
      DecisionDataSet<DataPoint, bool> dataSet;
      for (int i = 0; i < 1000; ++i) {
         DataPoint p;
         p.X = ((double)rand() / RAND_MAX) * 100;
         p.Y = ((double)rand() / RAND_MAX) * 100;
         dataSet.AddPoint(
            p,
            *p.Y > (*p.X - 50)*(*p.X - 50) / 25
         );
      }

      // create from it a decision tree
      std::unique_ptr < DecisionTree<DataPoint, bool>> tree;
      tree.reset(
         new CompactedBinaryDecisionTree<DataPoint, bool>(dataSet)
         );

      // evaluate every point in our range and make a bitmap of the result
      FILE *f = fopen("bleem.raw", "wb");
      for (int y = 99; y >= 0; --y)
      {
         for (int x = 0; x < 100; ++x)
         {
            fputc(tree->EvaluatePoint(DataPoint(x, y)) ? 255 : 0, f);
         }
      }
      fclose(f);
   }
   catch (DecisionTreeException &x)
   {
      printf("%s\r\n", x.what());
      getchar();
   }

   return 0;
}

