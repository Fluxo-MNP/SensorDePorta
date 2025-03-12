#include <Arduino.h>
#include "ATUADORES.h"
#include "LEDS.h"
#include "BUZZER.h"
#include "CONTATORA.h"
#include "ENTRADAS.h"

// Definição dos pinos
#define pinMosfet 6      
#define pinLedLaranja 1 
#define pinLedBranco 2 
#define pinLedAzul 0   
#define pinBuzzer 5    
#define pinValidTransmittion 3         
#define pinSensorToque 4    

// Instâncias das classes
Leds ledLaranja(pinLedLaranja);
Leds ledBranco(pinLedBranco);
Leds ledAzul(pinLedAzul);
Buzzer buzzer(pinBuzzer);
Contatora mosfet(pinMosfet);
Entradas vt(pinValidTransmittion);
Entradas sensorToque(pinSensorToque);

// Variáveis de controle
unsigned long tempoAntigo = 0;                // contador geral
unsigned long tempoAntigoBuzzer = 0;          // contador do buzzer
unsigned long tempoAntigoLedBranco = 0;       // contador do LED branco
unsigned long tempoAntigoLedAzul = 0;         // contador do LED azul
unsigned long tempoAntigoLedLaranja = 0;      // contador do LED laranja
bool estaContando = false;                    // variável que verifica se a contagem está acontecendo
bool placaFoiTocada = false;                   // variável que verifica se a contagem está acontecendo

void setup()
{
    Serial.begin(9600);
    ledLaranja.desligarAtuador(millis());
    ledBranco.desligarAtuador(millis());
    ledAzul.desligarAtuador(millis());
}

void loop()
{    unsigned long tempoAtual = millis();

    // Verifica se o sinal VT foi recebido e inicia a contagem
    if (vt.getEstado() == HIGH && !estaContando)
    {
        buzzer.ligarAtuador(tempoAtual); // Liga o buzzer imediatamente
        ledBranco.ligarAtuador(tempoAtual); // Liga o LED branco
        ledAzul.ligarAtuador(tempoAtual); // Liga o LED azul
        tempoAntigo = tempoAtual;
        tempoAntigoLedBranco = tempoAtual;
        tempoAntigoLedAzul = tempoAtual; // Inicia o contador do LED azul
        estaContando = true;
        placaFoiTocada = false; // Reseta o estado do toque
    }

    if (estaContando)
    {
        // Verifica se o sensor de toque foi ativado
        if (sensorToque.getEstado() == HIGH)
        {
            placaFoiTocada = true;
            ledBranco.desligarAtuador(tempoAtual); // Desliga o LED branco
            ledLaranja.desligarAtuador(tempoAtual); // Desliga o LED laranja
            mosfet.ligarAtuador(tempoAtual); // Liga o MOSFET
            estaContando = false;
        }

        // Desliga o LED azul após 3 segundos
        if (tempoAtual - tempoAntigoLedAzul >= 3000)
        {
            ledAzul.desligarAtuador(tempoAtual);
        }

        // Verifica se passou 1 minuto (60000 ms) e a placa não foi tocada
        if (tempoAtual - tempoAntigo >= 60000 && !placaFoiTocada)
        {
            // Pisca o LED laranja uma vez por segundo durante 10 segundos
            if (tempoAtual - tempoAntigoLedLaranja >= 1000)
            {
                ledLaranja.ligarAtuador(tempoAtual);
                tempoAntigoLedLaranja = tempoAtual;
            }

            // Desliga o LED laranja após 500ms (para criar o efeito de piscar)
            if (tempoAtual - tempoAntigoLedLaranja >= 500 && ledLaranja.getEstado() == HIGH)
            {
                ledLaranja.desligarAtuador(tempoAtual);
            }

            // Verifica se passaram 10 segundos desde o início da piscada
            if (tempoAtual - tempoAntigo >= 70000) // 60000 + 10000
            {
                ledLaranja.desligarAtuador(tempoAtual); // Desliga o LED laranja
                estaContando = false; // Finaliza a contagem
            }
        }

        // Controla o buzzer (liga/desliga a cada 5 segundos)
        if (tempoAtual - tempoAntigoBuzzer >= 5000)
        {
            buzzer.setIntervalo(5000); // Define o intervalo do buzzer
            buzzer.ligarAtuador(tempoAtual);
            tempoAntigoBuzzer = tempoAtual;
        }
    }

    // Desliga o buzzer após 300ms
    if (tempoAtual - tempoAntigoBuzzer >= 300 && buzzer.getEstado() == HIGH)
    {
        buzzer.desligarAtuador(tempoAtual);
        tempoAntigoBuzzer = tempoAtual;
    }

    delay(50);
}
