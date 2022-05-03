//Copyright to Josias Moukpe, 2019

#ifndef CLINKEDLIST_H
#define CLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct node {
    /*
    * Node for single linked list structure
    */
    int data; //data contained in node
    struct node* next; //pointer to next node

} Node;

typedef struct {
    /*
    * Single Linked List struct
    */ 
   int size; //overall size of Single Linked List
   Node* head; //pointer to first element in the list

} CLList;


//Methods to operate on list
void init(CLList* List); //initialize data member of the list
Node* traverse(CLList* List, int index);  //return the pointer to the node previous to the node at index 
void insert(CLList* List, int index, int data); //insert a node with payload data at position index
void suppress(CLList* List, int index);  //deletes a node at position index
void pushfront(CLList* List, int data); //insert node at the front of the list
void pushback(CLList* List, int data); //insert node at the end of the list
void popfront(CLList* List);  //delete node at the back of the list
void popback(CLList* List);  //delete node at the front of the list
void printlist(CLList* List); //print all elements in the list
void insertAsc(CLList* List, int data); //insert an element in the list in ascending order
unsigned int length(CLList* List);

void init(CLList* List) {
    /*
    *   initialize size to 0 and head to NULL
    */
   List->size = 0;
   List->head = NULL;
}

void printlist(CLList* List) {
    /*
    * print all elements in the list
    */
   printf("[");
   Node* tmp = List->head;

   if(List->size != 0) {
       while(tmp != NULL) {
           printf(" %d,", tmp->data);
           tmp = tmp->next;
       }
   }
   printf(" ]\n");
}

Node* traverse(CLList* List, int index) {
    /*
    * give an index N, traverse() traverse the list until N and return pointer to N-1
    * O(n)
    */
   
    //case 1: empty list
    if(List->size == 0) {
        printf("empty list!\n"); 
        return NULL;
    }

    //case 2: index is not present
    if(index < 0 || index >= List->size) {
        printf("Invalid index!\n");
        return NULL;
    }

    //case 3: index present
    Node* tmp = List->head; 
    for(unsigned int i = 0; i < index; ++i) {//traversing till index - 1 
        //printf("tmp value: %d for i = %d\n ", tmp->data, i);    
        tmp = tmp->next; //moving to the next node
    }
    //printf("about to return\n");
    return tmp;
}

void insert(CLList* List, int index, int data) {
    /*
    * insert a node with data at index
    * O(n)
    */

    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;

    
    if(List->size == 0) { //case 1: empty list
        List->head = new_node;
        new_node->next = NULL;
    } 
    else if(index == 0) { //case 2: front insertion
        new_node->next = List->head;
        List->head = new_node;
    } 
    else { //case 3: Non empty list with insert at middle
        Node* prev = traverse(List, index);
        new_node->next = prev->next;
        prev->next = new_node;
    }

    ++List->size;
}


void pushfront(CLList* List, int data) {
    /*
    * insert node at the front of the list
    */
   insert(List, 0, data);
} 

void pushback(CLList* List, int data) {
    /*
    * insert node at the end of the list
    */
   if(List->size == 1) { //edge case for single node list
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = data;
        new_node->next = List->head->next;
        List->head->next = new_node;
        ++List->size;

    } else {
        insert(List, List->size - 1, data);
    }
}  


void suppress(CLList* List, int index) {
    /*
    * suppress() deletes node at index
    * O(n)
    */ 

    //case 1: empty list
    if(List->size == 0) {
        printf("empty list!\n");
        return;
    }

    //case 2: invalid index
    if(index < 0 || index >= List->size) {
        printf("invalid index");
        return;
    }

    Node* to_del;
    
    if(index == 0) { //case 3: deleting head
       to_del = List->head;
       List->head = (List->head)->next;

    } else {  //case 4: deleting any node that is not head
        Node* prev = traverse(List, index - 1);
        to_del = prev->next;
        prev->next = to_del->next;

    }
    
    free(to_del);
    --List->size;
}

void popfront(CLList* List) {
    /*
    * delete node at the back of the list
    */
    suppress(List,0);
}  
void popback(CLList* List) {
    /*
    * delete node at the front of the list
    */
    suppress(List, List->size - 1);
}  

void sortinsert(CLList* List, Node* new_node) {
    /*
    * insert an element in the list in ascending order
    * finds appropriate location
    * insert the node with the element
    */

    //case empty and beginning

    if(List->head == NULL)
        List->head->data > new_node->data;
   /*
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;

    
    if(List->size == 0) { //case 1: empty list
        List->head = new_node;
        new_node->next = NULL;
    } 

    Node* prev = List->head; 
    while(data > tmp->data) {//traversing till index - 1 
        //printf("tmp value: %d for i = %d\n ", tmp->data, i);    
        tmp = tmp->next; //moving to the next node
    }
        new_node->next = prev->next;
        prev->next = new_node;
    //printf("about to return\n");
    } 
    else { //case 3: Non empty list with insert at middle
        Node* prev = traverse(List, index);
        
    }
    */
    ++List->size;
}

unsigned int length(CLList* List) {
    Node* tmp = List->head;
    if(List->head == NULL) return 0;

    unsigned int size = 1;
    while(tmp->next != List->head) {
        ++size;   
        tmp = tmp->next;
    }
    return size;
}


#endif