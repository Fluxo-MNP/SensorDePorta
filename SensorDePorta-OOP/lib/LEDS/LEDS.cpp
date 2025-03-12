#include "LEDS.h"

Leds::Leds(int pino) : Atuador(pino) {}

void Leds::ligarAtuador(unsigned long tempoAtual) {
    unsigned long tempoDecorrido = getTempoDecorrido(tempoAtual);

    if (tempoDecorrido >= this->getIntervalo() && this->getEstado() == LOW) {
        this->estado = HIGH;
        digitalWrite(this->pino, this->estado);
        setTempoAntigo(tempoAtual); // Atualiza o tempo antigo
    }
}

void Leds::desligarAtuador(unsigned long tempoAtual) {
    unsigned long tempoDecorrido = getTempoDecorrido(tempoAtual);

    if (tempoDecorrido >= this->getIntervalo() && this->getEstado() == HIGH) {
        this->estado = LOW;
        digitalWrite(this->pino, this->estado);
        setTempoAntigo(tempoAtual); // Atualiza o tempo antigo
    }
}