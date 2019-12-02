#include <ESP8266WiFi.h> //Biblioteca de WiFi do ESP8266

const char* servidorLog = "api.pushingbox.com"; //Endereço da API que irá enviar notificações para os dispositivos cadastrados
String idDispositivo = "v5E91D50196664C9"; //ID do cenário cadastrado no cénario da API 

void notifica(String mensagem) {
    WiFiClient client;

    if(client.connect(servidorLog, 80)) {      
      String postStr = "devid=";
      postStr += String(idDispositivo);
      postStr += "&message_parameter=";
      postStr += String(mensagem);
      postStr += "\r\n\r\n";
      
      client.print("POST /pushingbox HTTP/1.1\n");
      client.print("Host: api.pushingbox.com\n");
      client.print("Connection: close\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);
    }
    client.stop();
}

void setup() {
//----------Login no WiFi----------
  //WiFi.begin("Multicastlab", "ZJLHJ30101999"); //WiFi.begin("REDE-WiFi", "SENHA-REDE-WiFi");
  //WiFi.begin("VIVO-52FE", "9XGXU3CurB"); //WiFi.begin("REDE-WiFi", "SENHA-REDE-WiFi");
  WiFi.begin("Rede_Teste_ESP8266", "TesteESP8266"); //WiFi.begin("REDE-WiFi", "SENHA-REDE-WiFi");
}

void loop() {
  if(digitalRead(sensor_de_fogo) == HIGH){ //Caso o sensor esteja em 1
      /*digitalWrite(buzzer, HIGH); //Ativa o buzzer
      delay(200); //Aguarda 200 milissegundos
      digitalWrite(buzzer, LOW); //Desativa o buzzer
      delay(200); //Aguarda 200 milissegundos*/
      alarme();
      notifica("TESTE"); //Ativa a função "notifica()", ou seja, deve enviar uma notificação para o celular cadastrado na API 
  }else{ //Caso o sensor esteja em 0
    digitalWrite(buzzer, LOW); //O sensor permanece inativo
  }
}