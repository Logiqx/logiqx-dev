#
# The makefile that builds this tool (and others like it!)
#

NAME=rominfo
EXT=.exe
EXE=$(NAME)$(EXT)

SRC=src
OBJ=obj

OBJDIRS=$(OBJ)

OBJS=	$(DLOBJS) \
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

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h $(DLSRC)/datlib.h $(DLSRC)/macro.h $(DLSRC)/type.h $(DLSRC)/misc/getopt.h $(DLSRC)/mame/unzip.h
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
