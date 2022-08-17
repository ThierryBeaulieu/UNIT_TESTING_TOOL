
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
   BlackRed = 64,
   RedBlack = 4,
};

namespace Design {
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
}

class Test {
public:
   Test() {}
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
   virtual bool isPassed() {
      for (auto test : getSubTests()) {
         if (!test->isPassed()) return false;
      }
      return true;
   }
   virtual void addTest(std::shared_ptr<Test> subTest) {
      subTests_.push_back(subTest);
   }
   virtual void print() {
      if (Test::isPassed()) {
         Design::setTextColor(Font::BlackGreen);
      }
      else {
         Design::setTextColor(Font::BlackRed);
      }
      if (description_ != "") std::cout << description_ << std::endl;
      Design::resetTextColor();

      for (auto test : getSubTests()) {
         std::cout << "\t";
         test->print();
      }
   }
   virtual std::vector<std::pair<bool, int>> getResult() {
      std::vector<std::pair<bool, int>> allSubTests;

      for (auto subTest : subTests_) {
         std::vector<std::pair<bool, int>> newSubTests = subTest->getResult();
         for (auto element : newSubTests) {
            allSubTests.push_back(element);
         }
      }
      return allSubTests;
   }
private:
   std::string description_;
protected:
   std::vector<std::shared_ptr<Test>> subTests_;
};

class UnitTest : public Test {
public:
   UnitTest(const std::string& description, int ponderation) : Test(description), ponderation_(ponderation), isAnswerCorrect_(true) {}
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
   virtual std::vector<std::pair<bool, int>> getResult() {
      std::vector<std::pair<bool, int>> result;
      result.push_back(std::make_pair(isAnswerCorrect_, ponderation_));
      return result;
   }
   virtual void print() {
      std::cout << "\t";
      if (isAnswerCorrect_) {
         Design::setTextColor(Font::GreenBlack);
         std::cout << "[X] Test passed" << std::endl;
      }
      else {
         Design::setTextColor(Font::RedBlack);
         std::cout << "[ ] Test failed" << std::endl;
      }
      Design::resetTextColor();

   }
   void addSubTest() {}
   virtual bool isPassed() {
      return isAnswerCorrect_;
   }

private:
   bool isAnswerCorrect_;
   int ponderation_;
};

class TestSuite : public Test {
public:
   TestSuite(const std::string& description) : Test(description) {}
   void addSubTest(std::shared_ptr<UnitTest> unitTest) {
      Test::addTest(unitTest);
   }
};

// Needs to be a singleton
class TestContainer : public Test {
public:
   TestContainer() : Test() {}
   void present() {
      Design::setTextColor(Font::GreenBlack);
      std::cout << "=================================" << std::endl;
      std::cout << "Starting tests:                  " << std::endl;
      std::cout << "=================================" << std::endl;
      Design::resetTextColor();
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
   std::shared_ptr<UnitTest> unitTest = std::make_shared<UnitTest>(testName, ponderation);\

#define EndTest \
   container.addSubTest(unitTest);\
}

#define ExpectEqual(element1, element2) {\
   if(element1 != element2){\
      unitTest->setAnswer(false);\
   }\
}

#define ExpectNEq(element1, element2) {\
   if(element1 == element2){\
      unitTest->setAnswer(false);\
   }\
}