// #include <Arduino.h>

// // Definição dos pinos
// #define pino_mosfet 6     // PB5
// #define pino_led_laranja 1 // PC3
// #define pino_led_branco 2 // PC7
// #define pino_led_azul 0   // PD2
// #define pino_buzzer 5     // PD3
// #define pino_VT 3          // PC5
// #define pino_toque 4       // PC6 sensor

// class Atuador
// {
// protected:
//     int pino;
//     bool estado;
//     unsigned long tempoAntigo; // Tempo antigo para controle de intervalo
//     unsigned long intervalo;   // Intervalo de tempo para controle

// public:
//     Atuador(int pino);
//     bool getEstado();

//     // Métodos virtuais puros
//     virtual void ligarAtuador(unsigned long tempoAtual) = 0;
//     virtual void desligarAtuador(unsigned long tempoAtual) = 0;

//     // Métodos de controle de tempo
//     void setTempoAntigo(unsigned long tempoAntigo);
//     unsigned long getTempoDecorrido(unsigned long tempoAtual);

//     // Métodos para definir e obter o intervalo
//     void setIntervalo(unsigned long intervalo);
//     unsigned long getIntervalo();
// };

// Atuador::Atuador(int pino)
// {
//     this->pino = pino;
//     this->estado = LOW;
//     this->tempoAntigo = 0; // Inicializa o tempo antigo
//     this->intervalo = 0;   // Inicializa o intervalo
//     pinMode(this->pino, OUTPUT);
//     digitalWrite(this->pino, LOW); // Garante que o LED comece desligado
// }

// bool Atuador::getEstado()
// {
//     return this->estado;
// }

// void Atuador::setTempoAntigo(unsigned long tempoAntigo)
// {
//     this->tempoAntigo = tempoAntigo;
// }

// unsigned long Atuador::getTempoDecorrido(unsigned long tempoAtual)
// {
//     return tempoAtual - this->tempoAntigo;
// }

// void Atuador::setIntervalo(unsigned long intervalo)
// {
//     this->intervalo = intervalo;
// }

// unsigned long Atuador::getIntervalo()
// {
//     return this->intervalo;
// }

// class Buzzer : public Atuador
// {
// public:
//     Buzzer(int pino);

//     void ligarAtuador(unsigned long tempoAtual) override;
//     void desligarAtuador(unsigned long tempoAtual) override;
// };

// Buzzer::Buzzer(int pino) : Atuador(pino) {}

// void Buzzer::ligarAtuador(unsigned long tempoAtual)
// {
//     unsigned long tempoDecorrido = getTempoDecorrido(tempoAtual);

//     if (tempoDecorrido >= this->getIntervalo() && this->getEstado() == LOW)
//     {
//         this->estado = HIGH;
//         digitalWrite(this->pino, this->estado);
//         setTempoAntigo(tempoAtual); // Atualiza o tempo antigo
//     }
// }

// void Buzzer::desligarAtuador(unsigned long tempoAtual)
// {
//     unsigned long tempoDecorrido = getTempoDecorrido(tempoAtual);

//     if (tempoDecorrido >= this->getIntervalo() && this->getEstado() == HIGH)
//     {
//         this->estado = LOW;
//         digitalWrite(this->pino, this->estado);
//         setTempoAntigo(tempoAtual); // Atualiza o tempo antigo
//     }
// }

// class Contatora : public Atuador
// {
// public:
//     Contatora(int pino);
//     void ligarAtuador(unsigned long tempoAtual) override;
//     void desligarAtuador(unsigned long tempoAtual) override;
// };

// Contatora::Contatora(int pino) : Atuador(pino)
// {
//     // Inicializações, se necessário
// }

// void Contatora::ligarAtuador(unsigned long tempoAtual)
// {
//     this->estado = HIGH;
//     digitalWrite(this->pino, this->estado);
// }

// void Contatora::desligarAtuador(unsigned long tempoAtual)
// {
//     this->estado = LOW;
//     digitalWrite(this->pino, this->estado);
// }

// class Leds : public Atuador
// {
// public:
//     Leds(int pino);

//     void ligarAtuador(unsigned long tempoAtual) override;
//     void desligarAtuador(unsigned long tempoAtual) override;
// };

// Leds::Leds(int pino) : Atuador(pino) {}

// void Leds::ligarAtuador(unsigned long tempoAtual)
// {
//     unsigned long tempoDecorrido = getTempoDecorrido(tempoAtual);

//     if (tempoDecorrido >= this->getIntervalo() && this->getEstado() == LOW)
//     {
//         this->estado = HIGH;
//         digitalWrite(this->pino, this->estado);
//         setTempoAntigo(tempoAtual); // Atualiza o tempo antigo
//     }
// }

// void Leds::desligarAtuador(unsigned long tempoAtual)
// {
//     unsigned long tempoDecorrido = getTempoDecorrido(tempoAtual);

//     if (tempoDecorrido >= this->getIntervalo() && this->getEstado() == HIGH)
//     {
//         this->estado = LOW;
//         digitalWrite(this->pino, this->estado);
//         setTempoAntigo(tempoAtual); // Atualiza o tempo antigo
//     }
// }

// class Entradas
// {
// protected:
//     int pino;
//     bool estado;

// public:
//     Entradas(int pino);
//     bool getEstado();
// };

// Entradas::Entradas(int pino)
// {
//     this->pino = pino;
//     pinMode(pino, INPUT);
// }

// bool Entradas::getEstado()
// {
//     this->estado = digitalRead(this->pino);
//     return this->estado;
// }

// // Instâncias das classes
// Leds ledLaranja(pino_led_laranja);
// Leds ledBranco(pino_led_branco);
// Leds ledAzul(pino_led_azul);
// Buzzer buzzer(pino_buzzer);
// Contatora mosfet(pino_mosfet);
// Entradas vt(pino_VT);
// Entradas sensorToque(pino_toque);

// // Variáveis de controle
// unsigned long tempoAntigo = 0;                // contador geral
// unsigned long tempoAntigoBuzzer = 0;          // contador do buzzer
// unsigned long tempoAntigoLedBranco = 0;       // contador do LED branco
// unsigned long tempoAntigoLedAzul = 0;         // contador do LED azul
// unsigned long tempoAntigoLedLaranja = 0;      // contador do LED laranja
// bool estaContando = false;                    // variável que verifica se a contagem está acontecendo
// bool placaFoiTocada = false;                  // variável que verifica se a placa foi tocada

// void setup()
// {
//     Serial.begin(9600);

//     // Garante que todos os LEDs comecem desligados
//     ledLaranja.desligarAtuador(millis());
//     ledBranco.desligarAtuador(millis());
//     ledAzul.desligarAtuador(millis());
// }

// void loop()
// {
//     unsigned long tempoAtual = millis();

//     // Verifica se o sinal VT foi recebido e inicia a contagem
//     if (vt.getEstado() == HIGH && !estaContando)
//     {
//         buzzer.ligarAtuador(tempoAtual); // Liga o buzzer imediatamente
//         ledBranco.ligarAtuador(tempoAtual); // Liga o LED branco
//         ledAzul.ligarAtuador(tempoAtual); // Liga o LED azul
//         tempoAntigo = tempoAtual;
//         tempoAntigoLedBranco = tempoAtual;
//         tempoAntigoLedAzul = tempoAtual; // Inicia o contador do LED azul
//         estaContando = true;
//         placaFoiTocada = false; // Reseta o estado do toque
//     }

//     if (estaContando)
//     {
//         // Verifica se o sensor de toque foi ativado
//         if (sensorToque.getEstado() == HIGH)
//         {
//             placaFoiTocada = true;
//             ledBranco.desligarAtuador(tempoAtual); // Desliga o LED branco
//             ledLaranja.desligarAtuador(tempoAtual); // Desliga o LED laranja
//             mosfet.ligarAtuador(tempoAtual); // Liga o MOSFET
//             estaContando = false;
//         }

//         // Desliga o LED azul após 3 segundos
//         if (tempoAtual - tempoAntigoLedAzul >= 3000)
//         {
//             ledAzul.desligarAtuador(tempoAtual);
//         }

//         // Verifica se passou 1 minuto (60000 ms) e a placa não foi tocada
//         if (tempoAtual - tempoAntigo >= 60000 && !placaFoiTocada)
//         {
//             // Pisca o LED laranja uma vez por segundo durante 10 segundos
//             if (tempoAtual - tempoAntigoLedLaranja >= 1000)
//             {
//                 ledLaranja.ligarAtuador(tempoAtual);
//                 tempoAntigoLedLaranja = tempoAtual;
//             }

//             // Desliga o LED laranja após 500ms (para criar o efeito de piscar)
//             if (tempoAtual - tempoAntigoLedLaranja >= 500 && ledLaranja.getEstado() == HIGH)
//             {
//                 ledLaranja.desligarAtuador(tempoAtual);
//             }

//             // Verifica se passaram 10 segundos desde o início da piscada
//             if (tempoAtual - tempoAntigo >= 70000) // 60000 + 10000
//             {
//                 ledLaranja.desligarAtuador(tempoAtual); // Desliga o LED laranja
//                 estaContando = false; // Finaliza a contagem
//             }
//         }

//         // Controla o buzzer (liga/desliga a cada 5 segundos)
//         if (tempoAtual - tempoAntigoBuzzer >= 5000)
//         {
//             buzzer.setIntervalo(5000); // Define o intervalo do buzzer
//             buzzer.ligarAtuador(tempoAtual);
//             tempoAntigoBuzzer = tempoAtual;
//         }
//     }

//     // Desliga o buzzer após 300ms
//     if (tempoAtual - tempoAntigoBuzzer >= 300 && buzzer.getEstado() == HIGH)
//     {
//         buzzer.desligarAtuador(tempoAtual);
//         tempoAntigoBuzzer = tempoAtual;
//     }

//     delay(50);
// }