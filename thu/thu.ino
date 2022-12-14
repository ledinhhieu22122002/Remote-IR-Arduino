
#define LEDPIN 13
#define maxLen 800
#define rxPinIR 2 

volatile  unsigned int irBuffer[maxLen]; 
volatile unsigned int x = 0;

void setup() {
  Serial.begin(115200); 
  attachInterrupt(digitalPinToInterrupt(rxPinIR), rxIR_Interrupt_Handler, CHANGE);
}

void loop() {

  Serial.println(F("Press the button on the remote now - once only"));
  delay(5000); 
  if (x) { 
    digitalWrite(LEDPIN, HIGH);
    Serial.println();
    Serial.print(F("Raw: (")); 
    Serial.print((x - 1));
    Serial.print(F(") "));
    detachInterrupt(digitalPinToInterrupt(rxPinIR));
    for (int i = 1; i < x; i++) { 
      if (!(i & 0x1)) Serial.print(F("-"));
      Serial.print(irBuffer[i] - irBuffer[i - 1]);
      Serial.print(F(", "));
    }
    x = 0;
    Serial.println();
    Serial.println();
    digitalWrite(LEDPIN, LOW);
    attachInterrupt(digitalPinToInterrupt(rxPinIR), rxIR_Interrupt_Handler, CHANGE);
  }
}

void rxIR_Interrupt_Handler() {
  if (x > maxLen) return; 
  irBuffer[x++] = micros(); 
}