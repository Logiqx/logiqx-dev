#
# The makefile that builds this tool (and others like it!)
#

NAME=mamediff
EXT=.exe
EXE=$(NAME)$(EXT)

SRC=src
OBJ=obj

OBJDIRS=$(OBJ)

OBJS=	$(DLOBJS) \
	$(OBJ)/$(NAME).o \
	$(OBJ)/compare.o \
	$(OBJ)/generate.o \

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
# Compiling of seperate modules
#

$(OBJ)/mamediff.o: $(SRC)/mamediff.c $(SRC)/mamediff.h $(SRC)/compare.h $(SRC)/generate.h $(DLSRC)/datlib.h $(DLSRC)/macro.h $(DLSRC)/type.h $(DLSRC)/misc/getopt.h
	@echo Compiling $@...
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h $(SRC)/mamediff.h $(DLSRC)/datlib.h $(DLSRC)/macro.h $(DLSRC)/type.h
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
