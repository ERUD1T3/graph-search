/*

  Author: Josias Moukpe 
  Email: jmoukpe2016@my.fit.edu
  Course: cse2010
  Section: 14b
  Description: graph to manage friendships in social network

*/

#define HW6EC1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sllist.h"
#include "graph.h"
#include "query.h"

int main(int argc, char** argv) 
{

  FILE* ffriends = fopen(argv[1], "r"); // pointer data query files
  FILE* factions = fopen(argv[2], "r"); // pointer to query files
  
  
  if(factions == NULL ) 
  { // exits with failure if program fails to open data file
    printf("\nError: failed to open actions file.\n");
    exit(EXIT_FAILURE);
  }

  if(ffriends == NULL ) 
  { // exits with failure if program fails to open data file
    printf("\nError: failed to open fiends file.\n");
    exit(EXIT_FAILURE);
  }

  // Reading file inputs
  size_t len = 0; // keeps track of the length of the lines
  char* input_line = NULL;  // the input line charracter array  
  SLList* action = NULL; 
  SLList* friendship = NULL;
  uint number_of_users = getline(&input_line, &len, ffriends); // reading the first line 
  Graph* network = initGraph();


  // loop while not the end of the input file
  while(getline(&input_line, &len, ffriends) != EOF) {
    friendship = parseWords(input_line); // converts input line into sllist of words
    buildGraph(network, friendship);
  }

  printf("\n");

  // loop while not the end of the input file
  while(getline(&input_line, &len, factions) != EOF) {
    action = parseWords(input_line); // converts input line into sllist of words
    processQuery(network, action); // process the sllist of words in cmds
  }
  

  // destroyGraph();
  fclose(factions);
  fclose(ffriends);
  return EXIT_SUCCESS;
  
}

