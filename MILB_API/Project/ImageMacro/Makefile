### Root Directory of the Project
ROOT_DIR     := ../..

### The current path from Root Directory.
DIR          := Project/ImageMacro

### The List of Sub-Directory which have Makefile
### note: If current directory does not have the sub-directory, Variable "SUBDIR" is empty.
SUBDIRS      :=

### List of source files
### note: If current directory does not have C/ASM source files in "src" directory, CSRC/ASRC is empty.
CSRC :=
CSRC += imb2r.c
CSRC += imb2r1.c
CSRC += imb2r2.c
CSRC += imb2r3.c
CSRC += imb2r4.c
CSRC += imbmh.c
CSRC += imbmh1.c
CSRC += imcnr.c imcnraxi.c imcnrcspr.c imcnrget.c imcnrinit.c imcnrset.c   
CSRC += imela.c imelareg.c imelacore.c
CSRC += imfptcommon.c
CSRC += imfpt.c
CSRC += imiipdefine.c
CSRC += imiipstruct.c
CSRC += imiipstatic.c
CSRC += imiipmain.c
CSRC += imiipvoid.c
CSRC += imiipsub.c
CSRC += imiipcounter.c
CSRC += imiipnew.c
CSRC += imiipparam.c
CSRC += imiipparamenum.c
CSRC += imiipafnregister.c
CSRC += imiipfrectregister.c
CSRC += imiipmanyregister.c
CSRC += imiipmultiregister.c
CSRC += imiipfltregister.c
CSRC += imiipslregister.c
CSRC += imiipunitparameter.c
CSRC += imiipgpcparameter.c
CSRC += imimg.c
CSRC += imjpeg.c
CSRC += imjpegcommon.c
CSRC += imjpegshare.c
CSRC += imjpegskip.c
CSRC += im_ltm_common.c
CSRC += im_ltm_rbk.c
CSRC += imltmmaplist.c
CSRC += imltmmapevent.c
CSRC += imltmltmutlis.c
CSRC += imltmltmwin.c
CSRC += mxicutlis.c
CSRC += immxic.c
CSRC += mxicacccapa.c
CSRC += mxicmasterslave.c
CSRC += mxicmaster.c
CSRC += mxicslot.c
CSRC += mxicmonitoraccess.c
CSRC += mxiclevelport.c
CSRC += im_pro_b2b.c
CSRC += im_pro_common.c
CSRC += interruptsen.c
CSRC += interruptctrl.c
CSRC += interruptfactor.c
CSRC += interruptcallback.c
CSRC += interruptclear1.c
CSRC += interruptclear2.c
CSRC += im_pro_pas.c
CSRC += im_pro_sen.c
CSRC += im_pro_sro.c
CSRC += im_pro_stat.c
CSRC += imr2yclk.c
CSRC += imr2yutils.c
CSRC += imr2y.c
CSRC += imr2ystat.c
CSRC += imr2y2.c
CSRC += imr2y3.c
CSRC += imr2yproc.c
CSRC += imr2yctrl.c
CSRC += imr2yctrl2.c
CSRC += imr2yctrl3.c
CSRC += imr2yctrl4.c
CSRC += imr2yctrl5.c
CSRC += imr2yctrlsup.c
CSRC += imr2yedge.c
CSRC += imr2yset.c
CSRC += imr2yutility.c
CSRC += imr2yutility2.c
CSRC += imr2yutility3.c
CSRC += imr2yutility4.c
CSRC += imraw.c
CSRC += imrdma.c
CSRC += im_sdramc.c
CSRC += imshdr.c
CSRC += imshdr1.c
CSRC += imshdr2.c
CSRC += imshdr3.c
CSRC += imxch.c
CSRC += imxch1.c
CSRC += imxch2.c

CSRC += imdisp.c
CSRC += imdisp0.c
CSRC += imdisp1.c
CSRC += imdisp2.c
CSRC += imdisp3.c
CSRC += imdisp4.c
CSRC += imdisp5.c
CSRC += imdisp6.c
CSRC += imdisp7.c
CSRC += imdisp8.c
CSRC += imhdmienum.c
CSRC += imhdmistruct.c
CSRC += imhdmiunion.c
CSRC += imhdmi.c
CSRC += im_mipi.c
##### REMOVE_ME_RELEASE BEGIN #####
CSRC += imme.c
##### REMOVE_ME_RELEASE END #####


ASRC :=
ASRC += im_fpt_asm.s

##### REMOVE_ME_RELEASE BEGIN #####
ifeq "$(BUILD_IM_ME_OBJ)" "yes"
# target source overwrite only "im_me.c".
CSRC := imme.c
ASRC :=
endif
##### REMOVE_ME_RELEASE END #####





WS_DIR_NAME ?= Project
include $(ROOT_DIR)/$(WS_DIR_NAME)/common.mk





### Special compile/assemble
