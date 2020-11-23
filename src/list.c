#include "list.h"

static List_Typedef* InitList(int16_t initialSize);
static bool Add		(List_Typedef* lst, void* data, uint16_t dataSizeInBytes);
static bool Clear	(List_Typedef* lst);
static void Destroy	(List_Typedef** lst);
static bool RemoveAt(List_Typedef* lst, int16_t index);
static bool Insert	(List_Typedef* lst, int16_t index, void* data, uint16_t dataSize);

bool InitListContainer(ListStr_Typedef* listPtr) {

	listPtr->InitList	= &InitList;
	listPtr->Add		= &Add;
	listPtr->Clear		= &Clear;
	listPtr->Destroy	= &Destroy;
	listPtr->RemoveAt	= &RemoveAt;
	listPtr->Insert		= &Insert;
	return true;
}

static List_Typedef* InitList(int16_t initialSize){

	Root_Typedef** temp = NULL;
	Root_Typedef* ptemp = NULL;

	List_Typedef* retVal = calloc(1, sizeof(List_Typedef));
	if (retVal != NULL) {
		memset(retVal, 0, sizeof(List_Typedef));

		if (abs(initialSize) > 0) {
			temp = (Root_Typedef**)calloc(initialSize, sizeof(Root_Typedef*));
				if (temp != NULL) {
					retVal->ListPtrArr = temp;
				}
				else {
					return NULL;
				}
				for (uint16_t i = 0; i < initialSize; i++) {
					ptemp = NULL;
					ptemp = (Root_Typedef*)calloc(1, sizeof(Root_Typedef));
					if (ptemp != NULL) {
						retVal->ListPtrArr[i] = ptemp;
					}
					else {
						return NULL;
					}
				}
			retVal->Size = initialSize;
		}

		retVal->LastIndex = -1;
	}
	return retVal;
}

	static bool RemoveAt(List_Typedef* lst, int16_t index) {

		if (index > lst->LastIndex)
			return false;

		/* save the index's pointers*/
		void** tempListPtr			  = &(lst->ListPtrArr[index]->ListPtr);
		Root_Typedef* tempListPtrArr  = lst->ListPtrArr[index];

		void* lastListPtr = lst->ListPtrArr[lst->LastIndex]->ListPtr;
		Root_Typedef* lastListPtrArr = lst->ListPtrArr[lst->LastIndex];


		/* shrink the array in order to discard last index*/
		Root_Typedef**  temp = (Root_Typedef**)realloc(lst->ListPtrArr, (lst->Size - 1) * sizeof(Root_Typedef*));	/* increase the list holder */
		if (temp != NULL) {

			/* assign the shrinked array*/
			lst->ListPtrArr = temp;

			/* zero the last item*/
			lst->ListPtrArr[lst->LastIndex] = 0;

			/* push the data back in order not to create a empty hole in the array */
			for (uint16_t i = index; i < lst->Size; i++) {
				if ((i + 1) <= lst->LastIndex)
					lst->ListPtrArr[i] = lst->ListPtrArr[i + 1];
			}

			lst->Size -= 1;
			lst->LastIndex -= 1;

			/* copy the last item updated position */
			lst->ListPtrArr[lst->LastIndex] = lastListPtrArr;
			lst->ListPtrArr[lst->LastIndex]->ListPtr = lastListPtr;			

			/* Remove the list data */
			free(*tempListPtr);
			*tempListPtr = 0;

			/* Remove the list structure */
			free(tempListPtrArr);

		}else {
			/* error occured, no change was made, quit*/
			return false;
		}

		return true;
	}

	static bool Clear(List_Typedef* lst) {
	
		int listmaxLength = lst->Size;
		for (int i = 0; i < listmaxLength; i++) {
			if (lst->ListPtrArr[i] != 0x00) {
				
				if (lst->ListPtrArr[i]->ListPtr != 0x00) {
					free(lst->ListPtrArr[i]->ListPtr);
					lst->ListPtrArr[i]->ListPtr = 0;
					lst->ListPtrArr[i]->DataSize = 0;
				}							
			}
		}

		return true;
	}

	static void Destroy(List_Typedef** lst) {

		Clear(*lst);

		int listmaxLength = (*lst)->Size;
		for (int i = 0; i < listmaxLength; i++) {
			if ((*lst)->ListPtrArr[i] != 0x00) {
				free((*lst)->ListPtrArr[i]);
				(*lst)->ListPtrArr[i] = 0;
			}
		}

		/* free the root */
		free((*lst)->ListPtrArr);
		(*lst)->ListPtrArr = 0;

		(*lst)->Size = -1;
		(*lst)->LastIndex = -1;

		///* free the pointer itself*/
		free(*lst);
		*lst = 0;

	}

static bool Insert(List_Typedef* lst, int16_t index, void* data, uint16_t dataSize) {
	/* not implemented yet */
	return false;
}

static bool Add(List_Typedef* lst, void* data, uint16_t dataSizeInBytes) {

	bool retVal = false;
	void* tempData = NULL;

	tempData = calloc(1, dataSizeInBytes);		/* allocate for incoming data */
	if (!tempData)
		return retVal;
	memset(tempData, 0, dataSizeInBytes);		/* clear the array */
	memcpy(tempData, data, dataSizeInBytes);	/* copy the data   */

	lst->LastIndex += 1;						/* starts at -1 */
	/*0 = 0*/
	if (lst->Size == lst->LastIndex ) 			/* keeps track of initial data */
	{
		Root_Typedef** temp = NULL;
		Root_Typedef* ptemp = NULL;
		temp = (Root_Typedef**)realloc(lst->ListPtrArr, (lst->LastIndex + 1) * sizeof(Root_Typedef*));	/* increase the list holder */
		if (temp != NULL) {
			/*LastIndex = 0*/
			lst->ListPtrArr = temp;
				ptemp = (Root_Typedef*)calloc(1, sizeof(Root_Typedef));		/* initialize the new pointer */
				if (ptemp != NULL) {
					lst->ListPtrArr[lst->LastIndex] = ptemp;
				}
				else {
					return retVal;
				}
			lst->ListPtrArr[lst->LastIndex]->ListPtr = tempData;			/* keep the address of the pointer of copied data */
			lst->ListPtrArr[lst->LastIndex]->DataSize = dataSizeInBytes;	/* Add size of the data */
			lst->Size += 1;
		}
		else {
			return retVal;
		}

	} else if (lst->Size > lst->LastIndex) {
		lst->ListPtrArr[lst->LastIndex]->ListPtr = tempData;			/* keep the address of the pointer of copied data */
		lst->ListPtrArr[lst->LastIndex]->DataSize = dataSizeInBytes;	/* Add size of the data */
	}

	return true;
}