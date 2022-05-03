/*****************************************
 * query.h 
 * Interface for processing commands from input file
 * Josias Moukpe
 ****************************************/


#ifndef QUERY_H
#define QUERY_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"
#include "sllist.h"



/*******************************
 * METHODS PROTOTYPES
 ******************************/

void buildGraph(Graph* network, SLList* friendships);
void processQuery(Graph* network, SLList* query_list);
void AddFriendship(Graph* network, char* user1, char* user2);
void RemoveFriendship(Graph* network, char* user1, char* user2);
void WantToBefriend(Graph* network, char* user1, char* user2);


/************************************************
 * METHODS IMPLEMENTATION
 ***********************************************/


/* adds edge between two user vertices */
void AddFriendship(Graph* network, char* user1, char* user2){
    printf("AddFriendship %s %s ", user1, user2);
    Vertex* user1_vertex = searchUser(network->vertices, user1);
    Vertex* user2_vertex = searchUser(network->vertices, user2);
    addEdge(user1_vertex, user2_vertex);
    printf("\n");
}

/* remove edge between two user vertices */
void RemoveFriendship(Graph* network, char* user, char* target) {
    printf("RemoveFriendship %s %s ", user, target);
    Vertex* user_vertex = searchUser(network->vertices, user);
    Vertex* target_vertex = searchUser(network->vertices, target);

    removeEdge(user_vertex, target_vertex);
    printf("\n");
    return;
}

/* use an intermediate friend to create a new friendship */
void WantToBefriend(Graph* network, char* user1, char* user2) {
    printf("WantToBefriend %s %s ", user1, user2);
    Vertex* user1_vertex = searchUser(network->vertices, user1);
    Vertex* user2_vertex = searchUser(network->vertices, user2);

    if(isAdjacent(user1_vertex, user2_vertex)) {
        printf("AlreadyAFriendError");
        return;
    }

   
    
    
    #ifdef HW6EC1
    SLList* paths = shortestPaths(network, user1_vertex, user2_vertex);
    SLList* path;
    if(paths != NULL) {
        printf("\n- Length of shortest path: %d", ((SLList*)paths->head->data)->size - 1);
        for(Node* p = paths->head; p != NULL; p = p->next) {
            path = (SLList*)p->data;
            printf("\n- Your %s friend is %s.", ((path->size == 3)?"mutual":"intermediate"),(char*)getAt(path, 1));
            printf("\n- Path: "); printlist(path);
            // printf("\n");
        }
    }
    #endif

    #ifdef HW6
    SLList* path = shortestPath(network, user1_vertex, user2_vertex);
    if(path != NULL) {
        printf("\n- Length of shortest path: %d\n", path->size - 1);
        printf("- Your %s friend is %s.\n", ((path->size == 3)?"mutual":"intermediate"),(char*)getAt(path, 1));
        printf("- Path: "); printlist(path);
    }
    #endif

    else printf("- Sorry, none of your friends can help introduce you to %s.", user2);
    printf("\n");
}


/* build a network graph based a friendship pairs */
void buildGraph(Graph* network, SLList* friendships) {

    char* user1_name = (char*)getAt(friendships, 0);
    char* user2_name = (char*)getAt(friendships, 1);

    
    Vertex *user1 = NULL, *user2 = NULL;
    if(searchUser(network->vertices, user1_name) == NULL) {
        user1 = initVertex(user1_name);
        addVertex(network, user1);
    } else {
        user1 = searchUser(network->vertices, user1_name);
    }
    if(searchUser(network->vertices, user2_name) == NULL) {
        user2 = initVertex(user2_name);
        addVertex(network, user2);
    } 
    else {
        user2 = searchUser(network->vertices, user2_name);
    }

    addEdge(user1, user2);
}   


/* Executes actions from the actions file */ 
void processQuery(Graph* network, SLList* query_list) {
    if(!strcmp((char*)getAt(query_list, 0), "AddFriendship")) 
        AddFriendship(network, (char*)getAt(query_list, 1), (char*)getAt(query_list, 2));
    else if(!strcmp((char*)getAt(query_list, 0), "RemoveFriendship")) 
        RemoveFriendship(network, (char*)getAt(query_list, 1), (char*)getAt(query_list, 2));
    else if(!strcmp((char*)getAt(query_list, 0), "WantToBefriend")) 
        WantToBefriend(network, (char*)getAt(query_list, 1), (char*)getAt(query_list, 2));
    else 
        printf("Invalid command!\n");
    destroyList(query_list);
}

#endif // QUERY_H