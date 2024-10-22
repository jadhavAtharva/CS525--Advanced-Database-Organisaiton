#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<unistd.h>
#include<stdbool.h>
#include "storage_mgr.h"
#include<sys/stat.h>
#include<sys/types.h>

//File pointer created
FILE *PagePointer;  

void initStorageManager(void){
    PagePointer = NULL; //initialising the file pointer to NULL
    printf("Storage Manager Start");
}

//generates a new page file
RC createPageFile (char *newPageName){    
    PagePointer = fopen(newPageName, "w+");
    if (newPageName != NULL){
    SM_PageHandle newBlankPg = (SM_PageHandle)calloc(PAGE_SIZE, sizeof(char)); 

    int newPointer = fwrite(newBlankPg, sizeof(char), PAGE_SIZE,PagePointer);
    if(newPointer >= PAGE_SIZE){
        printf("File created successfully \n");
    }
    fclose(PagePointer);

    free(newBlankPg);
    printf("File closed and allocated memory is freed\n");
    return RC_OK;
    }
    else
    {
        return RC_FILE_NOT_FOUND;
    }
}

//opens an existing file and assigns it a handler
RC openPageFile(char *newPageName, SM_FileHandle *StructFHptr)
{
PagePointer = fopen(newPageName, "r+");
int totPages,currPage;
if(PagePointer != NULL)
{
    fseek(PagePointer, 0, SEEK_END);
    int lValue=0;
    lValue=ftell(PagePointer);
    int tPageValue=0;
    switch (lValue % PAGE_SIZE)
    {
    case 0: 
        tPageValue=(lValue/PAGE_SIZE);
        break;
    
    default:
        tPageValue=(lValue/PAGE_SIZE)+1;
        break;
    }
    
    StructFHptr->totalNumPages = tPageValue; //computed tPageValue is assigned to the totalNumPages variable of the structure.
    totPages=StructFHptr->totalNumPages;
    StructFHptr->curPagePos = 0; //assigns current page position to 0
    currPage=StructFHptr->curPagePos; //assigns the value of the structure to the currPage variable

    printf("Total pages: %d \n",totPages);
    printf("Current page: %d \n",currPage);
    
    StructFHptr->mgmtInfo = PagePointer;

    StructFHptr->fileName = newPageName;
    return RC_OK;
}
else {
    return RC_FILE_NOT_FOUND;
}
}

//closes a file associated with the provided SM_FileHandle
RC closePageFile(SM_FileHandle *StructFHptr) 
{
    RC returnCode;
    
    if (StructFHptr->mgmtInfo == NULL) 
    {
        returnCode = RC_FILE_NOT_FOUND;
    } 
    else if (fclose(StructFHptr->mgmtInfo) != 0) 
    {
        returnCode = RC_FILE_CLOSE_FAILED;
    } 
    else 
    {
        PagePointer = NULL;
        printf("Successfully closed the file.\n");
        returnCode = RC_OK;
    }
    
    switch (returnCode) 
    {
        case RC_FILE_NOT_FOUND:
            printf("Error: File not found.\n");
            break;
        case RC_FILE_CLOSE_FAILED:
            printf("Error: Failed to close the file.\n");
            break;
        case RC_OK:
            // No need for additional action here
            break;
        default:
            printf("Unknown error.\n");
            break;
    }
    
    return returnCode;
}

//deletes a page file specified and returns a success code if the deletion is successful, or an error code for a destroy error
RC destroyPageFile(char *PgFlName) 
{
    PagePointer = fopen(PgFlName, "r");
    
    return (PagePointer != NULL) ? (fclose(PagePointer), unlink(PgFlName), PagePointer = NULL, printf("\nPage destroyed successfully.\n"), RC_OK) : RC_FILE_NOT_FOUND;
}

//Reads a block of data from the specified page position in the file
RC readBlock (int noPg, SM_FileHandle *StructPHptr, SM_PageHandle StructFHptr)
{
    PagePointer = fopen(StructPHptr->fileName, "r+");
    bool nPagePointer = PagePointer != NULL;
    int totalPagenum, PosAfterRead, ptrCurPos;
    if (nPagePointer)
    {
        printf("Given file name exists and the file is opened.\n \n");

        switch ((StructPHptr->totalNumPages)> noPg && noPg>=0)
        {
        case 1:
            printf("Congratulations!! Your page was found.\n \n");
            break;

        default:
            totalPagenum=StructPHptr->totalNumPages;

            printf("Total Pages in the file: %d \n \n",totalPagenum);
            
            printf("Page number entered:  %d \n \n",noPg);
            printf("Sorry!! 404 Page not found \n \n");
            
            return RC_READ_NON_EXISTING_PAGE;
        }
        int pagestart = (noPg *PAGE_SIZE);

        (fseek(PagePointer, pagestart, SEEK_SET)!=0) ? printf("Cannot find the starting pointer to the page\n \n") : printf("Now the pointer is pointing to the begining of the page!!\n \n");
        
        fread(StructFHptr, 1, PAGE_SIZE, PagePointer);

        printf("Pointer before scanning %d and Pointer after scanning the file %d \n \n", pagestart, ftell(PagePointer));

        PosAfterRead = ftell(PagePointer);

        switch ((PosAfterRead % PAGE_SIZE)!=0)
        {
        case 1:
            ptrCurPos=(PosAfterRead/PAGE_SIZE);
            break;
        
        default:
            ptrCurPos=((PosAfterRead/PAGE_SIZE)-1);
            break;
        }
        StructPHptr -> curPagePos = ptrCurPos;

        int currPage=StructPHptr -> curPagePos;
        int totPages=StructPHptr->totalNumPages;
        
        printf("Pointer is present at: %d and inside the scanning record, total no. of pages: %d \n \n",currPage, totPages);

        switch (fclose(PagePointer) != 0)
        {
        case 1:
            printf("The file did not end properly! \n");
            break;
        
        default:
            printf("Congratulations!! the file is closed properly.\n");
            return RC_OK;
            break;
        }
    }
    else 
    {
        printf("404 File not found.\n \n");
        return RC_FILE_NOT_FOUND;
    }
}

//Retrieves the current block position from the provided SM_FileHandle and returns it
int getBlockPos (SM_FileHandle *StructFHptr)
{
    int recordLoc = StructFHptr ->curPagePos;
    (StructFHptr != NULL) ? printf("File Handler Commenced!! \n") : printf("No file handled not commenced!! \n");

    printf("Record Location: %d \n \n",recordLoc);
    if(StructFHptr != NULL){
        return recordLoc;
    }
    else{
        return 0;
    }
    
}

//Reads the first block of data from the file and returns the result
RC readFirstBlock (SM_FileHandle *StructFHptr, SM_PageHandle MemPageSH)
{
    switch (StructFHptr == NULL)
    {
    case 1:
        return RC_FILE_NOT_FOUND;
        break;
    
    default:
        return readBlock(0, StructFHptr, MemPageSH);
        break;
    }
}

//Calculates the page position of the previous block based on the current page position
RC readPreviousBlock(SM_FileHandle *StructFHptr, SM_PageHandle MemPageSH) 
{
    int currPos = getBlockPos(StructFHptr);
    StructFHptr -> curPagePos = currPos - 1;
    printf("After reading previous record, pointer is at: %d \n", currPos - 1);

    return readBlock(currPos - 1, StructFHptr, MemPageSH);
}

//Retrieves the current page position
RC readCurrentBlock(SM_FileHandle *StructFHptr, SM_PageHandle MemPageSH) {

    int onGoingPgN;
    if(StructFHptr == NULL){
        return RC_FILE_NOT_FOUND;
    }
    else{
        onGoingPgN = StructFHptr->curPagePos / PAGE_SIZE;
        printf("The current record placement is at: %d \n", onGoingPgN);
        return readBlock(onGoingPgN, StructFHptr, MemPageSH);
    }
}

//Calculates the page position of the next block based on the current page position
RC readNextBlock(SM_FileHandle *StructFHptr, SM_PageHandle MemPageSH) {
    if(StructFHptr == NULL){
        return RC_FILE_NOT_FOUND;
    }
    else{
        int currPos = getBlockPos(StructFHptr);
        StructFHptr->curPagePos = currPos + 1;
        int nextPageNum = StructFHptr->curPagePos;
        printf("The next record pointer is at %d \n", nextPageNum);
        return readBlock(nextPageNum, StructFHptr, MemPageSH);
    }
}

//Calculates the page position of the last block by subtracting 1 from the total number of pages
extern RC readLastBlock(SM_FileHandle *StructFHptr, SM_PageHandle MemPageSH) {
    int eofpg = StructFHptr->totalNumPages;
    int PagePtrL = eofpg - 1;

    return readBlock(PagePtrL, StructFHptr, MemPageSH);
}

//Writes the content of memHandle to the specified block index in the file
RC writeBlock(int PgPos, SM_FileHandle *StructFHptr, SM_PageHandle StructPHptr) 
{
    int flag = 0;
    if (PagePointer == NULL){
        flag = 1;
        return (printf("404! File not found!! \n \n"), RC_FILE_NOT_FOUND);
    }
    if (PgPos < 0 || PgPos >= StructFHptr->totalNumPages){
        flag = 1;
        return (printf("Page size not in given limit or invalid page number. \n \n"), RC_WRITE_FAILED);
    }

    if (StructFHptr == NULL){
        flag = 1;
        return (printf("404! File handle not found. \n \n"), RC_FILE_HANDLE_NOT_INIT);
    }
    if(flag == 0){
        int flag1 = 0;
        FILE *RecPtr = StructFHptr->mgmtInfo;
        
        if (RecPtr == NULL){
            flag1 = 1;
            return (printf("Invalid Record pointer. \n \n"), RC_FILE_NOT_FOUND);
        }

        if (fseek(RecPtr, PgPos * PAGE_SIZE, SEEK_SET) != 0){
            flag1 = 1;
            return (printf("Was not able to seek. \n \n"), RC_WRITE_FAILED);
        }
        if (flag1 == 0){

        size_t FileWritePtr = fwrite(StructPHptr, sizeof(char), PAGE_SIZE, RecPtr);

        if (FileWritePtr != PAGE_SIZE){
            flag1 = 1;
            return RC_WRITE_FAILED;
        }
        else{
        
                StructFHptr->curPagePos = PgPos;
                printf("Post writing the record, location of the block: %d\n \n", StructFHptr->curPagePos);
                printf("Post writing the record, pages in total: %d\n \n", StructFHptr->totalNumPages);
                return RC_OK;
            }
        }
    }
}

//hecks for a page error, writes content to the current page position in the file
RC writeCurrentBlock(SM_FileHandle *StructFHptr, SM_PageHandle StructPHptr) 
{
    // Use a ternary operator for concise error checking
    return (StructFHptr == NULL) ? (printf("404! File not found. Please check again.\n"), RC_FILE_NOT_FOUND) : writeBlock(StructFHptr->curPagePos, StructFHptr, StructPHptr);
}

//Checks for file existence, creates an empty block, and appends it as a new block to the file
RC appendEmptyBlock (SM_FileHandle *StructFHptr)
{
    char PgInitPtr = (char) calloc(PAGE_SIZE, sizeof(char));
    int totPos;
    int currPtrPost, PgTotVal;

    int nfseek = fseek(StructFHptr -> mgmtInfo, 0, SEEK_END);
    switch (PagePointer == NULL)
    {
    case 1:
        printf("404! File not found \n \n");
        return RC_FILE_NOT_FOUND;
        break;
    
    default:
        if (nfseek != 0) 
        {
            free(PgInitPtr);
            return RC_WRITE_FAILED;

        } else
        {
            fwrite(PgInitPtr, PAGE_SIZE, 1, StructFHptr -> mgmtInfo);

            StructFHptr->totalNumPages+= 1;
            StructFHptr -> curPagePos+=1 ;

            printf("Final total number of records(after appending): %d and post append location of the record: %d \n \n",StructFHptr->totalNumPages, StructFHptr -> curPagePos);
            
        }

        free(PgInitPtr);
        return RC_OK;
        break;
    }
}

//Checks for file existence and appends empty blocks to meet the required number of pages
RC ensureCapacity(int totalNumofPages, SM_FileHandle *filehandleptr) 
{
    PagePointer = fopen(filehandleptr->fileName, "a");
    int i;

    if (PagePointer == NULL) {
        printf("\nThe file does not exist\n");
        return RC_FILE_NOT_FOUND;
    }

    for(i=0; i < (filehandleptr->totalNumPages - totalNumofPages); i++){
        appendEmptyBlock(filehandleptr);
    }

    printf("Final location of record after adding the empty pages at the end to match the capacity: %d\n \n Last record number after adding the empty pages: %d \n \n", filehandleptr->curPagePos, filehandleptr->totalNumPages);

    fclose(PagePointer);
    return RC_OK;
}
