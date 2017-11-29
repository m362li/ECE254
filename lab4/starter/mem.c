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
- ordered linked list data structure by starting address
- last node is always unallocated memory whose starting address is the closest, or is, the range of memory

*/
struct mem_list{
	size_t* address_location;
	size_t memory_occupied;
	int is_allocated;
	
	struct mem_list *previous;
	struct mem_list *next;
};

mem_list best_fit_root;
mem_list worst_fit_root;

unsigned byte *best_fit_mem;
unsigned byte *worst_fit_mem;

size_t best_fit_mem_bytes;
size_t worst_fit_mem_bytes;

/* Functions */

/* memory initializer */
int best_fit_memory_init(size_t size)
{
	// To be completed by students
	// You call malloc once here to obtain the memory to be managed.
	
	if (size == 0 || size % 4 != 0)
		return -1;
	else {
		mem = malloc( size * sizeof(unsigned byte) );
		best_fit_mem_bytes = size;
		best_fit_root = { (size_t*) best_fit_mem, size, 0, NULL, NULL};
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
	mem_list current_node = best_fit_root;

	while (current_node != NULL) {
		size_t *starting_address;
		size_t blocks_to_occupy = (size / 4) + 1;
		mem_list *next_temp;
		mem_list *previous_temp;
		mem_list new_node;
 
		if (!current_node->is_allocated) {
			if (current_node->previous == NULL && current_node->next == NULL) {
				starting_address = current_node->starting_address;

				new_node = { starting_address, size, 1, NULL, &current_node };
				
				current_node->stating_address = starting_address + blocks_to_occupy;
				current_node->memory_occupied = best_fit_mem_bytes - (blocks_to_occupy * 4);
				current_node->previous = new_node;

				return starting_address;
			}
			if (current_node->previous != NULL && current_node->next != NULL) {
				size_t mem_available = (next_temp->starting_address - current_node->starting_address) * 4;

				if (size <= mem_available) {
					current_node->memory_occupied = size;
					current_node->blocks_occupied = blocks_to_occupy;
					current_node->is_allocated = 1;
				}
			}
		}

		current_node = *(current_node->next);
	}

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
