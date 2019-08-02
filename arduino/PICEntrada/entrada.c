/* TMU COMBO   220 II - 675 con condicionales*/
#include <p18f252.h>
#include <i2c.h>

#define F2520 1
 
//#define  PF220   1
// #define	PF250	1  // ajuntar a 220 para que furule
// #define	PF675	1
//#define	PF950	1
#define	PF300	1
//#define PARSER  1 //paralelo como serial alterado.
#define CERO 0
#define UNO 1

//****************************** Definiciones   **************************
//version 070129
#define   VERSION 	'2'
#define   REVISION 	'4'

#ifdef F2520

#pragma romdata CONFIG
  const rom unsigned char _configuration[14] = { \
    0xFF, \
    0x02, \
    0x06, \
    0x0E, \
    0xFF, \
    0x81, \
    0x81, \
    0xFF, \
    0x00, \
    0xC0, \
    0x0F, \
    0xC0, \
    0x0F, \
    0x40 \
  };
#pragma romdata

#else

#pragma romdata CONFIG
  const rom unsigned char _configuration[14] = { \
    0xFF, \
     0x22, \
     0x02, \
     0x0E, \
    0xFF, \
     0x81, \
     0x81, \
    0xFF, \
     0x00, \
     0xC0, \
     0x0F, \
     0xC0, \
     0x0F, \
     0x40 \
  };
#pragma romdata

#endif

//comunicacion serial
#define Set_Async_Mode  TXSTAbits.SYNC = 0
#define Set_8bit_Tx     TXSTAbits.TX9 = 0
#define Enable_Tx       TXSTAbits.TXEN = 1
#define Set_Serial_Pins RCSTAbits.SPEN = 1
#define Set_8bit_Rx     RCSTAbits.RX9 = 0
#define Enable_Rx       RCSTAbits.CREN = 1
#define Activa_Rx		RCSTAbits.CREN = 1
#define Inactiva_Rx		RCSTAbits.CREN = 0
#define Error_Ferr		RCSTAbits.FERR
#define Error_Over		RCSTAbits.OERR

//watch dog timer
#define Activa_WDT		WDTCON = 1
#define Inactiva_WDT	WDTCON = 0
#define TOBIT			RCONbits.TO

//IIC definiciones
#define _SDA			PORTCbits.RC4
#define _SCL			PORTCbits.RC3
#define sda				PORTC,4
#define scl				PORTC,3
#define SDA_SALIDA      TRISC = 0b11100001
#define SDA_ENTRADA     TRISC = 0b11110001
#define I2C_ENTRADA		TRISC = 0b11111001
#define Velocidad_I2C	SSPADD 

//direcciones i2c
#define RAM		0b11010000	//define la memoria de trabajo
#define ROM		0b10100000 	//define primer banco de memoria fiscal
#define ROM2	0B10100100	//define segundo banco de memoria fiscal

//valores
#define LF 			10
#define CR 			13
#define CN 			11		//este valor se puede variar
#define CONT		0
#define ESC 		27
#define STX 		2
#define ETX 		3
#define FIELD		28
#define ACK		putchar(0x12)

//puerto paralelo definiciones

#define RXA			PORTAbits.RA5
#define TXA			PORTAbits.RA4
#define IMP_RESET	PORTAbits.RA3

//puerto serie definiciones
#ifndef PARSER
#define TX_SERIE	PORTCbits.RC1
#else
#define TX_SERIE	PORTBbits.RB0
#endif
#ifdef PARSER
#define BUSY_SERIE	PORTBbits.RB7
#else
//puerto paralelo definiciones
#define BUSY_SERIE	PORTCbits.RC0
#endif

#define DTR_SERIE	PORTCbits.RC2
#define RC_232		PORTCbits.RC7

//definiciones de jumpers
#define JUMP1		PORTAbits.RA0
#define JUMP2		PORTAbits.RA1
#define COLISION    SSPCON1bits.WCOL
#define COLISION2   PIR2bits.BCLIF

//*********************** Variables y Constantes   ***********************
//variables globales

unsigned char cad[80];
unsigned char ncampos[20];
unsigned char DATOS[50];	
unsigned char  	aux, aux1, aux2;
unsigned char  	max, min;
unsigned char	S1, S2, S3, S4;
unsigned int   	contador, inicio, fin;
//para total - para el CHECK de la ROM - RAM
unsigned char 	e;
//bits de error para W_ROM
unsigned char bit_error1, bit_error2;
//fecha de documentos
unsigned char dd, mm, aa;
unsigned char hh, mi;

//*********************** Prototipo de Funciones *************************
//funcion principal
//funciones generales
void DELAY_VAR(void);
void CONFIGURA(void);
void putchar(unsigned char Byte);
void puts(const rom char *s);
unsigned char getchar(void);
void putchar_imp(unsigned char dato);
//void putchar_aud(unsigned char dato);
void puts_imp(const rom char *s);
//funciones II2C generales
void START_I2C(void);
void STOP_I2C(void);
void WI2C(unsigned char valor);
unsigned char RI2C (void);
//funciones II2C basicas
void R_COMANDO(void);
void LINEAI2C(void);
void RAM_INICIO(void);
void R_RAM(unsigned char inicio);
void W_RAM(unsigned char inicio);
void ROM_INICIO(unsigned char fast2);
void R_ROM(unsigned char fast);
void W_ROM(unsigned char tipo);
//unsigned char VERIFICA_FISCALIZA(void);
 #define SYS_FREQ        (110560000)
 
//*********************** Funciones Generales ****************************
//--------------------------------------------------------------------------------
//	Rutina DELAYI2C
//	021115
//--------------------------------------------------------------------------------
void DELAYI2C (void){
	ClrWdt();
	INTCONbits.TMR0IF = 0;
	while(!INTCONbits.TMR0IF);
}

//------------------------------------------------------------------------
//	Rutina DELAY_VAR
//	genera un retardo fijo
//-----------------------------------------------------------------------
void DELAY_VAR(void){
unsigned char daux;
daux= 250;
while(daux>0){
	ClrWdt();
	TMR0L = 264 - 200;
	DELAYI2C();
	daux--;};
}

//-----------------------------------------------------------------------
//	Rutina DELAY_VAR2
//	genera un retordo variable ciclos * DELAYVAR()
//-----------------------------------------------------------------------
void DELAY_VAR2(unsigned char ciclos){
for(aux=0; aux< ciclos; aux++) DELAY_VAR();
}

//-----------------------------------------------------------------------
//	Rutina CONFIGURA
//	configura el I/O, los timer y la comunicación serial
//-----------------------------------------------------------------------
void CONFIGURA(void){
//configura la comunicacion serial
SPBRG = 17;			//9600bps @ 11.0958MHz
Set_Async_Mode;		//modo asincronico
Enable_Tx;			//activa transmision
Set_8bit_Tx;		//transmitir 8 bit
//Enable_Rx;		//activa recepcion
Set_8bit_Rx;		//recibir 8 bit
Set_Serial_Pins;	//activar pines del UART
#ifdef F2520
ADCON1 = 0b00001111; 	//todos los puertos de salida // antes 111
#else
ADCON1 = 0b00000111; 	//todos los puertos de salida // antes 111
#endif
TRISA=0b00100111;
//TRISA = 0b11100111;		//configuracion para el puerto paralelo
			//todos B de salida
I2C_ENTRADA;			//configura el puerto C con el bus I2C
#ifdef PARSER	
	TRISB = 0b00000001; 	//todos B de salida menos ultimo entrada DTR
#else
    TRISB = 0; 				//garantiza estado puerto estado inactivo
#endif
TX_SERIE = UNO;
DTR_SERIE = 0;			//garantiza estado puerto 232 HAND CHEKING pin 20 DMB25
//configura el timer 0
T0CONbits.T08BIT= 1;	//8 bits
T0CONbits.T0CS = 0;		//Timer0 como timer
T0CONbits.PSA = 1;		//sin prescaler
T0CONbits.TMR0ON = 1;   //activa timer 0
INTCON = 0;				//Desactiva todas las interrupciones y limp. el flag del timer0
//realiza un reset para el puerto paralelo de la impresora
//valores del puerto paralelo por defecto
}

//----------------------------------------------------------------------
//	Rutina putchar
//	envia un caracter al PC
//-----------------------------------------------------------------------
void putchar(unsigned char Byte){
while(!PIR1bits.TXIF);
TXREG = Byte;
PIR1bits.TXIF = 0;
ClrWdt();
}
//-----------------------------------------------------------------------
//	Rutina puts
//	envia una cadena de carcteres a PC
//-----------------------------------------------------------------------
void puts(const rom char *s){
while(*s){
	putchar(*s);
    s++;};
}

//-----------------------------------------------------------------------
//	Rutina put_LF
//	envia un LF a la impresora
//-----------------------------------------------------------------------
void put_LF(void){
	putchar_imp(LF);
}

//----------------------------------------------------------------------
//	Rutina putchar_imp
//	envia un caracter a la impresora en formato rs232 o paralelo
//	velocidad serial 9600 bps @ 11.0598MHz
//-----------------------------------------------------------------------
void putchar_imp(unsigned char dato){
unsigned char m, txbit;
ClrWdt();
m =0;
//esto determina si la impresora esta ocupada
#ifdef PARSER
while((!BUSY_SERIE)&&(m<240)){  //&&(BUSY)
#else
while((BUSY_SERIE)&&(m<240)){  //&&(BUSY)
#endif  
	if(m==150) ClrWdt();
	if(m==75) ClrWdt();
	for(txbit= 0; txbit<150; txbit++){TMR0L = 1; DELAYI2C();};
	m++;};

TX_SERIE= CERO;

TMR0L = 0;
	DELAYI2C();
TMR0L = 250;
	DELAYI2C();
m=8;
while(m>0){
  txbit= dato&(0x01);
//#ifdef PARSER
//  TX_SERIE= !txbit;
//#else
  TX_SERIE= txbit;
//#endif
  dato= dato>>1;
  TMR0L = 1;
  DELAYI2C();
  m--;
};
//bit de stop
//fin seg puerto paralelo
TMR0L = 250;
DELAYI2C();
//seg puerto paralelo
TX_SERIE= UNO;

TMR0L = 0;
DELAYI2C();
return;
}
//-----------------------------------------------------------------------
//	Rutina puts_LF
//	envia varios caracteres a la impresora
//-----------------------------------------------------------------------
void puts_LF(unsigned char cantidad, unsigned char tipo){
aux= tipo;
while(cantidad>0){
	putchar_imp(aux);
	cantidad--;};
}
//-----------------------------------------------------------------------
//	Rutina puts_BN
//	envia varios espacios a la impresora
//-----------------------------------------------------------------------
void puts_BN(unsigned char cantidad){
static unsigned char aux_cantidad;
aux_cantidad= cantidad;
	while(aux_cantidad> 0){
		putchar_imp(' ');
		aux_cantidad--;};
}
//-----------------------------------------------------------------------
//	Rutina puts_imp
//	envia una cadena de caracteres a la impresora
//-----------------------------------------------------------------------
void puts_imp(const rom char *s){
while(*s){
	putchar_imp(*s);
    	s++;};
}
//AQUI ESTABA PUT_LF

//-----------------------------------------------------------------------
//	Rutina put_ESC
//	envia un ESC a la impresora
//-----------------------------------------------------------------------
void put_ESC(void){
	putchar_imp(ESC);
}
//-----------------------------------------------------------------------
//	Rutina put_CR
//	envia un CR a la impresora
//-----------------------------------------------------------------------
void put_CR(void){
	putchar_imp(CR);
}
//-----------------------------------------------------------------------
//	Rutina PRINT_DATO
//	imprime un valor comprimido en la cadena datos
//-----------------------------------------------------------------------
void PRINT_DATO(unsigned char num){
static unsigned char i, j;
//020701
j= DATOS[num];
i= j>>4; 	i= i&0x0f; 	i+= 0x30; 	putchar_imp(i);
i= j;		i= i&0x0f; 	i+= 0x30; 	putchar_imp(i);
}

//*********************** funciones II2C generales *******************************

//--------------------------------------------------------------------------------
//	Rutina verI2C
//	fuerza condicion de start en protocolo I2C
//--------------------------------------------------------------------------------
void verI2C(void ){
	ClrWdt();
//	if(COLISION!= 0) DETENER_EJECUCION(114);
//	if(COLISION2!= 0) DETENER_EJECUCION(115);
}

//--------------------------------------------------------------------------------
//	Rutina START_I2C
//	fuerza condicion de start en protocolo I2C
//--------------------------------------------------------------------------------
void START_I2C(void){
	ClrWdt();
	OpenI2C(MASTER, SLEW_ON);		//ABRE EL PUERTO
	Velocidad_I2C = 100;			//maximo 127
	DELAY_VAR();
	StartI2C();
	IdleI2C();		//Espera reconocimiento del esclavo
	verI2C();
}

//--------------------------------------------------------------------------------
//	Rutina STOP_I2C
//	fuerza condicion de stop en protocolo I2C
//--------------------------------------------------------------------------------
void STOP_I2C(void){
	StopI2C();
	IdleI2C();
	CloseI2C();
}

//--------------------------------------------------------------------------------
//	Rutina WI2C
//	escribe un byte en protocolo I2C
//--------------------------------------------------------------------------------
void WI2C(unsigned char valor){
	ClrWdt();
	WriteI2C(valor);
	verI2C();
}

//--------------------------------------------------------------------------------
//	Rutina RI2C
//	lee un byte en protocolo I2C
//--------------------------------------------------------------------------------
unsigned char RI2C (void){
unsigned char dato;
	ClrWdt();
	dato= 	ReadI2C();
	verI2C();
return dato;
}

//--------------------------------------------------------------------------------
//	Rutina LINEAI2C
//	Estabiliza y verifica la linea
//--------------------------------------------------------------------------------
void LINEAI2C(void){
unsigned char m;
	I2C_ENTRADA;				//garantiza que el bus no este en uso
	m =0;
	while(((_SDA==0)||(_SCL==0))&&(m<250)) m++;	//activar
	//020704
//	if(m> 240) DETENER_EJECUCION(110);
 	TRISC = 0b11100001;	//puertos de salida
	_SDA = 1;		//estabiliza las lineas
	_SCL = 1;
}

//*********************** funciones II2C basicas *******************************



//--------------------------------------------------------------------------------
//	Rutina RAM_INICIO
//	direcciona la memoria RAM
//--------------------------------------------------------------------------------
void RAM_INICIO(void){
LINEAI2C();		//condicion de la linea
S2= RAM;
START_I2C();		//start
WI2C(S2);	  	//direccionamiento
IdleI2C();		//Espera reconocimiento del esclavo
WI2C(aux);		//direccion de inicio
IdleI2C();		//Espera reconocimiento del esclavo
}

//--------------------------------------------------------------------------------
//	Rutina R_RAM
//	lee el contenido de la memoria desde min hasta max
//--------------------------------------------------------------------------------
void R_RAM(unsigned char inicio){
	aux= inicio;
	RAM_INICIO();
	STOP_I2C();		//stop
//lee todo el contenido del RELOJ
	S2++;
	START_I2C();		//start
	WI2C(S2);	        //direccionamiento
	IdleI2C();
	max--;
for(aux=min; aux<max; aux++){
	DATOS[aux] = RI2C();	//Recibir valor DATOS[aux]
	AckI2C();
	IdleI2C();};		//Reconocimiento por el master
	DATOS[max] = RI2C();	//Recibir valor DATOS[aux+1]
	NotAckI2C();	//no reconocimiento por el master
	IdleI2C();
	STOP_I2C();		//Stop
}

//--------------------------------------------------------------------------------
//	Rutina W_RAM
//      escribe en la memoria desde min hasta max
//--------------------------------------------------------------------------------
void W_RAM(unsigned char inicio){
unsigned char verf_e;
	aux= inicio;
	RAM_INICIO();
for(aux=min; aux< max; aux++){
	aux1= DATOS[aux];
	WI2C(aux1);			//esccribe DATOS[aux]
	IdleI2C();};		//Espera reconocimiento del esclavo
	STOP_I2C();			//Stop
	e=0;
	if(inicio<8){ DATOS[0]= 0; DATOS[1]= 0;};
//	XOR_I2C();
//	verf_e= e;
	LINEAI2C();
	R_RAM(inicio);
	max++;
	e= 0;
	if(inicio<8){ DATOS[0]= 0; DATOS[1]= 0;};
//	XOR_I2C();
//	if(e!= verf_e)	DETENER_EJECUCION(111);
}

//--------------------------------------------------------------------------------
//	Rutina ROM_INICIO para la 950
//	el primer banco es de 2048 registros de 64 bytes
//	el segundo banco es de 2048 registros de 64 bytes
//  modificado  021113
//--------------------------------------------------------------------------------
void ROM_INICIO(unsigned char fast2){
	if(fast2== 7) fast2= 0;				//esto asegura que se lee el banco 0
	S1= contador<<6; 					//64 bytes por registro
	if(fast2==2) 	S1= S1|0b00111100;	//posicion 60 - para R_ROM(2);
	S2= contador>>2;
	S3= contador>>9;
	S3= S3&(0b00001110);
	S3= S3|ROM;							//banco 1
	if(fast2==4) S3= S3|ROM2;			//banco 2
	if((fast2==0)||(fast2==4)) LINEAI2C();	//condicion de la linea
	START_I2C();				//start
	WI2C(S3);		  			//direccionamiento
	IdleI2C();					//Espera reconocimiento del esclavo
 	WI2C(S2);					//direccion de inicio
	IdleI2C();					//Espera reconocimiento del esclavo
	WI2C(S1);					//direccion de inicio
	IdleI2C();					//Espera reconocimiento del esclavo
}

//--------------------------------------------------------------------------------
//	Rutina R_ROM
//	lee el contenido de la memoria desde min hasta max
// 	modificado 021113
//--------------------------------------------------------------------------------
void R_ROM(unsigned char fast){
unsigned char i, j;
	ROM_INICIO(fast);
	STOP_I2C();		//stop
	//lee todo el contenido de la memoria
	S3++;
	START_I2C();	//start
	WI2C(S3);		//direccionamiento
	IdleI2C();		//Espera reconocimiento del esclavo
	e=0;
	i=0;						//lee 64 bytes. DATOS 0 a 63.
	if(fast== 2) i= 60;			//lee 4 bytes. DATOS 60 a 63. banco 1
	if(fast== 7) i=  63;		//en caso de prueba del check
	bit_error2= 1;
for(i= i; i<63; i++){
	j = RI2C();					//Recibir valor DATOS[aux]
	DATOS[i] = j;
	if(i<8) bit_error2+=  j;
	AckI2C();					//Reconocimiento por el master
	IdleI2C();
	e= e^j;};  		//calcula el BCC
	DATOS[63] = RI2C();			//Recibir valor DATOS[aux+1]
	NotAckI2C();				//no reconocimiento por el master
	IdleI2C();
	STOP_I2C();					//Stop
//error por BCC. CHECK para el banco 1
	if((fast==2)||(fast==3)) return;
	j= 112;
	if(fast== 7){ e= 0xE7; j= 113;};	//021113
//	if(e!= DATOS[63]) DETENER_EJECUCION(j);
}

//--------------------------------------------------------------------------------
//	Rutina W_ROM
//  escribe en la memoria fiscal
//	0, 1, 2, 3 escribe 64 bytes en banco 1
//	4 escribe 16 bytes en banco 2
//  modificado 021113
//--------------------------------------------------------------------------------
void W_ROM(unsigned char tipo){
unsigned char i, j;
	//para verificar si el registro esta usado
	if((contador> 47)&&(tipo== 0)&&(DATOS[0]!= 0xE7)) R_ROM(7);		//021113
	if(tipo!=4) tipo = 0;
	ROM_INICIO(tipo);
	min= 0;
	max= 63;
	e=0;
//	XOR_I2C();
	DATOS[63]= e;			//guarda el BCC de la data
	bit_error1= 1;
for(i=0; i< 64; i++){		//escribe 64 bytes. DATOS 0 a 63.
	j= DATOS[i];
	if(i<8) bit_error1+= j;  //define byte para verificar escritura
	WI2C(j);				//esccribe DATOS[aux]
	IdleI2C();};			//Espera reconocimiento del esclavo
	STOP_I2C();				//Stop

	LINEAI2C();
	R_ROM(tipo);
while(bit_error1!= bit_error2);		//021115 veriifca escritura
}


//-----------------------------------------------------------------------
//	Rutina NORMAL
//	establece los patrones normales de impresion copia + auditoria
//-----------------------------------------------------------------------
void NORMAL(void){
ACK;
#ifndef PF300
//inicializa la impresora
put_ESC(); putchar_imp(64);
//impresion en auditoria y en recibo
put_ESC(); putchar_imp('c'); putchar_imp('0'); putchar_imp(3);
put_ESC(); putchar_imp('c'); putchar_imp('1'); putchar_imp(3);
put_ESC(); putchar_imp('z'); putchar_imp(1);
//DELAY_VAR(); ADG
//put_CR(); ADG
#else
put_ESC();  putchar_imp('!'); putchar_imp(0);
#endif
}


//-----------------------------------------------------------------------
//	Rutina CORTAR
//	corta el papel
//-----------------------------------------------------------------------
void CORTAR(void){
//SIN_COPIA();
//avanza el papel
#ifndef PF300
puts_LF(2,LF);

#ifdef PF220
puts_LF(5,LF);
#endif
#ifdef PF675
puts_LF(6,LF);
#endif
#ifdef PF950
puts_LF(10,LF);
#endif
if(bit_cutter== 1){bit_cutter= 0; return;};
#endif
NORMAL();
#ifndef PF300
put_ESC(); putchar_imp('i');   //corta el papel
put_LF();
#endif
#ifdef PF300
putchar_imp(12);
#endif
//bit_cierre_economico= 0;
}

//-----------------------------------------------------------------------
//	Rutina CLEAR_DATOS
// 	borrar un conjunto de valores de la trama de datos
//-----------------------------------------------------------------------
void CLEAR_DATOS(unsigned char dato){
for(aux= min; aux<max; aux++) DATOS[aux]= dato;
}

//-----------------------------------------------------------------------
//	Rutina PRINT_LINEA
//-----------------------------------------------------------------------
void PRINT_LINEA(void){
//imprime linea
#ifndef PF300
puts_LF(40,'-');
#else
puts_LF(79,'-');
#endif
put_LF();
//MODO_TECNICO();
}

//-----------------------------------------------------------------------
//	Rutina PRINT_FECHA
//	imprime hora y fecha del RTC
//-----------------------------------------------------------------------
void PRINT_FECHA(void){
min= 0;
max= 64; //ADG SE LEE TODO PARA MANTENER EL BCC DE RAM
R_RAM(0);
puts_imp("FECHA: ");
//IMP_MENSAJES(201);  IMP_MENSAJES(202);
PRINT_DATO(4); putchar_imp('/'); PRINT_DATO(5); putchar_imp('/'); putchar_imp('2');putchar_imp('0');PRINT_DATO(6);
puts_BN(11);
puts_imp("HORA: ");
//IMP_MENSAJES(203);  IMP_MENSAJES(202);
PRINT_DATO(2); putchar_imp(':'); PRINT_DATO(1);
#ifndef PF300
put_LF();
#endif
//hora y fecha del documento activo
aa= DATOS[6];	//AÑO
mm= DATOS[5];	//MES
dd= DATOS[4];	//DIA
hh= DATOS[2];	//HORA
mi= DATOS[1];	//MIN
}

//--------------------------------------------------------------------------------
//	Rutina SET_RELOJ				041001
//--------------------------------------------------------------------------------
void SET_RELOJ(void){
//verifica estado de impresora

//verifica si los datos son validos
min= 3;
max= 9;
//CAD_NUMERO(2);
min= 10;
max= 16;
//CAD_NUMERO(3);

//verifica si se trata de una fecha valida
aux2=0;
aux= cad[4]<<4; aux+= cad[5];		//año
//VALIDA_DATO(aux,0x12);
aux= cad[6]<<4; aux+= cad[7];		//mes
if(aux==0) aux2++;
//VALIDA_DATO(aux,0x12);
aux= cad[8]<<4; aux+= cad[9];		//dia
if(aux==0) aux2++;
//VALIDA_DATO(aux,0x31);
//if(aux2!= 0) ERROR_RESP(1);

//verifica si se trata de una hora valida
aux= cad[11]<<4; aux+= cad[12];		//HH
//VALIDA_DATO(aux,0x23);
aux= cad[13]<<4; aux+= cad[14];		//MM
//VALIDA_DATO(aux,0x59);
aux= cad[15]<<4; aux+= cad[16];		//SS
//VALIDA_DATO(aux,0x59);
//if(aux2!= 0) ERROR_RESP(2);

//DEFINE_FECHA(4);
//ini_per= periodo;

//es la fecha del ultimo comprobante
min= 53;  //ANTES 46
max= 58;
R_RAM(46);

aux= DATOS[53];   //antes 46
cad[30]= aux>>4;
cad[31]= aux&0x0f;
aux= DATOS[54];
cad[32]= aux>>4;
cad[33]= aux&0x0f;
aux= DATOS[55];
cad[34]= aux>>4;
cad[35]= aux&0x0f;

//verifica la fecha con respecto a la RAM
//DEFINE_FECHA(30);

//borrado para desarrollo
//if((ini_per< periodo)&&(JUMP1)) ERROR_RESP(161);

//verifica la fecha con respecto al ultimo Z
//LEE_N_Z();
//contador= contador + 47;
//R_ROM(2);
//DEFINE_FECHA(0);
//borrado para desarrollo
//if(ini_per<valor) ERROR_RESP(162);
//valor= valor + 250;
//if((ini_per> valor)&&(JUMP1)) ERROR_RESP(163);

//serguir_set_reloj:
//se carga AA/MM/DD
	aux= 4; 	aux1= 6;
//	SET_FECHA_CAD_DATOS();

	DATOS[3]= 1;

//se carga HH/MM/SS
	aux= 11; 	aux1= 2;
//	SET_FECHA_CAD_DATOS();

//020701
	DATOS[0]= 0;

min=0;
max=7;
W_RAM(0);

}

//-----------------------------------------------------------------------
//	Rutina gets			041001
//-----------------------------------------------------------------------
unsigned char gets(void){
static unsigned char 	limite_rec;
static unsigned char 	aux_rec;
static unsigned char	limite_reset;
static unsigned char	data;

aux_rec=0;
limite_rec=0;
limite_reset=7;

//inicializa string de separadores de campos
for(aux=0; aux<20; aux++) ncampos[aux]=0;
//inicializa string de recepcion
for(aux=0; aux<150; aux++) cad[aux]=0;


//aciva el Watch Dog Timer
Activa_WDT;
DTR_SERIE = 1;
Activa_Rx;

while(aux_rec<121){

	DTR_SERIE = 1;
	Activa_Rx;

	//espera el dato
	while(!PIR1bits.RCIF);

	//recibe el dato
	data= RCREG;

	ClrWdt();

	//crea la trama
	if(data== STX){ aux_rec=0; limite_rec=1;};
	cad[aux_rec]= data;
	aux_rec++;
	if((data== ETX)&&(limite_rec!=0)){limite_rec = aux_rec; aux_rec=117;};

	//reset
	//020815
	if((limite_reset== 10)&&(data== 11)) limite_reset= 11;
	if((limite_reset== 13)&&(data== 14)) limite_reset= 14;
 	if(data!= limite_reset)	limite_reset= 7;
	if(data== limite_reset) limite_reset++;
//	while(limite_reset>17) bit_RESET= 0;
};

Inactiva_Rx;
DTR_SERIE = 0;
return limite_rec;
}

//*********************** Programa principal  041001 **************************************
void main(){

#ifdef DEBUG
Comando=RCON;
last_Comando=RCON;
#endif

DTR_SERIE = 0;
Inactiva_WDT;

CONFIGURA();

//envia mensaje a la impresora
//if(!JUMP1){MODO_TECNICO(); PRINT_FECHA();};
while(1){
	if(!JUMP1){ NORMAL();
	PRINT_FECHA(); putchar_imp(LF);	putchar_imp(LF); CORTAR();
	}
}
//CICLO_COMANDO();
}
