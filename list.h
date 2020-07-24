#ifndef _LIST_H_
#define _LIST_H_


enum type_t {
	UNKNOW =	-1,
	INT	   =	 0,
	DOUBLE =	 1,
	STRING =     2,
	PLUS   =    '+',
	MINUS  =    '-',
	MUL    =    '*',
	DIV	   =    '/',
	LPAREN =    '(',
	RPAREN =    ')',
	POWER  =    '^',
};


#include <stdint.h>

struct list_t
{
	uint64_t* _val;
	enum type_t _Ty;

	struct list_t* _next;
};

/*
	@brief - appends a new value at the back of the given list.
	@param[in] self the node that the new value is going to be appended in.
	@param[in] _val the new value to be appended.
	@param[in] _Ty the type of the value that is going to be appended.
*/
void list_push_back(struct list_t** self, void* _val, enum type_t _Ty);

/*
	@brief - Removes a value from the given list.
	@param[in] self the list that the value is going to be removed from.
	@param[in] n the given index.
	@return The node that has been deleted.
*/
struct list_t* list_pop_at(struct list_t** self, size_t n);

char* list_to_string(struct list_t** self);

#ifdef LIST_IMPL
	
#include <malloc.h>
#include <assert.h>
#include <string.h>

void list_push_back(struct list_t** self, void* _val, enum type_t _Ty)
{
	if (*self) 
	{
		struct list_t** tmp = &(*self)->_next;
		while (*tmp != NULL)
		{
			tmp = &(*tmp)->_next;
		}
		list_push_back(tmp, _val, _Ty);
	}
	else
	{
		*self = (struct list_t*)malloc(sizeof(struct list_t));
		assert(*self);

		(*self)->_val = _val;
		(*self)->_Ty = _Ty;
		(*self)->_next = NULL;
	}
}

struct list_t* list_pop_at(struct list_t** self, size_t n) 
{
	struct list_t** tmp = self;
	size_t _idx = 0;
	while ((*tmp)->_next) 
	{
		if (_idx == n) 
		{
			break;
		}
		tmp = &(*tmp)->_next;
		_idx++;
	}

	struct list_t* _Return = *tmp;
	(*tmp) = (*tmp)->_next;

	return _Return;
}

char* list_to_string(struct list_t** self)
{
	char* _Buffer = (char*)malloc(sizeof(char) * 1024);
	assert(_Buffer);

	strcpy(_Buffer, "[");
	struct list_t** tmp = self;
	
	while (*tmp) 
	{
		
		if ((*tmp)->_Ty == INT) 
		{
			if ((*tmp)->_next == NULL)
			{
				sprintf(_Buffer, "%s%lld", _Buffer, (int64_t)(*tmp)->_val);
			}
			else
			{
				sprintf(_Buffer, "%s%lld, ", _Buffer, (int64_t)(*tmp)->_val);
			}
		}
		else if ((*tmp)->_Ty == DOUBLE)
		{
			double* n = (double*)(*tmp)->_val;

			if ((*tmp)->_next == NULL)
			{
				sprintf(_Buffer, "%s%g", _Buffer, (double)*n);
			}
			else
			{
				sprintf(_Buffer, "%s%g, ", _Buffer, (double)*n);
			}
		}
		else if ((*tmp)->_Ty == STRING) 
		{
			if ((*tmp)->_next == NULL)
			{
				sprintf(_Buffer, "%s%s", _Buffer, (char*)(*tmp)->_val);
			}
			else
			{
				sprintf(_Buffer, "%s%s, ", _Buffer, (char*)(*tmp)->_val);
			}
		}
		else 
		{
			if ((*tmp)->_next == NULL)
			{
				sprintf(_Buffer, "%s%c", _Buffer, (char)(*tmp)->_val);
			}
			else
			{
				sprintf(_Buffer, "%s%c, ", _Buffer, (char)(*tmp)->_val);
			}
		}
		

		tmp = &(*tmp)->_next;
	}

	strcat(_Buffer, "]\0");

	return _Buffer;
}


#endif

#endif