#define ORANGE_BUTTON 21
#define BLUE_BUTTON 4
#define PIN_BUZZER 22

int latchPin = 2;         
int clockPin = 0;          
int dataPin = 15;           
int latchPin2 = 5;       
int clockPin2 = 19;         
int dataPin2 = 18;  

unsigned long lastUpdate1 = 0;
unsigned long lastUpdate2 = 0;
byte orangeLED = 0b11111111;
byte blueLED = 0b11111111;

void setup() {

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);

  pinMode(ORANGE_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);

  pinMode(PIN_BUZZER, OUTPUT);

  writeToOrangeLED(LSBFIRST, 0b11111111);
  writeToBlueLED(LSBFIRST, 0b11111111);
}

void loop() {
  
  unsigned long now = millis();

  if (digitalRead(ORANGE_BUTTON) == LOW) {
    orangeLED = 0b11111111;
    writeToOrangeLED(LSBFIRST, orangeLED);
    digitalWrite(PIN_BUZZER, LOW);
    lastUpdate1 = now;
    delay(200);
  }else if (now - lastUpdate1 >= 1200000UL) {
    lastUpdate1 = now;
    orangeLED <<= 1;
    writeToOrangeLED(LSBFIRST, orangeLED);
    if (orangeLED == 0) digitalWrite(PIN_BUZZER, HIGH);
  }

  if(digitalRead(BLUE_BUTTON) == LOW) {
    blueLED = 0b11111111;
    writeToBlueLED(LSBFIRST, blueLED);
    digitalWrite(PIN_BUZZER, LOW);
    lastUpdate2 = now;
    delay(200);
  }else if (now - lastUpdate2 >= 600000) {
    lastUpdate2 = now;
    blueLED >>= 1;
    writeToBlueLED(LSBFIRST, blueLED);
    if (blueLED == 0) digitalWrite(PIN_BUZZER, HIGH);
  }

  if(now - lastUpdate1 >= 1200000UL){
    lastUpdate1 = now;
    orangeLED <<= 1;
    writeToOrangeLED(LSBFIRST, orangeLED);
    if (orangeLED == 0) {
      delay(6000);
      digitalWrite(PIN_BUZZER, HIGH);
    }
  }

  if(now - lastUpdate2 >= 600000){
    lastUpdate2 = now;
    blueLED >>= 1;
    writeToBlueLED(LSBFIRST, blueLED);
    if (blueLED == 0) {
      delay(6000);
      digitalWrite(PIN_BUZZER, HIGH);
    }
  }
}

void writeToOrangeLED(int order, byte _data ) {
  digitalWrite(latchPin2, LOW);

  shiftOut(dataPin2, clockPin2, order, _data);

  digitalWrite(latchPin2, HIGH);
}

void writeToBlueLED(int order, byte _data) {
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, order, _data);

  digitalWrite(latchPin, HIGH);
}
