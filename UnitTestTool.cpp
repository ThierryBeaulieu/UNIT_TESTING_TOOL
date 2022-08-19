#include "UnitTestTool.h"

namespace Design {
   void setTextColor(unsigned char color) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
      HANDLE console_color;
      console_color = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(console_color, color);
#endif
   }

   void resetTextColor() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
      HANDLE console_color;
      console_color = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(console_color, Font::WhiteBlack);
#endif
   }

#if _DEBUG
   void printAllColorCombinations() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
      HANDLE console_color;
      console_color = GetStdHandle(STD_OUTPUT_HANDLE);
      for (int k = 1; k < 255; k++)
      {
         SetConsoleTextAttribute(console_color, k);
         std::cout << k << " This is a really nice color!" << std::endl;
      }
#endif
   }
#endif
}


Test::Test(const std::string& description): description_(description) {}


UnitTest::UnitTest(const std::string& description, int ponderation): Test(description)
{
   if(ponderation > 10 || ponderation < 0) abort();
   ponderation_ = ponderation;
}
UnitTest::~UnitTest(){}
void UnitTest::printResult(){}
std::pair<bool, int> UnitTest::getResult() {
   return std::make_pair(isTestPassing_, ponderation_);
}


TestSection::TestSection(const std::string& description): Test(description){}
TestSection::~TestSection(){}
void TestSection::printResult(){
   for(std::shared_ptr<Test> test: tests_){
      test->printResult();
   }
}
void TestSection::addTest(std::shared_ptr<Test> test) {
   tests_.push_back(test);
}


bool TestContainer::testingState_ = false;
TestContainer* TestContainer::instance_ = nullptr;
TestContainer* TestContainer::getInstance() {
   if (TestContainer::instance_ == nullptr) {
      TestContainer::instance_ = new TestContainer();
   }
   return TestContainer::instance_;
}
void TestContainer::printResult() {
   for (std::shared_ptr<Test> test : tests_) {
      test->printResult();
   }
}
void TestContainer::addTestSection(std::shared_ptr<Test> testSection) {
   tests_.push_back(testSection);
}
void TestContainer::addTest(std::shared_ptr<Test> test) {

   for (std::vector<std::shared_ptr<Test>>::iterator it = tests_.begin(); it < tests_.end(); it++) {
      if (TestSection* testSection = dynamic_cast<TestSection*>(it->get())) {
         testSection->addTest(test);
         break;
      }
   }
   tests_.push_back(test);
}
bool TestContainer::getTestingState() {
   return testingState_;
}
void TestContainer::setTestingState(bool testingState) {
   testingState_ = testingState;
}
