#pragma once

typedef struct
{
	void *Data1, *Data2;
} Pair;

#define panic(_Buffer, ...) fprintf(stderr, _Buffer)

