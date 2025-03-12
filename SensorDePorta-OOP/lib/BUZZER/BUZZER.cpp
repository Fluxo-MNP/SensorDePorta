#include <Arduino.h>
#include "BUZZER.h"
#include "ATUADORES.h"

Buzzer::Buzzer(int pino):Atuador(pino){
    this->tempoAntigo = 0;
    this->intervalo = 0;
}

void Buzzer::ligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo) {
   
    unsigned long tempoDecorrido = tempoAtual - tempoAntigo;

    if (tempoDecorrido >= intervalo && this->getEstado() == LOW) {
        this->estado = HIGH;
        digitalWrite(this->pino, this->estado);
        tempoAntigo = tempoAtual;
    }
}

void Buzzer::desligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo) {
    
    unsigned long tempoDecorrido = tempoAtual - tempoAntigo;

    if (tempoDecorrido >= intervalo && this->getEstado() == HIGH) {
        this->estado = LOW;
        digitalWrite(this->pino, this->estado);
        tempoAntigo = tempoAtual;
    }
}