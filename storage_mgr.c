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

void initStorageManager(void) { //initialize Storage manager
//he mgmtInfo to store additional information about the file needed by your implementation, e.g., a POSIX file descriptor mgmtInfo to store any bookkeeping info about a file your storage manager needs.
	//the totalNumPages has to be initialized based on the file size.
	//reserve some space in the beginning of a file to store information such as the total number of pages.
}

RC createPageFile(char * fileName) { //create Page, the totalNumPages has to be initialized based on the file size.
//Create a new page file fileName. The initial file size should be one page. This method should fill this single page with '\0' bytes.
}
RC openPageFile (char *fileName, SM_FileHandle *fHandle) {
    FILE *pfile;

    pfile = fopen(fileName, "r");
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

RC closePageFile (SM_FileHandle *fHandle) {
//Close an open page file or destroy (delete) a page file.
}

RC destroyPageFile (char *fileName) {

}

RC readBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage) {//A page handle is an pointer to an area in memory storing the data of a page
//The method reads the pageNumth block from a file and stores its content in the memory pointed to by the memPage page handle. If the file has less than pageNum pages, the method should return RC_READ_NON_EXISTING_PAGE.
}

int getBlockPos (SM_FileHandle *fHandle) {
//Return the current page position in a file
}

RC readFirstBlock (SM_FileHandle *fHandle, SM_PageHandle memPage) {
//Read the first respective last page in a file
}
RC readPreviousBlock (SM_FileHandle *fHandle, SM_PageHandle memPage) {
//Read the current, previous, or next page relative to the curPagePos of the file. The curPagePos should be moved to the page that was read. If the user tries to read a block before the first page of after the last page of the file, the method should return RC_READ_NON_EXISTING_PAGE
}
RC readCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage) { // readCurrentBlock reads the curPagePosth page counted from the beginning of the file.

}
RC readNextBlock (SM_FileHandle *fHandle, SM_PageHandle memPage) {

}
RC readLastBlock (SM_FileHandle *fHandle, SM_PageHandle memPage) {
//Read the first respective last page in a file
}

RC writeBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage) {
//Write a page to disk using either the current position or an absolute position.
}

RC writeCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage){
////Write a page to disk using either the current position or an absolute position.

}

RC appendEmptyBlock (SM_FileHandle *fHandle) {
//Increase the number of pages in the file by one. The new last page should be filled with zero bytes.
}

RC ensureCapacity(int numOfPages, SM_FileHandle *fHandle) {
//If the file has less than numberOfPages pages then increase the size to numberOfPages.
}
