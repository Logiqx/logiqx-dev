#
# The makefile that builds the dat library
#

MD=mkdir

CC=@gcc
CFLAGS+=-Wall -O2 -I $(LOGIQX)/dev

LD=@gcc
LIBS+=-lz -lm

UPX=@upx -9

DLSRC=$(LOGIQX)/dev/datlib/src

DLINCS=	$(DLSRC)/macro.h \
	$(DLSRC)/type.h \
	$(DLSRC)/token.h \

DLOBJ=$(LOGIQX)/dev/datlib/obj

DLOBJDIRS=$(DLOBJ) \
	$(DLOBJ)/drv \
	$(DLOBJ)/hash \
	$(DLOBJ)/misc \
	$(DLOBJ)/mame \
	$(DLOBJ)/mame/msdos \

DLOBJS=	$(DLOBJ)/datlib.o \
	$(DLOBJ)/driver.o \
	$(DLOBJ)/token.o \
	$(DLOBJ)/misc/getopt.o \
	$(DLOBJ)/hash/md5.o \
	$(DLOBJ)/hash/sha1.o \
	$(patsubst $(DLSRC)/drv/%.c, $(DLOBJ)/drv/%.o, \
		$(wildcard $(DLSRC)/drv/*.c)) \
	$(DLOBJ)/mame/msdos/msdos.o \
	$(DLOBJ)/mame/unzip.o

#
# Build the obj tree then build the EXE
#

datlib: dlmaketree $(DLOBJS)

#
# Creating obj directory tree
#

dlmaketree: $(sort $(DLOBJDIRS))

$(sort $(DLOBJDIRS)):
	$(MD) $@

#
# Compiling of separate modules
#

$(DLOBJ)/datlib.o: $(DLSRC)/datlib.c $(DLSRC)/datlib.h $(DLSRC)/driver.h $(DLINCS)
	@echo Compiling $@...
	$(CC) $(CFLAGS) $< -c -o $@

$(DLOBJ)/driver.o: $(DLSRC)/driver.c $(DLSRC)/driver.h $(DLSRC)/type.h
	@echo Compiling $@...
	$(CC) $(CFLAGS) $< -c -o $@

$(DLOBJ)/token.o: $(DLSRC)/token.c $(DLSRC)/token.h
	@echo Compiling $@...
	$(CC) $(CFLAGS) $< -c -o $@

$(DLOBJ)/misc/getopt.o: $(DLSRC)/misc/getopt.c
	@echo Compiling $@...
	$(CC) $(CFLAGS) $< -c -o $@

$(DLOBJ)/hash/%.o: $(DLSRC)/hash/%.c
	@echo Compiling $@...
	$(CC) $(CFLAGS) $< -c -o $@

$(DLOBJ)/drv/%.o: $(DLSRC)/drv/%.c $(DLINCS)
	@echo Compiling $@...
	$(CC) $(CFLAGS) $< -c -o $@

$(DLOBJ)/mame/msdos/msdos.o: $(DLSRC)/mame/msdos/msdos.c
	@echo Compiling $@...
	$(CC) $(CFLAGS) $< -c -o $@

$(DLOBJ)/mame/unzip.o: $(DLSRC)/mame/unzip.c $(DLSRC)/mame/unzip.h $(DLSRC)/mame/osd_cpu.h $(DLSRC)/mame/mame.h
	@echo Compiling $@...
	$(CC) $(CFLAGS) $< -c -o $@

#
# Complete removal of built objects
#

dlclean:
	@echo Removing $(DLOBJ) directory...
	@rm -fr $(DLOBJ)
