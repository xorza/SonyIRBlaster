#include <Arduino.h>
#include <IRremote.h>

int RECV_PIN = 3;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

void setup()
{
  Serial.begin(9600);
  
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}


void dump(decode_results *results) {
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.println("Could not decode message");
  } 
  else {
    if (results->decode_type == NEC) {
      Serial.print("Decoded NEC: ");
    } 
    else if (results->decode_type == SONY) {
      Serial.print("Decoded SONY: ");
    } 
    else if (results->decode_type == RC5) {
      Serial.print("Decoded RC5: ");
    } 
    else if (results->decode_type == RC6) {
      Serial.print("Decoded RC6: ");
    }
    Serial.print(results->value, HEX);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(" bits)");
  }
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  for (int i = 0; i < count; i++) {
    if ((i % 2) == 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    } 
    else {
      Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println("");
}


void loop() {
  // if (irrecv.decode(&results)) {
  //   dump(&results);
  //   irrecv.resume(); // Receive the next value
  // }

  for (size_t i = 0; i < 3; i++)
  {
      irsend.sendSony(0xB4B8F, 20);
     delay(10);
  }  

   delay(35000);
}