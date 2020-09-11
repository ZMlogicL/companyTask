### Root Directory of the Project
ROOT_DIR     := ../..

### The current path from Root Directory.
DIR          := Project/Image

### The List of Sub-Directory which have Makefile
### note: If current directory does not have the sub-directory, Variable "SUBDIR" is empty.
SUBDIRS      :=

### List of source files
### note: If current directory does not have C/ASM source files in "src" directory, CSRC/ASRC is empty.
CSRC :=
CSRC += jdsb2r_f2e.c
CSRC += jdscnr1a.c
CSRC += jdsdisp3a.c
CSRC += jdsela2d.c
CSRC += jdsfpt.c
CSRC += jdsiip4b.c
CSRC += jdsimg.c
CSRC += jdsjp7.c
CSRC += jdsltm1a.c
CSRC += jdsmxic.c
CSRC += jdspro.c
CSRC += jdsr2y_f2e.c
CSRC += jdsraw3a.c
CSRC += jdsrdma.c
CSRC += jdsshdr.c
CSRC += jdsxch.c
CSRC += kjdsdisp3a.c
CSRC += jmlbmh2a.c
#CSRC += jdsb2r_f2e.c
CSRC += jdsb2rf2e.c
#CSRC += jdscnr1a.c
CSRC += kjdscnr1a.c
#CSRC += jdsdisp3a.c
CSRC += kjdsdisp3a.c
#CSRC += jdsela2d.c
CSRC += kjdsela2d.c
#CSRC += jdsfpt.c
CSRC += kjdsfpt.c
#CSRC += jdsiip4b.c
CSRC += kjdsiip4b.c
#CSRC += jdsimg.c
CSRC += kjdsimg.c
#CSRC += jdsjp7.c
CSRC += kjdsjp7.c
#CSRC += jdsltm1a.c
CSRC += kjdsltm1a.c
#CSRC += jdsmxic.c
CSRC += kjdsmxic.c
#CSRC += jdspro.c
CSRC += kjdspro.c
#CSRC += jdsr2y_f2e.c
CSRC += jdsr2yf2e.c
CSRC += jdsr2yf2e2.c
CSRC += jdsr2yf2e3.c
#CSRC += jdsraw3a.c
CSRC += kjdsraw3a.c
CSRC += kjdsraw3a2.c
#CSRC += jdsrdma.c
CSRC += kjdsrdma.c
CSRC += jdsrdmatopreg.c
CSRC += jdsrdmacorereg.c
CSRC += jdsproprch.c

#CSRC += jdsshdr.c
CSRC += kjdsshdr.c
CSRC += kjdsshdr2.c
CSRC += kjdsshdr3.c
CSRC += kjdsshdr4.c
CSRC += jdsshdrtbl.c
#CSRC += jdsxch.c
CSRC += kjdsxch.c
#CSRC += jmlbmh2a.c
CSRC += kjmlbmh2a.c
CSRC += jdsdisplch.c
CSRC += jdsdispdcore.c
CSRC += jdsdispgrch.c
CSRC += jdsdispdbg.c
CSRC += jdsdispdsi.c
CSRC += jdsdisphdmi.c
CSRC += jdsprop2m.c
CSRC += jdspropwch.c
CSRC += fhdmitx2p0lp1.c
CSRC += fhdmitx2p0lp2.c
CSRC += fhdmitx2p0lp3.c
CSRC += fmipidsi11txlp.c
CSRC += jdsdisplchtbl.c
CSRC += jdsdispdcoretbl.c
##### REMOVE_ME_RELEASE BEGIN #####
#CSRC += jdsme.c
CSRC += kjdsme.c
##### REMOVE_ME_RELEASE END #####
#CSRC += sdramc.c
CSRC += ksdramc.c
CSRC += ksdramc2.c

ASRC :=

##### REMOVE_ME_RELEASE BEGIN #####
ifeq "$(BUILD_JDSME_OBJ)" "yes"
# target source overwrite only "jdsme.c".
CSRC :=
CSRC += jdsme.c
ASRC :=
endif
##### REMOVE_ME_RELEASE END #####




WS_DIR_NAME  ?= Project
include $(ROOT_DIR)/$(WS_DIR_NAME)/common.mk





### Special compile/assemble
