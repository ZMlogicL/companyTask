### Root Directory of the Project
ROOT_DIR     := ../../..

### The current path from Root Directory.
DIR          := Project/DeviceDriver/ARM

### The List of Sub-Directory which have Makefile
### note: If current directory does not have the sub-directory, Variable "SUBDIR" is empty.
SUBDIRS      :=

### List of source files
### note: If current directory does not have C/ASM source files in "src" directory, CSRC/ASRC is empty.
CSRC :=
CSRC += ddcache.c
CSRC += ddexiu.c
CSRC += ddgic.c
CSRC += ddnic.c
CSRC += ddtimestamp.c
CSRC += ddwdog.c
CSRC += ddxdmasnap.c
CSRC += ddipcu.c
CSRC += ddipcumb.c

ASRC :=
ASRC += ddarmasm.s
ASRC += ddcacheasm.s





WS_DIR_NAME ?= Project
include $(ROOT_DIR)/$(WS_DIR_NAME)/common.mk





### Special compile/assemble
