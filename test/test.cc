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
#include <sstream>
#include <vector>

using namespace Tk;

std::ostringstream ss;

#define CHECK(expected) if (ss.str() != expected "\n") \
     { \
          std::cout << "in line : " << __LINE__ << "\n" \
          << "expected: " << expected << '\n' \
          << "was     : " << ss.str(); \
          assert(false); \
     } \
     else \
     { \
          ss.str(std::string()); \
     }

// various callbacks

void cb0() {}
void cb1(int) {}
void cb2(std::string const &, int, int, int, int,
     std::string const &, std::string const &,
     std::string const &, int) {}
void cb3(std::string const &,
     std::string const &, int, std::string const &,
     int, int, int, int) {}
     
bool cbb0(std::string const &) { return true; }

void commandsTest()
{
     bell();
     CHECK("bell");;

     bind(".f", "<Button-1>");
     CHECK("bind .f <Button-1> {}");
     bind(".f", "<Button-1>", cb0);
     CHECK("bind .f <Button-1> { CppTk::callback0 }");
     bind(".f", "<Button-1>", cb1, event_x);
     CHECK("bind .f <Button-1> { CppTk::callback1 %x }");
     bind(".f", "<Button-1>", cb2, event_A, event_b, event_D,
          event_f, event_h, event_k, event_K, event_m, event_N);
     CHECK("bind .f <Button-1> { CppTk::callback2 %A %b %D %f %h %k %K "
          "%m %N }");
     bind(".f", "<Button-1>", cb3, event_s, event_T, event_w, event_W,
          event_x, event_y, event_X, event_Y);
     CHECK("bind .f <Button-1> { CppTk::callback3 %s %T %w %W %x %y %X %Y }");

     bindtags(".w");
     CHECK("bindtags .w");
     bindtags(".b1", "all . Button b1");
     CHECK("bindtags .b1 { all . Button b1 }");

     button(".b");
     CHECK("button .b");
     button(".b") -text("Hello");
     CHECK("button .b -text \"Hello\"");

     canvas(".c");
     CHECK("canvas .c");
     
     checkbutton(".cb") -text("check me");
     CHECK("checkbutton .cb -text \"check me\"");
     
     clipboard(clear);
     CHECK("clipboard clear");
     clipboard(clear) -displayof(".top");
     CHECK("clipboard clear -displayof .top");
     clipboard(append, "ala ma kota") -format("STRING") -cliptype("STRING");
     CHECK("clipboard append -format STRING -type STRING -- \"ala ma kota\"");
     clipboard(get);
     CHECK("clipboard get");
     
     destroy(".b");
     CHECK("destroy .b");
     
     entry(".e");
     CHECK("entry .e");
     
     focus() -displayof(".");
     CHECK("focus -displayof .");
     focus(".e");
     CHECK("focus .e");
     focus() -force(".e");
     CHECK("focus -force .e");
     focus() -lastfor(".");
     CHECK("focus -lastfor .");
     
     fonts(create, "myfont");
     CHECK("font create myfont");
     fonts(configure, "myfont") -size(20) -underline(true);
     CHECK("font configure myfont -size 20 -underline 1");
     fonts(deletefont, "myfont");
     CHECK("font delete myfont");
     fonts(families);
     CHECK("font families");
     
     frame(".f") -wndclass("myclass") -colormap("new") -container(true);
     CHECK("frame .f -class myclass -colormap new -container 1");
     
     grab(current);
     CHECK("grab current");
     grab(current, ".f");
     CHECK("grab current .f");
     grab(release, ".f");
     CHECK("grab release .f");
     grab(set, ".f");
     CHECK("grab set .f");
     grab(setglobal, ".f");
     CHECK("grab set -global .f");
     grab(status, ".f");
     CHECK("grab status .f");

     grid(bbox, ".");
     CHECK("grid bbox .");
     grid(bbox, ".", 2, 3);
     CHECK("grid bbox . 2 3");
     grid(bbox, ".", 2, 3, 4, 5);
     CHECK("grid bbox . 2 3 4 5");
     grid(columnconfigure, ".", 3) -minsize(5) -weight(2) -uniform("abc")
          -pad(5);
     CHECK("grid columnconfigure . 3 -minsize 5 -weight 2 -uniform abc"
          " -pad 5");
     grid(configure, ".b") -column(3) -columnspan(2) -in(".") -row(2)
          -rowspan(2) -sticky("ne");
     CHECK("grid configure .b -column 3 -columnspan 2 -in . -row 2"
          " -rowspan 2 -sticky ne");
     grid(forget, ".e");
     CHECK("grid forget .e");
     grid(info, ".e");
     CHECK("grid info .e");
     grid(location, ".e", 25, 30);
     CHECK("grid location .e 25 30");
     grid(propagate, ".");
     CHECK("grid propagate .");
     grid(propagate, ".", false);
     CHECK("grid propagate . 0");
     grid(rowconfigure, ".", 3) -minsize(5) -weight(2) -uniform("abc")
          -pad(5);
     CHECK("grid rowconfigure . 3 -minsize 5 -weight 2 -uniform abc -pad 5");
     grid(Tk::remove, ".e");
     CHECK("grid remove .e");
     grid(size, ".");
     CHECK("grid size .");
     grid(slaves, ".") -row(3) -column(4);
     CHECK("grid slaves . -row 3 -column 4");
     
     images(create, bitmap);
     CHECK("image create bitmap");
     images(create, photo) -Tk::gamma(1.5) -palette(10);
     CHECK("image create photo -gamma 1.5 -palette 10");
     images(create, photo, "myimg") -file("myimg.jpg");
     CHECK("image create photo myimg -file \"myimg.jpg\"");
     images(deleteimg, "myimg");
     CHECK("image delete myimg");
     images(height, "myimg");
     CHECK("image height myimg");
     images(inuse, "myimg");
     CHECK("image inuse myimg");
     images(names);
     CHECK("image names");
     images(type, "myimg");
     CHECK("image type myimg");
     images(types);
     CHECK("image types");
     images(width, "myimg");
     CHECK("image width myimg");
     
     label(".l");
     CHECK("label .l");
     
     labelframe(".lf") -labelanchor(nw) -labelwidget(".lf.w");
     CHECK("labelframe .lf -labelanchor nw -labelwidget .lf.w");
     
     listbox(".lb") -setgrid(true) -activestyle(underline)
          -selectmode(browse);
     CHECK("listbox .lb -setgrid 1 -activestyle underline"
          " -selectmode browse");

     lower(".e");
     CHECK("lower .e");
     lower(".e", ".f");
     CHECK("lower .e .f");
     
     menu(".m") -activeborderwidth(3) -postcommand(cb0) -tearoff(true)
          -title("My title");
     CHECK("menu .m -activeborderwidth 3 -postcommand CppTk::callback4"
          " -tearoff 1 -title \"My title\"");
     
     menubutton(".mb") -direction(above);
     CHECK("menubutton .mb -direction above");
     
     message(".msg") -aspect(200);
     CHECK("message .msg -aspect 200");
     
     option(add, "abc", "def");
     CHECK("option add \"abc\" \"def\"");
     option(add, "abc", "def", interactive);
     CHECK("option add \"abc\" \"def\" interactive");
     option(clear);
     CHECK("option clear");
     option(get, ".w", "abc", "def");
     CHECK("option get \".w\" \"abc\" def");
     option(readfile, "file");
     CHECK("option readfile \"file\"");
     
     pack(".b") -expand(true) -fill(x) -fill(both) -in(".f") -side(left);
     CHECK("pack .b -expand 1 -fill x -fill both -in .f -side left");
     pack(".b1", ".b2", ".b3");
     CHECK("pack .b1 .b2 .b3");
     pack(configure, ".b1") -after(".b2") -before(".b3");
     CHECK("pack configure .b1 -after .b2 -before .b3");
     pack(forget, ".b");
     CHECK("pack forget .b");
     pack(info, ".b");
     CHECK("pack info .b");
     pack(propagate, ".f");
     CHECK("pack propagate .f");
     pack(propagate, ".f", true);
     CHECK("pack propagate .f 1");
     pack(slaves, ".f");
     CHECK("pack slaves .f");
     
     panedwindow(".pw") -orient(horizontal);
     CHECK("panedwindow .pw -orient horizontal");
     panedwindow(".pw") -orient(vertical) -handlepad(50) -handlesize(10)
          -opaqueresize(true) -sashcursor("mycursor") -sashpad(5)
          -sashrelief(raised) -sashwidth(10) -showhandle(true);
     CHECK("panedwindow .pw -orient vertical -handlepad 50 -handlesize 10"
          " -opaqueresize 1 -sashcursor mycursor -sashpad 5"
          " -sashrelief raised -sashwidth 10 -showhandle 1");
     
     place(".b") -bordermode(inside) -x(10) -y(30);
     CHECK("place .b -bordermode inside -x 10 -y 30");
     // FIXME Floating Point Imprecision
     // place(configure, ".b") -relx(5) -rely(6) -relheight(0.5) -relwidth(0.6);
     // CHECK("place configure .b -relx 5 -rely 6 -relheight 0.5 -relwidth 0.6");
     place(forget, ".b");
     CHECK("place forget .b");
     place(info, ".b");
     CHECK("place info .b");
     place(slaves, ".f");
     CHECK("place slaves .f");
     
     radiobutton(".rb");
     CHECK("radiobutton .rb");
     
     raise(".b");
     CHECK("raise .b");
     raise(".b", ".f");
     CHECK("raise .b .f");
     
     scale(".s") -troughcolor("blue") -bigincrement(10) -digits(3) -from(5)
          -to(500) -length(100) -resolution(10) -showvalue(true)
          -sliderlength(100) -sliderrelief(raised) -tickinterval(20);
     CHECK("scale .s -troughcolor blue -bigincrement 10 -digits 3 -from 5"
          " -to 500 -length 100 -resolution 10 -showvalue 1"
          " -sliderlength 100 -sliderrelief raised -tickinterval 20");
     
     scrollbar(".sb") -jump(true) -activerelief(raised)
          -elementborderwidth(5);
     CHECK("scrollbar .sb -jump 1 -activerelief raised"
          " -elementborderwidth 5");
     
     selection(clear) -displayof(".w") -sel("PRIMARY");
     CHECK("selection clear -displayof .w -sel PRIMARY");
     selection(get) -cliptype("STRING");
     CHECK("selection get -type STRING");
     
     // FIXME Floating Point Imprecision
     // spinbox(".sp") -buttonbackground("blue") -buttoncursor("mycursor")
     //      -buttondownrelief(sunken) -buttonuprelief(raised) -format("%0.3f")
     //      -from(0) -to(10) -increment(0.1) -values("a b c d") -wrap(true);
     // CHECK("spinbox .sp -buttonbackground blue -buttoncursor mycursor"
     //      " -buttondownrelief sunken -buttonuprelief raised -format %0.3f"
     //      " -from 0 -to 10 -increment 0.1 -values \"a b c d\" -wrap 1");
     
     textw(".t") -autoseparators(true) -maxundo(100) -spacing1(5) -spacing2(6)
          -spacing3(7) -tabs("2c left 4c 6c center") -undo(true)
          -wrap(wrapchar);
     CHECK("text .t -autoseparators 1 -maxundo 100 -spacing1 5 -spacing2 6"
          " -spacing3 7 -tabs \"2c left 4c 6c center\" -undo 1 -wrap char");
     
     tk_chooseColor() -initialcolor("blue") -parent(".")
          -title("select color");
     CHECK("tk_chooseColor -initialcolor blue -parent ."
          " -title \"select color\"");
     
     tk_chooseDirectory() -initialdir("/usr/home") -mustexist(true);
     CHECK("tk_chooseDirectory -initialdir \"/usr/home\" -mustexist 1");
     
     tk_dialog(".d", "some title", "some text", warning, "OK", "OK",
          "Cancel");
     CHECK("tk_dialog .d \"some title\" \"some text\" warning \"OK\" \"OK\""
          " \"Cancel\"");
     
     tk_focusNext(".b");
     CHECK("tk_focusNext .b");
     tk_focusPrev(".b");
     CHECK("tk_focusPrev .b");
     
     tk_getOpenFile() -defaultextension(".txt")
          -filetypes("{{Text files} {.txt}}") -initialfile("file.txt")
          -multiple();
     CHECK("tk_getOpenFile -defaultextension \".txt\""
          " -filetypes {{{Text files} {.txt}}} -initialfile \"file.txt\""
          " -multiple");
     
     tk_getSaveFile();
     CHECK("tk_getSaveFile");
     
     tk_menuSetFocus(".m");
     CHECK("tk_menuSetFocus .m");
     
     tk_messageBox() -defaultbutton("OK") -icon(question)
          -messagetext("some text") -messagetype(yesnocancel);
     CHECK("tk_messageBox -default \"OK\" -icon question"
          " -message \"some text\" -type yesnocancel");
     
     std::vector<std::string> values;
     values.push_back("ala");
     values.push_back("ma");
     values.push_back("kota");
     std::string menuVal;
     tk_optionMenu(".m", menuVal, values.begin(), values.end());
     CHECK("tk_optionMenu .m CppTk::variable0 \"ala\" \"ma\" \"kota\"");
     
     tk_popup(".m", 50, 60);
     CHECK("tk_popup .m 50 60");
     tk_popup(".m", 50, 60, 3);
     CHECK("tk_popup .m 50 60 3");
     
     tk_setPalette("blue");
     CHECK("tk_setPalette blue");
     
     tk_textCopy(".t");
     CHECK("tk_textCopy .t")
     tk_textCut(".t");
     CHECK("tk_textCut .t")
     tk_textPaste(".t");
     CHECK("tk_textPaste .t")
     
     tkwait(visibility, ".w");
     CHECK("tkwait visibility .w");
     tkwait(window, ".w");
     CHECK("tkwait window .w");
     
     toplevel(".w") -screen("scr") -use("1234");
     CHECK("toplevel .w -screen \"scr\" -use 1234");
     
     winfo(atom, "name");
     CHECK("winfo atom name");
     winfo(atom, "name") -displayof(".w");
     CHECK("winfo atom -displayof .w name");
     winfo(atomname, "id");
     CHECK("winfo atomname id");
     winfo(cells, "name");
     CHECK("winfo cells name");
     winfo(children, "name");
     CHECK("winfo children name");
     winfo(wndclass, "name");
     CHECK("winfo class name");
     winfo(colormapfull, "name");
     CHECK("winfo colormapfull name");
     winfo(containing, 100, 200);
     CHECK("winfo containing 100 200");
     winfo(depth, "name");
     CHECK("winfo depth name");
     winfo(exists, "name");
     CHECK("winfo exists name");
     winfo(fpixels, "name", 100);
     CHECK("winfo fpixels name 100");
     winfo(geometry, "name");
     CHECK("winfo geometry name");
     winfo(height, "name");
     CHECK("winfo height name");
     winfo(id, "name");
     CHECK("winfo id name");
     winfo(ismapped, "name");
     CHECK("winfo ismapped name");
     winfo(manager, "name");
     CHECK("winfo manager name");
     winfo(name, "name");
     CHECK("winfo name name");
     winfo(parent, "name");
     CHECK("winfo parent name");
     winfo(pathname, "name");
     CHECK("winfo pathname name");
     winfo(pixels, "name", 100);
     CHECK("winfo pixels name 100");
     winfo(pointerx, "name");
     CHECK("winfo pointerx name");
     winfo(pointerxy, "name");
     CHECK("winfo pointerxy name");
     winfo(pointery, "name");
     CHECK("winfo pointery name");
     winfo(regheight, "name");
     CHECK("winfo regheight name");
     winfo(regwidth, "name");
     CHECK("winfo regwidth name");
     winfo(rgb, "name", "blue");
     CHECK("winfo rgb name blue");
     winfo(rootx, "name");
     CHECK("winfo rootx name");
     winfo(rooty, "name");
     CHECK("winfo rooty name");
     winfo(screen, "name");
     CHECK("winfo screen name");
     winfo(screencells, "name");
     CHECK("winfo screencells name");
     winfo(screendepth, "name");
     CHECK("winfo screendepth name");
     winfo(screenheight, "name");
     CHECK("winfo screenheight name");
     winfo(screenmmheight, "name");
     CHECK("winfo screenmmheight name");
     winfo(screenmmwidth, "name");
     CHECK("winfo screenmmwidth name");
     winfo(screenvisual, "name");
     CHECK("winfo screenvisual name");
     winfo(screenwidth, "name");
     CHECK("winfo screenwidth name");
     winfo(server, "name");
     CHECK("winfo server name");
     winfo(toplevel, "name");
     CHECK("winfo toplevel name");
     winfo(viewable, "name");
     CHECK("winfo viewable name");
     winfo(visual, "name");
     CHECK("winfo visual name");
     winfo(visualid, "name");
     CHECK("winfo visualid name");
     winfo(visualsavailable, "name");
     CHECK("winfo visualsavailable name");
     winfo(vrootheight, "name");
     CHECK("winfo vrootheight name");
     winfo(vrootwidth, "name");
     CHECK("winfo vrootwidth name");
     winfo(vrootx, "name");
     CHECK("winfo vrootx name");
     winfo(vrooty, "name");
     CHECK("winfo vrooty name");
     winfo(width, "name");
     CHECK("winfo width name");
     winfo(x, "name");
     CHECK("winfo x name");
     winfo(y, "name");
     CHECK("winfo y name");
     
     wm(aspect, ".w");
     CHECK("wm aspect .w");
     wm(aspect, ".w", 10, 20, 30, 40);
     CHECK("wm aspect .w \"10\" \"20\" \"30\" \"40\"");
     wm(aspect, ".w", "", "", "", "");
     CHECK("wm aspect .w \"\" \"\" \"\" \"\"");
     wm(client, ".w");
     CHECK("wm client .w");
     wm(client, ".w", "name");
     CHECK("wm client .w \"name\"");
     wm(deiconify, ".w");
     CHECK("wm deiconify .w");
     wm(focusmodel, ".w");
     CHECK("wm focusmodel .w");
     wm(focusmodel, ".w", active);
     CHECK("wm focusmodel .w \"active\"");
     wm(focusmodel, ".w", passive);
     CHECK("wm focusmodel .w \"passive\"");
     wm(frame, ".w");
     CHECK("wm frame .w");
     wm(geometry, ".w");
     CHECK("wm geometry .w");
     wm(geometry, ".w", "=100x200+50+60");
     CHECK("wm geometry .w \"=100x200+50+60\"");
     wm(grid, ".w");
     CHECK("wm grid .w");
     wm(grid, ".w", 10, 20, 30, 40);
     CHECK("wm grid .w \"10\" \"20\" \"30\" \"40\"");
     wm(group, ".w");
     CHECK("wm group .w");
     wm(group, ".w", ".w2");
     CHECK("wm group .w \".w2\"");
     wm(group, ".w", "");
     CHECK("wm group .w \"\"");
     wm(iconbitmap, ".w");
     CHECK("wm iconbitmap .w");
     wm(iconbitmap, ".w", "mybitmap");
     CHECK("wm iconbitmap .w \"mybitmap\"");
     wm(iconify, ".w");
     CHECK("wm iconify .w");
     wm(iconmask, ".w");
     CHECK("wm iconmask .w");
     wm(iconmask, ".w", "mybitmap");
     CHECK("wm iconmask .w \"mybitmap\"");
     wm(iconname, ".w");
     CHECK("wm iconname .w");
     wm(iconname, ".w", "myicon");
     CHECK("wm iconname .w \"myicon\"");
     wm(iconposition, ".w");
     CHECK("wm iconposition .w");
     wm(iconposition, ".w", 50, 60);
     CHECK("wm iconposition .w \"50\" \"60\"");
     wm(iconwindow, ".w");
     CHECK("wm iconwindow .w");
     wm(iconwindow, ".w", ".i");
     CHECK("wm iconwindow .w \".i\"");
     wm(maxsize, ".w");
     CHECK("wm maxsize .w");
     wm(maxsize, ".w", 200, 300);
     CHECK("wm maxsize .w \"200\" \"300\"");
     wm(minsize, ".w");
     CHECK("wm minsize .w");
     wm(minsize, ".w", 200, 300);
     CHECK("wm minsize .w \"200\" \"300\"");
     wm(overrideredirect, ".w");
     CHECK("wm overrideredirect .w");
     wm(overrideredirect, ".w", true);
     CHECK("wm overrideredirect .w \"1\"");
     wm(positionfrom, ".w");
     CHECK("wm positionfrom .w");
     wm(positionfrom, ".w", program);
     CHECK("wm positionfrom .w \"program\"");
     wm(positionfrom, ".w", user);
     CHECK("wm positionfrom .w \"user\"");
     wm(resizable, ".w");
     CHECK("wm resizable .w");
     wm(resizable, ".w", false, false);
     CHECK("wm resizable .w \"0\" \"0\"");
     wm(sizefrom, ".w");
     CHECK("wm sizefrom .w");
     wm(sizefrom, ".w", program);
     CHECK("wm sizefrom .w \"program\"");
     wm(sizefrom, ".w", user);
     CHECK("wm sizefrom .w \"user\"");
     wm(stackorder, ".w1");
     CHECK("wm stackorder .w1");
     wm(stackorder, ".w1", isabove, ".w2");
     CHECK("wm stackorder .w1 \"isabove\" \".w2\"");
     wm(stackorder, ".w1", isbelow, ".w2");
     CHECK("wm stackorder .w1 \"isbelow\" \".w2\"");
     wm(state, ".w");
     CHECK("wm state .w");
     wm(state, ".w", normal);
     CHECK("wm state .w \"normal\"");
     wm(state, ".w", iconic);
     CHECK("wm state .w \"iconic\"");
     wm(state, ".w", withdrawn);
     CHECK("wm state .w \"withdrawn\"");
     wm(state, ".w", icon);
     CHECK("wm state .w \"icon\"");
     wm(state, ".w", zoomed);
     CHECK("wm state .w \"zoomed\"");
     wm(title, ".w");
     CHECK("wm title .w");
     wm(title, ".w", "some title");
     CHECK("wm title .w \"some title\"");
     wm(transient, ".w");
     CHECK("wm transient .w");
     wm(transient, ".w", ".w1");
     CHECK("wm transient .w \".w1\"");
     wm(withdraw, ".w");
     CHECK("wm withdraw .w");
     
     wmprotocol(".w");
     CHECK("wm protocol .w");
     wmprotocol(".w", "WM_DELETE_WINDOW");
     CHECK("wm protocol .w WM_DELETE_WINDOW");
     wmprotocol(".w", "WM_DELETE_WINDOW", cb0);
     CHECK("wm protocol .w WM_DELETE_WINDOW { CppTk::callback5 }");

          
     std::cout << "commands test OK\n";
}

void widgetCommandsTest()
{
     ".lb" << activate(5);
     CHECK(".lb activate 5");
     ".sb" << activate(arrow1);
     CHECK(".sb activate arrow1");
     
     ".m" << add(cascade) -submenu(".m.m");
     CHECK(".m add cascade -menu .m.m");
     ".m" << add(checkbutton) -hidemargin(true);
     CHECK(".m add checkbutton -hidemargin 1");
     ".m" << add(command) -accelerator("Ctrl-x") -menulabel("select me");
     CHECK(".m add command -accelerator \"Ctrl-x\" -label \"select me\"");
     ".m" << add(radiobutton) -columnbreak(true) -value(5);
     CHECK(".m add radiobutton -columnbreak 1 -value \"5\"");
     ".m" << add(separator);
     CHECK(".m add separator");
     ".pw" << add(".b");
     CHECK(".pw add .b");
     
     ".c" << addtag("mytag", above, "item");
     CHECK(".c addtag mytag above item");
     ".c" << addtag("mytag", all);
     CHECK(".c addtag mytag all");
     ".c" << addtag("mytag", below, "item");
     CHECK(".c addtag mytag below item");
     ".c" << addtag("mytag", closest, 10, 20);
     CHECK(".c addtag mytag closest 10 20");
     ".c" << addtag("mytag", closest, 10, 20, 5);
     CHECK(".c addtag mytag closest 10 20 5");
     ".c" << addtag("mytag", closest, 10, 20, 5, "item");
     CHECK(".c addtag mytag closest 10 20 5 item");
     ".c" << addtag("mytag", enclosed, 10, 20, 30, 40);
     CHECK(".c addtag mytag enclosed 10 20 30 40");
     ".c" << addtag("mytag", overlapping, 10, 20, 30, 40);
     CHECK(".c addtag mytag overlapping 10 20 30 40");
     ".c" << addtag("mytag", withtag, "item");
     CHECK(".c addtag mytag withtag item");

     ".c" << bbox("item");
     CHECK(".c bbox item");
     ".e" << bbox(5);
     CHECK(".e bbox 5");
     ".e" << bbox(at(25));
     CHECK(".e bbox @25");

     std::vector<std::string> items;
     items.push_back("item1");
     items.push_back("item2");
     items.push_back("item3");
     ".c" << bbox(items.begin(), items.end());
     CHECK(".c bbox item1 item2 item3");

     ".c" << bind("item", "<Button-1>");
     CHECK(".c bind item <Button-1> {}");
     
     "myphoto" << blank();
     CHECK("myphoto blank");

     ".c" << canvasx(20);
     CHECK(".c canvasx 20");
     ".c" << canvasx(20, 5);
     CHECK(".c canvasx 20 5");

     ".c" << canvasy(20);
     CHECK(".c canvasy 20");
     ".c" << canvasy(20, 5);
     CHECK(".c canvasy 20 5");

     ".b" << cget(text);
     CHECK(".b cget -text");
     
     ".m" << clone(".m2");
     CHECK(".m clone .m2");
     ".m" << clone(".m2", tearoff);
     CHECK(".m clone .m2 tearoff");
     
     ".t" << compare(txt(5,6), "<", txt(6,5));
     CHECK(".t compare 5.6 < 6.5");

     ".b" << configure() -text("Hello") -height(10);
     CHECK(".b configure -text \"Hello\" -height 10");

     ".c" << coords("item");
     CHECK(".c coords item");
     ".c" << coords("item", 10, 20);
     CHECK(".c coords item 10 20");
     ".c" << coords("item", Point(10, 20));
     CHECK(".c coords item 10 20");
     ".c" << coords("item", 10, 20, 30, 40);
     CHECK(".c coords item 10 20 30 40");
     ".c" << coords("item", Point(10, 20), Point(30, 40));
     CHECK(".c coords item 10 20 30 40");
     ".c" << coords("item", Box(10, 20, 30, 40));
     CHECK(".c coords item 10 20 30 40");
     std::vector<int> crds;
     crds.push_back(10);
     crds.push_back(20);
     crds.push_back(30);
     crds.push_back(40);
     ".c" << coords("item", crds.begin(), crds.end());
     CHECK(".c coords item 10 20 30 40");
     ".s" << coords();
     CHECK(".s coords");
     ".s" << coords(150);
     CHECK(".s coords 150");
     
     "photo1" << copy("photo2") -from(10, 20, 30, 40) -to(10, 20, 30, 40)
          -shrink() -zoom(2, 3) -subsample(3, 4) -compositingrule(overlay);
     CHECK("photo1 copy photo2 -from 10 20 30 40 -to 10 20 30 40"
          " -shrink -zoom 2 3 -subsample 3 4 -compositingrule overlay");

     ".c" << create(text, 10, 20);
     CHECK(".c create text 10 20");
     ".c" << create(text, Point(10, 20));
     CHECK(".c create text 10 20");
     ".c" << create(rectangle, 10, 20, 30, 40);
     CHECK(".c create rectangle 10 20 30 40");
     ".c" << create(rectangle, Point(10, 20), Point(30, 40));
     CHECK(".c create rectangle 10 20 30 40");
     ".c" << create(rectangle, Box(10, 20, 30, 40));
     CHECK(".c create rectangle 10 20 30 40");
     ".c" << create(line, crds.begin(), crds.end());
     CHECK(".c create line 10 20 30 40");
     
     ".lb" << curselection();
     CHECK(".lb curselection");

     ".c" << dchars("item", 5);
     CHECK(".c dchars item 5");
     ".c" << dchars("item", 5, 7);
     CHECK(".c dchars item 5 7");
     ".c" << dchars("item", at(5, 6));
     CHECK(".c dchars item @5,6");
     
     ".t" << debug();
     CHECK(".t debug");
     ".t" << debug(true);
     CHECK(".t debug 1");

     ".m" << deleteentry(5);
     CHECK(".m delete 5");
     ".m" << deleteentry(5, 8);
     CHECK(".m delete 5 8");

     ".lb" << deleteitem(5);
     CHECK(".lb delete 5");
     ".c" << deleteitem("item");
     CHECK(".c delete item");
     ".c" << deleteitem(items.begin(), items.end());
     CHECK(".c delete item1 item2 item3");

     ".e" << deletetext(5);
     CHECK(".e delete 5");
     ".e" << deletetext(5, end);
     CHECK(".e delete 5 end");
     
     ".sb" << delta(50, 60);
     CHECK(".sb delta 50 60");

     ".cb" << deselect();
     CHECK(".cb deselect");
     
     ".t" << dlineinfo(txt(5,6));
     CHECK(".t dlineinfo 5.6");
     
     ".c" << dtag("mytag");
     CHECK(".c dtag mytag");
     ".c" << dtag("mytag", "myothertag");
     CHECK(".c dtag mytag myothertag");

     ".t" << dump(txt(5,6)) -all() -image() -mark() -tags() -text() -window();
     CHECK(".t dump -all -image -mark -tag -text -window 5.6");
     ".t" << dump(txt(5,6), txt(7,end)) -all();
     CHECK(".t dump -all 5.6 7.end");
     
     ".t" << edit(modified);
     CHECK(".t edit modified");
     ".t" << edit(modified, false);
     CHECK(".t edit modified 0");
     ".t" << edit(redo);
     CHECK(".t edit redo");
     ".t" << edit(reset);
     CHECK(".t edit reset");
     ".t" << edit(separator);
     CHECK(".t edit separator");
     ".t" << edit(undo);
     CHECK(".t edit undo");
     
     ".m" << entrycget(5, foreground);
     CHECK(".m entrycget 5 -foreground");
     ".m" << entrycget(5, menulabel);
     CHECK(".m entrycget 5 -label");
     
     ".m" << entryconfigure(5) -menulabel("select me");
     CHECK(".m entryconfigure 5 -label \"select me\"");

     ".c" << find(above, "item");
     CHECK(".c find above item");
     ".c" << find(all);
     CHECK(".c find all");
     ".c" << find(below, "item");
     CHECK(".c find below item");
     ".c" << find(closest, 10, 20);
     CHECK(".c find closest 10 20");
     ".c" << find(closest, 10, 20, 5);
     CHECK(".c find closest 10 20 5");
     ".c" << find(closest, 10, 20, 5, "item");
     CHECK(".c find closest 10 20 5 item");
     ".c" << find(enclosed, 10, 20, 30, 40);
     CHECK(".c find enclosed 10 20 30 40");
     ".c" << find(overlapping, 10, 20, 30, 40);
     CHECK(".c find overlapping 10 20 30 40");
     ".c" << find(withtag, "item");
     CHECK(".c find withtag item");

     ".c" << focus();
     CHECK(".c focus");
     ".c" << focus("item");
     CHECK(".c focus item");
     
     ".pw" << forget(".b");
     CHECK(".pw forget .b");

     ".b" << flash();
     CHECK(".b flash");
     
     ".sb" << fraction(50, 60);
     CHECK(".sb fraction 50 60");

     ".e" << get();
     CHECK(".e get");
     ".lb" << get(5);
     CHECK(".lb get 5");
     ".lb" << get(5, 8);
     CHECK(".lb get 5 8");
     ".t" << get(txt(5,6));
     CHECK(".t get 5.6");
     ".t" << get(txt(5,6), txt(7,end));
     CHECK(".t get 5.6 7.end");
     
     ".lb" << getsize();
     CHECK(".lb size");
     
     ".c" << gettags("item");
     CHECK(".c gettags item");

     ".e" << icursor(5);
     CHECK(".e icursor 5");
     ".c" << icursor("item", 5);
     CHECK(".c icursor item 5");
     
     ".pw" << identify(50, 60);
     CHECK(".pw identify 50 60");

     ".t" << images(cget, txt(5,6), align);
     CHECK(".t image cget 5.6 -align");     
     ".t" << images(cget, txt(5,6), image);
     CHECK(".t image cget 5.6 -image");     
     ".t" << images(cget, txt(5,6), name);
     CHECK(".t image cget 5.6 -name");     
     ".t" << images(cget, txt(5,6), padx);
     CHECK(".t image cget 5.6 -padx");     
     ".t" << images(cget, txt(5,6), pady);
     CHECK(".t image cget 5.6 -pady");
     ".t" << images(configure, txt(5,6)) -align(bottom);
     CHECK(".t image configure 5.6 -align bottom");
     ".t" << images(create, txt(5,6)) -name("myimage");
     CHECK(".t image create 5.6 -name myimage");
     ".t" << images(names);
     CHECK(".t image names");

     ".e" << index(5);
     CHECK(".e index 5");
     ".c" << index("item", end);
     CHECK(".c index item end");
     ".t" << index(txt(5,end));
     CHECK(".t index 5.end");

     ".e" << insert(5, "hello world");
     CHECK(".e insert 5 \"hello world\"");
     ".c" << insert("item", 5, "hello world");
     CHECK(".c insert item 5 \"hello world\"");
     ".lb" << insert(end, items.begin(), items.end());
     CHECK(".lb insert end \"item1\" \"item2\" \"item3\"");
     ".m" << insert(5, checkbutton);
     CHECK(".m insert 5 \"checkbutton\"");
     ".t" << insert(end, "ala ma kota");
     CHECK(".t insert end \"ala ma kota\"");
     ".t" << insert(end, std::string("ala ma kota"), "mytag");
     CHECK(".t insert end \"ala ma kota\" mytag");

     // Note: this is a trap - both strings will be treated as iterators
     //".t" << insert(end, "ala ma kota", "mytag");
     //CHECK(".t insert end \"ala ma kota\" mytag");

     ".b" << invoke();
     CHECK(".b invoke");
     ".m" << invoke(5);
     CHECK(".m invoke 5");

     ".c" << itemcget("item", text);
     CHECK(".c itemcget item -text");
     ".lb" << itemcget(5, background);
     CHECK(".lb itemcget 5 -background");

     ".c" << itemconfigure("item") -text("hello");
     CHECK(".c itemconfigure item -text \"hello\"");
     ".lb" << itemconfigure(5) -background("blue");
     CHECK(".lb itemconfigure 5 -background blue");

     ".c" << lower("item");
     CHECK(".c lower item");
     ".c" << lower("item1", "item2");
     CHECK(".c lower item1 item2");
     
     ".t" << mark(gravity, "mymark");
     CHECK(".t mark gravity mymark");
     ".t" << mark(gravity, "mymark", left);
     CHECK(".t mark gravity mymark left");
     ".t" << mark(names);
     CHECK(".t mark names");
     ".t" << mark(next, txt(5,6));
     CHECK(".t mark next 5.6");
     ".t" << mark(previous, txt(5,6));
     CHECK(".t mark previous 5.6");
     ".t" << mark(set, "mymark", txt(5,6));
     CHECK(".t mark set mymark 5.6");
     ".t" << mark(unset, "mymark");
     CHECK(".t mark unset mymark");

     ".c" << move("item", 10, 20);
     CHECK(".c move item 10 20");
     
     // FIXME Floating Point Imprecision
     // ".sb" << moveto(0.2);
     // CHECK(".sb moveto 0.2");
     
     ".lb" << nearest(25);
     CHECK(".lb nearest 25");
     
     ".pw" << panecget(".b", width);
     CHECK(".pw panecget .b -width");
     
     ".pw" << paneconfigure(".b") -after(".b2") -before(".b3") -height(20)
          -minsize(5) -padx(5) -pady(5) -sticky(w) -width(50);
     CHECK(".pw paneconfigure .b -after .b2 -before .b3 -height 20"
          " -minsize 5 -padx 5 -pady 5 -sticky w -width 50");
     
     ".pw" << panes();
     CHECK(".pw panes");
     
     ".m" << post(100, 150);
     CHECK(".m post 100 150");
     
     ".m" << postcascade(5);
     CHECK(".m postcascade 5");

     ".c" << postscript() -colormode(color) -file("file.eps");
     CHECK(".c postscript -colormode color -file \"file.eps\"");
     ".c" << postscript() -pageanchor(center);
     CHECK(".c postscript -pageanchor center");
     ".c" << postscript() -pageheight(10) -pagewidth("20i");
     CHECK(".c postscript -pageheight 10 -pagewidth 20i");
     ".c" << postscript() -pagex(10) -pagey(20);
     CHECK(".c postscript -pagex 10 -pagey 20");
     ".c" << postscript() -rotate(true);
     CHECK(".c postscript -rotate 1");
     ".c" << postscript() -x(10) -y(20);
     CHECK(".c postscript -x 10 -y 20");
     
     ".pw" << proxy(coord);
     CHECK(".pw proxy coord");
     ".pw" << proxy(forget);
     CHECK(".pw proxy forget");
     ".pw" << proxy(place, 50, 60);
     CHECK(".pw proxy place 50 60");
     
     "photo1" << put("red") -to(10, 20, 11, 21);
     CHECK("photo1 put red -to 10 20 11 21");

     ".c" << raise("item");
     CHECK(".c raise item");
     ".c" << raise("item1", "item2");
     CHECK(".c raise item1 item2");
     
     "photo1" << read("photo.gif") -to(10, 20);
     CHECK("photo1 read \"photo.gif\" -to 10 20");
     
     "photo1" << redither();
     CHECK("photo1 redither");
     
     ".pw" << sash(coord, 5);
     CHECK(".pw sash coord 5");
     ".pw" << sash(dragto, 5, 50, 60);
     CHECK(".pw sash dragto 5 50 60");
     ".pw" << sash(mark, 5, 50, 60);
     CHECK(".pw sash mark 5 50 60");
     ".pw" << sash(place, 5, 50, 60);
     CHECK(".pw sash place 5 50 60");
     
     // FIXME Floating Point Imprecision
     // ".c" << scale("item", 10, 20, 1.5, 1.6);
     // CHECK(".c scale item 10 20 1.5 1.6");
     
     ".e" << scan(mark, 10);
     CHECK(".e scan mark 10");
     ".e" << scan(dragto, 30);
     CHECK(".e scan dragto 30");
     ".c" << scan(mark, 10, 20);
     CHECK(".c scan mark 10 20");
     ".c" << scan(dragto, 30, 40);
     CHECK(".c scan dragto 30 40");
     ".c" << scan(dragto, 30, 40, 5);
     CHECK(".c scan dragto 30 40 5");
     
     ".sb" << scroll(5, units);
     CHECK(".sb scroll 5 units");
     ".sb" << scroll(6, pages);
     CHECK(".sb scroll 6 pages");
     
     int charcount;
     ".t" << search("pattern", txt(5,6)) -count(charcount);
     CHECK(".t search \"pattern\" -count CppTk::variable1 -- 5.6");
     ".t" << search("pattern", txt(5,6), txt(5,end)) -forwards() -backwards()
          -exact() -regexp() -nocase() -elide();
     CHECK(".t search \"pattern\" -forwards -backwards -exact -regexp"
          " -nocase -elide -- 5.6 5.end");

     ".lb" << see(5);
     CHECK(".lb see 5");
     ".t" << see(txt(5,6));
     CHECK(".t see 5.6");
     
     ".cb" << select();
     CHECK(".cb select");
     ".c" << select(adjust, "item", 5);
     CHECK(".c select adjust item 5");
     ".c" << select(clear);
     CHECK(".c select clear");
     ".c" << select(from, "item", 5);
     CHECK(".c select from item 5");
     ".c" << select(item);
     CHECK(".c select item");
     ".c" << select(to, "item", 5);
     CHECK(".c select to item 5");
     
     ".e" << selection(adjust, 5);
     CHECK(".e selection adjust 5");
     ".e" << selection(clear);
     CHECK(".e selection clear");
     ".e" << selection(from, 5);
     CHECK(".e selection from 5");
     ".e" << selection(present);
     CHECK(".e selection present");
     ".e" << selection(range, 5, 8);
     CHECK(".e selection range 5 8");
     ".e" << selection(to, 5);
     CHECK(".e selection to 5");
     ".lb" << selection(anchor, 5);
     CHECK(".lb selection anchor 5");
     ".lb" << selection(clear, 5);
     CHECK(".lb selection clear 5");
     ".lb" << selection(clear, 5, 8);
     CHECK(".lb selection clear 5 8");
     ".lb" << selection(includes, 5);
     CHECK(".lb selection includes 5");
     ".lb" << selection(set, 5);
     CHECK(".lb selection set 5");
     ".lb" << selection(set, 5, 8);
     CHECK(".lb selection set 5 8");
     ".sp" << selection(element);
     CHECK(".sp selection element");
     ".sp" << selection(element, 5);
     CHECK(".sp selection element 5");
     ".sp" << selection(range, 5, 7);
     CHECK(".sp selection range 5 7");
     
     ".s" << set(150);
     CHECK(".s set 150");
     // FIXME Floating Point Imprecision
     // ".sb" << set(0.2, 0.4);
     // CHECK(".sb set 0.2 0.4");
     ".sp" << set();
     CHECK(".sp set");
     
     ".t" << tag(add, "mytag", txt(5,6));
     CHECK(".t tag add mytag 5.6");
     ".t" << tag(add, "mytag", txt(5,6), txt(5,end));
     CHECK(".t tag add mytag 5.6 5.end");
     ".t" << tag(add, "mytag", txt(5,6), end);
     CHECK(".t tag add mytag 5.6 end");
     ".t" << tag(bind, "mytag", "<Button-1>");
     CHECK(".t tag bind mytag <Button-1>");
     ".t" << tag(bind, "mytag", "<Button-1>", cb0);
     CHECK(".t tag bind mytag <Button-1> { CppTk::callback6 }");
     ".t" << tag(bind, "mytag", "<Button-1>", cb1, event_x);
     CHECK(".t tag bind mytag <Button-1> { CppTk::callback7 %x }");
     ".t" << tag(bind, "mytag", "<Button-1>", cb2, event_A, event_b, event_D,
          event_f, event_h, event_k, event_K, event_m, event_N);
     CHECK(".t tag bind mytag <Button-1> { CppTk::callback8 %A %b %D %f %h"
          " %k %K %m %N }");
     ".t" << tag(bind, "mytag", "<Button-1>", cb3, event_s, event_T, event_w,
          event_W, event_x, event_y, event_X, event_Y);
     CHECK(".t tag bind mytag <Button-1> { CppTk::callback9 %s %T %w %W %x"
          " %y %X %Y }");
     ".t" << tag(cget, "mytag", background);
     CHECK(".t tag cget mytag -background");
     ".t" << tag(cget, "mytag", bgstipple);
     CHECK(".t tag cget mytag -bgstipple");
     ".t" << tag(cget, "mytag", borderwidth);
     CHECK(".t tag cget mytag -borderwidth");
     ".t" << tag(cget, "mytag", elide);
     CHECK(".t tag cget mytag -elide");
     ".t" << tag(cget, "mytag", fgstipple);
     CHECK(".t tag cget mytag -fgstipple");
     ".t" << tag(cget, "mytag", font);
     CHECK(".t tag cget mytag -font");
     ".t" << tag(cget, "mytag", foreground);
     CHECK(".t tag cget mytag -foreground");
     ".t" << tag(cget, "mytag", justify);
     CHECK(".t tag cget mytag -justify");
     ".t" << tag(cget, "mytag", lmargin1);
     CHECK(".t tag cget mytag -lmargin1");
     ".t" << tag(cget, "mytag", lmargin2);
     CHECK(".t tag cget mytag -lmargin2");
     ".t" << tag(cget, "mytag", offset);
     CHECK(".t tag cget mytag -offset");
     ".t" << tag(cget, "mytag", overstrike);
     CHECK(".t tag cget mytag -overstrike");
     ".t" << tag(cget, "mytag", relief);
     CHECK(".t tag cget mytag -relief");
     ".t" << tag(cget, "mytag", rmargin);
     CHECK(".t tag cget mytag -rmargin");
     ".t" << tag(cget, "mytag", spacing1);
     CHECK(".t tag cget mytag -spacing1");
     ".t" << tag(cget, "mytag", spacing2);
     CHECK(".t tag cget mytag -spacing2");
     ".t" << tag(cget, "mytag", spacing3);
     CHECK(".t tag cget mytag -spacing3");
     ".t" << tag(cget, "mytag", tabs);
     CHECK(".t tag cget mytag -tabs");
     ".t" << tag(cget, "mytag", underline);
     CHECK(".t tag cget mytag -underline");
     ".t" << tag(cget, "mytag", wrap);
     CHECK(".t tag cget mytag -wrap");
     ".t" << tag(configure, "mytag") -foreground("blue");
     CHECK(".t tag configure mytag -foreground blue");
     ".t" << tag(deletetag, "mytag");
     CHECK(".t tag delete mytag");
     ".t" << tag(lower, "mytag");
     CHECK(".t tag lower mytag");
     ".t" << tag(lower, "mytag", "belowthis");
     CHECK(".t tag lower mytag belowthis");
     ".t" << tag(names);
     CHECK(".t tag names");
     ".t" << tag(names, txt(5,6));
     CHECK(".t tag names 5.6");
     ".t" << tag(nextrange, "mytag", txt(5,6));
     CHECK(".t tag nextrange mytag 5.6");
     ".t" << tag(nextrange, "mytag", txt(5,6), txt(5,end));
     CHECK(".t tag nextrange mytag 5.6 5.end");
     ".t" << tag(prevrange, "mytag", txt(5,6));
     CHECK(".t tag prevrange mytag 5.6");
     ".t" << tag(prevrange, "mytag", txt(5,6), txt(5,end));
     CHECK(".t tag prevrange mytag 5.6 5.end");
     ".t" << tag(raise, "mytag");
     CHECK(".t tag raise mytag");
     ".t" << tag(raise, "mytag", "belowthis");
     CHECK(".t tag raise mytag belowthis");
     ".t" << tag(ranges, "mytag");
     CHECK(".t tag ranges mytag");
     ".t" << tag(Tk::remove, "mytag", txt(5,6));
     CHECK(".t tag remove mytag 5.6");
     ".t" << tag(Tk::remove, "mytag", txt(5,6), txt(5,end));
     CHECK(".t tag remove mytag 5.6 5.end");
     
     ".cb" << toggle();
     CHECK(".cb toggle");
     
     "photo1" << transparency(get, 10, 20);
     CHECK("photo1 transparency get 10 20");
     "photo1" << transparency(set, 10, 20, true);
     CHECK("photo1 transparency set 10 20 1");
     
     ".c" << type("item");
     CHECK(".c type item");
     ".m" << type(5);
     CHECK(".m type 5");
     
     ".e" << validate();
     CHECK(".e validate");
     
     ".t" << windows(cget, txt(5,6), align);
     CHECK(".t window cget 5.6 align");
     ".t" << windows(configure, txt(5,6)) -align(center);
     CHECK(".t window configure 5.6 -align center");
     ".t" << windows(create, txt(5,6));
     CHECK(".t window create 5.6");
     ".t" << windows(names);
     CHECK(".t window names");
     
     "photo1" << write("photo.gif") -grayscale();
     CHECK("photo1 write \"photo.gif\" -grayscale");
     
     std::pair<double, double>(".c" << xview());
     CHECK(".c xview");
     ".e" << xview(5);
     CHECK(".e xview 5");
     ".c" << xview(moveto, 0.5);
     CHECK(".c xview moveto 0.5");
     ".c" << xview(scroll, 5, units);
     CHECK(".c xview scroll 5 units");
     ".c" << xview(scroll, 5, pages);
     CHECK(".c xview scroll 5 pages");
     
     ".m" << yposition(5);
     CHECK(".m yposition 5");

     std::pair<double, double>(".c" << yview());
     CHECK(".c yview");
     ".c" << yview(moveto, 0.5);
     CHECK(".c yview moveto 0.5");
     ".c" << yview(scroll, 5, units);
     CHECK(".c yview scroll 5 units");
     ".c" << yview(scroll, 5, pages);
     CHECK(".c yview scroll 5 pages");
     

     std::cout << "widget commands test OK\n";
}

void optionsTest()
{
     button(".b") -activebackground("blue") -activeforeground("red");
     CHECK("button .b -activebackground blue -activeforeground red");

     ".c" << itemconfigure("item") -dash("-.-") -activedash("-.")
          -disableddash(".-.");
     CHECK(".c itemconfigure item -dash \"-.-\" -activedash \"-.\""
          " -disableddash \".-.\"");
     
     button(".b") -anchor(w) -background("blue");
     CHECK("button .b -anchor w -background blue");
     
     ".c" << create(line, 10, 20, 30, 40) -arrow(both)
          -arrowshape(10, 20, 30);
     CHECK(".c create line 10 20 30 40 -arrow both -arrowshape {10 20 30}");

     button(".b") -bitmap(warning) -borderwidth(10) -bg(20);
     CHECK("button .b -bitmap warning -borderwidth 10 -bg 20");
     ".c" << create(bitmap, 10, 20) -bitmap("bmp") -activebitmap("bmp")
          -disabledbitmap("bmp");
     CHECK(".c create bitmap 10 20 -bitmap bmp -activebitmap bmp"
          " -disabledbitmap bmp");

     ".c" << create(line, 10, 20, 30, 40) -capstyle(projecting);
     CHECK(".c create line 10 20 30 40 -capstyle projecting");
     
     canvas(".c") -closeenough(1.5);
     CHECK("canvas .c -closeenough 1.5");

     button(".b") -command(cb0);
     CHECK("button .b -command CppTk::callback10");
     CallbackHandle cmd(callback(cb0));
     button(".b") -command(cmd);
     CHECK("button .b -command { CppTk::callback11 }");

     button(".b") -compound(left);
     CHECK("button .b -compound left");
     
     canvas(".c") -confine(true);
     CHECK("canvas .c -confine 1");

     button(".b") -cursor("abc") -disabledforeground("blue");
     CHECK("button .b -cursor abc -disabledforeground blue");

     ".c" << itemconfigure("item") -dashoffset(5);
     CHECK(".c itemconfigure item -dashoffset 5");
     
     button(".b") -defaultstate(active);
     CHECK("button .b -default active");

     ".e" << configure() -exportselection(true);
     CHECK(".e configure -exportselection 1");
     
     ".c" << create(arc, 10, 20, 30, 40) -start(180) -extent(90)
          -style(pieslice);
     CHECK(".c create arc 10 20 30 40 -start 180 -extent 90 -style pieslice");

     ".c" << itemconfigure("item") -fill("red") -activefill("red")
          -disabledfill("red");
     CHECK(".c itemconfigure item -fill red -activefill red"
          " -disabledfill red");
     
     button(".b") -font("courier") -foreground("blue") -fg("red");
     CHECK("button .b -font courier -foreground blue -fg red");

     button(".b") -height(10);
     CHECK("button .b -height 10");

     button(".b") -highlightbackground("blue") -highlightcolor("red");
     CHECK("button .b -highlightbackground blue -highlightcolor red");

     button(".b") -highlightthickness(10) -image("abc");
     CHECK("button .b -highlightthickness 10 -image abc");

     ".c" << create(image, 10, 20) -image("img") -activeimage("img")
          -disabledimage("img");
     CHECK(".c create image 10 20 -image img -activeimage img"
          " -disabledimage img");

     checkbutton(".cb") -indicatoron(false) -offrelief(raised);
     CHECK("checkbutton .cb -indicatoron 0 -offrelief raised");
     
     canvas(".c") -insertbackground("blue") -insertborderwidth(3);
     CHECK("canvas .c -insertbackground blue -insertborderwidth 3");

     canvas(".c") -insertofftime(100) -insertontime(150) -insertwidth(2);
     CHECK("canvas .c -insertofftime 100 -insertontime 150 -insertwidth 2");

     ".e" << configure() -invalidcommand(cb0);
     CHECK(".e configure -invalidcommand CppTk::callback12");
     ".e" << configure() -invalidcommand("bell");
     CHECK(".e configure -invalidcommand { bell }");
     
     ".c" << create(line, 10, 20, 30, 40) -joinstyle(bevel);
     CHECK(".c create line 10 20 30 40 -joinstyle bevel");
     
     button(".b") -justify(left) -padx(10) -pady(15);
     CHECK("button .b -justify left -padx 10 -pady 15");

     ".c" << itemconfigure("item") -offset(n);
     CHECK(".c itemconfigure item -offset n");
     
     ".cb" << configure() -offrelief(raised) -offvalue(0) -onvalue(7)
          -selectcolor("blue");
     CHECK(".cb configure -offrelief raised -offvalue 0 -onvalue 7"
          " -selectcolor blue");
     
     ".c" << itemconfigure("item") -outline("red") -activeoutline("red")
          -disabledoutline("red");
     CHECK(".c itemconfigure item -outline red -activeoutline red"
          " -disabledoutline red");

     ".c" << itemconfigure("item") -outlinestipple("bmp")
          -activeoutlinestipple("bmp") -disabledoutlinestipple("bmp");
     CHECK(".c itemconfigure item -outlinestipple bmp"
          " -activeoutlinestipple bmp -disabledoutlinestipple bmp");

     menu(".m") -menutype(menubar) -menutype(tearoff) -menutype(normal);
     CHECK("menu .m -type menubar -type tearoff -type normal");
     
     button(".b") -overrelief(raised);
     CHECK("button .b -overrelief raised");
     
     ".e" << configure() -readonlybackground("blue");
     CHECK(".e configure -readonlybackground blue");

     button(".b") -relief(ridge) -repeatdelay(100) -repeatinterval(150);
     CHECK("button .b -relief ridge -repeatdelay 100 -repeatinterval 150");

     canvas(".c") -scrollregion(10, 20, 30, 40);
     CHECK("canvas .c -scrollregion 10 20 30 40");

     canvas(".c") -selectbackground("blue") -selectborderwidth(3)
          -selectforeground("red");
     CHECK("canvas .c -selectbackground blue -selectborderwidth 3"
          " -selectforeground red");
     
     ".cb" << configure() -selectcolor("blue") -selectimage("img");
     CHECK(".cb configure -selectcolor blue -selectimage img");
     
     ".e" << configure() -show("*");
     CHECK(".e configure -show \"*\"");

     ".c" << create(line, 10, 20, 30, 40) -smooth(bezier) -splinesteps(30);
     CHECK(".c create line 10 20 30 40 -smooth bezier -splinesteps 30");
     ".c" << create(line, 10, 20, 30, 40) -smooth(true);
     CHECK(".c create line 10 20 30 40 -smooth 1");
     
     button(".b") -state(disabled);
     CHECK("button .b -state disabled");

     ".c" << itemconfigure("item") -stipple("bmp") -activestipple("bmp")
          -disabledstipple("bmp");
     CHECK(".c itemconfigure item -stipple bmp -activestipple bmp"
          " -disabledstipple bmp");
     
     std::vector<std::string> sometags;
     sometags.push_back("tag1");
     sometags.push_back("tag2");
     sometags.push_back("tag3");
     ".c" << itemconfigure("item") -tags(sometags.begin(), sometags.end());
     CHECK(".c itemconfigure item -tags { tag1 tag2 tag3}");

     button(".b") -takefocus(1) -text("Hello");
     CHECK("button .b -takefocus 1 -text \"Hello\"");

     int i;
     double d;
     std::string s;
     button(".b") -textvariable(i);
     CHECK("button .b -textvariable CppTk::variable2");
     button(".b") -textvariable(d);
     CHECK("button .b -textvariable CppTk::variable3");
     button(".b") -textvariable(s);
     CHECK("button .b -textvariable CppTk::variable4");

     checkbutton(".cb") -variable(i);
     CHECK("checkbutton .cb -variable CppTk::variable5");
     
     button(".b") -underline(3) -wraplength(100);
     CHECK("button .b -underline 3 -wraplength 100");
     
     ".e" << configure() -validate(focus) -validatecommand(cbb0, valid_P);
     CHECK(".e configure -validate focus -validatecommand "
          "{ CppTk::callback13 %P }");
     
     button(".b") -width(10);
     CHECK("button .b -width 10");
     ".c" << itemconfigure("item") -width(2) -activewidth(2)
          -disabledwidth(2);
     CHECK(".c itemconfigure item -width 2 -activewidth 2 -disabledwidth 2");
     
     ".c" << create(window, 10, 20) -window(".e");
     CHECK(".c create window 10 20 -window .e");

     canvas(".c") -xscrollcommand("xcmd") -yscrollcommand("ycmd");
     CHECK("canvas .c -xscrollcommand \"xcmd\" -yscrollcommand \"ycmd\"");

     canvas(".c") -xscrollincrement(10) -yscrollincrement(20);
     CHECK("canvas .c -xscrollincrement 10 -yscrollincrement 20");


     std::cout << "options test OK\n";
}

void additionalTclTest()
{
     after(500);
     CHECK("after 500");
     after(500, cb0);
     CHECK("after 500 CppTk::callback14");
     after(500, std::string("bell"));
     CHECK("after 500 bell");
     after(cancel, std::string("someid"));
     CHECK("after cancel someid");
     afteridle(cb0);
     CHECK("after idle CppTk::callback15");
     
     update();
     CHECK("update");
     update(idletasks);
     CHECK("update idletasks");
     
     eval("some explicit Tcl/Tk command");
     CHECK("some explicit Tcl/Tk command");


     std::cout << "additional Tcl test OK\n";
}

int main(int, char *argv[])
{
     try
     {
          init(argv[0]);
          setDumpStream(ss);

          commandsTest();
          widgetCommandsTest();
          optionsTest();
          additionalTclTest();
     }
     catch (std::exception const &e)
     {
          std::cerr << "Error: " << e.what() << '\n';
     }
}
