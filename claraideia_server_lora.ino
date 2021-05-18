//
//#include <SoftwareSerial.h>
////#include <FS.h> 
//
////=====================================================================================
//// Diretivas de compilacao para as bibliotecas ESP32 e ESP8266
////=====================================================================================
////#if defined(ESP8266)
////  #include <ESP8266WiFi.h>
////#else
////  #include <WiFi.h> //ESP32 Core WiFi Library       
////#endif
////=====================================================================================
//// Diretivas de compilacao para as bibliotecas WEBSERVER ESP32 e ESP8266
////=====================================================================================
////
////#if defined(ESP8266)
////  #include <ESP8266WebServer.h>
////#else
////  #include <WebServer.h> 
////#endif
////=====================================================================================
//// Bibliotecas que integram o wifimanager
////=====================================================================================
////#include <DNSServer.h>
#include <WiFiManager.h>
//
//
////=====================================================================================
//// Bibliotecas do display 16x2 e 20x4
////=====================================================================================
////#include <Wire.h> // responsável pela comunicação com a interface i2c
#include <LiquidCrystal_I2C.h> 
//
////=====================================================================================
//// Bibliotecas responsaveis pelo protocolo MQTT
////=====================================================================================
//
#include <PubSubClient.h>
//
//
//
////=====================================================================================
//// Bibliotecas responsaveis conversao de dados JSON e Armazenamento interno de arquivo
////=====================================================================================
#include <ArduinoJson.h>
//#include <StreamUtils.h>
//#include <time.h>
////=====================================================================================
//// Bibliotecas responsaveis converda de data e hora tempo...
////=====================================================================================
//
//
////=====================================================================================
////Pinagem da Lora E32 433T30D
////=====================================================================================
//#define TX D5
//#define RX D6
//#define TIME_SLEEP 7000
//const long utcOffsetInSeconds = 3600;
//
//SoftwareSerial loraSerial(TX,RX);
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
StaticJsonBuffer<200> doc; 
////WiFiManager wifiManager;
WiFiClient espClient;
PubSubClient client(espClient);
//
////tm timeinfo;
////time_t now;
////long unsigned lastNTPtime;
////unsigned long lastEntryTime;
//
//
////=====================================================================================
//// Variaveis utilizadas no software
////=====================================================================================
////const char* ssid = "CLARAIDEIA_AP";
////const char* password = "12345678";
////const char *filename = "/config.json";
////const char* NTP_SERVER = "200.192.232.8";
////const char* TZ_INFO    = "BRST+3BRDT+2,M10.3.0,M2.3.0";  
//
////char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
////char mqtt_server[100] = "mqtt.claraideia.com.br";
////char mqtt_port[6]="1883";
////char mqtt_user[20]="claraideiaIOT";
////char mqtt_passwd[20]="claraideia1817698";
////char mqtt_topic[100]="/iot/claraideia/dados";
////char mqtt_device_name[100]="STA001";
////char geo_longitude[6]="20.1";
////char geo_latitude[6]="-127";
////boolean shouldSaveConfig = false;
////boolean flag = false;
//String output;
//
//
////=====================================================================================
////callback que indica que salvamos uma nova rede para se conectar (modo estação)
////void saveConfigCallback () {
////  Serial.println("Should save config");
////  shouldSaveConfig = true;
////}
//
////void setupWifiManager(){   
////  WiFiManagerParameter custom_text("<b><p style=\"color: red;\">CONFIGURA&Ccedil;&Atilde;O MQTT</p></b>");
////  WiFiManagerParameter custom_mqtt_server("mqtt_server", "mqtt.claraideia.com.br", mqtt_server, 100);
////  WiFiManagerParameter custom_mqtt_port("mqtt_port", "1883", mqtt_port, 6);
////  WiFiManagerParameter custom_mqtt_user("mqtt_user", "claraideiaIOT", mqtt_user, 20);
////  WiFiManagerParameter custom_mqtt_passwd("mqtt_passwd", "claraideia1817698", mqtt_passwd, 20);
////  WiFiManagerParameter custom_mqtt_topic("mqtt_topic", "/iot/claraideia/dados", mqtt_topic, 100);
////  WiFiManagerParameter custom_mqtt_device_name("mqtt_device_name", "STA001", mqtt_device_name, 100);
////  WiFiManagerParameter custom_text2("<b><p style=\"color: green;\">GEOLOCALIZA&Ccedil;&Atilde;O</p></b>");
////  WiFiManagerParameter custom_geo_longitude("geo_longitude", "20.5", geo_longitude, 6);
////  WiFiManagerParameter custom_geo_latitude("geo_latitude", "-121.01", geo_latitude, 6);
//  
////  WiFiManager wifiManager;
////  wifiManager.resetSettings();
////  wifiManager.setCustomHeadElement("<style>button{filter:hue-rotate(300deg);}</style>");
////  //callback para quando se conecta em uma rede, ou seja, quando passa a trabalhar em modo estação
////  wifiManager.setSaveConfigCallback(saveConfigCallback);   
//// 
////  wifiManager.addParameter(&custom_text);
////  wifiManager.addParameter(&custom_mqtt_server);
////  wifiManager.addParameter(&custom_mqtt_port);
////  wifiManager.addParameter(&custom_mqtt_user);
////  wifiManager.addParameter(&custom_mqtt_passwd);
////  wifiManager.addParameter(&custom_mqtt_topic);
////  wifiManager.addParameter(&custom_mqtt_device_name);
////  wifiManager.addParameter(&custom_text2);
////  wifiManager.addParameter(&custom_geo_longitude);
////  wifiManager.addParameter(&custom_geo_latitude);
//  
////  if (!wifiManager.autoConnect("CLARAIDEIA AP","12345678")) {
////    Serial.println("failed to connect and hit timeout");
////    delay(3000);
////    //reset and try again, or maybe put it to deep sleep
////    ESP.reset();
////    delay(5000);
////  }
////  //copy values to file for store
////  strcpy(mqtt_server, custom_mqtt_server.getValue());
////  strcpy(mqtt_port, custom_mqtt_port.getValue());
////  strcpy(mqtt_user, custom_mqtt_user.getValue());
////  strcpy(mqtt_passwd, custom_mqtt_passwd.getValue());
////  strcpy(mqtt_topic, custom_mqtt_topic.getValue());
////  strcpy(mqtt_device_name, custom_mqtt_device_name.getValue());
////  strcpy(geo_longitude, custom_geo_longitude.getValue());
////  strcpy(geo_latitude, custom_geo_latitude.getValue());
//  
////  if (shouldSaveConfig) {    
////    Serial.println("saving config");
////      if (!SPIFFS.exists(filename)) {
////                
////        DynamicJsonBuffer jsonBuffer;
////        JsonObject& json = jsonBuffer.createObject();        
////        json["mqtt_server"] = mqtt_server;
////        json["mqtt_port"] = mqtt_port;
////        json["mqtt_user"] = mqtt_user;
////        json["mqtt_passwd"] = mqtt_passwd;
////        json["mqtt_topic"] = mqtt_topic;
////        json["mqtt_device_name"] = mqtt_device_name;
////        json["geo_longitude"] = geo_longitude;
////        json["geo_latitude"] = geo_latitude;
////        File file = SPIFFS.open(filename, "w");
////        if (!file) {
////          Serial.println("failed to open config file for writing");
////        }
////        json.prettyPrintTo(Serial);
////        json.printTo(file);
////        file.close();
////      }
//
////    wifiManager.setMinimumSignalQuality(10);
////    wifiManager.setRemoveDuplicateAPs(true);
////    wifiManager.setDebugOutput(false);
////    wifiManager.setBreakAfterConfig(true);
////    //end save
////  }
////}
//
//
////void enableAPmode(){
////  flag = true;  
////  if ( flag ) {
////      Serial.println("resetar"); //tenta abrir o portal
////      if(!wifiManager.startConfigPortal("CLARAIDEIA_AP", "12345678") ){
////        Serial.println("Falha ao conectar");
////        delay(2000);
////        ESP.restart();
////        delay(1000);
////      }
////      Serial.println("Conectou ESP_AP!!!");
////      flag = false;         
////  }
//// ESP.reset();
////}
//
//
//
////void mountSystemFiles(){
////    if (SPIFFS.exists(filename)) {
////      //file exists, reading and loading
////      Serial.println("reading config file");
////      File file = SPIFFS.open(filename, "r");
////      delay(1000);
////      if (file) {
////        Serial.println("opened config file");
////        size_t size = file.size();
////        // Allocate a buffer to store contents of the file.
////        std::unique_ptr<char[]> buf(new char[size]);
////        file.readBytes(buf.get(), size);
////        
////        DynamicJsonBuffer jsonBuffer;
////        JsonObject& json = jsonBuffer.parseObject(buf.get());
////        
////        json.printTo(Serial);
////        json.printTo(file);
////        if (!json.success()){
////            Serial.println(F("Failed to read file, using default configuration"));
////        }else{
////          strcpy(mqtt_server, json["mqtt_server"]);
////          strcpy(mqtt_port, json["mqtt_port"]);
////          strcpy(mqtt_user, json["mqtt_user"]);
////          strcpy(mqtt_passwd, json["mqtt_passwd"]);  
////          strcpy(mqtt_topic, json["mqtt_topic"]); 
////          strcpy(mqtt_device_name, json["mqtt_device_name"]);  
////          strcpy(geo_longitude, json["geo_longitude"]); 
////          strcpy(geo_latitude, json["geo_latitude"]);        
////        }
////      }
////      file.close();
////      lista_diretorio();
////      lista_arquivos();
////    }else{
////      
////    }
////}
//
//

//
////callback que indica que o ESP entrou no modo AP
////void configModeCallback (WiFiManager *myWiFiManager) {
////   if ( Serial.available()){ 
////        lcd.setCursor(0,0);
////        lcd.print("Entered config mode");
////        lcd.setCursor(0,1);
////        lcd.print("Entrou no modo de configuração");
////        Serial.println(WiFi.softAPIP()); //imprime o IP do AP
////        Serial.println(myWiFiManager->getConfigPortalSSID()); //imprime o SSID criado da rede
////   }
////}
//
////void mqtt_callback( char* topic, byte* payload, unsigned int length ){
////  char rxj[512];
////  for( int i = 0; i < length; i++){
////    rxj[i] = payload[i]; 
////  }
////}
//
//
//

//

//
////void initMqtt() {
////  if (SPIFFS.exists(filename)) {
////    File file = SPIFFS.open(filename, "r"); 
////    size_t size = file.size(); 
////    std::unique_ptr<char[]> buf(new char[size]);
////    file.readBytes(buf.get(), size);
////    
////    DynamicJsonBuffer jsonBuffer;
////    JsonObject& json = jsonBuffer.parseObject(buf.get());
////    json.printTo(Serial);
////    
////    if (json.success()){
//////      strcpy(mqtt_server,json["mqtt_server"]);
//////      strcpy(mqtt_port,json["mqtt_port"]);
//////      strcpy(mqtt_user,json["mqtt_user"]);
//////      strcpy(mqtt_passwd,json["mqtt_passwd"]);
//////      strcpy(mqtt_topic,json["mqtt_topic"]);
//////      strcpy(mqtt_device_name,json["mqtt_device_name"]);
//////      strcpy(geo_longitude,json["geo_longitude"]);
//////      strcpy(geo_latitude,json["geo_latitude"]);
//////      client.setServer(mqtt_server,atoi(mqtt_port));
////        
////      check_config();
////    }else{
////        Serial.println(F("Falha na abertura do arquivo"));
////    }
////    file.close(); 
////  }
////  Serial.println("Servidor:"+String(mqtt_server));
////  Serial.println("Porta:"+String(mqtt_port));
////  Serial.println("User:"+String(mqtt_user));
////  Serial.println("Pass:"+String(mqtt_passwd));
////  Serial.println("Topic:"+String(mqtt_topic));
////  Serial.println("Device Name:"+String(mqtt_device_name));
////}
//
////bool getNTPtime(int sec) {
////
////  {
////    uint32_t start = millis();
////    do {
////      time(&now);
////      localtime_r(&now, &timeinfo);
////      delay(10);
////    } while (((millis() - start) <= (1000 * sec)) && (timeinfo.tm_year < (2016 - 1900)));
////    if (timeinfo.tm_year <= (2016 - 1900)) return false;  // the NTP call was not successful
////    char time_output[30];
////    strftime(time_output, 30, "%a  %d-%m-%y %T", localtime(&now));
////
////  }
////  return true;
////}
//
////void initNTP(){
////  configTime(0, 0, NTP_SERVER);
////  setenv("TZ", TZ_INFO, 1);
////  if (getNTPtime(10)) {  
////  } else {
////    ESP.restart();
////  }
////  lastNTPtime = time(&now);
////  lastEntryTime = millis();
////}
//
////String showTime(tm localTime) {
////  char buffer[32];
////  snprintf(buffer, sizeof(buffer),"%04d-%02d-%02dT%02d:%02d:%02dZ",localTime.tm_year + 1900, localTime.tm_mon + 1,localTime.tm_mday,localTime.tm_hour, localTime.tm_min, localTime.tm_sec);
////  return String(buffer);
////}
//  

//

//




////void lista_diretorio(){
////  Serial.println(" Listando Diretorios");
////  Dir dir = SPIFFS.openDir("/");
////  while (dir.next()) {
////    Serial.printf(" %s - %u bytes\n", dir.fileName().c_str(), dir.fileSize());
////  }
////  
////}
//
////void lista_arquivos(){
////  File file;
////  file = SPIFFS.open(filename, "r");
////   Serial.println(" Listando Arquivos");
////  if (file) {
////    Serial.printf("Nome: %s - %u bytes\n", file.name(), file.size());
////    while (file.available()){
////      Serial.println(file.readStringUntil('\n'));
////    }
////    file.close();
////  }
////}
//
//
////void check_config(){
////if( strlen(mqtt_server) == 0 &&  strlen(mqtt_port) == 0  && strlen(mqtt_user) == 0 && strlen(mqtt_passwd) == 0 && strlen(mqtt_topic) == 0 && strlen(mqtt_device_name) == 0 && strlen(geo_longitude) == 0 && strlen(geo_latitude) == 0 )
////  {
////      lcd.clear();
////      lcd.setCursor(0,0); 
////      lcd.print("Falta ");
////      lcd.setCursor(0,1);         
////      lcd.print(WiFi.localIP());
////      wifiManager.resetSettings();
////      if (SPIFFS.exists(filename)) {SPIFFS.remove(filename);}
////      ESP.restart();
////  }
////}
//
////void teste_mqtt(){
////  lista_diretorio();
////  lista_arquivos();
////  Serial.println("Servidor:"+String(mqtt_server));
////  Serial.println("Porta:"+String(mqtt_port));
////  Serial.println("User:"+String(mqtt_user));
////  Serial.println("Pass:"+String(mqtt_passwd));
////  Serial.println("Topic:"+String(mqtt_topic));
////  Serial.println("Device Name:"+String(mqtt_device_name));
////  
////  if( !client.connected()){
////    reconnect("teste");
////  }
////  if (client.connect("Esp8266Client", mqtt_user, mqtt_passwd)) {  
////    lcd.clear(); 
////    lcd.setCursor(0,0);     
////    lcd.print("Sending Data..."); 
////    client.publish(mqtt_topic,"teste");
////    client.subscribe(mqtt_topic);
////  }
////  client.loop();
//  
////}
//
//void test_lora() {
//  // put your main code here, to run repeatedly:
//  if( Serial.available() ){
//     String input = Serial.readString();
//     loraSerial.println(input);    
//  }
//  if( loraSerial.available() ){
//     String input = loraSerial.readString();
//     Serial.println(input);  
//  }
//  loraSerial.println("ping server");
//  delay(3000);
//}
//
//void setup() {
////  wifiManager.resetSettings();
////  if (SPIFFS.exists(filename)) {SPIFFS.remove(filename);}
////  while (!SPIFFS.begin()) ;
////  initDisplay();
////  if (WiFi.status()== WL_CONNECTED){initMqtt();}
//  initSerialLora();  
//
//  pinMode(LED_BUILTIN, OUTPUT);
//  Serial.println("Server Lora Ativo."); 
//  
//}
//
//
//void loop() {
//  digitalWrite(LED_BUILTIN, LOW);   
//  delay(1000);                      
//  digitalWrite(LED_BUILTIN, HIGH);
//  delay(2000);
//  test_lora();
//  //  teste_mqtt(); 
////  lcd.clear();
////  lcd.setCursor(0,0); 
////  lcd.print("Wifi Status:"+WiFi.status());
////  if (WiFi.status()== WL_CONNECTED){
////        Serial.println(" Conectado ao Wifi");
////        lcd.clear();
////        lcd.setCursor(0,0); 
////        lcd.print("IP:");
////        lcd.setCursor(0,1);         
////        lcd.print(WiFi.localIP());
////        delay(2000); 
////        execLora();
////        delay(2000);
////        initNTP(); 
////        getNTPtime(10);
////  }
////  else{
////      Serial.println(" Falha ao Conectar ao Wifi");
////      lcd.clear();
////      lcd.setCursor(0,0);
////      lcd.print("Aguardando Conexao no AP....");
////      lcd.setCursor(0,1);
////      lcd.print("Modo Access Point....");
////      lcd.setCursor(0,2);
////      lcd.print("Pressione Reset");
////      lcd.setCursor(0,3);
////      lcd.print("ao autenticar");
////      if (SPIFFS.exists(filename)) {SPIFFS.remove(filename);}
////      setupWifiManager();
////      mountSystemFiles();
////      enableAPmode();
////      delay(2000);
////  }
//}

#include <SoftwareSerial.h>
#define TX D5
#define RX D6


SoftwareSerial loraSerial(TX,RX);

void initSerialLora(){
  Serial.begin(9600);
  loraSerial.begin(9600);
  while(!loraSerial){;}
  while(!Serial){;} 
}

void initMqtt() {
     client.setServer("mqtt.claraideia.com.br",atoi("1883"));
}


void initDisplay(){
  lcd.begin (20,4);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Inicializando o");
  lcd.setCursor(0,1);
  lcd.print("Dispositivo");
  
}

void reconnect(char payload[400]) {
  while (!client.connected()) {
    if (client.connect("Esp8266Client", "claraideiaIOT", "claraideia1817698")) {
      client.publish("/iot/claraideia/dados",payload);
      client.subscribe("/iot/claraideia/dados");
    } else {      
      Serial.print(client.state());
      delay(5000);
    }
  }
}



void execMqtt(JsonObject& root){
  char payload[400];
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["description"] = "DHT11";
  json["temperature"] = root["temperatura"].as<String>();  
  json["humid"] = root["humidade"].as<String>(); 
  json["humid_solo"] = root["humidade-solo"].as<String>(); 
  //json["data_reading"] = showTime(timeinfo);
  json["station_name"] = "STA001";
//  json["longitude"] = geo_longitude;
//  json["latitude"] = geo_latitude;
  json.printTo(payload);
  if( !client.connected()){
    reconnect(payload);
  }
  if (client.connect("Esp8266Client", "claraideiaIOT", "claraideia1817698")) {  
    lcd.clear(); 
    lcd.setCursor(0,0);     
    lcd.print("Sending Data..."); 
    client.publish("/iot/claraideia/dados",payload);
    client.subscribe("/iot/claraideia/dados");
  }
  client.loop();
}

void execDisplay(String Temp,String Humid, String Humid_Solo){
  //acende o backlight do LCD
  lcd.setBacklight(HIGH);
  //posiciona o cursor para escrita
  lcd.setCursor(0,0);
  lcd.print("");
  lcd.print("Dados Recebidos");
  lcd.setCursor(0,1);
  lcd.print("Temperatura: "+Temp);
  lcd.setCursor(0,2);
  lcd.print("Humid: "+Humid);
  lcd.setCursor(0,3);
  lcd.print("Humid Solo: "+Humid_Solo);
  delay(2000); //intervalo de 1s
  lcd.clear();
}

void execLora(){
  while (!loraSerial.available()){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Dispositivo");
    lcd.setCursor(0,1);
    lcd.print("Tentando");
    lcd.setCursor(0,2);
    lcd.print("Comunicacao...");
    delay(1000);
  }
  if( loraSerial.available()){
      DynamicJsonBuffer jsonBuffer;           
      String output = loraSerial.readString();
      JsonObject& root = jsonBuffer.parseObject(output);
      String temp =  root[String("temperatura")];  
      String humid = root[String("humidade")];  
      //String humid_solo = root[String("humidade-solo")];  
      String humid_solo = "0";
      execDisplay(temp,humid,humid_solo);
      loraSerial.println("Server Pong");
      //execMqtt(root);
  }
}


void setup() {
  initSerialLora();
  initDisplay();
  initMqtt();
  Serial.println("Inicializando a Server");
  delay(3000);
}


void loop() {
// put your main code here, to run repeatedly:
  if( Serial.available()){
     String input = Serial.readString();
     loraSerial.println(input);     
  }
  if( loraSerial.available()){
     String input = loraSerial.readString();
     Serial.println(input);  
  }
  execLora();
  delay(1000);
}
