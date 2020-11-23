
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

static void printSTRList(char* textData,List_Typedef* list);
static void printINTList(char* textData, List_Typedef* list);
static void printFLTList(char* textData, List_Typedef* list);
static void printStructureList(char* textData, List_Typedef* list);
static void printListNodeAddressess(char* textData, List_Typedef* list);

ListStr_Typedef listsContainer = { 0 };
List_Typedef* listSTR = NULL;
List_Typedef* listINT = NULL;
List_Typedef* listFLT = NULL;
List_Typedef* listStructure = NULL;
List_Typedef* listCLEARTEST = NULL;
List_Typedef* listINT_2 = NULL;

int32_t temp = 0;
float tempf = 0.0F;
int main()
{
        /*------ 0 : Create List container and initialze some lists  */
        InitListContainer(&listsContainer);
        listSTR         = listsContainer.InitList(0);
        listINT         = listsContainer.InitList(51);
        listFLT         = listsContainer.InitList(0);
        listStructure   = listsContainer.InitList(0);    
        listINT_2       = listsContainer.InitList(0);

        /*------ 1 : Add string into list       */
        listsContainer.Add(listSTR, "TESTING 12345\0", 14);
        listsContainer.Add(listSTR, "TESTING 1234\0" , 13);
        listsContainer.Add(listSTR, "TESTING 123\0"  , 12);
        listsContainer.Add(listSTR, "TESTING\0"      , 8 );        

        /*------ 2 : Add integer into list      */
        for (int g = 0; g < 101; g++) {
            temp = g;
            listsContainer.Add(listINT, &temp, sizeof(int32_t));
        }

        /*------ 3 : Add float into list        */
        tempf = 0.0F;
        for (int g = 0; g < 101; g++) {
            tempf = 1.009F + (float)(g * 123.456F);
            listsContainer.Add(listFLT, &tempf, sizeof(float));
        }

        /*------ 4 : Add structure into list    */
        listsContainer.Add(listStructure, listFLT, sizeof(List_Typedef) * listFLT->Size);

        printSTRList(&"STRING ADDING TEST",listSTR);
        printINTList(&"INTEGER ADDING TEST",listINT);
        printFLTList(&"FLOAT ADDING TEST",listFLT);
        printStructureList(&"STRUCTURE ADDING TEST",listStructure);


        /*------ 5  : List clear test                */
            /*------ 5.1:  Add some string data into List    */
            listCLEARTEST = listsContainer.InitList(7);
            listsContainer.Add(listCLEARTEST, "NUCMETTIN", 40);
            listsContainer.Add(listCLEARTEST, "DRFGDFGDF", 40);
            listsContainer.Add(listCLEARTEST, "werwerewr", 40);
            listsContainer.Add(listCLEARTEST, "asdasdasd", 40);
            printListNodeAddressess(&"LIST CLEAR TEST- ADD DATA",listCLEARTEST);

            /*------ 5.2: Clear all added data from the List    */
            listsContainer.Clear(listCLEARTEST);
            printListNodeAddressess(&"LIST CLEAR TEST - CLEAR", listCLEARTEST);

            /*------ 5.3: Destroy the list                  */
            listsContainer.Destroy(&listCLEARTEST);
            printListNodeAddressess(&"LIST CLEAR TEST - DESTROY",listCLEARTEST);


        /*------ 6 :  List data remove test            */
            /*------ 6.1: Add some integer data into list      */
            for (int g = 0; g < 25; g++) {
                temp = g;
                listsContainer.Add(listINT_2, &temp, sizeof(int32_t));
            }
            printINTList(&"ADD DATA INTO LIST", listINT_2);

            /*------ 6.2: remove from the list                */
            listsContainer.RemoveAt(listINT_2, 0);
            listsContainer.RemoveAt(listINT_2, 20);
            listsContainer.RemoveAt(listINT_2, 13);
            printINTList(&"REMOVE FROM LIST", listINT_2);


        printf("%s\n", "end");
}

static void printSTRList(char* textData,List_Typedef* list) {
    printf("------------- %s -------------\n", textData);
    for (uint16_t i = 0; i < list->Size; i++) {
        char* str = (char*)list->ListPtrArr[i]->ListPtr;
        printf("%s\n", str);
    }
}

static void printINTList(char* textData, List_Typedef* list) {
    printf("------------- %s -------------\n", textData);
    for (uint16_t i = 0; i < list->Size; i++) {
        int32_t* temp = ((int32_t*)list->ListPtrArr[i]->ListPtr);
        printf("%d\n", *temp );
    }
}

static void printFLTList(char* textData, List_Typedef* list) {
    printf("------------- %s -------------\n", textData);
    for (uint16_t i = 0; i < list->Size; i++) {
        float* tempf = ((float*)list->ListPtrArr[i]->ListPtr);
        printf("%f\n", *tempf);
    }
}

static void printStructureList(char* textData, List_Typedef* list) {
    printf("------------- %s -------------\n", textData);
    for (uint16_t i = 0; i < list->Size; i++) {
        List_Typedef* tempf = ((List_Typedef*)list->ListPtrArr[i]->ListPtr);

        for (uint16_t i = 0; i < tempf->Size; i++) {
            float* temf = (float*)tempf->ListPtrArr[i]->ListPtr;
            printf("%f\n", *temf);
        }
    }
}

static void printListNodeAddressess(char* textData, List_Typedef* list) {
    printf("------------- %s -------------\n", textData);
    int32_t* temp = NULL;
    if(list == NULL)
        printf("--NO DATA --\n");
    else {
        for (uint16_t i = 0; i < list->Size; i++) {
            temp = NULL;
            if (list->ListPtrArr[i] != NULL) {
                if (list->ListPtrArr[i]->ListPtr != NULL) {
                    temp = ((int32_t*)list->ListPtrArr[i]->ListPtr);                    
                }
            }
            printf("0x%.8X\n", temp);
        }
    }
}