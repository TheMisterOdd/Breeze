#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>

struct elem {
	struct elem* prev, *next;
	void* value;
};

typedef struct {
	struct elem* root;
	size_t len;
} list_t;


/*
	@breif - returns a pointer to a new list
	@returns - a new list
*/
list_t* mklist();

/*
	@breif - creates a new list, if list == NULL
	@param[in/out] self The given list.
*/
void lazylist(list_t** self);

/*
	@breif - add a new element at the back of the list
	@param[in/out] self The given list.
	@param[in] value The new value to add.
*/
void pushbacklist(list_t** self, void* value);

/*
    [rmlist]
*/
void rmlist(list_t** self);

#ifdef LIST_IMPL

#include <stdio.h>
#include <assert.h>
#include <malloc.h>

list_t* mklist()
{
	list_t* self = (list_t*)malloc(sizeof(list_t));
	if (self == NULL)
	{
		fprintf(stderr, "[Error]: malloc() failed.\n");
		return NULL;
	}

	self->root = NULL;
	self->len = 0;

	return self;
}

void lazylist(list_t** self)
{
	if (*self == NULL)
		*self = mklist();
}

void pushbacklist(list_t** self, void* value)
{
	lazylist(self);
	struct elem** e = &(*self)->root;
	while (*e != NULL) 
	{
		e = &(*e)->next;
	}
	*e = (struct elem*)malloc(sizeof(struct elem));
	if (*e == NULL) 
	{	
		fprintf(stderr, "[Error]: malloc() failed.\n");
		return;
	}
	(*e)->value = value;
	(*e)->next = NULL;
	(*self)->len++;
}

struct elem* popatlist(list_t** self, size_t n) 
{
	if (self == NULL) 
	{
		return NULL;
	}
	
	if (n == 0) 
	{
		struct elem* tmp = (*self)->root;
		(*self)->root = tmp->next;
		return tmp;
	}
	
	size_t index = 0;
	struct elem* e = (*self)->root;
	while (e != NULL) 
	{
		if (index == n - 1) break;
		e = e->next;
		index++;
	}
	
	struct elem* pop = e->next;
	e->next = pop->next;
	return pop;
}

void rmlist(list_t** self) 
{   
    struct elem* e = (*self)->root;
    while (e != NULL) 
    {
        struct elem* next = e->next;
        free(e);
        e = next;
    }
    free(*self);
}

#endif

#endif
