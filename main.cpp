
#include "UnitTestTool.h"

int main() {
BeginTesting

BeginTestSection("First test suite")

   BeginTest('Equality', 2)
         int x = 6;
         ExpectEqual(x, 6)
   EndTest

   BeginTest('Second equality', 5)
      int house = 2;
      int building = 4;
      ExpectNEq(house, building);
   EndTest

   BeginTestSection("Second test section inside first one")
      BeginTest('Second equality', 5)
         int house = 2;
         int building = 4;
         ExpectNEq(house, building);
      EndTest
   EndTestSection

EndTestSection

EndTesting
   return 0;
}
