/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassk
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2yclassk.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2yClassk, ct_im_r2y_classk)
#define CT_IM_R2Y_CLASSK_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yClasskPrivate, CT_TYPE_IM_R2Y_CLASSK))


struct _CtImR2yClasskPrivate
{

};


static void ct_im_r2y_classk_constructor(CtImR2yClassk *self)
{
	CtImR2yClasskPrivate *priv = CT_IM_R2Y_CLASSK_GET_PRIVATE(self);
}

static void ct_im_r2y_classk_destructor(CtImR2yClassk *self)
{
	CtImR2yClasskPrivate *priv = CT_IM_R2Y_CLASSK_GET_PRIVATE(self);
}

TImR2yCtrlMultiAxis r2yCtrlMultiAxisTemp1[1] = {

		[0]={// max
				.cycCoeff = {
					0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
				},
				.boundary = {
					0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF,
				},
				.areaIndex = {
					{ 0xB, 0xB, 0xB, 0xB, 0xB, },
					{ 0xB, 0xB, 0xB, 0xB, 0xB, },
					{ 0xB, 0xB, 0xB, 0xB, 0xB, },
					{ 0xB, 0xB, 0xB, 0xB, 0xB, },
				},
				.areaAK = {
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
				},
				.areaBK = {
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
				},
				.areaCK = {
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
				},
				.areaDK = {
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
				},
				.areaEK = {
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
				},
				.areaFK = {
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
				},
				.areaGK = {
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
				},
				.areaHK = {
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
				},
				.areaIK = {
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
				},
				.areaJK = {
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
				},
				.areaKK = {
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
				},
				.areaLK = {
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
					{
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
						{ 0x7FF, 0x7FF, 0x7FF, },
					},
				},
				.areaAL = {
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
				},
				.areaBL = {
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
				},
				.areaCL = {
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
				},
				.areaDL = {
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
				},
				.areaEL = {
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
				},
				.areaFL = {
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
				},
				.areaGL = {
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
				},
				.areaHL = {
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
				},
				.areaIL = {
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
				},
				.areaJL = {
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
				},
				.areaKL = {
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
				},
				.areaLL = {
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
					{
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
						{ 0x1FF, 0x1FF, },
					},
				},
				.cycAlphaBlend = 0x20,
				.cycBlendGain = {
					0xFFF, 0xFFF, 0xFFF, 0xFFF,
				},
				.cycBlendBorder = {
					0xFFF, 0xFFF, 0xFFF, 0xFFF,
				},
				.cbaAlphaBlend = 0x20,
				.cbaBlendOffset = {
					0x7FF, 0x7FF, 0x7FF, 0x7FF,
				},
				.cbaBlendGain = {
					0xFF, 0xFF, 0xFF, 0xFF,
				},
				.cbaBlendBorder = {
					0xFFF, 0xFFF, 0xFFF,
				},
		},
};

CtImR2yClassk* ct_im_r2y_classk_new(void)
{
	CtImR2yClassk* self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSK, sizeof(CtImR2yClasskPrivate));

	return self;
}

CtImR2yClassk* ct_im_r2y_classk_get(void)
{
	static CtImR2yClassk* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSK, sizeof(CtImR2yClasskPrivate));
	}

	return self;
}
