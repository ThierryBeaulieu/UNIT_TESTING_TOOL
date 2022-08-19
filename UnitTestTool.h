#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <memory>
#include <iterator>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#endif

enum Font {
   GreenBlack = 10,
   BlackGreen = 160,
   WhiteBlack = 15,
   BlackGrey = 112,
   BlackBlue = 116,
   BlackRed = 64,
   RedBlack = 4,
};

namespace Design {
   void setTextColor(unsigned char color);
   void printAllColorCombinations();
   void resetTextColor();
}

class Test {
public:
   Test(const std::string& description);
   virtual void printResult() = 0;
private:
   std::string description_;
};

// leaf
class UnitTest : public Test {
public:
   UnitTest(const std::string& description, int ponderation);
   ~UnitTest();
   void printResult();
   std::pair<bool, int> getResult();
private:
   int ponderation_;
   bool isTestPassing_;
};

// container
class TestSection : public Test {
public:
   TestSection(const std::string& description);
   ~TestSection();
   void printResult();
   void addTest(std::shared_ptr<Test> test);
private:
   std::vector<std::shared_ptr<Test>> tests_;
};

// Needs to be a singleton
class TestContainer {
public:
   static TestContainer* getInstance();
   static bool getTestingState();
   static void setTestingState(bool testingState);
   TestContainer(TestContainer& testContainerCopy) = delete;
   void operator=(const TestContainer&) = delete;
   void printResult();
   void addTestSection(std::shared_ptr<Test> testSection);
   void addTest(std::shared_ptr<Test> test);
private:
   TestContainer() = default;
   static bool testingState_;
   static TestContainer* instance_;
   std::vector<std::shared_ptr<Test>> tests_;
};

#define BeginTesting {\
   if (!TestContainer::getTestingState()){ \
      TestContainer::setTestingState(true); \
   } \
   else { \
      abort(); \
   }

#define EndTesting \
   TestContainer::getInstance()->printResult(); \
}


#define BeginTestSection(testName) { \
   TestContainer::getInstance()->addTestSection(std::make_shared<TestSection>(testName));

#define EndTestSection }


#define BeginTest(testName, ponderation) {

#define EndTest }


#define ExpectEqual(element1, element2) { }

#define ExpectNEq(element1, element2) { }
