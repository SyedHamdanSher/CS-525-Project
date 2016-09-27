TOKEN = -g -Wall
COMP = gcc


default: test_1


dberror.o: dberror.c
	$(COMP) $(TOKEN) -o dberror.o -c dberror.c
	

storage_mgr.o: storage_mgr.c
	$(COMP) $(TOKEN) -c storage_mgr.c


test_assign1_1.o: test_assign1_1.c
	$(COMP) $(TOKEN) -c test_assign1_1.c


test_1: test_assign1_1.o storage_mgr.o dberror.o
	$(COMP) $(TOKEN) test_assign1_1.o storage_mgr.o dberror.o -o test_1 


garbage:
	rm test_1 test_assign1_1.o storage_mgr.o dberror.o
	