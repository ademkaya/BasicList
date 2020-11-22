# Basic List

This is a basic list implementation written in C language.

#### Usage : 
```sh

ListStr_Typedef listsContainer = { 0 };
/* list to be used */
List_Typedef* listSTR = NULL;

int main()
{
        /* Create List container and initialze some lists  */
            InitListContainer(&listsContainer);
            listSTR         = listsContainer.InitList(0);
        /* Add string into list                            */
            listsContainer.Add(listSTR, "TESTING 12345\0", 14);
            listsContainer.Add(listSTR, "TESTING 1234\0" , 13);
            listsContainer.Add(listSTR, "TESTING 123\0"  , 12);
            listsContainer.Add(listSTR, "TESTING\0"      , 8 );  
            
        /* reach the items in the list*/    
            char* ppp = listSTR->QuePtr[1];
            
        /* Remove data from index                          */
            listsContainer.Remove(listSTR, 0);
        /* Clear all added data from the List    */
            listsContainer.Clear(listSTR);
        /* Destroy the list                  */
            listsContainer.Destroy(&listSTR);

        return 0;
}
```

