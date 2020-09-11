1、im_pro_interrupt.c共有4717行，拆分成了6个类，
分别为interruptsen     interruptfactor    interruptcallback    interruptctrl     interruptclear1     interruptclear2      和一个公有.h文件interruptdefine.h

2、共有方法改动：ps：1：后面加后缀未加形参的为，函数名作参数，其余未标注均添加。
                                    2：此文件无对应的.h文件，函数声明等是从im_pro.h拆过来的。
                                    3：部分只用于原 im_pro_interrupt.c 文件的结构体，枚举，宏定义等(既目前只用于此6个类的)，各自归置，其余既用于
                                          im_pro_interrupt.c的，又用于其他文件的，未动，通过文件包含形式使用。



类1     interruptsen：(形参 InterruptSen*self  ;   interrupt_sen_new())

1、Im_PRO_SEN_Set_VD_Int_Handler   改成了      interrupt_sen_set_vd_int_handler;

2、Im_PRO_SEN_VD_Int_Handler        改成了       interrupt_sen_vd_int_handler           没加形参;

3、Im_PRO_SEN_Set_SG_VD_Int_Handler      改成了     interrupt_sen_set_sg_vd_int_handler   ;

4、Im_PRO_SEN_Set_Gyro_Int_Handler       改成了         interrupt_sen_set_gyro_int_handler     ；

5、Im_PRO_SLVS_Set_Common_Int_Handler     改成了        interrupt_sen_slvs_set_common_int_handler

6、Im_PRO_CMIPI_Set_Int_Handler      改成了       interrupt_sen_cmipi_set_int_handler   ;

7、Im_PRO_SLVS_Set_Int_Handler     改成了            interrupt_sen_slvs_set_int_handler       ;

8、Im_PRO_SEN_Sensor_If_Int_Handler_0     改成了   interrupt_sen_sensor_if_int_handler_0   没加形参；

9、     改成了     interrupt_sen_sensor_if_int_handler_1    没加形参;

10、Im_PRO_SEN_Sensor_If_Int_Handler_2       改成了    interrupt_sen_sensor_if_int_handler_2     没加形参；

11、Im_PRO_SEN_Sensor_If_Int_Handler_3       改成了     interrupt_sen_sensor_if_int_handler_3    没加形参 ；

12、Im_PRO_LVDS_Set_Int_Handler         改成了      interrupt_sen_lvds_set_int_handler         ;

13、Im_PRO_DMIPI_Set_Int_Handler        改成了        interrupt_sen_dmipi_set_int_handler   ;



类2     interruptfactor：(形参 InterruptFactor*self  ;   interrupt_factor_new())

1、私变公

2、私变公

3、私变公

4、私变公

5、Im_PRO_PRch_Set_Int_Handler    改成了    interrupt_factor_prch_set_int_handler

6、Im_PRO_PWch_Set_Int_Handler   改成了    interrupt_factor_pwch_set_int_handler

7、Im_PRO_B2BTOP_Pipe1_Int_Handler    改成了   interrupt_factor_b2btop_pipe1_int_handler    没加形参

8、Im_PRO_B2BTOP_Pipe2_Int_Handler    改成了   interrupt_factor_b2btop_pipe2_int_handler    没加形参

9、Im_PRO_PASTOP_Int_Handler     改成了    interrupt_factor_pastop_int_handler    没加形参

10、Im_PRO_SENTOP_Set_VHD_Delay   改成了   interrupt_factor_sentop_set_vhd_delay

11、Im_PRO_SENTOP_Set_Gyro_Int_Delay    改成了   interrupt_factor_sentop_set_gyro_int_delay

12、Im_PRO_SROTOP_Set_VHD_Delay      改成了    interrupt_factor_srotop_set_vhd_delay

13、Im_PRO_STATTOP_Interrupt_Ctrl    改成了     interrupt_factor_stattop_interrupt_ctrl

14、Im_PRO_B2BTOP_Set_VHD_Delay   改成了    interrupt_factor_b2btop_set_vhd_delay

15、Im_PRO_PASTOP_Set_VHD_Delay    改成了   interrupt_factor_pastop_set_vhd_delay

16、Im_PRO_SEN_HD_Int_Handler         改成了          interrupt_factor_hd_int_handler     没加形参；

17、Im_PRO_SEN_Set_HD_Int_Handler           改成了        interrupt_factor_set_hd_int_handler       ；

18、Im_PRO_SEN_Set_SG_HD_Int_Handler      改成了        interrupt_factor_set_sg_hd_int_handler ;



类3     interruptctrl：(形参 InterruptCtrl*self  ;   interrupt_ctrl_new())

1、Im_PRO_SEN_Int_Handler    改成了    interrupt_ctrl_sen_int_handler           没加形参

2、Im_PRO_LDIV_Set_Int_Handler   改成了   interrupt_ctrl_ldiv_set_int_handler

3、Im_PRO_OBD_Set_Int_Handler    改成了    interrupt_ctrl_obd_set_int_handler

4、Im_PRO_OBT_Set_Int_Handler    改成了    interrupt_ctrl_obt_set_int_handler

5、Im_PRO_SROTOP_Pipe_Set_VD_Int_Handler    改成了   interrupt_ctrl_srotop_pipe_set_vd_int_handler

6、Im_PRO_SROTOP_Pipe1_VD_Int_Handler   改成了   interrupt_ctrl_srotop_pipe1_vd_int_handler           没加形参

7、Im_PRO_SROTOP_Pipe2_VD_Int_Handler    改成了    interrupt_ctrl_srotop_pipe2_vd_int_handler           没加形参

8、Im_PRO_SROTOP_Pipe_Set_HD_Int_Handler   改成了    interrupt_ctrl_srotop_pipe_set_hd_int_handler

9、Im_PRO_SROTOP_Pipe1_HD_Int_Handler    改成了    interrupt_ctrl_srotop_pipe1_hd_int_handler           没加形参

10、Im_PRO_SROTOP_Pipe2_HD_Int_Handler   改成了    interrupt_ctrl_srotop_pipe2_hd_int_handler           没加形参

11、Im_PRO_B2BTOP_Pipe_Set_VD_Int_Handler    改成了    interrupt_ctrl_b2btop_pipe_set_vd_int_handler

12、Im_PRO_B2BTOP_Pipe1_VD_Int_Handler    改成了     interrupt_ctrl_b2btop_pipe1_vd_int_handler           没加形参

13、Im_PRO_B2BTOP_Pipe2_VD_Int_Handler    改成了     interrupt_ctrl_b2btop_pipe2_vd_int_handler           没加形参

14、Im_PRO_B2BTOP_Pipe_Set_HD_Int_Handler    改成了    interrupt_ctrl_b2btop_pipe_set_hd_int_handler

15、Im_PRO_B2BTOP_Pipe1_HD_Int_Handler     改成了      interrupt_ctrl_b2btop_pipe1_hd_int_handler           没加形参

16、Im_PRO_B2BTOP_Pipe2_HD_Int_Handler     改成了      interrupt_ctrl_b2btop_pipe2_hd_int_handler           没加形参



类4     interruptclear2：(形参 InterruptClear2*self  ;   interrupt_clear2_new())

1、Im_PRO_CMIPI_Set_Interrupt    改成了     interrupt_clear2_cmipi_set_interrupt

2、Im_PRO_MONI_Set_Interrupt    改成了    interrupt_clear2_moni_set_interrupt

3、Im_PRO_LDIV_Set_Interrupt    改成了     interrupt_clear2_ldiv_set_interrupt

4、Im_PRO_OBT_Set_Interrupt    改成了     interrupt_clear2_obt_set_interrupt

5、Im_PRO_OBD_Set_Interrupt     改成了    interrupt_clear2_obd_set_interrupt

6、Im_PRO_SROTOP_Interrupt_Ctrl    改成了    interrupt_clear2_srotop_interrupt_ctrl

7、Im_PRO_SDC_Set_Interrupt    改成了    interrupt_clear2_sdc_set_interrupt

8、Im_PRO_B2BTOP_Interrupt_Ctrl    改成了     interrupt_clear2_b2btop_interrupt_ctrl

9、Im_PRO_AEAWB_Set_Interrupt   改成了     interrupt_clear2_aeawb_set_interrupt

10、Im_PRO_AF_Set_Interrupt    改成了     interrupt_clear2_af_set_interrupt

11、Im_PRO_HIST_Set_Interrupt    改成了   interrupt_clear2_hist_set_interrupt

12、Im_PRO_PASTOP_Interrupt_Ctrl    改成了     interrupt_clear2_pastop_interrupt_ctrl

13、Im_PRO_PWch_Set_Interrupt    改成了           interrupt_clear2_pwch_set_interrupt

14、Im_PRO_PRch_Set_Interrupt    改成了     interrupt_clear2_prch_set_interrupt



类5     interruptclear1：(形参 InterruptClear1*self  ;   interrupt_clear1_new())

1、Im_PRO_SENTOP_Interrupt_Ctrl    改成了     interrupt_clear1_sentop_interrupt_ctrl

2、Im_PRO_SENTOP_SG_Interrupt_Ctrl   改成了    interrupt_clear1_sentop_sg_interrupt_ctrl

3、Im_PRO_SENTOP_Gyro_Interrupt_Ctrl    改成了     interrupt_clear1_sentop_gyro_interrupt_ctrl

4、Im_PRO_SLVS_Set_Common_Interrupt    改成了      interrupt_clear1_slvs_set_common_interrupt

5、Im_PRO_SLVS_Set_Interrupt    改成了     interrupt_clear1_slvs_set_interrupt

6、Im_PRO_LVDS_Set_Interrupt    改成了     interrupt_clear1_lvds_set_interrupt

7、Im_PRO_DMIPI_Set_Interrupt     改成了    interrupt_clear1_dmipi_set_interrupt



类6     interruptcallback：(形参 InterruptCallback*self  ;   interrupt_callback_new())

1、new func   处理gim_pro_inttbl_moni_int和gIM_PRO_MONI_CallBack_Func并平衡代码。

2、Im_PRO_STAT_Int_Handler     改成了        interrupt_callback_stat_int_handler        没加形参

3、Im_PRO_AEAWB_Set_Int_Handler    改成了         interrupt_callback_aeawb_set_int_handler

4、Im_PRO_AF_Set_Int_Handler    改成了      interrupt_callback_af_set_int_handler

5、Im_PRO_HIST_Set_Int_Handler    改成了     interrupt_callback_hist_set_int_handler

6、Im_PRO_PASTOP_Set_VD_Int_Handler     改成了     interrupt_callback_pastop_set_vd_int_handler

7、Im_PRO_PASTOP_VD_Int_Handler         改成了       interrupt_callback_pastop_vd_int_handler      没加形参

8、Im_PRO_PASTOP_Set_HD_Int_Handler    改成了     interrupt_callback_pastop_set_hd_int_handler

9、Im_PRO_PASTOP_HD_Int_Handler     改成了     interrupt_callback_pastop_hd_int_handler      没加形参

10、Im_PRO_SDC_Set_Int_Handler    改成了      interrupt_callback_sdc_set_int_handler

11、Im_PRO_MONI_Set_Int_Handler     改成了     interrupt_callback_moni_set_int_handler

12、Im_PRO_SROTOP_Pipe1_Int_Handler    改成了    interrupt_callback_srotop_pipe1_int_handler      没加形参

13、Im_PRO_SROTOP_Pipe2_Int_Handler    改成了    interrupt_callback_srotop_pipe2_int_handler      没加形参



从im_pro.h拆过来的，只用于此6个类的结构体，枚举，宏定义等记录如下：


类1：interruptsen
(没找到单单只在此6个类里面用的)


公有头文件 interruptdefine.h 中(  从im_pro_common.h  里拆出来的)

typedef struct {
	T_CALLBACK_LONG				p_callback;
	ULONG						user_param;
} T_IM_PRO_CALLBACK_INFO;

改成了：
typedef struct {
	T_CALLBACK_LONG				pCallback;
	ULONG						userParam;
} TimproCallbackInfo;



