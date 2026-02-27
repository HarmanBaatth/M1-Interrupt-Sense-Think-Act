#include <avr/interrupt.h>

// -------- Pins --------
const int PIR = 8;      
const int TILT = 9;     
const int SWITCH_EXT = 2;   

const int LED_EVENT = 13;   // Event LED
const int LED_TIMER = 12;   // Timer LED

// -------- Flags --------
volatile bool pciFlag = false;
volatile bool extFlag = false;
volatile bool timerFlag = false;

// -------- External Interrupt ISR --------
void extISR() {
  extFlag = true;
}

// -------- Timer1 ISR --------
ISR(TIMER1_COMPA_vect) {
  timerFlag = true;
}

// -------- Pin Change Interrupt ISR (D8–D13) --------
ISR(PCINT0_vect) {
  pciFlag = true;
}

// -------- Timer Setup --------
void setupTimer1() {

  cli();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 15624;                 // 1 second (16MHz /1024)
  TCCR1B |= (1 << WGM12);        // CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10);  // 1024 prescaler
  TIMSK1 |= (1 << OCIE1A);

  sei();
}

void setup() {

  Serial.begin(9600);

  pinMode(PIR, INPUT_PULLUP);
  pinMode(TILT, INPUT_PULLUP);
  pinMode(SWITCH_EXT, INPUT_PULLUP);

  pinMode(LED_EVENT, OUTPUT);
  pinMode(LED_TIMER, OUTPUT);

  // Enable PCI for D8 and D9
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);  
  PCMSK0 |= (1 << PCINT1);  

  // External Interrupt on Pin 2
  attachInterrupt(digitalPinToInterrupt(SWITCH_EXT), extISR, CHANGE);

  setupTimer1();
}

void loop() {

  // -------- Handle PCI (PIR + Tilt) --------
  if (pciFlag) {
    pciFlag = false;

    Serial.print("PCI Triggered | PIR = ");
    Serial.print(!digitalRead(PIR));
    Serial.print(" | TILT = ");
    Serial.println(!digitalRead(TILT));

    if (!digitalRead(PIR) && !digitalRead(TILT)) {
      digitalWrite(LED_EVENT, HIGH);
    } else {
      digitalWrite(LED_EVENT, LOW);
    }
  }

  // -------- Handle External Interrupt (Slide Switch) --------
  if (extFlag) {
    extFlag = false;
    Serial.println("External Interrupt: Slide Switch Changed");
  }

  // -------- Handle Timer Interrupt --------
  if (timerFlag) {
    timerFlag = false;
    digitalWrite(LED_TIMER, !digitalRead(LED_TIMER));
    Serial.println("Timer Interrupt: 1 second tick");
  }
}