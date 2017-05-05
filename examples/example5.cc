#include "cpptk.h"
#include <string>
#include <iostream>
#include <cmath>
#include <queue>

using namespace Tk;
using namespace std;

// parameters of the animation
int initLen = 100;
int delay   = 50;
double x1d  = 0.02;
double y1d  = 0.03;
double x2d  = 0.04;
double y2d  = 0.05;
double rd   = 0.01;
double gd   = 0.02;
double bd   = 0.03;

// queue of lines
queue<string> lines;

// this function creates and draws a new line
void newLine()
{
     static double x1a = 0.0;
     static double y1a = 0.0;
     static double x2a = 0.0;
     static double y2a = 0.0;
     static double ra = 0.0;
     static double ga = 0.0;
     static double ba = 0.0;
     
     // get the current size of the canvas
     int w = winfo(width, ".c");
     int h = winfo(height, ".c");
     
     // compute the coordinates of the new line
     Point p1(static_cast<int>(w / 2 * (1 + sin(x1a))),
              static_cast<int>(h / 2 * (1 + sin(y1a))));
     Point p2(static_cast<int>(w / 2 * (1 + sin(x2a))),
              static_cast<int>(h / 2 * (1 + sin(y2a))));
     
     // compute the color of the new line
     int r = static_cast<int>(127 * (1 + sin(ra)));
     int g = static_cast<int>(127 * (1 + sin(ga)));
     int b = static_cast<int>(127 * (1 + sin(ba)));

     // draw the line and add its id to the queue
     lines.push(".c" << create(line, p1, p2) -Tk::fill(rgb(r, g, b)));
     
     x1a += x1d;
     y1a += y1d;
     x2a += x2d;
     y2a += y2d;
     ra += rd;
     ga += gd;
     ba += ::bd;
}

// note: this is used so that there is
// only one callback registration
string afterCommand;

// this function makes each step of the animation
void nextStep()
{
     newLine();
     
     // remove the oldest line from the queue and from the screen
     ".c" << deleteitem(lines.front());
     lines.pop();
     
     // call me again
     after(delay, afterCommand);
}

int main(int, char *argv[])
{
     try
     {     
          init(argv[0]);
          
          // create the canvas widget
          
          pack(canvas(".c") -background("black"))
               -expand(true) -Tk::fill(both);
          update();
          
          // create the first initLen lines
          for (int i = 0; i != initLen; ++i)
          {
               newLine();
          }
          
          // register the callback function
          afterCommand = callback(nextStep);
          
          // start animation
          after(delay, afterCommand);
          
          runEventLoop();
     }
     catch (exception const &e)
     {
          cerr << "Error: " << e.what() << '\n';
     }
}
