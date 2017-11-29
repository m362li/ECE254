/**
 * @file memory.c
 * @brief: ECE254 Lab: memory allocation algorithm comparison template file
 * @author: 
 * @date: 2015-11-20
 */

/* includes */
#include <stdio.h> 
#include <stdlib.h> 
#include "mem.h"

/* defines */

/* global varaiables */

/*

mem_list

*/
struct mem_list{
	int* address_location;
	size_t allocated_memory;
	size_t block_size;
	int is_allocated;
	
	struct mem_list *next;
};

mem_list *best_fit_root;
mem_list *worst_fit_root;

unsigned byte *best_fit_mem;
unsigned byte *worst_fit_mem;

/* Functions */

/* memory initializer */
int best_fit_memory_init(size_t size)
{
	// To be completed by students
	// You call malloc once here to obtain the memory to be managed.
	
	if (size == 0 || size % 4 != 0)
		return -1;
	else {
		mem = malloc( size * sizeof(byte) );
		
		best_fit_root = malloc(sizeof (struct mem_list));
		
		best_fit_root->address_location = (int*) best_fit_mem;
		best_fit_root->allocated_memory = sizeof (struct mem_list);
		best_fit_root->block_size = size / 4;
		best_fit_root->is_allocated = 0;
		best_fit_root->next = NULL;
	}
	
	return 0;
}

int worst_fit_memory_init(size_t size)
{

	// To be completed by students
	// You call malloc once here to obtain the memory to be managed.
	return 0;

}

/* memory allocators */
void *best_fit_alloc(size_t size)
{
	if (size <= 0 || size > )
	// To be completed by students
	return NULL;
}


void *worst_fit_alloc(size_t size)
{
	// To be completed by students
	return NULL;
}

/* memory de-allocator */
void best_fit_dealloc(void *ptr) 
{

	// To be completed by students
	return;
}

void worst_fit_dealloc(void *ptr) 
{

	// To be completed by students
	return;
}

/* memory algorithm metric utility function(s) */

/* count how many free blocks are less than the input size */ 
int best_fit_count_extfrag(size_t size)
{
	// To be completed by students
	return 0;
}

int worst_fit_count_extfrag(size_t size)
{
	// To be completed by students
	return 0;
}
