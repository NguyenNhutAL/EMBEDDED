/*
 *Author: Nguyen Minh Nhut
 *Date: 18/06/2023
 *Description: this program sent to slave with spi standard
*/

#define SCK_PIN    4
#define MOSI_PIN   5
#define MISO_PIN   6
#define SS_PIN     7

void SPI_Soft_Init(void);
void SPI_Soft_Transmit(uint8_t mData);


void setup() {
  SPI_Soft_Init();
}

void loop() {
  digitalWrite(SS_PIN,LOW);
  SPI_Soft_Transmit('A');
  digitalWrite(SS_PIN,HIGH);
  delay(2000);
}


void SPI_Soft_Init()
{
  pinMode(SCK_PIN,OUTPUT);
  pinMode(MOSI_PIN,OUTPUT);
  pinMode(MISO_PIN,INPUT);
  pinMode(SS_PIN , OUTPUT);
  digitalWrite(SCK_PIN,LOW);
  digitalWrite(SS_PIN,HIGH);
}


void SPI_Soft_Transmit(uint8_t mData)
{
  uint8_t temp=0;
  for(int i=0;i<8;i++){
     temp= mData & 0x80 ;
     if(temp)
     {
        digitalWrite(MOSI_PIN,HIGH);
     }
     else
     {
        digitalWrite(MOSI_PIN,LOW);
     }
     delayMicroseconds(25);
     digitalWrite(SCK_PIN,HIGH);
     delayMicroseconds(25);
     digitalWrite(SCK_PIN,LOW);
     mData=mData<<1;
  }
}