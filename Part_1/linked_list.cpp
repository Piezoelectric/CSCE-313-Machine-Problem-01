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
	//Because list is empty, the free data pointer is the head_pointer
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
{	char* c = head_pointer;
	node* n = reinterpret_cast<node*> (head_pointer);
	
	/* removed the for loop that was here. -GH */
	
	//insert values
	free_data_pointer->key = k;
	free_data_pointer->value_len=data_len;
	
	//move location of copied data to be shifted by the size of the node
	data_ptr = reinterpret_cast<char*>(free_data_pointer);
	memcpy(data_ptr+sizeof(node),data_ptr, data_len);
	
	//non-empty list
	if(front_pointer != NULL){
		free_pointer->next = free_data_pointer; 
		free_pointer = free_pointer->next;
		if(free_data_pointer->next ==NULL){
			free_data_pointer = NULL;
		}
		else{
			free_data_pointer = free_data_pointer->next;
		}
		free_pointer->next = NULL;
	}
	//empty list
	else{
		front_pointer = free_data_pointer;
		free_pointer = front_pointer;
		
		if(free_data_pointer->next == NULL){
			free_data_pointer = NULL;
		}
		else{
			free_data_pointer = free_data_pointer->next;
		}
		free_pointer->next = NULL;
	}
}


int linked_list::Delete(int delete_key)
{
	node* search_result = Lookup(int delete_key); 
	if (search_result != NULL) {
		
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
		
		//delete
		
		//fill the gap in memory with memcpy (BONUS--TODO?)
	}
	else {
		std::cout << "ERROR: key was not found."
	}
}

/* Iterate through the list, if a given key exists, return the pointer to its node */
/* otherwise, return NULL                                                           */
struct node* linked_list::Lookup(int lookup_key)
{
	node* h = front_pointer;
	if(h == NULL){
		return NULL;
	}
	for (int i = 0; i < max_data_size; i++)
	{
		if (h->key == lookup_key) { return h; }
		if (h->next == NULL) { return NULL;}
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
	
	node* h = front_pointer;
	while (h->next)
	{
		std::cout << "Node: " << std::endl;
		std::cout << " - Key: " << h->key << std::endl;
		std::cout << " - Data: " << "TODO: What is a value?" << std::endl;
		h = h->next;
	}
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
