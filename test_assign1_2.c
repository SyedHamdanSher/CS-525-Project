#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "storage_mgr.h"
#include "dberror.h"
#include "test_helper.h"

// test name
char *testName;

/* test output files */
#define TESTPF "test_pagefile.bin"
#define EPAGE_SIZE 400 //page size less that PAGE_SIZE

/* prototypes for test functions */
static void testCreateOpenClose(void);
static void testLastFewFunc(void);
static void testSinglePageContent(void);

/* main function running all tests */
int
main (void)
{
  testName = "";
  
  initStorageManager();

  testLastFewFunc();

  return 0;
}


//checking whether some function works as individual functions
void testLastFewFunc(void)
{
  SM_FileHandle fh;
  SM_PageHandle ph,xh;
  testName = "test empty space file";

  ph = (SM_PageHandle) malloc(PAGE_SIZE);
  TEST_CHECK(createPageFile (TESTPF));
  TEST_CHECK(openPageFile (TESTPF, &fh));
  printf("created and opened file\n");

  // change ph to be a string and write that one to disk
  for (i=0; i < PAGE_SIZE; i++)
    ph[i] = (i % 10) + '0';
  TEST_CHECK(writeBlock (0, &fh, ph));
  printf("writing first block\n");

  /*xh = (SM_PageHandle) malloc(EPAGE_SIZE);

  // change ph to be a string having less size than PAGE_SIZE and write that one to disk
  for (i=0; i < EPAGE_SIZE; i++)
  ph[i] = (i % 10) + '0';
  FILE *pfile;
  //int flag;
  pfile = fopen(fh->fileName, "wb+");
  if(pfile != NULL){
    fseek(pfile,(PAGE_SIZE * (getBlockPos(&fh)+1)),SEEK_SET);
    fwrite(xh, sizeof(char), EPAGE_SIZE, pfile);
    fh->curPagePos=getBlockPos(&fh)+1;
    fh->mgmtInfo = pfile;
    fclose(pfile);
    printf("writing second block with SIZE less than PAGE_SIZE\n"); */
  

  //If the file has less than numberOfPages pages then increase the size to numberOfPages.
  TEST_CHECK(ensureCapacity(2, &fh));
  TEST_DONE();
}

/*void ensureCapacityfuncright(void)
{
  SM_FileHandle fh;
  SM_PageHandle ph;
  testName = "test empty space file";

  ph = (SM_PageHandle) malloc(EPAGE_SIZE);
  memset(ph,'I',EPAGE_SIZE);
  TEST_CHECK(createPageFile (TESTPF));
  TEST_CHECK(openPageFile (TESTPF, &fh));
  printf("created and opened file\n");
  ASSERT_TRUE(strcmp(fh.fileName, TESTPF) == 0, "filename correct");
  ASSERT_TRUE((fh.totalNumPages == 1), "expect 1 page in new file");
  ASSERT_TRUE((fh.curPagePos == 0), "freshly opened file's page position should be 0");

  //If the file has less than numberOfPages pages then increase the size to numberOfPages.
  TEST_CHECK(ensureCapacity(fh->totalNumPages, &fh));
}*/
