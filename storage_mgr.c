#include <studio.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "storage_mgr.h"
#include "dberror.h"

/* manipulating page files */

//This functions intializes the Storage Manager. Returns void
void initStorageManager(void){

}

//This creates a pagefile and intializes a memory allocation using calloc
RC createPageFile (char *fileName) {

    FILE *pfile;
    char *initialize;
    initialize = (char*) calloc(PAGE_SIZE, sizeof(char));

    pfile = fopen(fileName, "wb+");
    fwrite(initialize,sizeof(char),PAGE_SIZE,pfile);
    fclose(pfile);
    free(initialize);
    return RC_OK;

}

RC openPageFile (char *fileName, SM_FileHandle *fHandle) {
    FILE *pfile;

    pfile = fopen(fileName, "rb");
    if (pfile == NULL)
    {
        return RC_FILE_NOT_FOUND;
    }
    else
    {
        fHandle->fileName = fileName;
        fHandle->mgmtInfo = pfile;
        fHandle->totalNumPages = 1;
        fHandle->curPagePos = 0;
        fseek(pfile, 0, SEEK_SET);
        fwrite(fileName,PAGE_SIZE,0,pfile);
        fclose(pfile);
        return RC_OK;
    }
}



RC closePageFile (SM_FileHandle *fHandle){
    FILE *pfile;
    pfile = fopen(fHandle ->fileName, "rb");
    if (pfile == NULL){
        return RC_FILE_NOT_FOUND;
    }
    else{
        fclose(pfile);
        return RC_OK;
    }

}
//This function destroys a file. It first checks if the file exists.
RC destroyPageFile (char *fileName){
    int file_existence = access(fileName, F_OK);
    if (file_existence == 0){
        //if 0, file exists, so we destroy it
        remove(fileName);
        return RC_OK;

    }
    else
    {
        return RC_FILE_NOT_FOUND;
    }

}

RC readBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage) {//A page handle is an pointer to an area in memory storing the data of a page
//The method reads the pageNumth block from a file and stores its content in the memory pointed to by the memPage page handle. If the file has less than pageNum pages, the method should return RC_READ_NON_EXISTING_PAGE.
	
	//Open the File using "Read" mode
	pfile = fopen(fHandle->fileName, "r");
	

	// Check if the number of pages in the file are less than pageNum pages. If so, return non-existing page error
	if(pageNum > fHandle->totalNumPages || pageNum<0){
		fclose(pfile);
		return RC_READ_NON_EXISTING_PAGE;
	}

	//Check if the file pointer is null
	if(pfile == NULL){
		return RC_FILE_NOT_FOUND;
	}
	//Find position of the stream
	fseek(pfile, (pageNum*PAGE_SIZE), SEEK_SET);

	//Return an error if the total memory size required is less than the page size to be read
	if(fread(memPage, 1, PAGE_SIZE,pfile)< PAGE_SIZE){
		return RC_ERROR;
	}

	//The position of the current page in the structure file handle has to be updated with the latest pointer position
	fHandle->curPagePos = ftell(pfile);

	fclose(pfile);
	//Return OK after closing the file indicating that the file is read
	return RC_OK;

}



int getBlockPos (SM_FileHandle *fHandle) {
//Return the current page position in a file
	return fHandle->curPagePos;
}

RC readFirstBlock (SM_FileHandle *fHandle, SM_PageHandle memPage) {

//Read the first respective last page in a file
	return readBlock(0,fHandle,memPage);

}

//Read the current, previous, or next page relative to the curPagePos of the file. The curPagePos should be moved to the page that was read. If the user tries to read a block before the first page of after the last page of the file, the method should return RC_READ_NON_EXISTING_PAGE
RC readPreviousBlock (SM_FileHandle *fHandle, SM_PageHandle memPage) {
	
	return readBlock(fHandle->curPagePos-1,fHandle,memPage);

}

// readCurrentBlock reads the curPagePosth page counted from the beginning of the file.
RC readCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage){ 
	
	return readBlock(fHandle->curPagePos, fHandle,memPage);
}

//
RC readNextBlock (SM_FileHandle *fHandle, SM_PageHandle memPage){
	
	return readBlock(fHandle->curPagePos+1,fHandle,memPage);

}

//Read the first respective last page in a file
RC readLastBlock (SM_FileHandle *fHandle, SM_PageHandle memPage){
	
	return readBlock(fHandle->totalNumPages,fHandle,memPage);

}

RC writeBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage) {
//Write a page to disk using either the current position or an absolute position.
	FILE *pfile;
	//int flag;
	pfile = fopen(fHandle->fileName, "wb+");
	if(pfile != NULL){
		fseek(pfile,(PAGE_SIZE * pageNum),SEEK_SET);
		/*flag = */fwrite(memPage, sizeof(char), PAGE_SIZE, pfile);
		fHandle->curPagePos=pageNum;
		fHandle->mgmtInfo = pfile;
		fclose(pfile);
		return RC_OK;
	}
	else{
		return RC_FILE_NOT_FOUND;
	}
}

RC writeCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage){
////Write a page to disk using either the current position or an absolute position.
	int pos; 
	pos = getBlockPos(fHandle->curPagePos);
	RC flag;
	flag = writeBlock(pos, fHandle, memPage);
	return flag;
}

RC appendEmptyBlock (SM_FileHandle *fHandle) {
//Increase the number of pages in the file by one. The new last page should be filled with zero bytes.
	FILE *pfile;
    
    pfile = fopen(fHandle->fileName, "wb+");
    if(pfile!=NULL)
    {
    	char *initialize;
    	initialize = (char*) calloc(PAGE_SIZE, sizeof(char));
    	fwrite(initialize,sizeof(char),PAGE_SIZE,pfile);
    	//
    	fHandle->mgmtInfo = pfile;
       	fHandle->totalNumPages = fHandle->totalNumPages + 1;
       	fHandle->curPagePos = fHandle->totalNumPages-1;
    	//
    	fclose(pfile);
    	free(initialize);
    	return RC_OK;
	}
	else
	{
		fclose(pfile);
		return RC_FILE_NOT_FOUND;
	}
}

RC ensureCapacity(int numOfPages, SM_FileHandle *fHandle) {
//If the file has less than numberOfPages pages then increase the size to numberOfPages.
	if (fHandle->fileName == NULL){
		return RC_FILE_NOT_FOUND;
	}
	else{
		if (fHandle->totalNumPages < numOfPages){
			FILE *pfile;
			pfile = fHandle->mgmtInfo;
			int flag;
			flag = (numOfPages - fHandle->totalNumPages);
			SM_PageHandle ph;
			ph = (SM_PageHandle) malloc(PAGE_SIZE);
			memset(ph,'0',(flag*PAGE_SIZE));
    		fwrite(ph,sizeof(char),(flag*PAGE_SIZE),pfile);
            int n;
            n = fseek(pfile,0, SEEK_END);
			fHandle->curPagePos = n + 1;
			fHandle->totalNumPages = numOfPages;
			fHandle->mgmtInfo = pfile;
			fclose(pfile);
			free(ph);
		}
		else{
			perror("TotalNumber of PAges >= number of pages provided");
		}
	}return RC_OK;
}
