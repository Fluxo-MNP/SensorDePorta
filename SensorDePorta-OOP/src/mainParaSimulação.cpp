void loop() {
    Serial.println("Loop rodando...");
    delay(1000); // Delay de 1000ms apos cada Serial.print

    unsigned long tempoAtual = millis();

    if (vt.getEstado() == HIGH && !estaContando) {
        buzzer.ligarAtuador(tempoAtual);
        tempoAntigo = tempoAtual;
        ledBranco.atualizaTempo(tempoAtual);
        estaContando = true;
        Serial.println("Transmitindo valido - Iniciando contagem");
        delay(1000);
    }

    if (estaContando) {
        if (sensorToque.getEstado() == HIGH) {
            ledLaranja.ligarAtuador(tempoAtual);
            mosfet.ligarAtuador(tempoAtual);
            estaContando = false;
            Serial.println("Sensor de toque acionado - LED laranja e mosfet ligados");
            delay(1000);
        }

        if (ledBranco.getTempoDecorrido(tempoAtual) >= 700) {
            ledBranco.setIntervalo(700);
            ledBranco.ligarAtuador(tempoAtual);
            Serial.println("Tempo do LED branco alcançado - Ligando LED branco");
            delay(1000);
        }

        if (tempoAtual - tempoAntigo >= 12000) {
            ledAzul.ligarAtuador(tempoAtual);
            mosfet.desligarAtuador(tempoAtual);
            estaContando = false;
            Serial.println("12 segundos passados - LED azul ligado e mosfet desligado");
            delay(1000);
        }

        if (buzzer.getTempoDecorrido(tempoAtual) >= 5000) {
            buzzer.setIntervalo(5000);
            buzzer.ligarAtuador(tempoAtual);
            Serial.println("5 segundos passados - Buzzer ligado");
            delay(1000);
        }
    }

    // Aqui, agora o LED Laranja e Azul só vão desligar se o tempo correto for atingido
    if (ledLaranja.getTempoDecorrido(tempoAtual) >= 3000 && ledLaranja.getEstado() == HIGH) {
        ledLaranja.desligarAtuador(tempoAtual);
        Serial.println("3 segundos passados - LED laranja desligado");
        delay(1000);
    }

    if (ledAzul.getTempoDecorrido(tempoAtual) >= 3000 && ledAzul.getEstado() == HIGH) {
        ledAzul.desligarAtuador(tempoAtual);
        Serial.println("3 segundos passados - LED azul desligado");
        delay(1000);
    }

    if (ledBranco.getTempoDecorrido(tempoAtual) >= 300 && ledBranco.getEstado() == HIGH) {
        ledBranco.desligarAtuador(tempoAtual);
        Serial.println("Desligando LED branco");
        delay(1000);
    }

    if (buzzer.getTempoDecorrido(tempoAtual) >= 300 && buzzer.getEstado() == HIGH) {
        buzzer.desligarAtuador(tempoAtual);
        Serial.println("Desligando Buzzer");
        delay(1000);
    }

    delay(50);
}
