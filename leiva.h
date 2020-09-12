#ifndef _LEIVA_H_
#define _LEIVA_H_

/*
 *  Copyright 2020 The Leiva Authors. All rights reserved.
 *  Use of this source code is governed by a BSD-style
 *  license that can be found in the LICENSE file.
 *
 *   - To my girl, Paula.
 */

#define LEI_API

#define NO_ARGS_ERROR	    "leiva: no arguments listed." /* Not arguments */
#define NO_BUILD_ARGS_ERROR "leiva build: no listed files or arguments." /* Not arguments for the build command */
#define NO_RUN_ARGS_ERROR   "leiva run: no listed files or arguments." /* Not arguments for the run command */

/* Help */
#define HELP \
"Usage: leiva <command> [arguments]\n\n"\
"Commands:\n\n"\
"   build       compiles the leiva source files and creates an executable.\n"\
"   run         compiles the leiva source files and creates an executable.\n"\

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
#define KW_FMT     "format"

#define MATCH(x, y) ((!strcmp((char*)x, (char*)y)))

#endif
