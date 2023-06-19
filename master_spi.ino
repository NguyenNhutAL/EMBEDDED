#define SCK  4  
#define MOSI 5  
#define MISO 6 
#define SS   7 

uint8_t dataFromSlave = 0x00;

void spiSoftInit();
void clockSignal();
void spiSoftTransmitMaster(uint8_t mData);
uint8_t spiSoftReceiveMaster();

void setup() {
  pinMode(SCK, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(SS, OUTPUT);
  pinMode(MISO, INPUT);
  Serial.begin(115200);
  spiSoftInit();
}

void loop()
{
  for (char i = 'A'; i <= 'Z'; i++) {
    spiSoftTransmitMaster(i);
    Serial.print("Send Data to Slave: ");
    Serial.println(i);
    delay(500);
    dataFromSlave = spiSoftReceiveMaster();
    Serial.print("Data Received from Slave: ");
    Serial.println(dataFromSlave);
    delay(500);
  }
}

void spiSoftInit()
{
  digitalWrite(SCK, LOW);
  digitalWrite(MOSI, LOW);
  digitalWrite(SS, HIGH);
}

void clockSignal()
{
  digitalWrite(SCK, HIGH);
  delay(100);
  digitalWrite(SCK, LOW);
  delay(100);
}

void spiSoftTransmitMaster(uint8_t mData)
{
  uint8_t i = 0, x = 0;
  digitalWrite(SS, LOW);
  for (i = 0; i < 8; i++) {
    x = mData & 0x80; 
    if (x > 0)
      digitalWrite(MOSI, HIGH);
    else
      digitalWrite(MOSI, LOW);
    mData = mData << 1; 
    clockSignal();
    delay(2);
  }
  digitalWrite(SS, HIGH);
}

uint8_t spiSoftReceiveMaster()
{
  uint8_t _data = 0x00, i = 0;
  digitalWrite(SS, LOW);
  for (i = 0; i < 8; i++) {
    clockSignal(); 
    delay(2);
    _data = _data << 1;     
    _data = _data | digitalRead(MISO);  
  }
  digitalWrite(SS, HIGH);
  return _data;
}
