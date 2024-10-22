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

RC openPageFile (char *fileName, SM_FileHandle *filehandlepointer) {
    FILE *Fpointer = fopen(fileName, "r+");
    struct stat fileInfo;
    
    switch(filehandlepointer != NULL){
        case 1:
            switch(Fpointer != NULL){
                case 1:
                    filehandlepointer->fileName = fileName;
                    filehandlepointer->curPagePos = 0;
                    switch(fstat(fileno(Fpointer), &fileInfo) < 0){
                        case 1:
                            return RC_BUFFER_ERROR;
                        default:
                            printf("File pointer greater than 0.");
                    }
                    filehandlepointer->totalNumPages = fileInfo.st_size/ PAGE_SIZE;
                    fclose(Fpointer);
                    return RC_OK;
                default:
                    return RC_FILE_NOT_FOUND;
            }
        default:
            return RC_FILE_HANDLE_NOT_INIT;
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
        returnCode = RC_FILE_NOT_FOUND;
    } 
    else if(PagePointer == NULL)
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
    onGoingPgN = StructFHptr->curPagePos / PAGE_SIZE;
    printf("The current record placement is at: %d \n", onGoingPgN);
    return readBlock(onGoingPgN, StructFHptr, MemPageSH);
}

//Calculates the page position of the next block based on the current page position
RC readNextBlock(SM_FileHandle *StructFHptr, SM_PageHandle MemPageSH) {
    if(StructFHptr == NULL){
        return RC_FILE_NOT_FOUND;
    }
    int currPos = getBlockPos(StructFHptr);
    StructFHptr->curPagePos = currPos + 1;
    int nextPageNum = StructFHptr->curPagePos;
    printf("The next record pointer is at %d \n", nextPageNum);
    return readBlock(nextPageNum, StructFHptr, MemPageSH);
}

//Calculates the page position of the last block by subtracting 1 from the total number of pages
extern RC readLastBlock(SM_FileHandle *StructFHptr, SM_PageHandle MemPageSH) {
    int eofpg = StructFHptr->totalNumPages;
    int PagePtrL = eofpg - 1;

    return readBlock(PagePtrL, StructFHptr, MemPageSH);
}

RC writeBlock (int pageNum, SM_FileHandle *filehandlepointer, SM_PageHandle pagehandleptr) 
{
	int i=0;
    int close=0;
    int pgout=0;
    int m=0;
    int tell=0;
    int seek = 1;
    int pgend;
    int pg_sz;
    int startPos;
    int num_pg = pageNum;
    FILE *Fpointer;
    switch(pageNum < 0){
        case 1:
            return RC_WRITE_FAILED;
        default:
            printf("Page Number greater than 0.");
    }
    switch(pageNum > filehandlepointer->totalNumPages){
        case 1:
            return RC_WRITE_FAILED;
        default:
            printf("Page Number less than total number of pages.");
    }

    (m == 0) ? Fpointer = fopen(filehandlepointer->fileName, "r+") : printf("File not opened.");

    switch(Fpointer == NULL){
        case 1:
            return RC_FILE_NOT_FOUND;
        default:
            pg_sz=PAGE_SIZE;
            startPos = num_pg * pg_sz;
            switch(num_pg == 0){
                case 1:
                    (seek == 0) ? printf("seek not performed") : fseek(Fpointer, startPos, SEEK_SET); 		
                    for(int i = 0; i < pg_sz; i++){
                        pgend=feof(Fpointer);
                        (pgend == 0) ? printf(".") : appendEmptyBlock(filehandlepointer);
                        (pgout == 1) ? printf("Character not put.") : fputc(pagehandleptr[i], Fpointer);
                    }
                    (tell!=1) ? filehandlepointer->curPagePos = ftell(Fpointer) : printf("Current page position not found.");
                    (close == 1) ? printf("File not able to close.") : fclose(Fpointer);
                default:
                    filehandlepointer->curPagePos = startPos;
                    fclose(Fpointer);
                    writeCurrentBlock(filehandlepointer, pagehandleptr);
            }
            return RC_OK;
    }
}

RC writeCurrentBlock (SM_FileHandle *filehandlepointer, SM_PageHandle pagehandleptr) {
	FILE *Fpointer = fopen(filehandlepointer->fileName, "r+");
    int curPos;
    switch(filehandlepointer == 0){
        case 1:
            return RC_FILE_HANDLE_NOT_INIT;
        default:
                switch(Fpointer == NULL){
                    case 1:
                        return RC_FILE_NOT_FOUND;
                    default:
                        appendEmptyBlock(filehandlepointer);
                        curPos = filehandlepointer->curPagePos;
                        fseek(Fpointer, curPos, SEEK_SET);
                        printf("Writing int the block."); 
                        fwrite(pagehandleptr, 1, strlen(pagehandleptr), Fpointer);
                        curPos = ftell(Fpointer);    
                        printf("Closing the file pointer."); 	
                        fclose(Fpointer);
                        return RC_OK;
                }
    }
}

RC appendEmptyBlock (SM_FileHandle *filehandlepointer) {
    int j = 0;
    SM_PageHandle emptyBlock = (SM_PageHandle)calloc(PAGE_SIZE, sizeof(char));
    switch(filehandlepointer == 0){
        case 1:
            return RC_FILE_HANDLE_NOT_INIT;
        default:
            switch(fseek(PagePointer, j, SEEK_END) == 0 ){
                case 1:
                    fwrite(emptyBlock, sizeof(char), PAGE_SIZE, PagePointer);
                default:
                    free(emptyBlock);
                    printf(".");
                    return RC_WRITE_FAILED;
            }
            free(emptyBlock);
            filehandlepointer->totalNumPages = filehandlepointer->totalNumPages +1;
            return RC_OK;
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
