/* --------------------------------------------------------------------------- */
/* Developer: Andrew Kirfman, Margaret Baxter                                  */
/* Project: CSCE-313 Machine Problem #1                                        */
/*                                                                             */
/* File: ./MP1/linked_list.cpp                                                 */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/* User Defined Includes                                                       */
/* --------------------------------------------------------------------------- */

#include "linked_list.h"
#include <cstdint>
#include <algorithm>
#include <iterator>

/* Constructor */
linked_list::linked_list()
: front_pointer(nullptr)
, free_pointer(nullptr)
, free_data_pointer(nullptr)
{
	
}


void linked_list::Init(int M, int b)
{
	//set properties of the constructed linked list
	setHeadPointer( (char*) malloc(M));
	setBlockSize(b);
	setMemSize (M);
	//Max Data size is the size of the block minus the size of the head
	setMaxDataSize(b - sizeof(node));
	//Because list is empty the free data pointer is the head_pointer
	free_data_pointer = reinterpret_cast<node*>(head_pointer);
	initialized = true;
}

void linked_list::Destroy()
{	//free used data
	free(head_pointer);
	
	//reset pointers
	setHeadPointer(nullptr);
	setFrontPointer(nullptr);
	setFreePointer(nullptr);
	setFreeDataPointer(nullptr);
	setInitialized(true);
} 

/* Insert an element into the list with a given key, given data element, and with a given length*/
void linked_list::Insert (int k, char * data_ptr, int data_len)
{	
	if (data_len > getMaxDataSize() ) {
		std::cout << "Error: could not insert because the provided data_len " 
		          << std::to_string(data_len) << " is larger than the max data size, "
		          << std::to_string(getMaxDataSize()) << std::endl;
	}
	else { 
		if(front_pointer == nullptr) { //empty list
			front_pointer = reinterpret_cast<node*> (head_pointer);
			free_pointer = front_pointer;
			free_data_pointer = front_pointer + getBlockSize();
		}
		else {
			node * prev = free_pointer;
			free_pointer = free_data_pointer;
					prev->next = free_pointer;
			
			if (free_data_pointer->next == nullptr) {
				
				free_data_pointer += getBlockSize();
			}
			else {
				free_data_pointer = free_data_pointer->next;
			}	
		}
	
		free_pointer->next = nullptr;
		free_pointer->key = k;
		free_pointer->value_len = data_len;
		memcpy(free_pointer + sizeof(node), data_ptr,data_len);
	}
}


int linked_list::Delete(int delete_key)
{
	node* search_result = Lookup(delete_key); 
	if (search_result != nullptr) {
		
		//retrieve the node that is before the node-to-be-deleted
		node* prev_node = getFrontPointer();
		for (int i = 0; i < getMaxDataSize(); i++)
		{
			if (prev_node->next == search_result) { break; }
			else if (prev_node == search_result) { std::cout << "DEBUG: prev_node == search_result\n"; }
			else { prev_node = prev_node -> next; }
		}
		
		//reassign links that will be broken
		node* next_node = search_result->next;
		prev_node -> next = next_node;
		
		//fill the gap in memory with memcpy (BONUS--TODO?)
		void* dest = search_result;
		void* source = next_node;
		size_t temp_mem_length = (getFreePointer() - next_node);
		
		memmove(dest, source, temp_mem_length);
		//http://man7.org/linux/man-pages/man3/memmove.3.html
		
	}
	else {
		std::cout << "ERROR: delete_key " << std::to_string(delete_key)
		          << " was not found through Lookup.\n";
	}
}

/* Iterate through the list, if a given key exists, return the pointer to it's node */
/* otherwise, return NULL                                                           */
struct node* linked_list::Lookup(int lookup_key)
{
	node* h = front_pointer;
	if(h==NULL){
		return NULL;
	}
	for (int i = 0; i < max_data_size; i++)
	{
		if (h->key == lookup_key) { return h; }
		if(h->next==NULL){return NULL;}
		else { h = h->next; }
	}
	return NULL;
}

/* Prints the list by printing the key and the data of each node */
void linked_list::PrintList()
{
	
	/* IMPORTANT NOTE!
	 * 
	 * In order for the script that will grade your assignment to work 
	 * (i.e. so you get a grade higher than a 0),
	 * you need to print out each member of the list using the format below.  
	 * Your print list function should be written as a while loop that prints
	 * the following three lines exactly for each node and nothing else.  If
	 * you have any difficulties, talk to your TA and he will explain it further.  
	 * 
	 * The output lines that you should use are provided so that you will know
	 * exactly what you should output.  
	 */ 
	//std::cout << "Node: " << std::endl;
	//std::cout << " - Key: " << <KEY GOES HERE!> << std::endl;
	//std::cout << " - Data: " << <KEY GOES HERE!> << std::endl;
	
	/* Short example:
	 *   - Assume that you have a list with 4 elements.  
	 *     Your output should appear as follows
	 * 
	 * Node:
	 *  - Key: 1
	 *  - Data: Hello
	 * Node:
	 *  - Key: 2
	 *  - Data: World!
	 * Node:
	 *  - Key: 3
	 *  - Data: Hello
	 * Node:
	 *  - Key: 4
	 *  - Data: World!
	 * 
	 * ^^ Your output needs to exactly match this model to be counted as correct.  
	 * (With the exception that the values for key and data will be different 
	 * depending on what insertions you perform into your list.  The values provided
	 * here are for pedagogical purposes only)
	 */
	
	
}

/* Getter Functions */
char* linked_list::getHeadPointer()
{
	return head_pointer;
}

node* linked_list::getFrontPointer()
{
	return front_pointer;
}

node* linked_list::getFreePointer()
{
	return free_pointer;
}

node* linked_list::getFreeDataPointer()
{
	return free_data_pointer;
}

int linked_list::getBlockSize()
{
	return block_size;
}

int linked_list::getMemSize()
{
	return mem_size;
}

int linked_list::getMaxDataSize()
{
	return max_data_size;
}

bool linked_list::getInitialized()
{
	return initialized;
}

/* Setter Functions */
void linked_list::setHeadPointer(char *new_pointer)
{
	head_pointer = new_pointer;
}

void linked_list::setFrontPointer(node* new_pointer)
{
	front_pointer= new_pointer;
}

void linked_list::setFreePointer(node* new_pointer)
{
	free_pointer = new_pointer;
}

void linked_list::setFreeDataPointer(node* new_pointer)
{
	free_data_pointer= new_pointer;
}

void linked_list::setBlockSize(int new_block_size)
{
	block_size = new_block_size;
}

void linked_list::setMemSize(int new_mem_size)
{
	mem_size = new_mem_size;
}

void linked_list::setMaxDataSize(int new_max_data_size)
{
	max_data_size = new_max_data_size;
}

void linked_list::setInitialized(bool new_initialized)
{
	initialized = new_initialized;
}
