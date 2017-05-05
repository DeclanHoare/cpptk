#include "cpptk.h"
#include <iostream>

using namespace Tk;
using namespace std;

int main(int, char *argv[])
{
     try
     {
          init(argv[0]);
          
          label(".l") -text("Hello C++/Tk!");
          pack(".l") -padx(20) -pady(6);
          
          runEventLoop();
     }
     catch (exception const &e)
     {
          cerr << "Error: " << e.what() << '\n';
     }
}
