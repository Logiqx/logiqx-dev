#
# The makefile that builds this tool (and others like it!)
#

NAME=filelist
EXT=.exe
EXE=$(NAME)$(EXT)

SRC=src
OBJ=obj

OBJDIRS=$(OBJ)

OBJS=	$(DLOBJ)/misc/getopt.o \
	$(OBJ)/$(NAME).o

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

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h $(DLSRC)/macro.h $(DLSRC)/misc/getopt.h
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
