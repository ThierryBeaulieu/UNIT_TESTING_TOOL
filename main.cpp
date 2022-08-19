
#include "UnitTestTool.h"

int main() {
BeginTesting

BeginTestSuite("First test suite")
   BeginTest("Simple assertion", 20)
      int x = 6;
      ExpectEqual(x, 6)
   EndTest
   BeginTest("Verify pointers", 10)
      ExpectNEq(house, building);
   EndTest
EndTestSuite

EndTesting
   return 0;
}
