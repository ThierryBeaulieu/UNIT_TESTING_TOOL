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
   void setTextColor(unsigned char color);
   void printAllColorCombinations();
   void resetTextColor();
}

class Test {
public:
   Test(const std::string& description){}
private:
   std::string description_;
};

class UnitTest : public Test {
public:

private:
};

class TestSuite : public Test {
public:

};

// Needs to be a singleton
class TestContainer : public Test {
public:
private:
   std::vector<std::shared_ptr<Test>> tests_;
};

#define BeginTesting {


#define EndTesting }


#define BeginTestSuite(testName) {

#define EndTestSuite }


// TODO: Add a queue so that all tests are going to 
// be verified before using a color?
#define BeginTest(testName, ponderation) {

#define EndTest }

#define ExpectEqual(element1, element2) { }

#define ExpectNEq(element1, element2) { }