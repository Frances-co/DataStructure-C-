#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int x;
    struct node* next;
}stackNode;

void push(stackNode* pushMe);
stackNode* pop();

stackNode* head;
stackNode* top;

int main() {
    
    int arr[10]= {1,2,3,4,5,6,7,8,9,10};
    
    for(int i=0; i<10; i++){
        stackNode* node=(stackNode*)malloc(sizeof(stackNode));
        node->x= arr[i];
        push(node);
    }
    
    for(int i=0; i<10; i++){
        stackNode* current= pop();
        arr[i]= current->x;
        free(current); //Remember that free() takes a pointer to the
                       //node that we wanna release. 
    }
    
    for(int i=0; i<10; i++){
        printf("%d\n", arr[i]);
    }
    
    return 0;
}

void push(stackNode* pushMe){
    pushMe->next= NULL;
    if(head==NULL){
        head=pushMe;
        top=pushMe;
    }else{
        top->next= pushMe;
        top= pushMe;
    }
}
stackNode* pop() {
    if (head == NULL) {
        printf("The stack is empty!\n");
        return NULL;
    }

    if (head == top) {
        // Only one element in the stack
        stackNode* returnMe = top;
        head = top = NULL;
        return returnMe;
    }

    // Traverse to the node just before `top`
    stackNode* current = head;
    while (current->next != top) {
        current = current->next;
    }

    stackNode* returnMe = top; // Save the top to return
    top = current;            // Update top to the node just before
    top->next = NULL;         // Terminate the list
    return returnMe;
}














