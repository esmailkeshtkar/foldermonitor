/*
 *	A C++ function that uses inotify to monitor a given directory
 *	When a file is changed, passes the information to the loggingFunctions
 *	function.
 */

#include "header.h"

#define MAX_EVENTS 4096
#define LEN_NAME 32

#define EVENT_SIZE (sizeof (struct inotify_event))
#define BUF_LEN (MAX_EVENTS * (EVENT_SIZE+LEN_NAME))

void inotifyFunctions()
{
  void loggingFunctions(string s);

  char buf[BUF_LEN];
  int length, i=0;
  
  length = read(fd, buf, BUF_LEN);
  
  if(length < 0)
    perror("ERROR");
  
  while(i < length)
    {
      struct inotify_event *event = (struct inotify_event *) &buf[i];
      
      if(event->len)
	if((event->mask & IN_MODIFY) && !(event->mask & IN_ISDIR))
	  {
	    loggingFunctions(event->name);
	  }
      
      i+= EVENT_SIZE + event->len;
     }
}
