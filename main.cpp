
#include "UnitTestTool.h"

int main() {
BeginTesting

BeginTestSection("First test suite")

   BeginTest("Equality", 10)
         int x = 6;
         ExpectEqual(x, 6)
   EndTest

   BeginTest("Second equality", 0)
      int house = 2;
      int building = 4;
      ExpectNEq(house, building);
   EndTest

   BeginTestSection("Second test section inside first one")
      BeginTest("Second equality", 4)
         int house = 2;
         int building = 4;
         ExpectNEq(house, building);
      EndTest
   EndTestSection

EndTestSection

PrintTestResults

EndTesting
   return 0;
}
