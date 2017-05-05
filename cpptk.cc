//
// Copyright (C) 2004-2006, Maciej Sobczak
// Copyright 2017 Declan Hoare
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//

#include "cpptk.h"
#include <iomanip>

using namespace Tk;
using namespace Tk::details;

// various Tk bits and pieces

// starter pieces (genuine Tk commands)

Expr Tk::bell() { return Expr("bell"); }

Expr Tk::bindtags(std::string const &name, std::string const &tags)
{
     std::string str("bindtags ");
     str += name;
     if (tags.empty())
     {
          return Expr(str);
     }
     else
     {
          str += " { ";  str += tags;   str += " }";
          return Expr(str);
     }
}

Expr Tk::button(std::string const &name)
{
     std::string str("button ");
     str += name;
     return Expr(str);
}

Expr Tk::canvas(std::string const &name)
{
     std::string str("canvas ");
     str += name;
     return Expr(str);
}

Expr Tk::clipboard(std::string const &option)
{
     std::string str("clipboard ");
     str += option;
     return Expr(str);
}

Expr Tk::clipboard(std::string const &option, std::string const &data)
{
     std::string str("clipboard ");
     str += option;
     std::string postfix(" -- \"");
     postfix += quote(data);
     postfix += "\"";
     return Expr(str, postfix);
}

Expr Tk::destroy(std::string const &name)
{
     std::string str("destroy ");
     str += name;
     return Expr(str);
}

Expr Tk::entry(std::string const &name)
{
     std::string str("entry ");
     str += name;
     return Expr(str);
}

Expr Tk::fonts(std::string const &option, std::string const &name)
{
     std::string str("font ");
     str += option;
     if (name.empty())
     {
          return Expr(str);
     }
     else
     {
          str += " ";
          str += name;
          return Expr(str);
     }
}

Expr Tk::grab(std::string const &option, std::string const &name)
{
     std::string str("grab ");
     str += option;
     if (name.empty())
     {
          return Expr(str);
     }
     else
     {
          str += " ";
          str += name;
          return Expr(str);
     }
}

Expr Tk::images(std::string const &option, std::string const &tn, std::string const &name)
{
     std::string str("image ");
     str += option;
     if (tn.empty())
     {
          return Expr(str);
     }
     str += " "; str += tn;
     if (name.empty())
     {
          return Expr(str);
     }
     str += " ";
     if (option == "cget")
     {
          str += '-';
     }
     str += name;
     return Expr(str);
}

Expr Tk::label(std::string const &name)
{
     std::string str("label ");
     str += name;
     return Expr(str);
}

Expr Tk::labelframe(std::string const &name)
{
     std::string str("labelframe ");
     str += name;
     return Expr(str);
}

Expr Tk::listbox(std::string const &name)
{
     std::string str("listbox ");
     str += name;
     return Expr(str);
}

Expr Tk::menu(std::string const &name)
{
     std::string str("menu ");
     str += name;
     return Expr(str);
}

Expr Tk::menubutton(std::string const &name)
{
     std::string str("menubutton ");
     str += name;
     return Expr(str);
}

Expr Tk::message(std::string const &name)
{
     std::string str("message ");
     str += name;
     return Expr(str);
}

Expr Tk::option(std::string const &todo, std::string const &s1,
     std::string const &s2, std::string const &s3)
{
     std::string str("option ");
     str += todo;
     if (s1.empty())
     {
          return Expr(str);
     }
     str += " \""; str += s1; str += '\"';
     if (s2.empty())
     {
          return Expr(str);
     }
     str += " \""; str += s2; str += '\"';
     if (s3.empty())
     {
          return Expr(str);
     }
     str += " "; str += s3;
     return Expr(str);
}

Expr Tk::pack(std::string const &w1,
     std::string const &w2,
     std::string const &w3,
     std::string const &w4,
     std::string const &w5,
     std::string const &w6,
     std::string const &w7,
     std::string const &w8,
     std::string const &w9,
     std::string const &w10)
{
     std::string str("pack ");
     str += w1;
     if (!w2.empty()) { str += " "; str += w2; }
     if (!w3.empty()) { str += " "; str += w3; }
     if (!w4.empty()) { str += " "; str += w4; }
     if (!w5.empty()) { str += " "; str += w5; }
     if (!w6.empty()) { str += " "; str += w6; }
     if (!w7.empty()) { str += " "; str += w7; }
     if (!w8.empty()) { str += " "; str += w8; }
     if (!w9.empty()) { str += " "; str += w9; }
     if (!w10.empty()) { str += " "; str += w10; }
     
     return Expr(str);
}

Expr Tk::panedwindow(std::string const &name)
{
     std::string str("panedwindow ");
     str += name;
     return Expr(str);
}

Expr Tk::scale(std::string const &name)
{
     std::string str("scale ");
     str += name;
     return Expr(str);
}

Expr Tk::scrollbar(std::string const &name)
{
     std::string str("scrollbar ");
     str += name;
     return Expr(str);
}

Expr Tk::spinbox(std::string const &name)
{
     std::string str("spinbox ");
     str += name;
     return Expr(str);
}

Expr Tk::textw(std::string const &name)
{
     std::string str("text ");
     str += name;
     return Expr(str);
}

Expr Tk::tk_chooseColor()
{
     return Expr("tk_chooseColor");
}

Expr Tk::tk_chooseDirectory()
{
     return Expr("tk_chooseDirectory");
}

Expr Tk::tk_dialog(std::string const &window, std::string const &title,
     std::string const &text, std::string const &bitmap, std::string const &def,
     std::string const &but1, std::string const &but2, std::string const &but3,
     std::string const &but4)
{
     std::string str("tk_dialog ");
     str += window; str += " \"";
     str += title; str += "\" \"";
     str += quote(text); str += "\" ";
     str += bitmap; str += " \"";
     str += def; str += "\" \"";
     str += but1; str += "\"";
     if (but2.empty())
     {
          return Expr(str);
     }
     str += " \"";
     str += but2; str += "\"";
     if (but3.empty())
     {
          return Expr(str);
     }
     str += " \"";
     str += but3; str += "\"";
     if (but4.empty())
     {
          return Expr(str);
     }
     str += " \"";
     str += but4; str += "\"";
     return Expr(str);
}

Expr Tk::tk_focusNext(std::string const &window)
{
     std::string str("tk_focusNext ");
     str += window;
     return Expr(str);
}

Expr Tk::tk_focusPrev(std::string const &window)
{
     std::string str("tk_focusPrev ");
     str += window;
     return Expr(str);
}

Expr Tk::tk_getOpenFile()
{
     return Expr("tk_getOpenFile");
}

Expr Tk::tk_getSaveFile()
{
     return Expr("tk_getSaveFile");
}

Expr Tk::tk_menuSetFocus(std::string const &menu)
{
     std::string str("tk_menuSetFocus ");
     str += menu;
     return Expr(str);
}

Expr Tk::tk_messageBox()
{
     return Expr("tk_messageBox");
}

Expr Tk::tk_setPalette(std::string const &color)
{
     std::string str("tk_setPalette ");
     str += color;
     return Expr(str);
}

Expr Tk::tk_textCopy(std::string const &w)
{
     std::string str("tk_textCopy ");
     str += w;
     return Expr(str);
}

Expr Tk::tk_textCut(std::string const &w)
{
     std::string str("tk_textCut ");
     str += w;
     return Expr(str);
}

Expr Tk::tk_textPaste(std::string const &w)
{
     std::string str("tk_textPaste ");
     str += w;
     return Expr(str);
}

Expr Tk::tkwait(std::string const &option, std::string const &w)
{
     std::string str("tkwait ");
     str += option; str += " ";
     str += w;
     return Expr(str);
}

Expr Tk::winfo(std::string const &option, std::string const &w)
{
     std::string str("winfo ");
     str += option;
     std::string postfix(" ");
     postfix += w;
     return Expr(str, postfix);
}

Expr Tk::wm(std::string const &option, std::string const &w)
{
     std::string str("wm ");
     str += option; str += " ";
     str += w;
     return Expr(str);
}

Expr Tk::wmprotocol(std::string const &w, std::string const &proto)
{
     std::string str("wm protocol ");
     str += w;
     if (proto.empty())
     {
          return Expr(str);
     }
     str += " ";
     str += proto;
     return Expr(str);
}

// widget commands

Expr Tk::addtag(std::string const &tag, std::string const &spec)
{
     std::string str("addtag ");
     str += tag;    str += " ";
     str += spec;
     return Expr(str);
}

Expr Tk::blank()
{
     return Expr("blank");
}

Expr Tk::clone(std::string const &newpath, std::string const &type)
{
     std::string str("clone ");
     str += newpath;
     if (type.empty())
     {
          return Expr(str);
     }
     str += " ";    str += type;
     return Expr(str);
}

Expr Tk::compare(std::string const &indx1, std::string const &oper, std::string const &indx2)
{
     std::string str("compare ");
     str += indx1; str += " ";
     str += oper; str += " ";
     str += indx2;
     return Expr(str);
}

Expr Tk::coords()
{
     return Expr("coords");
}

Expr Tk::coords(std::string const &item, int x, int y)
{
     std::string str("coords ");
     str += item;   str += " ";
     str += toString(x); str += " ";
     str += toString(y);
     return Expr(str);
}

Expr Tk::coords(std::string const &item, Point const &p)
{
     return coords(item, p.x, p.y);
}

Expr Tk::coords(std::string const &item, int x1, int y1, int x2, int y2)
{
     std::string str("coords ");
     str += item;   str += " ";
     str += toString(x1);     str += " ";
     str += toString(y1);     str += " ";
     str += toString(x2);     str += " ";
     str += toString(y2);
     return Expr(str);
}

Expr Tk::coords(std::string const &item, Point const &p1, Point const &p2)
{
     return coords(item, p1.x, p1.y, p2.x, p2.y);
}

Expr Tk::coords(std::string const &item, Box const &b)
{
     return coords(item, b.x1, b.y1, b.x2, b.y2);
}

Expr Tk::copy(std::string const &photo)
{
     std::string str("copy ");
     str += photo;
     return Expr(str);
}

Expr Tk::curselection()
{
     return Expr("curselection");
}

Expr Tk::debug()
{
     return Expr("debug");
}

Expr Tk::debug(bool d)
{
     std::string str("debug ");
     str += toString(d);
     return Expr(str);
}

Expr Tk::deselect()
{
     return Expr("deselect");
}

Expr Tk::dlineinfo(std::string const &indx)
{
     std::string str("dlineinfo ");
     str += indx;
     return Expr(str);
}

Expr Tk::dtag(std::string const &tag, std::string const &todel)
{
     std::string str("dtag ");
     str += tag;
     if (todel.empty())
     {
          return Expr(str);
     }
     else
     {
          str += " ";    str += todel;
          return Expr(str);
     }
}

Expr Tk::dump(std::string const &indx1, std::string const &indx2)
{
     std::string str("dump");
     std::string postfix(" ");
     postfix += indx1;
     if (indx2.empty() == false)
     {
          postfix += " ";
          postfix += indx2;
     }
     return Expr("dump", postfix);
}

Expr Tk::edit(std::string const &option)
{
     std::string str("edit ");
     str += option;
     return Expr(str);
}

Expr Tk::find(std::string const &spec)
{
     std::string str("find ");
     str += spec;
     return Expr(str);
}

Expr Tk::flash()
{
     return Expr("flash");
}

Expr Tk::getsize()
{
     return Expr("size");
}

Expr Tk::gettags(std::string const &item)
{
     std::string str("gettags ");
     str += item;
     return Expr(str);
}

Expr Tk::insert(std::string const &indx, std::string const &txt, std::string const &tag)
{
     std::string str("insert ");
     str += indx; str += " \"";
     str += quote(txt); str += "\"";
     if (tag.empty())
     {
          return Expr(str);
     }
     str += " ";
     str += tag;
     return Expr(str);
}

Expr Tk::invoke()
{
     return Expr("invoke");
}

Expr Tk::move(std::string const &item, int x, int y)
{
     std::string str("move ");
     str += item;   str += " ";
     str += toString(x); str += " ";
     str += toString(y);
     return Expr(str);
}

Expr Tk::panecget(std::string const &w, std::string const &option)
{
     std::string str("panecget ");
     str += w; str += " -";
     str += option;
     return Expr(str);
}

Expr Tk::paneconfigure(std::string const &w)
{
     std::string str("paneconfigure ");
     str += w;
     return Expr(str);
}

Expr Tk::panes()
{
     return Expr("panes");
}

Expr Tk::postscript()
{
     return Expr("postscript");
}

Expr Tk::proxy(std::string const &option)
{
     std::string str("proxy ");
     str += option;
     return Expr(str);
}

Expr Tk::put(std::string const &color)
{
     std::string str("put ");
     str += color;
     return Expr(str);
}

Expr Tk::read(std::string const &file)
{
     std::string str("read \"");
     str += file; str += '\"';
     return Expr(str);
}

Expr Tk::redither()
{
     return Expr("redither");
}

Expr Tk::sash(std::string const &option, int index)
{
     std::string str("sash ");
     str += option; str += " ";
     str += toString(index);
     return Expr(str);
}

Expr Tk::search(std::string const &pattern,
     std::string const &indx1, std::string const &indx2)
{
     std::string str("search \"");
     str += quote(pattern); str += '\"';
     std::string postfix(" -- ");
     postfix += indx1;
     if (indx2.empty())
     {
          return Expr(str, postfix);
     }
     postfix += " ";
     postfix += indx2;
     return Expr(str, postfix);
}

Expr Tk::select()
{
     return Expr("select");
}

Expr Tk::select(std::string const &option)
{
     std::string str("select ");
     str += option;
     return Expr(str);
}

Expr Tk::selection(std::string const &option)
{
     std::string str("selection ");
     str += option;
     return Expr(str);
}

Expr Tk::tag(std::string const &option, std::string const &tagname)
{
     std::string str("tag ");
     str += option;
     if (tagname.empty())
     {
          return Expr(str);
     }
     str += " ";
     str += tagname;
     return Expr(str);
}

Expr Tk::tag(std::string const &option, std::string const &tagname,
     std::string const &indx1, std::string const &indx2)
{
     std::string str("tag ");
     str += option; str += " ";
     str += tagname; str += " ";
     if (option == "cget")
     {
          str += '-';
          str += indx1;
          return Expr(str);
     }
     str += indx1;
     if (indx2.empty())
     {
          return Expr(str);
     }
     str += " ";
     str += indx2;
     return Expr(str);
}

Expr Tk::tag(std::string const &option, std::string const &tagname,
     std::string const &indx1, char const *indx2)
{
     return Tk::tag(option, tagname, indx1, std::string(indx2));
}

Expr Tk::toggle()
{
     return Expr("toggle");
}

Expr Tk::transparency(std::string const &option, int x, int y)
{
     std::string str("transparency ");
     str += option; str += " ";
     str += toString(x); str += " ";
     str += toString(y);
     return Expr(str);
}

Expr Tk::transparency(std::string const &option, int x, int y, bool tr)
{
     std::string str("transparency ");
     str += option; str += " ";
     str += toString(x); str += " ";
     str += toString(y); str += " ";
     str += toString(tr);
     return Expr(str);
}

Expr Tk::windows(std::string const &option, std::string const &indx, std::string const &name)
{
     std::string str("window ");
     str += option;
     if (indx.empty())
     {
          return Expr(str);
     }
     str += " ";
     str += indx;
     if (name.empty())
     {
          return Expr(str);
     }
     str += " ";
     str += name;
     return Expr(str);
}

Expr Tk::write(std::string const &file)
{
     std::string str("write \"");
     str += file; str += '\"';
     return Expr(str);
}

Expr Tk::xview()
{
     return Expr("xview");
}

Expr Tk::xview(std::string const &option, double fraction)
{
     std::string str("xview ");
     str += option; str += " ";
     str += toString(fraction);
     return Expr(str);
}

Expr Tk::xview(std::string const option, int number, std::string const &what)
{
     std::string str("xview ");
     str += option; str += " ";
     str += toString(number); str += " ";
     str += what;
     return Expr(str);
}

Expr Tk::yview()
{
     return Expr("yview");
}

Expr Tk::yview(std::string const &option, double fraction)
{
     std::string str("yview ");
     str += option; str += " ";
     str += toString(fraction);
     return Expr(str);
}

Expr Tk::yview(std::string const option, int number, std::string const &what)
{
     std::string str("yview ");
     str += option; str += " ";
     str += toString(number); str += " ";
     str += what;
     return Expr(str);
}

// options

#define CPPTK_OPTION(name, quote) Option Tk::name(#name, quote);
#include "cpptkoptions.x"
#undef CPPTK_OPTION

// other options, requiring special syntax or compilation

Expr Tk::backwards()
{
     return Expr(" -backwards", false);
}

Expr Tk::cliptype(std::string const &type)
{
     std::string str(" -type ");
     str += type;
     return Expr(str, false);
}

Expr Tk::count(int &i)
{
     std::string str(" -count ");
     str += details::addLinkVar(i);
     return details::Expr(str, false);
}

Expr Tk::count(std::string const &name)
{
     std::string str(" -count ");
     str += name;
     return Expr(str, false);
}

Expr Tk::defaultbutton(std::string const &but)
{
     std::string str(" -default \"");
     str += but; str += '\"';
     return Expr(str, false);
}

Expr Tk::defaultstate(std::string const &name)
{
     std::string str(" -default ");
     str += name;
     return Expr(str, false);
}

Expr Tk::exact()
{
     return Expr(" -exact", false);
}

Expr Tk::filetypes(std::string const &types)
{
     std::string str(" -filetypes {");
     str += types;
     str += "}";
     return Expr(str, false);
}

Expr Tk::forwards()
{
     return Expr(" -forwards", false);
}

Expr Tk::grayscale()
{
     return Expr(" -grayscale", false);
}

Expr Tk::invalidcommand(char const *name)
{
     std::string str(" -invalidcommand { ");
     str += name; str += " }";
     return Expr(str, false);
}

Expr Tk::invalidcommand(std::string const &name)
{
     std::string str(" -invalidcommand { ");
     str += name; str += " }";
     return Expr(str, false);
}

Expr Tk::invalidcommand(CallbackHandle const &handle)
{
     std::string str(" -invalidcommand { ");
     str += handle.get(); str += " }";
     return Expr(str, false);
}

Expr Tk::menutype(std::string const &type)
{
     std::string str(" -type ");
     str += type;
     return Expr(str, false);
}

Expr Tk::messagetext(std::string const &txt)
{
     std::string str(" -message \"");
     str += txt; str += '\"';
     return Expr(str, false);
}

Expr Tk::messagetype(std::string const &type)
{
     std::string str(" -type ");
     str += type;
     return Expr(str, false);
}

Expr Tk::multiple()
{
     return Expr(" -multiple", false);
}

Expr Tk::nocase()
{
     return Expr(" -nocase", false);
}

Expr Tk::postcommand(std::string const &name)
{
     std::string str(" -postcommand { ");
     str += name; str += " }";
     return Expr(str, false);
}

Expr Tk::postcommand(CallbackHandle const &handle)
{
     std::string str(" -postcommand { ");
     str += handle.get(); str += " }";
     return Expr(str, false);
}

Expr Tk::regexp()
{
     return Expr(" -regexp", false);
}

Expr Tk::shrink()
{
     return Expr(" -shrink", false);
}

Expr Tk::submenu(std::string const &menu)
{
     std::string str(" -menu ");
     str += menu;
     return Expr(str, false);
}

Expr Tk::subsample(int x, int y)
{
     std::string str(" -subsample ");
     str += toString(x); str += " ";
     str += toString(y);
     return Expr(str, false);
}

Expr Tk::tags()
{
     return Expr(" -tag", false);
}

Expr Tk::tearoffcommand(std::string const &name)
{
     std::string str(" -tearoffcommand { ");
     str += name; str += " }";
     return Expr(str, false);
}

Expr Tk::tearoffcommand(CallbackHandle const &handle)
{
     std::string str(" -tearoffcommand { ");
     str += handle.get(); str += " }";
     return Expr(str, false);
}

Expr Tk::textvariable(std::string const &name)
{
     std::string str(" -textvariable ");
     str += name;
     return Expr(str, false);
}

Expr Tk::variable(std::string const &name)
{
     std::string str(" -variable ");
     str += name;
     return Expr(str, false);
}

Expr Tk::zoom(double x, double y)
{
     std::string str(" -zoom ");
     str += toString(x); str += " ";
     str += toString(y);
     return Expr(str, false);
}

// event attribute specifiers

EventAttr<std::string> Tk::event_A("%A"); // %A - character
EventAttr<int>    Tk::event_b("%b"); // %b - button number
EventAttr<int>    Tk::event_D("%D"); // %D - delta for mouse wheel
EventAttr<int>    Tk::event_f("%f"); // %f - focus flag
EventAttr<int>    Tk::event_h("%h"); // %h - height
EventAttr<std::string> Tk::event_k("%k"); // %k - keycode
EventAttr<std::string> Tk::event_K("%K"); // %K - keysym
EventAttr<std::string> Tk::event_m("%m"); // %m - mode
EventAttr<int>    Tk::event_N("%N"); // %N - keysym, numeric value
EventAttr<std::string> Tk::event_s("%s"); // %s - state
EventAttr<std::string> Tk::event_T("%T"); // %T - type
EventAttr<int>    Tk::event_w("%w"); // %w - width
EventAttr<std::string> Tk::event_W("%W"); // %W - window name
EventAttr<int>    Tk::event_x("%x"); // %x - x coordinate
EventAttr<int>    Tk::event_X("%X"); // %X - root x coordinate
EventAttr<int>    Tk::event_y("%y"); // %x - y coordinate
EventAttr<int>    Tk::event_Y("%Y"); // %Y - root y coordinate

ValidateAttr<int>    Tk::valid_d("%d"); // %d - type of action
ValidateAttr<int>    Tk::valid_i("%i"); // %i - index of char
ValidateAttr<std::string> Tk::valid_P("%P"); // %P - new value
ValidateAttr<std::string> Tk::valid_s("%s"); // %s - current value
ValidateAttr<std::string> Tk::valid_S("%S"); // %S - diff
ValidateAttr<std::string> Tk::valid_v("%v"); // %v - current type of valid.
ValidateAttr<std::string> Tk::valid_V("%V"); // %V - type of trigger
ValidateAttr<std::string> Tk::valid_W("%W"); // %W - name of entry widget


// constants

#define CPPTK_CONSTANT(c) char const * Tk::c = #c;
#include "cpptkconstants.x"
#undef CPPTK_CONSTANT

// additional constants

char const * Tk::deletefont = "delete"; // instead of conflicting 'delete'
char const * Tk::deleteimg  = "delete"; // instead of conflicting 'delete'
char const * Tk::deletetag  = "delete"; // instead of conflicting 'delete'
char const * Tk::setglobal  = "set -global";
char const * Tk::wrapchar   = "char";   // instead of conflicting 'char'
char const * Tk::wrapword   = "word";   // for consistency

// additional functions

Expr Tk::afteridle(std::string const &cmd)
{
     std::string str("after idle { ");
     str += cmd; str += " }";
     return Expr(str);
}

Expr Tk::update(std::string const &option)
{
     std::string str("update");
     if (option.empty())
     {
          return Expr(str);
     }
     str += " ";
     str += option;
     return Expr(str);
}

// multipurpose tokens

Tk::details::BindToken::BindToken() : BasicToken("bind") {}

Expr Tk::details::BindToken::operator()(std::string const &name,
     std::string const &seq) const
{
     std::string str("bind ");
     str += name;   str += " ";
     str += seq;    str += " {}";
     return Expr(str);
}

BindToken Tk::bind;

Tk::details::CheckButtonToken::CheckButtonToken()
     : BasicToken("checkbutton") {}

Expr Tk::details::CheckButtonToken::operator()(std::string const &name) const
{
     std::string str("checkbutton ");
     str += name;
     return Expr(str);
}

CheckButtonToken Tk::checkbutton;

Tk::details::FrameToken::FrameToken() : BasicToken("frame") {}

Expr Tk::details::FrameToken::operator()(std::string const &name) const
{
     std::string str("frame ");
     str += name;
     return Expr(str);
}

FrameToken Tk::frame;

Tk::details::GridToken::GridToken() : BasicToken("grid") {}

Expr Tk::details::GridToken::operator()(std::string const &option,
     std::string const &name) const
{
     std::string str("grid ");
     str += option; str += " ";
     str += name;
     return Expr(str);
}

Expr Tk::details::GridToken::operator()(std::string const &option,
     std::string const &name, int x, int y) const
{
     std::string str("grid ");
     str += option; str += " ";
     str += name; str += " ";
     str += toString(x); str += " ";
     str += toString(y);
     return Expr(str);
}

Expr Tk::details::GridToken::operator()(std::string const &option,
     std::string const &name, int col1, int row1, int col2, int row2) const
{
     std::string str("grid ");
     str += option; str += " ";
     str += name; str += " ";
     str += toString(col1); str += " ";
     str += toString(row1); str += " ";
     str += toString(col2); str += " ";
     str += toString(row2);
     return Expr(str);
}

GridToken Tk::grid;

Tk::details::LowerToken::LowerToken() : BasicToken("lower") {}

Expr Tk::details::LowerToken::operator()(std::string const &name,
     std::string const &belowthis) const
{
     std::string str("lower ");
     str += name;
     if (belowthis.empty())
     {
          return Expr(str);
     }
     str += " "; str += belowthis;
     return Expr(str);    
}

LowerToken Tk::lower;

Tk::details::PlaceToken::PlaceToken() : BasicToken("place") {}

Expr Tk::details::PlaceToken::operator()(std::string const &w) const
{
     std::string str("place ");
     str += w;
     return Expr(str);
}

Expr Tk::details::PlaceToken::operator()(std::string const &option,
     std::string const &w) const
{
     std::string str("place ");
     str += option; str += " ";
     str += w;
     return Expr(str);
}

PlaceToken Tk::place;

Tk::details::RadioButtonToken::RadioButtonToken()
     : BasicToken("radiobutton") {}

Expr Tk::details::RadioButtonToken::operator()(std::string const &name) const
{
     std::string str("radiobutton ");
     str += name;
     return Expr(str);
}

RadioButtonToken Tk::radiobutton;

Tk::details::RaiseToken::RaiseToken() : BasicToken("raise") {}

Expr Tk::details::RaiseToken::operator()(std::string const &name,
     std::string const &abovethis) const
{
     std::string str("raise ");
     str += name;
     if (abovethis.empty())
     {
          return Expr(str);
     }
     str += " "; str += abovethis;
     return Expr(str);    
}

RaiseToken Tk::raise;

Tk::details::ToplevelToken::ToplevelToken() : BasicToken("toplevel") {}

Expr Tk::details::ToplevelToken::operator()(std::string const &w) const
{
     std::string str("toplevel ");
     str += w;
     return Expr(str);
}

ToplevelToken Tk::toplevel;

Tk::details::AddToken::AddToken() : BasicToken("add") {}

Expr Tk::details::AddToken::operator()(std::string const &tn) const
{
     std::string str("add ");
     str += tn;
     return Expr(str);
}

AddToken Tk::add;

Tk::details::BboxToken::BboxToken() : BasicToken("bbox") {}

BboxToken Tk::bbox;

Tk::details::CgetToken::CgetToken() : BasicToken("cget") {}

Expr Tk::details::CgetToken::operator()(std::string const &name) const
{
     std::string str("cget -");
     str += name;
     return Expr(str);
}

CgetToken Tk::cget;

Tk::details::ConfigureToken::ConfigureToken() : BasicToken("configure") {}

Expr Tk::details::ConfigureToken::operator()() const
{
     return Expr("configure");
}

ConfigureToken Tk::configure;

Tk::details::CreateToken::CreateToken() : BasicToken("create") {}

Expr Tk::details::CreateToken::operator()(std::string const &type,
     int x, int y) const
{
     std::string str("create ");
     str += type;   str += " ";
     str += toString(x); str += " ";
     str += toString(y);
     return Expr(str);
}

Expr Tk::details::CreateToken::operator()(std::string const &type,
     Point const &p) const
{
     return create(type, p.x, p.y);
}

Expr Tk::details::CreateToken::operator()(std::string const &type,
     int x1, int y1, int x2, int y2) const
{
     std::string str("create ");
     str += type;   str += " ";
     str += toString(x1); str += " ";
     str += toString(y1); str += " ";
     str += toString(x2); str += " ";
     str += toString(y2);
     return Expr(str);
}

Expr Tk::details::CreateToken::operator()(std::string const &type,
     Point const &p1, Point const &p2) const
{
     return create(type, p1.x, p1.y, p2.x, p2.y);
}

Expr Tk::details::CreateToken::operator()(std::string const &type,
     Box const &b) const
{
     return create(type, b.x1, b.y1, b.x2, b.y2);
}

CreateToken Tk::create;

Tk::details::FocusToken::FocusToken() : BasicToken("focus") {}

Expr Tk::details::FocusToken::operator()(std::string const &name) const
{
     std::string str("focus");
     if (name.empty())
     {
          return Expr(str);
     }
     else
     {
          str += " ";    str += name;
          return Expr(str);
     }
}

FocusToken Tk::focus;

Tk::details::ForgetToken::ForgetToken() : BasicToken("forget") {}

Expr Tk::details::ForgetToken::operator()(std::string const &name) const
{
     std::string str("forget ");
     str += name;
     return Expr(str);
}

ForgetToken Tk::forget;

Tk::details::GetToken::GetToken() : BasicToken("get") {}

Expr Tk::details::GetToken::operator()() const
{
     return Expr("get");
}

GetToken Tk::get;

Tk::details::MoveToToken::MoveToToken() : BasicToken("moveto") {}

Expr Tk::details::MoveToToken::operator()(double fraction) const
{
     std::string str("moveto ");
     str += toString(fraction);
     return Expr(str);
}

MoveToToken Tk::moveto;

Tk::details::ScrollToken::ScrollToken() : BasicToken("scroll") {}

Expr Tk::details::ScrollToken::operator()(int n, std::string const &what) const
{
     std::string str("scroll ");
     str += toString(n); str += " ";
     str += what;
     return Expr(str);
}

ScrollToken Tk::scroll;

Tk::details::SetToken::SetToken() : BasicToken("set") {}

Expr Tk::details::SetToken::operator()() const
{
     return Expr("set");
}

Expr Tk::details::SetToken::operator()(double first, double last) const
{
     std::string str("set ");
     str += toString(first); str += " ";
     str += toString(last);
     return Expr(str);
}

SetToken Tk::set;

Tk::details::TypeToken::TypeToken() : BasicToken("type") {}

TypeToken Tk::type;

Tk::details::ValidateToken::ValidateToken() : BasicToken("validate") {}

Expr Tk::details::ValidateToken::operator()() const
{
     return Expr("validate");
}

Expr Tk::details::ValidateToken::operator()(std::string const &when) const
{
     std::string str(" -validate ");
     str += when;
     return Expr(str, false);
}

ValidateToken Tk::validate;

Tk::details::AllToken::AllToken() : BasicToken("all") {}

Expr Tk::details::AllToken::operator()() const
{
     return Expr(" -all", false);
}

AllToken Tk::all;

Tk::details::CommandToken::CommandToken() : BasicToken("command") {}

Expr Tk::details::CommandToken::operator()(std::string const &name) const
{
     std::string str(" -command { ");
     str += name; str += " }";
     return Expr(str, false);
}

Expr Tk::details::CommandToken::operator()(CallbackHandle const &handle) const
{
     std::string str(" -command { ");
     str += handle.get(); str += " }";
     return Expr(str, false);
}

CommandToken Tk::command;

Tk::details::ElideToken::ElideToken() : BasicToken("elide") {}

Expr Tk::details::ElideToken::operator()() const
{
     return Expr(" -elide", false);
}

Expr Tk::details::ElideToken::operator()(bool b) const
{
     std::string str(" -elide ");
     str += toString(b);
     return Expr(str, false);
}

ElideToken Tk::elide;

Tk::details::FromToken::FromToken() : BasicToken("from") {}

Expr Tk::details::FromToken::operator()(int val) const
{
     std::string str(" -from ");
     str += toString(val);
     return Expr(str, false);
}

Expr Tk::details::FromToken::operator()(int x1, int y1, int x2, int y2) const
{
     std::string str(" -from ");
     str += toString(x1); str += " ";
     str += toString(y1); str += " ";
     str += toString(x2); str += " ";
     str += toString(y2);
     return Expr(str, false);
}

FromToken Tk::from;

Tk::details::ImageToken::ImageToken() : BasicToken("image") {}

Expr Tk::details::ImageToken::operator()() const
{
     return Expr(" -image", false);
}

Expr Tk::details::ImageToken::operator()(std::string const &name) const
{
     std::string str(" -image ");
     str += name;
     return Expr(str, false);
}

ImageToken Tk::image;

Tk::details::MarkToken::MarkToken() : BasicToken("mark") {}

Expr Tk::details::MarkToken::operator()() const
{
     return Expr(" -mark", false);
}

Expr Tk::details::MarkToken::operator()(std::string const &option,
     std::string const &markname, std::string const &dir) const
{
     std::string str("mark ");
     str += option;
     if (markname.empty())
     {
          return Expr(str);
     }
     str += " ";
     str += markname;
     if (dir.empty())
     {
          return Expr(str);
     }
     str += " ";
     str += dir;
     return Expr(str);
}

MarkToken Tk::mark;

Tk::details::MenuLabelToken::MenuLabelToken() : BasicToken("label") {}

Expr Tk::details::MenuLabelToken::operator()(std::string const &label) const
{
     std::string str(" -label \"");
     str += label; str += '\"';
     return Expr(str, false);
}

MenuLabelToken Tk::menulabel;

Tk::details::TextToken::TextToken() : BasicToken("text") {}

Expr Tk::details::TextToken::operator()() const
{
     return Expr(" -text", false);
}

Expr Tk::details::TextToken::operator()(std::string const &t) const
{
     std::string str(" -text \"");
     str += quote(t); str += '\"';
     return Expr(str, false);
}

TextToken Tk::text;

Tk::details::ToToken::ToToken() : BasicToken("to") {}

Expr Tk::details::ToToken::operator()(int val) const
{
     std::string str(" -to ");
     str += toString(val);
     return Expr(str, false);
}

Expr Tk::details::ToToken::operator()(int x, int y) const
{
     std::string str(" -to ");
     str += toString(x); str += " ";
     str += toString(y);
     return Expr(str, false);
}

Expr Tk::details::ToToken::operator()(int x1, int y1, int x2, int y2) const
{
     std::string str(" -to ");
     str += toString(x1); str += " ";
     str += toString(y1); str += " ";
     str += toString(x2); str += " ";
     str += toString(y2);
     return Expr(str, false);
}

ToToken Tk::to;

Tk::details::WindowToken::WindowToken() : BasicToken("window") {}

Expr Tk::details::WindowToken::operator()(std::string const &name) const
{
     std::string str(" -window");
     if (name.empty())
     {
          return Expr(str, false);
     }
     str += " "; str += name;
     return Expr(str, false);
}

WindowToken Tk::window;

Tk::details::WndClassToken::WndClassToken() : BasicToken("class") {}

Expr Tk::details::WndClassToken::operator()(std::string const &name) const
{
     std::string str(" -class ");
     str += name;
     return Expr(str, false);
}

WndClassToken Tk::wndclass;

Tk::details::AfterToken::AfterToken() : BasicToken("after") {}

Expr Tk::details::AfterToken::operator()(int time) const
{
     std::string str("after ");
     str += toString(time);
     return Expr(str);
}

Expr Tk::details::AfterToken::operator()(std::string const &name) const
{
     std::string str(" -after ");
     str += name;
     return Expr(str, false);
}

Expr Tk::details::AfterToken::operator()(int time, std::string const &name) const
{
     std::string str("after ");
     str += toString(time); str += " ";
     str += name;
     return Expr(str);
}

Expr Tk::details::AfterToken::operator()(std::string const &option,
     std::string const &id) const
{
     std::string str("after ");
     str += option; str += " ";
     str += id;
     return Expr(str);
}

AfterToken Tk::after;

Tk::details::RGBToken::RGBToken() : BasicToken("rgb") {}

std::string Tk::details::RGBToken::operator()(int r, int g, int b) const
{
     if (r < 0)   r = 0;
     if (r > 255) r = 255;
     if (g < 0)   g = 0;
     if (g > 255) g = 255;
     if (b < 0)   b = 0;
     if (b > 255) b = 255;
     std::ostringstream ss;
     ss << '#' << std::setw(2) << std::setfill('0') << std::hex << r
           << std::setw(2) << std::setfill('0') << std::hex << g
           << std::setw(2) << std::setfill('0') << std::hex << b;
     return ss.str();
}

RGBToken Tk::rgb;

