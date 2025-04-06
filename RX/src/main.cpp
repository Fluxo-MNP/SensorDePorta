#include <Arduino.h>
#include "ATUADORES.h"
#include "LEDS.h"
#include "BUZZER.h"
#include "CONTATORA.h"
#include "ENTRADAS.h"

int estadoVT(){
    return digitalRead(5);  
}

// Definição dos pinos
#define pinLedAzul 4
#define pinLedLaranja 7
#define pinLedBranco 13
#define pinValidTransmittion 5
#define pinSensorToque 6
#define pinBuzzer 10
#define pinMosfet 9

// Instâncias das classes
Leds ledLaranja(pinLedLaranja);
Leds ledBranco(pinLedBranco);
Leds ledAzul(pinLedAzul);
Buzzer buzzer(pinBuzzer);
Contatora mosfet(pinMosfet);
// Entradas vt(pinValidTransmittion);
Entradas sensorToque(pinSensorToque);

// Variáveis de controle

unsigned long tempoAntigo = 0;           // contador geral
unsigned long tempoAntigoBuzzer = 0;     // contador do buzzer
unsigned long tempoAntigoLedBranco = 0;  // contador do LED branco
unsigned long tempoAntigoLedAzul = 0;    // contador do LED azul
unsigned long tempoAntigoLedLaranja = 0; // contador do LED laranja
bool estaContando = false;   // variável que verifica se a contagem está acontecendo
bool placaFoiTocada = false; // variável que verifica se a contagem está acontecendo


void setup()
{
    Serial.begin(9600);
    pinMode(pinValidTransmittion, INPUT_PULLUP);

    // ledLaranja.desligarAtuador(tempoAtual);
    // ledBranco.desligarAtuador(tempoAtual);
    // ledAzul.desligarAtuador(tempoAtual);
}

// ... (outras partes do código permanecem iguais)

void loop()
{
    unsigned long tempoAtual = millis();
    Serial.println(tempoAtual);
    
    if (digitalRead(pinValidTransmittion) == 1 && !estaContando)
    {
        buzzer.ligarAtuador(tempoAtual);    // Liga o buzzer imediatamente
        ledBranco.ligarAtuador(tempoAtual); // Liga o LED branco
        ledAzul.ligarAtuador(tempoAtual);   // Liga o LED azul
        tempoAntigo = tempoAtual;
        tempoAntigoLedBranco = tempoAtual;
        tempoAntigoLedAzul = tempoAtual; // Inicia o contador do LED azul
        tempoAntigoLedLaranja = tempoAtual; // Inicia o contador do LED laranja
        estaContando = true;
        placaFoiTocada = false; // Reseta o estado do toque
    }

    if (estaContando)
    {
        Serial.println("Contando...");

        // Verifica se o sensor de toque foi ativado
        if (sensorToque.getEstado() == 1)
        {
            buzzer.desligarAtuador(tempoAtual);     // Desliga o buzzer
            placaFoiTocada = true;
            ledBranco.desligarAtuador(tempoAtual);  // Desliga o LED branco
            ledLaranja.desligarAtuador(tempoAtual); // Desliga o LED laranja
            ledAzul.desligarAtuador(tempoAtual);    // Desliga o LED azul

            mosfet.ligarAtuador(tempoAtual);        // Liga o MOSFET
            estaContando = false;
        }

        // Desliga o LED azul após 3 segundos
        if (ledAzul.getDiferencaTempo(tempoAtual) >= 3000)
        {
            ledAzul.desligarAtuador(tempoAtual);
        }

        // Verifica se passou 10 segundos e a placa não foi tocada
        if (tempoAtual - tempoAntigo >= 10000 && !placaFoiTocada)
        {
            // Pisca o LED laranja (500ms ligado, 500ms desligado)
            if (tempoAtual - tempoAntigoLedLaranja >= 500) // Verifica a cada 500ms
            {
                if (ledLaranja.getEstado() == LOW)
                {
                    Serial.println("LED Laranja Ligando");
                    ledLaranja.ligarAtuador(tempoAtual);
                }
                else
                {
                    Serial.println("LED Laranja Desligando");
                    ledLaranja.desligarAtuador(tempoAtual);
                }
                tempoAntigoLedLaranja = tempoAtual; // Atualiza o tempo da última mudança
            }
            
            // Finaliza a contagem após 10 segundos de piscadas (total 20s)
            if (tempoAtual - tempoAntigo >= 20000) // 10s de contagem inicial + 10s piscando
            {
                Serial.println("Fim da piscada do LED laranja");
                ledLaranja.desligarAtuador(tempoAtual);
                ledAzul.desligarAtuador(tempoAtual);
                ledBranco.desligarAtuador(tempoAtual);
                mosfet.desligarAtuador(tempoAtual); // DESLIGA O MOSFET SOMENTE AQUI
                buzzer.desligarAtuador(tempoAtual);
                estaContando = false;
            }
            else
            {
                // Mantém o MOSFET ligado durante as piscadas
                mosfet.ligarAtuador(tempoAtual);
            }
        }

        // Controla o buzzer (liga/desliga a cada 5 segundos)
        if (buzzer.getDiferencaTempo(tempoAtual) >= 5000)
        {
            buzzer.setIntervalo(5000); // Define o intervalo do buzzer
            buzzer.ligarAtuador(tempoAtual);
            tempoAntigoBuzzer = tempoAtual;
        }
    }

    // Desliga o buzzer após 300ms
    if (buzzer.getDiferencaTempo(tempoAtual) >= 300 && buzzer.getEstado() == HIGH)
    {
        buzzer.desligarAtuador(tempoAtual);
        tempoAntigoBuzzer = tempoAtual;
    }

    delay(50);
}