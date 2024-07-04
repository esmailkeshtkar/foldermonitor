//Esmail Keshtkar
//handles signals sent by the console

#include "header.h"

void parseConfigFile();

//receives a signal that determines operation
void signalHandling(int signum)
{
  //rereads the config file
  if(signum == 1)
    {
      log << "\n REREADING CONFIG FILE..." << endl;
      parseConfigFile();
    }
  //terminates the program
  if(signum == 2)
    {
      remove(pid.c_str());
      log << "\nSIGINT SIGNAL RECEIVED ... TERMINATING PROGRAM..." << endl;
      inotify_rm_watch(fd, wd);
      close(fd);
      log.close();
      exit(0);
    }
   //terminates the program
  if(signum == 15)
    {
      remove(pid.c_str());
      log << "\nSIGTERM SIGNAL RECEIVED ... TERMINATING PROGRAM..." << endl;
      inotify_rm_watch(fd, wd);
      close(fd);
      log.close();
      exit(0);
    }
}
