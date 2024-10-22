#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include "storage_mgr.h"
#include "buffer_mgr.h"


typedef struct frameBfPg
{
	int flagNo; 
    int Client_C; 
    bool bad; 
    int referenceNo; 
	SM_PageHandle dt; 
	PageNumber pagesInTot; 
} frameBfPg;

int flagg = 0; 
int wordCntComplete = 0; 
int buffSize = 0; 
int pageNumbersPgCnt = 0; 
int endPtrBP = 0; 

//Implement setNewPage
void setNewPg(frameBfPg *framePg, frameBfPg *bPFrame, int indexPgFrame)
{	
	int numberOfPg, NumberFg, Client_cnt;
    numberOfPg=bPFrame->pagesInTot;
    bool badIsIt;
	framePg[indexPgFrame].pagesInTot = numberOfPg;
	NumberFg=bPFrame->flagNo;
    badIsIt=bPFrame->bad;
    Client_cnt=bPFrame->Client_C;
	framePg[indexPgFrame].flagNo = NumberFg;
	framePg[indexPgFrame].dt = bPFrame->dt;
	framePg[indexPgFrame].bad = badIsIt;
	framePg[indexPgFrame].Client_C = Client_cnt;
}

//Implement writeToDisk
void writeToDisk(BM_BufferPool *const bufferPlBM, frameBfPg *bufferPgFrm, int indexPgFrm)
{
	bool blockForWriting;
    int countWordOfDisk;
    SM_FileHandle fileHndSM;
	blockForWriting=true;
	openPageFile(bufferPlBM->pageFile, &fileHndSM);
    switch(blockForWriting!=false){
        case 1:
            writeBlock(bufferPgFrm[indexPgFrm].pagesInTot, &fileHndSM, bufferPgFrm[indexPgFrm].dt);
        default:
            break;
    }
	countWordOfDisk=wordCntComplete;
	countWordOfDisk=countWordOfDisk+1;
	wordCntComplete=countWordOfDisk;
}

//Implement ClockStrategy
void CLOCK_Strategy(BM_BufferPool *const bufferPlBM, frameBfPg *buffPgFrmeMain) {
    bool reqPgFnd;
    reqPgFnd = false;
    int temp1;
    frameBfPg *buffPgFrme = (frameBfPg *)bufferPlBM->mgmtData;

    while (!reqPgFnd) {
        switch(!(endPtrBP % buffSize)){
            case 1:
                endPtrBP = 0;
                temp1 = 1;
            default:
                break;
        }
        switch(temp1 == 1){
            case 1:
                if (buffPgFrme[endPtrBP].Client_C == NULL){
                    int temp2 = 1;
                    if(temp2 == 1){
                        (buffPgFrme[endPtrBP].bad == 1) ? writeToDisk(bufferPlBM, buffPgFrme, endPtrBP) : printf("PageFrame is dirty.");
                    }
                    setNewPg(buffPgFrme, buffPgFrmeMain, endPtrBP);
                    endPtrBP = endPtrBP + 1;
                    reqPgFnd = true;
                }
            default:
                ((buffPgFrme[endPtrBP]).pagesInTot == (*buffPgFrmeMain).pagesInTot) ? reqPgFnd = true : printf("Req. page not found.");
                buffPgFrme[endPtrBP].flagNo = 1;
                endPtrBP++;
        }
    }
    int cnt = 0;
    while(cnt < buffSize){
        buffPgFrme[cnt].flagNo = 0;
        cnt++;
    }
}

//Implement LRU Strategy
void LRU_Strategy(BM_BufferPool *const bufferPlBM, frameBfPg *buffPgFrmeMain)
{  
	bool badOrNot;
	int fileLstIndx;

	fileLstIndx = 0;
	int numOfLstFile;

	frameBfPg *pageFrmeBuffPtr = (frameBfPg *)bufferPlBM->mgmtData;
	numOfLstFile = pageFrmeBuffPtr[0].flagNo;

	for(int i = fileLstIndx + 1; i < buffSize; i++){
		int numOfFile;
		numOfFile=pageFrmeBuffPtr[i].flagNo;
		(numOfFile < numOfLstFile) ? numOfLstFile = numOfFile, fileLstIndx = i : printf(".");
	}
	
	badOrNot=pageFrmeBuffPtr[fileLstIndx].bad;

	(badOrNot != true) ? badOrNot=badOrNot : writeToDisk(bufferPlBM, pageFrmeBuffPtr, fileLstIndx) ;

	(badOrNot!=badOrNot) ? printf(".") : setNewPg(pageFrmeBuffPtr, buffPgFrmeMain, fileLstIndx);
}

void FIFO_Strategy(BM_BufferPool *const bufferPlBM, frameBfPg *buffPgFrme)
{   
	frameBfPg *pageFrmeBuffPtr = (frameBfPg *)bufferPlBM->mgmtData;
    int presentInd, totNumOfPg, countOfRead;
	totNumOfPg=buffSize;
	countOfRead=pageNumbersPgCnt;
    presentInd = countOfRead % totNumOfPg;
	int p;

	for(int temp1 = 0; temp1 < totNumOfPg; temp1++)
	{   	
		if (pageFrmeBuffPtr[presentInd].Client_C == 0)
		{
			(pageFrmeBuffPtr[presentInd].bad == true) ? writeToDisk(bufferPlBM, pageFrmeBuffPtr, presentInd) : printf("....");
            setNewPg(pageFrmeBuffPtr, buffPgFrme, presentInd);
			break;
		}
		else
		{
		    presentInd = presentInd + 1;
			(presentInd % buffSize != 0) ? presentInd = presentInd : printf("..");
			(presentInd % buffSize == 0) ? presentInd = 0 : printf("...");
		}
	}
}

//Implement initBufferPool
RC initBufferPool(BM_BufferPool *const bufferPlBM, const char *const fileNameOfPg,
						 const int pagesNumber, ReplacementStrategy strategyReplace,
						 void *dataStart)
{
	buffSize = pagesNumber;
	frameBfPg *page = calloc(pagesNumber, sizeof(frameBfPg));

	int temp1=0, temp2;

	while(temp1 < pagesNumber){
		page[temp1].bad = false;
		page[temp1].referenceNo = 0;
		page[temp1].flagNo = 0;
		temp1 += 1;
	}

	temp1 = 0;
	while(temp1 < pagesNumber){
		page[temp1].dt = NULL;
		page[temp1].pagesInTot = -1;	
		page[temp1].Client_C = 0;
		temp1 += 1;
	}

	temp2=0;

	switch(temp2 == 0){
		case 1:
			bufferPlBM->mgmtData = page;
			bufferPlBM->numPages = pagesNumber;
			bufferPlBM->strategy = strategyReplace;
			bufferPlBM->pageFile = (char *)fileNameOfPg;
			wordCntComplete = endPtrBP = 0;
		default:
			break;
	}
 return RC_OK;
}

RC shutdownBufferPool(BM_BufferPool *const bufferPlBM)
{
	int numberOfPages, temp1;

	frameBfPg *page_frameptr = (frameBfPg *)bufferPlBM->mgmtData;

	numberOfPages = buffSize;

	for(int temp1 = 0; temp1 < numberOfPages; temp1++){

        switch(page_frameptr[temp1].Client_C != 0){
            case 1: 
                return RC_BUFFER_PIN_PG;
            default:
                continue;
        } 
	}
    
	forceFlushPool(bufferPlBM);
    bufferPlBM->mgmtData = NULL;
    printf("Buffer flushed Successfully.");
	free(page_frameptr);
    printf("Page frame pointer free successfully.");
	return RC_OK;
}


// Implement forceFlushPool
RC forceFlushPool(BM_BufferPool *const bufferPlBM)
{
	bool badOrNot;	
	SM_FileHandle fileHndSM;
	int countOfClient;
	frameBfPg *buffPgFrmePte = (frameBfPg *)bufferPlBM->mgmtData;
	int pageNumbers = buffSize;

	int temp1 = 0, temp2, temp3;
	while (temp1 < pageNumbers)
	{
		countOfClient=buffPgFrmePte[temp1].Client_C;
		badOrNot=buffPgFrmePte[temp1].bad;

		(countOfClient == 0 ) ? printf("Client count 0.") : printf("Client count not 0.");

		(badOrNot != false) ? printf("Dirty flag true") : printf("Dirty flag false");

		if (countOfClient == 0 )
		{
            if(badOrNot == true)
            {
                temp2=0;
                (temp2 != 0) ? printf("Flag temp2 not true") : openPageFile(bufferPlBM->pageFile, &fileHndSM);

                temp3=0;
                (temp3 != 0) ? printf("Flag temp3 not true") : writeBlock(buffPgFrmePte[temp1].pagesInTot, &fileHndSM, buffPgFrmePte[temp1].dt);
                
                (temp3 != 0) ? printf("Flag temp3 not true") : wordCntComplete++;

                buffPgFrmePte[temp1].bad = badOrNot = false;
				printf("Buffer Page frame not bad.");
                
            }
		}
		temp1++;
	}
	return RC_OK;
}

RC markDirty(BM_BufferPool *const buffPlBM, BM_PageHandle *const pgHndlBM) 
{
	int temp1 = 0;
    frameBfPg *buffPgFrme = (frameBfPg *)buffPlBM->mgmtData;

    while (temp1 < buffSize)
    {
        if (pgHndlBM->pageNum == buffPgFrme[temp1].pagesInTot)
        {
            buffPgFrme[temp1].bad = true;
			printf("Returning OK.");
            return RC_OK;
        }

        temp1++;
    }

    return RC_BUFFER_ERROR;
}


RC unpinPage(BM_BufferPool *const bufferPlBM, BM_PageHandle *const pgHndlBM) 
{
    frameBfPg *buffPgFrme = (frameBfPg *)bufferPlBM->mgmtData;
    
    for (int j = 0; j < buffSize; j++)
    {
        if (pgHndlBM->pageNum == buffPgFrme[j].pagesInTot)
        {
            buffPgFrme[j].Client_C = buffPgFrme[j].Client_C - 1;

            return RC_OK;
        }
    }
    return RC_PAGE_NOT_FOUND;
}


RC forcePage(BM_BufferPool *const bufferPlBM, BM_PageHandle *const pgHndlBM) 
{
	int temp = 0;
    frameBfPg *buffPgFrme = (frameBfPg *)bufferPlBM->mgmtData;
    
    while (temp < buffSize)
    {
        if (buffPgFrme[temp].pagesInTot == pgHndlBM->pageNum) 
        {
            writeToDisk(bufferPlBM, buffPgFrme, temp);

            buffPgFrme[temp].bad = false;

        }
        temp++;
    }
    return RC_OK;
    printf("All good.");
}


//noPg
bool noPg(BM_BufferPool *const bufferPlBM, BM_PageHandle *const pgHndlBM,const PageNumber totNoPges)
{
        const int firstPgPos = 0;
		frameBfPg *buffPgFrme = (frameBfPg *)bufferPlBM->mgmtData;
		SM_FileHandle filehandlepointer;
		openPageFile(bufferPlBM->pageFile, &filehandlepointer);
		pageNumbersPgCnt = flagg;
		buffPgFrme[firstPgPos].Client_C++;
		pageNumbersPgCnt = 0;
		buffPgFrme[firstPgPos].dt = (SM_PageHandle)malloc(PAGE_SIZE);
		pgHndlBM->pageNum = totNoPges;
		readBlock(totNoPges, &filehandlepointer, buffPgFrme[firstPgPos].dt);
        printf("Block read successfully.");
		buffPgFrme[firstPgPos].pagesInTot = totNoPges;
		ensureCapacity(totNoPges, &filehandlepointer);
        printf("Capacity ensured.");
		buffPgFrme[firstPgPos].referenceNo = 0;
		pgHndlBM->data = buffPgFrme[0].dt;
		buffPgFrme[firstPgPos].flagNo = flagg;
}


RC pinPage(BM_BufferPool *const bufferPlBM, BM_PageHandle *const pgHndlBM,const PageNumber totNumOfPg)
{   
    const int pgPosFirst = 0;
    int k = 0, pgTemp;
    bool isTheBufferFull = true;

    frameBfPg *frmePgMgmtData = (frameBfPg *)bufferPlBM->mgmtData;

    frameBfPg *buffPgFrme = (frameBfPg *)malloc(sizeof(frameBfPg));

    switch(frmePgMgmtData[pgPosFirst].pagesInTot == -1){
		case 1:
			noPg(bufferPlBM, pgHndlBM, totNumOfPg);
        	return RC_OK;
		default:
			printf("Invalid number of pages");
	}
	pgTemp = frmePgMgmtData[k].pagesInTot;
	
    for(k = 0; k < buffSize; k++)
    {
		switch(frmePgMgmtData[k].pagesInTot == totNumOfPg){
			case 1:
				isTheBufferFull = false;
                frmePgMgmtData[k].Client_C++;
				flagg++;
				
                (bufferPlBM->strategy == RS_LRU) ? frmePgMgmtData[k].flagNo = flagg : printf("Strategy checked.");

                pgHndlBM->data = frmePgMgmtData[k].dt;
				pgHndlBM->pageNum = totNumOfPg;
			
                (bufferPlBM->strategy == RS_CLOCK) ? frmePgMgmtData[k].flagNo = 1 : printf("");
				
				endPtrBP = endPtrBP +1;
			default:
				printf("Number of pages not equal.");
		}
        int iter = 1;

		switch(pgTemp == -1){
			case 1:
				if(iter == 1)
				{
					SM_FileHandle filehandlepointer;
                    frmePgMgmtData[k].dt = (SM_PageHandle)malloc(PAGE_SIZE);
					openPageFile(bufferPlBM->pageFile, &filehandlepointer);
					printf("Page opened successfully.");
					readBlock(totNumOfPg, &filehandlepointer, frmePgMgmtData[k].dt);
					printf("Block read successfully.");
                    frmePgMgmtData[k].referenceNo = 0;
					pageNumbersPgCnt = pageNumbersPgCnt+1;
                    flagg = flagg +1;
                    frmePgMgmtData[k].Client_C = 1;
					frmePgMgmtData[k].pagesInTot = totNumOfPg;

					switch(bufferPlBM->strategy)
					{
						case RS_LRU:
							frmePgMgmtData[k].flagNo = flagg;
						default:
							printf("Not a valid strategy.");
					}
					pgHndlBM->pageNum = totNumOfPg;
					pgHndlBM->data = frmePgMgmtData[k].dt;

					switch(bufferPlBM->strategy){		
						case RS_CLOCK:
							frmePgMgmtData[k].flagNo = 1;
							
						default:
							printf("Not a valid strategy.");
					}
					isTheBufferFull = false;
				}
			default:
				printf("Invalid pgHndlBM.");
		}
    }
	SM_FileHandle filehandlepointer;
	switch(isTheBufferFull == true){
		case 1:
			
			openPageFile(bufferPlBM->pageFile, &filehandlepointer);

			flagg = flagg + 1;
			frameBfPg *buffPgFrme = (frameBfPg *)malloc(sizeof(frameBfPg));
			buffPgFrme->dt = (SM_PageHandle)malloc(PAGE_SIZE);
            buffPgFrme->pagesInTot = totNumOfPg;
			buffPgFrme->referenceNo = 0;
			
			readBlock(totNumOfPg, &filehandlepointer, buffPgFrme->dt);
			
			pageNumbersPgCnt = pageNumbersPgCnt +1;
			buffPgFrme->Client_C = 1;
			buffPgFrme->bad = !true;
			
            (bufferPlBM->strategy == RS_LRU) ? buffPgFrme->flagNo = flagg : printf(".....");

            pgHndlBM->data = buffPgFrme->dt;
			pgHndlBM->pageNum = totNumOfPg;

            (bufferPlBM->strategy == RS_CLOCK) ? buffPgFrme->flagNo = 1 : printf("......");

			ReplacementStrategy strategy = bufferPlBM->strategy;

			if(strategy == RS_FIFO)
			{
				FIFO_Strategy(bufferPlBM, buffPgFrme);
			}
			if(strategy == RS_LRU)
			{
				LRU_Strategy(bufferPlBM, buffPgFrme);
			}
			if(strategy == RS_CLOCK)
			{
				CLOCK_Strategy(bufferPlBM, buffPgFrme);
			}
			printf("No Strategy Implemented\n");
		default:
			printf("..");
            break;
	}
    return RC_OK;
	printf("All Okay.");
}


PageNumber *getFrameContents(BM_BufferPool *const bufferPlBM) 
{
	PageNumber *frmeContntPgNum = malloc(sizeof(PageNumber) * bufferPlBM->numPages);
    int temp = 0;
    frameBfPg *pageFrmeBuff = (frameBfPg *)bufferPlBM->mgmtData;
    
 
    while (temp < bufferPlBM->numPages)
    {
        PageNumber pageNum = pageFrmeBuff[temp].pagesInTot;

        switch (pageNum)
        {
            case -1:
                frmeContntPgNum[temp] = NO_PAGE; 
                break;
            default:
                frmeContntPgNum[temp] = pageNum; 
                break;
        }

        temp++;
    }

    return frmeContntPgNum;
}


bool *getDirtyFlags(BM_BufferPool *const bufferPlBM) 
{
    frameBfPg *pageFrmeBuff = (frameBfPg *)bufferPlBM->mgmtData;
	int temp = 0;
    bool *flagsForBadPgs = malloc(sizeof(bool) * buffSize);

	printf("Checking for buffer size and iterating.");
    while (temp < buffSize)
    {
        flagsForBadPgs[temp] = pageFrmeBuff[temp].bad;
		printf("+");
        temp++;
    }
    return flagsForBadPgs;
}


int getNumWriteIO(BM_BufferPool *const bufferPlBM) 
{
	printf("Initialising a page frame buffer.");
    frameBfPg *pageFrmeBuff = (frameBfPg *)bufferPlBM->mgmtData;
    return wordCntComplete;
}


int *getFixCounts(BM_BufferPool* const bufferPlBM) 
{
    int* countFinal = malloc(sizeof(int) * bufferPlBM->numPages);
    int temp = 0;
    frameBfPg* pageFrmeBuff = (frameBfPg*)bufferPlBM->mgmtData;
    
    while (temp < bufferPlBM->numPages)
    {
        int clientCount_C = pageFrmeBuff[temp].Client_C;

        switch (clientCount_C)
        {
            case -1:
                countFinal[temp] = 0; 
                break;
            default:
                countFinal[temp] = clientCount_C; 
                break;
        }
    	temp++;
    }

    return countFinal;
}


int getNumReadIO(BM_BufferPool *const bufferPlBM) 
{
	frameBfPg* pgrRame = ( frameBfPg*)bufferPlBM->mgmtData;
    // Increment and return the number of pages that have been read from disk
    return ++pageNumbersPgCnt;
}

