#ifndef BSP_BUZZER_H
#define BSP_BUZZER_H

#include "stm32f1xx_hal.h"

#define  proport          72000 	//Tclk/(arr+1)=72000000/(1000)

//根据Tout= ((arr+1)*(psc+1))/Tclk推出psc值就是本句define定义的值，Tout为音调频率131Hz的倒数，Tclk=72MHz                                                
#define  L1       ((proport/262)-1)//中调　do 的频率
#define  L2       ((proport/296)-1)//中调　re 的频率
#define  L3       ((proport/330)-1)//中调　mi 的频率
#define  L4       ((proport/349)-1)//中调　fa 的频率
#define  L5       ((proport/392)-1)//中调　sol的频率
#define  L6       ((proport/440)-1)//中调　la 的频率
#define  L7       ((proport/494)-1)//中调　si 的频率
                                               
#define  M1       ((proport/523)-1)//高调　do 的频率
#define  M2       ((proport/587)-1)//高调　re 的频率
#define  M3       ((proport/659)-1)//高调　mi 的频率
#define  M4       ((proport/699)-1)//高调　fa 的频率
#define  M5       ((proport/784)-1)//高调　sol的频率
#define  M6       ((proport/880)-1)//高调　la 的频率
#define  M7       ((proport/988)-1)//高调　si 的频率

#define  H1       ((proport/1048)-1)//高调　do 的频率
#define  H2       ((proport/1176)-1)//高调　re 的频率
#define  H3       ((proport/1320)-1)//高调　mi 的频率
#define  H4       ((proport/1480)-1)//高调　fa 的频率
#define  H5       ((proport/1640)-1)//高调　sol的频率
#define  H6       ((proport/1760)-1)//高调　la 的频率
#define  H7       ((proport/1976)-1)//高调　si 的频率

#define  Z0       0//

void Solitary_brave(void);
void Wind_Rises(void);
void Wind_Rises1(void);
void Wind_Rises2(void);
void Wind_Rises3(void);

extern void buzzer_on(uint16_t psc, uint16_t pwm);
extern void buzzer_off(void);

#endif
