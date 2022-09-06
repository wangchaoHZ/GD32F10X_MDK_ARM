/*!
    \file    main.c
    \brief   ...

    \version 2022-09-07, V1.0.0, Demo Project for GD32F10x
*/

#include "gd32f10x.h"
#include "gd32f103c_start.h"
#include "systick.h"
#include "ulog.h"

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/

int main(void)
{
    systick_config();
    ulog_init();
    ulog_info("this is a demo project.");
}
