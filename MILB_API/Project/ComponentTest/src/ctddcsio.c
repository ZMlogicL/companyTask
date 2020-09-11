/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :杨升柄
*@brief               :CtDdCsio类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/
#include "stdlib.h"
#include "string.h"
#include "dd_csio.h"
#include "dd_uart.h"
#include "dd_top.h"
#include "dd_hdmac1.h"
#include "dd_gic.h"
#include "dd_tmr32.h"
#include "uart_csio.h"
#include "ct_dd_csio.h"
#include "ctddcsiomain.h"
#include "ctddcsio.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdCsio, ct_dd_csio);
#define CT_DD_CSIO_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdCsioPrivate,CT_TYPE_DD_CSIO))

struct _CtDdCsioPrivate
{
};

static kuint32*					S_SEND_SIZE;
static kuchar*					S_BUF2_USED;
static kuchar*					S_SEND_FLG;
static kuchar* 					S_SENDING_CH_NUMBER;

static kuchar* 					S_RCV_BUF82 = NULL;
static kushort* 					S_RCV_BUF162 = NULL;
static kuchar* 					S_RCV_BUF8 = NULL;
static kushort* 					S_RCV_BUF16 = NULL;
static kuchar* 					S_RCV_BUF8_SLAVE = NULL;


static kuchar 						S_BUF8[8] = {0x11, 0x22, 0x44, 0x08, 0x10, 0x20, 0x40, 0x80};
static kuchar 						S_BUF8_SLAVE[8] = {0x33, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB};
static kushort 					S_BUF16[8] = {0x0198, 0x0176, 0x0154, 0x0132, 0x0110, 0x0120, 0x0140, 0x0180};
static E_DD_CSIO_TYPE 	S_TYPE[D_DD_USIO_CH_NUM_MAX] = {E_DD_CSIO_TYPE_MASTER};

#if 0
const static kuchar 			S_BUF8[255] =
	{
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
		21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
		41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,
		61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,
		81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,
		101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,
		121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,
		141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,
		161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,
		181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,
		201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,
		221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,
		241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
	};

const static kuchar 			S_BUF82[512] =
	{
		   0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
		   0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
		   0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,
		   0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
		   0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60,
		   0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,
		   0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80,
		   0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90,
		   0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0,
		   0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0,
		   0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0,
		   0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0,
		   0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0,
		   0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0,
		   0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF, 0x12,
		   0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22,
		   0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32,
		   0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42,
		   0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52,
		   0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62,
		   0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72,
		   0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82,
		   0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92,
		   0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2,
		   0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2,
		   0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2,
		   0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2,
		   0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2,
		   0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2,
		   0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF, 0x13, 0x14, 0x15,
		   0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
		   0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35
	};

const static kushort 		S_BUF162[512]	=
	{
			0x0100, 0x0101, 0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x0108, 0x0109, 0x010A, 0x010B, 0x010C,
			0x010D, 0x010E, 0x010F,0x0110, 0x0111, 0x0112, 0x0113, 0x0114, 0x0115, 0x0116, 0x0117, 0x0118, 0x0119,
			0x011A, 0x011B, 0x011C, 0x011D, 0x011E, 0x011F,0x0120, 0x0121, 0x0122, 0x0123, 0x0124, 0x0125, 0x0126,
			0x0127, 0x0128, 0x0129, 0x012A, 0x012B, 0x012C, 0x012D, 0x012E, 0x012F,0x0130, 0x0131, 0x0132, 0x0133,
			0x0134, 0x0135, 0x0136, 0x0137, 0x0138, 0x0139, 0x013A, 0x013B, 0x013C, 0x013D, 0x013E, 0x013F,0x0140,
			0x0141, 0x0142, 0x0143, 0x0144, 0x0145, 0x0146, 0x0147, 0x0148, 0x0149, 0x014A, 0x014B, 0x014C, 0x014D,
			0x014E, 0x014F,0x0150, 0x0151, 0x0152, 0x0153, 0x0154, 0x0155, 0x0156, 0x0157, 0x0158, 0x0159, 0x015A,
			0x015B, 0x015C, 0x015D, 0x015E, 0x015F,0x0160, 0x0161, 0x0162, 0x0163, 0x0164, 0x0165, 0x0166, 0x0167,
			0x0168, 0x0169, 0x016A, 0x016B, 0x016C, 0x016D, 0x016E, 0x016F,0x0170, 0x0171, 0x0172, 0x0173, 0x0174,
			0x0175, 0x0176, 0x0177, 0x0178, 0x0179, 0x017A, 0x017B, 0x017C, 0x017D, 0x017E, 0x017F,0x0180, 0x0181,
			0x0182, 0x0183, 0x0184, 0x0185, 0x0186, 0x0187, 0x0188, 0x0189, 0x018A, 0x018B, 0x018C, 0x018D, 0x018E,
			0x018F,0x0190, 0x0191, 0x0192, 0x0193, 0x0194, 0x0195, 0x0196, 0x0197, 0x0198, 0x0199, 0x019A, 0x019B,
			0x019C, 0x019D, 0x019E, 0x019F,0x01A0, 0x01A1, 0x01A2, 0x01A3, 0x01A4, 0x01A5, 0x01A6, 0x01A7, 0x01A8,
			0x01A9, 0x01AA, 0x01AB, 0x01AC, 0x01AD, 0x01AE, 0x01AF,0x01B0, 0x01B1, 0x01B2, 0x01B3, 0x01B4, 0x01B5,
			0x01B6, 0x01B7, 0x01B8, 0x01B9, 0x01BA, 0x01BB, 0x01BC, 0x01BD, 0x01BE, 0x01BF,0x01C0, 0x01C1, 0x01C2,
			0x01C3, 0x01C4, 0x01C5, 0x01C6, 0x01C7, 0x01C8, 0x01C9, 0x01CA, 0x01CB, 0x01CC, 0x01CD, 0x01CE, 0x01CF,
			0x01D0, 0x01D1, 0x01D2, 0x01D3, 0x01D4, 0x01D5, 0x01D6, 0x01D7, 0x01D8, 0x01D9, 0x01DA, 0x01DB, 0x01DC,
			0x01DD, 0x01DE, 0x01DF,0x01E0, 0x01E1, 0x01E2, 0x01E3, 0x01E4, 0x01E5, 0x01E6, 0x01E7, 0x01E8, 0x01E9,
			0x01EA, 0x01EB, 0x01EC, 0x01ED, 0x01EE, 0x01EF,0x01F0, 0x01F1, 0x01F2, 0x01F3, 0x01F4, 0x01F5, 0x01F6,
			0x01F7,0x01F8, 0x01F9, 0x01FA, 0x01FB, 0x01FC, 0x01FD, 0x01FE, 0x01FF,0x01F0, 0x01F1, 0x01F2, 0x01F3,
			0x01F4, 0x01F5, 0x01F6, 0x01F7, 0x01F8, 0x01F9, 0x01FA, 0x01FB, 0x01FC, 0x01FD, 0x01FE, 0x01FF,0x01E0,
			0x01E1, 0x01E2, 0x01E3, 0x01E4, 0x01E5, 0x01E6, 0x01E7, 0x01E8, 0x01E9, 0x01EA, 0x01EB, 0x01EC, 0x01ED,
			0x01EE, 0x01EF,0x01D0, 0x01D1, 0x01D2, 0x01D3, 0x01D4, 0x01D5, 0x01D6, 0x01D7, 0x01D8, 0x01D9, 0x01DA,
			0x01DB, 0x01DC, 0x01DD, 0x01DE, 0x01DF,0x01C0, 0x01C1, 0x01C2, 0x01C3, 0x01C4, 0x01C5, 0x01C6, 0x01C7,
			0x01C8, 0x01C9, 0x01CA, 0x01CB, 0x01CC, 0x01CD, 0x01CE, 0x01CF,0x01B0, 0x01B1, 0x01B2, 0x01B3, 0x01B4,
			0x01B5, 0x01B6, 0x01B7, 0x01B8, 0x01B9, 0x01BA, 0x01BB, 0x01BC, 0x01BD, 0x01BE, 0x01BF, 0x01A0, 0x01A1,
			0x01A2, 0x01A3, 0x01A4, 0x01A5, 0x01A6, 0x01A7, 0x01A8, 0x01A9, 0x01AA, 0x01AB, 0x01AC, 0x01AD, 0x01AE,
			0x01AF,0x0190, 0x0191, 0x0192, 0x0193, 0x0194, 0x0195, 0x0196, 0x0197, 0x0198, 0x0199, 0x019A, 0x019B,
			0x019C, 0x019D, 0x019E, 0x019F,0x0180, 0x0181, 0x0182, 0x0183, 0x0184, 0x0185, 0x0186, 0x0187, 0x0188,
			0x0189, 0x018A, 0x018B, 0x018C, 0x018D, 0x018E, 0x018F,0x0170, 0x0171, 0x0172, 0x0173, 0x0174, 0x0175,
			0x0176, 0x0177, 0x0178, 0x0179, 0x017A, 0x017B, 0x017C, 0x017D, 0x017E, 0x017F,0x0160, 0x0161, 0x0162,
			0x0163, 0x0164, 0x0165, 0x0166, 0x0167, 0x0168, 0x0169, 0x016A, 0x016B, 0x016C, 0x016D, 0x016E, 0x016F,
			0x0150, 0x0151, 0x0152, 0x0153, 0x0154, 0x0155, 0x0156, 0x0157, 0x0158, 0x0159, 0x015A, 0x015B, 0x015C,
			0x015D, 0x015E, 0x015F,0x0140, 0x0141, 0x0142, 0x0143, 0x0144, 0x0145, 0x0146, 0x0147, 0x0148, 0x0149,
			0x014A, 0x014B, 0x014C, 0x014D, 0x014E, 0x014F,0x0130, 0x0131, 0x0132, 0x0133, 0x0134, 0x0135, 0x0136,
			0x0137, 0x0138, 0x0139, 0x013A, 0x013B, 0x013C, 0x013D, 0x013E, 0x013F,0x0120, 0x0121, 0x0122, 0x0123,
			0x0124, 0x0125, 0x0126, 0x0127, 0x0128, 0x0129, 0x012A, 0x012B, 0x012C, 0x012D, 0x012E, 0x012F,0x0110,
			0x0111, 0x0112, 0x0113, 0x0114, 0x0115, 0x0116, 0x0117, 0x0118, 0x0119, 0x011A, 0x011B, 0x011C, 0x011D,
			0x011E, 0x011F,0x0100, 0x0101, 0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x0108, 0x0109, 0x010A,
			0x010B, 0x010C, 0x010D, 0x010E, 0x010F
	};

#endif

#ifdef CO_DEBUG_ON_PC
static kchar* 					S_CMD_ARGV[25];
#endif	/*CO_DEBUG_ON_PC */

/*
 * DECLS
 */
#ifdef CO_DEBUG_ON_PC
static void ctCsioSetCmd( kint cmdArgc, kchar* cmdArgv );
static void ctCsioRegDump(kint ch);
#endif	/* CO_DEBUG_ON_PC */

static void ct_dd_csio_constructor(CtDdCsio *self)
{
#if 0
	memcpy(self->gBuf8, S_BUF8, sizeof(S_BUF8));
	memcpy(self->gBuf82, S_BUF82, sizeof(S_BUF82));
	memcpy(self->gBuf162, S_BUF162, sizeof(S_BUF162));
#endif

	memcpy(self->gBuf8, S_BUF8, sizeof(S_BUF8));
	memcpy(self->gBuf8Slave, S_BUF8_SLAVE, sizeof(S_BUF8_SLAVE));
	memcpy(self->gBuf16, S_BUF16, sizeof(S_BUF16));
	memcpy(self->gType, S_TYPE, sizeof(S_TYPE));

	self->gDataLength = E_DD_CSIO_DATA_LENGTH_8;

	S_SEND_SIZE = &(self->gSendSize);
	S_BUF2_USED = &(self->gBuf2Used);
	S_SEND_FLG = &(self->gSendFlg);
	S_SENDING_CH_NUMBER = &(self->gSendingChNumber);

	S_RCV_BUF82 = self->gRcvBuf82;
	S_RCV_BUF162 = self->gRcvBuf162;
	S_RCV_BUF8 = self->gRcvBuf8;
	S_RCV_BUF16 = self->gRcvBuf16;
	S_RCV_BUF8_SLAVE = self->gRcvBuf8Slave;

	self->ret = D_DDIM_OK;
	self->tmout = D_DDIM_USER_SEM_WAIT_POL;
}

static void ct_dd_csio_destructor(CtDdCsio *self)
{
}

/*
 * IMPL
 */
#ifdef CO_DEBUG_ON_PC
static void ctCsioSetCmd( kint cmdArgc, kchar* cmdArgv )
{
	kint32 j;
	kint32 cmdPos = 0;

	for( j = 0; j < cmdArgc; j++ ) {
		S_BUF162S_CMD_ARGV[ j ] = ( cmdArgv + ( cmdPos * CtDdCsio_TEST_CMD_LEN ) );
		cmdPos++;
	}
}

static void ctCsioRegDump(kint ch)
{
	Ddim_Print(("---- CSIO Register dump ----\n"));
	Ddim_Print(("CSIO%d.SMR   = 0x%02x\n", ch, IO_USIO.CSIO[ch].SMR.byte));
	Ddim_Print(("CSIO%d.SCR   = 0x%02x\n", ch, IO_USIO.CSIO[ch].SCR.byte));
	Ddim_Print(("CSIO%d.ESCR  = 0x%02x\n", ch, IO_USIO.CSIO[ch].ESCR.byte));
	Ddim_Print(("CSIO%d.SSR   = 0x%02x\n", ch, IO_USIO.CSIO[ch].SSR.byte));
	Ddim_Print(("CSIO%d.DR    = 0x%04x\n", ch, IO_USIO.CSIO[ch].DR.hword));
	Ddim_Print(("CSIO%d.BGR   = 0x%04x\n", ch, IO_USIO.CSIO[ch].BGR.hword));
	Ddim_Print(("CSIO%d.FCR   = 0x%04x\n", ch, IO_USIO.CSIO[ch].FCR.hword));
	Ddim_Print(("CSIO%d.FBYTE = 0x%04x\n", ch, IO_USIO.CSIO[ch].FBYTE.hword));
	Ddim_Print(("----------------------------\n"));

	return;
}
#endif	/* CO_DEBUG_ON_PC */

/*
 * PUBLIC
 */
void ct_dd_csio_callback( kint32 result )
{
	kint32 index;

	Ddim_Print(("CSIO Callback. result=%X\n", result));

	if ((*S_SEND_SIZE) <= 300) {
		if ( *S_BUF2_USED ) {
			for (index = 0; index < (*S_SEND_SIZE); index++ ){
				Ddim_Print(("gRcvBuf82[%d]=0x%X    gRcvBuf162[%d]=0x%X\n",
						index, S_RCV_BUF82[index], index, S_RCV_BUF162[index]));
			}
		}else
		{
			for (index = 0; index < (*S_SEND_SIZE); index++ ){
				Ddim_Print(("Rcv_buf8[%d]=0x%X    Rcv_buf16[%d]=0x%X\n",
						index, S_RCV_BUF8[index], index, S_RCV_BUF16[index]));
			}
		}
	}
}

void ct_dd_csio_send_callback( kint32 result )
{
	Ddim_Print(("CSIO Send Callback. result=%X\n", result));
}

void ct_dd_csio_receive_callback( kint32 result )
{
	kint32 index;

	Ddim_Print(("CSIO Receive Callback. result=%X\n", result));

	if ((*S_SEND_SIZE) <= 300) {
		if ( *S_BUF2_USED ) {
			for (index = 0; index < (*S_SEND_SIZE); index++ ){
				Ddim_Print(("gRcvBuf82[%d]=0x%X    gRcvBuf162[%d]=0x%X\n",
						index, S_RCV_BUF82[index], index, S_RCV_BUF162[index]));
			}
		}else
		{
			for (index = 0; index < (*S_SEND_SIZE); index++ ){
				Ddim_Print(("Rcv_buf8[%d]=0x%X    Rcv_buf16[%d]=0x%X\n",
						index, S_RCV_BUF8[index], index, S_RCV_BUF16[index]));
			}
		}
	}
}

void ct_dd_csio_callback_full_duplex(kint32 result )
{
	kint32 index;

	Ddim_Print(("CSIO Callback. (full_duplex) result=%X\n", result));

	for (index = 0; index < 8; index++ ){
		Ddim_Print(("Rcv_buf8[%d]=0x%X    Rcv_buf16[%d]=0x%X    Rcv_buf8_slave[%d]=0x%X\n",
				index, S_RCV_BUF8[index], index, S_RCV_BUF16[index], index, S_RCV_BUF8_SLAVE[index]));
	}
}

void ct_dd_csio_callback_full_duplex_dma( kint32 result )
{
	Ddim_Print(("CSIO Callback. (full_duplex_dma) result=%X\n", result));
}

void ct_dd_csio_timer_handler_callback(void)
{
	kint32 ret;

	if(*S_SEND_FLG == 1){
		Ddim_Print(("CSIO Send Timeout.\n"));
		ret = Dd_CSIO_Stop(*S_SENDING_CH_NUMBER);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Stop ERR. ret=0x%x\n", ret));
		}
		*S_SEND_FLG = 0;
	}
}

void ct_dd_csio_set_port( CtDdCsio *self )
{
	Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_P86, 1 );
	Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_P87, 1 );
	Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_PE5, 1 );
	Dd_Top_Set_Gpio_Function( E_DD_TOP_GPIO_PE3, 1 );
	Dd_Top_Set_Gpio_Direction( E_DD_TOP_GPIO_PE4, 0 );
	Dd_Top_Set_Gpio_Direction( E_DD_TOP_GPIO_PE2, 0 );

	Dd_GIC_Ctrl(E_DD_GIC_INTID_UART_CH0_RECEPTION_INT, 1, D_DD_GIC_PRI14, 1);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_UART_CH1_RECEPTION_INT, 1, D_DD_GIC_PRI14, 1);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_UART_CH0_TRANSMISSION_INT, 1, D_DD_GIC_PRI14, 1);
	Dd_GIC_Ctrl(E_DD_GIC_INTID_UART_CH1_TRANSMISSION_INT, 1, D_DD_GIC_PRI14, 1);
}

void ct_dd_csio_from_main_with_ctrl(CtDdCsio *self, kuchar ch )
{
	T_DD_CSIO_CTRL csioCtrl;
	T_DD_CSIO_FIFO_CTRL fifoCtrl;

	csioCtrl.fifo_ctrl = &fifoCtrl;

	Dd_CSIO_Get_Ctrl(ch, &csioCtrl);
	Ddim_Print(("CSIO Ctrl_Get OK.\n"));
	Ddim_Print(("CSIO baudrate              =%lu\n", csioCtrl.baudrate));
	Ddim_Print(("CSIO mode                  =%d\n", csioCtrl.mode));
	Ddim_Print(("CSIO bit_direction         =%d\n", csioCtrl.bit_direction));
	Ddim_Print(("CSIO data_length           =%d\n", csioCtrl.data_length));
	Ddim_Print(("CSIO type                  =%d\n", csioCtrl.type));
	Ddim_Print(("CSIO output                =%d\n", csioCtrl.sop));
	Ddim_Print(("CSIO pcallback             =%p\n", csioCtrl.pcallback));
	Ddim_Print(("CSIO fifo_ctrl->fsel       =%d\n", csioCtrl.fifo_ctrl->fsel));
	Ddim_Print(("CSIO fifo_ctrl->fe2        =%d\n", csioCtrl.fifo_ctrl->fe2));
	Ddim_Print(("CSIO fifo_ctrl->fe1        =%d\n", csioCtrl.fifo_ctrl->fe1));
	Ddim_Print(("CSIO fifo_ctrl->fbyte_recv =%d\n", csioCtrl.fifo_ctrl->fbyte_recv));
}

void ct_dd_csio_from_main_with_err(CtDdCsio *self, kint32 tmout, kushort baudrate)
{
	kint32 ret;
	T_DD_CSIO_CTRL csioCtrl;
	T_DD_CSIO_SEND_CTRL csioSendCtrl;

	ret = Dd_CSIO_Open( D_DD_USIO_CH_NUM_MAX, tmout );
	Ddim_Print(("Dd_CSIO_Open(): CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Open( 0, -2 );
	Ddim_Print(("Dd_CSIO_Open(): tmout value error. ret=%X\n", ret ));

	ret = Dd_CSIO_Close( D_DD_USIO_CH_NUM_MAX );
	Ddim_Print(("Dd_CSIO_Close(): CH number error. ret=%X\n", ret ));


	ret = Dd_CSIO_Ctrl( D_DD_USIO_CH_NUM_MAX, &csioCtrl );
	Ddim_Print(("Dd_CSIO_Ctrl(): CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Ctrl( 0, NULL );
	Ddim_Print(("Dd_CSIO_Ctrl(): csioCtrl is NULL. ret=%X\n", ret ));


	ret = Dd_CSIO_Get_Ctrl( D_DD_USIO_CH_NUM_MAX, &csioCtrl );
	Ddim_Print(("Dd_CSIO_Get_Ctrl(): CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Get_Ctrl( 0, NULL );
	Ddim_Print(("Dd_CSIO_Get_Ctrl(): csioCtrl is NULL. ret=%X\n", ret ));


	ret = Dd_CSIO_Set_Send_Data( D_DD_USIO_CH_NUM_MAX, self->gBuf8, 1 );
	Ddim_Print(("Dd_CSIO_Set_Send_Data(): CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Set_Send_Data( 0, NULL, 1 );
	Ddim_Print(("Dd_CSIO_Set_Send_Data(): send_addr is NULL. ret=%X\n", ret ));

	ret = Dd_CSIO_Set_Send_Data( 0, self->gBuf8, 0 );
	Ddim_Print(("Dd_CSIO_Set_Send_Data(): num is 0. ret=%X\n", ret ));


	ret = Dd_CSIO_Start_Send( D_DD_USIO_CH_NUM_MAX );
	Ddim_Print(("Dd_CSIO_Start_Send(): CH number error. ret=%X\n", ret ));


	ret = Dd_CSIO_Set_Recv_Data( D_DD_USIO_CH_NUM_MAX, self->gRcvBuf8, 1 );
	Ddim_Print(("Dd_CSIO_Set_Recv_Data(): CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Set_Recv_Data( 0, NULL, 1 );
	Ddim_Print(("Dd_CSIO_Set_Recv_Data(): recv_addr is NULL. ret=%X\n", ret ));

	ret = Dd_CSIO_Set_Recv_Data( 0, self->gRcvBuf8, 0 );
	Ddim_Print(("Dd_CSIO_Set_Recv_Data(): num is 0. ret=%X\n", ret ));


	ret = Dd_CSIO_Start_Recv( D_DD_USIO_CH_NUM_MAX );
	Ddim_Print(("Dd_CSIO_Start_Recv(): CH number error. ret=%X\n", ret ));


	ret = Dd_CSIO_Start_Full_Duplex( D_DD_USIO_CH_NUM_MAX );
	Ddim_Print(("Dd_CSIO_Start_Full_Duplex(): CH number error. ret=%X\n", ret ));


	ret = Dd_CSIO_Stop( D_DD_USIO_CH_NUM_MAX );
	Ddim_Print(("Dd_CSIO_Stop(): CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Calculate( NULL);
	Ddim_Print(("Dd_CSIO_Calculate(): cal_tbl is NULL. ret=%X\n", ret ));

	Dd_CSIO_Int_Handler_Tx( D_DD_USIO_CH_NUM_MAX);
	Ddim_Print(("Dd_CSIO_Int_Handler_Tx(): CH number error.\n"));

	Dd_CSIO_Int_Handler_Rx( D_DD_USIO_CH_NUM_MAX);
	Ddim_Print(("Dd_CSIO_Int_Handler_Rx(): CH number error.\n"));


	ret = Dd_CSIO_Send( D_DD_USIO_CH_NUM_MAX, &csioSendCtrl, self->gBuf8, 1 );
	Ddim_Print(("Dd_CSIO_Send(): CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Send( 0, NULL, self->gBuf8, 1 );
	Ddim_Print(("Dd_CSIO_Send(): csioSendCtrl is NULL. ret=%X\n", ret ));

	ret = Dd_CSIO_Send( 0, &csioSendCtrl, NULL, 1 );
	Ddim_Print(("Dd_CSIO_Send(): send_addr is NULL. ret=%X\n", ret ));

	ret = Dd_CSIO_Send( 0, &csioSendCtrl, self->gBuf8, 0 );
	Ddim_Print(("Dd_CSIO_Send(): num is 0. ret=%X\n", ret ));

	ret = Dd_CSIO_Start_Send_DMA( D_DD_USIO_CH_NUM_MAX, 5, D_DD_CSIO_SEND_DMA_MODE_DEMAND );
	Ddim_Print(("Dd_CSIO_Start_Send_DMA(): CSIO CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Start_Send_DMA( 0, D_DD_HDMAC1_CH_NUM_MAX, D_DD_CSIO_SEND_DMA_MODE_DEMAND );
	Ddim_Print(("Dd_CSIO_Start_Send_DMA(): DMA CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Start_Send_DMA( 0, 0, D_DD_CSIO_SEND_DMA_MODE_DEMAND + 1 );
	Ddim_Print(("Dd_CSIO_Start_Send_DMA(): DMA mode error. ret=%X\n", ret ));


	ret = Dd_CSIO_Start_Recv_DMA( D_DD_USIO_CH_NUM_MAX, 5, D_DD_CSIO_RECV_DMA_MODE_DEMAND );
	Ddim_Print(("Dd_CSIO_Start_Recv_DMA(): CSIO CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Start_Recv_DMA( 0, D_DD_HDMAC1_CH_NUM_MAX, D_DD_CSIO_RECV_DMA_MODE_DEMAND  );
	Ddim_Print(("Dd_CSIO_Start_Recv_DMA(): DMA CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Start_Recv_DMA( 0, 0, D_DD_CSIO_RECV_DMA_MODE_DEMAND + 1 );
	Ddim_Print(("Dd_CSIO_Start_Recv_DMA(): DMA mode error. ret=%X\n", ret ));


	ret = Dd_CSIO_Start_Full_Duplex_DMA( D_DD_USIO_CH_NUM_MAX, 0, 1 );
	Ddim_Print(("Dd_CSIO_Start_Full_DMA(): CSIO CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Start_Full_Duplex_DMA( 0, D_DD_HDMAC1_CH_NUM_MAX, 7 );
	Ddim_Print(("Dd_CSIO_Start_Full_DMA(): DMA CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Start_Full_Duplex_DMA( 0, 7, D_DD_HDMAC1_CH_NUM_MAX );
	Ddim_Print(("Dd_CSIO_Start_Full_DMA(): DMA CH number error. ret=%X\n", ret ));


	ret = Dd_CSIO_Set_Baudrate(D_DD_USIO_CH_NUM_MAX, 10000);
	Ddim_Print(("Dd_CSIO_Set_Baudrate(): CSIO CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Get_Baudrate(D_DD_USIO_CH_NUM_MAX, &baudrate);
	Ddim_Print(("Dd_CSIO_Get_Baudrate(): CSIO CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Get_Baudrate(0, NULL);
	Ddim_Print(("Dd_CSIO_Get_Baudrate(): baud_rate is NULL. ret=%X\n", ret ));


	ret = Dd_CSIO_Save_Send_FIFO_Pointer(D_DD_USIO_CH_NUM_MAX, 0);
	Ddim_Print(("Dd_CSIO_Save_Send_FIFO_Pointer(): CSIO CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Save_Send_FIFO_Pointer(0, 2);
	Ddim_Print(("Dd_CSIO_Save_Send_FIFO_Pointer(): CSIO lost_detect error. ret=%X\n", ret ));


	ret = Dd_CSIO_Reload_Send_FIFO_Pointer(D_DD_USIO_CH_NUM_MAX);
	Ddim_Print(("Dd_CSIO_Reload_Send_FIFO_Pointer(): CSIO CH number error. ret=%X\n", ret ));


	ret = Dd_CSIO_Get_Reload_Status(D_DD_USIO_CH_NUM_MAX);
	Ddim_Print(("Dd_CSIO_Get_Reload_Status(): CSIO CH number error. ret=%X\n", ret ));


	ret = Dd_CSIO_Reset_FIFO(D_DD_USIO_CH_NUM_MAX, 0);
	Ddim_Print(("Dd_CSIO_Reset_FIFO(): CSIO CH number error. ret=%X\n", ret ));

	ret = Dd_CSIO_Reset_FIFO(0, 0);
	Ddim_Print(("Dd_CSIO_Reset_FIFO(): fifo_num number error. ret=%X\n", ret ));
}

/*
 * @brief	CSIO PCSim Test.
 * @param	void
 * @return	void
 */
void ct_dd_csio_pcsim_test(CtDdCsio *self)
{
#ifdef CO_DEBUG_ON_PC
	kint cmdCnt = 0;

	// CSIO Test command data
	kchar csioTestArgv1[][CtDdCsio_TEST_CMD_LEN] = { "ddcsio", "open", "0", "0" };
	kchar csioTestArgv2[][CtDdCsio_TEST_CMD_LEN] = { "ddcsio", "ctrl", "0", "0", "normal_h",
													"lsb", "8", "sop0", "1200", "fsel0",
													"fe00", "2", "fset0", "flste0", "cb1" };
	kchar csioTestArgv3[][CtDdCsio_TEST_CMD_LEN] = { "ddcsio", "get_ctrl", "0" };
	kchar csioTestArgv4[][CtDdCsio_TEST_CMD_LEN] = { "ddcsio", "set_brate", "0", "3488" };

	// Test CSIO

	Ddim_Print(("\n======== CSIO ========\n"));
	Ddim_Print((">> Test 1-1-1 ~ 1-1-6\n"));
	// Dd_CSIO_Open
	cmdCnt = 4;
	ctCsioSetCmd(cmdCnt, (kchar*)csioTestArgv1);
	CtDdCsioMain* csMain =  ct_dd_csio_main_new();
	ct_dd_csio_main_test(csMain,cmdCnt, S_BUF162S_CMD_ARGV);
	k_object_unref(csMain);
	csMain = NULL;

	// Dd_CSIO_Ctrl
	cmdCnt = 15;
	ctCsioSetCmd(cmdCnt, (kchar*)csioTestArgv2);
	CtDdCsioMain* csMain1 =  ct_dd_csio_main_new();
	ct_dd_csio_main_test(csMain1,cmdCnt, S_BUF162S_CMD_ARGV);
	k_object_unref(csMain1);
	csMain1 = NULL;

	// check register
	ctCsioRegDump(0);

	Ddim_Print(("\n>> Test 1-2-1 ~ 1-2-6\n"));
	// Dd_CSIO_Get_Ctrl
	cmdCnt = 3;
	ctCsioSetCmd(cmdCnt, (kchar*)csioTestArgv3);
	CtDdCsioMain* csMain2 =  ct_dd_csio_main_new();
	ct_dd_csio_main_test(csMain2,cmdCnt, S_BUF162S_CMD_ARGV);
	k_object_unref(csMain2);
	csMain2 = NULL;

	Ddim_Print(("\n>> Test 1-3-1\n"));
	// Dd_UART_Open (same ch)
	cmdCnt = 4;
	ctCsioSetCmd(cmdCnt, (kchar*)csioTestArgv4);
	CtDdCsioMain* csMain3 =  ct_dd_csio_main_new();
	ct_dd_csio_main_test(csMain3,cmdCnt, S_BUF162S_CMD_ARGV);
	k_object_unref(csMain3);
	csMain3 = NULL;

	// check register
	ctCsioRegDump(0);

	Ddim_Print(("\n>> Test 2-1-1\n"));
	// Dd_UART_Open (same ch)
	cmdCnt = 4;
	ctCsioSetCmd(cmdCnt, (kchar*)csioTestArgv1);
	CtDdCsioMain* csMain4 =  ct_dd_csio_main_new();
	ct_dd_csio_main_test(csMain4,cmdCnt, S_BUF162S_CMD_ARGV);
	k_object_unref(csMain4);
	csMain4 = NULL;
#endif	/* CO_DEBUG_ON_PC*/
}

kint32 ct_dd_csio_from_process(CtDdCsio *self, kuchar ch, kuchar num)
{
	self->csioCtrl.fifo_ctrl = &self->fifoCtrl;

	switch (num) {
		// Send
		case 1:
			self->calTbl.in_freq = 100000;
			self->calTbl.cal_freq = 0;
			self->ret = Dd_CSIO_Calculate(&self->calTbl);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. ret=0x%x\n", self->ret));
			}

			// Transmit mode              :Nomal I
			self->csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_H;
			// Baudrate
			self->csioCtrl.baudrate = self->calTbl.cal_freq;
			// Serial output              :Output
			self->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			self->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :8 bit
			self->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
			// Type                       :Master/Slave
			self->csioCtrl.type = self->gType[ch];

			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			self->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			self->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			self->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Disable
			self->csioCtrl.fifo_ctrl->fe2 = 0;
			// FIFO 1 enable              :Disable
			self->csioCtrl.fifo_ctrl->fe1 = 0;
			// FIFO receive data size     :0 byte
			self->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			self->csioCtrl.pcallback = 0;
			self->gAsync = 0;

			self->gSendSize = 3;

			self->ret = Dd_CSIO_Open(ch, self->tmout);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. ret=0x%x\n", self->ret));
			}
			self->ret = Dd_CSIO_Ctrl(ch, &self->csioCtrl);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. ret=0x%x\n", self->ret));
			}
			self->ret = Dd_CSIO_Set_Send_Data(ch, self->gBuf8, self->gSendSize);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. ret=0x%x\n", self->ret));
			}
			break;

		case 2:
			self->calTbl.in_freq = 100000;
			self->calTbl.cal_freq = 0;
			self->ret = Dd_CSIO_Calculate(&self->calTbl);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. ret=0x%x\n", self->ret));
			}

			// Transmit mode              :Nomal II
			self->csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_L;
			// Baudrate
			self->csioCtrl.baudrate = self->calTbl.cal_freq;
			// Serial output              :Output
			self->csioCtrl.sop = 0;
			// Bit direction              :LSB First
			self->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_LSB_FIRST;
			// Data length                :5 bit
			self->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_5;
			// Type                       :Master/Slave
			self->csioCtrl.type = self->gType[ch];

			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			self->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			self->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			self->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Disable
			self->csioCtrl.fifo_ctrl->fe2 = 0;
			// FIFO 1 enable              :Disable
			self->csioCtrl.fifo_ctrl->fe1 = 0;
			// FIFO receive data size     :0 byte
			self->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			self->csioCtrl.pcallback = ct_dd_csio_send_callback;
			self->gAsync = 1;

			self->gSendSize = 3;

			self->ret = Dd_CSIO_Open(ch, self->tmout);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. ret=0x%x\n", self->ret));
			}
			self->ret = Dd_CSIO_Ctrl(ch, &self->csioCtrl);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. ret=0x%x\n", self->ret));
			}
			self->ret = Dd_CSIO_Set_Send_Data(ch, self->gBuf8, self->gSendSize);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. ret=0x%x\n", self->ret));
			}
			break;

		case 3:
			self->calTbl.in_freq = 100000;
			self->calTbl.cal_freq = 0;
			self->ret = Dd_CSIO_Calculate(&self->calTbl);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. ret=0x%x\n", self->ret));
			}

			// Transmit mode              :SPI I
			self->csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_H;
			// Baudrate
			self->csioCtrl.baudrate = self->calTbl.cal_freq;
			// Serial output              :Output
			self->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			self->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :9 bit
			self->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_9;
			// Type                       :Master/Slave
			self->csioCtrl.type = self->gType[ch];

			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			self->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			self->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			self->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Disable
			self->csioCtrl.fifo_ctrl->fe2 = 0;
			// FIFO 2 enable              :Enable
			self->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO receive data size     :0 byte
			self->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			self->csioCtrl.pcallback = 0;
			self->gAsync = 0;

			self->gSendSize = 3;

			self->ret = Dd_CSIO_Open(ch, self->tmout);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. ret=0x%x\n", self->ret));
			}
			self->ret = Dd_CSIO_Ctrl(ch, &self->csioCtrl);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. ret=0x%x\n", self->ret));
			}
			self->ret = Dd_CSIO_Set_Send_Data(ch, self->gBuf16, self->gSendSize);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. ret=0x%x\n", self->ret));
			}
			break;

		case 4:
			self->calTbl.in_freq = 100000;
			self->calTbl.cal_freq = 0;
			self->ret = Dd_CSIO_Calculate(&self->calTbl);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. ret=0x%x\n", self->ret));
			}

			// Transmit mode              :SPI II
			self->csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_L;
			// Baudrate
			self->csioCtrl.baudrate = self->calTbl.cal_freq;
			// Serial output              :Output
			self->csioCtrl.sop = 0;
			// Bit direction              :LSB First
			self->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_LSB_FIRST;
			// Data length                :8 bit
			self->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
			// Type                       :Master/Slave
			self->csioCtrl.type = self->gType[ch];

			// FIFO selection             :Send=FIFO2,Receive=FIFO1
			self->csioCtrl.fifo_ctrl->fsel = 1;
			// FIFO Data-lost check       :Disable
			self->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			self->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Enable
			self->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO 1 enable              :Disable
			self->csioCtrl.fifo_ctrl->fe1 = 0;
			// FIFO receive data size     :0 byte
			self->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			self->csioCtrl.pcallback = ct_dd_csio_send_callback;
			self->gAsync = 1;

			self->gSendSize = 3;

			self->ret = Dd_CSIO_Open(ch, self->tmout);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. ret=0x%x\n", self->ret));
			}
			self->ret = Dd_CSIO_Ctrl(ch, &self->csioCtrl);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. ret=0x%x\n", self->ret));
			}
			self->ret = Dd_CSIO_Set_Send_Data(ch, self->gBuf8, self->gSendSize);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. ret=0x%x\n", self->ret));
			}
			break;
		// PROCESS1 + interrupt enable
		case 5:
			self->calTbl.in_freq = 100000;
			self->calTbl.cal_freq = 0;
			self->ret = Dd_CSIO_Calculate(&self->calTbl);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. ret=0x%x\n", self->ret));
			}

			// Transmit mode              :Nomal I
			self->csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_H;
			// Baudrate
			self->csioCtrl.baudrate = self->calTbl.cal_freq;
			// Serial output              :Output
			self->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			self->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :8 bit
			self->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
			// Type                       :Master/Slave
			self->csioCtrl.type = self->gType[ch];

			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			self->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			self->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			self->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Disable
			self->csioCtrl.fifo_ctrl->fe2 = 0;
			// FIFO 1 enable              :Disable
			self->csioCtrl.fifo_ctrl->fe1 = 0;
			// FIFO receive data size     :0 byte
			self->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			self->csioCtrl.pcallback = ct_dd_csio_send_callback;
			self->gAsync = 1;

			self->gSendSize = 3;

			self->ret = Dd_CSIO_Open(ch, self->tmout);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. ret=0x%x\n", self->ret));
			}
			self->ret = Dd_CSIO_Ctrl(ch, &self->csioCtrl);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. ret=0x%x\n", self->ret));
			}
			self->ret = Dd_CSIO_Set_Send_Data(ch, self->gBuf8, self->gSendSize);
			if (self->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. ret=0x%x\n", self->ret));
			}
			break;
	}
	return self->ret;
}

CtDdCsio* ct_dd_csio_new(void) 
{
    CtDdCsio *self = k_object_new_with_private(CT_TYPE_DD_CSIO, sizeof(CtDdCsioPrivate));
    return self;
}
