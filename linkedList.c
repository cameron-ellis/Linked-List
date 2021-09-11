/*
    Author: Cameron Ellis
    Description: Implementation of a Linked List ADT that supports initilization, insertion and deletion of nodes, getter functions, as well as list clearing and memory management functions.
    Date: 10/10/2020
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct nodeStruct {
    void * object;
    struct nodeStruct * next;
} Node;

typedef struct linkedList {
    Node *head;
    int listLength;
} ListInfo;

typedef struct {
    ListInfo *linkListStruct;
} List;

//Function Initializations
List initList();
Node * createNode(void*);
int insertAtHead(void*, List);
int deleteAtHead(List);
int insertAtTail(void*, List);
int deleteAtTail(List);
void* getAtIndex(int, List);
int deleteAtIndex(int, List);
int insertAtIndex(void*, int, List);
int deleteAtObject(void*, List);
int countItems(List);
void clearList(List);
void freeList(List);

/* This function returns an empty List object. */
List initList() {
    List userList;
    ListInfo * linkList = malloc(sizeof(ListInfo));
    linkList->listLength = 0;  //initialize length to zero
    linkList->head = NULL;  //initialize head of linked list to NULL
    userList.linkListStruct = linkList; //set linkListStruct to the linkList we just initialized
    return(userList);
}

/* This function creates a Node that can be added to the Linked List */
Node * createNode(void * object) {
    Node *p;
    p = malloc(sizeof(Node));
    if(p){
        p->object = object;  //set node object to the passed void pointer
        p->next = NULL;      //set the next Node to NULL and return
    }
    return(p);
}

/* This function returns the number of objects in the list.
PERFORMANCE REQUIREMENT: This function must not take time
proportional to the length of the list. */
int countItems(List userList) {
    //get item count from userList struct member and return
    int itemCount = userList.linkListStruct->listLength;
    return(itemCount);
}

/* This function inserts the object of the first parameter at the
head of the list */
int insertAtHead(void * object, List userList) {
    if (object == NULL) {
        return -4; //Object must be non-NULL
    }
    else {
        Node * ListObj = createNode(object);
        if (ListObj == NULL) {
            return -1;  //memory could not be allocated to insert object
        }
        else {
            ListObj->next = userList.linkListStruct->head; //set ListObj before head
            userList.linkListStruct->head = ListObj;  //set new head equal to the ListObj
            userList.linkListStruct->listLength++; //increment listLength
            return 0;
        }
    }
}

/* This function inserts the object of the first parameter
at the tail of the list. */
int insertAtTail(void * object, List userList) {
    if (object == NULL) {
        return -4; //Object must be non-NULL
    }
    else if (userList.linkListStruct->listLength == 0) {
        int result = insertAtHead(object,userList);
        return result; //If no items in list, make insert at tail work essentially like insertAtHead
    }
    else {
        Node * ListObj = createNode(object);  //create node for passed object
        if (ListObj == NULL) {
            return -1;  //memory could not be allocated
        }
        Node * p = userList.linkListStruct->head;
        while (p->next != NULL) {
            p = p->next;  //scan until end of linked list
        }
        p->next = ListObj; //set old last item next equal to new last item
        userList.linkListStruct->listLength++;
        return 0;
    }
}
/* This function inserts the object into the list at the specified index location. */
int insertAtIndex(void * object, int idx, List userList) {
    if (object == NULL) {
        return -4; //Object must be non-NULL
    }
    else if (userList.linkListStruct->listLength == 0) {
        int result = insertAtHead(object,userList);
        return result; //If no items in list, make insert at index work essentially like insertAtHead
    }
    else if (idx == 1) {
        return insertAtHead(object, userList);  //works the same as insertAtHead
    }
    else if ((idx < 1) || (idx > userList.linkListStruct->listLength)){
        return -2;  //error code for if index is out of bounds of linked list
    }
    else {
        Node * ListObj = createNode(object);
        if (ListObj == NULL) {
            return -1;  //memory could not be allocated to insert object
        }
        Node * p = userList.linkListStruct->head;
        int i = 1;
        while(i < (idx - 1)) {
            p = p->next; //scan through linked list till one BEFORE idx to insert at
            i++;
        }
        ListObj->next = p->next;  //set ListObj before the index to insert at
        p->next = ListObj;  //set ListObj after the idx that is before the idx to be inserted at
        userList.linkListStruct->listLength++;
        return 0; //addition successful
    }
}

/* This function deletes the object at the head of a list */
int deleteAtHead(List userList) {
    if (userList.linkListStruct->listLength == 0) {
        return -3;  //no items in list to delete
    }
    else {
    Node * p = userList.linkListStruct->head;  //get first item to delete
    Node * q = userList.linkListStruct->head->next;  //get item after first item for new head
    free(p);  //delete first item
    userList.linkListStruct->head = q;  //set new head to item after deleted item
    userList.linkListStruct->listLength--; //decrement count
    return 0; //successful removal
    }
}

/* This function deletes the object at the tail of the list */
int deleteAtTail(List userList) {
    if (userList.linkListStruct->listLength == 0) {
        return -3;  //no items in list to delete
    }
    else {
        Node * p = userList.linkListStruct->head;
        int i = 1;
        while (i < (userList.linkListStruct->listLength - 1)) {
            p = p->next;  //scan through to item before last item
            i++;
        }
        Node * q = p->next; //set q equal to last item
        free(q); //delete last item
        p->next = NULL; //set new tail node next pointer to NULL
        userList.linkListStruct->listLength--; //decrement count
        return 0; //successful removal
    }
}

/* This function deletes the object at a given index location */
int deleteAtIndex(int idx, List userList) {
    if (userList.linkListStruct->listLength == 0) {
        return -3;  //no items in list to delete
    }
    else if (idx == 1) {
        return deleteAtHead(userList);  //same as delete at head
    }
    else if (idx == userList.linkListStruct->listLength) {
        return deleteAtTail(userList);  //same as delete at tail
    }
    else if ((idx < 1) || (idx > userList.linkListStruct->listLength)) {
        return -2; //error code for index being out of bounds of linked list
    }
    else {
        Node * p = userList.linkListStruct->head;
        int i = 1;
        while (i < (idx - 1)) {
            p = p->next;   //land on node BEFORE the one to remove
            i++;
        }
        Node * q = p->next;  //node to remove
        p->next = p->next->next;  //skip over node to remove
        free(q);  //remove node at index
        userList.linkListStruct->listLength--;
        return 0; //successful removal
    }
}

/* This function takes an object, scans through the list and deletes the node
containing the object. Object CANNOT be NULL */
int deleteAtObject(void * object, List userList) {
    Node * p = userList.linkListStruct->head;
    if (object == NULL) {
        return -4; //Error code for object passed being NULL
    }
    else if(userList.linkListStruct->listLength == 0) {
        return -3; //no objects in list to delete
    }
    else if(p->object == object) {
        return deleteAtHead(userList); //if first node holds passed object
    }
    else {
        int i = 1;  //incrementation variable to keep track of index
        while (p->next->object != object) {
            if (i == userList.linkListStruct->listLength) {
                return -5; //error code for if passed object is not in list
            }
            else {
                p = p->next;  //move to next node
                i++;  //increment index count
            }
        }
        Node * q = p->next; //set q equal to node containing object
        p->next = p->next->next; //skip over node to remove
        free(q);  //delete node containing object to delete
        userList.linkListStruct->listLength--;
        return 0;  //successful removal
    }
}

/* This function returns the object at the index location
given by the first parameter. */
void * getAtIndex(int idx, List userList) {
    void * returnObj;
    if (userList.linkListStruct->listLength == 0) {
        returnObj = NULL; //if array is empty
        return returnObj;
    }
    else if((idx < 1) || (idx > userList.linkListStruct->listLength)) {
        returnObj = NULL;  //if out of bounds of list
        return returnObj;
    }
    else {
        int i = 1;
        Node * p = userList.linkListStruct->head;
        while (i < (idx)) {
            p = p->next;  //scan through list till item at index equals p
            i++;
        }
        returnObj = p->object;  //return the object from pointer at index
        return returnObj;
    }
}

/* This function clears the list (makes it empty) */
void clearList(List userList) {
    Node *p, *q;
    p = userList.linkListStruct->head;
    for (int i = 0; i < countItems(userList); i++) {  //increment through list
        q = p->next; //set q to one item past p
        free(p); //free item at p
        p = q;  //set p to next item saved in q
    }
    userList.linkListStruct->listLength = 0;  //set itemCount to zero once list cleared
}

/* This function frees all memory allocated for a list. */
void freeList(List userList) {
    clearList(userList);  //first clear the items in the list
    free(userList.linkListStruct);  //then clear memory allocated in linkListStruct
}

int main() {
    List userList = initList();
    char * str = "hello";
    int num1 = 2;
    float fl1 = 5.9904;
    char * str2 = "pls";
    double d1 = 17.2222;

    printf("%p\n", &fl1);
    printf("%p\n", &num1);
    printf("%p\n", str2);
    printf("%p\n", str);
    printf("%p\n", &d1);

    int r1 = insertAtHead(str,userList);
    int r2 = insertAtHead(&num1,userList);
    int r3 = insertAtHead(&fl1,userList);
    int r4 = insertAtIndex(str2,3,userList);
    int r5 = insertAtTail(&d1,userList);
    printf("Num Items: %d\n", countItems(userList));
    printf("%d %d %d %d %d\n", r1,r2,r3,r4,r5);

    printf("%p\n",getAtIndex(1,userList));
    printf("%p\n",getAtIndex(2,userList));
    printf("%p\n",getAtIndex(3,userList));
    printf("%p\n",getAtIndex(4,userList));
    printf("%p\n",getAtIndex(5,userList));

    /*
    int re1 = deleteAtObject(&fl1,userList);
    int re2 = deleteAtObject(&d1,userList);
    int re3 = deleteAtObject(str2,userList);

    printf("%d %d %d\n",re1,re2,re3);

    printf("%p\n", getAtIndex(1,userList));
    printf("%p\n", getAtIndex(2,userList));

    printf("%p\n", &num1);
    printf("%p\n", str);
    */

    clearList(userList);
    freeList(userList);
}
