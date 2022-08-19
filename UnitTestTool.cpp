#include "UnitTestTool.h"

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