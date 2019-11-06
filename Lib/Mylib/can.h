#ifndef CAN_INIT_H
#define CAN_INIT_H
#include "common_defs.h"

#define OBD_REQ (uint16_t)0x7DF
#define OBD_ANS (uint16_t)0x7E8
#define SWA_REQ (uint16_t)0x797
#define SWA_ANS	(uint16_t)0x79F
#define ABS_REQ	(uint16_t)0x760
#define ABS_ANS	(uint16_t)0x768
#define TEST_ANS	(uint16_t)0x78
#define ENGINE_COOLANT_TEMP 0x05
#define ENGINE_RPM 0x0C
#define SPEED 0x0D
#define DROS 0x09

#define CAN_ENABLE_FILTERS 1

/* 
Частота 48Mhz 
Для изменения скорости достаточно изменить PSC.
Для 500Kb/s 6
Для 250Kb/s 12
Для 125Kb/s 24
*/
#define CAN_PSC 6
#define CAN_JW  2
#define CAN_SEG1 11
#define CAN_SEG2 4

/* Тестовый режим, без трансивера */
//#define CAN_TESTMODE 1

/* Организация памяти FDCAN */
#define FDCAN_START_AD (uint32_t)0x4000AC00
#define FDCAN_END_AD (uint32_t)0x4000D3FF
#define FDCAN_11B_FILTER_CNT 2
#define FDCAN_29B_FILTER_CNT 0
#define FDCAN_RXFIFO0_CNT 10
#define FDCAN_RXFIFO1_CNT 0
#define FDCAN_TX_EVENT_FIFO_CNT 0
#define FDCAN_TXFIFO_CNT 10

#define FDCAN_RXFIFO_HEAD 8 
#define FDCAN_RXFIFO_DATA_SIZE 8
#define FDCAN_RXFIFO_EL_SIZE (FDCAN_RXFIFO_HEAD+FDCAN_RXFIFO_DATA_SIZE)
#define FDCAN_RXFIFO_EL_W_SIZE (FDCAN_RXFIFO_EL_SIZE/4)

#define FDCAN_RXFIFO0_START (FDCAN_START_AD+FDCAN_11B_FILTER_CNT*4+FDCAN_29B_FILTER_CNT*4)
#define FDCAN_RXFIFO0_OFFSET (FDCAN_11B_FILTER_CNT+FDCAN_29B_FILTER_CNT)

#define FDCAN_TXFIFO_START (FDCAN_RXFIFO0_START+FDCAN_RXFIFO0_CNT*FDCAN_RXFIFO_EL_SIZE)
#define FDCAN_TXFIFO_OFFSET (FDCAN_RXFIFO0_OFFSET+FDCAN_RXFIFO0_CNT*4)

#define FDCAN_TXFIFO_HEAD 8 
#define FDCAN_TXFIFO_DATA_SIZE 8
#define FDCAN_TXFIFO_EL_SIZE (FDCAN_TXFIFO_HEAD+FDCAN_TXFIFO_DATA_SIZE)
#define FDCAN_TXFIFO_EL_W_SIZE (FDCAN_TXFIFO_EL_SIZE/4)


/* Тип фильтра */
#define FILTER_TYPE_RANGE 0
#define FILTER_TYPE_DUAL 1
#define FILTER_TYPE_CLASSIC 2
#define FILTER_TYPE_DISABLE 3

#define FILTER_STORE_FIFO0 1
#define FILTER_STORE_FIFO1 2
#define FILTER_REJECT 3

struct can_data_struct
{    
  uint16_t 	rpm;
  int16_t 	coolant_temp;
  uint8_t 	speed;
  uint8_t 	dros;
  uint32_t  iqr_call_count;
  uint32_t  iqr_call_rate;
  uint32_t  iqr_overall_call_count;
  uint32_t  iqr_overall_call_rate;
};

struct can_message
{
	uint16_t msg_id;
	uint8_t msg[8];
};

struct can_fifo_element
{
	uint32_t b0;
	uint32_t b1;
    uint32_t b2;
    uint32_t b3;
};



extern volatile struct can_data_struct can_data;
extern const struct can_message canreq_rpm;

void can1_init(void);
void cansend(struct can_message *msg);
void can_send_next(void);
void parse_msg(struct can_message *msg);
void get_msg(struct can_message* msg,uint8_t idx);
#endif
