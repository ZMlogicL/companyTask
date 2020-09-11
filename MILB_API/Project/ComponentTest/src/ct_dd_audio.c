/**
 * @file		ct_dd_audio.c
 * @brief		ct code for dd_audio.c.
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#include "audio_if.h"
#include "dd_audio.h"
#include "dd_hdmac0.h"
#include "dd_top.h"
#include "dd_cache.h"
#include "dd_pdm.h"
#include "dd_gic.h"
#include "peripheral.h"
#include <string.h>
#include <stdlib.h>
#include "ctddaudio.h"
#include "ctddaudioint.h"
#include "ctddaudioctrl.h"
#include "ctddaudioctrl1.h"
#include "ctddaudioctrl2.h"
#include "ctddaudioctrl3.h"
#include "ctddaudioctrl4.h"
#include "ctddaudioctrl5.h"
#include "ctddaudioctrl6.h"
#include "ctddaudioctrl7.h"
#include "ctddaudioctrl8.h"
#include "ctddaudioctrl9.h"
#include "ctddaudioctrl10.h"
#include "ctddaudioget.h"
#include "ctddaudiostart.h"
#include "ctddaudiostop.h"
#include "ctddaudioset.h"
#include "ctddaudioset1.h"
#include "ctddaudioset2.h"
#include "ctddaudioset3.h"
#include "ctddaudiothree.h"
#include "ctddaudiothree1.h"
#include "ctddaudiothree2.h"
#include "ctddaudiothree3.h"
#include "ctddaudiothree4.h"
#include "ctddaudiothree5.h"
#include "ctddaudiothree6.h"
#include "ctddaudiothree7.h"
#include "ctddaudiothree8.h"
#include "ctddaudiothree9.h"
#include "ctddaudiothree10.h"
#include "ctddaudiothree11.h"
#include "ctddaudiothree12.h"
#include "ctddaudiothree13.h"
#include "ctddaudiothree14.h"
#include "ctddaudiothree15.h"
#include "ctddaudiothree16.h"
#include "ctddaudiofifo.h"
#include "ctddaudiofifo1.h"
#include "ctddaudiofifo2.h"
#include "ctddaudiofifo3.h"

/**
 * @brief		Command processing of dd_audio_if.h
 * @param[in]	INT32 argc
 * @param[in]	CHAR** argv
 * @return		None
 * @note		Command processing of MBch.
 * @attention	None
 */
VOID ct_dd_audio_if_main(int argc, char** argv)
{
//	ct_dd_audio_set_gpio();
	
	Dd_CACHE_L1_Clean_Flush_Dcache_All();
	Dd_CACHE_L2_Clean_Flush_Dcache_All();
	
	if(atoi(argv[1]) == 1) {
		switch (atoi(argv[2])) {
			case 1:
				ct_dd_audio_input_open_test1(0);
				break;
			case 2:
				ct_dd_audio_input_open_test2(0);
				break;
			case 3:
				ct_dd_audio_input_open_test3(0);
				break;
			case 4:
				ct_dd_audio_input_open_test1(1);
				break;
			case 5:
				ct_dd_audio_input_open_test2(1);
				break;
			case 6:
				ct_dd_audio_input_open_test3(1);
				break;
			case 7:
				ct_dd_audio_input_open_test1(2);
				break;
			case 8:
				ct_dd_audio_input_open_test2(2);
				break;
			case 9:
				ct_dd_audio_input_open_test3(2);
				break;
			case 10:
				ct_dd_audio_input_open_test1(4);
				break;
			case 11:
				ct_dd_audio_input_open_test2(4);
				break;
			case 12:
				ct_dd_audio_input_open_test3(4);
				break;
			case 13:
				ct_dd_audio_input_open_test1(5);
				break;
			case 14:
				ct_dd_audio_input_open_test2(5);
				break;
			case 15:
				ct_dd_audio_input_open_test3(5);
				break;
			case 16:
				ct_dd_audio_output_open_test1(0);
				break;
			case 17:
				ct_dd_audio_output_open_test2(0);
				break;
			case 18:
				ct_dd_audio_output_open_test3(0);
				break;
			case 19:
				ct_dd_audio_output_open_test1(1);
				break;
			case 20:
				ct_dd_audio_output_open_test2(1);
				break;
			case 21:
				ct_dd_audio_output_open_test3(1);
				break;
			case 22:
				ct_dd_audio_output_open_test1(2);
				break;
			case 23:
				ct_dd_audio_output_open_test2(2);
				break;
			case 24:
				ct_dd_audio_output_open_test3(2);
				break;
			case 25:
				ct_dd_audio_output_open_test1(3);
				break;
			case 26:
				ct_dd_audio_output_open_test2(3);
				break;
			case 27:
				ct_dd_audio_output_open_test3(3);
				break;
			case 28:
				ct_dd_audio_input_close_test(0);
				break;
			case 29:
				ct_dd_audio_input_close_test(1);
				break;
			case 30:
				ct_dd_audio_input_close_test(2);
				break;
			case 31:
				ct_dd_audio_input_close_test(4);
				break;
			case 32:
				ct_dd_audio_input_close_test(5);
				break;
			case 33:
				ct_dd_audio_output_close_test(0);
				break;
			case 34:
				ct_dd_audio_output_close_test(1);
				break;
			case 35:
				ct_dd_audio_output_close_test(2);
				break;
			case 36:
				ct_dd_audio_output_close_test(3);
				break;
			case 37:
				ct_dd_audio_int_handler_test1(0);
				break;
			case 38:
				ct_dd_audio_int_handler_test2(0);
				break;
			case 39:
				ct_dd_audio_int_handler_test3(0);
				break;
			case 40:
				ct_dd_audio_int_handler_test4(0);
				break;
			case 41:
				ct_dd_audio_int_handler_test5(0);
				break;
			case 42:
				ct_dd_audio_int_handler_test6(0);
				break;
			case 43:
				ct_dd_audio_int_handler_test7(0);
				break;
			case 44:
				ct_dd_audio_int_handler_test8(0);
				break;
			case 45:
				ct_dd_audio_int_handler_test9(0);
				break;
			case 46:
				ct_dd_audio_int_handler_test10(0);
				break;
			case 47:
				ct_dd_audio_int_handler_test11(0);
				break;
			case 48:
				ct_dd_audio_int_handler_test12(0);
				break;
			case 49:
				ct_dd_audio_int_handler_test13(0);
				break;
			case 50:
				ct_dd_audio_int_handler_test14(0);
				break;
			case 51:
				ct_dd_audio_int_handler_test15(0);
				break;
			case 52:
				ct_dd_audio_int_handler_test16(0);
				break;
			case 53:
				ct_dd_audio_int_handler_test17(0);
				break;
			case 54:
				ct_dd_audio_int_handler_test18(0);
				break;
			case 55:
				ct_dd_audio_int_handler_test19(0);
				break;
			case 56:
				ct_dd_audio_int_handler_test1(1);
				break;
			case 57:
				ct_dd_audio_int_handler_test2(1);
				break;
			case 58:
				ct_dd_audio_int_handler_test3(1);
				break;
			case 59:
				ct_dd_audio_int_handler_test4(1);
				break;
			case 60:
				ct_dd_audio_int_handler_test5(1);
				break;
			case 61:
				ct_dd_audio_int_handler_test6(1);
				break;
			case 62:
				ct_dd_audio_int_handler_test7(1);
				break;
			case 63:
				ct_dd_audio_int_handler_test8(1);
				break;
			case 64:
				ct_dd_audio_int_handler_test9(1);
				break;
			case 65:
				ct_dd_audio_int_handler_test10(1);
				break;
			case 66:
				ct_dd_audio_int_handler_test11(1);
				break;
			case 67:
				ct_dd_audio_int_handler_test12(1);
				break;
			case 68:
				ct_dd_audio_int_handler_test13(1);
				break;
			case 69:
				ct_dd_audio_int_handler_test14(1);
				break;
			case 70:
				ct_dd_audio_int_handler_test15(1);
				break;
			case 71:
				ct_dd_audio_int_handler_test16(1);
				break;
			case 72:
				ct_dd_audio_int_handler_test17(1);
				break;
			case 73:
				ct_dd_audio_int_handler_test18(1);
				break;
			case 74:
				ct_dd_audio_int_handler_test19(1);
				break;
			case 75:
				ct_dd_audio_int_handler_test1(2);
				break;
			case 76:
				ct_dd_audio_int_handler_test2(2);
				break;
			case 77:
				ct_dd_audio_int_handler_test3(2);
				break;
			case 78:
				ct_dd_audio_int_handler_test4(2);
				break;
			case 79:
				ct_dd_audio_int_handler_test5(2);
				break;
			case 80:
				ct_dd_audio_int_handler_test6(2);
				break;
			case 81:
				ct_dd_audio_int_handler_test7(2);
				break;
			case 82:
				ct_dd_audio_int_handler_test8(2);
				break;
			case 83:
				ct_dd_audio_int_handler_test9(2);
				break;
			case 84:
				ct_dd_audio_int_handler_test10(2);
				break;
			case 85:
				ct_dd_audio_int_handler_test11(2);
				break;
			case 86:
				ct_dd_audio_int_handler_test12(2);
				break;
			case 87:
				ct_dd_audio_int_handler_test13(2);
				break;
			case 88:
				ct_dd_audio_int_handler_test14(2);
				break;
			case 89:
				ct_dd_audio_int_handler_test15(2);
				break;
			case 90:
				ct_dd_audio_int_handler_test16(2);
				break;
			case 91:
				ct_dd_audio_int_handler_test17(2);
				break;
			case 92:
				ct_dd_audio_int_handler_test18(2);
				break;
			case 93:
				ct_dd_audio_int_handler_test19(2);
				break;
			case 94:
				ct_dd_audio_int_handler_test1(3);
				break;
			case 95:
				ct_dd_audio_int_handler_test2(3);
				break;
			case 96:
				ct_dd_audio_int_handler_test3(3);
				break;
			case 97:
				ct_dd_audio_int_handler_test4(3);
				break;
			case 98:
				ct_dd_audio_int_handler_test5(3);
				break;
			case 99:
				ct_dd_audio_int_handler_test6(3);
				break;
			case 100:
				ct_dd_audio_int_handler_test7(3);
				break;
			case 101:
				ct_dd_audio_int_handler_test8(3);
				break;
			case 102:
				ct_dd_audio_int_handler_test9(3);
				break;
			case 103:
				ct_dd_audio_int_handler_test10(3);
				break;
			case 104:
				ct_dd_audio_int_handler_test11(3);
				break;
			case 105:
				ct_dd_audio_int_handler_test12(3);
				break;
			case 106:
				ct_dd_audio_int_handler_test13(3);
				break;
			case 107:
				ct_dd_audio_int_handler_test14(3);
				break;
			case 108:
				ct_dd_audio_int_handler_test15(3);
				break;
			case 109:
				ct_dd_audio_int_handler_test16(3);
				break;
			case 110:
				ct_dd_audio_int_handler_test17(3);
				break;
			case 111:
				ct_dd_audio_int_handler_test18(3);
				break;
			case 112:
				ct_dd_audio_int_handler_test19(3);
				break;
			case 113:
				ct_dd_audio_int_handler_test1(4);
				break;
			case 114:
				ct_dd_audio_int_handler_test2(4);
				break;
			case 115:
				ct_dd_audio_int_handler_test3(4);
				break;
			case 116:
				ct_dd_audio_int_handler_test4(4);
				break;
			case 117:
				ct_dd_audio_int_handler_test5(4);
				break;
			case 118:
				ct_dd_audio_int_handler_test6(4);
				break;
			case 119:
				ct_dd_audio_int_handler_test7(4);
				break;
			case 120:
				ct_dd_audio_int_handler_test8(4);
				break;
			case 121:
				ct_dd_audio_int_handler_test9(4);
				break;
			case 122:
				ct_dd_audio_int_handler_test10(4);
				break;
			case 123:
				ct_dd_audio_int_handler_test11(4);
				break;
			case 124:
				ct_dd_audio_int_handler_test12(4);
				break;
			case 125:
				ct_dd_audio_int_handler_test13(4);
				break;
			case 126:
				ct_dd_audio_int_handler_test14(4);
				break;
			case 127:
				ct_dd_audio_int_handler_test15(4);
				break;
			case 128:
				ct_dd_audio_int_handler_test16(4);
				break;
			case 129:
				ct_dd_audio_int_handler_test17(4);
				break;
			case 130:
				ct_dd_audio_int_handler_test18(4);
				break;
			case 131:
				ct_dd_audio_int_handler_test19(4);
				break;
			case 132:
				ct_dd_audio_int_handler_test1(5);
				break;
			case 133:
				ct_dd_audio_int_handler_test2(5);
				break;
			case 134:
				ct_dd_audio_int_handler_test3(5);
				break;
			case 135:
				ct_dd_audio_int_handler_test4(5);
				break;
			case 136:
				ct_dd_audio_int_handler_test5(5);
				break;
			case 137:
				ct_dd_audio_int_handler_test6(5);
				break;
			case 138:
				ct_dd_audio_int_handler_test7(5);
				break;
			case 139:
				ct_dd_audio_int_handler_test8(5);
				break;
			case 140:
				ct_dd_audio_int_handler_test9(5);
				break;
			case 141:
				ct_dd_audio_int_handler_test10(5);
				break;
			case 142:
				ct_dd_audio_int_handler_test11(5);
				break;
			case 143:
				ct_dd_audio_int_handler_test12(5);
				break;
			case 144:
				ct_dd_audio_int_handler_test13(5);
				break;
			case 145:
				ct_dd_audio_int_handler_test14(5);
				break;
			case 146:
				ct_dd_audio_int_handler_test15(5);
				break;
			case 147:
				ct_dd_audio_int_handler_test16(5);
				break;
			case 148:
				ct_dd_audio_int_handler_test17(5);
				break;
			case 149:
				ct_dd_audio_int_handler_test18(5);
				break;
			case 150:
				ct_dd_audio_int_handler_test19(5);
				break;
			case 151:
				ct_dd_audio_init_test();
				break;
			case 152:
				ct_dd_audio_reset_test(0);
				break;
			case 153:
				ct_dd_audio_reset_test(1);
				break;
			case 154:
				ct_dd_audio_reset_test(2);
				break;
			case 155:
				ct_dd_audio_reset_test(3);
				break;
			case 156:
				ct_dd_audio_reset_test(4);
				break;
			case 157:
				ct_dd_audio_reset_test(5);
				break;
			case 158:
				ct_dd_audio_ctrl_common_test1(0);
				break;
			case 159:
				ct_dd_audio_ctrl_common_test2(0);
				break;
			case 160:
				ct_dd_audio_ctrl_common_test3(0);
				break;
			case 161:
				ct_dd_audio_ctrl_common_test4(0);
				break;
			case 162:
				ct_dd_audio_ctrl_common_test5(0);
				break;
			case 163:
				ct_dd_audio_ctrl_common_test1(1);
				break;
			case 164:
				ct_dd_audio_ctrl_common_test2(1);
				break;
			case 165:
				ct_dd_audio_ctrl_common_test3(1);
				break;
			case 166:
				ct_dd_audio_ctrl_common_test4(1);
				break;
			case 167:
				ct_dd_audio_ctrl_common_test5(1);
				break;
			case 168:
				ct_dd_audio_ctrl_common_test1(2);
				break;
			case 169:
				ct_dd_audio_ctrl_common_test2(2);
				break;
			case 170:
				ct_dd_audio_ctrl_common_test3(2);
				break;
			case 171:
				ct_dd_audio_ctrl_common_test4(2);
				break;
			case 172:
				ct_dd_audio_ctrl_common_test5(2);
				break;
			case 173:
				ct_dd_audio_ctrl_common_test1(3);
				break;
			case 174:
				ct_dd_audio_ctrl_common_test2(3);
				break;
			case 175:
				ct_dd_audio_ctrl_common_test3(3);
				break;
			case 176:
				ct_dd_audio_ctrl_common_test4(3);
				break;
			case 177:
				ct_dd_audio_ctrl_common_test5(3);
				break;
			case 178:
				ct_dd_audio_ctrl_common_test1(4);
				break;
			case 179:
				ct_dd_audio_ctrl_common_test2(4);
				break;
			case 180:
				ct_dd_audio_ctrl_common_test3(4);
				break;
			case 181:
				ct_dd_audio_ctrl_common_test4(4);
				break;
			case 182:
				ct_dd_audio_ctrl_common_test5(4);
				break;
			case 183:
				ct_dd_audio_ctrl_common_test1(5);
				break;
			case 184:
				ct_dd_audio_ctrl_common_test2(5);
				break;
			case 185:
				ct_dd_audio_ctrl_common_test3(5);
				break;
			case 186:
				ct_dd_audio_ctrl_common_test4(5);
				break;
			case 187:
				ct_dd_audio_ctrl_common_test5(5);
				break;
			case 188:
				ct_dd_audio_get_ctrl_common_test1(0);
				break;
			case 189:
				ct_dd_audio_get_ctrl_common_test1(1);
				break;
			case 190:
				ct_dd_audio_get_ctrl_common_test1(2);
				break;
			case 191:
				ct_dd_audio_get_ctrl_common_test1(3);
				break;
			case 192:
				ct_dd_audio_get_ctrl_common_test1(4);
				break;
			case 193:
				ct_dd_audio_get_ctrl_common_test1(5);
				break;
			case 194:
				ct_dd_audio_ctrl_input_test1(0);
				break;
			case 195:
				ct_dd_audio_ctrl_input_test2(0);
				break;
			case 196:
				ct_dd_audio_ctrl_input_test3(0);
				break;
			case 197:
				ct_dd_audio_ctrl_input_test4(0);
				break;
			case 198:
				ct_dd_audio_ctrl_input_test5(0);
				break;
			case 199:
				ct_dd_audio_ctrl_input_test6(0);
				break;
			case 200:
				ct_dd_audio_ctrl_input_test7(0);
				break;
			case 201:
				ct_dd_audio_ctrl_input_test8(0);
				break;
			case 202:
				ct_dd_audio_ctrl_input_test9(0);
				break;
			case 203:
				ct_dd_audio_ctrl_input_test10(0);
				break;
			case 204:
				ct_dd_audio_ctrl_input_test11(0);
				break;
			case 205:
				ct_dd_audio_ctrl_input_test12(0);
				break;
			case 206:
				ct_dd_audio_ctrl_input_test13(0);
				break;
			case 207:
				ct_dd_audio_ctrl_input_test14(0);
				break;
			case 208:
				ct_dd_audio_ctrl_input_test1(1);
				break;
			case 209:
				ct_dd_audio_ctrl_input_test2(1);
				break;
			case 210:
				ct_dd_audio_ctrl_input_test3(1);
				break;
			case 211:
				ct_dd_audio_ctrl_input_test4(1);
				break;
			case 212:
				ct_dd_audio_ctrl_input_test5(1);
				break;
			case 213:
				ct_dd_audio_ctrl_input_test6(1);
				break;
			case 214:
				ct_dd_audio_ctrl_input_test7(1);
				break;
			case 215:
				ct_dd_audio_ctrl_input_test8(1);
				break;
			case 216:
				ct_dd_audio_ctrl_input_test9(1);
				break;
			case 217:
				ct_dd_audio_ctrl_input_test10(1);
				break;
			case 218:
				ct_dd_audio_ctrl_input_test11(1);
				break;
			case 219:
				ct_dd_audio_ctrl_input_test12(1);
				break;
			case 220:
				ct_dd_audio_ctrl_input_test13(1);
				break;
			case 221:
				ct_dd_audio_ctrl_input_test14(1);
				break;
			case 222:
				ct_dd_audio_ctrl_input_test1(2);
				break;
			case 223:
				ct_dd_audio_ctrl_input_test2(2);
				break;
			case 224:
				ct_dd_audio_ctrl_input_test3(2);
				break;
			case 225:
				ct_dd_audio_ctrl_input_test4(2);
				break;
			case 226:
				ct_dd_audio_ctrl_input_test5(2);
				break;
			case 227:
				ct_dd_audio_ctrl_input_test6(2);
				break;
			case 228:
				ct_dd_audio_ctrl_input_test7(2);
				break;
			case 229:
				ct_dd_audio_ctrl_input_test8(2);
				break;
			case 230:
				ct_dd_audio_ctrl_input_test9(2);
				break;
			case 231:
				ct_dd_audio_ctrl_input_test10(2);
				break;
			case 232:
				ct_dd_audio_ctrl_input_test11(2);
				break;
			case 233:
				ct_dd_audio_ctrl_input_test12(2);
				break;
			case 234:
				ct_dd_audio_ctrl_input_test13(2);
				break;
			case 235:
				ct_dd_audio_ctrl_input_test14(2);
				break;
			case 236:
				ct_dd_audio_ctrl_input_test1(4);
				break;
			case 237:
				ct_dd_audio_ctrl_input_test2(4);
				break;
			case 238:
				ct_dd_audio_ctrl_input_test3(4);
				break;
			case 239:
				ct_dd_audio_ctrl_input_test4(4);
				break;
			case 240:
				ct_dd_audio_ctrl_input_test5(4);
				break;
			case 241:
				ct_dd_audio_ctrl_input_test6(4);
				break;
			case 242:
				ct_dd_audio_ctrl_input_test7(4);
				break;
			case 243:
				ct_dd_audio_ctrl_input_test8(4);
				break;
			case 244:
				ct_dd_audio_ctrl_input_test9(4);
				break;
			case 245:
				ct_dd_audio_ctrl_input_test10(4);
				break;
			case 246:
				ct_dd_audio_ctrl_input_test11(4);
				break;
			case 247:
				ct_dd_audio_ctrl_input_test12(4);
				break;
			case 248:
				ct_dd_audio_ctrl_input_test13(4);
				break;
			case 249:
				ct_dd_audio_ctrl_input_test14(4);
				break;
			case 250:
				ct_dd_audio_ctrl_input_test1(5);
				break;
			case 251:
				ct_dd_audio_ctrl_input_test2(5);
				break;
			case 252:
				ct_dd_audio_ctrl_input_test3(5);
				break;
			case 253:
				ct_dd_audio_ctrl_input_test4(5);
				break;
			case 254:
				ct_dd_audio_ctrl_input_test5(5);
				break;
			case 255:
				ct_dd_audio_ctrl_input_test6(5);
				break;
			case 256:
				ct_dd_audio_ctrl_input_test7(5);
				break;
			case 257:
				ct_dd_audio_ctrl_input_test8(5);
				break;
			case 258:
				ct_dd_audio_ctrl_input_test9(5);
				break;
			case 259:
				ct_dd_audio_ctrl_input_test10(5);
				break;
			case 260:
				ct_dd_audio_ctrl_input_test11(5);
				break;
			case 261:
				ct_dd_audio_ctrl_input_test12(5);
				break;
			case 262:
				ct_dd_audio_ctrl_input_test13(5);
				break;
			case 263:
				ct_dd_audio_ctrl_input_test14(5);
				break;
			case 264:
				ct_dd_audio_get_ctrl_input_test1(0);
				break;
			case 265:
				ct_dd_audio_get_ctrl_input_test1(1);
				break;
			case 266:
				ct_dd_audio_get_ctrl_input_test1(2);
				break;
			case 267:
				ct_dd_audio_get_ctrl_input_test1(4);
				break;
			case 268:
				ct_dd_audio_get_ctrl_input_test1(5);
				break;
			case 269:
				ct_dd_audio_ctrl_output_test1(0);
				break;
			case 270:
				ct_dd_audio_ctrl_output_test2(0);
				break;
			case 271:
				ct_dd_audio_ctrl_output_test3(0);
				break;
			case 272:
				ct_dd_audio_ctrl_output_test4(0);
				break;
			case 273:
				ct_dd_audio_ctrl_output_test5(0);
				break;
			case 274:
				ct_dd_audio_ctrl_output_test6(0);
				break;
			case 275:
				ct_dd_audio_ctrl_output_test7(0);
				break;
			case 276:
				ct_dd_audio_ctrl_output_test8(0);
				break;
			case 277:
				ct_dd_audio_ctrl_output_test9(0);
				break;
			case 278:
				ct_dd_audio_ctrl_output_test10(0);
				break;
			case 279:
				ct_dd_audio_ctrl_output_test11(0);
				break;
			case 280:
				ct_dd_audio_ctrl_output_test12(0);
				break;
			case 281:
				ct_dd_audio_ctrl_output_test13(0);
				break;
			case 282:
				ct_dd_audio_ctrl_output_test14(0);
				break;
			case 283:
				ct_dd_audio_ctrl_output_test15(0);
				break;
			case 284:
				ct_dd_audio_ctrl_output_test16(0);
				break;
			case 285:
				ct_dd_audio_ctrl_output_test17(0);
				break;
			case 286:
				ct_dd_audio_ctrl_output_test18(0);
				break;
			case 287:
				ct_dd_audio_ctrl_output_test19(0);
				break;
			case 288:
				ct_dd_audio_ctrl_output_test20(0);
				break;
			case 289:
				ct_dd_audio_ctrl_output_test21(0);
				break;
			case 290:
				ct_dd_audio_ctrl_output_test22(0);
				break;
			case 291:
				ct_dd_audio_ctrl_output_test23(0);
				break;
			case 292:
				ct_dd_audio_ctrl_output_test24(0);
				break;
			case 293:
				ct_dd_audio_ctrl_output_test25(0);
				break;
			case 294:
				ct_dd_audio_ctrl_output_test26(0);
				break;
			case 295:
				ct_dd_audio_ctrl_output_test27(0);
				break;
			case 296:
				ct_dd_audio_ctrl_output_test28(0);
				break;
			case 297:
				ct_dd_audio_ctrl_output_test1(1);
				break;
			case 298:
				ct_dd_audio_ctrl_output_test2(1);
				break;
			case 299:
				ct_dd_audio_ctrl_output_test3(1);
				break;
			case 300:
				ct_dd_audio_ctrl_output_test4(1);
				break;
			case 301:
				ct_dd_audio_ctrl_output_test5(1);
				break;
			case 302:
				ct_dd_audio_ctrl_output_test6(1);
				break;
			case 303:
				ct_dd_audio_ctrl_output_test7(1);
				break;
			case 304:
				ct_dd_audio_ctrl_output_test8(1);
				break;
			case 305:
				ct_dd_audio_ctrl_output_test9(1);
				break;
			case 306:
				ct_dd_audio_ctrl_output_test10(1);
				break;
			case 307:
				ct_dd_audio_ctrl_output_test11(1);
				break;
			case 308:
				ct_dd_audio_ctrl_output_test12(1);
				break;
			case 309:
				ct_dd_audio_ctrl_output_test13(1);
				break;
			case 310:
				ct_dd_audio_ctrl_output_test14(1);
				break;
			case 311:
				ct_dd_audio_ctrl_output_test15(1);
				break;
			case 312:
				ct_dd_audio_ctrl_output_test16(1);
				break;
			case 313:
				ct_dd_audio_ctrl_output_test17(1);
				break;
			case 314:
				ct_dd_audio_ctrl_output_test18(1);
				break;
			case 315:
				ct_dd_audio_ctrl_output_test19(1);
				break;
			case 316:
				ct_dd_audio_ctrl_output_test20(1);
				break;
			case 317:
				ct_dd_audio_ctrl_output_test21(1);
				break;
			case 318:
				ct_dd_audio_ctrl_output_test22(1);
				break;
			case 319:
				ct_dd_audio_ctrl_output_test23(1);
				break;
			case 320:
				ct_dd_audio_ctrl_output_test24(1);
				break;
			case 321:
				ct_dd_audio_ctrl_output_test25(1);
				break;
			case 322:
				ct_dd_audio_ctrl_output_test26(1);
				break;
			case 323:
				ct_dd_audio_ctrl_output_test27(1);
				break;
			case 324:
				ct_dd_audio_ctrl_output_test28(1);
				break;
			case 325:
				ct_dd_audio_ctrl_output_test1(2);
				break;
			case 326:
				ct_dd_audio_ctrl_output_test2(2);
				break;
			case 327:
				ct_dd_audio_ctrl_output_test3(2);
				break;
			case 328:
				ct_dd_audio_ctrl_output_test4(2);
				break;
			case 329:
				ct_dd_audio_ctrl_output_test5(2);
				break;
			case 330:
				ct_dd_audio_ctrl_output_test6(2);
				break;
			case 331:
				ct_dd_audio_ctrl_output_test7(2);
				break;
			case 332:
				ct_dd_audio_ctrl_output_test8(2);
				break;
			case 333:
				ct_dd_audio_ctrl_output_test9(2);
				break;
			case 334:
				ct_dd_audio_ctrl_output_test10(2);
				break;
			case 335:
				ct_dd_audio_ctrl_output_test11(2);
				break;
			case 336:
				ct_dd_audio_ctrl_output_test12(2);
				break;
			case 337:
				ct_dd_audio_ctrl_output_test13(2);
				break;
			case 338:
				ct_dd_audio_ctrl_output_test14(2);
				break;
			case 339:
				ct_dd_audio_ctrl_output_test15(2);
				break;
			case 340:
				ct_dd_audio_ctrl_output_test16(2);
				break;
			case 341:
				ct_dd_audio_ctrl_output_test17(2);
				break;
			case 342:
				ct_dd_audio_ctrl_output_test18(2);
				break;
			case 343:
				ct_dd_audio_ctrl_output_test19(2);
				break;
			case 344:
				ct_dd_audio_ctrl_output_test20(2);
				break;
			case 345:
				ct_dd_audio_ctrl_output_test21(2);
				break;
			case 346:
				ct_dd_audio_ctrl_output_test22(2);
				break;
			case 347:
				ct_dd_audio_ctrl_output_test23(2);
				break;
			case 348:
				ct_dd_audio_ctrl_output_test24(2);
				break;
			case 349:
				ct_dd_audio_ctrl_output_test25(2);
				break;
			case 350:
				ct_dd_audio_ctrl_output_test26(2);
				break;
			case 351:
				ct_dd_audio_ctrl_output_test27(2);
				break;
			case 352:
				ct_dd_audio_ctrl_output_test28(2);
				break;
			case 353:
				ct_dd_audio_ctrl_output_test1(3);
				break;
			case 354:
				ct_dd_audio_ctrl_output_test2(3);
				break;
			case 355:
				ct_dd_audio_ctrl_output_test3(3);
				break;
			case 356:
				ct_dd_audio_ctrl_output_test4(3);
				break;
			case 357:
				ct_dd_audio_ctrl_output_test5(3);
				break;
			case 358:
				ct_dd_audio_ctrl_output_test6(3);
				break;
			case 359:
				ct_dd_audio_ctrl_output_test7(3);
				break;
			case 360:
				ct_dd_audio_ctrl_output_test8(3);
				break;
			case 361:
				ct_dd_audio_ctrl_output_test9(3);
				break;
			case 362:
				ct_dd_audio_ctrl_output_test10(3);
				break;
			case 363:
				ct_dd_audio_ctrl_output_test11(3);
				break;
			case 364:
				ct_dd_audio_ctrl_output_test12(3);
				break;
			case 365:
				ct_dd_audio_ctrl_output_test13(3);
				break;
			case 366:
				ct_dd_audio_ctrl_output_test14(3);
				break;
			case 367:
				ct_dd_audio_ctrl_output_test15(3);
				break;
			case 368:
				ct_dd_audio_ctrl_output_test16(3);
				break;
			case 369:
				ct_dd_audio_ctrl_output_test17(3);
				break;
			case 370:
				ct_dd_audio_ctrl_output_test18(3);
				break;
			case 371:
				ct_dd_audio_ctrl_output_test19(3);
				break;
			case 372:
				ct_dd_audio_ctrl_output_test20(3);
				break;
			case 373:
				ct_dd_audio_ctrl_output_test21(3);
				break;
			case 374:
				ct_dd_audio_ctrl_output_test22(3);
				break;
			case 375:
				ct_dd_audio_ctrl_output_test23(3);
				break;
			case 376:
				ct_dd_audio_ctrl_output_test24(3);
				break;
			case 377:
				ct_dd_audio_ctrl_output_test25(3);
				break;
			case 378:
				ct_dd_audio_ctrl_output_test26(3);
				break;
			case 379:
				ct_dd_audio_ctrl_output_test27(3);
				break;
			case 380:
				ct_dd_audio_ctrl_output_test28(3);
				break;
			case 381:
				ct_dd_audio_get_ctrl_output_test1(0);
				break;
			case 382:
				ct_dd_audio_get_ctrl_output_test1(1);
				break;
			case 383:
				ct_dd_audio_get_ctrl_output_test1(2);
				break;
			case 384:
				ct_dd_audio_get_ctrl_output_test1(3);
				break;
			case 385:
				ct_dd_audio_ctrl_i2scmmn_test1(0);
				break;
			case 386:
				ct_dd_audio_ctrl_i2scmmn_test2(0);
				break;
			case 387:
				ct_dd_audio_ctrl_i2scmmn_test3(0);
				break;
			case 388:
				ct_dd_audio_ctrl_i2scmmn_test4(0);
				break;
			case 389:
				ct_dd_audio_ctrl_i2scmmn_test5(0);
				break;
			case 390:
				ct_dd_audio_ctrl_i2scmmn_test6(0);
				break;
			case 391:
				ct_dd_audio_ctrl_i2scmmn_test7(0);
				break;
			case 392:
				ct_dd_audio_ctrl_i2scmmn_test8(0);
				break;
			case 393:
				ct_dd_audio_ctrl_i2scmmn_test9(0);
				break;
			case 394:
				ct_dd_audio_ctrl_i2scmmn_test10(0);
				break;
			case 395:
				ct_dd_audio_ctrl_i2scmmn_test11(0);
				break;
			case 396:
				ct_dd_audio_ctrl_i2scmmn_test12(0);
				break;
			case 397:
				ct_dd_audio_ctrl_i2scmmn_test13(0);
				break;
			case 398:
				ct_dd_audio_ctrl_i2scmmn_test14(0);
				break;
			case 399:
				ct_dd_audio_ctrl_i2scmmn_test15(0);
				break;
			case 400:
				ct_dd_audio_ctrl_i2scmmn_test16(0);
				break;
			case 401:
				ct_dd_audio_ctrl_i2scmmn_test17(0);
				break;
			case 402:
				ct_dd_audio_ctrl_i2scmmn_test18(0);
				break;
			case 403:
				ct_dd_audio_ctrl_i2scmmn_test19(0);
				break;
			case 404:
				ct_dd_audio_ctrl_i2scmmn_test20(0);
				break;
			case 405:
				ct_dd_audio_ctrl_i2scmmn_test21(0);
				break;
			case 406:
				ct_dd_audio_ctrl_i2scmmn_test22(0);
				break;
			case 407:
				ct_dd_audio_ctrl_i2scmmn_test23(0);
				break;
			case 408:
				ct_dd_audio_ctrl_i2scmmn_test24(0);
				break;
			case 409:
				ct_dd_audio_ctrl_i2scmmn_test25(0);
				break;
			case 410:
				ct_dd_audio_ctrl_i2scmmn_test26(0);
				break;
			case 411:
				ct_dd_audio_ctrl_i2scmmn_test27(0);
				break;
			case 412:
				ct_dd_audio_ctrl_i2scmmn_test28(0);
				break;
			case 413:
				ct_dd_audio_ctrl_i2scmmn_test29(0);
				break;
			case 414:
				ct_dd_audio_ctrl_i2scmmn_test30(0);
				break;
			case 415:
				ct_dd_audio_ctrl_i2scmmn_test31(0);
				break;
			case 416:
				ct_dd_audio_ctrl_i2scmmn_test32(0);
				break;
			case 417:
				ct_dd_audio_ctrl_i2scmmn_test33(0);
				break;
			case 418:
				ct_dd_audio_ctrl_i2scmmn_test34(0);
				break;
			case 419:
				ct_dd_audio_ctrl_i2scmmn_test35(0);
				break;
			case 420:
				ct_dd_audio_ctrl_i2scmmn_test25(1);
				break;
			case 421:
				ct_dd_audio_get_ctrl_i2scmmn_test1(2);
				break;
			case 422:
				ct_dd_audio_ctrl_i2scmmn_test2(2);
				break;
			case 423:
				ct_dd_audio_ctrl_i2scmmn_test3(2);
				break;
			case 424:
				ct_dd_audio_ctrl_i2scmmn_test4(2);
				break;
			case 425:
				ct_dd_audio_ctrl_i2scmmn_test5(2);
				break;
			case 426:
				ct_dd_audio_ctrl_i2scmmn_test6(2);
				break;
			case 427:
				ct_dd_audio_ctrl_i2scmmn_test7(2);
				break;
			case 428:
				ct_dd_audio_ctrl_i2scmmn_test8(2);
				break;
			case 429:
				ct_dd_audio_ctrl_i2scmmn_test9(2);
				break;
			case 430:
				ct_dd_audio_ctrl_i2scmmn_test10(2);
				break;
			case 431:
				ct_dd_audio_ctrl_i2scmmn_test11(2);
				break;
			case 432:
				ct_dd_audio_ctrl_i2scmmn_test12(2);
				break;
			case 433:
				ct_dd_audio_ctrl_i2scmmn_test13(2);
				break;
			case 434:
				ct_dd_audio_ctrl_i2scmmn_test14(2);
				break;
			case 435:
				ct_dd_audio_ctrl_i2scmmn_test15(2);
				break;
			case 436:
				ct_dd_audio_ctrl_i2scmmn_test16(2);
				break;
			case 437:
				ct_dd_audio_ctrl_i2scmmn_test17(2);
				break;
			case 438:
				ct_dd_audio_ctrl_i2scmmn_test18(2);
				break;
			case 439:
				ct_dd_audio_ctrl_i2scmmn_test19(2);
				break;
			case 440:
				ct_dd_audio_ctrl_i2scmmn_test20(2);
				break;
			case 441:
				ct_dd_audio_ctrl_i2scmmn_test21(2);
				break;
			case 442:
				ct_dd_audio_ctrl_i2scmmn_test22(2);
				break;
			case 443:
				ct_dd_audio_ctrl_i2scmmn_test23(2);
				break;
			case 444:
				ct_dd_audio_ctrl_i2scmmn_test24(2);
				break;
			case 445:
				ct_dd_audio_ctrl_i2scmmn_test25(2);
				break;
			case 446:
				ct_dd_audio_ctrl_i2scmmn_test26(2);
				break;
			case 447:
				ct_dd_audio_ctrl_i2scmmn_test27(2);
				break;
			case 448:
				ct_dd_audio_ctrl_i2scmmn_test28(2);
				break;
			case 449:
				ct_dd_audio_ctrl_i2scmmn_test29(2);
				break;
			case 450:
				ct_dd_audio_ctrl_i2scmmn_test30(2);
				break;
			case 451:
				ct_dd_audio_ctrl_i2scmmn_test31(2);
				break;
			case 452:
				ct_dd_audio_ctrl_i2scmmn_test32(2);
				break;
			case 453:
				ct_dd_audio_ctrl_i2scmmn_test33(2);
				break;
			case 454:
				ct_dd_audio_ctrl_i2scmmn_test34(2);
				break;
			case 455:
				ct_dd_audio_ctrl_i2scmmn_test35(2);
				break;
			case 456:
				ct_dd_audio_ctrl_i2scmmn_test1(3);
				break;
			case 457:
				ct_dd_audio_ctrl_i2scmmn_test2(3);
				break;
			case 458:
				ct_dd_audio_ctrl_i2scmmn_test3(3);
				break;
			case 459:
				ct_dd_audio_ctrl_i2scmmn_test4(3);
				break;
			case 460:
				ct_dd_audio_ctrl_i2scmmn_test5(3);
				break;
			case 461:
				ct_dd_audio_ctrl_i2scmmn_test6(3);
				break;
			case 462:
				ct_dd_audio_ctrl_i2scmmn_test7(3);
				break;
			case 463:
				ct_dd_audio_ctrl_i2scmmn_test8(3);
				break;
			case 464:
				ct_dd_audio_ctrl_i2scmmn_test9(3);
				break;
			case 465:
				ct_dd_audio_ctrl_i2scmmn_test10(3);
				break;
			case 466:
				ct_dd_audio_ctrl_i2scmmn_test11(3);
				break;
			case 467:
				ct_dd_audio_ctrl_i2scmmn_test12(3);
				break;
			case 468:
				ct_dd_audio_ctrl_i2scmmn_test13(3);
				break;
			case 469:
				ct_dd_audio_ctrl_i2scmmn_test14(3);
				break;
			case 470:
				ct_dd_audio_ctrl_i2scmmn_test15(3);
				break;
			case 471:
				ct_dd_audio_ctrl_i2scmmn_test16(3);
				break;
			case 472:
				ct_dd_audio_ctrl_i2scmmn_test17(3);
				break;
			case 473:
				ct_dd_audio_ctrl_i2scmmn_test18(3);
				break;
			case 474:
				ct_dd_audio_ctrl_i2scmmn_test19(3);
				break;
			case 475:
				ct_dd_audio_ctrl_i2scmmn_test20(3);
				break;
			case 476:
				ct_dd_audio_ctrl_i2scmmn_test21(3);
				break;
			case 477:
				ct_dd_audio_ctrl_i2scmmn_test22(3);
				break;
			case 478:
				ct_dd_audio_ctrl_i2scmmn_test23(3);
				break;
			case 479:
				ct_dd_audio_ctrl_i2scmmn_test24(3);
				break;
			case 480:
				ct_dd_audio_ctrl_i2scmmn_test25(3);
				break;
			case 481:
				ct_dd_audio_ctrl_i2scmmn_test26(3);
				break;
			case 482:
				ct_dd_audio_ctrl_i2scmmn_test28(3);
				break;
			case 483:
				ct_dd_audio_ctrl_i2scmmn_test30(3);
				break;
			case 484:
				ct_dd_audio_ctrl_i2scmmn_test31(3);
				break;
			case 485:
				ct_dd_audio_ctrl_i2scmmn_test33(3);
				break;
			case 486:
				ct_dd_audio_ctrl_i2scmmn_test35(3);
				break;
			case 487:
				ct_dd_audio_ctrl_i2scmmn_test36(4);
				break;
			case 488:
				ct_dd_audio_ctrl_i2scmmn_test37(4);
				break;
			case 489:
				ct_dd_audio_ctrl_i2scmmn_test3(4);
				break;
			case 490:
				ct_dd_audio_ctrl_i2scmmn_test4(4);
				break;
			case 491:
				ct_dd_audio_ctrl_i2scmmn_test5(4);
				break;
			case 492:
				ct_dd_audio_ctrl_i2scmmn_test7(4);
				break;
			case 493:
				ct_dd_audio_ctrl_i2scmmn_test8(4);
				break;
			case 494:
				ct_dd_audio_ctrl_i2scmmn_test9(4);
				break;
			case 495:
				ct_dd_audio_ctrl_i2scmmn_test10(4);
				break;
			case 496:
				ct_dd_audio_ctrl_i2scmmn_test11(4);
				break;
			case 497:
				ct_dd_audio_ctrl_i2scmmn_test12(4);
				break;
			case 498:
				ct_dd_audio_ctrl_i2scmmn_test13(4);
				break;
			case 499:
				ct_dd_audio_ctrl_i2scmmn_test14(4);
				break;
			case 500:
				ct_dd_audio_ctrl_i2scmmn_test15(4);
				break;
			case 501:
				ct_dd_audio_ctrl_i2scmmn_test16(4);
				break;
			case 502:
				ct_dd_audio_ctrl_i2scmmn_test17(4);
				break;
			case 503:
				ct_dd_audio_ctrl_i2scmmn_test18(4);
				break;
			case 504:
				ct_dd_audio_ctrl_i2scmmn_test19(4);
				break;
			case 505:
				ct_dd_audio_ctrl_i2scmmn_test20(4);
				break;
			case 506:
				ct_dd_audio_ctrl_i2scmmn_test21(4);
				break;
			case 507:
				ct_dd_audio_ctrl_i2scmmn_test22(4);
				break;
			case 508:
				ct_dd_audio_ctrl_i2scmmn_test23(4);
				break;
			case 509:
				ct_dd_audio_ctrl_i2scmmn_test24(4);
				break;
			case 510:
				ct_dd_audio_ctrl_i2scmmn_test25(4);
				break;
			case 511:
				ct_dd_audio_ctrl_i2scmmn_test26(4);
				break;
			case 512:
				ct_dd_audio_ctrl_i2scmmn_test27(4);
				break;
			case 513:
				ct_dd_audio_ctrl_i2scmmn_test30(4);
				break;
			case 514:
				ct_dd_audio_ctrl_i2scmmn_test31(4);
				break;
			case 515:
				ct_dd_audio_ctrl_i2scmmn_test32(4);
				break;
			case 516:
				ct_dd_audio_ctrl_i2scmmn_test35(4);
				break;
			case 517:
				ct_dd_audio_ctrl_i2scmmn_test36(5);
				break;
			case 518:
				ct_dd_audio_ctrl_i2scmmn_test37(5);
				break;
			case 519:
				ct_dd_audio_ctrl_i2scmmn_test3(5);
				break;
			case 520:
				ct_dd_audio_ctrl_i2scmmn_test4(5);
				break;
			case 521:
				ct_dd_audio_ctrl_i2scmmn_test5(5);
				break;
			case 522:
				ct_dd_audio_ctrl_i2scmmn_test7(5);
				break;
			case 523:
				ct_dd_audio_ctrl_i2scmmn_test8(5);
				break;
			case 524:
				ct_dd_audio_ctrl_i2scmmn_test9(5);
				break;
			case 525:
				ct_dd_audio_ctrl_i2scmmn_test10(5);
				break;
			case 526:
				ct_dd_audio_ctrl_i2scmmn_test11(5);
				break;
			case 527:
				ct_dd_audio_ctrl_i2scmmn_test12(5);
				break;
			case 528:
				ct_dd_audio_ctrl_i2scmmn_test13(5);
				break;
			case 529:
				ct_dd_audio_ctrl_i2scmmn_test14(5);
				break;
			case 530:
				ct_dd_audio_ctrl_i2scmmn_test15(5);
				break;
			case 531:
				ct_dd_audio_ctrl_i2scmmn_test16(5);
				break;
			case 532:
				ct_dd_audio_ctrl_i2scmmn_test17(5);
				break;
			case 533:
				ct_dd_audio_ctrl_i2scmmn_test18(5);
				break;
			case 534:
				ct_dd_audio_ctrl_i2scmmn_test19(5);
				break;
			case 535:
				ct_dd_audio_ctrl_i2scmmn_test20(5);
				break;
			case 536:
				ct_dd_audio_ctrl_i2scmmn_test21(5);
				break;
			case 537:
				ct_dd_audio_ctrl_i2scmmn_test22(5);
				break;
			case 538:
				ct_dd_audio_ctrl_i2scmmn_test23(5);
				break;
			case 539:
				ct_dd_audio_ctrl_i2scmmn_test24(5);
				break;
			case 540:
				ct_dd_audio_ctrl_i2scmmn_test25(5);
				break;
			case 541:
				ct_dd_audio_ctrl_i2scmmn_test26(5);
				break;
			case 542:
				ct_dd_audio_ctrl_i2scmmn_test27(5);
				break;
			case 543:
				ct_dd_audio_ctrl_i2scmmn_test30(5);
				break;
			case 544:
				ct_dd_audio_ctrl_i2scmmn_test31(5);
				break;
			case 545:
				ct_dd_audio_ctrl_i2scmmn_test32(5);
				break;
			case 546:
				ct_dd_audio_ctrl_i2scmmn_test35(5);
				break;
			case 547:
				ct_dd_audio_get_ctrl_i2scmmn_test1(0);
				break;
			case 548:
				ct_dd_audio_get_ctrl_i2scmmn_test1(1);
				break;
			case 549:
				ct_dd_audio_get_ctrl_i2scmmn_test1(2);
				break;
			case 550:
				ct_dd_audio_get_ctrl_i2scmmn_test1(3);
				break;
			case 551:
				ct_dd_audio_get_ctrl_i2scmmn_test1(4);
				break;
			case 552:
				ct_dd_audio_get_ctrl_i2scmmn_test1(5);
				break;
			case 553:
				ct_dd_audio_ctrl_i2sin_test1(0);
				break;
			case 554:
				ct_dd_audio_ctrl_i2sin_test2(0);
				break;
			case 555:
				ct_dd_audio_ctrl_i2sin_test3(0);
				break;
			case 556:
				ct_dd_audio_ctrl_i2sin_test4(0);
				break;
			case 557:
				ct_dd_audio_ctrl_i2sin_test5(0);
				break;
			case 558:
				ct_dd_audio_ctrl_i2sin_test6(0);
				break;
			case 559:
				ct_dd_audio_ctrl_i2sin_test7(0);
				break;
			case 560:
				ct_dd_audio_ctrl_i2sin_test8(0);
				break;
			case 561:
				ct_dd_audio_ctrl_i2sin_test9(0);
				break;
			case 562:
				ct_dd_audio_ctrl_i2sin_test10(0);
				break;
			case 563:
				ct_dd_audio_ctrl_i2sin_test1(1);
				break;
			case 564:
				ct_dd_audio_ctrl_i2sin_test2(1);
				break;
			case 565:
				ct_dd_audio_ctrl_i2sin_test3(1);
				break;
			case 566:
				ct_dd_audio_ctrl_i2sin_test4(1);
				break;
			case 567:
				ct_dd_audio_ctrl_i2sin_test5(1);
				break;
			case 568:
				ct_dd_audio_ctrl_i2sin_test6(1);
				break;
			case 569:
				ct_dd_audio_ctrl_i2sin_test7(1);
				break;
			case 570:
				ct_dd_audio_ctrl_i2sin_test8(1);
				break;
			case 571:
				ct_dd_audio_ctrl_i2sin_test9(1);
				break;
			case 572:
				ct_dd_audio_ctrl_i2sin_test10(1);
				break;
			case 573:
				ct_dd_audio_ctrl_i2sin_test1(2);
				break;
			case 574:
				ct_dd_audio_ctrl_i2sin_test2(2);
				break;
			case 575:
				ct_dd_audio_ctrl_i2sin_test3(2);
				break;
			case 576:
				ct_dd_audio_ctrl_i2sin_test4(2);
				break;
			case 577:
				ct_dd_audio_ctrl_i2sin_test5(2);
				break;
			case 578:
				ct_dd_audio_ctrl_i2sin_test6(2);
				break;
			case 579:
				ct_dd_audio_ctrl_i2sin_test7(2);
				break;
			case 580:
				ct_dd_audio_ctrl_i2sin_test8(2);
				break;
			case 581:
				ct_dd_audio_ctrl_i2sin_test9(2);
				break;
			case 582:
				ct_dd_audio_ctrl_i2sin_test10(2);
				break;
			case 583:
				ct_dd_audio_ctrl_i2sin_test1(4);
				break;
			case 584:
				ct_dd_audio_ctrl_i2sin_test2(4);
				break;
			case 585:
				ct_dd_audio_ctrl_i2sin_test3(4);
				break;
			case 586:
				ct_dd_audio_ctrl_i2sin_test4(4);
				break;
			case 587:
				ct_dd_audio_ctrl_i2sin_test5(4);
				break;
			case 588:
				ct_dd_audio_ctrl_i2sin_test6(4);
				break;
			case 589:
				ct_dd_audio_ctrl_i2sin_test7(4);
				break;
			case 590:
				ct_dd_audio_ctrl_i2sin_test8(4);
				break;
			case 591:
				ct_dd_audio_ctrl_i2sin_test9(4);
				break;
			case 592:
				ct_dd_audio_ctrl_i2sin_test10(4);
				break;
			case 593:
				ct_dd_audio_ctrl_i2sin_test1(5);
				break;
			case 594:
				ct_dd_audio_ctrl_i2sin_test2(5);
				break;
			case 595:
				ct_dd_audio_ctrl_i2sin_test3(5);
				break;
			case 596:
				ct_dd_audio_ctrl_i2sin_test4(5);
				break;
			case 597:
				ct_dd_audio_ctrl_i2sin_test5(5);
				break;
			case 598:
				ct_dd_audio_ctrl_i2sin_test6(5);
				break;
			case 599:
				ct_dd_audio_ctrl_i2sin_test7(5);
				break;
			case 600:
				ct_dd_audio_ctrl_i2sin_test8(5);
				break;
			case 601:
				ct_dd_audio_ctrl_i2sin_test9(5);
				break;
			case 602:
				ct_dd_audio_ctrl_i2sin_test10(5);
				break;
			case 603:
				ct_dd_audio_get_ctrl_i2sin_test1(0);
				break;
			case 604:
				ct_dd_audio_get_ctrl_i2sin_test1(1);
				break;
			case 605:
				ct_dd_audio_get_ctrl_i2sin_test1(2);
				break;
			case 606:
				ct_dd_audio_get_ctrl_i2sin_test1(4);
				break;
			case 607:
				ct_dd_audio_get_ctrl_i2sin_test1(5);
				break;
			case 608:
				ct_dd_audio_ctrl_i2sout_test1(0);
				break;
			case 609:
				ct_dd_audio_ctrl_i2sout_test2(0);
				break;
			case 610:
				ct_dd_audio_ctrl_i2sout_test3(0);
				break;
			case 611:
				ct_dd_audio_ctrl_i2sout_test4(0);
				break;
			case 612:
				ct_dd_audio_ctrl_i2sout_test5(0);
				break;
			case 613:
				ct_dd_audio_ctrl_i2sout_test6(0);
				break;
			case 614:
				ct_dd_audio_ctrl_i2sout_test7(0);
				break;
			case 615:
				ct_dd_audio_ctrl_i2sout_test8(0);
				break;
			case 616:
				ct_dd_audio_ctrl_i2sout_test9(0);
				break;
			case 617:
				ct_dd_audio_ctrl_i2sout_test10(0);
				break;
			case 618:
				ct_dd_audio_ctrl_i2sout_test11(0);
				break;
			case 619:
				ct_dd_audio_ctrl_i2sout_test12(0);
				break;
			case 620:
				ct_dd_audio_ctrl_i2sout_test13(0);
				break;
			case 621:
				ct_dd_audio_ctrl_i2sout_test14(0);
				break;
			case 622:
				ct_dd_audio_ctrl_i2sout_test15(0);
				break;
			case 623:
				ct_dd_audio_ctrl_i2sout_test16(0);
				break;
			case 624:
				ct_dd_audio_ctrl_i2sout_test17(0);
				break;
			case 625:
				ct_dd_audio_ctrl_i2sout_test18(0);
				break;
			case 626:
				ct_dd_audio_ctrl_i2sout_test19(0);
				break;
			case 627:
				ct_dd_audio_ctrl_i2sout_test20(0);
				break;
			case 628:
				ct_dd_audio_ctrl_i2sout_test21(0);
				break;
			case 629:
				ct_dd_audio_ctrl_i2sout_test22(0);
				break;
			case 630:
				ct_dd_audio_ctrl_i2sout_test23(0);
				break;
			case 631:
				ct_dd_audio_ctrl_i2sout_test24(0);
				break;
			case 632:
				ct_dd_audio_ctrl_i2sout_test25(0);
				break;
			case 633:
				ct_dd_audio_ctrl_i2sout_test26(0);
				break;
			case 634:
				ct_dd_audio_ctrl_i2sout_test27(0);
				break;
			case 635:
				ct_dd_audio_ctrl_i2sout_test28(0);
				break;
			case 636:
				ct_dd_audio_ctrl_i2sout_test29(0);
				break;
			case 637:
				ct_dd_audio_ctrl_i2sout_test30(0);
				break;
			case 638:
				ct_dd_audio_ctrl_i2sout_test31(0);
				break;
			case 639:
				ct_dd_audio_ctrl_i2sout_test32(0);
				break;
			case 640:
				ct_dd_audio_ctrl_i2sout_test33(0);
				break;
			case 641:
				ct_dd_audio_ctrl_i2sout_test34(0);
				break;
			case 642:
				ct_dd_audio_ctrl_i2sout_test35(0);
				break;
			case 643:
				ct_dd_audio_ctrl_i2sout_test1(1);
				break;
			case 644:
				ct_dd_audio_ctrl_i2sout_test2(1);
				break;
			case 645:
				ct_dd_audio_ctrl_i2sout_test3(1);
				break;
			case 646:
				ct_dd_audio_ctrl_i2sout_test4(1);
				break;
			case 647:
				ct_dd_audio_ctrl_i2sout_test5(1);
				break;
			case 648:
				ct_dd_audio_ctrl_i2sout_test6(1);
				break;
			case 649:
				ct_dd_audio_ctrl_i2sout_test7(1);
				break;
			case 650:
				ct_dd_audio_ctrl_i2sout_test8(1);
				break;
			case 651:
				ct_dd_audio_ctrl_i2sout_test9(1);
				break;
			case 652:
				ct_dd_audio_ctrl_i2sout_test10(1);
				break;
			case 653:
				ct_dd_audio_ctrl_i2sout_test11(1);
				break;
			case 654:
				ct_dd_audio_ctrl_i2sout_test12(1);
				break;
			case 655:
				ct_dd_audio_ctrl_i2sout_test13(1);
				break;
			case 656:
				ct_dd_audio_ctrl_i2sout_test14(1);
				break;
			case 657:
				ct_dd_audio_ctrl_i2sout_test15(1);
				break;
			case 658:
				ct_dd_audio_ctrl_i2sout_test16(1);
				break;
			case 659:
				ct_dd_audio_ctrl_i2sout_test17(1);
				break;
			case 660:
				ct_dd_audio_ctrl_i2sout_test18(1);
				break;
			case 661:
				ct_dd_audio_ctrl_i2sout_test19(1);
				break;
			case 662:
				ct_dd_audio_ctrl_i2sout_test20(1);
				break;
			case 663:
				ct_dd_audio_ctrl_i2sout_test21(1);
				break;
			case 664:
				ct_dd_audio_ctrl_i2sout_test22(1);
				break;
			case 665:
				ct_dd_audio_ctrl_i2sout_test23(1);
				break;
			case 666:
				ct_dd_audio_ctrl_i2sout_test24(1);
				break;
			case 667:
				ct_dd_audio_ctrl_i2sout_test25(1);
				break;
			case 668:
				ct_dd_audio_ctrl_i2sout_test26(1);
				break;
			case 669:
				ct_dd_audio_ctrl_i2sout_test27(1);
				break;
			case 670:
				ct_dd_audio_ctrl_i2sout_test28(1);
				break;
			case 671:
				ct_dd_audio_ctrl_i2sout_test29(1);
				break;
			case 672:
				ct_dd_audio_ctrl_i2sout_test30(1);
				break;
			case 673:
				ct_dd_audio_ctrl_i2sout_test31(1);
				break;
			case 674:
				ct_dd_audio_ctrl_i2sout_test32(1);
				break;
			case 675:
				ct_dd_audio_ctrl_i2sout_test33(1);
				break;
			case 676:
				ct_dd_audio_ctrl_i2sout_test34(1);
				break;
			case 677:
				ct_dd_audio_ctrl_i2sout_test35(1);
				break;
			case 678:
				ct_dd_audio_ctrl_i2sout_test1(2);
				break;
			case 679:
				ct_dd_audio_ctrl_i2sout_test2(2);
				break;
			case 680:
				ct_dd_audio_ctrl_i2sout_test3(2);
				break;
			case 681:
				ct_dd_audio_ctrl_i2sout_test4(2);
				break;
			case 682:
				ct_dd_audio_ctrl_i2sout_test5(2);
				break;
			case 683:
				ct_dd_audio_ctrl_i2sout_test6(2);
				break;
			case 684:
				ct_dd_audio_ctrl_i2sout_test7(2);
				break;
			case 685:
				ct_dd_audio_ctrl_i2sout_test8(2);
				break;
			case 686:
				ct_dd_audio_ctrl_i2sout_test9(2);
				break;
			case 687:
				ct_dd_audio_ctrl_i2sout_test10(2);
				break;
			case 688:
				ct_dd_audio_ctrl_i2sout_test11(2);
				break;
			case 689:
				ct_dd_audio_ctrl_i2sout_test12(2);
				break;
			case 690:
				ct_dd_audio_ctrl_i2sout_test13(2);
				break;
			case 691:
				ct_dd_audio_ctrl_i2sout_test14(2);
				break;
			case 692:
				ct_dd_audio_ctrl_i2sout_test15(2);
				break;
			case 693:
				ct_dd_audio_ctrl_i2sout_test16(2);
				break;
			case 694:
				ct_dd_audio_ctrl_i2sout_test17(2);
				break;
			case 695:
				ct_dd_audio_ctrl_i2sout_test18(2);
				break;
			case 696:
				ct_dd_audio_ctrl_i2sout_test19(2);
				break;
			case 697:
				ct_dd_audio_ctrl_i2sout_test20(2);
				break;
			case 698:
				ct_dd_audio_ctrl_i2sout_test21(2);
				break;
			case 699:
				ct_dd_audio_ctrl_i2sout_test22(2);
				break;
			case 700:
				ct_dd_audio_ctrl_i2sout_test23(2);
				break;
			case 701:
				ct_dd_audio_ctrl_i2sout_test24(2);
				break;
			case 702:
				ct_dd_audio_ctrl_i2sout_test25(2);
				break;
			case 703:
				ct_dd_audio_ctrl_i2sout_test26(2);
				break;
			case 704:
				ct_dd_audio_ctrl_i2sout_test27(2);
				break;
			case 705:
				ct_dd_audio_ctrl_i2sout_test28(2);
				break;
			case 706:
				ct_dd_audio_ctrl_i2sout_test29(2);
				break;
			case 707:
				ct_dd_audio_ctrl_i2sout_test30(2);
				break;
			case 708:
				ct_dd_audio_ctrl_i2sout_test31(2);
				break;
			case 709:
				ct_dd_audio_ctrl_i2sout_test32(2);
				break;
			case 710:
				ct_dd_audio_ctrl_i2sout_test33(2);
				break;
			case 711:
				ct_dd_audio_ctrl_i2sout_test34(2);
				break;
			case 712:
				ct_dd_audio_ctrl_i2sout_test35(2);
				break;
			case 713:
				ct_dd_audio_ctrl_i2sout_test1(3);
				break;
			case 714:
				ct_dd_audio_ctrl_i2sout_test2(3);
				break;
			case 715:
				ct_dd_audio_ctrl_i2sout_test3(3);
				break;
			case 716:
				ct_dd_audio_ctrl_i2sout_test4(3);
				break;
			case 717:
				ct_dd_audio_ctrl_i2sout_test5(3);
				break;
			case 718:
				ct_dd_audio_ctrl_i2sout_test6(3);
				break;
			case 719:
				ct_dd_audio_ctrl_i2sout_test7(3);
				break;
			case 720:
				ct_dd_audio_ctrl_i2sout_test8(3);
				break;
			case 721:
				ct_dd_audio_ctrl_i2sout_test9(3);
				break;
			case 722:
				ct_dd_audio_ctrl_i2sout_test10(3);
				break;
			case 723:
				ct_dd_audio_ctrl_i2sout_test11(3);
				break;
			case 724:
				ct_dd_audio_ctrl_i2sout_test12(3);
				break;
			case 725:
				ct_dd_audio_ctrl_i2sout_test13(3);
				break;
			case 726:
				ct_dd_audio_ctrl_i2sout_test14(3);
				break;
			case 727:
				ct_dd_audio_ctrl_i2sout_test15(3);
				break;
			case 728:
				ct_dd_audio_ctrl_i2sout_test16(3);
				break;
			case 729:
				ct_dd_audio_ctrl_i2sout_test17(3);
				break;
			case 730:
				ct_dd_audio_ctrl_i2sout_test18(3);
				break;
			case 731:
				ct_dd_audio_ctrl_i2sout_test19(3);
				break;
			case 732:
				ct_dd_audio_ctrl_i2sout_test20(3);
				break;
			case 733:
				ct_dd_audio_ctrl_i2sout_test21(3);
				break;
			case 734:
				ct_dd_audio_ctrl_i2sout_test22(3);
				break;
			case 735:
				ct_dd_audio_ctrl_i2sout_test23(3);
				break;
			case 736:
				ct_dd_audio_ctrl_i2sout_test24(3);
				break;
			case 737:
				ct_dd_audio_ctrl_i2sout_test25(3);
				break;
			case 738:
				ct_dd_audio_ctrl_i2sout_test26(3);
				break;
			case 739:
				ct_dd_audio_ctrl_i2sout_test27(3);
				break;
			case 740:
				ct_dd_audio_ctrl_i2sout_test28(3);
				break;
			case 741:
				ct_dd_audio_ctrl_i2sout_test29(3);
				break;
			case 742:
				ct_dd_audio_ctrl_i2sout_test30(3);
				break;
			case 743:
				ct_dd_audio_ctrl_i2sout_test31(3);
				break;
			case 744:
				ct_dd_audio_ctrl_i2sout_test32(3);
				break;
			case 745:
				ct_dd_audio_ctrl_i2sout_test33(3);
				break;
			case 746:
				ct_dd_audio_ctrl_i2sout_test34(3);
				break;
			case 747:
				ct_dd_audio_ctrl_i2sout_test35(3);
				break;
			case 748:
				ct_dd_audio_get_ctrl_i2sout_test1(0);
				break;
			case 749:
				ct_dd_audio_get_ctrl_i2sout_test1(1);
				break;
			case 750:
				ct_dd_audio_get_ctrl_i2sout_test1(2);
				break;
			case 751:
				ct_dd_audio_get_ctrl_i2sout_test1(3);
				break;
			case 752:
				ct_dd_audio_ctrl_dmain_test1(0);
				break;
			case 753:
				ct_dd_audio_ctrl_dmain_test2(0);
				break;
			case 754:
				ct_dd_audio_ctrl_dmain_test1(1);
				break;
			case 755:
				ct_dd_audio_ctrl_dmain_test2(1);
				break;
			case 756:
				ct_dd_audio_ctrl_dmain_test1(2);
				break;
			case 757:
				ct_dd_audio_ctrl_dmain_test2(2);
				break;
			case 758:
				ct_dd_audio_ctrl_dmain_test1(4);
				break;
			case 759:
				ct_dd_audio_ctrl_dmain_test2(4);
				break;
			case 760:
				ct_dd_audio_ctrl_dmain_test1(5);
				break;
			case 761:
				ct_dd_audio_ctrl_dmain_test2(5);
				break;
			case 762:
				ct_dd_audio_get_ctrl_dmain_test1(0);
				break;
			case 763:
				ct_dd_audio_get_ctrl_dmain_test1(1);
				break;
			case 764:
				ct_dd_audio_get_ctrl_dmain_test1(2);
				break;
			case 765:
				ct_dd_audio_get_ctrl_dmain_test1(4);
				break;
			case 766:
				ct_dd_audio_get_ctrl_dmain_test1(5);
				break;
			case 767:
				ct_dd_audio_ctrl_dmaout_test1(0);
				break;
			case 768:
				ct_dd_audio_ctrl_dmaout_test2(0);
				break;
			case 769:
				ct_dd_audio_ctrl_dmaout_test1(1);
				break;
			case 770:
				ct_dd_audio_ctrl_dmaout_test2(1);
				break;
			case 771:
				ct_dd_audio_ctrl_dmaout_test1(2);
				break;
			case 772:
				ct_dd_audio_ctrl_dmaout_test2(2);
				break;
			case 773:
				ct_dd_audio_ctrl_dmaout_test1(3);
				break;
			case 774:
				ct_dd_audio_ctrl_dmaout_test2(3);
				break;
			case 775:
				ct_dd_audio_get_ctrl_dmaout_test1(0);
				break;
			case 776:
				ct_dd_audio_get_ctrl_dmaout_test1(1);
				break;
			case 777:
				ct_dd_audio_get_ctrl_dmaout_test1(2);
				break;
			case 778:
				ct_dd_audio_get_ctrl_dmaout_test1(3);
				break;
			case 779:
				ct_dd_audio_start_input_test1(0);
				break;
			case 780:
				ct_dd_audio_start_input_test1(2);
				break;
			case 781:
				ct_dd_audio_start_input_test1(4);
				break;
			case 782:
				ct_dd_audio_start_input_test1(5);
				break;
			case 783:
				ct_dd_audio_start_input_test_multi01();
				break;
			case 784:
				ct_dd_audio_start_input_test_multi45();
				break;
			case 785:
				ct_dd_audio_start_input_test1(0);
				ct_dd_audio_stop_input_test(0);
				break;
			case 786:
				ct_dd_audio_start_input_test1(2);
				ct_dd_audio_stop_input_test(2);
				break;
			case 787:
				ct_dd_audio_start_input_test1(4);
				ct_dd_audio_stop_input_test(4);
				break;
			case 788:
				ct_dd_audio_start_input_test1(5);
				ct_dd_audio_stop_input_test(5);
				break;
			case 789:
				ct_dd_audio_start_input_test_multi01();
				ct_dd_audio_stop_input_test(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 790:
				ct_dd_audio_start_input_test_multi45();
				ct_dd_audio_stop_input_test(D_DD_AUDIO_IF_CH4_CH5);
				break;
			case 791:
				ct_dd_audio_get_status_input_test(0);
				break;
			case 792:
				ct_dd_audio_get_status_input_test(1);
				break;
			case 793:
				ct_dd_audio_get_status_input_test(2);
				break;
			case 794:
				ct_dd_audio_get_status_input_test(4);
				break;
			case 795:
				ct_dd_audio_get_status_input_test(5);
				break;
			case 796:
				ct_dd_audio_start_output_test1(0);
				break;
			case 797:
				ct_dd_audio_start_output_test1(2);
				break;
			case 798:
				ct_dd_audio_start_output_test1(3);
				break;
			case 799:
				ct_dd_audio_start_output_test_multi();
				break;
			case 800:
				ct_dd_audio_start_output_test1(0);
				ct_dd_audio_stop_output_test(0);
				break;
			case 801:
				ct_dd_audio_start_output_test1(2);
				ct_dd_audio_stop_output_test(2);
				break;
			case 802:
				ct_dd_audio_start_output_test1(3);
				ct_dd_audio_stop_output_test(3);
				break;
			case 803:
				ct_dd_audio_start_output_test_multi();
				ct_dd_audio_stop_output_test(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 804:
				ct_dd_audio_get_status_output_test(0);
				break;
			case 805:
				ct_dd_audio_get_status_output_test(1);
				break;
			case 806:
				ct_dd_audio_get_status_output_test(2);
				break;
			case 807:
				ct_dd_audio_get_status_output_test(3);
				break;
			case 808:
				ct_dd_audio_start_loop_back_test1(0);
				break;
			case 809:
				ct_dd_audio_start_loop_back_test1(2);
				break;
			case 810:
				ct_dd_audio_start_loop_back_test_multi();
				break;
			case 811:
				ct_dd_audio_start_loop_back_test1(0);
				ct_dd_audio_stop_loop_back_test(0);
				break;
			case 812:
				ct_dd_audio_start_loop_back_test1(2);
				ct_dd_audio_stop_loop_back_test(2);
				break;
			case 813:
				ct_dd_audio_start_loop_back_test_multi();
				ct_dd_audio_stop_loop_back_test(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 814:
				ct_dd_audio_get_status_loop_back_test(0);
				break;
			case 815:
				ct_dd_audio_get_status_loop_back_test(1);
				break;
			case 816:
				ct_dd_audio_get_status_loop_back_test(2);
				break;
			case 817:
				ct_dd_audio_set_enable_fifo_full_dmain_test1(0);
				break;
			case 818:
				ct_dd_audio_set_enable_fifo_full_dmain_test2(0);
				break;
			case 819:
				ct_dd_audio_set_enable_fifo_full_dmain_test1(1);
				break;
			case 820:
				ct_dd_audio_set_enable_fifo_full_dmain_test2(1);
				break;
			case 821:
				ct_dd_audio_set_enable_fifo_full_dmain_test1(2);
				break;
			case 822:
				ct_dd_audio_set_enable_fifo_full_dmain_test2(2);
				break;
			case 823:
				ct_dd_audio_set_enable_fifo_full_dmain_test1(4);
				break;
			case 824:
				ct_dd_audio_set_enable_fifo_full_dmain_test2(4);
				break;
			case 825:
				ct_dd_audio_set_enable_fifo_full_dmain_test1(5);
				break;
			case 826:
				ct_dd_audio_set_enable_fifo_full_dmain_test2(5);
				break;
			case 827:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test1(0);
				break;
			case 828:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test2(0);
				break;
			case 829:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test1(1);
				break;
			case 830:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test2(1);
				break;
			case 831:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test1(2);
				break;
			case 832:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test2(2);
				break;
			case 833:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test1(3);
				break;
			case 834:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test2(3);
				break;
			case 835:
				ct_dd_audio_set_input_dmarequest_enable_test1(0);
				break;
			case 836:
				ct_dd_audio_set_input_dmarequest_enable_test2(0);
				break;
			case 837:
				ct_dd_audio_set_input_dmarequest_enable_test1(1);
				break;
			case 838:
				ct_dd_audio_set_input_dmarequest_enable_test2(1);
				break;
			case 839:
				ct_dd_audio_set_input_dmarequest_enable_test1(2);
				break;
			case 840:
				ct_dd_audio_set_input_dmarequest_enable_test2(2);
				break;
			case 841:
				ct_dd_audio_set_input_dmarequest_enable_test1(4);
				break;
			case 842:
				ct_dd_audio_set_input_dmarequest_enable_test2(4);
				break;
			case 843:
				ct_dd_audio_set_input_dmarequest_enable_test1(5);
				break;
			case 844:
				ct_dd_audio_set_input_dmarequest_enable_test2(5);
				break;
			case 845:
				ct_dd_audio_set_output_dmarequest_enable_test1(0);
				break;
			case 846:
				ct_dd_audio_set_output_dmarequest_enable_test2(0);
				break;
			case 847:
				ct_dd_audio_set_output_dmarequest_enable_test1(1);
				break;
			case 848:
				ct_dd_audio_set_output_dmarequest_enable_test2(1);
				break;
			case 849:
				ct_dd_audio_set_output_dmarequest_enable_test1(2);
				break;
			case 850:
				ct_dd_audio_set_output_dmarequest_enable_test2(2);
				break;
			case 851:
				ct_dd_audio_set_output_dmarequest_enable_test1(3);
				break;
			case 852:
				ct_dd_audio_set_output_dmarequest_enable_test2(3);
				break;
			case 853:
				ct_dd_audio_get_in_dmasample_test(0);
				break;
			case 854:
				ct_dd_audio_get_in_dmasample_test(1);
				break;
			case 855:
				ct_dd_audio_get_in_dmasample_test(2);
				break;
			case 856:
				ct_dd_audio_get_in_dmasample_test(4);
				break;
			case 857:
				ct_dd_audio_get_in_dmasample_test(5);
				break;
			case 858:
				ct_dd_audio_get_out_dmasample_test(0);
				break;
			case 859:
				ct_dd_audio_get_out_dmasample_test(1);
				break;
			case 860:
				ct_dd_audio_get_out_dmasample_test(2);
				break;
			case 861:
				ct_dd_audio_get_out_dmasample_test(3);
				break;
			case 862:
				ct_dd_audio_set_swaphw_auidlr_test1(0);
				break;
			case 863:
				ct_dd_audio_set_swaphw_auidlr_test2(0);
				break;
			case 864:
				ct_dd_audio_set_swaphw_auidlr_test3(0);
				break;
			case 865:
				ct_dd_audio_set_swaphw_auidlr_test1(1);
				break;
			case 866:
				ct_dd_audio_set_swaphw_auidlr_test2(1);
				break;
			case 867:
				ct_dd_audio_set_swaphw_auidlr_test3(1);
				break;
			case 868:
				ct_dd_audio_set_swaphw_auidlr_test1(2);
				break;
			case 869:
				ct_dd_audio_set_swaphw_auidlr_test2(2);
				break;
			case 870:
				ct_dd_audio_set_swaphw_auidlr_test3(2);
				break;
			case 871:
				ct_dd_audio_set_swaphw_auidlr_test1(4);
				break;
			case 872:
				ct_dd_audio_set_swaphw_auidlr_test2(4);
				break;
			case 873:
				ct_dd_audio_set_swaphw_auidlr_test3(4);
				break;
			case 874:
				ct_dd_audio_set_swaphw_auidlr_test1(5);
				break;
			case 875:
				ct_dd_audio_set_swaphw_auidlr_test2(5);
				break;
			case 876:
				ct_dd_audio_set_swaphw_auidlr_test3(5);
				break;
			case 877:
				ct_dd_audio_set_swapbyte_auidlr_test1(0);
				break;
			case 878:
				ct_dd_audio_set_swapbyte_auidlr_test2(0);
				break;
			case 879:
				ct_dd_audio_set_swapbyte_auidlr_test3(0);
				break;
			case 880:
				ct_dd_audio_set_swapbyte_auidlr_test1(1);
				break;
			case 881:
				ct_dd_audio_set_swapbyte_auidlr_test2(1);
				break;
			case 882:
				ct_dd_audio_set_swapbyte_auidlr_test3(1);
				break;
			case 883:
				ct_dd_audio_set_swapbyte_auidlr_test1(2);
				break;
			case 884:
				ct_dd_audio_set_swapbyte_auidlr_test2(2);
				break;
			case 885:
				ct_dd_audio_set_swapbyte_auidlr_test3(2);
				break;
			case 886:
				ct_dd_audio_set_swapbyte_auidlr_test1(4);
				break;
			case 887:
				ct_dd_audio_set_swapbyte_auidlr_test2(4);
				break;
			case 888:
				ct_dd_audio_set_swapbyte_auidlr_test3(4);
				break;
			case 889:
				ct_dd_audio_set_swapbyte_auidlr_test1(5);
				break;
			case 890:
				ct_dd_audio_set_swapbyte_auidlr_test2(5);
				break;
			case 891:
				ct_dd_audio_set_swapbyte_auidlr_test3(5);
				break;
			case 892:
				ct_dd_audio_set_swaphw_auodlr_test1(0);
				break;
			case 893:
				ct_dd_audio_set_swaphw_auodlr_test2(0);
				break;
			case 894:
				ct_dd_audio_set_swaphw_auodlr_test3(0);
				break;
			case 895:
				ct_dd_audio_set_swaphw_auodlr_test4(0);
				break;
			case 896:
				ct_dd_audio_set_swaphw_auodlr_test1(1);
				break;
			case 897:
				ct_dd_audio_set_swaphw_auodlr_test2(1);
				break;
			case 898:
				ct_dd_audio_set_swaphw_auodlr_test3(1);
				break;
			case 899:
				ct_dd_audio_set_swaphw_auodlr_test4(1);
				break;
			case 900:
				ct_dd_audio_set_swaphw_auodlr_test1(2);
				break;
			case 901:
				ct_dd_audio_set_swaphw_auodlr_test2(2);
				break;
			case 902:
				ct_dd_audio_set_swaphw_auodlr_test3(2);
				break;
			case 903:
				ct_dd_audio_set_swaphw_auodlr_test4(2);
				break;
			case 904:
				ct_dd_audio_set_swaphw_auodlr_test1(3);
				break;
			case 905:
				ct_dd_audio_set_swaphw_auodlr_test2(3);
				break;
			case 906:
				ct_dd_audio_set_swaphw_auodlr_test3(3);
				break;
			case 907:
				ct_dd_audio_set_swapbyte_auodlr_test1(0);
				break;
			case 908:
				ct_dd_audio_set_swapbyte_auodlr_test2(0);
				break;
			case 909:
				ct_dd_audio_set_swapbyte_auodlr_test3(0);
				break;
			case 910:
				ct_dd_audio_set_swapbyte_auodlr_test4(0);
				break;
			case 911:
				ct_dd_audio_set_swapbyte_auodlr_test1(1);
				break;
			case 912:
				ct_dd_audio_set_swapbyte_auodlr_test2(1);
				break;
			case 913:
				ct_dd_audio_set_swapbyte_auodlr_test3(1);
				break;
			case 914:
				ct_dd_audio_set_swapbyte_auodlr_test4(1);
				break;
			case 915:
				ct_dd_audio_set_swapbyte_auodlr_test1(2);
				break;
			case 916:
				ct_dd_audio_set_swapbyte_auodlr_test2(2);
				break;
			case 917:
				ct_dd_audio_set_swapbyte_auodlr_test3(2);
				break;
			case 918:
				ct_dd_audio_set_swapbyte_auodlr_test4(2);
				break;
			case 919:
				ct_dd_audio_set_swapbyte_auodlr_test1(3);
				break;
			case 920:
				ct_dd_audio_set_swapbyte_auodlr_test2(3);
				break;
			case 921:
				ct_dd_audio_set_swapbyte_auodlr_test3(3);
				break;
			case 922:
				ct_dd_audio_get_addr_reg_auidlr_test(0);
				break;
			case 923:
				ct_dd_audio_get_addr_reg_auidlr_test(1);
				break;
			case 924:
				ct_dd_audio_get_addr_reg_auidlr_test(2);
				break;
			case 925:
				ct_dd_audio_get_addr_reg_auidlr_test(4);
				break;
			case 926:
				ct_dd_audio_get_addr_reg_auidlr_test(5);
				break;
			case 927:
				ct_dd_audio_get_addr_reg_auodlr_test(0);
				break;
			case 928:
				ct_dd_audio_get_addr_reg_auodlr_test(1);
				break;
			case 929:
				ct_dd_audio_get_addr_reg_auodlr_test(2);
				break;
			case 930:
				ct_dd_audio_get_addr_reg_auodlr_test(3);
				break;
			case 931:
				ct_dd_audio_get_addr_reg_auidl_test(0);
				break;
			case 932:
				ct_dd_audio_get_addr_reg_auidl_test(1);
				break;
			case 933:
				ct_dd_audio_get_addr_reg_auidl_test(2);
				break;
			case 934:
				ct_dd_audio_get_addr_reg_auidl_test(4);
				break;
			case 935:
				ct_dd_audio_get_addr_reg_auidl_test(5);
				break;
			case 936:
				ct_dd_audio_get_addr_reg_auidr_test(0);
				break;
			case 937:
				ct_dd_audio_get_addr_reg_auidr_test(1);
				break;
			case 938:
				ct_dd_audio_get_addr_reg_auidr_test(2);
				break;
			case 939:
				ct_dd_audio_get_addr_reg_auidr_test(4);
				break;
			case 940:
				ct_dd_audio_get_addr_reg_auidr_test(5);
				break;
			case 941:
				ct_dd_audio_get_addr_reg_auodl_test(0);
				break;
			case 942:
				ct_dd_audio_get_addr_reg_auodl_test(1);
				break;
			case 943:
				ct_dd_audio_get_addr_reg_auodl_test(2);
				break;
			case 944:
				ct_dd_audio_get_addr_reg_auodl_test(3);
				break;
			case 945:
				ct_dd_audio_get_addr_reg_auodr_test(0);
				break;
			case 946:
				ct_dd_audio_get_addr_reg_auodr_test(1);
				break;
			case 947:
				ct_dd_audio_get_addr_reg_auodr_test(2);
				break;
			case 948:
				ct_dd_audio_get_addr_reg_auodr_test(3);
				break;
			case 949:
				ct_dd_audio_get_addr_reg_auiddmapt_test(0);
				break;
			case 950:
				ct_dd_audio_get_addr_reg_auiddmapt_test(1);
				break;
			case 951:
				ct_dd_audio_get_addr_reg_auiddmapt_test(2);
				break;
			case 952:
				ct_dd_audio_get_addr_reg_auiddmapt_test(4);
				break;
			case 953:
				ct_dd_audio_get_addr_reg_auiddmapt_test(5);
				break;
			case 954:
				ct_dd_audio_get_addr_reg_auoddmapt_test(0);
				break;
			case 955:
				ct_dd_audio_get_addr_reg_auoddmapt_test(1);
				break;
			case 956:
				ct_dd_audio_get_addr_reg_auoddmapt_test(2);
				break;
			case 957:
				ct_dd_audio_get_addr_reg_auoddmapt_test(3);
				break;
			case 958:
				ct_dd_audio_set_enable_input_intr_test1(0);
				break;
			case 959:
				ct_dd_audio_set_enable_input_intr_test2(0);
				break;
			case 960:
				ct_dd_audio_set_enable_input_intr_test3(0);
				break;
			case 961:
				ct_dd_audio_set_enable_input_intr_test4(0);
				break;
			case 962:
				ct_dd_audio_set_enable_input_intr_test5(0);
				break;
			case 963:
				ct_dd_audio_set_enable_input_intr_test6(0);
				break;
			case 964:
				ct_dd_audio_set_enable_input_intr_test7(0);
				break;
			case 965:
				ct_dd_audio_set_enable_input_intr_test8(0);
				break;
			case 966:
				ct_dd_audio_set_enable_input_intr_test1(1);
				break;
			case 967:
				ct_dd_audio_set_enable_input_intr_test2(1);
				break;
			case 968:
				ct_dd_audio_set_enable_input_intr_test3(1);
				break;
			case 969:
				ct_dd_audio_set_enable_input_intr_test4(1);
				break;
			case 970:
				ct_dd_audio_set_enable_input_intr_test5(1);
				break;
			case 971:
				ct_dd_audio_set_enable_input_intr_test6(1);
				break;
			case 972:
				ct_dd_audio_set_enable_input_intr_test7(1);
				break;
			case 973:
				ct_dd_audio_set_enable_input_intr_test8(1);
				break;
			case 974:
				ct_dd_audio_set_enable_input_intr_test1(2);
				break;
			case 975:
				ct_dd_audio_set_enable_input_intr_test2(2);
				break;
			case 976:
				ct_dd_audio_set_enable_input_intr_test3(2);
				break;
			case 977:
				ct_dd_audio_set_enable_input_intr_test4(2);
				break;
			case 978:
				ct_dd_audio_set_enable_input_intr_test5(2);
				break;
			case 979:
				ct_dd_audio_set_enable_input_intr_test6(2);
				break;
			case 980:
				ct_dd_audio_set_enable_input_intr_test7(2);
				break;
			case 981:
				ct_dd_audio_set_enable_input_intr_test8(2);
				break;
			case 982:
				ct_dd_audio_set_enable_input_intr_test1(4);
				break;
			case 983:
				ct_dd_audio_set_enable_input_intr_test2(4);
				break;
			case 984:
				ct_dd_audio_set_enable_input_intr_test3(4);
				break;
			case 985:
				ct_dd_audio_set_enable_input_intr_test4(4);
				break;
			case 986:
				ct_dd_audio_set_enable_input_intr_test5(4);
				break;
			case 987:
				ct_dd_audio_set_enable_input_intr_test6(4);
				break;
			case 988:
				ct_dd_audio_set_enable_input_intr_test7(4);
				break;
			case 989:
				ct_dd_audio_set_enable_input_intr_test8(4);
				break;
			case 990:
				ct_dd_audio_set_enable_input_intr_test1(5);
				break;
			case 991:
				ct_dd_audio_set_enable_input_intr_test2(5);
				break;
			case 992:
				ct_dd_audio_set_enable_input_intr_test3(5);
				break;
			case 993:
				ct_dd_audio_set_enable_input_intr_test4(5);
				break;
			case 994:
				ct_dd_audio_set_enable_input_intr_test5(5);
				break;
			case 995:
				ct_dd_audio_set_enable_input_intr_test6(5);
				break;
			case 996:
				ct_dd_audio_set_enable_input_intr_test7(5);
				break;
			case 997:
				ct_dd_audio_set_enable_input_intr_test8(5);
				break;
			case 998:
				ct_dd_audio_set_enable_output_intr_test1(0);
				break;
			case 999:
				ct_dd_audio_set_enable_output_intr_test2(0);
				break;
			case 1000:
				ct_dd_audio_set_enable_output_intr_test3(0);
				break;
			case 1001:
				ct_dd_audio_set_enable_output_intr_test4(0);
				break;
			case 1002:
				ct_dd_audio_set_enable_output_intr_test5(0);
				break;
			case 1003:
				ct_dd_audio_set_enable_output_intr_test6(0);
				break;
			case 1004:
				ct_dd_audio_set_enable_output_intr_test7(0);
				break;
			case 1005:
				ct_dd_audio_set_enable_output_intr_test8(0);
				break;
			case 1006:
				ct_dd_audio_set_enable_output_intr_test1(1);
				break;
			case 1007:
				ct_dd_audio_set_enable_output_intr_test2(1);
				break;
			case 1008:
				ct_dd_audio_set_enable_output_intr_test3(1);
				break;
			case 1009:
				ct_dd_audio_set_enable_output_intr_test4(1);
				break;
			case 1010:
				ct_dd_audio_set_enable_output_intr_test5(1);
				break;
			case 1011:
				ct_dd_audio_set_enable_output_intr_test6(1);
				break;
			case 1012:
				ct_dd_audio_set_enable_output_intr_test7(1);
				break;
			case 1013:
				ct_dd_audio_set_enable_output_intr_test8(1);
				break;
			case 1014:
				ct_dd_audio_set_enable_output_intr_test1(2);
				break;
			case 1015:
				ct_dd_audio_set_enable_output_intr_test2(2);
				break;
			case 1016:
				ct_dd_audio_set_enable_output_intr_test3(2);
				break;
			case 1017:
				ct_dd_audio_set_enable_output_intr_test4(2);
				break;
			case 1018:
				ct_dd_audio_set_enable_output_intr_test5(2);
				break;
			case 1019:
				ct_dd_audio_set_enable_output_intr_test6(2);
				break;
			case 1020:
				ct_dd_audio_set_enable_output_intr_test7(2);
				break;
			case 1021:
				ct_dd_audio_set_enable_output_intr_test8(2);
				break;
			case 1022:
				ct_dd_audio_set_enable_output_intr_test1(3);
				break;
			case 1023:
				ct_dd_audio_set_enable_output_intr_test2(3);
				break;
			case 1024:
				ct_dd_audio_set_enable_output_intr_test3(3);
				break;
			case 1025:
				ct_dd_audio_set_enable_output_intr_test4(3);
				break;
			case 1026:
				ct_dd_audio_set_enable_output_intr_test5(3);
				break;
			case 1027:
				ct_dd_audio_set_enable_output_intr_test6(3);
				break;
			case 1028:
				ct_dd_audio_set_enable_output_intr_test7(3);
				break;
			case 1029:
				ct_dd_audio_set_enable_output_intr_test8(3);
				break;
			case 1030:
				ct_dd_audio_set_enable_in_over_flow_intr_test1(0);
				break;
			case 1031:
				ct_dd_audio_set_enable_in_over_flow_intr_test2(0);
				break;
			case 1032:
				ct_dd_audio_set_enable_in_over_flow_intr_test1(1);
				break;
			case 1033:
				ct_dd_audio_set_enable_in_over_flow_intr_test2(1);
				break;
			case 1034:
				ct_dd_audio_set_enable_in_over_flow_intr_test1(2);
				break;
			case 1035:
				ct_dd_audio_set_enable_in_over_flow_intr_test2(2);
				break;
			case 1036:
				ct_dd_audio_set_enable_in_over_flow_intr_test1(4);
				break;
			case 1037:
				ct_dd_audio_set_enable_in_over_flow_intr_test2(4);
				break;
			case 1038:
				ct_dd_audio_set_enable_in_over_flow_intr_test1(5);
				break;
			case 1039:
				ct_dd_audio_set_enable_in_over_flow_intr_test2(5);
				break;
			case 1040:
				ct_dd_audio_set_enable_out_under_flow_intr_test1(0);
				break;
			case 1041:
				ct_dd_audio_set_enable_out_under_flow_intr_test2(0);
				break;
			case 1042:
				ct_dd_audio_set_enable_out_under_flow_intr_test1(1);
				break;
			case 1043:
				ct_dd_audio_set_enable_out_under_flow_intr_test2(1);
				break;
			case 1044:
				ct_dd_audio_set_enable_out_under_flow_intr_test1(2);
				break;
			case 1045:
				ct_dd_audio_set_enable_out_under_flow_intr_test2(2);
				break;
			case 1046:
				ct_dd_audio_set_enable_out_under_flow_intr_test1(3);
				break;
			case 1047:
				ct_dd_audio_set_enable_out_under_flow_intr_test2(3);
				break;
			case 1048:
				ct_dd_audio_get_input_fifo_status_test(0);
				break;
			case 1049:
				ct_dd_audio_get_input_fifo_status_test(1);
				break;
			case 1050:
				ct_dd_audio_get_input_fifo_status_test(2);
				break;
			case 1051:
				ct_dd_audio_get_input_fifo_status_test(4);
				break;
			case 1052:
				ct_dd_audio_get_input_fifo_status_test(5);
				break;
			case 1053:
				ct_dd_audio_get_output_fifo_status_test(0);
				break;
			case 1054:
				ct_dd_audio_get_output_fifo_status_test(1);
				break;
			case 1055:
				ct_dd_audio_get_output_fifo_status_test(2);
				break;
			case 1056:
				ct_dd_audio_get_output_fifo_status_test(3);
				break;
			default :
				Ddim_Print(("ddaudio : ERROR command line\n"));
				break;
		}
	}
	else if(atoi(argv[1]) == 2) {
		switch (atoi(argv[2])) {
			case 1:
				ct_dd_audio_input_open_test1(3);
				break;
			case 2:
				ct_dd_audio_input_open_test1(6);
				break;
			case 3:
				ct_dd_audio_input_open_test4(0);
				break;
			case 4:
				ct_dd_audio_output_open_test1(4);
				break;
			case 5:
				ct_dd_audio_output_open_test4(0);
				break;
			case 6:
				ct_dd_audio_input_close_test(3);
				break;
			case 7:
				ct_dd_audio_input_close_test(6);
				break;
			case 8:
				ct_dd_audio_output_close_test(4);
				break;
			case 9:
				ct_dd_audio_int_handler_test1(6);
				break;
			case 10:
				ct_dd_audio_reset_test(6);
				break;
			case 11:
				ct_dd_audio_ctrl_common_test1(6);
				break;
			case 12:
				ct_dd_audio_ctrl_common_test6(0);
				break;
			case 13:
				ct_dd_audio_ctrl_common_test7(0);
				break;
			case 14:
				ct_dd_audio_ctrl_common_test8(0);
				break;
			case 15:
				ct_dd_audio_ctrl_common_test9(0);
				break;
			case 16:
				ct_dd_audio_ctrl_common_test10(0);
				break;
			case 17:
				ct_dd_audio_ctrl_common_test11(0);
				break;
			case 18:
				ct_dd_audio_get_ctrl_common_test1(6);
				break;
			case 19:
				ct_dd_audio_get_ctrl_common_test2(0);
				break;
			case 20:
				ct_dd_audio_ctrl_input_test15(0);
				break;
			case 21:
				ct_dd_audio_ctrl_input_test16(0);
				break;
			case 22:
				ct_dd_audio_ctrl_input_test17(0);
				break;
			case 23:
				ct_dd_audio_ctrl_input_test18(0);
				break;
			case 24:
				ct_dd_audio_ctrl_input_test15(1);
				break;
			case 25:
				ct_dd_audio_ctrl_input_test16(1);
				break;
			case 26:
				ct_dd_audio_ctrl_input_test17(1);
				break;
			case 27:
				ct_dd_audio_ctrl_input_test18(1);
				break;
			case 28:
				ct_dd_audio_ctrl_input_test15(2);
				break;
			case 29:
				ct_dd_audio_ctrl_input_test16(2);
				break;
			case 30:
				ct_dd_audio_ctrl_input_test17(2);
				break;
			case 31:
				ct_dd_audio_ctrl_input_test18(2);
				break;
			case 32:
				ct_dd_audio_ctrl_input_test15(4);
				break;
			case 33:
				ct_dd_audio_ctrl_input_test16(4);
				break;
			case 34:
				ct_dd_audio_ctrl_input_test17(4);
				break;
			case 35:
				ct_dd_audio_ctrl_input_test18(4);
				break;
			case 36:
				ct_dd_audio_ctrl_input_test15(5);
				break;
			case 37:
				ct_dd_audio_ctrl_input_test16(5);
				break;
			case 38:
				ct_dd_audio_ctrl_input_test17(5);
				break;
			case 39:
				ct_dd_audio_ctrl_input_test18(5);
				break;
			case 40:
				ct_dd_audio_ctrl_input_test1(3);
				break;
			case 41:
				ct_dd_audio_ctrl_input_test1(6);
				break;
			case 42:
				ct_dd_audio_ctrl_input_test19(0);
				break;
			case 43:
				ct_dd_audio_ctrl_input_test20(0);
				break;
			case 44:
				ct_dd_audio_ctrl_input_test21(0);
				break;
			case 45:
				ct_dd_audio_ctrl_input_test22(0);
				break;
			case 46:
				ct_dd_audio_ctrl_input_test23(0);
				break;
			case 47:
				ct_dd_audio_get_ctrl_input_test1(3);
				break;
			case 48:
				ct_dd_audio_get_ctrl_input_test1(6);
				break;
			case 49:
				ct_dd_audio_get_ctrl_input_test2(0);
				break;
			case 50:
				ct_dd_audio_ctrl_output_test29(0);
				break;
			case 51:
				ct_dd_audio_ctrl_output_test30(0);
				break;
			case 52:
				ct_dd_audio_ctrl_output_test31(0);
				break;
			case 53:
				ct_dd_audio_ctrl_output_test32(0);
				break;
			case 54:
				ct_dd_audio_ctrl_output_test33(0);
				break;
			case 55:
				ct_dd_audio_ctrl_output_test34(0);
				break;
			case 56:
				ct_dd_audio_ctrl_output_test35(0);
				break;
			case 57:
				ct_dd_audio_ctrl_output_test36(0);
				break;
			case 58:
				ct_dd_audio_ctrl_output_test37(0);
				break;
			case 59:
				ct_dd_audio_ctrl_output_test38(0);
				break;
			case 60:
				ct_dd_audio_ctrl_output_test29(1);
				break;
			case 61:
				ct_dd_audio_ctrl_output_test30(1);
				break;
			case 62:
				ct_dd_audio_ctrl_output_test31(1);
				break;
			case 63:
				ct_dd_audio_ctrl_output_test32(1);
				break;
			case 64:
				ct_dd_audio_ctrl_output_test33(1);
				break;
			case 65:
				ct_dd_audio_ctrl_output_test34(1);
				break;
			case 66:
				ct_dd_audio_ctrl_output_test35(1);
				break;
			case 67:
				ct_dd_audio_ctrl_output_test36(1);
				break;
			case 68:
				ct_dd_audio_ctrl_output_test37(1);
				break;
			case 69:
				ct_dd_audio_ctrl_output_test38(1);
				break;
			case 70:
				ct_dd_audio_ctrl_output_test29(2);
				break;
			case 71:
				ct_dd_audio_ctrl_output_test30(2);
				break;
			case 72:
				ct_dd_audio_ctrl_output_test31(2);
				break;
			case 73:
				ct_dd_audio_ctrl_output_test32(2);
				break;
			case 74:
				ct_dd_audio_ctrl_output_test33(2);
				break;
			case 75:
				ct_dd_audio_ctrl_output_test34(2);
				break;
			case 76:
				ct_dd_audio_ctrl_output_test35(2);
				break;
			case 77:
				ct_dd_audio_ctrl_output_test36(2);
				break;
			case 78:
				ct_dd_audio_ctrl_output_test37(2);
				break;
			case 79:
				ct_dd_audio_ctrl_output_test38(2);
				break;
			case 80:
				ct_dd_audio_ctrl_output_test29(3);
				break;
			case 81:
				ct_dd_audio_ctrl_output_test30(3);
				break;
			case 82:
				ct_dd_audio_ctrl_output_test31(3);
				break;
			case 83:
				ct_dd_audio_ctrl_output_test32(3);
				break;
			case 84:
				ct_dd_audio_ctrl_output_test33(3);
				break;
			case 85:
				ct_dd_audio_ctrl_output_test34(3);
				break;
			case 86:
				ct_dd_audio_ctrl_output_test35(3);
				break;
			case 87:
				ct_dd_audio_ctrl_output_test36(3);
				break;
			case 88:
				ct_dd_audio_ctrl_output_test37(3);
				break;
			case 89:
				ct_dd_audio_ctrl_output_test38(3);
				break;
			case 90:
				ct_dd_audio_ctrl_output_test1(4);
				break;
			case 91:
				ct_dd_audio_ctrl_output_test39(0);
				break;
			case 92:
				ct_dd_audio_ctrl_output_test40(0);
				break;
			case 93:
				ct_dd_audio_ctrl_output_test41(0);
				break;
			case 94:
				ct_dd_audio_ctrl_output_test42(0);
				break;
			case 95:
				ct_dd_audio_ctrl_output_test43(0);
				break;
			case 96:
				ct_dd_audio_ctrl_output_test44(0);
				break;
			case 97:
				ct_dd_audio_ctrl_output_test45(0);
				break;
			case 98:
				ct_dd_audio_get_ctrl_output_test1(4);
				break;
			case 99:
				ct_dd_audio_get_ctrl_output_test2(0);
				break;
			case 100:
				ct_dd_audio_ctrl_i2scmmn_test38(0);
				break;
			case 101:
				ct_dd_audio_ctrl_i2scmmn_test39(0);
				break;
			case 102:
				ct_dd_audio_ctrl_i2scmmn_test40(0);
				break;
			case 103:
				ct_dd_audio_ctrl_i2scmmn_test41(0);
				break;
			case 104:
				ct_dd_audio_ctrl_i2scmmn_test38(2);
				break;
			case 105:
				ct_dd_audio_ctrl_i2scmmn_test39(2);
				break;
			case 106:
				ct_dd_audio_ctrl_i2scmmn_test40(2);
				break;
			case 107:
				ct_dd_audio_ctrl_i2scmmn_test41(2);
				break;
			case 108:
				ct_dd_audio_ctrl_i2scmmn_test39(3);
				break;
			case 109:
				ct_dd_audio_ctrl_i2scmmn_test41(3);
				break;
			case 110:
				ct_dd_audio_ctrl_i2scmmn_test38(4);
				break;
			case 111:
				ct_dd_audio_ctrl_i2scmmn_test40(4);
				break;
			case 112:
				ct_dd_audio_ctrl_i2scmmn_test38(5);
				break;
			case 113:
				ct_dd_audio_ctrl_i2scmmn_test40(5);
				break;
			case 114:
				ct_dd_audio_ctrl_i2scmmn_test1(6);
				break;
			case 115:
				ct_dd_audio_ctrl_i2scmmn_test42(0);
				break;
			case 116:
				ct_dd_audio_ctrl_i2scmmn_test43(0);
				break;
			case 117:
				ct_dd_audio_ctrl_i2scmmn_test44(0);
				break;
			case 118:
				ct_dd_audio_ctrl_i2scmmn_test45(0);
				break;
			case 119:
				ct_dd_audio_ctrl_i2scmmn_test46(0);
				break;
			case 120:
				ct_dd_audio_ctrl_i2scmmn_test47(0);
				break;
			case 121:
				ct_dd_audio_ctrl_i2scmmn_test48(0);
				break;
			case 122:
				ct_dd_audio_get_ctrl_i2scmmn_test1(6);
				break;
			case 123:
				ct_dd_audio_get_ctrl_i2scmmn_test2(0);
				break;
			case 124:
				ct_dd_audio_ctrl_i2sin_test11(0);
				break;
			case 125:
				ct_dd_audio_ctrl_i2sin_test11(1);
				break;
			case 126:
				ct_dd_audio_ctrl_i2sin_test11(2);
				break;
			case 127:
				ct_dd_audio_ctrl_i2sin_test11(4);
				break;
			case 128:
				ct_dd_audio_ctrl_i2sin_test11(5);
				break;
			case 129:
				ct_dd_audio_ctrl_i2sin_test1(3);
				break;
			case 130:
				ct_dd_audio_ctrl_i2sin_test1(6);
				break;
			case 131:
				ct_dd_audio_ctrl_i2sin_test12(0);
				break;
			case 132:
				ct_dd_audio_ctrl_i2sin_test13(0);
				break;
			case 133:
				ct_dd_audio_ctrl_i2sin_test14(0);
				break;
			case 134:
				ct_dd_audio_get_ctrl_i2sin_test1(3);
				break;
			case 135:
				ct_dd_audio_get_ctrl_i2sin_test1(6);
				break;
			case 136:
				ct_dd_audio_get_ctrl_i2sin_test2(0);
				break;
			case 137:
				ct_dd_audio_ctrl_i2sout_test36(0);
				break;
			case 138:
				ct_dd_audio_ctrl_i2sout_test37(0);
				break;
			case 139:
				ct_dd_audio_ctrl_i2sout_test38(0);
				break;
			case 140:
				ct_dd_audio_ctrl_i2sout_test39(0);
				break;
			case 141:
				ct_dd_audio_ctrl_i2sout_test40(0);
				break;
			case 142:
				ct_dd_audio_ctrl_i2sout_test36(1);
				break;
			case 143:
				ct_dd_audio_ctrl_i2sout_test37(1);
				break;
			case 144:
				ct_dd_audio_ctrl_i2sout_test38(1);
				break;
			case 145:
				ct_dd_audio_ctrl_i2sout_test39(1);
				break;
			case 146:
				ct_dd_audio_ctrl_i2sout_test40(1);
				break;
			case 147:
				ct_dd_audio_ctrl_i2sout_test36(2);
				break;
			case 148:
				ct_dd_audio_ctrl_i2sout_test37(2);
				break;
			case 149:
				ct_dd_audio_ctrl_i2sout_test38(2);
				break;
			case 150:
				ct_dd_audio_ctrl_i2sout_test39(2);
				break;
			case 151:
				ct_dd_audio_ctrl_i2sout_test40(2);
				break;
			case 152:
				ct_dd_audio_ctrl_i2sout_test36(3);
				break;
			case 153:
				ct_dd_audio_ctrl_i2sout_test37(3);
				break;
			case 154:
				ct_dd_audio_ctrl_i2sout_test38(3);
				break;
			case 155:
				ct_dd_audio_ctrl_i2sout_test39(3);
				break;
			case 156:
				ct_dd_audio_ctrl_i2sout_test40(3);
				break;
			case 157:
				ct_dd_audio_ctrl_i2sout_test1(4);
				break;
			case 158:
				ct_dd_audio_ctrl_i2sout_test41(0);
				break;
			case 159:
				ct_dd_audio_ctrl_i2sout_test42(0);
				break;
			case 160:
				ct_dd_audio_ctrl_i2sout_test43(0);
				break;
			case 161:
				ct_dd_audio_ctrl_i2sout_test44(0);
				break;
			case 162:
				ct_dd_audio_get_ctrl_i2sout_test1(4);
				break;
			case 163:
				ct_dd_audio_get_ctrl_i2sout_test2(0);
				break;
			case 164:
				ct_dd_audio_ctrl_dmain_test3(0);
				break;
			case 165:
				ct_dd_audio_ctrl_dmain_test4(0);
				break;
			case 166:
				ct_dd_audio_ctrl_dmain_test5(0);
				break;
			case 167:
				ct_dd_audio_ctrl_dmain_test3(1);
				break;
			case 168:
				ct_dd_audio_ctrl_dmain_test4(1);
				break;
			case 169:
				ct_dd_audio_ctrl_dmain_test5(1);
				break;
			case 170:
				ct_dd_audio_ctrl_dmain_test3(2);
				break;
			case 171:
				ct_dd_audio_ctrl_dmain_test4(2);
				break;
			case 172:
				ct_dd_audio_ctrl_dmain_test5(2);
				break;
			case 173:
				ct_dd_audio_ctrl_dmain_test3(4);
				break;
			case 174:
				ct_dd_audio_ctrl_dmain_test4(4);
				break;
			case 175:
				ct_dd_audio_ctrl_dmain_test5(4);
				break;
			case 176:
				ct_dd_audio_ctrl_dmain_test3(5);
				break;
			case 177:
				ct_dd_audio_ctrl_dmain_test4(5);
				break;
			case 178:
				ct_dd_audio_ctrl_dmain_test5(5);
				break;
			case 179:
				ct_dd_audio_ctrl_dmain_test1(3);
				break;
			case 180:
				ct_dd_audio_ctrl_dmain_test1(6);
				break;
			case 181:
				ct_dd_audio_ctrl_dmain_test6(0);
				break;
			case 182:
				ct_dd_audio_ctrl_dmain_test7(0);
				break;
			case 183:
				ct_dd_audio_get_ctrl_dmain_test1(3);
				break;
			case 184:
				ct_dd_audio_get_ctrl_dmain_test1(6);
				break;
			case 185:
				ct_dd_audio_get_ctrl_dmain_test2(0);
				break;
			case 186:
				ct_dd_audio_ctrl_dmaout_test3(0);
				break;
			case 187:
				ct_dd_audio_ctrl_dmaout_test4(0);
				break;
			case 188:
				ct_dd_audio_ctrl_dmaout_test5(0);
				break;
			case 189:
				ct_dd_audio_ctrl_dmaout_test3(1);
				break;
			case 190:
				ct_dd_audio_ctrl_dmaout_test4(1);
				break;
			case 191:
				ct_dd_audio_ctrl_dmaout_test5(1);
				break;
			case 192:
				ct_dd_audio_ctrl_dmaout_test3(2);
				break;
			case 193:
				ct_dd_audio_ctrl_dmaout_test4(2);
				break;
			case 194:
				ct_dd_audio_ctrl_dmaout_test5(2);
				break;
			case 195:
				ct_dd_audio_ctrl_dmaout_test3(3);
				break;
			case 196:
				ct_dd_audio_ctrl_dmaout_test4(3);
				break;
			case 197:
				ct_dd_audio_ctrl_dmaout_test5(3);
				break;
			case 198:
				ct_dd_audio_ctrl_dmaout_test1(4);
				break;
			case 199:
				ct_dd_audio_ctrl_dmaout_test6(0);
				break;
			case 200:
				ct_dd_audio_ctrl_dmaout_test7(0);
				break;
			case 201:
				ct_dd_audio_get_ctrl_dmaout_test1(4);
				break;
			case 202:
				ct_dd_audio_get_ctrl_dmaout_test2(0);
				break;
			case 203:
				ct_dd_audio_start_input_test1(0);
				ct_dd_audio_start_input_test2(0);
				break;
			case 204:
				ct_dd_audio_start_input_test1(2);
				ct_dd_audio_start_input_test2(2);
				break;
			case 205:
				ct_dd_audio_start_input_test1(4);
				ct_dd_audio_start_input_test2(4);
				break;
			case 206:
				ct_dd_audio_start_input_test1(5);
				ct_dd_audio_start_input_test2(5);
				break;
			case 207:
				ct_dd_audio_start_input_test1(0);
				ct_dd_audio_start_input_test2(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 208:
				ct_dd_audio_start_input_test1(4);
				ct_dd_audio_start_input_test2(D_DD_AUDIO_IF_CH4_CH5);
				break;
			case 209:
				ct_dd_audio_start_input_test1(5);
				ct_dd_audio_start_input_test2(D_DD_AUDIO_IF_CH4_CH5);
				break;
			case 210:
				ct_dd_audio_start_input_test2(3);
				break;
			case 211:
				ct_dd_audio_start_input_test2(6);
				break;
			case 212:
				ct_dd_audio_init_test();
				ct_dd_audio_stop_input_test(0);
				break;
			case 213:
				ct_dd_audio_init_test();
				ct_dd_audio_stop_input_test(2);
				break;
			case 214:
				ct_dd_audio_init_test();
				ct_dd_audio_stop_input_test(4);
				break;
			case 215:
				ct_dd_audio_init_test();
				ct_dd_audio_stop_input_test(5);
				break;
			case 216:
				ct_dd_audio_init_test();
				ct_dd_audio_stop_input_test(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 217:
				ct_dd_audio_start_input_test1(0);
				ct_dd_audio_stop_input_test(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 218:
				ct_dd_audio_init_test();
				ct_dd_audio_stop_input_test(D_DD_AUDIO_IF_CH4_CH5);
				break;
			case 219:
				ct_dd_audio_start_input_test1(4);
				ct_dd_audio_stop_input_test(D_DD_AUDIO_IF_CH4_CH5);
				break;
			case 220:
				ct_dd_audio_start_input_test1(5);
				ct_dd_audio_stop_input_test(D_DD_AUDIO_IF_CH4_CH5);
				break;
			case 221:
				ct_dd_audio_stop_input_test(3);
				break;
			case 222:
				ct_dd_audio_stop_input_test(6);
				break;
			case 223:
				ct_dd_audio_get_status_input_test(3);
				break;
			case 224:
				ct_dd_audio_get_status_input_test(6);
				break;
			case 225:
				ct_dd_audio_start_output_test1(0);
				ct_dd_audio_start_output_test2(0);
				break;
			case 226:
				ct_dd_audio_start_loop_back_test1(0);
				ct_dd_audio_start_output_test2(0);
				break;
			case 227:
				ct_dd_audio_start_output_test1(2);
				ct_dd_audio_start_output_test2(2);
				break;
			case 228:
				ct_dd_audio_start_loop_back_test1(2);
				ct_dd_audio_start_output_test2(2);
				break;
			case 229:
				ct_dd_audio_start_output_test1(3);
				ct_dd_audio_start_output_test2(3);
				break;
			case 230:
				ct_dd_audio_start_output_test1(0);
				ct_dd_audio_start_output_test2(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 231:
				ct_dd_audio_start_loop_back_test1(0);
				ct_dd_audio_start_output_test2(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 232:
				ct_dd_audio_start_output_test2(4);
				break;
			case 233:
				ct_dd_audio_stop_output_test(0);
				break;
			case 234:
				ct_dd_audio_stop_output_test(2);
				break;
			case 235:
				ct_dd_audio_stop_output_test(3);
				break;
			case 236:
				ct_dd_audio_stop_output_test(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 237:
				ct_dd_audio_start_output_test1(0);
				ct_dd_audio_stop_output_test(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 238:
				ct_dd_audio_stop_output_test(4);
				break;
			case 239:
				ct_dd_audio_get_status_output_test(4);
				break;
			case 240:
				ct_dd_audio_start_loop_back_test2(0);
				break;
			case 241:
				ct_dd_audio_start_loop_back_test3(0);
				break;
			case 242:
				ct_dd_audio_start_loop_back_test1(0);
				ct_dd_audio_start_loop_back_test2(0);
				break;
			case 243:
				ct_dd_audio_start_loop_back_test2(2);
				break;
			case 244:
				ct_dd_audio_start_loop_back_test3(2);
				break;
			case 245:
				ct_dd_audio_start_loop_back_test1(0);
				ct_dd_audio_start_loop_back_test2(2);
				break;
			case 246:
				ct_dd_audio_start_loop_back_test2(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 247:
				ct_dd_audio_start_input_test1(0);
				ct_dd_audio_start_loop_back_test2(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 248:
				ct_dd_audio_start_loop_back_test_multi();
				ct_dd_audio_start_loop_back_test2(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 249:
				ct_dd_audio_start_loop_back_test_multi();
				ct_dd_audio_stop_loop_back_test(0);
				ct_dd_audio_start_loop_back_test2(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 250:
				ct_dd_audio_start_output_test1(0);
				ct_dd_audio_start_loop_back_test_multi2();
				break;
			case 251:
				ct_dd_audio_start_loop_back_test2(3);
				break;
			case 252:
				ct_dd_audio_stop_loop_back_test(0);
				break;
			case 253:
				ct_dd_audio_stop_loop_back_test(2);
				break;
			case 254:
				ct_dd_audio_stop_loop_back_test(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 255:
				ct_dd_audio_start_loop_back_test1(0);
				ct_dd_audio_stop_loop_back_test(D_DD_AUDIO_IF_CH0_CH1);
				break;
			case 256:
				ct_dd_audio_stop_loop_back_test(3);
				break;
			case 257:
				ct_dd_audio_get_status_loop_back_test(3);
				break;
			case 258:
				ct_dd_audio_set_enable_fifo_full_dmain_test3(0);
				break;
			case 259:
				ct_dd_audio_set_enable_fifo_full_dmain_test3(1);
				break;
			case 260:
				ct_dd_audio_set_enable_fifo_full_dmain_test3(2);
				break;
			case 261:
				ct_dd_audio_set_enable_fifo_full_dmain_test3(4);
				break;
			case 262:
				ct_dd_audio_set_enable_fifo_full_dmain_test3(5);
				break;
			case 263:
				ct_dd_audio_set_enable_fifo_full_dmain_test4(3);
				break;
			case 264:
				ct_dd_audio_set_enable_fifo_full_dmain_test4(6);
				break;
			case 265:
				ct_dd_audio_set_enable_fifo_full_dmain_test5(0);
				break;
			case 266:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test3(0);
				break;
			case 267:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test3(1);
				break;
			case 268:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test3(2);
				break;
			case 269:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test3(3);
				break;
			case 270:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test4(4);
				break;
			case 271:
				ct_dd_audio_set_enable_fifo_empty_dma_out_test5(0);
				break;
			case 272:
				ct_dd_audio_set_input_dmarequest_enable_test3(0);
				break;
			case 273:
				ct_dd_audio_set_input_dmarequest_enable_test3(1);
				break;
			case 274:
				ct_dd_audio_set_input_dmarequest_enable_test3(2);
				break;
			case 275:
				ct_dd_audio_set_input_dmarequest_enable_test3(4);
				break;
			case 276:
				ct_dd_audio_set_input_dmarequest_enable_test3(5);
				break;
			case 277:
				ct_dd_audio_set_input_dmarequest_enable_test4(3);
				break;
			case 278:
				ct_dd_audio_set_input_dmarequest_enable_test4(6);
				break;
			case 279:
				ct_dd_audio_set_input_dmarequest_enable_test5(0);
				break;
			case 280:
				ct_dd_audio_set_output_dmarequest_enable_test3(0);
				break;
			case 281:
				ct_dd_audio_set_output_dmarequest_enable_test3(1);
				break;
			case 282:
				ct_dd_audio_set_output_dmarequest_enable_test3(2);
				break;
			case 283:
				ct_dd_audio_set_output_dmarequest_enable_test3(3);
				break;
			case 284:
				ct_dd_audio_set_output_dmarequest_enable_test4(4);
				break;
			case 285:
				ct_dd_audio_set_output_dmarequest_enable_test5(0);
				break;
			case 286:
				ct_dd_audio_get_in_dmasample_test(3);
				break;
			case 287:
				ct_dd_audio_get_in_dmasample_test(6);
				break;
			case 288:
				ct_dd_audio_get_out_dmasample_test(4);
				break;
			case 289:
				ct_dd_audio_set_swaphw_auidlr_test4(0);
				break;
			case 290:
				ct_dd_audio_set_swaphw_auidlr_test4(1);
				break;
			case 291:
				ct_dd_audio_set_swaphw_auidlr_test4(2);
				break;
			case 292:
				ct_dd_audio_set_swaphw_auidlr_test4(4);
				break;
			case 293:
				ct_dd_audio_set_swaphw_auidlr_test4(5);
				break;
			case 294:
				ct_dd_audio_set_swaphw_auidlr_test5(3);
				break;
			case 295:
				ct_dd_audio_set_swaphw_auidlr_test5(6);
				break;
			case 296:
				ct_dd_audio_set_swaphw_auidlr_test6(0);
				break;
			case 297:
				ct_dd_audio_set_swapbyte_auidlr_test4(0);
				break;
			case 298:
				ct_dd_audio_set_swapbyte_auidlr_test4(1);
				break;
			case 299:
				ct_dd_audio_set_swapbyte_auidlr_test4(2);
				break;
			case 300:
				ct_dd_audio_set_swapbyte_auidlr_test4(4);
				break;
			case 301:
				ct_dd_audio_set_swapbyte_auidlr_test4(5);
				break;
			case 302:
				ct_dd_audio_set_swapbyte_auidlr_test5(3);
				break;
			case 303:
				ct_dd_audio_set_swapbyte_auidlr_test5(6);
				break;
			case 304:
				ct_dd_audio_set_swapbyte_auidlr_test6(0);
				break;
			case 305:
				ct_dd_audio_set_swaphw_auodlr_test5(0);
				break;
			case 306:
				ct_dd_audio_set_swaphw_auodlr_test6(0);
				break;
			case 307:
				ct_dd_audio_set_swaphw_auodlr_test5(1);
				break;
			case 308:
				ct_dd_audio_set_swaphw_auodlr_test6(1);
				break;
			case 309:
				ct_dd_audio_set_swaphw_auodlr_test5(2);
				break;
			case 310:
				ct_dd_audio_set_swaphw_auodlr_test6(2);
				break;
			case 311:
				ct_dd_audio_set_swaphw_auodlr_test5(3);
				break;
			case 312:
				ct_dd_audio_set_swaphw_auodlr_test7(4);
				break;
			case 313:
				ct_dd_audio_set_swaphw_auodlr_test8(0);
				break;
			case 314:
				ct_dd_audio_set_swapbyte_auodlr_test5(0);
				break;
			case 315:
				ct_dd_audio_set_swapbyte_auodlr_test6(0);
				break;
			case 316:
				ct_dd_audio_set_swapbyte_auodlr_test5(1);
				break;
			case 317:
				ct_dd_audio_set_swapbyte_auodlr_test6(1);
				break;
			case 318:
				ct_dd_audio_set_swapbyte_auodlr_test5(2);
				break;
			case 319:
				ct_dd_audio_set_swapbyte_auodlr_test6(2);
				break;
			case 320:
				ct_dd_audio_set_swapbyte_auodlr_test5(3);
				break;
			case 321:
				ct_dd_audio_set_swapbyte_auodlr_test7(4);
				break;
			case 322:
				ct_dd_audio_set_swapbyte_auodlr_test8(0);
				break;
			case 323:
				ct_dd_audio_get_addr_reg_auidlr_test(3);
				break;
			case 324:
				ct_dd_audio_get_addr_reg_auidlr_test(6);
				break;
			case 325:
				ct_dd_audio_get_addr_reg_auodlr_test(4);
				break;
			case 326:
				ct_dd_audio_get_addr_reg_auidl_test(3);
				break;
			case 327:
				ct_dd_audio_get_addr_reg_auidl_test(6);
				break;
			case 328:
				ct_dd_audio_get_addr_reg_auidr_test(3);
				break;
			case 329:
				ct_dd_audio_get_addr_reg_auidr_test(6);
				break;
			case 330:
				ct_dd_audio_get_addr_reg_auodl_test(4);
				break;
			case 331:
				ct_dd_audio_get_addr_reg_auodr_test(4);
				break;
			case 332:
				ct_dd_audio_get_addr_reg_auiddmapt_test(3);
				break;
			case 333:
				ct_dd_audio_get_addr_reg_auiddmapt_test(6);
				break;
			case 334:
				ct_dd_audio_get_addr_reg_auoddmapt_test(4);
				break;
			case 335:
				ct_dd_audio_set_enable_input_intr_test9(0);
				break;
			case 336:
				ct_dd_audio_set_enable_input_intr_test10(0);
				break;
			case 337:
				ct_dd_audio_set_enable_input_intr_test9(1);
				break;
			case 338:
				ct_dd_audio_set_enable_input_intr_test10(1);
				break;
			case 339:
				ct_dd_audio_set_enable_input_intr_test9(2);
				break;
			case 340:
				ct_dd_audio_set_enable_input_intr_test10(2);
				break;
			case 341:
				ct_dd_audio_set_enable_input_intr_test9(4);
				break;
			case 342:
				ct_dd_audio_set_enable_input_intr_test10(4);
				break;
			case 343:
				ct_dd_audio_set_enable_input_intr_test9(5);
				break;
			case 344:
				ct_dd_audio_set_enable_input_intr_test10(5);
				break;
			case 345:
				ct_dd_audio_set_enable_input_intr_test11(3);
				break;
			case 346:
				ct_dd_audio_set_enable_input_intr_test11(6);
				break;
			case 347:
				ct_dd_audio_set_enable_input_intr_test12(0);
				break;
			case 348:
				ct_dd_audio_set_enable_output_intr_test9(0);
				break;
			case 349:
				ct_dd_audio_set_enable_output_intr_test10(0);
				break;
			case 350:
				ct_dd_audio_set_enable_output_intr_test9(1);
				break;
			case 351:
				ct_dd_audio_set_enable_output_intr_test10(1);
				break;
			case 352:
				ct_dd_audio_set_enable_output_intr_test9(2);
				break;
			case 353:
				ct_dd_audio_set_enable_output_intr_test10(2);
				break;
			case 354:
				ct_dd_audio_set_enable_output_intr_test9(3);
				break;
			case 355:
				ct_dd_audio_set_enable_output_intr_test10(3);
				break;
			case 356:
				ct_dd_audio_set_enable_output_intr_test11(4);
				break;
			case 357:
				ct_dd_audio_set_enable_output_intr_test12(0);
				break;
			case 358:
				ct_dd_audio_set_enable_in_over_flow_intr_test3(3);
				break;
			case 359:
				ct_dd_audio_set_enable_in_over_flow_intr_test3(6);
				break;
			case 360:
				ct_dd_audio_set_enable_in_over_flow_intr_test4(0);
				break;
			case 361:
				ct_dd_audio_set_enable_out_under_flow_intr_test3(4);
				break;
			case 362:
				ct_dd_audio_set_enable_out_under_flow_intr_test4(0);
				break;
			case 363:
				ct_dd_audio_get_input_fifo_status_test(3);
				break;
			case 364:
				ct_dd_audio_get_input_fifo_status_test(6);
				break;
			case 365:
				ct_dd_audio_get_output_fifo_status_test(4);
				break;
			case 366:
				ct_dd_audio_input_open_test5(0);
				break;
			case 367:
				ct_dd_audio_output_open_test5(0);
				break;
			default :
				Ddim_Print(("ddaudio : ERROR command line\n"));
				break;
		}
	}
	else if(atoi(argv[1]) == 3) {
		switch (atoi(argv[2])) {
			case 0:
				ct_dd_audio_3_reg_rw();
				break;
			case 1:
				ct_dd_audio_3_input_open_close(0);
				break;
			case 2:
				ct_dd_audio_3_input_open_close(1);
				break;
			case 3:
				ct_dd_audio_3_input_open_close(2);
				break;
			case 4:
				ct_dd_audio_3_input_open_close(4);
				break;
			case 5:
				ct_dd_audio_3_input_open_close(5);
				break;
			case 6:
				ct_dd_audio_3_output_open_close(0);
				break;
			case 7:
				ct_dd_audio_3_output_open_close(1);
				break;
			case 8:
				ct_dd_audio_3_output_open_close(2);
				break;
			case 9:
				ct_dd_audio_3_output_open_close(3);
				break;
			case 10:
				ct_dd_audio_3_init(0);
				break;
			case 11:
				ct_dd_audio_3_init(1);
				break;
			case 12:
				ct_dd_audio_3_init(2);
				break;
			case 13:
				ct_dd_audio_3_init(3);
				break;
			case 14:
				ct_dd_audio_3_init(4);
				break;
			case 15:
				ct_dd_audio_3_init(5);
				break;
			case 16:
				ct_dd_audio_3_update_input_setting(0);
				break;
			case 17:
				ct_dd_audio_3_update_input_setting(1);
				break;
			case 18:
				ct_dd_audio_3_update_input_setting(2);
				break;
			case 19:
				ct_dd_audio_3_update_input_setting(4);
				break;
			case 20:
				ct_dd_audio_3_update_input_setting(5);
				break;
			case 21:
				ct_dd_audio_3_update_output_setting(0);
				break;
			case 22:
				ct_dd_audio_3_update_output_setting(1);
				break;
			case 23:
				ct_dd_audio_3_update_output_setting(2);
				break;
			case 24:
				ct_dd_audio_3_update_output_setting(3);
				break;
			case 25:
				ct_dd_audio_3_reset_input_status(0);
				break;
			case 26:
				ct_dd_audio_3_reset_input_status(1);
				break;
			case 27:
				ct_dd_audio_3_reset_input_status(2);
				break;
			case 28:
				ct_dd_audio_3_reset_input_status(4);
				break;
			case 29:
				ct_dd_audio_3_reset_input_status(5);
				break;
			case 30:
				ct_dd_audio_3_reset_output_status(0);
				break;
			case 31:
				ct_dd_audio_3_reset_output_status(1);
				break;
			case 32:
				ct_dd_audio_3_reset_output_status(2);
				break;
			case 33:
				ct_dd_audio_3_reset_output_status(3);
				break;
			case 34:
				ct_dd_audio_3_start_stop_input(0);
				break;
			case 35:
				ct_dd_audio_3_start_stop_input(2);
				break;
			case 36:
				ct_dd_audio_3_start_stop_input(4);
				break;
			case 37:
				ct_dd_audio_3_start_stop_input(5);
				break;
			case 38:
				ct_dd_audio_3_start_stop_output(0);
				break;
			case 39:
				ct_dd_audio_3_start_stop_output(2);
				break;
			case 40:
				ct_dd_audio_3_start_stop_output(3);
				break;
			case 41:
				ct_dd_audio_3_041();
				break;
			case 42:
				ct_dd_audio_3_042();
				break;
			case 43:
				ct_dd_audio_3_043();
				break;
			case 44:
				ct_dd_audio_3_044();
				break;
			case 45:
				ct_dd_audio_3_045();
				break;
			case 46:
				ct_dd_audio_3_046();
				break;
			case 47:
				ct_dd_audio_3_047();
				break;
			case 48:
				ct_dd_audio_3_048();
				break;
			case 49:
				ct_dd_audio_3_049();
				break;
			case 50:
				ct_dd_audio_3_050();
				break;
			case 51:
				ct_dd_audio_3_051();
				break;
			case 52:
				ct_dd_audio_3_052();
				break;
			case 53:
				ct_dd_audio_3_053();
				break;
			case 54:
				ct_dd_audio_3_054();
				break;
			case 55:
				ct_dd_audio_3_055();
				break;
			case 56:
				ct_dd_audio_3_056();
				break;
			case 57:
				ct_dd_audio_3_057();
				break;
			case 58:
				ct_dd_audio_3_058();
				break;
			case 59:
				ct_dd_audio_3_059();
				break;
			case 60:
				ct_dd_audio_3_060();
				break;
			case 61:
				ct_dd_audio_3_061();
				break;
			case 62:
				ct_dd_audio_3_062();
				break;
			case 63:
				ct_dd_audio_3_063();
				break;
			case 64:
				ct_dd_audio_3_064();
				break;
			case 65:
				ct_dd_audio_3_065();
				break;
			case 66:
				ct_dd_audio_3_066();
				break;
			case 67:
				ct_dd_audio_3_067();
				break;
			case 68:
				ct_dd_audio_3_068();
				break;
			case 69:
				ct_dd_audio_3_069();
				break;
			case 70:
				ct_dd_audio_3_070();
				break;
			case 71:
				ct_dd_audio_3_071();
				break;
			case 72:
				ct_dd_audio_3_072();
				break;
			case 73:
				ct_dd_audio_3_073();
				break;
			case 74:
				ct_dd_audio_3_074();
				break;
			case 75:
				ct_dd_audio_3_075();
				break;
			case 76:
				ct_dd_audio_3_076();
				break;
			case 77:
				ct_dd_audio_3_077();
				break;
			case 78:
				ct_dd_audio_3_078();
				break;
			case 79:
				ct_dd_audio_3_079();
				break;
			case 80:
				ct_dd_audio_3_080();
				break;
			case 81:
				ct_dd_audio_3_081();
				break;
			case 82:
				ct_dd_audio_3_082();
				break;
			case 83:
				ct_dd_audio_3_083();
				break;
			case 84:
				ct_dd_audio_3_084();
				break;
			case 85:
				ct_dd_audio_3_085();
				break;
			case 86:
				ct_dd_audio_3_086();
				break;
			case 87:
				ct_dd_audio_3_087();
				break;
			case 88:
				ct_dd_audio_3_088();
				break;
			case 89:
				ct_dd_audio_3_089();
				break;
			case 90:
				ct_dd_audio_3_090();
				break;
			case 91:
				ct_dd_audio_3_091();
				break;
			case 92:
				ct_dd_audio_3_092();
				break;
			case 93:
				ct_dd_audio_3_093();
				break;
			case 94:
				ct_dd_audio_3_094();
				break;
			case 95:
				ct_dd_audio_3_095();
				break;
			case 96:
				ct_dd_audio_3_096();
				break;
			case 97:
				ct_dd_audio_3_097();
				break;
			case 98:
				ct_dd_audio_3_098();
				break;
			case 99:
				ct_dd_audio_3_099();
				break;
			case 100:
				ct_dd_audio_3_100();
				break;
			case 101:
				ct_dd_audio_3_101();
				break;
			case 102:
				ct_dd_audio_3_102();
				break;
			case 103:
				ct_dd_audio_3_103();
				break;
			case 104:
				ct_dd_audio_3_104();
				break;
			case 105:
				ct_dd_audio_3_105();
				break;
			case 106:
				ct_dd_audio_3_106();
				break;
			case 107:
				ct_dd_audio_3_107();
				break;
			case 108:
				ct_dd_audio_3_108();
				break;
			case 109:
				ct_dd_audio_3_109();
				break;
			case 110:
				ct_dd_audio_3_110();
				break;
			case 111:
				ct_dd_audio_3_111();
				break;
			case 112:
				ct_dd_audio_3_112();
				break;
			case 113:
				ct_dd_audio_3_113();
				break;
			case 114:
				ct_dd_audio_3_114();
				break;
			case 115:
				ct_dd_audio_3_115();
				break;
			case 116:
				ct_dd_audio_3_116();
				break;
			case 117:
				ct_dd_audio_3_117();
				break;
			case 118:
				ct_dd_audio_3_118();
				break;
			case 119:
				ct_dd_audio_3_119();
				break;
			case 120:
				ct_dd_audio_3_120();
				break;
			case 121:
				ct_dd_audio_3_121();
				break;
			case 122:
				ct_dd_audio_3_122();
				break;
			case 123:
				ct_dd_audio_3_123();
				break;
			case 124:
				ct_dd_audio_3_124();
				break;
			case 125:
				ct_dd_audio_3_125();
				break;
			case 126:
				ct_dd_audio_3_126();
				break;
			case 127:
				ct_dd_audio_3_127();
				break;
			case 128:
				ct_dd_audio_3_128();
				break;
			case 129:
				ct_dd_audio_3_129();
				break;
			case 130:
				ct_dd_audio_3_130();
				break;
			case 131:
				ct_dd_audio_3_131();
				break;
			default :
				Ddim_Print(("ddaudio : ERROR command line\n"));
				break;
		}
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "hdmi") ) {
		ct_dd_audio_3_hdmi();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "rec_monitor0_n") ) {
		ct_dd_audio_fifo_monitor_rec0_n();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "rec_monitor0") ) {
		ct_dd_audio_fifo_monitor_rec0();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "rec_monitor0_s") ) {
		ct_dd_audio_fifo_monitor_rec0_slave();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "rec_monitor1") ) {
		ct_dd_audio_fifo_monitor_rec1();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "rec_monitor1_s") ) {
		ct_dd_audio_fifo_monitor_rec1_slave();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "rec_monitor2_n") ) {
		ct_dd_audio_fifo_monitor_rec2_n();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "rec_monitor2") ) {
		ct_dd_audio_fifo_monitor_rec2();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "rec_monitor2_s") ) {
		ct_dd_audio_fifo_monitor_rec2_slave();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "rec_monitor3_n") ) {
		ct_dd_audio_fifo_monitor_rec3_n();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "rec_monitor3") ) {
		ct_dd_audio_fifo_monitor_rec3();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "rec_monitor3_s") ) {
		ct_dd_audio_fifo_monitor_rec3_slave();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor0_n") ) {
		ct_dd_audio_fifo_monitor_play0_n();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor0") ) {
		ct_dd_audio_fifo_monitor_play0();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor0_s") ) {
		ct_dd_audio_fifo_monitor_play0_slave();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor1") ) {
		ct_dd_audio_fifo_monitor_play1();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor1_s") ) {
		ct_dd_audio_fifo_monitor_play1_slave();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor2_n") ) {
		ct_dd_audio_fifo_monitor_play2_n();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor2") ) {
		ct_dd_audio_fifo_monitor_play2();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor2_s") ) {
		ct_dd_audio_fifo_monitor_play2_slave();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor3_n") ) {
		ct_dd_audio_fifo_monitor_play3_n();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor3") ) {
		ct_dd_audio_fifo_monitor_play3();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor3_s") ) {
		ct_dd_audio_fifo_monitor_play3_slave();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor0_d2") ) {
		ct_dd_audio_fifo_monitor_play0_D2();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor1_d2") ) {
		ct_dd_audio_fifo_monitor_play1_D2();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor2_d2") ) {
		ct_dd_audio_fifo_monitor_play2_D2();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "play_monitor3_d2") ) {
		ct_dd_audio_fifo_monitor_play3_D2();
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "bitshift") ) {
		ct_dd_audio_bit_shift((UINT16*)CT_DD_Audio_WORK_AREA , 0x1000000);
	}
	else if( (2 == argc) && !strcmp(argv[argc-1], "pdm_sync") ) {
		ct_dd_audio_sync_pdm();
	}
	else {
		Ddim_Print(("ddaudio : ERROR command line\n"));
	}

	Dd_CACHE_L1_Clean_Flush_Dcache_All();
	Dd_CACHE_L2_Clean_Flush_Dcache_All();

}

