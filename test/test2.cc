//
// Copyright (C) 2004-2006, Maciej Sobczak
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//

#include "../cpptk.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace Tk;

int main(int, char *argv[])
{
     try
     {
          init(argv[0]);
          
          std::string str;
          int i;
     
          str = std::string(eval("return \"ala ma kota\""));
          assert(str == "ala ma kota");
     
          i = eval("return 5");
          assert(i == 5);
     
          double d = eval("return 3.14159");
          assert(std::fabs(d - 3.14159) < 0.00001);

          Point p = eval("return {3 4}");
          assert(p.x == 3 && p.y == 4);
          
          Box b = eval("return {6 7 8 9}");
          assert(b.x1 == 6 && b.y1 == 7 && b.x2 == 8 && b.y2 == 9);
          
          std::pair<int, int> p2 = eval("return {3 4}");
          assert(p2.first == 3 && p2.second == 4);
          
          std::pair<std::string, std::string> p3 = eval("return {ala ma}");
          assert(p3.first == "ala" && p3.second == "ma");
          
          std::vector<int> v1 = eval("return {1 2 3 4 5 6 7}");
          assert(v1.size() == 7);
          assert(v1[0] == 1 && v1[1] == 2 && v1[2] == 3 && v1[3] == 4
               && v1[4] == 5 && v1[5] == 6 && v1[6] == 7);

          std::vector<std::string> v2 = eval("return {ala ma {nowego kota}}");
          assert(v2.size() == 3);
          assert(v2[0] == "ala");
          assert(v2[1] == "ma");
          assert(v2[2] == "nowego kota");
          
          
          std::cout << "conversion test OK\n";
     }
     catch(std::exception const &e)
     {
          std::cerr << "Error: " << e.what() << '\n';
     }
}
