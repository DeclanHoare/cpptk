#include "cpptk.h"
#include <iostream>
#include <fstream>

using namespace Tk;

// this procedure will support the "File->Open" menu command
void openFile()
{
     // open standard "Open File" dialog
     
     std::string fileName(tk_getOpenFile());
     
     // read the file
     
     std::ifstream f(fileName.c_str());
     std::string fileContent(
          std::istreambuf_iterator<char>(f.rdbuf()),
          std::istreambuf_iterator<char>());
     
     // put the file content into the text widget
     
     ".t" << deletetext(txt(1,0), end);
     ".t" << insert(end, fileContent);
}

// this procedure will support the "File->Save" menu command
void saveFile()
{
     // open standard "Save File" dialog
     
     std::string fileName(tk_getSaveFile());
     
     // get the content from the text widget
     
     std::string content(".t" << get(txt(1,0), end));
     
     // write the file
     
     std::ofstream f(fileName.c_str());
     f << content;
}

int main(int, char *argv[])
{
     try
     {
          init(argv[0]);
          
          // create the menubar

          frame(".mbar") -borderwidth(1) -relief(raised);
          pack(".mbar") -Tk::fill(x);
          
          // create the menu File entry
          
          menubutton(".mbar.file") -text("File") -submenu(".mbar.file.m");
          pack(".mbar.file") -side(Tk::left);
          
          // create the drop-down menu
          
          std::string drop(menu(".mbar.file.m"));
          drop << add(command) -menulabel("Open") -command(openFile);
          drop << add(command) -menulabel("Save") -command(saveFile);
          drop << add(command) -menulabel("Exit") -command(std::string("exit"));
          
          // create the text widget with its scrollbar
          
          textw(".t") -background("white") -yscrollcommand(".s set");
          scrollbar(".s") -command(std::string(".t yview"));
          pack(".s") -side(Tk::right) -Tk::fill(y);
          pack(".t") -expand(true) -Tk::fill(both);
          
          runEventLoop();
     }
     catch (std::exception const &e)
     {
          std::cerr << "Error: " << e.what() << '\n';
     }
}
