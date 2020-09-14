#ifndef __JDSCNR_CSPR_REG_H__
#define __JDSCNR_CSPR_REG_H__


#include "../Project/Image/src/kjdscnr1a.h"
///*	structure of cspren (2842_1000h)	*/
//union IoCnrCsprRegCspren{
//	unsigned long		word;
//	struct {
//		unsigned long	cspren	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of cgdken (2842_1008h)	*/
//union IoCnrCsprRegCgdken{
//	unsigned long		word;
//	struct {
//		unsigned long	cgdken	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of mcen	(2842_1020h)	*/
//union IoCnrCsprRegMcen{
//	unsigned long		word;
//	struct {
//		unsigned long	mcen	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of mcythh (2842_1024h)	*/
//union IoCnrCsprRegMcythh{
//	unsigned long		word;
//	struct {
//		unsigned long	mcythh0	:8;
//		unsigned long	mcythh1	:8;
//		unsigned long	mcythh2	:8;
//		unsigned long	mcythh3	:8;
//	}bit;
//};
//
///*	structure of mcythv (2842_1028h)	*/
//union IoCnrCsprRegMcythv{
//	unsigned long		word;
//	struct {
//		unsigned long	mcythv0	:8;
//		unsigned long	mcythv1	:8;
//		unsigned long	mcythv2	:8;
//		unsigned long	mcythv3	:8;
//	}bit;
//};
//
///*	structure of mccthh (2842_102Ch)	*/
//union IoCnrCsprRegMccthh{
//	unsigned long		word;
//	struct {
//		unsigned long	mccthh0	:8;
//		unsigned long	mccthh1	:8;
//		unsigned long	mccthh2	:8;
//		unsigned long	mccthh3	:8;
//	}bit;
//};
//
///*	structure of mccthv (2842_1030h)	*/
//union IoCnrCsprRegMccthv{
//	unsigned long		word;
//	struct {
//		unsigned long	mccthv0	:8;
//		unsigned long	mccthv1	:8;
//		unsigned long	mccthv2	:8;
//		unsigned long	mccthv3	:8;
//	}bit;
//};
//
///*	structure of mcydym (2842_1034h)	*/
//union IoCnrCsprRegMcydym{
//	unsigned long		word;
//	struct {
//		unsigned long	mcydym	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of mcydymdt	(2842_1038h)	*/
//union IoCnrCsprRegMcydymdt{
//	unsigned long		word;
//	struct {
//		unsigned long	mcydymycr	:8;
//		unsigned long				:8;
//		unsigned long	mcydymyg	:9;
//		unsigned long				:7;
//	}bit;
//};
//
///*	structure of mcyscl (2842_1040h)	*/
//union IoCnrCsprRegMcyscl{
//	unsigned long		word;
//	struct {
//		unsigned long	mcyscl	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of mcysclof	(2842_1048h)	*/
//union IoCnrCsprRegMcysclof1{
//	unsigned long		word;
//	struct {
//		unsigned long	mcysclof0	:8;
//		unsigned long	mcysclof1	:8;
//		unsigned long	mcysclof2	:8;
//		unsigned long	mcysclof3	:8;
//	}bit;
//};
//union IoCnrCsprRegMcysclof2{
//	unsigned long		word;
//	struct {
//		unsigned long	mcysclof4	:8;
//		unsigned long	mcysclof5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegMcysclof{
//	union IoCnrCsprRegMcysclof1	mcysclof1;
//	union IoCnrCsprRegMcysclof2	mcysclof2;
//};
//
///*	structure of mcysclga	(2842_1050h)	*/
//union IoCnrCsprRegMcysclga1{
//	unsigned long		word;
//	struct {
//		long			mcysclga0	:8;
//		long			mcysclga1	:8;
//		long			mcysclga2	:8;
//		long			mcysclga3	:8;
//	}bit;
//};
//union IoCnrCsprRegMcysclga2{
//	unsigned long		word;
//	struct {
//		long			mcysclga4	:8;
//		long			mcysclga5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegMcysclga{
//	union IoCnrCsprRegMcysclga1	mcysclga1;
//	union IoCnrCsprRegMcysclga2	mcysclga2;
//};
//
///*	structure of mcysclbd	(2842_1058h)	*/
//union IoCnrCsprRegMcysclbd1{
//	unsigned long		word;
//	struct {
//		unsigned long	mcysclbd1	:8;
//		unsigned long	mcysclbd2	:8;
//		unsigned long	mcysclbd3	:8;
//		unsigned long	mcysclbd4	:8;
//	}bit;
//};
//union IoCnrCsprRegMcysclbd2{
//	unsigned long		word;
//	struct {
//		unsigned long	mcysclbd5	:8;
//		unsigned long				:24;
//	}bit;
//};
//struct IoCnrCsprRegMcysclbd{
//	union IoCnrCsprRegMcysclbd1	mcysclbd1;
//	union IoCnrCsprRegMcysclbd2	mcysclbd2;
//};
//
///*	structure of mccscl (2842_1060h)	*/
//union IoCnrCsprRegMccscl{
//	unsigned long		word;
//	struct {
//		unsigned long	mccscl	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of mccsclof	(2842_1068h)	*/
//union IoCnrCsprRegMccsclof1{
//	unsigned long		word;
//	struct {
//		unsigned long	mccsclof0	:8;
//		unsigned long	mccsclof1	:8;
//		unsigned long	mccsclof2	:8;
//		unsigned long	mccsclof3	:8;
//	}bit;
//};
//union IoCnrCsprRegMccsclof2{
//	unsigned long		word;
//	struct {
//		unsigned long	mccsclof4	:8;
//		unsigned long	mccsclof5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegMccsclof{
//	union IoCnrCsprRegMccsclof1	mccsclof1;
//	union IoCnrCsprRegMccsclof2	mccsclof2;
//};
//
///*	structure of mccsclga	(2842_1070h)	*/
//union IoCnrCsprRegMccsclga1{
//	unsigned long		word;
//	struct {
//		long			mccsclga0	:8;
//		long			mccsclga1	:8;
//		long			mccsclga2	:8;
//		long			mccsclga3	:8;
//	}bit;
//};
//union IoCnrCsprRegMccsclga2{
//	unsigned long		word;
//	struct {
//		long			mccsclga4	:8;
//		long			mccsclga5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegMccsclga{
//	union IoCnrCsprRegMccsclga1	mccsclga1;
//	union IoCnrCsprRegMccsclga2	mccsclga2;
//};
//
///*	structure of mccsclbd	(2842_1078h)	*/
//union IoCnrCsprRegMccsclbd1{
//	unsigned long		word;
//	struct {
//		unsigned long	mccsclbd1	:8;
//		unsigned long	mccsclbd2	:8;
//		unsigned long	mccsclbd3	:8;
//		unsigned long	mccsclbd4	:8;
//	}bit;
//};
//union IoCnrCsprRegMccsclbd2{
//	unsigned long		word;
//	struct {
//		unsigned long	mccsclbd5	:8;
//		unsigned long				:24;
//	}bit;
//};
//struct IoCnrCsprRegMccsclbd{
//	union IoCnrCsprRegMccsclbd1	mccsclbd1;
//	union IoCnrCsprRegMccsclbd2	mccsclbd2;
//};
//
///*	structure of mcsscl (2842_1080h)	*/
//union IoCnrCsprRegMcsscl{
//	unsigned long		word;
//	struct {
//		unsigned long	mcsscl	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of mcssclof	(2842_1088h)	*/
//union IoCnrCsprRegMcssclof1{
//	unsigned long		word;
//	struct {
//		unsigned long	mcssclof0	:8;
//		unsigned long	mcssclof1	:8;
//		unsigned long	mcssclof2	:8;
//		unsigned long	mcssclof3	:8;
//	}bit;
//};
//union IoCnrCsprRegMcssclof2{
//	unsigned long		word;
//	struct {
//		unsigned long	mcssclof4	:8;
//		unsigned long	mcssclof5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegMcssclof{
//	union IoCnrCsprRegMcssclof1	mcssclof1;
//	union IoCnrCsprRegMcssclof2	mcssclof2;
//};
//
///*	structure of mcssclga	(2842_1090h)	*/
//union IoCnrCsprRegMcssclga1{
//	unsigned long		word;
//	struct {
//		long			mcssclga0	:8;
//		long			mcssclga1	:8;
//		long			mcssclga2	:8;
//		long			mcssclga3	:8;
//	}bit;
//};
//union IoCnrCsprRegMcssclga2{
//	unsigned long		word;
//	struct {
//		long			mcssclga4	:8;
//		long			mcssclga5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegMcssclga{
//	union IoCnrCsprRegMcssclga1	mcssclga1;
//	union IoCnrCsprRegMcssclga2	mcssclga2;
//};
//
///*	structure of mcssclbd	(2842_1098h)	*/
//union IoCnrCsprRegMcssclbd1{
//	unsigned long		word;
//	struct {
//		unsigned long	mcssclbd1	:8;
//		unsigned long	mcssclbd2	:8;
//		unsigned long	mcssclbd3	:8;
//		unsigned long	mcssclbd4	:8;
//	}bit;
//};
//union IoCnrCsprRegMcssclbd2{
//	unsigned long		word;
//	struct {
//		unsigned long	mcssclbd5	:8;
//		unsigned long				:24;
//	}bit;
//};
//struct IoCnrCsprRegMcssclbd{
//	union IoCnrCsprRegMcssclbd1	mcssclbd1;
//	union IoCnrCsprRegMcssclbd2	mcssclbd2;
//};
//
///*	structure of lcen	(2842_10C0h)	*/
//union IoCnrCsprRegLcen{
//	unsigned long		word;
//	struct {
//		unsigned long	lcen	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of lcythh (2842_10C4h)	*/
//union IoCnrCsprRegLcythh{
//	unsigned long		word;
//	struct {
//		unsigned long	lcythh0	:8;
//		unsigned long	lcythh1	:8;
//		unsigned long	lcythh2	:8;
//		unsigned long	lcythh3	:8;
//	}bit;
//};
//
///*	structure of lcythv (2842_10C8h)	*/
//union IoCnrCsprRegLcythv{
//	unsigned long		word;
//	struct {
//		unsigned long	lcythv0	:8;
//		unsigned long	lcythv1	:8;
//		unsigned long	lcythv2	:8;
//		unsigned long	lcythv3	:8;
//	}bit;
//};
//
///*	structure of lccthh (2842_10CCh)	*/
//union IoCnrCsprRegLccthh{
//	unsigned long		word;
//	struct {
//		unsigned long	lccthh0	:8;
//		unsigned long	lccthh1	:8;
//		unsigned long	lccthh2	:8;
//		unsigned long	lccthh3	:8;
//	}bit;
//};
//
///*	structure of lccthv (2842_10D0h)	*/
//union IoCnrCsprRegLccthv{
//	unsigned long		word;
//	struct {
//		unsigned long	lccthv0	:8;
//		unsigned long	lccthv1	:8;
//		unsigned long	lccthv2	:8;
//		unsigned long	lccthv3	:8;
//	}bit;
//};
//
///*	structure of lcydym (2842_10D4h)	*/
//union IoCnrCsprRegLcydym{
//	unsigned long		word;
//	struct {
//		unsigned long	lcydym	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of lcydymdt	(2842_10D8h)	*/
//union IoCnrCsprRegLcydymdt{
//	unsigned long		word;
//	struct {
//		unsigned long	lcydymycr	:8;
//		unsigned long				:8;
//		unsigned long	lcydymyg	:9;
//		unsigned long				:7;
//	}bit;
//};
//
///*	structure of lcyscl (2842_10E0h)	*/
//union IoCnrCsprRegLcyscl{
//	unsigned long		word;
//	struct {
//		unsigned long	lcyscl	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of lcysclof	(2842_10E8h)	*/
//union IoCnrCsprRegLcysclof1{
//	unsigned long		word;
//	struct {
//		unsigned long	lcysclof0	:8;
//		unsigned long	lcysclof1	:8;
//		unsigned long	lcysclof2	:8;
//		unsigned long	lcysclof3	:8;
//	}bit;
//};
//union IoCnrCsprRegLcysclof1{
//	unsigned long		word;
//	struct {
//		unsigned long	lcysclof4	:8;
//		unsigned long	lcysclof5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegLcysclof{
//	union IoCnrCsprRegLcysclof1	lcysclof1;
//	union IoCnrCsprRegLcysclof1	lcysclof2;
//};
//
///*	structure of lcysclga	(2842_10F0h)	*/
//union IoCnrCsprRegLcysclga1{
//	unsigned long		word;
//	struct {
//		long			lcysclga0	:8;
//		long			lcysclga1	:8;
//		long			lcysclga2	:8;
//		long			lcysclga3	:8;
//	}bit;
//};
//union IoCnrCsprRegLcysclga1{
//	unsigned long		word;
//	struct {
//		long			lcysclga4	:8;
//		long			lcysclga5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegLcysclga{
//	union IoCnrCsprRegLcysclga1	lcysclga1;
//	union IoCnrCsprRegLcysclga1	lcysclga2;
//};
//
///*	structure of lcysclbd	(2842_10F8h)	*/
//union IoCnrCsprRegLcysclbd1{
//	unsigned long		word;
//	struct {
//		unsigned long	lcysclbd1	:8;
//		unsigned long	lcysclbd2	:8;
//		unsigned long	lcysclbd3	:8;
//		unsigned long	lcysclbd4	:8;
//	}bit;
//};
//union IoCnrCsprRegLcysclbd2{
//	unsigned long		word;
//	struct {
//		unsigned long	lcysclbd5	:8;
//		unsigned long				:24;
//	}bit;
//};
//struct IoCnrCsprRegLcysclbd{
//	union IoCnrCsprRegLcysclbd1	lcysclbd1;
//	union IoCnrCsprRegLcysclbd2	lcysclbd2;
//};
//
///*	structure of lccscl (2842_1100h)	*/
//union IoCnrCsprRegLccscl{
//	unsigned long		word;
//	struct {
//		unsigned long	lccscl	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of lccsclof	(2842_1108h)	*/
//union IoCnrCsprRegLccsclof1{
//	unsigned long		word;
//	struct {
//		unsigned long	lccsclof0	:8;
//		unsigned long	lccsclof1	:8;
//		unsigned long	lccsclof2	:8;
//		unsigned long	lccsclof3	:8;
//	}bit;
//};
//union IoCnrCsprRegLccsclof2{
//	unsigned long		word;
//	struct {
//		unsigned long	lccsclof4	:8;
//		unsigned long	lccsclof5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegLccsclof{
//	union IoCnrCsprRegLccsclof1	lccsclof1;
//	union IoCnrCsprRegLccsclof2	lccsclof2;
//};
//
///*	structure of lccsclga	(2842_1110h)	*/
//union IoCnrCsprRegLccsclga1{
//	unsigned long		word;
//	struct {
//		long			lccsclga0	:8;
//		long			lccsclga1	:8;
//		long			lccsclga2	:8;
//		long			lccsclga3	:8;
//	}bit;
//};
//union IoCnrCsprRegLccsclga2{
//	unsigned long		word;
//	struct {
//		long			lccsclga4	:8;
//		long			lccsclga5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegLccsclga{
//	union IoCnrCsprRegLccsclga1	lccsclga1;
//	union IoCnrCsprRegLccsclga2	lccsclga2;
//};
//
///*	structure of lccsclbd	(2842_1118h)	*/
//union IoCnrCsprRegLccsclbd1{
//	unsigned long		word;
//	struct {
//		unsigned long	lccsclbd1	:8;
//		unsigned long	lccsclbd2	:8;
//		unsigned long	lccsclbd3	:8;
//		unsigned long	lccsclbd4	:8;
//	}bit;
//};
//union IoCnrCsprRegLccsclbd2{
//	unsigned long		word;
//	struct {
//		unsigned long	lccsclbd5	:8;
//		unsigned long				:24;
//	}bit;
//};
//struct IoCnrCsprRegLccsclbd{
//	union IoCnrCsprRegLccsclbd1	lccsclbd1;
//	union IoCnrCsprRegLccsclbd2	lccsclbd2;
//};
//
///*	structure of lcsscl (2842_1120h)	*/
//union IoCnrCsprRegLcsscl{
//	unsigned long		word;
//	struct {
//		unsigned long	lcsscl	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of lcssclof	(2842_1128h)	*/
//union IoCnrCsprRegLcssclof1{
//	unsigned long		word;
//	struct {
//		unsigned long	lcssclof0	:8;
//		unsigned long	lcssclof1	:8;
//		unsigned long	lcssclof2	:8;
//		unsigned long	lcssclof3	:8;
//	}bit;
//};
//union IoCnrCsprRegLcssclof2{
//	unsigned long		word;
//	struct {
//		unsigned long	lcssclof4	:8;
//		unsigned long	lcssclof5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegLcssclof{
//	union IoCnrCsprRegLcssclof1	lcssclof1;
//	union IoCnrCsprRegLcssclof2	lcssclof2;
//};
//
///*	structure of lcssclga	(2842_1130h)	*/
//union IoCnrCsprRegLcssclga1{
//	unsigned long		word;
//	struct {
//		long			lcssclga0	:8;
//		long			lcssclga1	:8;
//		long			lcssclga2	:8;
//		long			lcssclga3	:8;
//	}bit;
//};
//union IoCnrCsprRegLcssclga2{
//	unsigned long		word;
//	struct {
//		long			lcssclga4	:8;
//		long			lcssclga5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegLcssclga{
//	union IoCnrCsprRegLcssclga1	lcssclga1;
//	union IoCnrCsprRegLcssclga2	lcssclga2;
//};
//
///*	structure of lcssclbd	(2842_1138h)	*/
//union IoCnrCsprRegLcssclbd1{
//	unsigned long		word;
//	struct {
//		unsigned long	lcssclbd1	:8;
//		unsigned long	lcssclbd2	:8;
//		unsigned long	lcssclbd3	:8;
//		unsigned long	lcssclbd4	:8;
//	}bit;
//};
//union IoCnrCsprRegLcssclbd2{
//	unsigned long		word;
//	struct {
//		unsigned long	lcssclbd5	:8;
//		unsigned long				:24;
//	}bit;
//};
//struct IoCnrCsprRegLcssclbd{
//	union IoCnrCsprRegLcssclbd1	lcssclbd1;
//	union IoCnrCsprRegLcssclbd2	lcssclbd2;
//};
//
///*	structure of blend	(2842_1160h)	*/
//union IoCnrCsprRegBlend{
//	unsigned long		word;
//	struct {
//		unsigned long	blendmd		:2;
//		unsigned long				:6;
//		unsigned long	cspralpbd	:5;
//		unsigned long				:3;
//		unsigned long	csrgen		:1;
//		unsigned long				:3;
//		unsigned long	csrgmd		:3;
//		unsigned long				:9;
//	}bit;
//};
//
///*	structure of cesclof	(2842_1168h)	*/
//union IoCnrCsprRegCesclof1{
//	unsigned long		word;
//	struct {
//		unsigned long	cesclof0	:6;
//		unsigned long				:2;
//		unsigned long	cesclof1	:6;
//		unsigned long				:2;
//		unsigned long	cesclof2	:6;
//		unsigned long				:2;
//		unsigned long	cesclof3	:6;
//		unsigned long				:2;
//	}bit;
//};
//union IoCnrCsprRegCesclof2{
//	unsigned long		word;
//	struct {
//		unsigned long	cesclof4	:6;
//		unsigned long				:2;
//		unsigned long	cesclof5	:6;
//		unsigned long				:2;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegCesclof{
//	union IoCnrCsprRegCesclof1	cesclof1;
//	union IoCnrCsprRegCesclof2	cesclof2;
//};
//
///*	structure of cesclga	(2842_1170h)	*/
//union IoCnrCsprRegCesclga1{
//	unsigned long		word;
//	struct {
//		long			cesclga0	:8;
//		long			cesclga1	:8;
//		long			cesclga2	:8;
//		long			cesclga3	:8;
//	}bit;
//};
//union IoCnrCsprRegCesclga2{
//	unsigned long		word;
//	struct {
//		long			cesclga4	:8;
//		long			cesclga5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegCesclga{
//	union IoCnrCsprRegCesclga1	cesclga1;
//	union IoCnrCsprRegCesclga2	cesclga2;
//};
//
///*	structure of cesclbd	(2842_1178h)	*/
//union IoCnrCsprRegCesclbd1{
//	unsigned long		word;
//	struct {
//		unsigned long	cesclbd1	:8;
//		unsigned long	cesclbd2	:8;
//		unsigned long	cesclbd3	:8;
//		unsigned long	cesclbd4	:8;
//	}bit;
//};
//union IoCnrCsprRegCesclbd2{
//	unsigned long		word;
//	struct {
//		unsigned long	cesclbd5	:8;
//		unsigned long				:24;
//	}bit;
//};
//struct IoCnrCsprRegCesclbd{
//	union IoCnrCsprRegCesclbd1	cesclbd1;
//	union IoCnrCsprRegCesclbd2	cesclbd2;
//};
//
///*	structure of cphpt	(2842_1190h)	*/
//union IoCnrCsprRegCphpt{
//	unsigned long		word;
//	struct {
//		long			cdcb	:8;
//		long			cdcr	:8;
//		unsigned long			:16;
//	}bit;
//};
//
///*	structure of cphptk	(2842_1194h)	*/
//union IoCnrCsprRegCphptk{
//	unsigned long		word;
//	struct {
//		unsigned long	kcb		:10;
//		unsigned long			:6;
//		unsigned long	kcr		:10;
//		unsigned long			:6;
//	}bit;
//};
//
///*	structure of cdsclof	(2842_11A0h)	*/
//union IoCnrCsprRegCdsclof1{
//	unsigned long		word;
//	struct {
//		unsigned long	cdsclof0	:9;
//		unsigned long				:7;
//		unsigned long	cdsclof1	:9;
//		unsigned long				:7;
//	}bit;
//};
//union IoCnrCsprRegCdsclof2{
//	unsigned long		word;
//	struct {
//		unsigned long	cdsclof2	:9;
//		unsigned long				:7;
//		unsigned long	cdsclof3	:9;
//		unsigned long				:7;
//	}bit;
//};
//union IoCnrCsprRegCdsclof3{
//	unsigned long		word;
//	struct {
//		unsigned long	CDSCLOF_4	:9;
//		unsigned long				:7;
//		unsigned long	CDSCLOF_5	:9;
//		unsigned long				:7;
//	}bit;
//};
//struct IoCnrCsprRegCdsclof{
//	union IoCnrCsprRegCdsclof1	cdsclof1;
//	union IoCnrCsprRegCdsclof2	cdsclof2;
//	union IoCnrCsprRegCdsclof3	cdsclof3;
//};
//
///*	structure of cdsclga	(2842_11B0h)	*/
//union IoCnrCsprRegCdsclga1{
//	unsigned long		word;
//	struct {
//		long			cdsclga0	:11;
//		unsigned long				:5;
//		long			cdsclga1	:11;
//		unsigned long				:5;
//	}bit;
//};
//union IoCnrCsprRegCdsclga2{
//	unsigned long		word;
//	struct {
//		long			cdsclga2	:11;
//		unsigned long				:5;
//		long			cdsclga3	:11;
//		unsigned long				:5;
//	}bit;
//};
//union IoCnrCsprRegCdsclga3{
//	unsigned long		word;
//	struct {
//		long			cdsclga4	:11;
//		unsigned long				:5;
//		long			cdsclga5	:11;
//		unsigned long				:5;
//	}bit;
//};
//struct IoCnrCsprRegCdsclga{
//	union IoCnrCsprRegCdsclga1	cdsclga1;
//	union IoCnrCsprRegCdsclga2	cdsclga2;
//	union IoCnrCsprRegCdsclga3	cdsclga3;
//};
//
///*	structure of cdsclbd	(2842_11C0h)	*/
//union IoCnrCsprRegCdsclbd1{
//	unsigned long		word;
//	struct {
//		unsigned long	cdsclbd1	:11;
//		unsigned long				:5;
//		unsigned long	cdsclbd2	:11;
//		unsigned long				:5;
//	}bit;
//};
//union IoCnrCsprRegCdsclbd2{
//	unsigned long		word;
//	struct {
//		unsigned long	cdsclbd3	:11;
//		unsigned long				:5;
//		unsigned long	cdsclbd4	:11;
//		unsigned long				:5;
//	}bit;
//};
//union IoCnrCsprRegCdsclbd3{
//	unsigned long		word;
//	struct {
//		unsigned long	cdsclbd5	:11;
//		unsigned long				:21;
//	}bit;
//};
//struct IoCnrCsprRegCdsclbd{
//	union IoCnrCsprRegCdsclbd1	cdsclbd1;
//	union IoCnrCsprRegCdsclbd2	cdsclbd2;
//	union IoCnrCsprRegCdsclbd3	cdsclbd3;
//};
//
///*	structure of whtmd	(2842_11D0h)	*/
//union IoCnrCsprRegWhtmd{
//	unsigned long		word;
//	struct {
//		unsigned long	whten	:1;
//		unsigned long			:7;
//		unsigned long	whtval	:5;
//		unsigned long			:3;
//		unsigned long	whtbase	:2;
//		unsigned long			:14;
//	}bit;
//};
//
///*	structure of sprs	(2842_1200h)	*/
//union IoCnrCsprRegSprs{
//	unsigned long		word;
//	struct {
//		unsigned long	sprs	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of sprscbof	(2842_1208h)	*/
//union IoCnrCsprRegSprscbof1{
//	unsigned long		word;
//	struct {
//		long			sprscbof0	:8;
//		long			sprscbof1	:8;
//		long			sprscbof2	:8;
//		long			sprscbof3	:8;
//	}bit;
//};
//union IoCnrCsprRegSprscbof2{
//	unsigned long		word;
//	struct {
//		long			sprscbof4	:8;
//		long			sprscbof5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegSprscbof{
//	union IoCnrCsprRegSprscbof1	sprscbof1;
//	union IoCnrCsprRegSprscbof2	sprscbof2;
//};
//
///*	structure of sprscbga	(2842_1210h)	*/
//union IoCnrCsprRegSprscbga1{
//	unsigned long		word;
//	struct {
//		long			sprscbga0	:12;
//		unsigned long				:4;
//		long			sprscbga1	:12;
//		unsigned long				:4;
//	}bit;
//};
//union IoCnrCsprRegSprscbga2{
//	unsigned long		word;
//	struct {
//		long			sprscbga2	:12;
//		unsigned long				:4;
//		long			sprscbga3	:12;
//		unsigned long				:4;
//	}bit;
//};
//union IoCnrCsprRegSprscbga3{
//	unsigned long		word;
//	struct {
//		long			sprscbga4	:12;
//		unsigned long				:4;
//		long			sprscbga5	:12;
//		unsigned long				:4;
//	}bit;
//};
//struct IoCnrCsprRegSprscbga{
//	union IoCnrCsprRegSprscbga1	sprscbga1;
//	union IoCnrCsprRegSprscbga2	sprscbga2;
//	union IoCnrCsprRegSprscbga3	sprscbga3;
//};
//
///*	structure of sprscbbd	(2842_1220h)	*/
//union IoCnrCsprRegSprscbbd1{
//	unsigned long		word;
//	struct {
//		long			sprscbbd1	:8;
//		long			sprscbbd2	:8;
//		long			sprscbbd3	:8;
//		long			sprscbbd4	:8;
//	}bit;
//};
//union IoCnrCsprRegSprscbbd2{
//	unsigned long		word;
//	struct {
//		long			sprscbbd5	:8;
//		unsigned long				:24;
//	}bit;
//};
//struct IoCnrCsprRegSprscbbd{
//	union IoCnrCsprRegSprscbbd1	sprscbbd1;
//	union IoCnrCsprRegSprscbbd2	sprscbbd2;
//};
//
///*	structure of sprscrof	(2842_1228h)	*/
//union IoCnrCsprRegSprscrof1{
//	unsigned long		word;
//	struct {
//		long			sprscrof0	:8;
//		long			sprscrof1	:8;
//		long			sprscrof2	:8;
//		long			sprscrof3	:8;
//	}bit;
//};
//union IoCnrCsprRegSprscrof2{
//	unsigned long		word;
//	struct {
//		long			sprscrof4	:8;
//		long			sprscrof5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegSprscrof{
//	union IoCnrCsprRegSprscrof1	sprscrof1;
//	union IoCnrCsprRegSprscrof2	sprscrof2;
//};
//
///*	structure of sprscrga	(2842_1230h)	*/
//union IoCnrCsprRegSprscrga1{
//	unsigned long		word;
//	struct {
//		long			sprscrga0	:12;
//		unsigned long				:4;
//		long			sprscrga1	:12;
//		unsigned long				:4;
//	}bit;
//};
//union IoCnrCsprRegSprscrga2{
//	unsigned long		word;
//	struct {
//		long			sprscrga2	:12;
//		unsigned long				:4;
//		long			sprscrga3	:12;
//		unsigned long				:4;
//	}bit;
//};
//union IoCnrCsprRegSprscrga3{
//	unsigned long		word;
//	struct {
//		long			sprscrga4	:12;
//		unsigned long				:4;
//		long			sprscrga5	:12;
//		unsigned long				:4;
//	}bit;
//};
//struct IoCnrCsprRegSprscrga{
//	union IoCnrCsprRegSprscrga1	sprscrga1;
//	union IoCnrCsprRegSprscrga2	sprscrga2;
//	union IoCnrCsprRegSprscrga3	sprscrga3;
//};
//
///*	structure of sprscrbd	(2842_1240h)	*/
//union IoCnrCsprRegSprscrbd1{
//	unsigned long		word;
//	struct {
//		long			sprscrbd1	:8;
//		long			sprscrbd2	:8;
//		long			sprscrbd3	:8;
//		long			sprscrbd4	:8;
//	}bit;
//};
//union IoCnrCsprRegSprscrbd2{
//	unsigned long		word;
//	struct {
//		long			sprscrbd5	:8;
//		unsigned long				:24;
//	}bit;
//};
//struct IoCnrCsprRegSprscrbd{
//	union IoCnrCsprRegSprscrbd1	sprscrbd1;
//	union IoCnrCsprRegSprscrbd2	sprscrbd2;
//};
//
///*	structure of sprd	(2842_1280h)	*/
//union IoCnrCsprRegSprd{
//	unsigned long		word;
//	struct {
//		unsigned long	sprd	:1;
//		unsigned long			:31;
//	}bit;
//};
//
///*	structure of sprdcbof	(2842_1288h)	*/
//union IoCnrCsprRegSprdcbof1{
//	unsigned long		word;
//	struct {
//		long			sprdcbof0	:8;
//		long			sprdcbof1	:8;
//		long			sprdcbof2	:8;
//		long			sprdcbof3	:8;
//	}bit;
//};
//union IoCnrCsprRegSprdcbof2{
//	unsigned long		word;
//	struct {
//		long			sprdcbof4	:8;
//		long			sprdcbof5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoCnrCsprRegSprdcbof{
//	union IoCnrCsprRegSprdcbof1	sprdcbof1;
//	union IoCnrCsprRegSprdcbof2	sprdcbof2;
//};
//
///*	structure of sprdcbga	(2842_1290h)	*/
//union IoSnrSsprRegSprdcbga1{
//	unsigned long		word;
//	struct {
//		long			sprdcbga0	:12;
//		unsigned long				:4;
//		long			sprdcbga1	:12;
//		unsigned long				:4;
//	}bit;
//};
//union IoSnrSsprRegSprdcbga2{
//	unsigned long		word;
//	struct {
//		long			sprdcbga2	:12;
//		unsigned long				:4;
//		long			sprdcbga3	:12;
//		unsigned long				:4;
//	}bit;
//};
//union IoSnrSsprRegSprdcbga3{
//	unsigned long		word;
//	struct {
//		long			sprdcbga4	:12;
//		unsigned long				:4;
//		long			sprdcbga5	:12;
//		unsigned long				:4;
//	}bit;
//};
//struct IoCnrCsprRegSprdcbga{
//	union IoSnrSsprRegSprdcbga1	sprdcbga1;
//	union IoSnrSsprRegSprdcbga2	sprdcbga2;
//	union IoSnrSsprRegSprdcbga3	sprdcbga3;
//};
//
///*	structure of sprdcbbd	(2842_12A0h)	*/
//union IoSnrSsprRegSprdcbbd1{
//	unsigned long		word;
//	struct {
//		long			sprdcbbd1	:8;
//		long			sprdcbbd2	:8;
//		long			sprdcbbd3	:8;
//		long			sprdcbbd4	:8;
//	}bit;
//};
//union IoSnrSsprRegSprdcbbd2{
//	unsigned long		word;
//	struct {
//		long			sprdcbbd5	:8;
//		unsigned long				:24;
//	}bit;
//};
//struct IoCnrCsprRegSprdcbbd{
//	union IoSnrSsprRegSprdcbbd1	sprdcbbd1;
//	union IoSnrSsprRegSprdcbbd2	sprdcbbd2;
//};
//
///*	structure of sprdcrof	(2842_12A8h)	*/
//union IoSnrSsprRegSprdcrof1{
//	unsigned long		word;
//	struct {
//		long			sprdcrof0	:8;
//		long			sprdcrof1	:8;
//		long			sprdcrof2	:8;
//		long			sprdcrof3	:8;
//	}bit;
//};
//union IoSnrSsprRegSprdcrof2{
//	unsigned long		word;
//	struct {
//		long			sprdcrof4	:8;
//		long			sprdcrof5	:8;
//		unsigned long				:16;
//	}bit;
//};
//struct IoSnrSsprRegSprdcrof{
//	union IoSnrSsprRegSprdcrof1	sprdcrof1;
//	union IoSnrSsprRegSprdcrof2	sprdcrof2;
//};
//
///*	structure of sprdcrga	(2842_12B0h)	*/
//union IoSnrSsprRegSprdcrga1{
//	unsigned long		word;
//	struct {
//		long			sprdcrga0	:12;
//		unsigned long				:4;
//		long			sprdcrga1	:12;
//		unsigned long				:4;
//	}bit;
//};
//union IoSnrSsprRegSprdcrga2{
//	unsigned long		word;
//	struct {
//		long			sprdcrga2	:12;
//		unsigned long				:4;
//		long			sprdcrga3	:12;
//		unsigned long				:4;
//	}bit;
//};
//union IoSnrSsprRegSprdcrga3{
//	unsigned long		word;
//	struct {
//		long			sprdcrga4	:12;
//		unsigned long				:4;
//		long			sprdcrga5	:12;
//		unsigned long				:4;
//	}bit;
//};
//struct IoSnrSsprRegSprdcrga{
//	union IoSnrSsprRegSprdcrga1	sprdcrga1;
//	union IoSnrSsprRegSprdcrga2	sprdcrga2;
//	union IoSnrSsprRegSprdcrga3	sprdcrga3;
//};
//
///*	structure of sprdcrbd	(2842_12C0h)	*/
//union IoCnrCsprRegSprdcrbd1{
//	unsigned long		word;
//	struct {
//		long			sprdcrbd1	:8;
//		long			sprdcrbd2	:8;
//		long			sprdcrbd3	:8;
//		long			sprdcrbd4	:8;
//	}bit;
//};
//union IoCnrCsprRegSprdcrbd2{
//	unsigned long		word;
//	struct {
//		long			sprdcrbd5	:8;
//		unsigned long				:24;
//	}bit;
//};
//struct IoCnrCsprRegSprdcrbd{
//	union IoCnrCsprRegSprdcrbd1	sprdcrbd1;
//	union IoCnrCsprRegSprdcrbd2	sprdcrbd2;
//};
//
///* Define i/o mapping */
//struct IoCnrCsprReg{
//	/* JDSIMG */
//	union  IoCnrCsprRegCspren	cspren;		/* 2842_(1000 - 1003h) */
//
//	unsigned char dmy_1004_1007[0x1008-0x1004];	/* 2842_(1004 - 1007h) */
//
//	union  IoCnrCsprRegCgdken	cgdken;		/* 2842_(1008 - 100Bh) */
//
//	unsigned char dmy_100C_101F[0x1020-0x100C];	/* 2842_(100C - 101Fh) */
//
//	union  IoCnrCsprRegMcen		mcen;		/* 2842_(1020 - 1023h) */
//	union  IoCnrCsprRegMcythh	mcythh;		/* 2842_(1024 - 1027h) */
//	union  IoCnrCsprRegMcythv	mcythv;		/* 2842_(1028 - 102Bh) */
//	union  IoCnrCsprRegMccthh	mccthh;		/* 2842_(102C - 102Fh) */
//	union  IoCnrCsprRegMccthv	mccthv;		/* 2842_(1030 - 1033h) */
//	union  IoCnrCsprRegMcydym	mcydym;		/* 2842_(1034 - 1037h) */
//	union  IoCnrCsprRegMcydymdt	mcydymdt;	/* 2842_(1038 - 103Bh) */
//
//	unsigned char dmy_103C_103F[0x1040-0x103C];	/* 2842_(103C - 103Fh) */
//
//	union  IoCnrCsprRegMcyscl	mcyscl;		/* 2842_(1040 - 1043h) */
//
//	unsigned char dmy_1044_1047[0x1048-0x1044];	/* 2842_(1044 - 1047h) */
//
//	struct IoCnrCsprRegMcysclof	mcysclof;	/* 2842_(1048 - 104Fh) */
//	struct IoCnrCsprRegMcysclga	mcysclga;	/* 2842_(1050 - 1057h) */
//	struct IoCnrCsprRegMcysclbd	mcysclbd;	/* 2842_(1058 - 105Fh) */
//	union  IoCnrCsprRegMccscl	mccscl;		/* 2842_(1060 - 1063h) */
//
//	unsigned char dmy_1064_1067[0x1068-0x1064];	/* 2842_(1064 - 1067h) */
//
//	struct IoCnrCsprRegMccsclof	mccsclof;	/* 2842_(1068 - 106Fh) */
//	struct IoCnrCsprRegMccsclga	mccsclga;	/* 2842_(1070 - 1077h) */
//	struct IoCnrCsprRegMccsclbd	mccsclbd;	/* 2842_(1078 - 107Fh) */
//	union  IoCnrCsprRegMcsscl	mcsscl;		/* 2842_(1080 - 1083h) */
//
//	unsigned char dmy_1084_1087[0x1088-0x1084];	/* 2842_(1084 - 1087h) */
//
//	struct IoCnrCsprRegMcssclof	mcssclof;	/* 2842_(1088 - 108Fh) */
//	struct IoCnrCsprRegMcssclga	mcssclga;	/* 2842_(1090 - 1097h) */
//	struct IoCnrCsprRegMcssclbd	mcssclbd;	/* 2842_(1098 - 109Fh) */
//
//	unsigned char dmy_10A0_10BF[0x10C0-0x10A0];	/* 2842_(10A0 - 10BFh) */
//
//	union  IoCnrCsprRegLcen		lcen;		/* 2842_(10C0 - 10C3h) */
//	union  IoCnrCsprRegLcythh	lcythh;		/* 2842_(10C4 - 10C7h) */
//	union  IoCnrCsprRegLcythv	lcythv;		/* 2842_(10C8 - 10CBh) */
//	union  IoCnrCsprRegLccthh	lccthh;		/* 2842_(10CC - 10CFh) */
//	union  IoCnrCsprRegLccthv	lccthv;		/* 2842_(10D0 - 10D3h) */
//	union  IoCnrCsprRegLcydym	lcydym;		/* 2842_(10D4 - 10D7h) */
//	union  IoCnrCsprRegLcydymdt	lcydymdt;	/* 2842_(10D8 - 10DBh) */
//
//	unsigned char dmy_10DC_10DF[0x10E0-0x10DC];	/* 2842_(10DC - 10DFh) */
//
//	union  IoCnrCsprRegLcyscl	lcyscl;		/* 2842_(10E0 - 10E3h) */
//
//	unsigned char dmy_10E4_10E7[0x10E8-0x10E4];	/* 2842_(10E4 - 10E7h) */
//
//	struct IoCnrCsprRegLcysclof	lcysclof;	/* 2842_(10E8 - 10EFh) */
//	struct IoCnrCsprRegLcysclga	lcysclga;	/* 2842_(10F0 - 10F7h) */
//	struct IoCnrCsprRegLcysclbd	lcysclbd;	/* 2842_(10F8 - 10FFh) */
//	union  IoCnrCsprRegLccscl	lccscl;		/* 2842_(1100 - 1103h) */
//
//	unsigned char dmy_1104_1107[0x1108-0x1104];	/* 2842_(1104 - 1107h) */
//
//	struct IoCnrCsprRegLccsclof	lccsclof;	/* 2842_(1108 - 110Fh) */
//	struct IoCnrCsprRegLccsclga	lccsclga;	/* 2842_(1110 - 1117h) */
//	struct IoCnrCsprRegLccsclbd	lccsclbd;	/* 2842_(1118 - 111Fh) */
//	union  IoCnrCsprRegLcsscl	lcsscl;		/* 2842_(1120 - 1123h) */
//
//	unsigned char dmy_1124_1127[0x1128-0x1124];	/* 2842_(1124 - 1127h) */
//
//	struct IoCnrCsprRegLcssclof	lcssclof;	/* 2842_(1128 - 112Fh) */
//	struct IoCnrCsprRegLcssclga	lcssclga;	/* 2842_(1130 - 1137h) */
//	struct IoCnrCsprRegLcssclbd	lcssclbd;	/* 2842_(1138 - 113Fh) */
//
//	unsigned char dmy_1140_115F[0x1160-0x1140];	/* 2842_(1140 - 115Fh) */
//
//	union  IoCnrCsprRegBlend 	blend;		/* 2842_(1160 - 1163h) */
//
//	unsigned char dmy_1164_1167[0x1168-0x1164];	/* 2842_(1164 - 1167h) */
//
//	struct IoCnrCsprRegCesclof	cesclof;	/* 2842_(1168 - 116Fh) */
//	struct IoCnrCsprRegCesclga	cesclga;	/* 2842_(1170 - 1177h) */
//	struct IoCnrCsprRegCesclbd	cesclbd;	/* 2842_(1178 - 117Fh) */
//
//	unsigned char dmy_1180_118F[0x11A0-0x1190];	/* 2842_(1180 - 118Fh) */
//
//	union  IoCnrCsprRegCphpt	cphpt;		/* 2842_(1190 - 1193h) */
//	union  IoCnrCsprRegCphptk	cphptk;		/* 2842_(1194 - 1197h) */
//
//	unsigned char dmy_1198_119F[0x11A0-0x1198];	/* 2842_(1198 - 119Fh) */
//
//	struct IoCnrCsprRegCdsclof	cdsclof;	/* 2842_(11A0 - 11ABh) */
//
//	unsigned char dmy_11AC_11AF[0x11B0-0x11AC];	/* 2842_(11AC - 11AFh) */
//
//	struct IoCnrCsprRegCdsclga	cdsclga;	/* 2842_(11B0 - 11BBh) */
//
//	unsigned char dmy_11BC_11BF[0x11C0-0x11BC];	/* 2842_(11BC - 11BFh) */
//
//	struct IoCnrCsprRegCdsclbd	cdsclbd;	/* 2842_(11C0 - 11CBh) */
//
//	unsigned char dmy_11CC_11CF[0x11D0-0x11CC];	/* 2842_(11CC - 11CFh) */
//
//	union  IoCnrCsprRegWhtmd	whtmd;		/* 2842_(11D0 - 11D3h) */
//
//	unsigned char dmy_11D4_11FF[0x1200-0x11D4];	/* 2842_(11D4 - 11FFh) */
//
//	union  IoCnrCsprRegSprs		sprs;		/* 2842_(1200 - 1203h) */
//
//	unsigned char dmy_1204_1207[0x1208-0x1204];	/* 2842_(1204 - 1207h) */
//
//	struct IoCnrCsprRegSprscbof	sprscbof;	/* 2842_(1208 - 120Fh) */
//	struct IoCnrCsprRegSprscbga	sprscbga;	/* 2842_(1210 - 121Bh) */
//
//	unsigned char dmy_121C_121F[0x1220-0x121C];	/* 2842_(121C - 121Fh) */
//
//	struct IoCnrCsprRegSprscbbd	sprscbbd;	/* 2842_(1220 - 1227h) */
//	struct IoCnrCsprRegSprscrof	sprscrof;	/* 2842_(1228 - 122Fh) */
//	struct IoCnrCsprRegSprscrga	sprscrga;	/* 2842_(1230 - 123Bh) */
//
//	unsigned char dmy_123C_123F[0x1240-0x123C];	/* 2842_(123C - 123Fh) */
//
//	struct IoCnrCsprRegSprscrbd	sprscrbd;	/* 2842_(1240 - 1247h) */
//
//	unsigned char dmy_1248_127F[0x1280-0x1248];	/* 2842_(1248 - 127Fh) */
//
//	union  IoCnrCsprRegSprd		sprd;		/* 2842_(1280 - 1283h) */
//
//	unsigned char dmy_1284_1287[0x1288-0x1284];	/* 2842_(1284 - 1287h) */
//
//	struct IoCnrCsprRegSprdcbof	sprdcbof;	/* 2842_(1288 - 128Fh) */
//	struct IoCnrCsprRegSprdcbga	sprdcbga;	/* 2842_(1290 - 129Bh) */
//
//	unsigned char dmy_129C_129F[0x12A0-0x129C];	/* 2842_(129C - 129Fh) */
//
//	struct IoCnrCsprRegSprdcbbd	sprdcbbd;	/* 2842_(12A0 - 12A7h) */
//	struct IoSnrSsprRegSprdcrof	sprdcrof;	/* 2842_(12A8 - 12AFh) */
//	struct IoSnrSsprRegSprdcrga	sprdcrga;	/* 2842_(12B0 - 12BBh) */
//
//	unsigned char dmy_12BC_12BF[0x12C0-0x12BC];	/* 2842_(12BC - 12BFh) */
//
//	struct IoCnrCsprRegSprdcrbd	sprdcrbd;	/* 2842_(12C0 - 12C7h) */
//
//	unsigned char dmy_12C8_1FFF[0x2000-0x12C8];	/* 2842_(12C8 - 1FFFh) */
//
//};

#endif	  // #define __JDSCNR_CSPR_REG_H__
