
// Leitura de distância com o sensor HC-SR04
#include <Ultrasonic.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// Define o nome do sensor(ultrassom) e onde esta ligado o trig(8) e o echo(7) respectivamente
Ultrasonic ultrassom(12,13);  
WiFiServer server(80);

long distancia;

const char* ssid = "(((H)))";
const char* password = "vinips62"; 

// Esta função "setup" roda uma vez quando a placa e ligada ou resetada
void setup() {        
  Serial.begin(9600); //Habilita Comunicação Serial a uma taxa de 9600 bauds.

  // Inicia conexão com a rede wifi
  Serial.println();
  Serial.println();
  Serial.print("Conectando a rede ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);

  // Espera o servidor conectar
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado"); 
}
// Função que se repete infinitamente quando a placa é ligada
void loop(){
  distancia = ultrassom.Ranging(CM); // ultrassom.Ranging(CM) retorna a distancia em
                                     // centímetros(CM) ou polegadas(INC)
  Serial.print(distancia);           //imprime o valor da variável distancia
  Serial.println("cm");
  delay(1000);

  if(WiFi.status()== WL_CONNECTED){  //Check WiFi connection status
 
    HTTPClient http;  //Declare object of class HTTPClient
 
    http.begin("http://192.168.0.14:3333/store-sensor-data");  //Specify request destination
    http.addHeader("Content-Type", "text/plain");  //Specify content-type header
    
    //Send the request
    int httpCode = http.POST("Message from ESP8266");   //Send the request
    String payload = http.getString();  //Get the response payload
 
    Serial.println(payload);  //Print request response payload
 
    http.end();  //Close connection 
  }
}
