#
# The makefile that builds this tool (and others like it!)
#

NAME=rombuild
EXT=.exe
EXE=$(NAME)$(EXT)

SRC=src
OBJ=obj

OBJDIRS=$(OBJ)

OBJS=	$(DLOBJ)/misc/getopt.o \
	$(DLOBJ)/mame/unzip.o \
	$(DLOBJ)/mame/msdos/msdos.o \
	$(OBJ)/$(NAME).o \
	$(OBJ)/rominfo.o

#
# Build the obj tree then build the EXE
#

all: dlmaketree maketree $(EXE)

include $(LOGIQX)/dev/datlib/makefile

#
# Creating obj directory tree
#

maketree: $(sort $(OBJDIRS))

$(sort $(OBJDIRS)):
	$(MD) $@

#
# Compiling of separate modules
#

$(OBJ)/rombuild.o: $(SRC)/rombuild.c $(SRC)/rombuild.h $(DLSRC)/macro.h $(DLSRC)/misc/getopt.h $(DLSRC)/mame/unzip.h
	@echo Compiling $@...
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJ)/rominfo.o: $(SRC)/rominfo.c $(SRC)/rombuild.h $(DLSRC)/macro.h
	@echo Compiling $@...
	$(CC) $(CFLAGS) $< -c -o $@

#
# Linking the object files to make the EXE
#

$(EXE): $(OBJS)
	@echo Linking $@...
	$(LD) $(OBJS) $(LIBS) -o $@
	$(UPX) $@

#
# Complete removal of built objects
#

clean: dlclean
	@echo Removing $(EXE) and $(OBJ) directory...
	@rm -fr $(EXE) $(OBJ)
