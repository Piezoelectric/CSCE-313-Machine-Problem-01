/* --------------------------------------------------------------------------- */
/* Developer: Andrew Kirfman, Margaret Baxter                                  */
/* Project: CSCE-313 Machine Problem #1                                        */
/*                                                                             */
/* File: ./MP1/Part_2/main.cpp                                                 */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/* Standard Library Includes                                                   */
/* --------------------------------------------------------------------------- */
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <climits>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

/* --------------------------------------------------------------------------- */
/* User Defined Includes                                                       */
/* --------------------------------------------------------------------------- */

#include "linked_list2.h"

int main(int argc, char ** argv) 
{	
	int opt;
	int b=NULL;
	int M=NULL;
	int t = NULL;
	while((opt= getopt(argc, argv, "b:m:t:"))!=-1)
	{
		switch (opt){
			case 'b':
				 b= atoi(optarg);
				break;
			case 'm':
				 M=atoi(optarg);
				break;
			case 't':
				t=atoi(optarg);
		}
	}			
	
	char buf [1024];
	memset (buf, 1, 1024);		// set each byte to 1
	
	char * msg = "a sample message";
	
	// Instantiate the tiered list class
	linked_list2 *test_list = new linked_list2;
	
	test_list->Init(M, b, t); // initialize
	// test operations
	int testnums [] = {0, 1<<29 , (1<<29) + 5 , 50, (1<<30) + 5, (1<<30) - 500};
	int i = 0;
	// some sample insertions
	for (i=0; i< 6; i ++)
	{
		test_list->Insert (testnums [i], msg, 50);   // insert 50 bytes from the buffer as value for each of the insertions
	}
	
	test_list->PrintList();
		
	// end test operations	
	//test_list->Destroy();
	
}
