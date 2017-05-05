#include "cpptk.h"
#include <iostream>

using namespace Tk;
using namespace std;

void sayHello()
{
     cout << "Hello C++/Tk!" << endl;
}

int main(int, char *argv[])
{
     try
     {
          init(argv[0]);
          
          button(".b") -text("Say Hello") -command(sayHello);
          pack(".b") -padx(20) -pady(6);
          
          runEventLoop();
     }
     catch (exception const &e)
     {
          cerr << "Error: " << e.what() << '\n';
     }
}
