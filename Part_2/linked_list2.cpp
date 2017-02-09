/* --------------------------------------------------------------------------- */
/* Developer: Andrew Kirfman, Margaret Baxter                                  */
/* Project: CSCE-313 Machine Problem #1                                        */
/*                                                                             */
/* File: ./MP1/linked_list2.cpp                                                */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/* Standard Library Includes                                                   */
/* --------------------------------------------------------------------------- */

#include <iostream>
#include <string.h>
#include <climits>

/* --------------------------------------------------------------------------- */
/* User Defined Includes                                                       */
/* --------------------------------------------------------------------------- */

#include "linked_list2.h"

linked_list2::linked_list2()
{	
}

void linked_list2::Init(int M, int b, int t)
{
	setMemSize(M);
	setBlockSize(b);
	setNumTiers(t);
	setMaxDataSize(block_size-sizeof(node*));
	
  setHeadPointer((char**) malloc(M));
	
	//allocate memory
	for(int i=0; i< getNumTiers(); i++){
		//head_pointer[i]= (char*) malloc(M*t); why does this work?!
		head_pointer[i]= (char*) malloc(M/t);
	}
	
	free_data_pointer = new node*[t];
	free_pointer = new node*[t];
	front_pointer = new node*[t];
	
	for(int j=0; j< getNumTiers(); j++){
		free_data_pointer[j] = reinterpret_cast<node*> (head_pointer[j]);
		free_pointer[j] = nullptr;
		front_pointer[j] = nullptr;
	}

	setInitialized(true);
	
}


void linked_list2::Destroy()
{
	for(int i=0; i< getNumTiers();i++){
		free(head_pointer[i]);
		head_pointer[i]= nullptr;
		front_pointer[i] = nullptr;
		free_pointer[i] = nullptr;
		free_data_pointer[i]= nullptr;
	}
	
	free(head_pointer);
	setHeadPointer(nullptr);
	setInitialized(false);
}

void linked_list2::Insert(int k,char * data_ptr, int data_len)
{
	int key_tier = Find_tier(k);
	if(front_pointer[key_tier]==NULL){
		front_pointer[key_tier] = reinterpret_cast<node*> (head_pointer[key_tier]);
		free_pointer[key_tier] = front_pointer[key_tier];
		free_data_pointer[key_tier] = free_pointer[key_tier]+ getBlockSize();
	}
	else{
		node* prev = free_pointer[key_tier];
		free_pointer[key_tier] = free_data_pointer[key_tier];
		prev->next = free_pointer[key_tier];
		
		if(free_data_pointer[key_tier]->next == nullptr){
			free_data_pointer[key_tier] += getBlockSize();
		}
		else{
			free_data_pointer[key_tier]= free_data_pointer[key_tier]->next;
		}
		
	}	
	free_pointer[key_tier]->next = nullptr;
	free_pointer[key_tier]->key = k;
	free_pointer[key_tier]->value_len = data_len;
	memcpy(free_pointer[key_tier]+ 1, data_ptr, data_len);
	
}

int linked_list2::Delete(int delete_key)
{
	//check if key exists
	node* q = Lookup(delete_key);
	
	if(q != NULL) {
		int key_tier = Find_tier(delete_key);
		
		node* prev_node; //node before q
		node* next_node; //node after q
		
		//find the next_node
		next_node = q->next;
		
		//find the prev_node
		prev_node = front_pointer[key_tier];
		
		//special case: q is the first of the tier
		if (prev_node == q) {
			front_pointer[key_tier] = next_node;
		}
		else {
			//reassign links
			prev_node->next = next_node;
		}
		
		//memmove-same as the one in part 1
		/*void* dest = q;
		void* source = next_node;
		size_t temp_mem_length = (free_pointer[key_tier] - next_node);
		memmove(dest, source, temp_mem_length);*/
		
		return 0;
	}
	else {
		return 1; //treat 0 as default 
	}
}

node* linked_list2::Lookup(int lookup_key)
{
	int key_tier = Find_tier(lookup_key);
	node* h = front_pointer[key_tier];
	
	//code from part 1
	if(h == NULL){
		return NULL;
	}
	for (int i = 0; i < max_data_size; i++)
	//Here I make the assumption that each tier is size m,
	//so that I can use max_data_size as the number of blocks in the tier. TODO verify
	{
		if (h->key == lookup_key) { return h; }
		else if (h->next == NULL) { return NULL;}
		else { h = h->next; }
	}
	return NULL;
}
//Well it doesn't segfault so that's a plus

void linked_list2::PrintList()
{
	
	/* IMPORTANT NOTE!
	 * 
	 * In order for the script that will grade your assignment to work 
	 * (i.e. so you get a grade higher than a 0),
	 * you need to print out each member of the list using the format below.  
	 * Your print list function should be written as a while loop that prints 
	 * the tier of the list and then each node underneath it.  
	 * the following four lines exactly for each node and nothing else.  If
	 * you have any difficulties, talk to your TA and he will explain it further. 
	 * 
	 * The output lines that you should use are provided so that you will know
	 * exactly what you should output.  
	 */ 
	// Do this for every tier
	// std::cout << "Tier " << <TIER NUMBER GOESHERE> << std::endl;
	
	// Do this for every node 
	//std::cout << "Node: " << std::endl;
	//std::cout << " - Key: " << <KEY GOES HERE!> << std::endl;
	//std::cout << " - Data: " << <KEY GOES HERE!> << std::endl;
	
	/* Short example:
	 *   - Assume a list with two tiers each with two elements in each tier.  
	 *     the print out would appear as follows
	 * 
	 * Tier 0
	 * Node: 
	 *  - Key: 1
	 *  - Data: Hello
	 * Node:
	 *  - Key: 2
	 *  - Data: World!
	 * Tier 1
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
	for(int i=0; i< getNumTiers(); i++){
	node* h = reinterpret_cast<node*> (front_pointer[i]);
	if(h!=NULL){
		 std::cout << "Tier " << i << std::endl;
		while (true)
		{	
			std::cout << "Node: " << std::endl;
			std::cout << " - Key: " << h->key << std::endl;
			std::cout << " - Data: ";
			char* data = reinterpret_cast<char*> (h);
			data = data + sizeof(node);
			std::cout<< data;	
			std::cout<< std::endl;
			if(h->next == NULL){
				break;
			}
			h = h->next;


		}
	}
	}
}

int linked_list2::Find_tier(int key)
{
	int tier = key * ((double)num_tiers / INT_MAX);
	return tier;
}

/* Getter Functions */
char** linked_list2::getHeadPointer()
{
	return head_pointer;
}

node** linked_list2::getFrontPointer()
{
	return front_pointer;
}

node** linked_list2::getFreePointer()
{
	return free_pointer;
}

node** linked_list2::getFreeDataPointer()
{
	return free_data_pointer;
}

int linked_list2::getBlockSize()
{
	return block_size;
}

int linked_list2::getMemSize()
{
	return mem_size;
}

int linked_list2::getMaxDataSize()
{
	return max_data_size;
}

int linked_list2::getNumTiers()
{
	return num_tiers;
}

int linked_list2::getInitialized()
{
	return initialized;
}

/* Setter Functions */
void linked_list2::setHeadPointer(char** new_head_pointer)
{
	head_pointer = new_head_pointer;
}

void linked_list2::setFrontPointer(node** new_front_pointer)
{
	front_pointer = new_front_pointer;
}

void linked_list2::setFreePointer(node** new_free_pointer)
{
	free_pointer = new_free_pointer;
}

void linked_list2::setFreeDataPointer(node** new_free_data_pointer)
{
	free_data_pointer = new_free_data_pointer;
}

void linked_list2::setBlockSize(int new_block_size)
{
	block_size = new_block_size;
}

void linked_list2::setMemSize(int new_mem_size)
{
	mem_size = new_mem_size;
}

void linked_list2::setMaxDataSize(int new_max_data_size)
{
	max_data_size = new_max_data_size;
}

void linked_list2::setNumTiers(int new_num_tiers)
{
	num_tiers = new_num_tiers;
}

void linked_list2::setInitialized(bool new_initialized)
{
	initialized = new_initialized;
}
