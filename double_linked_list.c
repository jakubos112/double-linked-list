#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int data;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct{
    Node *head;
    Node *tail;
    int size;

}List;

List* createList(){
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void addLastElement(List* list, int data){
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    if(list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
        newNode->prev = NULL;
        newNode->next = NULL;
    }
    else{
        list->tail->next = newNode;
        newNode->prev = list->tail;
        newNode->next = NULL;
    }
    list->size++;
}

void addFirstElement(List* list, int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    if(list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
        newNode->prev = NULL;
        newNode->next = NULL;
    }
    else{
        list->head->prev = newNode;
        newNode->next = list->head;
        list->head = newNode;
        newNode->prev = NULL;
    }
    list->size++;
}

void deleteLastElement(List* list){
    if(list->size == 0) return;
    if(list->size == 1){
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    }else{
        Node *temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(temp);
        
    }
    
    list->size--;
    
}

void deleteFirstElement(List* list){
    if(list->size == 0) return;
    if(list->size == 1){
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    }
    else{
        Node *temp = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(temp);
    }
    list->size--;
}

void printData(List* list, int index){
    Node* node = list->head;
    for(int i = 0; i <= index; i++){
        if(i == index){
            printf("Data: %d\n",node->data);
        }
        node = node->next;
    }
}

void freeList(List* list){
    while(list->head != NULL){
        deleteFirstElement(list);
    }
    free(list);
}

void replaceData(List* list, int index, int newData){
    Node* node = list->head;
    for(int i = 0; i <= index; i++){
        if(i == index){
            node->data = newData; 
        }
        node = node->next;
    }
}

Node* findData(List* list, int find) {
    Node* node = list->head;
    while (node != NULL) {
        if (node->data == find) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void findAndDelete(List* list, int find) {
    Node* node = findData(list, find);
    if (node == NULL) {
        return;
    }

    if (node == list->head) {
        deleteFirstElement(list);
        return;
    }

    if (node == list->tail) {
        deleteLastElement(list);
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    list->size--;
}

void addInOrder(List* list, int newData) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        list->size++;
        return;
    }

    if (newData <= list->head->data) {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
        list->size++;
        return;
    }

    Node *current = list->head;
    while (current->next != NULL && current->next->data < newData) {
        current = current->next;
    }

    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != NULL) {
        current->next->prev = newNode;
    } else {
        list->tail = newNode;
    }
    current->next = newNode;
    list->size++;
}

int main(){
    
    printf("\nDouble-linked List\n");
    return 0;
}