#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

// ----- Button Setup -----
const int buttonPin = 2;
volatile int mode = 0; // 0 = Inductance, 1 = Capacitance
volatile bool modeChanged = false;

// ----- Inductance Variables -----
double pulse, frequency, capacitance, inductance;

// ----- Capacitance Variables -----
#define analogPin      A0          
#define chargePin      7          
#define dischargePin   3        
#define resistorValue  2150.0F    

unsigned long startTime;
unsigned long elapsedTime;
float microFarads;
float nanoFarads;

// ----- Interrupt Function -----
void switchMode() {
  mode = (mode + 1) % 2;  // Toggle between 0 (Inductance) and 1 (Capacitance)
  modeChanged = true; // Indicate mode switch for LCD update
}

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), switchMode, FALLING); // Interrupt-based mode switching

  pinMode(11, INPUT);
  pinMode(13, OUTPUT);
  pinMode(chargePin, OUTPUT);
  digitalWrite(chargePin, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ready");
  delay(1000);
}

void loop() {
  // If mode changed, update LCD
  if (modeChanged) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Switched to Mode:");
    lcd.setCursor(0, 1);
    lcd.print(mode == 0 ? "Inductance" : "Capacitance");
    Serial.print("Mode switched to: ");
    Serial.println(mode == 0 ? "Inductance" : "Capacitance");
    modeChanged = false;
    delay(1000);
  }

  // Debugging Mode State
  Serial.print("Current Mode: ");
  Serial.println(mode == 0 ? "Inductance" : "Capacitance");

  if (mode == 0) {
    runInductanceMode();
  } else {
    runCapacitanceMode();
  }
}

// ------------------- Inductance Mode -------------------
void runInductanceMode() {
  digitalWrite(13, HIGH);
  delay(5);
  digitalWrite(13, LOW);
  delayMicroseconds(100);

  pulse = pulseIn(11, HIGH, 5000);
  if (pulse > 0.1) {
    capacitance = 237.E-8;  
    frequency = 1.E6 / (2 * pulse);
    inductance = 1. / (capacitance * frequency * frequency * 4. * 3.14159 * 3.14159);
    inductance *= 1E6;

    Serial.print("Inductance Measurement:");
    Serial.print(" Pulse uS: ");
    Serial.print(pulse);
    Serial.print("\tFrequency Hz: ");
    Serial.print(frequency);
    Serial.print("\tInductance uH: ");
    Serial.println(inductance);

    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Inductance Mode");
    lcd.setCursor(0, 1); 
    lcd.print(inductance);
    lcd.setCursor(14, 1); 
    lcd.print("uH");
    delay(500);
  } else {
    Serial.println("Inductance Measurement Timeout");
  }
}

// ------------------- Capacitance Mode -------------------
void runCapacitanceMode() {
  digitalWrite(chargePin, HIGH);
  startTime = micros();
  
  while (analogRead(analogPin) < 648) {
    if (modeChanged) return;
  }

  elapsedTime = micros() - startTime;
  microFarads = ((float)elapsedTime / resistorValue);

  Serial.print("Capacitance Measurement: ");
  Serial.print("Elapsed Time: ");
  Serial.print(elapsedTime);
  Serial.print("\tmicroFarads: ");
  Serial.println(microFarads);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Capacitance Mode");

  if (microFarads > 1) {
    lcd.setCursor(0, 1);  
    lcd.print(microFarads);
    lcd.setCursor(14, 1);        
    lcd.print("uF");
    Serial.print(microFarads);
    Serial.println(" uF");
  } else {
    nanoFarads = microFarads * 1000.0;
    lcd.setCursor(0, 1);       
    lcd.print(nanoFarads);
    lcd.setCursor(14, 1);       
    lcd.print("nF");
    Serial.print(nanoFarads);
    Serial.println(" nF");
  }

  delay(500);
  digitalWrite(chargePin, LOW);
  pinMode(dischargePin, OUTPUT);
  digitalWrite(dischargePin, LOW);
  
  while (analogRead(analogPin) > 0) {
    if (modeChanged) return;
  }

  pinMode(dischargePin, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("DISCHARGING.....");
  delay(500);
}
