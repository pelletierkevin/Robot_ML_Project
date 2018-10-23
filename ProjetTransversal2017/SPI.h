#ifndef SPI_H
#define SPI_H

#include <CFG_Globale.h>
#include "string.h"
#include "LIB_PROJET_T_Timers.h"


#define TAILLE_DATA 0x01
#define START_SPI 0x45
#define STOP_SPI 0x47
#define TIMEOUT_SLAVE_ACK 0x01
#define ACK_SLAVE_OK_STOP 0x99
#define ACK_SLAVE_KO_STOP 0x98
#define ACK_SLAVE_OK_START 0x97
#define ACK_SLAVE_OK_WRITE 0x96
#define PARITE_OK 0x04
#define PARITE_KO 0x05
#define SLAVE_SEND_OK 0x06

#define WRITE_TO_SLAVE 0x22
#define READ_FROM_SLAVE 0x23

enum SPI_Slave_State{WAITING,READ,WRITE,START,STOP,PARITY_CHECK};

void SPI0_Init_Master (void);
void SPI0_Init_Slave (void);
unsigned char  SPI_Read_Slave (void);

unsigned char SPI_Send_Master_Write (unsigned char write_commande, char *value);
unsigned char SPI_Send_Read_Master (unsigned char read_commande, char *value);
char* SPI_Read_Slave_From_Master (unsigned char value);
void SPI_Write_From_Master(unsigned char value);
unsigned char SPI_Write_From_Master_ACK_WAIT (unsigned char value);
unsigned char SPI_Send_From_Slave (unsigned char value);

unsigned char Parite_SPI(unsigned char value);
unsigned char calcul_bit(unsigned char value);
unsigned char Timeout_reception_SPI_Master(void);
unsigned char Timeout_spi_com(void);
void SYSCLK_Init (void);
void PORT_Init (void);

#endif