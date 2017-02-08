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
	
	
   setHeadPointer((char**) malloc(M*t));
	
	//allocate memory
	for(int i=0; i< getNumTiers(); i++){
		
		head_pointer[i]= (char*) malloc(M*t);
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

/*ptr node | data node | data node |data
data+node
node can be done by +1
but side of data has to be determined size(data) =5 cant just +5 it is 5 chars*/
int linked_list2::Delete(int delete_key)
{
	return 0;
}

node* linked_list2::Lookup(int lookup_key)
{
	return NULL;
}

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
	int num_bigger_tiers = INT_MAX%num_tiers;
    int tier_size = INT_MAX/num_tiers;

    int extra = 0;
    int tier_bound = tier_size;

    //This will = 1 for as many tiers that should be one larger
    if(num_bigger_tiers > 0)
    {
        extra = 1;
    }

    for (int i = 0; i < num_tiers; i++)
    {
        tier_bound += extra;
        if(key <= tier_bound + extra)
        {
            return i;
        }

        //move bound up to max key values of the next region
        tier_bound += tier_size;

        if(num_bigger_tiers - i > 0)
        {
            extra = 1;
        }
        else
        {
            extra = 0;
        }

        tier_bound += extra;

    }
    return -1;
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
