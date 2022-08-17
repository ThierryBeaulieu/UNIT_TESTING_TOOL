
#pragma once

#include <iostream>
#include <vector>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#endif

enum Font {
   Green = 10,
   BlackGreen = 160,
   Original = 15,
   GreenYellow = 16,
};

void printSuite(const std::string& content) {
   std::cout << content << std::endl;
}

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
   SetConsoleTextAttribute(console_color, Font::Original);
#endif
}

#define BeginTestSuite(testName) {\
   setTextColor(Font::BlackGreen);\
   printSuite(testName);\
   resetTextColor();

#define EndTestSuite }

void printUnit(const std::string& testName) {
   std::cout << "[X] " << testName << std::endl;
}


// TODO: Add a queue so that all tests are going to 
// be verified before using a color?
#define BeginTest(testName, ponderation) {\
   setTextColor(Font::Green);\
   printUnit(testName);\
   resetTextColor();

#define EndTest }


#define ExpectEqual(element1, element2)\
   if (element1 == element2){\
   std::cout << "Hello world" << std::endl;\
   }

class Test {
   public:
   private:
};

#define BeginTesting
#define EndTesting


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