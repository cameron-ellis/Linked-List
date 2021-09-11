/*
	Author: Cameron Ellis
	Purpose: Updated Link List Algorithm to Include Dummy Node and puts data items in order using comparison fuction.
	Date: 10/16/2020
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	void* object;
	struct node* next;
} Node;

typedef struct linkedlist {
	Node *head;
   	int listLength;
} ListInfo;

typedef struct list{
	ListInfo *listInfo;
} List;

/* Function interfaces */
List initList();
Node * createNode(void * obj);
int insertAtHead(void*, List);
int insertAtTail(void*, List);
int insertAtIndex(void*, int, List);
void* getAtIndex(int,List);
int countItems(List);
int insertBefore(void* obj1, void* obj2, List);
int findFirstOccurrenceObj(void* obj, List);
void clearList(List);
void freeList(List);

/* Functions Important to this Pre Lab 8 */

/* This function inserts the object in its ascending
order position according to the user-defined global
comparison function cmp(void*,void*). */
int insertInOrder(void*, List);

/* This function deletes all objects that are
evaluated as equal to the object of the first
parameter according to the user-defined global
comparison function cmp(void*,void*). */
int removeEq(void*, List);  //Returns number of items removed

/* The user-defined global comparison function cmp(void*,void*)
is assumed to return a negative number if the first object
is less than the second object; zero if they are equal;
and a strictly positive number if the first object is
greater than the second object. */
int cmp(void*, void*);  //leave blank for now, focus on insert functions


int insertInOrder(void* obj, List userList) {
	Node * p = userList.listInfo->head->next;
	//Check to see if any objects are in the list first
	if (p == NULL) {
		return insertAtHead(obj,userList); //if no objects present insert object at head
	}
	//Check if first object is greater that the passed object
	else if (cmp(obj,p->object) < 0) {
		return insertAtHead(obj,userList);
	}
	//Check if first object is equal to the one passed
	else if (cmp(obj,p->object) == 0) {
		return -1; //object is already present don't insert
	}
	//If first object isn't greater than passed object, scan through list
	else {
	while (p->next != NULL) {
		//If passed object is less than the next obj insert before next obj
		if (cmp(obj,p->next->object) < 0) {
			Node * insObj = createNode(obj); //create a node for the obj
			if (insObj == NULL) {
				return -1; //memory could not be allocated for Node
			}
			Node * q = p->next; //put node containing larger object in q
			p->next = insObj; //set next node after p to the node with insObj
			insObj->next = q; //set node after insObj to the one with the larger obj
			userList.listInfo->listLength++; //increment list length
			return 0; //insertion successful
		}
		//If passed object is equal to the next object, insert next to it
		else if (cmp(obj,p->next->object) == 0) {
			/*
			Node * insObj = createNode(obj); //create a node for the obj
			if (insObj == NULL) {
				return -1; //memory could not be allocated for Node
			}
			Node * q = p->next; //put node containing equal object in q
			p->next = insObj; //set next node after p to the node with insObj
			insObj->next = q; //set node after insObj to the one with the equal obj
			userList.listInfo->listLength++; //increment list length
			return 0; //insertion successful
			*/
			return -1; //object already present
		}
		else {
			p = p->next; //if passed object is larger move on
		}
	}
	return insertAtTail(obj,userList);
}
/*
If we get to the end of the list and object hasn't been inserted
	then is must be the largest object and we insert it at the end
	return insertAtTail(obj,userList)
*/
}

int removeEq(void* obj, List userList) {
	Node * p = userList.listInfo->head;
	if (p == NULL) {
		return 0; //no objects in list to delete
	}
	while (p->next != NULL) {
		//Loop to delete multiple instances of obj in succession
		while (cmp(obj, p->next->object) == 0) {
			Node * q = p->next; //set q to Node to delete
			p->next = p->next->next; //skip over node to remove
			free(q); //delete node
			userList.listInfo->listLength--; //decrement listLength
			if (p->next == NULL) {
				return 0; //all instances deleted
			}
		}
		p = p->next; //once we have deleted instances in succesion, shift p over
	}
	return 0; //all instances deleted
}


int cmp(void* obj1, void* obj2) {
	int *a, *b;
	a = (int*)obj1;  //set obj1 to a
	b = (int*)obj2;  //set obj2 to b
	int diff = (*a - *b);
	/* If obj1 > obj2 positive number is returned
	   If obj1 = obj2 0 is returned
	   If obj1 < obj2 negative number is returned */
	return diff;
}





int main() {
/*To test and make sure dummy node implementation works
List userList = initList();
	char * str = "hello";
	int num1 = 2;
	float fl1 = 5.9904;
	char * str2 = "pls";
	double d1 = 17.2222;
	int num2 = 12;

	printf("%p\n", &fl1);
	printf("%p\n", &num1);
	printf("%p\n", str2);
	printf("%p\n", str);
	printf("%p\n", &d1);

	int r1 = insertAtHead(str,userList);
	int r2 = insertAtHead(&num1,userList);
	int r3 = insertAtHead(&fl1,userList);
	int r4 = insertBefore(str2,&num2,userList);
	int r5 = insertAtTail(&d1,userList);
	printf("Num Items: %d\n", countItems(userList));
	printf("%d %d %d %d %d\n", r1,r2,r3,r4,r5);

	printf("%p\n", getAtIndex(0,userList));
	printf("%p\n", getAtIndex(1,userList));
	printf("%p\n", getAtIndex(2,userList));
	printf("%p\n", getAtIndex(3,userList));
	printf("%p\n", getAtIndex(4,userList));

	printf("%d\n", findFirstOccurrenceObj(&d1,userList));


	clearList(userList);
	freeList(userList);
	*/


//To test insertInOrder and removeEq functions
	List userList1 = initList();
	List userList2 = initList();

	int a = 1;
	int b = 6;
	int c = 3;
	int d = 20;
	int e = 12;
	int f = 9;


	insertInOrder(&a,userList1);
	insertInOrder(&b,userList1);
	insertInOrder(&c,userList1);
	insertInOrder(&b,userList1);
	insertInOrder(&b,userList1);
	insertInOrder(&d,userList1);
	insertInOrder(&e,userList1);
	insertInOrder(&f,userList1);


	insertInOrder(&b,userList2);
	insertInOrder(&a,userList2);
	insertInOrder(&c,userList2);
	insertInOrder(&f,userList2);
	insertInOrder(&d,userList2);
	insertInOrder(&b,userList2);
	insertInOrder(&e,userList2);
	insertInOrder(&b,userList2);


	removeEq(&b,userList1);
	removeEq(&b,userList2);


	for (int i = 0; i < countItems(userList1); i++) {
		int * num = getAtIndex(i,userList1);
		printf("Num %d: %d\n", (i+1), *num);
	}

	for (int i = 0; i < countItems(userList2); i++) {
		int * num = getAtIndex(i,userList2);
		printf("Num %d: %d\n", (i+1), *num);
	}

	freeList(userList1);
	freeList(userList2);

	return 0;
}


/* This function makes an empty list object */
List initList() {
	List userList;
	ListInfo * linkList = malloc(sizeof(ListInfo));
	linkList->listLength = 0;  //initialize length to zero
	linkList->head = malloc(sizeof(Node)); //allocate memory to dummy node
	linkList->head->next = NULL;  //initialize head of linked list to NULL
	userList.listInfo = linkList;  //set listInfo to the the linkList just initialized
	return(userList);
}

/* This function creates a Node that can be added to a Linked List */
Node * createNode(void * obj) {
	Node * p;
	p = malloc(sizeof(Node));  //malloc to initialize node
	if (p) {   //check to see if malloc failed
		p->object = obj;  //set node obj to the passed void pointer
		p->next = NULL;  //set the next Node to NULL and return
	}
	return(p);
}

/* This function returns the number of Nodes/Objects in the list without
taking time proportional to the length of the list */
int countItems(List userList) {
	//get item count from userList struct member and return
	int itemCount = userList.listInfo->listLength;
	return(itemCount);
}

/* This function inserts the object of the first parameter at the head
of the list. Object passed must not be NULL */
int insertAtHead(void * obj, List userList) {
	if (obj == NULL) {
		return -4; //object must be no-NULL
	}
	else {
		Node * ListObj = createNode(obj);
		if (ListObj == NULL) {
			return -1; //memory could not be allocated to insert object
		}
		else {
			ListObj->next = userList.listInfo->head->next; //set ListObj before head
			userList.listInfo->head->next = ListObj; //set new head equal to the ListObj
			userList.listInfo->listLength++; //increment listLength
			return 0; //successful insertion
		}
	}
}

/* This function inserts the object of the first parameter at
the tail of the list. Passed object must not be NULL */
int insertAtTail(void * obj, List userList) {
	if (obj == NULL) {
		return -4; //object must be non-NULL
	}
	else if (userList.listInfo->listLength == 0) {
		//if no Nodes in list, make insert tail work like insertAtHead for same result
		return insertAtHead(obj,userList);
	}
	else {
		Node * ListObj = createNode(obj);  //create Node for passed object
		if (ListObj == NULL) {
			return -1; //memory could not be allocated to make Node
		}
		Node * p = userList.listInfo->head->next;
		while (p->next != NULL) {
			p = p->next;  //scan until end of linked list
		}
		p->next = ListObj; //set old last item next value equal to new last item
		userList.listInfo->listLength++;
		return 0;  //insertion successful
	}
}

/* This function inserts the object into the list at the
specified index location. Passed object must not be NULL */
int insertAtIndex(void * obj, int index, List userList) {
	int idx = index + 1; //shift to index by 1 inside function for easier use
	if (obj == NULL) {
		return -4; //object must be non-NULL
	}
	else if (userList.listInfo->listLength == 0) {
		//If no Nodes in list, insertAtIndex works the same as insertAtHead
		return insertAtHead(obj,userList);
	}
	else if (idx == 1) {
		//If inserting at first index, funciton works the same as insertAtHead
		return insertAtHead(obj,userList);
	}
	else if ((idx < 1) || (idx > userList.listInfo->listLength)) {
		//Error code for if index entered is out of bounds of linked list
		return -2;
	}
	else {
		Node * ListObj = createNode(obj);
		if (ListObj == NULL) {
			return -1; //memory could not be allocated to insert object
		}
		Node * p = userList.listInfo->head->next;
		int i = 1;  //incrementation variable for looping through list
		while(i < (idx - 1)) {
			p = p->next;  //scan through list until one Node before idx to insert at
			i++;
		}
		ListObj->next = p->next;  //set ListObj before the index to insert at
		p->next = ListObj; //set ListObj after the idx that is before the idx to be inserted at
		userList.listInfo->listLength++;
		return 0; //insertion successful
	}
}

/* This function returns the object at the index location given
by the first parameter */
void * getAtIndex(int index, List userList) {
	int idx = index + 1; //shift to index by 1 inside function for easier use
	void * obj;
	if (userList.listInfo->listLength == 0) {
		//If list is empty, return a NULL object
		obj = NULL;
		return obj;
	}
	else if ((idx < 1) || (idx > userList.listInfo->listLength)) {
		//If passed index is out of bounds of list
		obj = NULL;
		return obj;
	}
	else {
		int i = 1;
		Node * p = userList.listInfo->head->next;
		while (i < idx) {
			p = p->next;  //scan through list until Node at passed index is reached
			i++;
		}
		obj = p->object;  //set obj to the object contained by the Node at idx
		return obj; //return object at index
	}
}

/* This function inserts obj1 before obj2 in the list. If obj2 is not in
the list, then obj1 is placed at the head */
int insertBefore(void * obj1, void * obj2, List userList) {
	Node * p = userList.listInfo->head->next;
	if ((obj1 == NULL) || (obj2 == NULL)) {
		return -4; //Error code for object passed being NULL
	}
	else if (userList.listInfo->listLength == 0) {
		return insertAtHead(obj1,userList); //if no objects in list insert obj1 at head
	}
	else if (p->object == obj2) {
		return insertAtHead(obj1,userList); //if first object contains obj2 insert obj1 at head
	}
	else {
		while (p->next != obj2) {
			if (p->next == NULL) {
				return insertAtHead(obj1,userList); //if obj2 not found in entire list insert obj1 at head
			}
			else {
				p = p->next; //move to next Node
			}
		}
		//Once object is found, exit loop and p is the Node before the Node containing obj2
		Node * insObj1 = createNode(obj1);
		if (insObj1 == NULL) {
			return -1; //memory could not be allocated to create Node
		}
		else {
			Node * q = p->next; //set q to Node contaning obj2
			p->next = insObj1; //set Node containing obj1 to before Node containing obj2
			insObj1->next = q; //set obj1 Node next to obj2 Node
			userList.listInfo->listLength++;
			return 1; //successful insertion
		}
	}
}

/* This function returns the index of the first occurrence of the specified
object or zero if the object is not in the list. In this case index must
start at 1 since 0 is taken for the error code. Passed object must not
be NULL. */
int findFirstOccurrenceObj(void * obj, List userList) {
	if (obj == NULL) {
		return -4; //object must be non-NULL
	}
	else if (userList.listInfo->listLength == 0) {
		return 0; //Error code if no objects are in the list
	}
	else {
		Node * p = userList.listInfo->head->next; //set p to the head of the list
		int len = userList.listInfo->listLength; //get length of list
		for (int i = 0; i < len; i++) {
			if (p->object == obj) {
				return (i+1); //if object is found return index based at 1
			}
			else {
				p = p->next; //if object not found move to next Node
			}
		}
		return 0; //Error code if object not found in entire list
	}
}

/* This function clears the list (makes it empty) */
void clearList(List userList) {
	Node *p, *q;
	p = userList.listInfo->head->next;
	for (int i = 0; i < countItems(userList); i++) {  //increment through list
		q = p->next; //set q to one Node past p
		free(p); //free item at p
		p = q; //set p to next Node saved in q
	}
	userList.listInfo->listLength = 0; //set itemCount to zero once list cleared
	userList.listInfo->head->next = NULL; //set head of linked list to NULL
}

/* This function frees all memory allocated for a list */
void freeList(List userList) {
	clearList(userList); //first clear all Nodes in the list
	free(userList.listInfo->head); //free memory allocated to dummy node
	free(userList.listInfo); //then clear memory allocated to listInfo
}
