#include <Arduino.h>
#include "comandos.h"
#include "tempo.h"

void setup()
{
  pinMode(PinoContatora, OUTPUT);
  pinMode(PinoLedLaranja, OUTPUT);
  pinMode(PinoLedBranco, OUTPUT);
  pinMode(PinoLedAzul, OUTPUT);
  pinMode(PinoBuzzer, OUTPUT);

  pinMode(PinoVT, INPUT);
  pinMode(PinoSensorDeToque, INPUT);

  digitalWrite(PinoVT, LOW);
  digitalWrite(PinoBuzzer, LOW);
  digitalWrite(PinoContatora, LOW);
}

void loop()
{
  estaContando = false;
  tempoAtual = millis();
  estaContando = VerificarRecepcaoSinal(tempoAtual, estaContando);
  bool leituraDigitalPinoToque = digitalRead(PinoSensorDeToque);

  if (estaContando)
  {

    AcionarDisjuntor(leituraDigitalPinoToque);
    
    AcionarDispositivos(tempoAntigoLedBranco, 700, PinoLedBranco);

    if (tempoAtual - tempoAntigo >= 12000)
    {
      digitalWrite(PinoLedAzul, HIGH);  // aciona o led azul se n tiver tocado no sensor
      digitalWrite(PinoContatora, LOW); // desliga disjuntor
      tempoAntigoLedsLaranjaAzul = tempoAtual;
      estaContando = false;
    }
    AcionarDispositivos(tempoAntigoBuzzer, 5000, PinoBuzzer);
  }
  DesligarDispositivos(tempoAntigoLedBranco, PinoLedBranco);
  DesligarDispositivos(tempoAntigoBuzzer, PinoBuzzer);

  if (tempoAtual - tempoAntigoLedsLaranjaAzul >= 3000)
  {
    digitalWrite(PinoLedAzul, LOW);
    digitalWrite(PinoLedLaranja, LOW);
  }

  delay(50);
}