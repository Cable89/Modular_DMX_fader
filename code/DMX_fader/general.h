/*
 * general.h
 *
 * Created: 28.02.2015 14:51:40
 *  Author: Ole
 */ 


#ifndef GENERAL_H_
#define GENERAL_H_

//#define MASTER
#define SLAVE

#define ADDRESS_PORT PIND
#define A0 PD5
#define A1 PD6
#define A2 PD7
#define ADDRESS_MASK ( (1 << A0) | (1 << A1) | (1 << A2) )
#define ADDRESS_OFFSET A0

#endif /* GENERAL_H_ */