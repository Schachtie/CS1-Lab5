#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	//Check for empty list
	if (head == NULL)
	{
		return 0;
	}

	//Traverse list and increment length accordingly
	node* tempNode = head;
	int length = 1;
	while (tempNode->next != NULL)
	{
		++length;
		tempNode = tempNode->next;
	}
	return length;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	//Get length and allocate appropriate memory space
	int strLength = length(head);
	if (strLength == 0)
	{
		return NULL;
	}
	char* cStr = (char*)calloc(strLength + 1, sizeof(char));
	if (cStr == NULL)
	{
		return NULL;
	}
	else
	{
		//Traverse list and assign each char from linked list into the c string, append null character at end
		node* tempNode = head;
		char* strStart = cStr;
		do
		{
			*cStr = tempNode->letter;
			tempNode = tempNode->next;
			++cStr;
		} while (tempNode != NULL);
		*cStr = '\0';
		return strStart;
	}
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	node* newNode = (node*)calloc(1, sizeof(node));
	if (newNode != NULL)
	{
		//Initalize newNode memebers
		newNode->letter = c;
		newNode->next = NULL;

		//Check for empty list
		if (*pHead == NULL)
		{
			*pHead = newNode;
			return;
		}

		//Traverse to end of list
		node* listStart = *pHead;
		while ((*pHead)->next != NULL)
		{
			*pHead = (*pHead)->next;
		}

		//Add newNode and reset pHead
		(*pHead)->next = newNode;	
		*pHead = listStart;	
	}
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	//Check for empty list
	if (*pHead == NULL)
	{
		return;
	}

	//Begin freeing each node sequentially
	node* currentNode = *pHead;
	node* nextNode = currentNode->next;
	free(currentNode);
	while (nextNode != NULL)
	{
		currentNode = nextNode;
		nextNode = nextNode->next;
		free(currentNode);
	}
	*pHead = NULL;
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}