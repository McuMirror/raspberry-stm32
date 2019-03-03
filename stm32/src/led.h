/******************************************************************************

  Copyright (C), 2019-2029, DIY Co., Ltd.

 ******************************************************************************
  File Name     : led.h
  Version       : Initial Draft
  Author        : Juven
  Created       : 2019/2/26
  Last Modified :
  Description   : led header
  Function List :
  History       :
  1.Date        : 2019/2/26
    Author      : Juven
    Modification: Created file

******************************************************************************/

#ifndef __LED_H
#define __LED_H

#include "sys.h"

//LED �˿ڶ���

#define LED PAout(4)  

void led_init(void);  //��ʼ��

void led_flash(u16 time);

#endif
