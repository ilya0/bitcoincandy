#include <ESP8266WiFi.h>
#include "Koyn.h"
/* Assign a light bulb to pin 16. */
#define purchase D0
/* Required payment value for the light bulb in satoshis. (0.01 BTC) */
#define PAYMENT_VALUE 1000000
int condition = D5; // green
int buzzer = D1; // buzzer
int wifi = D6; // yellow

/* Create a Bitcoin address with the encoded address ex."mqBPVCaTaJDVGruNTkTD3CKTVMYqmVow6R" */
BitcoinAddress myAddress("2Mux4j9zTACR7MXYfer8UMZZwToVDepDCNV", ADDRESS_ENCODED);

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello world");
  //set modes
  pinMode(condition,OUTPUT); // d5 - green status on light
  pinMode(wifi,OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(purchase, OUTPUT);
  
  
  //run buzzer test and lights
   pinMode(purchase,HIGH);
   delay(2000);
   tone(buzzer, 349); //buzzer test
   delay(1000);
   pinMode(16,HIGH); //purchase light test
   delay(1000);
   pinMode(condition,HIGH); //green light test
   delay(1000);
   pinMode(wifi,HIGH); //wifi test
   delay(1000);
   pinMode(purchase,HIGH);
   delay(1000);

   /// reset pins
   tone(buzzer, LOW);
   pinMode(wifi,LOW);
   pinMode(condition,LOW);
   pinMode(purchase,LOW);
   
  digitalWrite(D5, HIGH); // turn on the status light to working
  
  WiFi.begin("You are being watched", "password1");
  //WiFi.begin("bring hookers internet is slow", "thepasswordisactually$kynet1000");
  //WiFi.begin("CrashSpaceS", "password4fails");
  
  while (WiFi.status()  != WL_CONNECTED){
    tone(buzzer, 440);
    delay(500);
    tone(buzzer,415);
    delay(500);
    tone(buzzer,392);
    delay(500);
    tone(buzzer,370);
    delay(500);
    pinMode(wifi,LOW);
    delay(500);
    pinMode(wifi,HIGH);
    delay(500);
    pinMode(wifi,LOW);
    
    yield();
  }
  tone(buzzer,LOW);
  Koyn.begin();
  Koyn.onNewTransaction(&paymentCallback);
  
}

void loop(){
  /* Check if the board is synced with the network. */
  if (Koyn.isSynced()){
    Serial.println("Koyn Synced!");
    /* Track my address to receive transactions callbacks. */
    Koyn.trackAddress(&myAddress);
  }
  /* Performs the library routines (syncing, validation, tracking, ..etc). */
  Koyn.run();
}

/* This callback function will be called when a BTC transaction is received. */
void paymentCallback(BitcoinTransaction tx)
{
  Serial.println("TRANSACTION RECIEVED");
  unsigned long totalAmountSentToMe = 0;
  /* Loop on all transaction outputs to sum up all received bitcoins. */
  for (int i = 0; i < tx.getOutputsCount(); i++)
  {
    /* Create an empty address. */
    BitcoinAddress to;
    /* Retrieving to address from transaction. */
    tx.getOutput(i, &to);
    /* Check if the bitcoins were sent to me. */
    if (to == myAddress)
    {
      /* Sum up the amount. */
      totalAmountSentToMe += tx.getOutputAmount(i);
    }
  }

  /* Check if the total amount sent to me is enough. */
  if (totalAmountSentToMe >= PAYMENT_VALUE)
  {
    Serial.println("GOT DAT CRYPTO!");
     Serial.println("GOT DAT Crypto! GOT DAT Crypto! GOT DAT Crypto! GOT DAT Crypto! GOT DAT Crypto! GOT DAT Crypto! GOT DAT Crypto! GOT DAT Crypto! GOT DAT Crypto! GOT DAT Crypto! GOT DAT Crypto!GOT DAT Crypto!GOT DAT Crypto!");
      digitalWrite(purchase, HIGH);
      tone(buzzer, 349);
      delay(500);
      tone(buzzer,370);
      delay(500);
      tone(buzzer,392);
      delay(500);
      tone(buzzer,415);
      delay(1000);
      digitalWrite(purchase, LOW);
      tone(buzzer, LOW);
    
    /* Turn on the light bulb. */
    digitalWrite(purchase, HIGH);
    /* Delay for a second. */
    Koyn.delay(1000);
    /* Turn off the light bulb. */
    digitalWrite(purchase, LOW);
  }
}
