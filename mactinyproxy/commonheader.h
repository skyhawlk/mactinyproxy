//
//  commonheader.h
//  mactinyproxy
//
//  Created by Avishay Dinar on 30/08/2020.
//  Copyright © 2020 Avishay Dinar. All rights reserved.
//

#ifndef commonheader_h
#define commonheader_h
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <map>
#include <queue>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sys/time.h>
#include <pwd.h>
#include <thread>
#include <mutex>
#include <signal.h>
#include <fts.h>
#include <libproc.h>
#include <condition_variable>
#include <CoreFoundation/CoreFoundation.h>
#include <array>
#include <utility>
#include <ctime>
#include <sysexits.h>
#include <future>

#include "proxymgr.hpp"
#include "global-config-support.h"
#include "../libmactinyproxy/common.h"
#include "../libmactinyproxy/conf.h"
#include "../libmactinyproxy/log.h"
#include "../libmactinyproxy/main.h"
#include "../libmactinyproxy/filter.h"


/* Global variables for the main controls of the program */
#define MAXBUFFSIZE     ((size_t)(1024 * 96))   /* Max size of buffer */
#define MAX_IDLE_TIME   (60 * 10)       /* 10 minutes of no activity */

#define FILTER_ENABLE

#define PACKAGE_BUGREPORT "https://tinyproxy.github.io/"
#define PACKAGE_NAME "Tinyproxy"
#define PACKAGE_STRING  "Tinyproxy 1.10.0-git-45-gf825bea"
#define PACKAGE_TARNAME "tinyproxy"
#define PACKAGE_URL ""
#define PACKAGE_VERSION "1.10.0-git-45-gf825bea"
#define PATH_SEPARATOR ":"
#define POD2MAN "/usr/bin/pod2man"
#define SET_MAKE
#define SHELL "/bin/sh"
#define STRIP
#define TINYPROXY_STATHOST "tinyproxy.stats"
#define VERSION "1.10.0-git-45-gf825bea"
#define SYSCONFDIR  "etc"
#define PACKAGE_NAME "Tinyproxy"
#define PACKAGE "tinyproxy"


extern struct config_s *config;
extern unsigned int received_sighup;    /* boolean */
static struct config_s configs[2];
extern int reload_config (int reload_logging);
static const char* config_file;

#endif /* commonheader_h */
