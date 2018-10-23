#include "SPI.h"


//-----------------------------------------------------------------------------
// SPI0_Init
//-----------------------------------------------------------------------------
//
// Configure SPI0 8-bit, 2MHz SCK, Maitre, interruption SPI0, front montant
sbit CS = P1^0;

void SPI0_Init_Master (void)
{
 SPI0CFG = 0x07; // DonnÃ©e lu sur premiere front montant horloge
 // 8-bit de donnÃ©es
 SPI0CN = 0x03; //Maitre; SPI actif; drapeau dÃ©sactivÃ©
 P0MDOUT |= 0x14; //MOSI SCLK en Push Pull
 P0MDOUT &= 0xF7;//MISO  Drain ouvert
 SPI0CKR = SYSCLK/2/2000000; // <= 2MHz 
	P4 = 0x01;
 //EIE1 |= 0x01; // active interruption du SPI SPI0 
}

void SPI0_Init_Slave (void)
{
	SPI0CFG = 0x07; // DonnÃ©e lu sur premiere front montant horloge
 // 8-bit de donnÃ©es
 SPI0CN = 0x01; //Esclave; SPI actif; drapeau dÃ©sactivÃ©
 P0MDOUT |= 0x08; //MISO en Push Pull
 P0MDOUT &= 0xCF;//MOSI NSS Drain ouvert	
 EIE1 |= 0x01; // active interruption du SPI SPI0 
	//RXOVRN = 1;
	

}
void PORT_Init (void)
{
   XBR0   |= 0x06;                     // Enable SPI0 and UART0
   XBR1    = 0x00;
   XBR2    = 0x40;                     // Enable crossbar and weak pull-ups
   P0MDOUT |= 0x15;                    // enable P0.0 (TX), P0.2 (SCK), and 
                                       // P0.4 (MOSI) as push-pull outputs 
   P1MDOUT |= 0xC0;                    // enable P1.6 (LED) and P1.7 (EE_CS)
                                       // as push-pull outputs
}

void SYSCLK_Init (void)
{
   int i;                              // delay counter
   OSCXCN = 0x67;                      // start external oscillator with
                                       // 22.1184 MHz crystal
   for (i=0; i < 256; i++) ;           // Wait for osc. to start up
   while (!(OSCXCN & 0x80)) ;          // Wait for crystal osc. to settle
   OSCICN = 0x88;                      // select external oscillator as SYSCLK
                                       // source and enable missing clock
                                       // detector
}

//_____________________________________________________________ECRITURE MAITRE____________________________________________________________________//
void SPI_Write_From_Master (unsigned char value)
{
		P4 = 0x00;//Activation du CS
		Timer0_us (10); // On attends deux cycles d'horloges du spi 
		SPI0DAT = value;
		while(TXBSY == 1);//Attente de la fin de l'envois
		P4 = 0x01;
		Timer0_us (1);//Desactivation CS
}

unsigned char SPI_Write_From_Master_ACK_WAIT (unsigned char value)
{
	unsigned char erreur = 0x00;
	P4 = 0x00;//Activation du CS
	Timer0_us (1); // On attends deux cycles d'horloges du spi 
	do{
			SPI0DAT = value;
			erreur = ACK_SLAVE_OK_STOP;//Timeout_reception_SPI_Master();
			while(TXBSY == 1);//Attente de la fin de l'envois
	}while (erreur==0x00);//Attente rÃ©ponse esclave
	P4 = 0x01;
	Timer0_us (1);//Attente lecture esclave
	return erreur;
}




unsigned char SPI_Send_Master_Write (unsigned char write_commande, char *value)
{
	unsigned char longeur_data;
	unsigned char nb_bit_parite=0x00;
	unsigned char erreur = 0x00;
 

	/*DÃ©but de Trame*/
	//Octet Start
	SPI_Write_From_Master(START_SPI);
		
	//Octet Commande
	SPI_Write_From_Master(write_commande);

	/*DonnÃ©e de Trame*/
	for(longeur_data = 0; longeur_data < strlen(value); longeur_data++)
	{		
			SPI_Write_From_Master(value[longeur_data]);
			nb_bit_parite +=calcul_bit(value[longeur_data]);
	}	
		 	
	/*Fin de Trame*/
	
	SPI_Write_From_Master(Parite_SPI(nb_bit_parite));
	

	
	//erreur = SPI_Write_From_Master_ACK_WAIT(STOP_SPI);//Verification de la rÃ©ception de l'octet par l'esclave


	
	return  erreur;
}




//_______________________________________________________________________LECTURE ESCLAVE________________________________________________________//

unsigned char  SPI_Read_Slave (void)
{
	unsigned char value = 0x00;
	
	value = SPI0DAT;
	
	return value;
}

unsigned char  SPI_Send_From_Slave (unsigned char value)
{
	unsigned char erreur = 0x00;
	//while (RXOVRN==1);
	SPI0DAT = value;
	erreur = Timeout_spi_com();
	while (TXBSY == 1 && erreur==0x00);
	
	return erreur;
}



//_______________________________________________________________________LECTURE MAITRE________________________________________________________//
char* SPI_Read_Slave_From_Master (unsigned char value)
{
		char* value_return;
		unsigned char erreur = 0x00;
	
		while(RXOVRN==0 && erreur == 0x00)
		{
			erreur = Timeout_spi_com();
		}
		value = SPI0DAT;
		while(TXBSY == 1);//Attente de la fin de l'envois
		
		return value_return;
}

unsigned char SPI_Send_Read_Master (unsigned char read_commande, char *value)
{
	//unsigned char longeur_data;
	unsigned char nb_bit_parite=0x00;
	unsigned char erreur = 0x00;
 
	

	/*DÃ©but de Trame*/
	//Octet Start
	SPI_Write_From_Master(START_SPI);
	
	//Octet Commande
	SPI_Write_From_Master(read_commande);
			 	
	/*Fin de Trame*/
 SPI_Write_From_Master(STOP_SPI);//Verification de la rÃ©ception de l'octet par l'esclave
	

	return  erreur;
}




unsigned char calcul_bit(unsigned char value)
{
	unsigned char Nb_bit_return ,i_bcl = 0;

	for (i_bcl=0; i_bcl<8; i_bcl++) 
  {
       if (value&(1<<i_bcl))//On effectue un et bit Ã  bit sur l'octet entier pour compter le nombre de bit Ã  1
			 {
				 ++Nb_bit_return;
			 }
  }
	
	return Nb_bit_return;
}



unsigned char Parite_SPI(unsigned char value)
{
	if(value%2==0)
		{
			return 0x01;
		}
	
	else
		{
			return 0x00;
		}
}

unsigned char Timeout_reception_SPI_Master(void)
{
		unsigned  char ack_slave = 0x00;

		if(RXOVRN==1)//Data arrivÃ© dans le buffer
		{
			RXOVRN = 0;
				if(SPI0DAT==ACK_SLAVE_OK_STOP)//DonnÃ©e recu et traitÃ© par l'esclave
				{
						ack_slave = ACK_SLAVE_OK_STOP;
				}
				else
				{
						ack_slave = ACK_SLAVE_KO_STOP;
				}
		}
		else //Aucune Reponse reÃ§u
		{
				if(Timeout_spi_com()==0)//Timeout Ã©coulÃ©
				{
						ack_slave = TIMEOUT_SLAVE_ACK;
				}
				else
				{
						ack_slave = 0x00;
				}
		}

		return ack_slave;
	
}



unsigned char Timeout_spi_com(void)
{
	unsigned char timeout  = 0x01;
	return timeout;
}

