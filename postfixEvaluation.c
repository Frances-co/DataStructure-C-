//LinkedList stack; ik it would be kinda easier and more straightforward with array-based stack, but I'm just playing around atm...
//----
//Comments in this code are mostly some study shit and thigns I didn't know abt
//----

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//IMP IMP IMP IMP:::
//I have to create my structs before any forward declaration if
//these function declaration will return one of these structs or
//take one of them as an argument.


//stack nodes:
typedef struct node{
    int num;
    struct node* next;
} stackNode;

//::IMP::
//If I weren't evaluating the expression, but converting from 1
//form into another, I would use 2 different nodes..
//WHY?
//cuz in the conversion case, the stack may hold an operator
//or an operand which is a character
//So we would need a node for char x; and another node for int x
//In this case, the stack only have operands, so no need for chars
//inside the stack...

//For conversion, we can put a char and an int in a single node
//and in case it's operand, set the char var to null and vice
//versa, but this would consume unused memory which is useless.

//forward declarations:
double substringToDouble(char *start, char *end);
double doOperation(char operatorr, double operand1, double operand2);
stackNode* push(int x, stackNode** top);
double pop(stackNode* top);


int main() {
    int expressionSize;
    scanf("%d", &expressionSize);
    char expression[expressionSize+1]; //+1 for the '\0'
    
    //kinda weird to be -1, but check the implementation of the
    //default:
    //and you'll get it..
    //It's needed for handing the first number in the expression
    int spaceIndex= -1;
    
    for(int i=0; i<expressionSize; i++){
        scanf("%c", &expression[i]);
    }
    //This loop is better than this line below:
    //scanf("%s", &expression); 
    //cuz this one above is vulnerable to overflows
    //it would be okay if we can do f"{var}" like in python:
    //scanf(f"%{expressionSize}s", expression);
    
    stackNode* top=NULL;
    
    for(int i=0; expression[i]!='\0'; i++){
        switch(expression[i]){
            case '+':
            case '-':
            case '/':
            case '*':
                
                //doOperation(expression[i], pop()->num, pop()->num);
                //Line above isn't correct cuz: the order in which pop()->num is evaluated could vary based on the compiler or optimization settings.
                double operand2= pop(top);
                double operand1= pop(top);
                double result= doOperation(expression[i], operand1, operand2);
                push(result, &top);
                
            default:
                if(expression[i]==' '){
                    
                    if(spaceIndex== -1){
                        top= push(substringToDouble(&expression[0], &expression[i-1]), &top);
                        spaceIndex=i;
                    }
                    else{
                        top= push(substringToDouble(&expression[spaceIndex+1], &expression[i-1]), &top);
                        spaceIndex= i;
                    }
                    
                }
            
            
        }
    }
    
    return 0;
}

double doOperation(char operatorr, double operand1, double operand2){
    switch(operatorr){
        case '+':
            return operand1 + operand2;
        
        case '-':
            return operand1 - operand2;
        
        case '*':
            return operand1 * operand2;
        
        case '/':
            return operand1 / operand2;
    }
}

stackNode* push(int x, stackNode** top){
    if(*top==NULL){
        *top= (stackNode* )malloc(sizeof(stackNode));
        (*top)->num= x;
        //IMP IMP IMP IMP IMP IMP::::
        //Here, I thought that it's unnecessary to set top->next
        //to NULL cuz I thought it will happen implicitly if I
        //didn't do it explicitly.
        //But look:
        //If you don't explicitly set a value for top->next, it 
        //will not automatically be set to NULL by default. In C, 
        //uninitialized pointers (such as top->next if you don't 
        //assign a value to it) contain garbage values (random data
        //), which could lead to undefined behavior.
        //So we should do this:
        (*top)->next= NULL;
        //IMP IMP IMP IMP IMP IMP::::
        // -> operator has higher precedence than * dereference
        //operator; therefore, we must use parentheses!!!!!!
        return *top;
    }
    else{
        stackNode* newTop= (stackNode *)malloc(sizeof(stackNode));
        newTop->num= x;
        newTop->next= *top;
        *top= newTop;
        return *top;
    }
}

double pop(stackNode* top){
    int popMe= top->num;
    free(top);
    return popMe;
}

double substringToDouble(char *start, char *end) {
    size_t length = end - start; //substring length
    char temp[length + 1]; // +1 for null-terminator

    strncpy(temp, start, length);
    temp[length] = '\0';
    return strtod(temp, NULL);
}

//Clean Version:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//stack nodes:
typedef struct node{
    int num;
    struct node* next;
} stackNode;

//forward declarations:
double substringToDouble(char *start, char *end);
double doOperation(char operatorr, double operand1, double operand2);
stackNode* push(int x, stackNode** top);
double pop(stackNode* top);
int isOperator(char x);


int main() {
    int expressionSize;
    scanf("%d", &expressionSize);
    char expression[(expressionSize+1)*2]; //+1 for the '\0'

    int spaceIndex= -1;

    scanf("%s", &expression);

    stackNode* top=NULL;
    double result;

    for(int i=0; expression[i]!='\0'; i++){
        switch(expression[i]){
            case '+':
            case '-':
            case '/':
            case '*':
                double operand2= pop(top);
                double operand1= pop(top);
                result= doOperation(expression[i], operand1, operand2);
                printf("%f\n", result);
                push(result, &top);
                if(isOperator(expression[i+2])){
                    i=i+1;//we add 1, and the loop will add 1 at its end, so we end up in i+2 which is the operator, skipping a useless space.
                          //the problem is we need this space calculation shit cuz our logic is based on it.
                }
                else
                    spaceIndex=i+1;

                //Note that this program expect a space between each number and operator, between each independent unit.
                //Ex:9 3 4 * 8 + 4 / -
                //So if we find, say *, then we set spaceIndex to i+1

            default:
                if(expression[i]==' '){

                    if(spaceIndex== -1){
                        top= push(substringToDouble(&expression[0], &expression[i-1]), &top);
                        spaceIndex=i;
                    }
                    else{
                        top= push(substringToDouble(&expression[spaceIndex+1], &expression[i-1]), &top);
                        spaceIndex= i;
                    }

                }


        }
    }
    printf("%d", result);

    return 0;
}

double doOperation(char operatorr, double operand1, double operand2){
    switch(operatorr){
        case '+':
            return operand1 + operand2;

        case '-':
            return operand1 - operand2;

        case '*':
            return operand1 * operand2;

        case '/':
            return operand1 / operand2;
    }
}

stackNode* push(int x, stackNode** top){
    if(*top==NULL){
        *top= (stackNode* )malloc(sizeof(stackNode));
        (*top)->num= x;
        (*top)->next= NULL;
        return *top;
    }
    else{
        stackNode* newTop= (stackNode *)malloc(sizeof(stackNode));
        newTop->num= x;
        newTop->next= *top;
        *top= newTop;
        return *top;
    }
}

double pop(stackNode* top){
    int popMe= top->num;
    free(top);
    return popMe;
}

double substringToDouble(char *start, char *end) {
    size_t length = end - start; //substring length
    char temp[length + 1]; // +1 for null-terminator

    strncpy(temp, start, length);
    temp[length] = '\0';
    return strtod(temp, NULL);
}

int isOperator(char x){
    if(x=='-'||x=='+'||x=='/'||x=='*')
        return 1;
    else
        return 0;
}




//testcase:9 3 4 * 8 + 4 / -







