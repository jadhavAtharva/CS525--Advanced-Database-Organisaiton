#include "record_mgr.h"
#include <stdio.h>
#include "buffer_mgr.h"
#include <stdlib.h>
#include "storage_mgr.h"
#include <string.h>

BM_PageHandle *pageHndlBM;
BM_BufferPool *poolBuff_BM;
RecordManager *managerRecordRM;

int getFreeSlotIndex(char* data, int recordSize)
{
	int totalSlots ;
	if(recordSize != 0){
		totalSlots = (PAGE_SIZE / recordSize);
	}else{
		totalSlots = 0;
	}
	int temp, index = 0;
	while(totalSlots > index){
		temp = index * recordSize;
        if (*(data + temp) != '#')
            return index;
		index++;
	}
    return -1;
}

char *incrementPointer(char *pointer, int offset)
{
	int tempVal = offset;
    pointer = pointer + tempVal;
	printf("");
    return pointer;
}

RC initRecordManager(void *mgmtData)
{
	int i = 0;
	printf(".");
	if(i == 0){
		return RC_OK;
	}
	printf(".");
}

RC shutdownRecordManager()
{
	int i = 0;
	(i == 0) ? realloc(managerRecordRM, 0) : printf("");
	return RC_OK;
}

RC createTable(char *name, Schema *schema)
{
	char data[PAGE_SIZE];
	printf("_____Creating Table_____");
	char *pageHndlBM = data;
	bool temp = true;

	int const NUMBER_OF_TUPLES = 0;
	bool exceptionThrown;
	SM_FileHandle fileHandle;

	if(temp){
		managerRecordRM = (RecordManager *)malloc(sizeof(RecordManager));
	}

	initBufferPool( &managerRecordRM->bufferPool, name, 100, RS_LRU, NULL);
	int iterator = 0;
	bool fl = true;
	int attributesOfTableCreate[] = {NUMBER_OF_TUPLES, 1, schema->numAttr, schema->keySize};
	int i = 0;

	while(iterator < sizeof(attributesOfTableCreate) / sizeof(attributesOfTableCreate[0])){
		(i == 0) ? *(int*)pageHndlBM = attributesOfTableCreate[iterator] : printf("");
		if(fl && i == 0){
			pageHndlBM = pageHndlBM + sizeof(int);
		}

		iterator++;
	}

	for (int iterator = 0; iterator < schema->numAttr; iterator++)
	{
		if(i == 0){
			strncpy(pageHndlBM, schema->attrNames[iterator], 20);
			pageHndlBM = pageHndlBM + 20;
		}
		(fl) ? *(int*)pageHndlBM = (int)schema->dataTypes[iterator] : printf("");
		if(fl && i == 0){
			pageHndlBM = pageHndlBM + sizeof(int);
		}
		(i == 0) ? *(int*)pageHndlBM = (int)schema->typeLength[iterator] : printf("");
		pageHndlBM = pageHndlBM + sizeof(int);
	}

	exceptionThrown = false;
	

	int result = createPageFile(name);

	if(i == 0){
		(result != RC_OK) ? exceptionThrown = true : printf("");
	}

	switch((!exceptionThrown)){
		case 1:
			result = openPageFile(name, &fileHandle);
			if(fl){
				(result != RC_OK) ? exceptionThrown = true : printf("");
			}
		default:
			printf("");
	}

	switch((!exceptionThrown)){
		case 1:
			result = writeBlock(0, &fileHandle, data);
			if(fl){
				(result != RC_OK) ? exceptionThrown = true : printf("");
			}
		default:
			printf("");
	}

	switch((!exceptionThrown)){
		case 1:
			result = closePageFile(&fileHandle);
			if(fl){
				(result != RC_OK) ? exceptionThrown = true : printf("");
			}
		default:
			printf("");
	}

	switch((exceptionThrown)){
		case 1:
			return result;
		default:
			printf("");
	}
	return RC_OK;
}

RC openTable(RM_TableData *rel, char *name)
{
	bool fl = TRUE;
	int one = 1;
    rel->mgmtData = managerRecordRM;
	int zero = 0;
    int numOfAttr;
   
    pinPage(&managerRecordRM->bufferPool, &managerRecordRM->pageHandle, 0);
	rel->name = name;
    pageHndlBM = (char *)managerRecordRM->pageHandle.data;
	printf("");
	pageHndlBM = incrementPointer(pageHndlBM, 4);
    managerRecordRM->totalRecordsInTable = *(int *)(char *)managerRecordRM->pageHandle.data;
	printf("");
    managerRecordRM->firstFreePage.slot = zero;
	int i = 0;
    managerRecordRM->firstFreePage.page = one;
	printf("");
	if(i == 0){
		pageHndlBM = incrementPointer(pageHndlBM, 4);
		switch(fl){
			case 1:
				numOfAttr = *(int *)pageHndlBM;
				pageHndlBM = incrementPointer(pageHndlBM, 4);
			default:
				printf("");
		}
	}
    Schema *schema = (Schema *)malloc(sizeof(Schema));
	if(fl){
		schema->numAttr = numOfAttr;
		(fl) ? schema->attrNames = malloc(numOfAttr * sizeof(char *)) : printf("");
		(i == 0) ? schema->dataTypes = malloc(numOfAttr * sizeof(DataType)) : printf("");
		(fl) ? schema->typeLength = malloc(numOfAttr * sizeof(int)) : printf("");
	}
	if(fl){
		    for (int i = 0; i < numOfAttr; i++){
				schema->attrNames[i] = malloc(20);
			}
	}
    i = 0;
    while (i < schema->numAttr) 
    {
        // Allocate memory for attribute name
        schema->attrNames[i] = (char *)malloc(20);
		switch(schema->attrNames[i] == NULL){
			case 1: 
				return RC_ERROR;
			default:
				printf("");
		}
		if(fl){
			(i == 0) ? strncat(schema->attrNames[i], pageHndlBM, 20) : printf("");
        	(fl) ? pageHndlBM = incrementPointer(pageHndlBM, 20) : printf("");
		}
		int intSiz = 4;
		int intSize = 4;
		if(fl){
			schema->dataTypes[i] = *(int *)pageHndlBM;
			printf("");
			i = i + 1;
			pageHndlBM = incrementPointer(pageHndlBM, intSiz);
			printf("");
			(fl) ? schema->typeLength[i] = *(int *)pageHndlBM : printf("");
			(i == 0) ? fl = TRUE : printf("");
			pageHndlBM = incrementPointer(pageHndlBM, intSize);
			i++;
		}
    }
    rel->schema = schema;
	switch(fl){
		case 1:
			unpinPage(&managerRecordRM->bufferPool, pageHndlBM);
			i = 0;
    		forcePage(&managerRecordRM->bufferPool, pageHndlBM);
		default:
			printf("");
	}
    
    return RC_OK;
}

RC closeTable(RM_TableData *rel)
{
	int temp = 0;
	if(temp == 0){
	RecordManager *managerRecordRM = rel->mgmtData;
	shutdownBufferPool(&managerRecordRM->bufferPool);
	}
	printf("");
	return RC_OK;
}

RC deleteTable(char *name)
{
	bool temp1 = TRUE;
	(temp1) ? destroyPageFile(name) : printf("");
	return RC_OK;
}

int getNumTuples(RM_TableData *rel)
{
	int totRecords;
	RecordManager *managerRecordRM = rel->mgmtData;
	(managerRecordRM != NULL) ? totRecords = managerRecordRM->totalRecordsInTable : printf("");
	return totRecords;
}

RC insertRecord(RM_TableData *rel, Record *record)
{
    bool checkrc, copybit, markdirtycheck;
    bool validslotsearch = true;
    bool assign = true;
	int j = 9;
    RID *recordID = &record->id;

    char *dataptr, *recordptr;
	bool fl = TRUE;

    recordID->slot = -1;
    bool ptrvalue;
    int Sizeofrecord, Offsetofrecord;
    Sizeofrecord = getRecordSize(rel->schema);

    markdirtycheck = true;
    ptrvalue = true;
    checkrc = true;
    switch(assign)
    {
        case true:
        managerRecordRM = rel->mgmtData;
        pageHndlBM = &managerRecordRM->pageHandle;
        poolBuff_BM = &managerRecordRM->bufferPool;
        break;

        default:
        break;
    }

    int i=0;
    while(recordID->slot == -1)
    {
        switch(!validslotsearch)
        {
            case true:
            unpinPage(poolBuff_BM, pageHndlBM);
            recordID->page=recordID->page+1;
            break;
            
            default:
            recordID->page = managerRecordRM->firstFreePage.page;
            validslotsearch = false;
            break;
        }
        
        if(i>=0)
        {
			switch(fl){
				case 1:
					(fl) ? pinPage(poolBuff_BM, pageHndlBM, recordID->page) : printf("");
					fl = TRUE;
					dataptr = managerRecordRM->pageHandle.data;
					ptrvalue=true;
					(fl) ? recordID->slot = getFreeSlotIndex(dataptr, Sizeofrecord) : printf("");
					j = 0;
					markdirtycheck=true;
				default:
					printf("");
			}
        }
        i++;
		j++;
    }
    
    copybit = true;
    recordptr = dataptr;

    switch(markdirtycheck == true)
    {
        case true:
        if(markDirty(poolBuff_BM, pageHndlBM))
        {
            return RC_MARK_DIRTY_FAILED;
        }
        break;

        default:
        break;
    }

    Offsetofrecord = recordID->slot * Sizeofrecord;
    recordptr = incrementPointer(recordptr, Offsetofrecord);

    switch(ptrvalue)
    {
        case true:
        *recordptr = '#';
        recordptr++;
        break;

        default:
        break;
    }

    switch(copybit)
    {
        case true:
        memcpy(recordptr, record->data + 1, Sizeofrecord - 1);
        break;

        default:
        break;
    }

    switch(checkrc)
    {
        case true:
        managerRecordRM->totalRecordsInTable=managerRecordRM->totalRecordsInTable+1;
        pinPage(poolBuff_BM, pageHndlBM, 0);
        break;
    }

    if(unpinPage(poolBuff_BM, pageHndlBM))
    {
        return RC_UNPIN_PAGE_FAILED;
    }
        
    return RC_OK;
}



RC deleteRecord(RM_TableData *rel, RID id)
{
	int Sizeofrecord, Offsetofrecord, ispinpage = 1;
	bool assign, ismodify;
	Offsetofrecord = id.slot * Sizeofrecord;
	assign=true;
	char *Datapageptr;
	bool fl = true;
	Sizeofrecord = getRecordSize(rel->schema);

	RecordManager *recordManager;
	switch(assign==true){
		case 1:
			recordManager = rel->mgmtData;
			if(fl){
				pageHndlBM = &recordManager->pageHandle;
			}
			fl = true;
			ismodify=true;
			poolBuff_BM = &recordManager->bufferPool;
		default:
			printf("");
	}


	(ispinpage==1) ? pinPage(poolBuff_BM, pageHndlBM, id.page) : printf("");

	switch(ismodify==true){
		case 1:
			if(fl){
				managerRecordRM->firstFreePage.page = id.page;
				Datapageptr = managerRecordRM->pageHandle.data;
				Datapageptr = incrementPointer(Datapageptr, Offsetofrecord);
			}
		default:
			printf("");
	}

	switch(unpinPage(poolBuff_BM, pageHndlBM)){
		case 1:
			return RC_UNPIN_PAGE_FAILED;
		default:
			printf("");
	}

	switch(markDirty(poolBuff_BM, pageHndlBM)){
		case 1:
			return RC_MARK_DIRTY_FAILED;
		default:
			printf("");
	}

	return RC_OK;
}

RC updateRecord(RM_TableData *rel, Record *record)
{
    char *Datapageptr;
	int assign=0;
	int Sizeofrecord;
	int Offsetofrecord;
	bool inc;
	bool fl = TRUE;
	int i = 0;
	bool copybit;

    switch(assign)
    {
        case 0:
        managerRecordRM = rel->mgmtData;
        poolBuff_BM = &managerRecordRM->bufferPool;
        pageHndlBM = &managerRecordRM->pageHandle;
        inc = true;
        copybit = true;
        break;
        
        default:
        break;
    }

	switch(fl){
		case 1:
			Sizeofrecord = getRecordSize(rel->schema);
			fl = TRUE;
			if(fl){
				RID id = record->id;
				(i == 0) ? Offsetofrecord = id.slot * Sizeofrecord : printf("");
				(fl) ? pinPage(poolBuff_BM, pageHndlBM, id.page) : printf("");
				(i == 0) ? Datapageptr = managerRecordRM->pageHandle.data : printf("");
			}
			
		default:
			printf("");
	}
    switch(inc)
    {
        case true:
        Datapageptr = incrementPointer(Datapageptr, Offsetofrecord);
        Datapageptr=Datapageptr+1;
        break;

        default:
        break;
    }

    switch(copybit)
    {
        case true:
        memcpy(Datapageptr, record->data + 1, Sizeofrecord);
        break;
    }

    return (unpinPage(poolBuff_BM, pageHndlBM)) ? RC_UNPIN_PAGE_FAILED : (markDirty(poolBuff_BM, pageHndlBM)) ? RC_MARK_DIRTY_FAILED : RC_OK;
}

RC getRecord(RM_TableData *rel, RID id, Record *record)
{
	int assign=0, j = 0, pagenum;
	char *newdataptr;
	int i = 0, Sizeofrecord, Offsetrecord;
	char *dataptr;
	bool fl = true, inc, copybit;

	switch(assign==0){
		case 1:
			pageHndlBM = &managerRecordRM->pageHandle;
			managerRecordRM = rel->mgmtData;
			poolBuff_BM = &managerRecordRM->bufferPool;
		default:
			printf("");
	}
	record->id = id;
	if(fl){
		j = 1;
	}
	pagenum = id.page;
	if(fl){
		copybit=true;
		inc=true;
	}

	switch(pinPage(poolBuff_BM, pageHndlBM, pagenum) == RC_OK){
		case 1:
			Sizeofrecord = getRecordSize(rel->schema);
			printf("");
			Offsetrecord = id.slot * Sizeofrecord;
			switch(inc == true && i == 0){
				case 1:
					if(fl){
						dataptr = managerRecordRM->pageHandle.data;
					}
					
					(i == 0) ? dataptr = incrementPointer(dataptr, Offsetrecord) : printf("");

					(fl) ? newdataptr = record->data : printf("");
					if(fl && i == 0){
						newdataptr=newdataptr+1;
					}
			}

			(copybit==true) ? memcpy(newdataptr, dataptr + 1, Sizeofrecord) : printf("");

			switch(unpinPage(poolBuff_BM, pageHndlBM) != RC_OK){
				case 1:
					return RC_UNPIN_PAGE_FAILED;
				default:
					printf("");
			}

		default:
			printf("");
	}

	switch(pinPage(poolBuff_BM, pageHndlBM, pagenum) != RC_OK){
		case 1:
			return RC_PIN_PAGE_FAILED;
		default:
			printf("");
	}

	return RC_OK;
}

//// SCAN FUNCTIONS 

RC startScan(RM_TableData* rel, RM_ScanHandle* scan, Expr* cond)
{
	bool fl = true;
	int i = 0;
    RecordManager *scanManager= malloc(sizeof(RecordManager));

	switch(cond == 0){
		case 1:
			return RC_SCAN_CONDITION_NOT_FOUND;
		default:
			printf("");
	}

	if(fl){
		openTable(rel, "ScanTable");
	}

    RecordManager *tableManager;
	if(fl){
		tableManager = rel->mgmtData;
		tableManager->totalRecordsInTable = 20;
	}

   	switch(!scanManager){
		case 1:
			return RC_MELLOC_MEM_ALLOC_FAILED;
		default:
			printf("");
   	}

    (i == 0) ? (*scanManager).recordID.page = 1 : printf("");
    (fl) ? (*scanManager).recordID.slot = 0 : printf("");
    (i == 0) ? (*scanManager).scanCount = 0 : printf("");
    (fl) ? (*scanManager).condition = cond : printf("");

    if(i == 0){
		(*scan).mgmtData = scanManager;
	}

    if(fl){
		(*scan).rel = rel;
		fl = TRUE;
	}

    return RC_OK;
}

extern RC next(RM_ScanHandle *scan, Record *record)
{
	 Schema *schema = scan->rel->schema;
	int sizeOfRecord = getRecordSize(schema);
    RecordManager *scanManager = ((RM_ScanHandle *)scan)->mgmtData;
	int totalSlotsCount = (PAGE_SIZE + sizeOfRecord - 1) / sizeOfRecord;
    RecordManager *scanTableManager = scan->rel->mgmtData;
	int scanCount = (*scanManager).scanCount;
	int totalRecordsInTable = getNumTuples(scan->rel);
	int i = 9;
	bool fl = TRUE;
    switch (!scanManager->condition)
    {
        case true:
            return RC_SCAN_CONDITION_NOT_FOUND;
        default:
            break;
    }

    Value *result = (Value *)malloc(sizeof(Value));

    switch (!totalRecordsInTable)
    {
        case true:
            return RC_RM_NO_MORE_TUPLES;
        default:
            break;
    }

    RID scanManagerRecordID = {scanManager->recordID.page, scanManager->recordID.slot};
	int j =0;
    while (totalRecordsInTable >= scanCount)
    {
		fl = TRUE;
		i = 0;
        if (scanCount != 0)
        {
            (i == 0) ? scanManager->recordID.slot = scanManager->recordID.slot + 1 : printf("");
            switch ((scanManager->recordID.page + 1) * totalSlotsCount <= scanTableManager->totalRecordsInTable)
            {
                case true:
                    scanManager->recordID.slot = 0;
                    scanManager->recordID.page = scanManager->recordID.page + 1;
                    break;
                default:
                    break;
            }
        }
        else
        {
            scanManager->recordID.page = 1;
			i = 0;
            scanManager->recordID.slot = 0;
        }
		printf("");
        pinPage(&scanTableManager->bufferPool, &scanManager->pageHandle, scanManager->recordID.page);
		j = 9;
        char *data = scanManager->pageHandle.data;
        int recordOffset = scanManager->recordID.slot * sizeOfRecord;
		if(fl){
			data = incrementPointer(data, recordOffset);
			j = 10;
        	memcpy(&(record->id), &(scanManager->recordID), sizeof(RID));
		}
        char *dataPointer = record->data + 1;
		switch(fl){
			case 1:
				memcpy(dataPointer, data + 1, sizeOfRecord);
        		(j == 10) ? evalExpr(record, schema, scanManager->condition, &result) : printf("");
			default:
				printf("");
		}
        scanManager->scanCount++;
        scanCount++;
        switch (result->v.boolV)
        {
            case TRUE:
                unpinPage(&scanTableManager->bufferPool, &scanManager->pageHandle);
                return RC_OK;
            default:
                break;
        }
    }
    
	if(fl){
		(fl) ? unpinPage(&scanTableManager->bufferPool, &scanManager->pageHandle) : printf("");
		switch(fl) {
			case 1:
				(*scanManager).recordID.page = 1;
				if(fl){
					(*scanManager).recordID.slot = 0;
				}
				(*scanManager).scanCount = 0;
			default: 
				printf("");
		}
	}
    return RC_RM_NO_MORE_TUPLES;
}

extern RC closeScan(RM_ScanHandle *scan)
{
    RecordManager *scanManager = (RecordManager *) scan->mgmtData;
	int j = 9;
	BM_BufferPool *bufferPool;
	RecordManager *scanTableManager = scan->rel->mgmtData;
	BM_PageHandle *pageHandle;
    RecordManager *tableManager = (RecordManager *) scan->rel->mgmtData;
	bool fl = true;
	int i = 0;
	
	switch(fl){
		case 1:
			switch(scanManager->scanCount >= 1){
				case 1:
					bufferPool = &scanTableManager->bufferPool;
					printf("");
					pageHandle = &scanManager->pageHandle;
					if(fl){
						unpinPage(bufferPool, pageHandle);
					}
					(fl) ? (*scanManager).recordID.page = 1 : printf("");
					(i == 0) ? (*scanManager).recordID.slot = 0 : printf("");
					(fl) ? (*scanManager).scanCount = 0 : printf("");
				default:
					printf("");								
			}
		default:
			printf("");
		}

	if(fl){
		free(scanManager);
    	scan->mgmtData = NULL;
	}

    return RC_OK;
}

//// SCHEMA FUNCTIONS 

int getRecordSize(Schema *schema)
{
	int sizeOfRecord = 0, attributeSize = 0;
	int temp = 0;
	bool fl = true;

	while(temp < schema->numAttr){

		if(schema->dataTypes[temp] == DT_STRING){
			attributeSize = schema->typeLength[temp];
		}
		else if(schema->dataTypes[temp] == DT_INT){
			attributeSize = sizeof(int);
		}
		else if(schema->dataTypes[temp] == DT_FLOAT){
			attributeSize = sizeof(float);
		}
		else if(schema->dataTypes[temp] == DT_BOOL){
			attributeSize = sizeof(bool);
		}
		else{
			printf("");
		}

    	if(fl){
			sizeOfRecord = sizeOfRecord + attributeSize;
		}
		temp++;
	}

	return ++sizeOfRecord;
}

Schema *createSchema(int numberofAttribute, char **attributeNames, DataType *dataTypes, int *typeLength, int sizeOfKey, int *keys)
{
	bool j;
	int schemaSize = sizeof(Schema);
	bool fl = true;
	int i = 0;
	Schema *sch = (Schema *)malloc(schemaSize);

	(attributeNames != NULL) ? sch->attrNames = attributeNames : printf("");
	(attributeNames == NULL) ? sch->attrNames = NULL : printf("");

	(dataTypes != NULL) ? sch->dataTypes = dataTypes : printf("");
	(dataTypes == NULL) ? sch->dataTypes = NULL : printf("");

	(numberofAttribute > 0) ? sch->numAttr = numberofAttribute : printf("");

	if(fl){
		sch->keyAttrs = keys;
	}
	
	(typeLength > 0) ? sch->typeLength = typeLength : printf("");
	(typeLength <= 0) ? sch->typeLength = 0 : printf("");

	if(fl && i == 0){
		sch->keySize = sizeOfKey;
	}
	return sch;
}

RC freeSchema(Schema *schema)
{	
	bool fl = TRUE;
	if(fl){
		realloc(schema, 0);
	}
	printf("");
	return RC_OK;
}


//// DEALING WITH RECORDS AND ATTRIBUTE VALUES

RC createRecord(Record **record, Schema *schema)
{
	bool temp = true;
	char *dataPointer;
	Record *newRec;
	switch(!temp){
		case 1:
			printf("");
		default :
			newRec = (Record *)calloc(1,sizeof(Record));
			printf("");
			newRec->id.page = newRec->id.slot = -1;
			newRec->data = (char *)calloc(1,getRecordSize(schema));
			dataPointer = newRec->data;
			*record = newRec;
			*dataPointer = '\0';
			*dataPointer++ = '-';
	}
	return RC_OK;
}

RC attrOffset(Schema *schema, int attributeNumber, int *result)
{
	*result = 1;
	int iterator = 0;

	while(iterator < attributeNumber){
		if(schema->dataTypes[iterator] == DT_STRING){
			*result += schema->typeLength[iterator];
		}
		else if(schema->dataTypes[iterator] == DT_INT){
			*result += sizeof(int);
		}
		else if(schema->dataTypes[iterator] == DT_FLOAT){
			*result += sizeof(float);
		}
		else if(schema->dataTypes[iterator] == DT_BOOL){
			*result += sizeof(bool);
		}
		else{
			printf("");
		}
		iterator++;
	}

	return RC_OK;
}

RC freeRecord(Record *record)
{
	bool fl1 = true;
	if(fl1){
		realloc(record, 0);
	}
	printf("");
	return RC_OK;
}

RC getAttr(Record *record, Schema *schema, int attributeNumber, Value **value)
{   
	
	int i = 0, offset = i, j = 0, attributeSize = j;
	attrOffset(schema, attributeNumber, &offset);
	bool fl = true;
	char *dataPtr = incrementPointer(record->data, offset);
	Value *attribute = (Value *)calloc(1, sizeof(Value));
	if(fl){
		printf("");
		schema->dataTypes[attributeNumber] = (attributeNumber == 1) ? 1 : schema->dataTypes[attributeNumber];
	}

	switch(DT_STRING == schema->dataTypes[attributeNumber]){
		case 1:
			attribute->v.stringV = (char *)calloc(schema->typeLength[attributeNumber] + 1, sizeof(char));
			printf("");
			if(fl){
				attribute->v.stringV = strndup(dataPtr, schema->typeLength[attributeNumber]);

				attribute->dt = DT_STRING;
			}
		default:
			printf("");
	}

	if(fl){
		int value = *((int *)dataPtr);
		switch(schema->dataTypes[attributeNumber] == DT_INT){
			case 1:
				printf("");
				if(fl){
					attribute->v.intV = value;
					attribute->dt = DT_INT;
					attributeSize = sizeof(int);
				}
			default:
				printf("");
		}
	}

	if(fl){
		float value = *((float *)dataPtr);
		switch(schema->dataTypes[attributeNumber] == DT_FLOAT){
			case 1:
				printf("");
				if(fl){
					attribute->v.floatV = value;
					attribute->dt = DT_FLOAT;
					attributeSize = sizeof(float);
				}
			default:
				printf("");
		}
	}

	if(fl){
		bool value = *((bool *)dataPtr);
		switch(schema->dataTypes[attributeNumber] == DT_BOOL){
			case 1:
				printf("");
				if(fl){
					attribute->v.boolV = value;
					attribute->dt = DT_BOOL;

					attributeSize = sizeof(bool);
				}
		}
	}

	*value = attribute;
	fl = TRUE;
	return RC_OK;
}

RC setAttr(Record *record, Schema *schema, int attributeNumber, Value *value)
{
	bool callattroffset=true;
	bool fl = true;
	char *dataptr;
	int offset_value = 0, incbit, offset_new;
	int len, assignbit, valueFl, valueStr, valueIn, valueBl;
	

	(callattroffset!=false) ? incbit=1, assignbit=1, attrOffset(schema, attributeNumber, &offset_value) : printf("");

	(incbit!=0) ? dataptr = record->data, dataptr = incrementPointer(dataptr, offset_value) : printf("");

	if(fl){
		valueFl = DT_FLOAT;
		valueStr = DT_STRING;
		valueIn = DT_INT;
		valueBl = DT_BOOL;
	}

	switch(assignbit!=0){
		case 1:

			switch(schema->dataTypes[attributeNumber] == valueFl){
				case 1:
					if (incbit!=0)
					{
						dataptr = incrementPointer(record->data, sizeof(float));
					}
				default:
					printf("");
			}
			
			switch(schema->dataTypes[attributeNumber] == valueBl){
				case 1:
					if (incbit!=0)
					{
						dataptr = incrementPointer(value->v.stringV, sizeof(bool));
					}
				default:
					printf("");
			}
		
			switch(schema->dataTypes[attributeNumber] == valueStr){
				case 1:
					len = schema->typeLength[attributeNumber];

					if(fl){
					strncpy(dataptr, value->v.stringV, len);
					}

					(fl) ? offset_new = schema->typeLength[attributeNumber] : printf("");
					
					if (incbit!=0)
					{
						fl = TRUE;
						dataptr = incrementPointer(dataptr, offset_new);
					}
			}

			switch(schema->dataTypes[attributeNumber] == valueStr){
				case 1:
					len = schema->typeLength[attributeNumber];

					if(fl){
					strncpy(dataptr, value->v.stringV, len);
					offset_new = schema->typeLength[attributeNumber];
					}
					
					if (fl && incbit!=0)
					{
						dataptr = incrementPointer(dataptr, offset_new);
					}
				default:
					printf("");
			}

			switch(schema->dataTypes[attributeNumber] == valueIn){
				case 1:
					*(int *)dataptr = value->v.intV;

					if (incbit!=0)
					{
						dataptr = incrementPointer(dataptr, sizeof(int));
					}
				default:
					printf("");
			}

		}

	return RC_OK;
}
