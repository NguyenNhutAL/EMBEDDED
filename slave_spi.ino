/*
 *Author: Nguyen Minh Nhut
 *Date: 18/06/2023
 *Description: this program recieve from master with spi standard
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
  uint8_t rev;
  rev=SPI_Receive();
  delay(2000);

}

void SPI_Soft_Init()
{
  pinMode(SCK_PIN,INPUT);
  pinMode(MOSI_PIN,INPUT);
  pinMode(MISO_PIN,OUTPUT);
  pinMode(SS_PIN,INPUT);
}


uint8_t SPI_Receive(){
  uint8_t dataReceive=0;
  while(digitalRead(SS_PIN) == HIGH);          //waiting until SS=0. Start condition
  for(int i=0;i<8;i++){
    while(digitalRead(SCK_PIN)==LOW);          // waiting until SCK == 1 --> receive data
      dataReceive = dataReceive | digitalRead(MOSI);
      dataReceive = dataReceive<<1;
    while(digitalRead(SCK_PIN)==HIGH);        //  waiting until SCK == 0 --> received 1 bit and prepare for process receive continue bit
  }
  return dataReceive;
}
