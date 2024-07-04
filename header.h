/*
 *
 *	header file used for multiple C++ files. 
 * 
 */

#ifndef __PROJECT5__
#define __PROJECT5__

//import libraries
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <map>
#include <tclap/CmdLine.h>
#include <rude/config.h>
#include <unistd.h>
#include <csignal>
#include <signal.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

using std::map;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::string;
using namespace rude; 
using namespace std;

enum command{isDaemon, configFile, verbose, logfile, password, numversions, watchdir};

extern map<int, string> argMap;
extern ofstream log;
extern int fd;
extern int wd;
extern ofstream pidfile;
extern string pid;
extern bool configRead;
extern string dirname;
 
#endif

