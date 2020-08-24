#ifndef _MAIN_H_
#define _MAIN_H_

#include "Arg.h"

#include <iostream>

int main(int argc, char** argv) 
{
	return Arg::analize(argc, argv);
}

#endif /* _MAIN_H_ */