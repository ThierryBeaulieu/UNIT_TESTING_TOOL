
#include "UnitTestTool.h"

int main() {
BeginTesting
BeginTestSuite("First test suite")
   BeginTest("Simple assertion", 20)
      int x = 6;
      ExpectEqual(x, 6)
   EndTest
   BeginTest("Verify pointers", 10)
      class House {
      public:
         House(int color): color_(color){}
         int color_;
      private:
      };
      House * house = new House(4);
      House * building = new House(4);
      ExpectNEq(house, building);
   EndTest
EndTestSuite

BeginTestSuite("Second test suite")
   BeginTest("Bad assertion", 20)
      int x = 6;
      ExpectEqual(x, 5)
   EndTest
EndTestSuite
EndTesting
   return 0;
}
