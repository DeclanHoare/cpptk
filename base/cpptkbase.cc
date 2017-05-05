//
// Copyright (C) 2004-2006, Maciej Sobczak
// Copyright 2017 Declan Hoare
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//

#include "cpptkbase.h"
#include <tcl.h>
#include <tk.h>
#include <map>
#include <ostream>
#include <iostream>
#include <sstream>
#include <boost/scoped_ptr.hpp>

using namespace Tk;
using namespace Tk::details;

namespace { // anonymous

class Interp
{
public:
     Interp()
     {
          interp_ = Tcl_CreateInterp();
	
          int cc = Tcl_Init(interp_);
          if (cc != TCL_OK)
          {
               throw TkError(Tcl_GetStringResult(interp_));
          }

          cc = Tk_Init(interp_);
          if (cc != TCL_OK)
          {
               throw TkError(Tcl_GetStringResult(interp_));
          }
          
          cc = Tcl_Eval(interp_, "namespace eval CppTk {}");
          if (cc != TCL_OK)
          {
               throw TkError(Tcl_GetStringResult(interp_));
          }
     }
     
     ~Interp()
     {
          // GUI programs are supposed to exit by calling "exit"
          // then - explicit delete here is harmful
          //Tcl_DeleteInterp(interp_);
     }
     
     Tcl_Interp * get() const { return interp_; }

private:
     Tcl_Interp * interp_;
};

// lazy-initialization of Tcl interpreter
Tcl_Interp * getInterp()
{
     static Interp interp;
     return interp.get();
}

// output stream for dumping Tk commands
// (useful for automated testing)
std::ostream *dumpstream = &std::cerr;

void do_eval(std::string const &str)
{
#ifdef CPPTK_DUMP_COMMANDS
     *dumpstream << str << '\n';
#endif // CPPTK_DUMP_COMMANDS

#ifndef CPPTK_DONT_EVALUATE
     int cc = Tcl_Eval(getInterp(), str.c_str());
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(getInterp()));
     }
#endif
}

// map for callbacks
typedef std::map<int, std::shared_ptr<CallbackBase> > CallbacksMap;
CallbacksMap callbacks;

// callback id
int callbackId = 0;

char const *callbackPrefix = "CppTk::callback";

typedef std::map<int *,    std::string> IntLinks;
typedef std::map<double *, std::string> DoubleLinks;
typedef std::map<std::string *, std::string> StringLinks;

IntLinks intLinks;
DoubleLinks doubleLinks;
StringLinks stringLinks;

typedef std::map<std::string *, char *> StringLinkBuffers;
StringLinkBuffers stringLinkBuffers;

int linkId = 0;

char const *linkVarPrefix = "CppTk::variable";

// this function refreshes Tcl variables from C++ variables
void linkCpptoTcl()
{
     // synchronize C++ variables with Tcl variables
     // it is enough to refresh string buffers and update links
     
     // refresh string buffers
     for (StringLinks::iterator it = stringLinks.begin();
          it != stringLinks.end(); ++it)
     {
          std::string *ps = it->first; // pointer to C++ string (original value)

          StringLinkBuffers::iterator itb = stringLinkBuffers.find(ps);
          char *&pb = itb->second; // pointer to Tcl buffer (destination)
          
          if (pb != NULL)
          {
               Tcl_Free(pb);
          }
          pb = Tcl_Alloc(static_cast<unsigned int>(ps->size()) + 1);
          std::copy(ps->begin(), ps->end(), pb);
          pb[ps->size()] = '\0';
          
          Tcl_UpdateLinkedVar(getInterp(), it->second.c_str());
     }
     
     // update other (int and double) Tcl links
     for (IntLinks::iterator it = intLinks.begin();
          it != intLinks.end(); ++it)
     {
          Tcl_UpdateLinkedVar(getInterp(), it->second.c_str());
     }
     for (DoubleLinks::iterator it = doubleLinks.begin();
          it != doubleLinks.end(); ++it)
     {
          Tcl_UpdateLinkedVar(getInterp(), it->second.c_str());
     }
}

// this function refreshes C++ variables from Tcl variables
void linkTcltoCpp()
{
     // it is enough to refresh strings from their buffers
     for (StringLinks::iterator it = stringLinks.begin();
          it != stringLinks.end(); ++it)
     {
          std::string *ps = it->first; // pointer to C++ string (destination)
          
          StringLinkBuffers::iterator itb = stringLinkBuffers.find(ps);
          char *pb = itb->second; // pointer to Tcl buffer (original value)
          
          if (pb != NULL)
          {
               ps->assign(pb);
          }
          else
          {
               ps->clear();
          }
     }
}

} // namespace // anonymous


// global flag for avoiding multiple-error problem
bool Tk::TkError::inTkError = false;


// generic callback handler

extern "C"
int callbackHandler(ClientData cd, Tcl_Interp *interp,
     int objc, Tcl_Obj *CONST objv[])
{
     int slot = static_cast<int>(reinterpret_cast<size_t>(cd));
     
     CallbacksMap::iterator it = callbacks.find(slot);
     if (it == callbacks.end())
     {
          Tcl_SetResult(interp,
               (char*)"Trying to invoke non-existent callback", TCL_STATIC);
          return TCL_ERROR;
     }
     
     try
     {
          // refresh C++ variables
          linkTcltoCpp();
          
          Params p(objc, reinterpret_cast<void*>(
               const_cast<Tcl_Obj **>(objv)));
          it->second->invoke(p);
          
          // refresh Tcl variables
          linkCpptoTcl();
     }
     catch (std::exception const &e)
     {
          Tcl_SetResult(interp, const_cast<char*>(e.what()), TCL_VOLATILE);
          return TCL_ERROR;
     }
     return TCL_OK;
}

// generic callback deleter

extern "C"
void callbackDeleter(ClientData cd)
{
     int slot = static_cast<int>(reinterpret_cast<size_t>(cd));
     callbacks.erase(slot);
}

std::string Tk::details::addCallback(std::shared_ptr<CallbackBase> cb)
{
     int newSlot = callbackId++;
     callbacks[newSlot] = cb;
     
     std::string newCmd(callbackPrefix);
     newCmd += std::to_string(newSlot);
     
     Tcl_CreateObjCommand(getInterp(), newCmd.c_str(),
          callbackHandler, reinterpret_cast<ClientData>(
			static_cast<size_t>(newSlot)),
          callbackDeleter);
     
     return newCmd;
}

std::string Tk::details::addLinkVar(int &i)
{
     int newLink = linkId++;
     std::string newLinkVar(linkVarPrefix);
     newLinkVar += std::to_string(newLink);
     
     int cc = Tcl_LinkVar(getInterp(), newLinkVar.c_str(),
          reinterpret_cast<char*>(&i), TCL_LINK_INT);
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(getInterp()));
     }
     
     intLinks[&i] = newLinkVar;
     return newLinkVar;
}

std::string Tk::details::addLinkVar(double &d)
{
     int newLink = linkId++;
     std::string newLinkVar(linkVarPrefix);
     newLinkVar += std::to_string(newLink);
     
     int cc = Tcl_LinkVar(getInterp(), newLinkVar.c_str(),
          reinterpret_cast<char*>(&d), TCL_LINK_DOUBLE);
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(getInterp()));
     }
     
     doubleLinks[&d] = newLinkVar;
     return newLinkVar;
}

std::string Tk::details::addLinkVar(std::string &s)
{
     int newLink = linkId++;
     std::string newLinkVar(linkVarPrefix);
     newLinkVar += std::to_string(newLink);
     
     std::pair<std::map<std::string *, char *>::iterator, bool> it =
          stringLinkBuffers.insert(make_pair(&s, static_cast<char*>(NULL)));
     
     char *&pb = it.first->second;
     pb = Tcl_Alloc(static_cast<unsigned int>(s.size()) + 1);
     copy(s.begin(), s.end(), pb);
     pb[s.size()] = '\0';
     
     int cc = Tcl_LinkVar(getInterp(), newLinkVar.c_str(),
          reinterpret_cast<char*>(&it.first->second), TCL_LINK_STRING);
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(getInterp()));
     }
     
     stringLinks[&s] = newLinkVar;
     return newLinkVar;
}

void Tk::details::deleteLinkVar(int &i)
{
     IntLinks::iterator it = intLinks.find(&i);
     if (it == intLinks.end())
     {
          return;
     }
     
     Tcl_UnlinkVar(getInterp(), it->second.c_str());
     intLinks.erase(it);
}

void Tk::details::deleteLinkVar(double &d)
{
     DoubleLinks::iterator it = doubleLinks.find(&d);
     if (it == doubleLinks.end())
     {
          return;
     }
     
     Tcl_UnlinkVar(getInterp(), it->second.c_str());
     doubleLinks.erase(it);
}

void Tk::details::deleteLinkVar(std::string &s)
{
     StringLinks::iterator it = stringLinks.find(&s);
     if (it == stringLinks.end())
     {
          return;
     }
     
     Tcl_UnlinkVar(getInterp(), it->second.c_str());
     stringLinks.erase(it);
     
     StringLinkBuffers::iterator itb = stringLinkBuffers.find(&s);
     char *pb = itb->second;
     if (pb != NULL)
     {
          Tcl_Free(pb);
     }
     
     stringLinkBuffers.erase(itb);
}

void Tk::details::setResult(bool b)
{
     Tcl_SetObjResult(getInterp(), Tcl_NewBooleanObj(b));
}

void Tk::details::setResult(long i)
{
     Tcl_SetObjResult(getInterp(), Tcl_NewLongObj(i));
}

void Tk::details::setResult(double d)
{
     Tcl_SetObjResult(getInterp(), Tcl_NewDoubleObj(d));
}

void Tk::details::setResult(std::string const &s)
{
     Tcl_SetObjResult(getInterp(),
          Tcl_NewStringObj(s.data(), static_cast<int>(s.size())));
}

int Tk::details::getResultLen()
{
     Tcl_Interp *interp = getInterp();
     
     Tcl_Obj *list = Tcl_GetObjResult(interp);
     int len, cc;
     
     cc = Tcl_ListObjLength(interp, list, &len);
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(interp));
     }
     
     return len;
}

template <>
int Tk::details::getResultElem<int>(int indx)
{
     Tcl_Interp *interp = getInterp();

     Tcl_Obj *list = Tcl_GetObjResult(interp);
     Tcl_Obj *obj;
     
     int cc = Tcl_ListObjIndex(interp, list, indx, &obj);
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(interp));
     }
     
     int val;
     cc = Tcl_GetIntFromObj(interp, obj, &val);
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(interp));
     }
     
     return val;
}

template <>
double Tk::details::getResultElem<double>(int indx)
{
     Tcl_Interp *interp = getInterp();

     Tcl_Obj *list = Tcl_GetObjResult(interp);
     Tcl_Obj *obj;
     
     int cc = Tcl_ListObjIndex(interp, list, indx, &obj);
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(interp));
     }
     
     double val;
     cc = Tcl_GetDoubleFromObj(interp, obj, &val);
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(interp));
     }
     
     return val;
}

template <>
std::string Tk::details::getResultElem<std::string>(int indx)
{
     Tcl_Interp *interp = getInterp();

     Tcl_Obj *list = Tcl_GetObjResult(interp);
     Tcl_Obj *obj;
     
     int cc = Tcl_ListObjIndex(interp, list, indx, &obj);
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(interp));
     }
     
     return Tcl_GetString(obj);
}

details::Command::Command(std::string const &str, std::string const &postfix)
     : invoked_(false), str_(str), postfix_(postfix)
{
}

details::Command::~Command()
{
     if (!TkError::inTkError)
     {
          invokeOnce();
     }
}

std::string Tk::details::Command::invoke() const
{
     invokeOnce();
     return Tcl_GetStringResult(getInterp());
}

void Tk::details::Command::invokeOnce() const
{
     if (invoked_ == false)
     {
          invoked_ = true;
          
          std::string cmd(str_);
          cmd += postfix_;
          
          do_eval(cmd);
     }
}

details::Expr::Expr(std::string const &str, bool starter)
{
     if (starter)
     {
          cmd_.reset(new Command(str));
     }
     else
     {
          str_ = str;
     }
}

details::Expr::Expr(std::string const &str, std::string const &postfix)
{
     cmd_.reset(new Command(str, postfix));
}

std::string Tk::details::Expr::getValue() const
{
     if (!str_.empty())
     {
          return str_;
     }
     else
     {
          return cmd_->getValue();
     }
}

details::Expr::operator std::string() const
{
     return cmd_->invoke();
}

details::Expr::operator int() const
{
     cmd_->invokeOnce();
     
     Tcl_Interp *interp = getInterp();
     Tcl_Obj *obj = Tcl_GetObjResult(interp);

     int val, cc;
     cc = Tcl_GetIntFromObj(interp, obj, &val);
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(interp));
     }
     
     return val;
}

details::Expr::operator double() const
{
     cmd_->invokeOnce();
     
     Tcl_Interp *interp = getInterp();
     Tcl_Obj *obj = Tcl_GetObjResult(interp);
     
     double val;
     int cc = Tcl_GetDoubleFromObj(interp, obj, &val);
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(interp));
     }
     
     return val;
}

details::Expr::operator Tk::Point() const
{
     std::string ret(cmd_->invoke());
     if (ret.empty())
     {
          return Tk::Point(0, 0);
     }

     int len = getResultLen();
     if (len < 2)
     {
          throw TkError("Cannot convert the result list to Point\n");
     }
     
     int x = getResultElem<int>(0);
     int y = getResultElem<int>(1);
     
     return Point(x, y);
}

details::Expr::operator Tk::Box() const
{
     std::string ret(cmd_->invoke());
     if (ret.empty())
     {
          return Tk::Box(0, 0, 0, 0);
     }
     
     int len = getResultLen();
     if (len < 4)
     {
          throw TkError("Cannot convert the result list to Box\n");
     }
     
     int x1 = getResultElem<int>(0);
     int y1 = getResultElem<int>(1);
     int x2 = getResultElem<int>(2);
     int y2 = getResultElem<int>(3);
     
     return Box(x1, y1, x2, y2);
}

// these two specializations are used to extract parameter
// with the requested type

template <>
int Tk::details::Params::get<int>(int argno) const
{
     if (argno < 1 || argno >= argc_)
     {
          throw TkError("Parameter number out of valid range");
     }
     
     Tcl_Obj *CONST *objv = reinterpret_cast<Tcl_Obj *CONST *>(objv_);
     
     int res, cc;
     cc = Tcl_GetIntFromObj(getInterp(), objv[argno], &res);
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(getInterp()));
     }
     
     return res;
}

template <>
std::string Tk::details::Params::get<std::string>(int argno) const
{
     if (argno < 1 || argno >= argc_)
     {
          throw TkError("Parameter number out of valid range");
     }
     
     Tcl_Obj *CONST *objv = reinterpret_cast<Tcl_Obj *CONST *>(objv_);
     
     std::string res = Tcl_GetString(objv[argno]);
     return res;
}

std::ostream & Tk::details::operator<<(std::ostream &os, BasicToken const &token)
{
     return os << static_cast<std::string>(token);
}

namespace { // anonymous

void doSingleQuote(std::string &s, char c)
{
     std::string::size_type pos = 0;
     while ((pos = s.find(c, pos)) != std::string::npos)
     {
          s.insert(pos, "\\");
          pos += 2;
     }
}

} // namespace anonymous

// this function is used to quote quotation marks in string values'
// in later version, it will not be needed
std::string Tk::details::quote(std::string const &s)
{
     std::string ret(s);
     doSingleQuote(ret, '\\');
     doSingleQuote(ret, '\"');
     doSingleQuote(ret, '$');
     doSingleQuote(ret, '[');
     doSingleQuote(ret, ']');
     
     return ret;
}

// basic Tk expression operations

Expr Tk::operator-(Expr const &lhs, Expr const &rhs)
{
     std::shared_ptr<Command> cmd(lhs.getCmd());
     cmd->append(rhs.getValue());
     
     return Expr(cmd);
}

Expr Tk::operator<<(std::string const &w, Expr const &rhs)
{
     std::shared_ptr<Command> cmd(rhs.getCmd());
     cmd->prepend(" ");
     cmd->prepend(w);

     return Expr(cmd);
}

// helper functions

void Tk::deleteCallback(std::string const &name)
{
     std::string::size_type pos = name.find_first_not_of(callbackPrefix);
     if (pos == std::string::npos) return;
     
     int slot = std::stoi(name.substr(pos, name.size()));
     callbacks.erase(slot);
     
     int cc = Tcl_DeleteCommand(getInterp(), name.c_str());
     if (cc != TCL_OK)
     {
          throw TkError(Tcl_GetStringResult(getInterp()));
     }
}

Tk::CallbackHandle::CallbackHandle(std::string const &name) : name_(name) {}

Tk::CallbackHandle::~CallbackHandle() { deleteCallback(name_); }

Expr Tk::eval(std::string const &str)
{
     return Expr(str);
}

void Tk::init(char *argv0)
{
	Tcl_FindExecutable(argv0);
}

void Tk::runEventLoop()
{
     // refresh Tcl variables
     linkCpptoTcl();
     
     Tk_MainLoop();
}

void Tk::setDumpStream(std::ostream &os)
{
	dumpstream = &os;
}
