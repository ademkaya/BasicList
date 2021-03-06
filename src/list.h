#ifndef __LIST_H__
#define __LIST_H__

/*
	 * max list count set as uint16
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct Root {
	void*	 ListPtr;
	uint16_t DataSize;
}Root_Typedef;

typedef struct List {
	Root_Typedef**  ListPtrArr;
	int16_t			Size;
	int16_t			LastIndex;	
}List_Typedef;

typedef struct ListStr {

	List_Typedef*   (*InitList)	 (int16_t initialSize);

	bool			(*Add)		 (List_Typedef* lst, void* data, uint16_t dataSize);
	bool			(*Clear)	 (List_Typedef* lst		  );
	bool			(*Destroy)	 (List_Typedef** lst);
	bool			(*RemoveAt)	 (List_Typedef* lst,int16_t index);
	bool			(*Insert)	 (List_Typedef* lst, int16_t index ,void* data, uint16_t dataSize);

	uint16_t		TotalListCount;

}ListStr_Typedef;

bool InitListContainer(ListStr_Typedef* listPtr);

#endif