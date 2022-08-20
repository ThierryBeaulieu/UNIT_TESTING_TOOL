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


UnitTest::UnitTest(const std::string& description, int ponderation): Test(description), isTestPassing_(false)
{
   if(ponderation > 10 || ponderation < 0) abort();
   ponderation_ = ponderation;
}
UnitTest::~UnitTest(){}
void UnitTest::printResult(){
   std::cout << "Unit Test: " << Test::description_ << std::endl;
}
std::pair<bool, int> UnitTest::getResult() {
   return std::make_pair(isTestPassing_, ponderation_);
}


TestSection::TestSection(const std::string& description): Test(description){}
TestSection::~TestSection(){}
void TestSection::printResult(){
   std::cout << "Test section: " << Test::description_ << std::endl;
   for(std::shared_ptr<Test> test: tests_){
      test->printResult();
   }
}
void TestSection::addTest(std::shared_ptr<Test> test) {
   tests_.push_back(test);
}


bool TestContainer::mutex_ = false;
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
         return;
      }
   }
   tests_.push_back(test);
}
bool TestContainer::getMutex() {
   return mutex_;
}
void TestContainer::setMutex(bool mutex) {
   mutex_ = mutex;
}
