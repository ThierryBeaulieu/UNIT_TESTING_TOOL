
#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <memory>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#endif

enum Font {
   GreenBlack = 10,
   BlackGreen = 160,
   WhiteBlack = 15,
   BlackGrey = 112,
   BlackBlue = 116,
};

void setTextColor(unsigned char color) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
   HANDLE console_color;
   console_color = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(console_color, color);
#endif
}

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

void resetTextColor() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
   HANDLE console_color;
   console_color = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(console_color, Font::WhiteBlack);
#endif
}


class Test {
public:
   Test(){}
   Test(const std::string& description) {
      description_ = description;
   }
   const std::string& getDescription() {
      return description_;
   }
   void setDescription(const std::string& description) {
      description_ = description;
   }
   std::vector<std::shared_ptr<Test>> getSubTests() {
      return subTests_;
   }
   virtual void addTest(std::shared_ptr<Test> subTest) {
      subTests_.push_back(subTest);
   }
   virtual void print() {
      std::cout << description_ << std::endl;
      for (auto test : getSubTests()) {
         test->print();
      }
   }
   virtual const std::vector<std::pair<bool, int>>& getResult() {
      std::vector<std::pair<bool, int>> result;
      result.push_back(std::make_pair(false, 1));
      return result;
   }
private:
   std::string description_;
protected:
   std::vector<std::shared_ptr<Test>> subTests_;
};

class UnitTest : public Test {
public:
   UnitTest(std::string description, int ponderation) : Test(description), ponderation_(ponderation), isAnswerCorrect_(false) {}
   const int getPonderation() {
      return ponderation_;
   }
   void setPonderation(int ponderation) {
      ponderation_ = ponderation;
   }
   bool isAnswerCorrect() {
      return isAnswerCorrect_;
   }
   void setAnswer(bool result) {
      isAnswerCorrect_ = result;
   }
   virtual const std::vector<std::pair<bool, int>>& getResult() {
      std::vector<std::pair<bool, int>> result;
      result.push_back(std::make_pair(isAnswerCorrect_, ponderation_));
      return result;
   }
   virtual void print() {
      if (isAnswerCorrect_) {
         std::cout << "[X] Test passed" << std::endl;
      }
      else {
         std::cout << "[ ] Test failed" << std::endl;
      }
   }
   void addSubTest() {}
private:
   bool isAnswerCorrect_;
   int ponderation_;
};

class TestSuite : public Test {
public:
   TestSuite(const std::string& description): Test() {}
   void addSubTest(std::shared_ptr<UnitTest> unitTest) {
      Test::addTest(unitTest);
   }
};

// Doit être un singleton
class TestContainer : public Test {
public:
   TestContainer() : Test() {}
   void present() {
      setTextColor(Font::BlackGreen);
      std::cout << "=================================" << std::endl;
      std::cout << "Starting tests:                  " << std::endl;
      std::cout << "=================================" << std::endl;
      resetTextColor();
   }
   void addSubTest(std::shared_ptr<TestSuite> testSuite) {
      Test::addTest(testSuite);
   }
   void addSubTest(std::shared_ptr<UnitTest> unitTest) {
      Test::subTests_.back()->addTest(unitTest);
   }
};


#define BeginTesting { \
   TestContainer container = TestContainer(); \
   container.present();

#define EndTesting \
   container.print();\
}


#define BeginTestSuite(testName) {\
   std::shared_ptr<TestSuite> testSuite = std::make_shared<TestSuite>(testName);\
   container.addSubTest(testSuite);

#define EndTestSuite }


// TODO: Add a queue so that all tests are going to 
// be verified before using a color?
#define BeginTest(testName, ponderation) {\
   std::shared_ptr<UnitTest> unitTest = std::make_shared<UnitTest>(testName, ponderation);


#define EndTest }

#define ExpectEqual(element1, element2)

int main() {
BeginTesting
   BeginTestSuite("Verification of the tests")
      BeginTest("Asserting", 20)
         int x = 6;
         ExpectEqual(x, 5)
      EndTest
   EndTestSuite

   BeginTestSuite("Second test")
      BeginTest("Asserting again", 20)
         int x = 6;
         ExpectEqual(x, 5)
      EndTest
   EndTestSuite
EndTesting
   return 0;
}