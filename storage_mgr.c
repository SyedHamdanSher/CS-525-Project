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

}

RC createPageFile(char * fileName) { //create Page

}
RC openPageFile(char *fileName, SM_FileHandle *fHandle) {

}

RC closePageFile (SM_FileHandle *fHandle) {

}

RC destroyPageFile (char *fileName) {

}

RC readBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage) {

}

int getBlockPos (SM_FileHandle *fHandle) {

}

RC readFirstBlock (SM_FileHandle *fHandle, SM_PageHandle memPage) {

}
RC readPreviousBlock (SM_FileHandle *fHandle, SM_PageHandle memPage) {

}
RC readCurrentBlock (SM_FileHandle *fHandle, SM_PageHandle memPage) {

}
RC readNextBlock (SM_FileHandle *fHandle, SM_PageHandle memPage) {

}
RC readLastBlock (SM_FileHandle *fHandle, SM_PageHandle memPage) {

}

RC writeBlock (int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage) {

}

RC ensureCapacity(int numOfPages, SM_FileHandle *fHandle) {

}

