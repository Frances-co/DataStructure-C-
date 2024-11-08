#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
struct node {
    char info;
    struct node *l, *r;
};

// Define the stack structure
struct stackNode {
    struct node* treeNode;
    struct stackNode* next;
};

// Function to create a new tree node
struct node* createNode(char value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->info = value;
    newNode->l = NULL;
    newNode->r = NULL;
    return newNode;
}

// Function to create a new stack node
struct stackNode* createStackNode(struct node* treeNode) {
    struct stackNode* newStackNode = (struct stackNode*)malloc(sizeof(struct stackNode));
    newStackNode->treeNode = treeNode;
    newStackNode->next = NULL;
    return newStackNode;
}

// Push a tree node onto the stack
void push(struct stackNode** stack, struct node* treeNode) {
    struct stackNode* newStackNode = createStackNode(treeNode);
    newStackNode->next = *stack;
    *stack = newStackNode;
}

// Pop a tree node from the stack
struct node* pop(struct stackNode** stack) {
    if (*stack == NULL) {
        return NULL;
    }
    struct stackNode* temp = *stack;
    *stack = (*stack)->next;
    struct node* treeNode = temp->treeNode;
    free(temp);
    return treeNode;
}

// Check if the stack is empty
int isEmpty(struct stackNode* stack) {
    return stack == NULL;
}

// In-order traversal using a stack
void inorderTraversal(struct node* root) {
    struct stackNode* stack = NULL;  // Initialize the stack
    struct node* current = root;

    while (current != NULL || !isEmpty(stack)) {
        // Reach the leftmost node of the current node
        while (current != NULL) {
            push(&stack, current);
            current = current->l;
            
            //:::IMP:::
            //Note that when we reach the left-lower-most node,
            //So current is null so far..
            //We then pop it, move the right subtree, and go down
            //to the left-lower-most node
            //If the current node is right, then the result of
            //current= current->r; will be null
            //HOWEVER, HERE IS THE TRICK
            
            //Outer while loop won't stop cuz the STACK is NOT EMPTY YET
            //So we'll go up one node, use the inner while loop
            //to check for a left path again..
            //And on and on...
        }

        // Current must be NULL at this point, so we pop the top item from stack
        current = pop(&stack);
        printf("%c ", current->info);  // Visit the node

        // Move to the right subtree
        current = current->r;
    }
}

// Main function to test the code
int main() {
    // Constructing a simple binary tree for testing
    struct node* root = createNode('P');
    root->l = createNode('M');
    root->r = createNode('L');
    root->l->l = createNode('S');
    root->r->r = createNode('E');
    root->l->l->l = createNode('A');
    root->l->l->r = createNode('A');
    root->r->r->r = createNode('R');
    root->r->r->r->l = createNode('T');
    root->r->r->r->r = createNode('E');
    root->r->r->r->r->l = createNode('E');
    
    //OUTPUT==> ASAMPLETREE
    printf("In-order traversal of the tree:\n");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
