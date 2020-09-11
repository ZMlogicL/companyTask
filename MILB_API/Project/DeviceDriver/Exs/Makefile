### Root Directory of the Project
ROOT_DIR     := ../../..

### The current path from Root Directory.
DIR          := Project/DeviceDriver/Exs

### The List of Sub-Directory which have Makefile
### note: If current directory does not have the sub-directory, Variable "SUBDIR" is empty.
SUBDIRS      :=

### List of source files
### note: If current directory does not have C/ASM source files in "src" directory, CSRC/ASRC is empty.
CSRC := ddexs.c
CSRC := ddexsbranch.c
CSRC += ddgpv.c
CSRC += ddgpvib.c
CSRC += ddgpvmaster.c
CSRC += ddgpvslave.c
CSRC += ddhdmac.c
CSRC += ddhdmacbranch.c
##### REMOVE_RELEASE BEGIN #####
CSRC += ddrelc.c
CSRC += ddrelccommon.c
##### REMOVE_RELEASE END #####
CSRC += ddpcierc.c
CSRC += ddpcierccommon.c
CSRC += ddpciercint.c
CSRC += ddpcieep.c
CSRC += ddxdmac.c
CSRC += ddxdmaccopysdram.c

ASRC :=
ASRC +=





WS_DIR_NAME ?= Project
include $(ROOT_DIR)/$(WS_DIR_NAME)/common.mk





### Special compile/assemble
