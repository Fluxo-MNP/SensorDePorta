#include <Arduino.h>
#include "ATUADORES.h"
#include "LEDS.h"
#include "BUZZER.h"
#include "CONTATORA.h"
#include "ENTRADAS.h"
#include "VT.h"

// Definição dos pinos
#define pino_mosfet 3      // PB5
#define pino_led_laranja 5 // PC3
#define pino_led_amarelo 9 // PC7
#define pino_led_azul 11   // PD2
#define pino_buzzer 12     // PD3
#define pino_VT 7          // PC5
#define pino_toque 8       // PC6 sensor

// Instâncias das classes
Leds ledLaranja(pino_led_laranja);
Leds ledAmarelo(pino_led_amarelo);
Leds ledAzul(pino_led_azul);
Buzzer buzzer(pino_buzzer);
Contatora mosfet(pino_mosfet);
ValidTransmittion vt(pino_VT);
Entradas sensorToque(pino_toque);

// Variáveis de controle
unsigned long tempoAntigo = 0;                // contador geral
unsigned long tempoAntigoBuzzer = 0;          // contador do buzzer
unsigned long tempoAntigoLedAmarelo = 0;      // contador do led amarelo
unsigned long tempoAntigoLedsLaranjaAzul = 0; // contador dos leds laranja e azul
bool estaContando = false;                    // variável que verifica se a contagem está acontecendo

void setup()
{
    // Inicializações já feitas nos construtores das classes
}

void loop()
{
    unsigned long tempoAtual = millis();

    // Verifica se o sinal VT foi recebido e inicia a contagem
    if (vt.getEstado() == HIGH && !estaContando)
    {
        buzzer.ligarAtuador(tempoAtual); // Liga o buzzer imediatamente
        tempoAntigo = tempoAtual;
        tempoAntigoLedAmarelo = tempoAtual;
        estaContando = true;
    }

    if (estaContando)
    {
        // Verifica se o sensor de toque foi ativado
        if (sensorToque.getEstado() == HIGH)
        {
            ledLaranja.ligarAtuador(tempoAtual); // Liga o LED laranja
            mosfet.ligarAtuador(tempoAtual);     // Liga o MOSFET
            tempoAntigoLedsLaranjaAzul = tempoAtual;
            estaContando = false;
        }

        // Controla o LED amarelo (pisca a cada 700ms)
        if (tempoAtual - tempoAntigoLedAmarelo >= 700)
        {
            ledAmarelo.setIntervalo(700); // Define o intervalo de piscagem
            ledAmarelo.ligarAtuador(tempoAtual);
            tempoAntigoLedAmarelo = tempoAtual;
        }

        // Desliga tudo após 12 segundos se o sensor não for tocado
        if (tempoAtual - tempoAntigo >= 12000)
        {
            ledAzul.ligarAtuador(tempoAtual);   // Liga o LED azul
            mosfet.desligarAtuador(tempoAtual); // Desliga o MOSFET
            tempoAntigoLedsLaranjaAzul = tempoAtual;
            estaContando = false;
        }

        // Controla o buzzer (liga/desliga a cada 5 segundos)
        if (tempoAtual - tempoAntigoBuzzer >= 5000)
        {
            buzzer.setIntervalo(5000); // Define o intervalo do buzzer
            buzzer.ligarAtuador(tempoAtual);
            tempoAntigoBuzzer = tempoAtual;
        }
    }

    // Desliga o LED amarelo após 300ms
    if (tempoAtual - tempoAntigoLedAmarelo >= 300 && ledAmarelo.getEstado() == HIGH)
    {
        ledAmarelo.desligarAtuador(tempoAtual);
        tempoAntigoLedAmarelo = tempoAtual;
    }

    // Desliga o buzzer após 300ms
    if (tempoAtual - tempoAntigoBuzzer >= 300 && buzzer.getEstado() == HIGH)
    {
        buzzer.desligarAtuador(tempoAtual);
        tempoAntigoBuzzer = tempoAtual;
    }

    // Desliga os LEDs laranja e azul após 3 segundos
    if (tempoAtual - tempoAntigoLedsLaranjaAzul >= 3000)
    {
        ledLaranja.desligarAtuador(tempoAtual);
        ledAzul.desligarAtuador(tempoAtual);
    }

    delay(50);
}