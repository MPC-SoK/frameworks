CILPATH=/root/obliv-c
CFLAGS=-DREMOTE_HOST=$(REMOTE_HOST) -O3
testSorting.o: ../crossTabs.oc testSorting.c ../../common/util.c $(CILPATH)/_build/libobliv.a
	$(CILPATH)/bin/oblivcc $(CFLAGS) -I . ../crossTabs.oc testSorting.c ../../common/util.c -o testSorting.o

clean:
	rm -f testSorting.o crossTabs.oc.cil.c crossTabs.oc.cil.i crossTabs.oc.i
