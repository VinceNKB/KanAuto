#ifndef _GLOBAL_H
#define _GLOBAL_H

//#define _WIN32_WINNT 0x0501 //仅XP或以上系统有效 
#include <assert.h>
#include <string.h>
#include <windows.h>
#include <iostream>
#include <atlimage.h> 
#include <time.h>
//#include "stdafx.h"

extern HWND IESHwnd;
extern HWND KCVHwnd;
extern CCriticalSection critical_section;

extern time_t t_clock1;
extern time_t t_clock2;
extern time_t t_clock3;

extern bool isShift;
extern bool atkDlgOn;

extern volatile bool AtkOn;

extern volatile bool p_fakeMin;

extern volatile bool march1Run;
extern volatile bool march2Run;
extern volatile bool march3Run;

BOOL CALLBACK FindChildWnd(HWND hWnd, LPARAM lParam);

#define PICPATH "e://pic//"

#define ENTER_X 482
#define ENTER_Y 378
#define ENTER_W 50
#define ENTER_H 50
//开始游戏

#define HOME_NAME_X 109
#define HOME_NAME_Y 3
#define HOME_NAME_W 162
#define HOME_NAME_H 17
#define HOME_NAME_PID "id"
//提督名

#define HOME_SHIP_NUM_X 635
#define HOME_SHIP_NUM_Y 9
#define HOME_SHIP_NUM_W 35
#define HOME_SHIP_NUM_H 15
//舰队数量

#define HOME_BUCKET_NUM_X 691
#define HOME_BUCKET_NUM_Y 9
#define HOME_BUCKET_NUM_W 40
#define HOME_BUCKET_NUM_H 15
//桶数量

#define HOME_CONSTRU_NUM_X 753
#define HOME_CONSTRU_NUM_Y 9
#define HOME_CONSTRU_NUM_W 43
#define HOME_CONSTRU_NUM_H 15
//开发资材数量

#define HOME_ATTACK_X 156
#define HOME_ATTACK_Y 221
#define HOME_ATTACK_W 80
#define HOME_ATTACK_H 88
#define HOME_ATTACK_PID "home_attack"
//主界面出击按钮

#define HOME_ARMY_X 165
#define HOME_ARMY_Y 103
#define HOME_ARMY_W 66
#define HOME_ARMY_H 59
#define HOME_ARMY_PID "home_army"
//主界面编成按钮

#define HOME_MODIFY_X 286
#define HOME_MODIFY_Y 189
#define HOME_MODIFY_W 58
#define HOME_MODIFY_H 61
#define HOME_MODIFY_PID "home_modify"
//主界面改造按钮

#define HOME_FACTORY_X 240
#define HOME_FACTORY_Y 331
#define HOME_FACTORY_W 58
#define HOME_FACTORY_H 64
#define HOME_FACTORY_PID "home_factory"
//主界面工厂按钮

#define HOME_REPAIR_X 94
#define HOME_REPAIR_Y 329
#define HOME_REPAIR_W 55
#define HOME_REPAIR_H 65
#define HOME_REPAIR_PID "home_repair"
//主界面修理按钮

#define HOME_FOOD_X 48
#define HOME_FOOD_Y 191
#define HOME_FOOD_W 57
#define HOME_FOOD_H 63
#define HOME_FOOD_PID "home_food"
//主界面补给按钮

#define FUNC_ARMY_X 4
#define FUNC_ARMY_Y 133
#define FUNC_ARMY_W 36
#define FUNC_ARMY_H 37
#define FUNC_ARMY_PID "func_army"
//编成界面按钮

#define FUNC_FOOD_X 4
#define FUNC_FOOD_Y 185
#define FUNC_FOOD_W 36
#define FUNC_FOOD_H 37
#define FUNC_FOOD_PID "func_food"
//补给界面按钮


#define FUNC_MODIFY_X 4
#define FUNC_MODIFY_Y 241
#define FUNC_MODIFY_W 36
#define FUNC_MODIFY_H 37
#define FUNC_MODIFY_PID "func_modify"
//改造界面按钮

#define FUNC_REPAIR_X 4
#define FUNC_REPAIR_Y 294
#define FUNC_REPAIR_W 36
#define FUNC_REPAIR_H 37
#define FUNC_REPAIR_PID "func_repair"
//修理界面按钮


#define FUNC_FACTORY_X 4
#define FUNC_FACTORY_Y 347
#define FUNC_FACTORY_W 36
#define FUNC_FACTORY_H 37
#define FUNC_FACTORY_PID "func_factory"
//工厂界面按钮


#define FOOD_FLEET_ALL_X 113
#define FOOD_FLEET_ALL_Y 162
#define FOOD_FLEET_ALL_W 10
#define FOOD_FLEET_ALL_H 10
#define FOOD_FLEET_ALL_ENABLE "food_fleet_all_enable"
#define FOOD_FLEET_ALL_DISABLE "food_fleet_all_disable"
//团队补给选项

#define FOOD_FLEET_BUTTON_X 658
#define FOOD_FLEET_BUTTON_Y 425
#define FOOD_FLEET_BUTTON_W 87
#define FOOD_FLEET_BUTTON_H 30
#define FOOD_FLEET_BUTTON_ENABLE "food_fleet_button_enable"
#define FOOD_FLEET_BUTTON_DISABLE "food_fleet_button_disable"
//补给按钮

#define MARCH_RETURN_X 500
#define MARCH_RETURN_Y 12
#define MARCH_RETURN_W 232
#define MARCH_RETURN_H 30
//远征归来的标志

//#define MARCH_RETURN_SU_X 781
//#define MARCH_RETURN_SU_Y 457
//#define MARCH_RETURN_SU_W 40
//#define MARCH_RETURN_SU_H 40
//#define MARCH_RETURN_SU_PID "marchreturnsuccesstag"
////远征归来界面 单击两次


#define MARCH_CHOOSE_X 618
#define MARCH_CHOOSE_Y 148
#define MARCH_CHOOSE_W 129
#define MARCH_CHOOSE_H 166
#define MARCH_CHOOSE_PID "marchbutton"
//出击界面的远征按钮

#define MARCH_NO1_X 117
#define MARCH_NO1_Y 158
#define MARCH_NO_W 440
#define MARCH_NO_H 30
#define MARCH_LIST_NUM 8
#define MARCH_NO1_PID "marchno1"
//选远征号

#define MARCH_GO_X 643
#define MARCH_GO_Y 428
#define MARCH_GO_W 74
#define MARCH_GO_H 33
//选定远征no后单击决定或已有远征不能进行

#define MARCH_GO_CONFIRM_X 474
#define MARCH_GO_CONFIRM_Y 102
#define MARCH_GO_CONFIRM_W 79
#define MARCH_GO_CONFIRM_H 22
#define MARCH_GO_CONFIRM_PID "marchgoconfirm"
//确定是否在远征界面中



#define MARCH_GO5_X 630
#define MARCH_GO5_Y 121
#define MARCH_GO5_W 50
#define MARCH_GO5_H 14
//开始远征第二确认界面,用于确认

#define MARCH_GO3_X 570
#define MARCH_GO3_Y 427
#define MARCH_GO3_W 123
#define MARCH_GO3_H 37
//开始远征第二确认界面按钮


#define MARCH_NEED_YOU1_X 474
#define MARCH_NEED_YOU1_Y 169
#define MARCH_NEED_YOU2_X 474
#define MARCH_NEED_YOU2_Y 219
#define MARCH_NEED_YOU3_X 474
#define MARCH_NEED_YOU3_Y 269
#define MARCH_NEED_YOU4_X 474
#define MARCH_NEED_YOU4_Y 319
#define MARCH_NEED_YOU5_X 474
#define MARCH_NEED_YOU5_Y 369
#define MARCH_NEED_YOU6_X 474
#define MARCH_NEED_YOU6_Y 419
#define MARCH_NEED_YOU_W 8
#define MARCH_NEED_YOU_H 9



#define MARCH_NEED_DAN1_X 505
#define MARCH_NEED_DAN1_Y 167
#define MARCH_NEED_DAN2_X 474
#define MARCH_NEED_DAN2_Y 217
#define MARCH_NEED_DAN3_X 474
#define MARCH_NEED_DAN3_Y 267
#define MARCH_NEED_DAN4_X 474
#define MARCH_NEED_DAN4_Y 317
#define MARCH_NEED_DAN5_X 474
#define MARCH_NEED_DAN5_Y 367
#define MARCH_NEED_DAN6_X 474
#define MARCH_NEED_DAN6_Y 417
#define MARCH_NEED_DAN_W 2
#define MARCH_NEED_DAN_H 10

#define MARCH_GO_CONFIRM2_X 563 
#define MARCH_GO_CONFIRM2_Y 169
#define MARCH_GO_CONFIRM2_W 14
#define MARCH_GO_CONFIRM2_H 121
//

#define BACK_X 6
#define BACK_Y 6
#define BACK_W 6
#define BACK_H 6
//回港

#define NEXT_X 749
#define NEXT_Y 429
#define NEXT_W 28
#define NEXT_H 29
//次



#define HOME_CONFIRM_X 764
#define HOME_CONFIRM_Y 439
#define HOME_CONFIRM_W 23
#define HOME_CONFIRM_H 21
//右下角的设置按钮

#define HOME_BUTTON_X 0
#define HOME_BUTTON_Y 0
#define HOME_BUTTON_W 90
#define HOME_BUTTON_H 90
//左上角的圆

#define MARCH_GO6_X 631
#define MARCH_GO6_Y 431
#define MARCH_GO6_W 150
#define MARCH_GO6_H 29

#define MARCH_RETURN1_X 153
#define MARCH_RETURN1_Y 203
#define MARCH_RETURN1_W 136
#define MARCH_RETURN1_H 62
//远征返回(成功、失败)的“远征”二字

#define MARCH_SHIP_NO_CHECK2_X 389
#define MARCH_SHIP_NO_CHECK2_Y 113
#define MARCH_SHIP_NO_CHECK2_W 12
#define MARCH_SHIP_NO_CHECK2_H 12

#define MARCH_SHIP_NO_CHECK3_X 419
#define MARCH_SHIP_NO_CHECK3_Y 113
#define MARCH_SHIP_NO_CHECK3_W 12
#define MARCH_SHIP_NO_CHECK3_H 12

#define MARCH_SHIP_NO_CHECK4_X 450
#define MARCH_SHIP_NO_CHECK4_Y 114
#define MARCH_SHIP_NO_CHECK4_W 12
#define MARCH_SHIP_NO_CHECK3_H 12


#define SUPPLY_CHECK_X 620
#define SUPPLY_CHECK_Y 108
#define SUPPLY_CHECK_W 164
#define SUPPLY_CHECK_H 27
//确认当前界面是不是补给界面


#define SUPPLY_SHIP_NO_CHECK1_X 139
#define SUPPLY_SHIP_NO_CHECK1_Y 111
#define SUPPLY_SHIP_NO_CHECK1_W 19
#define SUPPLY_SHIP_NO_CHECK1_H 17

#define SUPPLY_SHIP_NO_CHECK2_X 170
#define SUPPLY_SHIP_NO_CHECK2_Y 111
#define SUPPLY_SHIP_NO_CHECK2_W 18
#define SUPPLY_SHIP_NO_CHECK2_H 18

#define SUPPLY_SHIP_NO_CHECK3_X 201
#define SUPPLY_SHIP_NO_CHECK3_Y 113
#define SUPPLY_SHIP_NO_CHECK3_W 13
#define SUPPLY_SHIP_NO_CHECK3_H 15

#define SUPPLY_SHIP_NO_CHECK4_X 232
#define SUPPLY_SHIP_NO_CHECK4_Y 114
#define SUPPLY_SHIP_NO_CHECK4_W 13
#define SUPPLY_SHIP_NO_CHECK4_H 13




#define ATTACK_BUTTON_CHOOSE_X 170
#define ATTACK_BUTTON_CHOOSE_Y 146
#define ATTACK_BUTTON_CHOOSE_W 118
#define ATTACK_BUTTON_CHOOSE_H 164

#define ATTACK_AREA_CHECK_X 127
#define ATTACK_AREA_CHECK_Y 110
#define ATTACK_AREA_CHECK_W 197
#define ATTACK_AREA_CHECK_H	18

#define ATTACK_AREA1_X 127
#define ATTACK_AREA1_Y 446
#define ATTACK_AREA1_W 55
#define ATTACK_AREA1_H 12

#define ATTACK_AREA2_X 203
#define ATTACK_AREA2_Y 446
#define ATTACK_AREA2_W 52
#define ATTACK_AREA2_H 12

#define ATTACK_AREA3_X 283
#define ATTACK_AREA3_Y 448
#define ATTACK_AREA3_W 51
#define ATTACK_AREA3_H 11

#define ATTACK_AREA4_X 352
#define ATTACK_AREA4_Y 447
#define ATTACK_AREA4_W 50
#define ATTACK_AREA4_H 12

#define ATTACK_AREA5_X 427
#define ATTACK_AREA5_Y 446
#define ATTACK_AREA5_W 50
#define ATTACK_AREA5_H 13

#define ATTACK_AREA6_X 504
#define ATTACK_AREA6_Y 448
#define ATTACK_AREA6_W 50
#define ATTACK_AREA6_H 11

#define ATTACK_AREAEX_X 690
#define ATTACK_AREAEX_Y 249
#define ATTACK_AREAEX_W 45
#define ATTACK_AREAEX_H 53
//红三角

#define ATTACK_AREACONFIRM_X 647
#define ATTACK_AREACONFIRM_Y 426
#define ATTACK_AREACONFIRM_W 78
#define ATTACK_AREACONFIRM_H 35

#define ATTACK_OUT_BUTTOM_X 560
#define ATTACK_OUT_BUTTOM_Y 428
#define ATTACK_OUT_BUTTOM_W 139
#define ATTACK_OUT_BUTTOM_H 35

#define ATK_CHOOSE_ZHENXING_X 440
#define ATK_CHOOSE_ZHENXING_Y 405
#define ATK_CHOOSE_ZHENXING_W 66
#define ATK_CHOOSE_ZHENXING_H 18

#define ATK_ZHENGXING_CHOOSE1_X 400 
#define ATK_ZHENGXING_CHOOSE1_Y 173
#define ATK_ZHENGXING_CHOOSE1_W 94
#define ATK_ZHENGXING_CHOOSE1_H 23

#define ATK_ZHENGXING_CHOOSE2_X 530
#define ATK_ZHENGXING_CHOOSE2_Y 173
#define ATK_ZHENGXING_CHOOSE2_W 94
#define ATK_ZHENGXING_CHOOSE2_H 23

#define ATK_ZHENGXING_CHOOSE3_X 662
#define ATK_ZHENGXING_CHOOSE3_Y 173
#define ATK_ZHENGXING_CHOOSE3_W 94
#define ATK_ZHENGXING_CHOOSE3_H 23

#define ATK_ZHENGXING_CHOOSE4_X 468
#define ATK_ZHENGXING_CHOOSE4_Y 332
#define ATK_ZHENGXING_CHOOSE4_W 94
#define ATK_ZHENGXING_CHOOSE4_H 23

#define ATK_ZHENGXING_CHOOSE5_X 599
#define ATK_ZHENGXING_CHOOSE5_Y 332
#define ATK_ZHENGXING_CHOOSE5_W 94
#define ATK_ZHENGXING_CHOOSE5_H 23


#define ATK_RUYE_CHOOSE_X 40
#define ATK_RUYE_CHOOSE_Y 31
#define ATK_RUYE_CHOOSE_W 86
#define ATK_RUYE_CHOOSE_H 21

#define ATK_LV_X 234
#define ATK_LV_Y 87
#define ATK_LV_W 17
#define ATK_LV_H 12

#define ATK_GETSHIP_X 747
#define ATK_GETSHIP_Y 427
#define ATK_GETSHIP_W 27
#define ATK_GETSHIP_H 27

#define ATK_CONTINUE_X 258
#define ATK_CONTINUE_Y 211
#define ATK_CONTINUE_W 74
#define ATK_CONTINUE_H 57


#define ATK_NEXT_X 739
#define ATK_NEXT_Y 418
#define ATK_NEXT_W 27
#define ATK_NEXT_H 27

#define ATK_NEXT2_X 745
#define ATK_NEXT2_Y 423
#define ATK_NEXT2_W 16
#define ATK_NEXT2_H 17

#define ATK_ZHUIJI_X 265
#define ATK_ZHUIJI_Y 210
#define ATK_ZHUIJI_W 55 
#define ATK_ZHUIJI_H 64

#define ATK_LV2_X 270
#define ATK_LV2_Y 87
#define ATK_LV2_W 16
#define ATK_LV2_H 12

#define ATK_LV3_X 270
#define ATK_LV3_Y 87
#define ATK_LV3_W 17
#define ATK_LV3_H 12

#define ATK_LUOPAN_X 289
#define ATK_LUOPAN_Y 172
#define ATK_LUOPAN_W 43
#define ATK_LUOPAN_H 101

#endif