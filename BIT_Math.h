/*
 * BIT_Math.h
 *
 * Created: 10/2/2023 8:43:06 PM
 *  Author: M Osama
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT)       (REG |= (1<<BIT))
#define CLR_BIT(REG,BIT)       (REG &= (~(1<<BIT)))
#define TOG_BIT(REG,BIT)       (REG ^= (1<<BIT))
#define READ_BIT(REG,BIT)      ((REG & (1<<BIT))>>BIT)




#endif /* BIT_MATH_H_ */