#include <Arduino.h>
#include "ATUADORES.h"
#include "LEDS.h"
#include "BUZZER.h"
#include "CONTATORA.h"
#include "ENTRADAS.h"
#include "VT.h"

// Definição dos pinos
#define pinMosfet 6      // PB5
#define pinLedLaranja 1 // PC3
#define pinLedBranco 2 // PC7
#define pinLedAzul 0   // PD2
#define pinBuzzer 5     // PD3
#define pinValidTransmittion 3          // PC5
#define pinSensorToque 4       // PC6 sensor

// Instâncias das classes
Leds ledLaranja(pinLedLaranja);
Leds ledBranco(pinLedBranco);
Leds ledAzul(pinLedAzul);
Buzzer buzzer(pinBuzzer);
Contatora mosfet(pinMosfet);
ValidTransmittion vt(pinValidTransmittion);
Entradas sensorToque(pinSensorToque);

// Variáveis de controle
unsigned long tempoAntigo = 0;                // contador geral
unsigned long tempoAntigoBuzzer = 0;          // contador do buzzer
unsigned long tempoAntigoledBranco = 0;      // contador do led branco
unsigned long tempoAntigoLedsLaranjaAzul = 0; // contador dos leds laranja e azul
bool estaContando = false;                    // variável que verifica se a contagem está acontecendo

void setup()
{
}

void loop()
{
    unsigned long tempoAtual = millis();

    // Verifica se o sinal VT foi recebido e inicia a contagem
    if (vt.getEstado() == HIGH && !estaContando)
    {
        buzzer.ligarAtuador(tempoAtual); // Liga o buzzer imediatamente
        tempoAntigo = tempoAtual;
        ledBranco.atualizaTempo(tempoAtual);
        estaContando = true;
    }

    if (estaContando)
    {
        // Verifica se o sensor de toque foi ativado
        if (sensorToque.getEstado() == HIGH)
        {
            ledLaranja.ligarAtuador(tempoAtual); // Liga o LED laranja
            mosfet.ligarAtuador(tempoAtual);     // Liga o MOSFET
            ledLaranja.atualizaTempo(tempoAtual);
            ledAzul.atualizaTempo(tempoAtual);
            estaContando = false;
        }

        // Controla o LED branco (pisca a cada 700ms)
        if (tempoAtual - tempoAntigoledBranco >= 700)
        {
            ledBranco.setIntervalo(700); // Define o intervalo de piscagem
            ledBranco.ligarAtuador(tempoAtual);
            ledBranco.atualizaTempo(tempoAtual);
        }

        // Desliga tudo após 12 segundos se o sensor não for tocado
        if (tempoAtual - tempoAntigo >= 12000)
        {
            ledAzul.ligarAtuador(tempoAtual);   // Liga o LED azul
            mosfet.desligarAtuador(tempoAtual); // Desliga o MOSFET
            ledLaranja.atualizaTempo(tempoAtual);
            ledAzul.atualizaTempo(tempoAtual);
            estaContando = false;
        }

        // Controla o buzzer (liga/desliga a cada 5 segundos)
        if (tempoAtual - tempoAntigoBuzzer >= 5000)
        {
            buzzer.setIntervalo(5000); // Define o intervalo do buzzer
            buzzer.ligarAtuador(tempoAtual);
            buzzer.atualizaTempo(tempoAtual);
        }
    }

    // Desliga o LED branco após 300ms
    if (tempoAtual - tempoAntigoledBranco >= 300 && ledBranco.getEstado() == HIGH)
    {
        ledBranco.desligarAtuador(tempoAtual);
        ledBranco.atualizaTempo(tempoAtual);
    }

    // Desliga o buzzer após 300ms
    if (tempoAtual - tempoAntigoBuzzer >= 300 && buzzer.getEstado() == HIGH)
    {
        buzzer.desligarAtuador(tempoAtual);
        buzzer.atualizaTempo(tempoAtual);
    }

    // Desliga os LEDs laranja e azul após 3 segundos
    if (tempoAtual - tempoAntigoLedsLaranjaAzul >= 3000)
    {
        ledLaranja.desligarAtuador(tempoAtual);
        ledAzul.desligarAtuador(tempoAtual);
    }

    delay(50);
}