#include <Arduino.h>
#include "comandos.h"
#include "tempo.h"

bool estaContando = false;

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

  tempoAtual = millis();
  estaContando = VerificarRecepcaoSinal(tempoAtual, estaContando);

  if (estaContando)
  {
    if (digitalRead(PinoSensorDeToque) == HIGH)
    {
      digitalWrite(PinoLedLaranja, HIGH); // aciona led laranja e liga o disjuntor se o sensor ativar
      digitalWrite(PinoContatora, HIGH);  // liga disjuntor
      tempoAntigoLedsLaranjaAzul = tempoAtual;
      estaContando = false;
    }

    if (tempoAtual - tempoAntigoLedBranco >= 700)
    {
      digitalWrite(PinoLedBranco, HIGH); // aciona led Branco a cada 1 segundo
      tempoAntigoLedBranco = tempoAtual;
    }

    if (tempoAtual - tempoAntigo >= 12000)
    {
      digitalWrite(PinoLedAzul, HIGH);  // aciona o led azul se n tiver tocado no sensor
      digitalWrite(PinoContatora, LOW); // desliga disjuntor
      tempoAntigoLedsLaranjaAzul = tempoAtual;
      estaContando = false;
    }

    if (tempoAtual - tempoAntigoBuzzer >= 5000)
    {
      digitalWrite(PinoBuzzer, HIGH);
      tempoAntigoBuzzer = tempoAtual;
    }
  }

  if (tempoAtual - tempoAntigoLedBranco >= 300 && digitalRead(PinoLedBranco) == HIGH)
  {
    digitalWrite(PinoLedBranco, LOW);
    tempoAntigoLedBranco = tempoAtual;
  }

  if (tempoAtual - tempoAntigoBuzzer >= 300 && digitalRead(PinoBuzzer) == HIGH)
  {
    digitalWrite(PinoBuzzer, LOW);
    tempoAntigoBuzzer = tempoAtual;
  }

  if (tempoAtual - tempoAntigoLedsLaranjaAzul >= 3000)
  {
    digitalWrite(PinoLedAzul, LOW);
    digitalWrite(PinoLedLaranja, LOW);
  }

  delay(50);
}