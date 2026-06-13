#ifndef CAN_H
#define CAN_H

#define CAN_QUEUE_SIZE 20

#define ENGINE_ECU_ID   0x100
#define BATTERY_ECU_ID  0x101
#define BRAKE_ECU_ID    0x102

typedef struct
{
    unsigned int id;

    unsigned char dlc;

    unsigned char data[8];

} CAN_Frame;

void can_init(void);

void can_send(CAN_Frame *frame);

int can_receive(CAN_Frame *frame);

#endif