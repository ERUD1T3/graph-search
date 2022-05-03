/************************************
 * GRAPH INTERFACE FOR HW6
 * Josias Moukpe
 ************************************/ 
#ifndef GRAPH_H
#define GRAPH_H 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sllist.h"

typedef unsigned int uint;
typedef struct vertex Vertex; 
typedef struct edge Edge;
typedef struct graph Graph; 


struct edge
{
    uint weight;
    Vertex* left;
    Vertex* right;
};



struct vertex 
{
    bool is_visited;
    void* data;
    // char* data;
    SLList* adj_nodes;
    Vertex* par; // previous vertex in BFS
};

struct graph
{
    // uint size;
    SLList* vertices;
    SLList* edges;  
};


/********************************
 * PROTOTYPE METHODS
 *******************************/

Vertex* initVertex(void* data);
Graph* initGraph();
void addVertex(Graph* graph, Vertex* vertex);
void removeVertex(Graph* graph, Vertex* vertex);
void addEdge(Vertex* vertex1, Vertex* vertex2);
void removeEdge(Vertex* vertex1, Vertex* vertex2);
Vertex* searchUser(SLList* userlist, char* name); // TODO: improve using binary search
void deleteAdj(SLList* adjlist, char* name); // TODO: improve using binary search
void printVertices(SLList* vertices);
void insortVertex(SLList* List,  void* data);
bool isAdjacent(Vertex* src, Vertex* target);
void destroyGraph();
void setAllVerticesToUnvisited(Graph* graph);
SLList* shortestPath(Graph* graph, Vertex* src, Vertex* dest);
SLList* shortestPaths(Graph* graph, Vertex* src, Vertex* dest);

SLList* shortestWeightedPaths(Graph* wgraph, Vertex* src, Vertex* dest);
SLList* shortestWeightedPath(Graph* wgraph, Vertex* src, Vertex* dest);
Edge* initEdge(Graph* graph, Vertex* v1, Vertex* v2, uint weight); // initialize edge and add it to graph
uint weight(Graph* graph, Vertex* v1, Vertex* v2);

/********************************
 * METHODS IMPLEMENTATION
 *******************************/ 
 
/* initialize edge and add it to graph */
Edge* initEdge(Graph* graph, Vertex* left, Vertex* right, uint weight) {
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->left = left;
    new_edge->right = right;
    new_edge->weight = weight;
    pushback(graph->edges, new_edge);
    return new_edge;
}

uint weight(Graph* graph, Vertex* v1, Vertex* v2) {
    for(Node* e = graph->edges->head; e != NULL; e = e->next) {
        Edge* edge = (Edge*)e->data;
        if((edge->left == v1 && edge->right == v2) || 
        (edge->left == v2 && edge->right == v1)) {
            return edge->weight;
        }
    }
    return 0;
}

/* insert a node with data at index */
void insortVertex(SLList* List,  void* data) {
    Node* new_node = initNode(data);
    if(List->size == 0) { //case 1: empty list
        List->head = new_node;
        new_node->next = NULL;
    } 
    else 
    if(strcmp((char*)((Vertex*)List->head->data)->data, (char*)((Vertex*)data)->data) > 0) { // inserting before the head
        new_node->next = List->head;
        List->head = new_node;
    }   
    else { // case 3: insert sort

        Node* prev = List->head;
        while(prev->next != NULL && 
        (strcmp((char*)((Vertex*)prev->next->data)->data, (char*)((Vertex*)data)->data) < 0)) 
            prev = prev->next;
        new_node->next = prev->next;
        prev->next = new_node;
    }
    ++List->size;
}


/* return the node previous to the found node */
void deleteAdj(SLList* adjlist, char* name) {
    // printf("name is delete is %s", name);
    if(adjlist->size == 0) {
        printf("empty list");
        return;
    }
    Node* to_del = NULL, *prev = NULL;
    char* to_comp = (char*)((Vertex*)adjlist->head->data)->data;
    if(!strcmp(to_comp, name)) {
        // printf("name is %s, to_comp is %s", name, to_comp);
        to_del = adjlist->head;
        adjlist->head = to_del->next;
        free(to_del);
        return;
    }
    for(Node* curr = adjlist->head; curr->next != NULL; curr = curr->next) {
        char* to_comp = (char*)((Vertex*)curr->next->data)->data;
        // printf("\nname: %s vs to_comp: %s", name, to_comp);
        if(!strcmp(to_comp, name)) {
            prev = curr;
            to_del = curr->next;
            break;
        }
    }

    prev->next = to_del->next;
    free(to_del);
}


/* removes edge between two vertices */
void removeEdge(Vertex* vertex1, Vertex* vertex2) {
    if(!isAdjacent(vertex1, vertex2) || !isAdjacent(vertex2, vertex1)) 
    {
        printf("No FriendshipError");
        return;
    }

    deleteAdj(vertex1->adj_nodes, (char*)vertex2->data);
    deleteAdj(vertex2->adj_nodes, (char*)vertex1->data);
    
}

/* returns true if target is adjacent to source */
bool isAdjacent(Vertex* src, Vertex* target) {
    for(Node* curr = src->adj_nodes->head; curr != NULL; curr = curr->next) {
        char* to_comp = (char*)((Vertex*)curr->data)->data;
        // printf("\nname: %s vs to_comp: %s", name, to_comp);
        if(!strcmp(to_comp, (char*)target->data)) return true;
          
    }
    return false;
}


/* clear graph memory */
void destroyGraph() {
    return;
}



/* searches the graph for a user and return the pointer of its vertex if found and NULL otherwise */
Vertex* searchUser(SLList* userlist, char* name) {
    for(Node* curr = userlist->head; curr != NULL; curr = curr->next) {
        char* to_comp = (char*)((Vertex*)curr->data)->data;
        if(!strcmp(to_comp, name)) return (Vertex*)curr->data;
          
    }
    return NULL;
}


/* initialize a new graph node with data param and an empty list of adjacent nodes */
Vertex* initVertex(void* data) {
    Vertex* new_node = (Vertex*)malloc(sizeof(Vertex));
    new_node->data = data;
    new_node->is_visited = false;
    new_node->adj_nodes = initList(); 
    new_node->par = NULL;
    return new_node;
}


/* initialized a graph with size = 0 and empty list of vertices */
Graph* initGraph() {
    Graph* new_graph = (Graph*)malloc(sizeof(Graph));
    // new_graph->size = 0;
    new_graph->vertices = initList();
    new_graph->edges = initList();
    return new_graph;
}

/* add new egde between two vertices */
void addEdge(Vertex* vertex1, Vertex* vertex2) {
    if(isAdjacent(vertex1, vertex2) || isAdjacent(vertex2, vertex1)) 
    {
        printf("ExistingFriendshipError");
        return;
    }
    insortVertex(vertex2->adj_nodes, vertex1);
    insortVertex(vertex1->adj_nodes, vertex2);
}


/* add a new vertex to the graph */
void addVertex(Graph* graph, Vertex* vertex) {
    insortVertex(graph->vertices, vertex);
}

/* print vertices in a graph */
void printVertices(SLList* vertices) {
    if(vertices == NULL || vertices->size == 0 ) {
        printf("empty list");
        return;
    }

    if(vertices->size != 0) {
        for(Node* tmp = vertices->head; tmp != NULL; tmp = tmp->next) {
            char* to_print = (char*)((Vertex*)tmp->data)->data;
            printf("%s ", to_print);
        }
    }
}

/* return a pointer to the shortest path */
SLList* shortestPath(Graph* graph, Vertex* src, Vertex* dest) {
    Vertex* curr = NULL;
    SLList* queue = initList();
    SLList* path = NULL; 

    
    setAllVerticesToUnvisited(graph);
    src->par = NULL;
    pushback(queue, src);
    while(queue->size != 0) {
        curr = (Vertex*)popfront(queue);
        if(!(curr->is_visited)) {
            curr->is_visited = true;
            SLList* neighbors = curr->adj_nodes;
            for(Node* neigh = neighbors->head; neigh!= NULL; neigh = neigh->next) {
                Vertex* adj = (Vertex*)neigh->data;
                if(!(adj->is_visited)) {
                    adj->par = curr;
                    if(!strcmp((char*)adj->data, (char*)dest->data)) {
                        path = initList();
                        for(Vertex* tmp = adj; tmp != NULL; tmp = tmp->par) pushfront(path, tmp->data);
                        return path;
                    }
                    pushback(queue, adj);
                }
            }
        }
    }
    return path;
}


/* return a pointer to the list of shortest paths */
SLList* shortestPaths(Graph* graph, Vertex* src, Vertex* dest) {
    Vertex* curr = NULL;
    SLList* queue = initList();
    SLList* path = NULL, *paths = initList(); 

    
    setAllVerticesToUnvisited(graph);
    src->par = NULL;
    pushback(queue, src);
    while(queue->size != 0) {
        curr = (Vertex*)popfront(queue);
        if(!(curr->is_visited)) {
            curr->is_visited = true;
            SLList* neighbors = curr->adj_nodes;
            for(Node* neigh = neighbors->head; neigh!= NULL; neigh = neigh->next) {
                Vertex* adj = (Vertex*)neigh->data;
                if(!(adj->is_visited)) {
                    adj->par = curr;
                    if(!strcmp((char*)adj->data, (char*)dest->data)) {
                        path = initList();
                        for(Vertex* tmp = adj; tmp != NULL; tmp = tmp->par) pushfront(path, tmp->data);
                        // return path;
                        pushback(paths, path);
                    }
                    pushback(queue, adj);
                }
            }
        }
    }
    return ((paths->size == 0)?NULL:paths);
}


/* set all the vertices in the graph to unvisited */
void setAllVerticesToUnvisited(Graph* graph) {
    for(Node* tmp = graph->vertices->head; tmp != NULL; tmp = tmp->next) {
            ((Vertex*)tmp->data)->is_visited = false;
    }
}

/* finds shortest path in a weighted graph using djikstra alg */
SLList* shortestWeightedPath(Graph* wgraph, Vertex* src, Vertex* dest) {
    // 
}

/* finds shortest paths (if multiple paths are available) in a weighted graph using djikstra alg */
SLList* shortestWeightedPaths(Graph* wgraph, Vertex* src, Vertex* dest) {
    // 
}
#endif // GRAPH_H