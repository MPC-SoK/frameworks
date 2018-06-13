testName=crossTabs
$(if $(testName),,$(error 'testName' must be defined before Makefile.simple is used))
CILPATH=/root/obliv-c
COMMONPATH=../common
REMOTE_HOST=localhost
CFLAGS=-DREMOTE_HOST=$(REMOTE_HOST) -O3
./a.out: $(testName).oc $(testName).c ${COMMONPATH}/util.c $(CILPATH)/_build/libobliv.a
	$(CILPATH)/bin/oblivcc $(CFLAGS) $(testName).oc $(testName).c ${COMMONPATH}/util.c -lm
clean:
	rm -f a.out
