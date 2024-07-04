/*
 * Description
 *
 *	A C++ program that uses TCLAP to parse command line information
 *	-d is a flag that determines whether the program runs in the background or not
 *	An optional configuration file name can be given as well.
 *	Stores the information obtained from the command line in a map.
 * 
 */
#include "header.h"

void parseCommandLine(int argc, char*argv[])
{
  TCLAP::CmdLine cmd("Directory Monitor Daemon by Esmail Keshtkar", ' ', "1.0");
  TCLAP::SwitchArg daemonSwitch("d", "daemon", "Run in daemon mode (forks to run as a daemon)", cmd, false);
  TCLAP::UnlabeledValueArg<string> confArg("configfile", "The name of the configuration file. Defaults to dirmond.conf", false, "dirmond.conf", "input filename", false);
  cmd.add(confArg);
  cmd.parse(argc, argv);

  argMap[isDaemon] = daemonSwitch.getValue() ? "true" : "false";
  argMap[configFile] = confArg.getValue();
  
  cout << "Running program as daemon?: " << argMap[isDaemon] << endl;
 
}
