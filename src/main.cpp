#include <Arduino.h>
#include <IRremote.h>

const int RECV_PIN = 3;
const int TRIGGER_PIN = 2;
const int LED_PIN = 13;
const int PULL_PIN = 5;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

void setup()
{
  Serial.begin(9600);

  irrecv.enableIRIn();

  pinMode(TRIGGER_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PULL_PIN, OUTPUT);

  digitalWrite(PULL_PIN, LOW);
}

void dump(decode_results *results)
{
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN)
  {
    Serial.println("Could not decode message");
  }
  else
  {
    if (results->decode_type == NEC)
    {
      Serial.print("Decoded NEC: ");
    }
    else if (results->decode_type == SONY)
    {
      Serial.print("Decoded SONY: ");
    }
    else if (results->decode_type == RC5)
    {
      Serial.print("Decoded RC5: ");
    }
    else if (results->decode_type == RC6)
    {
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

  for (int i = 0; i < count; i++)
  {
    if ((i % 2) == 1)
    {
      Serial.print(results->rawbuf[i] * USECPERTICK, DEC);
    }
    else
    {
      Serial.print(-(int)results->rawbuf[i] * USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println("");
}

void loop()
{
  // if (irrecv.decode(&results)) {
  //   dump(&results);
  //   irrecv.resume(); // Receive the next value
  // }

  if (digitalRead(TRIGGER_PIN) == HIGH)
  {
    digitalWrite(LED_PIN, HIGH);

    for (size_t i = 0; i < 3; i++)
    {
      irsend.sendSony(0xB4B8F, 20);
      delay(10);
    }

    delay(500);
    digitalWrite(LED_PIN, LOW);
  }
}