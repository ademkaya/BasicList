#include "list.h"

static List_Typedef* InitList(int16_t initialSize);
static bool Add	 (List_Typedef* lst, void* data, uint16_t dataSizeInBytes);
static bool Clear(List_Typedef* lst);
static void Destroy(List_Typedef** lst);
static void Remove(List_Typedef* lst, int16_t index);

bool InitListContainer(ListStr_Typedef* listPtr) {

	listPtr->InitList	= &InitList;
	listPtr->Add		= &Add;
	listPtr->Clear		= &Clear;
	listPtr->Destroy	= &Destroy;
	listPtr->Remove		= &Remove;

	return true;
}

static List_Typedef* InitList(int16_t initialSize){

	List_Typedef* retVal = calloc(1, sizeof(List_Typedef));
	if (retVal != NULL) {
		memset(retVal, 0, sizeof(List_Typedef));

		if (abs(initialSize) > 0) {
			retVal->QuePtr = (void**)calloc(initialSize, sizeof(void*));
			retVal->Size = initialSize;
		}

		retVal->LastIndex = -1;
	}
	return retVal;
}

static void Remove(List_Typedef* lst, int16_t index) {

	/* Remove the data from the index */
	free(lst->QuePtr[index]);
	lst->QuePtr[index] = 0;

	/* push the data back in order no to create a empty hole in the array */
	for (uint16_t i = index; i < lst->Size; i++) {
		if ((i + 1) <= lst->LastIndex)
			lst->QuePtr[i] = lst->QuePtr[i + 1];
	}

	lst->Size -= 1;
	lst->LastIndex -= 1;

}

static bool Clear(List_Typedef* lst) {
	bool retVal = false;

	int listmaxLength = lst->Size;
	for (int i = 0; i < listmaxLength; i++) {
		if (lst->QuePtr[i] != 0x00) {
			free(lst->QuePtr[i]);
			lst->QuePtr[i] = 0;
		}
	}

	return retVal;
}

static void Destroy(List_Typedef** lst) {

	Clear(*lst);

	free((*lst)->QuePtr);
	(*lst)->QuePtr = 0;

	/* free the pointer itself*/
	free(*lst);
	*lst = 0;

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
		void** temp = NULL;
		temp = (void**)realloc(lst->QuePtr, (lst->LastIndex + 1)*sizeof(void*));	/* increase the list holder */
		if (temp != NULL) {
			lst->QuePtr = temp;
			/*LastIndex = 0*/
			lst->QuePtr[lst->LastIndex] = tempData;			/* keep the address of the pointer of copied data */
			lst->Size += 1;
		}
		else {
			return retVal;
		}

	} else if (lst->Size > lst->LastIndex) {
		lst->QuePtr[lst->LastIndex] = tempData;			/* keep the address of the pointer of copied data */
	}

	return true;
}