//      ZENRAY
//      A portable light therapy device that uses researched frequencies to lessen users' anxiety, depression and insomnia symptoms. We will use a device consisting of 9-12 white led lights, controlled by arduino and program 2-3 presets for our MVP that focus on different areas (amusement and stress relief, insomnia relief). The programmes will be based on extensive research in the area that has been carried out since the 70s, our unique selling point is that the device is affordable and portable (similar solutions cost up to 2000 euros on the market right now and are tedious to set up), possibly syncable with music.
// this is a nodemcu esp8266 web server that will be used to control the device via wifi and a web browser

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// This needs to be an existing endpoint (smartphone hotspot)
const char* ssid = "Zenray";
const char* password = "zenray123";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found");
}

bool runProgram(name){
  // we need to stream the program to the device and then run it

}

bool stopProgram(){
  // we need to stop the program that is currently running

}


void defineInterfaceEndpoints(server) {
  // POST /runProgram/:name
  server.on("/runProgram/:name", HTTP_POST, [](){
    if (server.hasArg("name")) {
      String name = server.arg("name");
      if (runProgram(name)) {
        server.send(200, "text/plain", "program started");
      } else {
        server.send(500, "text/plain", "program failed to start");
      }
    } else {
      server.send(400, "text/plain", "missing program name");
    }
  });

  // POST stop program
  server.on("/stopProgram", HTTP_POST, [](){
    if (stopProgram()) {
      server.send(200, "text/plain", "program stopped");
    } else {
      server.send(500, "text/plain", "program failed to stop");
    }
  });

  // GET /status
  server.on("/status", HTTP_GET, [](){
      // TODO: return status
    server.send(200, "text/plain", "status");
  });
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });


  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

}


void loop() {
  server.handleClient();

}