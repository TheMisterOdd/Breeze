#pragma once

/* Errors: */
#define NO_ARGS_ERROR	"leiva: no arguments listed."
#define NO_BUILD_ARGS_ERROR "leiva build: no listed files or arguments."
#define NO_RUN_ARGS_ERROR "leiva run: no listed files or arguments."


/* Help */
#define help_fmt(cmd, desc) "\t" cmd "\t\t" desc "\n"
#define HELP \
"Usage: leiva <command> [arguments]\n\n"\
"Commands:\n\n"\
"\tbuild\t\tcompiles the leiva source files and creates an executable.\n"\
"\trun\t\tcompiles the leiva source files and creates an executable.\n"\

/* Version related: */
#define VERSION_MAJOR    0
#define VERSION_MINOR    1
#define VERSION_REVISION 0

#ifdef _WIN32 
/* The operating system of the machine is windows. */
#define SYSTEM_OS "windows"
#else
/* The operating system of the machine is unix. */
#define SYSTEM_OS "unix"
#endif

#if defined(_M_IX86) || defined(__i386__)
#define SYSTEM_ARCH "amd86"
#else
#define SYSTEM_ARCH "amd64"
#endif

/* Args keywords */
#define KW_HELP    "help" 
#define KW_VERSION "version" 
#define KW_BUILD   "build" 
#define KW_RUN     "run"


#include <cstdlib>
class Arg
{
public:
	static int analize(int argc, char** argv);
};

