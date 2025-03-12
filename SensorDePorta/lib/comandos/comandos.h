#ifndef COMANDOS_H
#define COMANDOS_H

#define PinoLedAzul 0
#define PinoLedLaranja 1
#define PinoLedBranco 2
#define PinoVT 3
#define PinoSensorDeToque 4
#define PinoBuzzer 5
#define PinoContatora 6

bool VerificarRecepcaoSinal(unsigned long tempoAtual, bool &estaContando);


/**
 * @brief caso o pino de toque seja acionado esteja em HIGH, o disjuntor será acionado
 * 
 * @param pinoSensorToque faz a leitura digital do sensor de toque
 */
void AcionarDisjuntor(int pinoSensorToque);
void AcionarDispositivos(unsigned long &tempoReferencia, int valorReferenciaTempo, int pinoAcionado);
void DesligarDispositivos(unsigned long &tempoReferencia, int pino);
#endif