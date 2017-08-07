/*******************************************************************************
 * Copyright 2012 Kronos Incorporated. All rights reserved.
 *
 * File Name : template.c
 *
 * Description :
 *
 * Version : 0.1.0
 *
 * Created Date : 12 05 2012
 *
 * Modification History :
 *    0.1    RSM    Initial Release
 *
 ******************************************************************************/


#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include "time.h"

/* version number.  Note: the bug release is a normally a date code */
#define MAJOR_REVISION 0
#define MINOR_REVISION 1
#if !defined(BUG_RELEASE_REVISION)
#define BUG_RELEASE_REVISION "0000000"
#endif

int g_iVerboseFlag;

static struct option long_options[] =
  {
    /* These options set a flag. */
    {"verbose", no_argument, &g_iVerboseFlag, 1},
    {"brief",   no_argument, &g_iVerboseFlag, 0},
    /* These options don't set a flag.
       We distinguish them by their indices. */
    {"debug_level",   required_argument, 0, 'd'}, 
    {"help",       no_argument,             0 ,'h'},
    {0, 0, 0, 0}
  };
/* prototypes */
void Usage (char *Name);
void Version (char *Name);

int main(int argc, char *argv[])
{
  int  c = -1;
  int option_index = 0;
  int t_iError = 0;
  int t_uiCount = 0;

  g_iVerboseFlag = 1;
  fprintf(stdout, "%s: Compiled on %s %s\n",argv[0],
	  CompileDate,CompileTime);
  fprintf(stdout, "%s: Release %d.%d.%s\n",argv[0],
	  MAJOR_REVISION,
	  MINOR_REVISION,
	  BUG_RELEASE_REVISION);

  if (argc == 1) {
    fprintf(stdout,"%s: No passed Parameters using defaults!\n",argv[0]);
  } 
  
  while ((c = getopt_long (argc, argv, "hd:",
			     long_options, 
			     &option_index)) != -1) {
    switch (c)
      {
      case 'd':
	g_iVerboseFlag = strtoul(optarg,(char **)NULL,10);
        t_iError = 1;
	break; 
      case 'h':
	Usage(argv[0]);
        t_iError = 1;
	/* getopt_long already printed an error message. */
	break;
      case 'v':
        Version(argv[0]);
        t_iError = 1;
        break;
      } 
  }
  if (t_iError == 0) {
    Version(argv[0]);
  }
  return t_iError;
}

void Usage (char *Name) 
{
  Version(Name);
  fprintf(stdout,"%s Usage\n",Name);
  fprintf(stdout, "--verbose:\t\t (default on) prints information to stdout\n");
  fprintf(stdout, "--brief:\t\t (default off) runs quiet\n");
  fprintf(stdout, "-d, --debug_level:\t debug level\n"); 
  fprintf(stdout, "-h, --help: \t\t this menu\n");
  return ;
}

void Version(char *Name)
{
  fprintf(stdout, "%s: Compiled on %s %s\n",Name,
          CompileDate,CompileTime);
  fprintf(stdout, "%s: Release %d.%d.%s\n",Name,
          MAJOR_REVISION,
          MINOR_REVISION,
          BUG_RELEASE_REVISION);

  return;
}

