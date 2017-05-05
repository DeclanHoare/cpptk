#include "cpptk.h"
#include <iostream>

using namespace Tk;
using namespace std;

// these variables are used to communicate with widgets
string str;
int len;

// 'check' validates user input
bool check(string const &s)
{
     return s.size() <= 12;
}

void compute()
{
     len = static_cast<int>(str.size());
}

int main(int, char *argv[])
{
     try
     {
          init(argv[0]);
          
          label(".lab1") -text("strlen(");

          // create entry widget with validation
          entry(".e1") -textvariable(str) -validate(key)
               -validatecommand(check, valid_P) -width(20);
          
          label(".lab2") -text(")");
          
          button(".b") -text(" = ") -command(compute);
          
          entry(".e2") -textvariable(len) -width(5) -justify(Tk::right);
          
          pack(".lab1", ".e1", ".lab2", ".b", ".e2") -side(Tk::left) -padx(5);
          
          runEventLoop();
     }
     catch (exception const &e)
     {
          cerr << "Error: " << e.what() << '\n';
     }
}
