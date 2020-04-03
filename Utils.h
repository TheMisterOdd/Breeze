#pragma once

#include <stdio.h>

typedef struct
{
	void* data1;
	void* data2;
} Pair;

#define panic(_Buffer, ...) fprintf(stderr, _Buffer)

