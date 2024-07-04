/*
 *	A C++ file that sends log information to an output log
 *	If verbose is enabled then it tells when a file was modified.
 *	Additionally, this file uses pipes to create a copy of a modified
 *	file and send it to the .versions folder with a timestamp attached
 *	to the end of the file name.
 * 
 */
#include "header.h"

#define BUFFER_SIZE 1024

void loggingFunctions(string s)
{
  FILE *date;
  FILE *copyFile;
  string shellcmd = "date +\"%Y.%m.%d-%H:%M:%S\"";
  char tmpbuffer[BUFFER_SIZE];
  char *line_p;
  string timestamp;
  string copy;

  date = popen(shellcmd.c_str(), "r");

  line_p = fgets(tmpbuffer, BUFFER_SIZE, date);
 
  timestamp = line_p;
  
  timestamp.erase(remove(timestamp.begin(), timestamp.end(), '\n'), timestamp.end());
  
  copy = "cp "+argMap[watchdir]+"/"+s+" "+dirname+"/"+s+"."+timestamp;
  copy.erase(remove(copy.begin(), copy.end(), '\n'), copy.end());
  copyFile = popen(copy.c_str(), "r");
  
  if(argMap[verbose] == "true")
    {
      log << "\nThe File \"" << s << "\" was modified at " << line_p;
      log << "The File \"" << s << "." << timestamp << "\" was placed in the directory: " << dirname; 
    }
  else
    {
      log << "\nThe File \"" << s << "\" was modified." << endl;
      log << "A copy of the file was placed in the directory: " << dirname;
    }

  log << endl;

  pclose(date);
  pclose(copyFile);
}


