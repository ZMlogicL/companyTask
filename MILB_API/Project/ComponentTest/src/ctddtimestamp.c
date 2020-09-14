/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdTimestamp类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_timestamp.c
 * @brief		dd_timestamp Component Test
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include <stdlib.h>
#include <string.h>
#include "driver_common.h"
#include "ddtimestamp.h"
#include "ctddtimestamp.h"
#include "ddimusercustom.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdTimestamp, ct_dd_timestamp);
#define CT_DD_TIMESTAMP_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdTimestampPrivate,CT_TYPE_DD_TIMESTAMP))

struct _CtDdTimestampPrivate {
    kint i;
};

static void ct_dd_timestamp_constructor(CtDdTimestamp *self) 
{
// CtDdTimestampPrivate *priv = CT_DD_TIMESTAMP_GET_PRIVATE(self);
}

static void ct_dd_timestamp_destructor(CtDdTimestamp *self)
{
// CtDdTimestampPrivate *priv = CT_DD_TIMESTAMP_GET_PRIVATE(self);
}
/*
 *PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
/**
 * @brief  Command main function for TIMESTAMP test.
 * @param  int argc	:The number of parameters
 *		   char** argv	:The value of parameters
 * @return void
 *
 * The meaning of parameters
 * +-----+----------+------------+------------+------------+-----------------------------------------------------+
 * | P1  | P2       | P3         | P4         | P5         |Meaning                                              |
 * +-----+----------+------------+------------+------------+-----------------------------------------------------+
 * | 1   | -        | -          | -          | -          |Initialize Timestamp Register.                       |
 * +-----+----------+------------+------------+------------+-----------------------------------------------------+
 * | 2   | -        | -          | -          | -          |Exclusively controll of Timestamp Open/Close.        |
 * +-----+----------+------------+------------+------------+-----------------------------------------------------+
 * | 3   | hdbg     | counter    | frequency  | -          |Timestamp Controller.                                |
 * +-----+----------+------------+------------+------------+-----------------------------------------------------+
 * | 4   | -        | -          | -          | -          |Timestamp Start/Stop.                                |
 * +-----+----------+------------+------------+------------+-----------------------------------------------------+
 * | 5   | counter  | -          | -          | -          |Timestamp Counter Set/Get.                           |
 * +-----+----------+------------+------------+------------+-----------------------------------------------------+
 * | 6   | usec     | frequency  | -          | -          |Timestamp Timer Set.                                 |
 * +-----+----------+------------+------------+------------+-----------------------------------------------------+
 * | 7   | -        | -          | -          | -          |Timestamp Get API.                                   |
 * +-----+----------+------------+------------+------------+-----------------------------------------------------+
 * | 8   | -        | -          | -          | -          |Timestamp Error Test.                                |
 * +-----+----------+------------+------------+------------+-----------------------------------------------------+
 * | 9   | -        | -          | -          | -          |Timestamp API Sequence.                              |
 * +-----+----------+------------+------------+------------+-----------------------------------------------------+
 */
void ct_dd_timestamp_main(CtDdTimestamp *self, kint argc, KType* argv)
{
	DdTimestamp *dtStamp = dd_timestamp_new();

	switch (strtol(argv[1], NULL, 16)) {
		case 1:		// Init
			Ddim_Print(("dd_timestamp_init Test Start\n"));
			dd_timestamp_init(dtStamp);
			
			// CNTCR
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTCR_En;
			Ddim_Print(("CNTCR EN = 0x%08x (set 0x00000000)\n", self->dat));
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTCR_HDbg;
			Ddim_Print(("CNTCR HDBG = 0x%08x (set 0x00000000)\n", self->dat));
			// CNTCVL
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTCVL;
			Ddim_Print(("CNTCVL = 0x%08x (set 0x00000000)\n", self->dat));
			// CNTCVU
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTCVU;
			Ddim_Print(("CNTCVU = 0x%08x (set 0x00000000)\n", self->dat));
			// CNTFID0
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTFID0;
			Ddim_Print(("CNTFID0 = 0x%08x (set 0x00000000)\n", self->dat));

			Ddim_Print(("dd_timestamp_init Test End\n"));
			break;
			
		case 2:		// Open/Close
			// DdimUserCustom_SEM_WAIT_POL
			Ddim_Print(("dd_timestamp_open / dd_timestamp_close POL Test Start\n"));
			self->dat = dd_timestamp_open(dtStamp, DdimUserCustom_SEM_WAIT_POL);
			Ddim_Print(("dd_timestamp_open return = 0x%08x\n", self->dat));
			if(self->dat == D_DDIM_OK){
				self->dat = dd_timestamp_close(dtStamp);
				Ddim_Print(("dd_timestamp_close return = 0x%08x\n", self->dat));
			}
			Ddim_Print(("dd_timestamp_open / dd_timestamp_close POL Test End\n"));
			
			// Twai
			Ddim_Print(("dd_timestamp_open / dd_timestamp_close Twai Test Start\n"));
			self->dat = dd_timestamp_open(dtStamp, 200);
			Ddim_Print(("dd_timestamp_open return = 0x%08x\n", self->dat));
			if(self->dat == D_DDIM_OK){
				self->dat = dd_timestamp_close(dtStamp);
				Ddim_Print(("dd_timestamp_close return = 0x%08x\n", self->dat));
			}
			Ddim_Print(("dd_timestamp_open / dd_timestamp_close Twai Test End\n"));
			
			break;
			
		case 3:		// Ctrl
			Ddim_Print(("dd_timestamp_ctrl Test Start\n"));
			self->timestampCtrl.hdbg = strtoul(argv[2], NULL, 16);
			self->timestampCtrl.counter = strtoull(argv[3], NULL, 16);
			self->timestampCtrl.frequency = strtoul(argv[4], NULL, 16);
			
			if(dd_timestamp_ctrl(dtStamp, &self->timestampCtrl) == D_DDIM_OK){
				// CNTCR
				self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTCR_HDbg;
				Ddim_Print(("CNTCR HDBG = 0x%08x\n", self->dat));
				// CNTCVL
				self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTCVL;
				Ddim_Print(("CNTCVL = 0x%08x\n", self->dat));
				// CNTCVU
				self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTCVU;
				Ddim_Print(("CNTCVU = 0x%08x\n", self->dat));
				// CNTFID0
				self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTFID0;
				Ddim_Print(("CNTFID0 = 0x%08x\n", self->dat));
				// DdTimestamp
				self->dat = dd_timestamp_get_control(dtStamp, &self->timestampCtrlGet);
				if(self->dat == D_DDIM_OK){
					Ddim_Print(("T_DD_TIMESTAMP_CTRL hdbg = 0x%08lx\n", 
						self->timestampCtrlGet.hdbg));
					Ddim_Print(("T_DD_TIMESTAMP_CTRL counter = 0x%016llx\n", 
						self->timestampCtrlGet.counter));
					Ddim_Print(("T_DD_TIMESTAMP_CTRL frequency = 0x%08lx\n", 
						self->timestampCtrlGet.frequency));
				}
			}
			else{
				Ddim_Print(("please check parameter!!\n"));
			}
			
			Ddim_Print(("dd_timestamp_ctrl Test End\n"));
			
			break;
			
		case 4:		// Start/Stop
			Ddim_Print(("dd_timestamp_start / dd_timestamp_stop Test Start\n"));
			
			dd_timestamp_start(dtStamp);
			// CNTCR EN
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTCR_En;
			Ddim_Print(("CNTCR EN = 0x%08x (set 0x00000001)\n", self->dat));
			
			dd_timestamp_stop(dtStamp);
			// CNTCR EN
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTCR_En;
			Ddim_Print(("CNTCR EN = 0x%08x (set 0x00000000)\n", self->dat));
			
			Ddim_Print(("dd_timestamp_start / dd_timestamp_stop Test End\n"));
			
			break;
			
		case 5:		// Counter Set/Get
			Ddim_Print(("dd_timestamp_set_counter / dd_timestamp_get_counter Test Start\n"));
			self->timestampCounter = strtoull(argv[2], NULL, 16);
			
			if(self->timestampCounter <= 0){
				self->timestampCounter = 0;
			}
			if(dd_timestamp_set_counter(dtStamp, self->timestampCounter) == D_DDIM_OK){
				if(dd_timestamp_get_counter(dtStamp, &self->timestampCounterGet) == D_DDIM_OK){
					Ddim_Print(("Counter = 0x%016llx\n", self->timestampCounterGet));
				}
			}
			
			Ddim_Print(("dd_timestamp_set_counter / dd_timestamp_get_counter Test End\n"));
			
			break;
			
		case 6:		// Timer Set
			Ddim_Print(("dd_timestamp_set_timer Test Start\n"));
			self->usec = strtoul(argv[2], NULL, 16);
			self->frequency = strtoul(argv[3], NULL, 16);
			
			if(self->usec <= 0){
				self->usec = 0;
			}
			if(self->frequency <= 0){
				self->frequency = 0;
			}
			if(dd_timestamp_set_timer(dtStamp, self->usec, self->frequency) == D_DDIM_OK){
				// CNTCR
				self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTCR_En;
				Ddim_Print(("CNTCR EN = 0x%08x\n", self->dat));
				// CNTCVL
				self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTCVL;
				Ddim_Print(("CNTCVL = 0x%08x\n", self->dat));
				// CNTCVU
				self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTCVU;
				Ddim_Print(("CNTCVU = 0x%08x\n", self->dat));
				// CNTFID0
				self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTFID0;
				Ddim_Print(("CNTFID0 = 0x%08x\n", self->dat));
			}
			
			Ddim_Print(("dd_timestamp_set_timer Test End\n"));
			
			break;
			
		case 7:		// Get API
			// CNTSR
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CNTSR_Dbgh;
			Ddim_Print(("CNTSR Get DBGH = %d\n", self->dat));
			// PERIPID4
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_PIDR4_Des_2;
			Ddim_Print(("PERIPID4 Get DES_2 = %d\n", self->dat));
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_PIDR4_Size;
			Ddim_Print(("PERIPID4 Get SIZE = %d\n", self->dat));
			// PERIPID0
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_PIDR0_Part_0;
			Ddim_Print(("PERIPID0 Get PART_0 = %d\n", self->dat));
			// PERIPID1
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_PIDR1_Des_0;
			Ddim_Print(("PERIPID1 Get DES_0 = %d\n", self->dat));
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_PIDR1_Part_1;
			Ddim_Print(("PERIPID1 Get PART_1 = %d\n", self->dat));
			// PERIPID2
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_PIDR2_Des_1;
			Ddim_Print(("PERIPID2 Get DES_1 = %d\n", self->dat));
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_PIDR2_Jedec;
			Ddim_Print(("PERIPID2 Get JEDEC = %d\n", self->dat));
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_PIDR2_Revision;
			Ddim_Print(("PERIPID2 Get REVISION = %d\n", self->dat));
			// PERIPID3
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_PIDR3_Cmod;
			Ddim_Print(("PERIPID3 Get CMOD = %d\n", self->dat));
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_PIDR3_Revand;
			Ddim_Print(("PERIPID3 Get REVAND = %d\n", self->dat));
			// CIDR0
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CIDR0_Prmbl_0;
			Ddim_Print(("CIDR0 Get PRMBL_0 = %d\n", self->dat));
			// CIDR1
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CIDR1_Prmbl_1;
			Ddim_Print(("CIDR1 Get PRMBL_1 = %d\n", self->dat));
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CIDR1_Class;
			Ddim_Print(("CIDR1 Get CLASS = %d\n", self->dat));
			// CIDR2
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CIDR2_Prmbl_2;
			Ddim_Print(("CIDR2 Get PRMBL_2 = %d\n", self->dat));
			// CIDR3
			self->dat = DdTimestamp_Dd_TIMESTAMP_Get_CIDR3_Prmbl_3;
			Ddim_Print(("CIDR3 Get PRMBL_3 = %d\n", self->dat));
			
			break;
			
		case 8:		// Error Test
			Ddim_Print(("dd_timestamp_open Error Test\n"));
			self->dat = dd_timestamp_open(dtStamp, DdimUserCustom_SEM_WAIT_FEVR - 1);
			Ddim_Print(("dd_timestamp_open Error = 0x%08x\n", self->dat));
			self->dat = dd_timestamp_open(dtStamp, DdimUserCustom_SEM_WAIT_POL);
			self->dat = dd_timestamp_open(dtStamp, DdimUserCustom_SEM_WAIT_POL);
			Ddim_Print(("dd_timestamp_open Error = 0x%08x\n", self->dat));
			
			Ddim_Print(("dd_timestamp_ctrl Error Test\n"));
			self->dat = dd_timestamp_ctrl(dtStamp, NULL);
			Ddim_Print(("dd_timestamp_ctrl Error = 0x%08x\n", self->dat));
			self->timestampCtrl.hdbg = 0;
			self->timestampCtrl.counter = 0;
			self->timestampCtrl.frequency = 0x0;
			self->dat = dd_timestamp_ctrl(dtStamp, &self->timestampCtrl);
			Ddim_Print(("dd_timestamp_ctrl Error = 0x%08x\n", self->dat));
			self->timestampCtrl.hdbg = 0;
			self->timestampCtrl.counter = 0;
			self->timestampCtrl.frequency = 0xFFFFFFFF;
			self->dat = dd_timestamp_ctrl(dtStamp, &self->timestampCtrl);
			Ddim_Print(("dd_timestamp_ctrl Error = 0x%08x\n", self->dat));
			
			Ddim_Print(("dd_timestamp_get_counter Error Test\n"));
			self->dat = dd_timestamp_get_counter(dtStamp, NULL);
			Ddim_Print(("dd_timestamp_get_counter Error = 0x%08x\n", self->dat));
			
			Ddim_Print(("dd_timestamp_get_control Error Test\n"));
			self->dat = dd_timestamp_get_control(dtStamp, NULL);
			Ddim_Print(("dd_timestamp_get_control Error = 0x%08x\n", self->dat));
			
			Ddim_Print(("dd_timestamp_set_timer Error Test\n"));
			self->dat = dd_timestamp_set_timer(dtStamp, 1000000, 0x0);
			Ddim_Print(("dd_timestamp_set_timer Error = 0x%08x\n", self->dat));
			self->dat = dd_timestamp_set_timer(dtStamp, 1000000, 0xFFFFFFFF);
			Ddim_Print(("dd_timestamp_set_timer Error = 0x%08x\n", self->dat));
			
			break;
			
		case 9:		// Sequence
			Ddim_Print(("Sequence Test Start\n"));
			self->timestampCtrl.hdbg = 0;						// has no effect
			self->timestampCtrl.counter = 0x0000000000000000;	// Counter
			self->timestampCtrl.frequency = 0xEE6B2800;			// 4GHz
			
			dd_timestamp_init(dtStamp);
			dd_timestamp_open(dtStamp, DdimUserCustom_SEM_WAIT_POL);
			dd_timestamp_ctrl(dtStamp, &self->timestampCtrl);
			
			dd_timestamp_start(dtStamp);
			
			dd_timestamp_get_control(dtStamp, &self->timestampCtrlGet);
			Ddim_Print(("T_DD_TIMESTAMP_CTRL hdbg = 0x%08lx\n", self->timestampCtrlGet.hdbg));
			Ddim_Print(("T_DD_TIMESTAMP_CTRL counter = 0x%016llx\n", self->timestampCtrlGet.counter));
			Ddim_Print(("T_DD_TIMESTAMP_CTRL frequency = 0x%08lx\n", self->timestampCtrlGet.frequency));
			
			dd_timestamp_stop(dtStamp);
			dd_timestamp_close(dtStamp);
			
			Ddim_Print(("Sequence Test End\n"));
			break;
			
		default :
			Ddim_Print(("please check 1st parameter!!\n"));
	}
	k_object_unref(dtStamp);
	dtStamp = NULL; 
}

CtDdTimestamp *ct_dd_timestamp_new(void)
{
    CtDdTimestamp *self = k_object_new_with_private(CT_TYPE_DD_TIMESTAMP, sizeof(CtDdTimestampPrivate));
    return self;
}
