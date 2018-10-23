                   // SFR declarations


#include "SPI.h"
#include "Timers.h"


//Var Globales
sbit BP = P3^7;// Bouton envois donnée
sbit LED = P1^6;

unsigned char global_data_spi = 0x00;//Donne recu sur le SPI
unsigned char global_data_for_master_spi = 0x05;//Donne recu sur le SPI
unsigned char global_parity_state = 0x01;
unsigned char global_cpt_write_to_slave = 0x00;
unsigned char global_cpt_read_from_slave = 0x00;
unsigned char global_cpt_start = 0x00;
unsigned char global_nb_parite_spi_slave = 0x00;//Nombre de bit à 1
unsigned char global_nb_octet_spi_recu = 0x00;//Nombre d'octet recu
static enum SPI_Slave_State Etat_SPI_BUS = WAITING;

//Prototype
void Oscillator_Init();
void Port_IO_Init();


void main(void) {
			
			WDTCN     = 0xDE;
			WDTCN     = 0xAD;
			EA = 1;
	
			//SPI TEST
			SYSCLK_Init();
			//SPI0_Init_Slave ();                     
			SPI0_Init_Master ();
			Port_IO_Init(); 
			
			LED=1;
	
while(1) 
	{
  SPI_Send_Master_Write(WRITE_TO_SLAVE,"s");
	/*	P4 = 0x00;
		Timer0_us(1);
		SPI_Write_From_Master(START_SPI);
		Timer0_us(100);	
		P4 = 0x01;
		Timer0_us(10);*/	
		
	}
}
 
/*
void SPI0_ISR(void) interrupt 6 
{
	
	switch(SPI0DAT)
	{
		case START_SPI: //Début de communication 
			Etat_SPI_BUS = START;
			break;
		
		case STOP_SPI: //Début de communication 
			Etat_SPI_BUS =STOP;
			break;
		
		case WRITE_TO_SLAVE: //Début de communication 
			Etat_SPI_BUS =WRITE;	
			break;
		
		case READ_FROM_SLAVE: //Début de communication 
			Etat_SPI_BUS =READ;
			break;

}
	
	
	
	
	
	

	if(Etat_SPI_BUS == START )
	{
		if(global_cpt_start==0)
		{
			global_nb_parite_spi_slave += calcul_bit(SPI0DAT);//Calcul de la parité
			SPI_Send_From_Slave(ACK_SLAVE_OK_START);
		}
			global_cpt_start++;

	}
	else if(Etat_SPI_BUS == WRITE)
	{
				global_nb_parite_spi_slave += calcul_bit(SPI0DAT);//Calcul de la parité
		
				if(global_cpt_write_to_slave==1)//Premier passage écriture fait on lit la data
				{
						global_data_spi = SPI0DAT;//On lit la donnée du maitre
						Etat_SPI_BUS = PARITY_CHECK;//On attend l'octet de parité
				}
				
				SPI_Send_From_Slave(ACK_SLAVE_OK_WRITE);
				global_cpt_write_to_slave++;
	}
	else if(Etat_SPI_BUS == READ)
	{
			if(global_cpt_read_from_slave==0)
			{
				global_nb_parite_spi_slave += calcul_bit(SPI0DAT);//Calcul de la parité)
			}
			else
			{
				Etat_SPI_BUS = PARITY_CHECK;//On attend l'octet de parité
			}
				SPI0DAT = global_data_for_master_spi;
				global_cpt_read_from_slave++;
	}
	else if(Etat_SPI_BUS == PARITY_CHECK)//Vérification de la parité
	{
			if(Parite_SPI(global_nb_parite_spi_slave)==SPI0DAT)//Parité OK
				{
						global_parity_state = 0x02;
				}
				else//Parité Mauvaise
				{
						global_parity_state = 0x01;
				}
	}
	else if(Etat_SPI_BUS == STOP )
	{
				if(global_parity_state==0x02)
				{
						SPI_Send_From_Slave(ACK_SLAVE_OK_STOP);
				}
				else if(global_parity_state==0x01)
				{
						SPI_Send_From_Slave(ACK_SLAVE_KO_STOP);
				}
				
				Etat_SPI_BUS = WAITING;
				global_cpt_start = 0;
				global_cpt_read_from_slave = 0;
				global_cpt_write_to_slave = 0;
				global_parity_state = 0x01;
	}
		SPIF = 0;
}*/








//Définition fonction
void Oscillator_Init()
{
    int i = 0;
    OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    OSCICN    = 0x0C;
}

void Port_IO_Init()
{

	
		P0MDOUT |= 0x01; // active P0.0 (TX), 
		P74OUT |= 0x01;																 
		P0MDOUT |= 0x40; // enable TX1 as a push-pull output
		XBR0      = 0x04;
		XBR0   |= 0x06;                     // Enable SPI0 and UART0
		XBR1    = 0x00;
		XBR2      = 0x40; // Enable crossbar and weak pull-ups
		XBR2 |= 0x44; //active uart1
	 P1MDOUT |= 0xC0;
		P3        |= 0x80;
}

