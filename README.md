# CS-525-Project
Personnel information:

 ( Name, CWID, Email id, Leader Name)
1. Ericson Akatakpo, A20349354, eakatakp@hawk.iit.edu, Ericson Akatakpo
2. Syed Hamdan Sher, A20378710, ssher1@gmail.com, Ericson Akatakpo
3. James Mwakichako, A20297757, jmwakich@hawk.iit.edu, Ericson Akatakpo
4. Gaurav Gadhvi, A20344904, ggadhvi@gmail.com, Ericson Akatakpo



File list:

1. dberror.h
2. dberror.c
3. storage_mgr.c
4. storage_mgr.h
5. test_assign1_1.c
6. test_helper.h
7. Makefile.mk



Installation instruction:
Make sure while running the make command on fourier there should be no object file or executable file already created.
It worked locally as well as at fourier




Function descriptions: of all additional 
functions

Assignement implementation of a storage manager includes creating and opening a file, reading blocks from a file on disk into memory and writing blocks from memory to a file on disk. 

CreatePageFile:
	This creates a pagefile and intializes a memory allocation using calloc

OpenPageFile:
	Opens an existing page file. Should return RC_FILE_NOT_FOUND if the file does not exist. 
The second parameter is an existing file handle. If opening the file is successful,then the fields of this file handle should be initialized with the information about the opened file. 
For instance, you would have to read the total number of pages that are stored in the file from disk.

ClosePageFile:
	This is used to close the existing page in the file or gives an error message if the page does not exist.

DestroyPageFile:
	This is used to remove the page from the file or gives an error message if the page does not exist.

GetBlockPos:
	This is used to maintain the track of the current page position in the file by returning the current block position.

ReadCurrentBlock, ReadPreviousBlock, ReadNextBLock:
	This reads the current, previous or next page depending on the curPagePos of the file.The curPagePos should be moved to the page that was read.

ReadFirstBlock, ReadLastBlock:
	This reads the first and the last pages in the file.

WriteBlock,WriteCurrentBlock:
  	This is used to write the page to the disk by either using the current position or an absolute position.

AppendEmptyBlock:
	This is used to increment the number of pages in the file by one. The page that is incremented is assigned zero bytes.

EnsureCapacity:
	this method checks if the file has pages less than numberofPages. If so, it adds some bytes of memory to reach the size which is equal to numberofPages passed as parameter + PAGE_SIZE.

Additional error codes: of all additional error codes

#define RC_TOTALNUMPAGES_GREATEROREQUALTO_NUMOFPAGES 999
if the total number of pages is greater or equal to the number of pages passed to the function then this error code is used.

#define RC_TOTALMEMSIZE_LESSTHAN_PAGESIZE 998
If the total memory size of the file opened is less than the page size then this error code is used.

Data structure: main data structure used.
Character Arrays using pointers

Extra credit: of all extra credits

Additional files: of all additional files

Test cases: of all additional test cases added (leave if blank if there isn't any)


















..............................

Personnel information ( Name, CWID, Email id, Leader Name)


File list 


Installation instruction


 


Function descriptions: of all additional functions


 


Additional error codes: of all additional error codes (leave if blank if there isn't any)


 


Data structure: main data structure used (leave if blank if there isn't any)


 


Extra credit: of all extra credits (leave if blank if there isn't any)


 


Additional files: of all additional files


 


Test cases: of all additional test cases added (leave if blank if there isn't any)

