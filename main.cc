/*
 *	Main C++ program for a daemon process that monitors a folder.
 *	Combined with several various C++ files in order to
 *	run either in the foreground or background (daemon)
 *	and monitor a specified folder designated by a configuration file
 *	Whenever a file in that folder is changed, the program
 *	will create a copy and append a timestamp to it
 *	and put the copy into a .versions subfolder
 * 
 */


#include "header.h"

int fd;
int wd;
int sig = 0;
ofstream pidfile;
ofstream log;
string pid = "dirmond.pid";
map<int, string> argMap;
string dirname;
bool configRead;

bool fileexists(const char *filename)
{
  ifstream ifile(filename);
  return ifile;
}

void parseConfigFile();

int main(int argc, char*argv[])
{
  void signalHandling(int i);
  void inotifyFunctions();
  void parseCommandLine(int a, char *b[]);
  mode_t mode = 0755;
  
  signal(SIGHUP, signalHandling);
  signal(SIGINT, signalHandling);
  signal(SIGTERM, signalHandling);


  pid_t forkvalue;
  bool forked = false;
  enum command{isDaemon, configFile, verbose, logfile, password, numversions, watchdir};

  if(fileexists(pid.c_str()))
      { cout << "ANOTHER INSTANCE OF THIS PROGRAM IS ALREADY RUNNING IN THE BACKGROUND. PLEASE TERMINATE IT AND TRY AGAIN." << endl;
	exit(0);
      }

  parseCommandLine(argc, argv);
  parseConfigFile();
  configRead = true;
  cout << "Logging all future events to: " << argMap[logfile] << endl;

  dirname = argMap[watchdir]+"/.versions";
  log << "Storing backup copies in directory: " << dirname << endl;

  if(mkdir(dirname.c_str(), mode) == 0)
    log << "Directory does not exist! Making backup directory: " << dirname << endl;
  else
    log << "Backup directory: " << dirname << " exists. Storing backups there." << endl;
  
  log << "Watching Directory: " << argMap[watchdir].c_str() << endl;
 
  if(argMap[isDaemon] == "true")
    {
      forked = true;
      forkvalue = fork();
      pidfile.open(pid.c_str());
      
      switch(forkvalue){
      case -1:
	log << "FORK FAILED..." << endl;
	exit(1);
	break;
      case 0:
	pidfile << getpid() << endl;
	pidfile.close();
	log << "FORK SUCCESSFUL...RUNNING IN BACKGROUND" << endl;
	break;
      default:
	exit(0);
      }

    }

  if(wd==-1)
    {
      cout << "ERROR WATCHING DIRECTORY" << endl;
    }

  if(!forked)
    {
      cout << "Running program in foreground...press Ctrl+C to terminate." << endl;
    }  

  fd = inotify_init();
  wd = inotify_add_watch(fd, argMap[watchdir].c_str(), IN_MODIFY);

  while(1)
    {
      inotifyFunctions();
    }
    

  return 0;
}
