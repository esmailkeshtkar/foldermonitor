/*
 *	A C++ file that parses a configuration file using RudeConfig
 *	looks under the parameters section. If the paramter or one or more definitions do not exist
 *	then it terminates the program. Stores the config information into a map.
 */

#include "header.h"

void parseConfigFile()
{
  Config conf;

  conf.load(argMap[configFile].c_str());

  conf.setSection("Parameters");
  

  if(!conf.exists("Verbose")  	 ||
     !conf.exists("LogFile") 	 ||
     !conf.exists("Password")	 ||
     !conf.exists("NumVersions") ||
     !conf.exists("WatchDir"))
    {
      printf("ERROR! Configuration file is missing definitions!\n");
      exit(0);
    }

  argMap[verbose] = conf.getBoolValue("Verbose") ? "true" : "false";
  argMap[logfile] = conf.getStringValue("LogFile");
  argMap[numversions] = conf.getIntValue("NumVersions");
  
  if(configRead == false)
    {
      argMap[password] = conf.getStringValue("Password");
      argMap[watchdir] = conf.getStringValue("WatchDir");
    }

  if(configRead == true)
    {
      if(argMap[password] != conf.getStringValue("Password"))
	log << "USER ATTEMPTED TO CHANGE PASSWORD WHILE PROGRAM WAS RUNNING!" << endl;
      if(argMap[watchdir] != conf.getStringValue("WatchDir"))
        log << "USER ATTEMPTED TO CHANGE WATCHDIR WHILE PROGRAM WAS RUNNING!" << endl;
    }

  
  if(configRead==false)
    log.open(argMap[logfile].c_str());
  
  log << "Config file read!" << endl;
  log << "Verbose Logging Enabled?: " << argMap[verbose].c_str() << endl;

  conf.save();
}
