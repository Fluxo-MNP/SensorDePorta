#ifndef COMANDOS_H
#define COMANDOS_H

#define PinoLedAzul 0
#define PinoLedLaranja 1
#define PinoLedBranco 2
#define PinoVT 3
#define PinoSensorDeToque 4
#define PinoBuzzer 5
#define PinoContatora 6

bool VerificarRecepcaoSinal(unsigned long tempoAtual, bool estaContando);

#endif