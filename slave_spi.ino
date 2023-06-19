#define SCK  4 
#define MOSI 5  
#define MISO 6  
#define SS   7  

bool stateSlave = 1;
uint8_t dataReceived = 0x00;
uint8_t sizeDataReceived = 0;
uint8_t dataTransmited = 0x00;
uint8_t sizeDataTransmited = 0;

void spiSoftTransmit();
void spiSoftReceived();
void spiSoftSlave();

void setup()
{
  Serial.begin(115200);
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(SS, INPUT);
  pinMode(MISO, OUTPUT);
}

void loop()
{
  if (digitalRead(SS) == HIGH) {
    if (sizeDataReceived == 8) {
      Serial.print("Data Received from Master: ");
      Serial.println((char)dataReceived);
      dataReceived = 0x00;
      sizeDataReceived = 0;
      stateSlave = 0;
      dataTransmited = 88;
    }
    else
    {
      dataReceived = 0x00;
      sizeDataReceived = 0;
    }
    if (sizeDataTransmited == 8) {
      dataTransmited = 88;
      sizeDataTransmited = 0;
      stateSlave = 1;
      Serial.println("Transmited Data");
    }
    else
    {
      sizeDataTransmited = 0;
    }
  }
}


void spiSoftSlave()
{
  if (digitalRead(SS) == HIGH) return;
  if (stateSlave)
    spiSoftReceived();
  else
    spiSoftTransmit();
}

void spiSoftReceived()
{
  dataReceived = dataReceived << 1;
  dataReceived = dataReceived | digitalRead(MOSI);   
  delay(2);
  sizeDataReceived++;
}

void spiSoftTransmit()
{
  uint8_t x = 0;
  x = dataTransmited & 0x80; 
  if (x > 0)
    digitalWrite(MISO, HIGH);
  else
    digitalWrite(MISO, LOW);
  dataTransmited = dataTransmited << 1; 
  sizeDataTransmited++;
}
