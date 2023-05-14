//      ZENRAY
//      A portable light therapy device that uses researched frequencies to lessen users' anxiety, depression and insomnia symptoms. We will use a device consisting of 9-12 white led lights, controlled by arduino and program 2-3 presets for our MVP that focus on different areas (amusement and stress relief, insomnia relief). The programmes will be based on extensive research in the area that has been carried out since the 70s, our unique selling point is that the device is affordable and portable (similar solutions cost up to 2000 euros on the market right now and are tedious to set up), possibly syncable with music.
// this is a nodemcu esp8266 web server that will be used to control the device via wifi and a web browser

#include <Arduino.h>
#include <WiFi.h>

// we also make use of MAX7219 8x8 LED matri
// import the library for the LED matrix
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <SPI.h>

// define the number of devices we have in the chain and the hardware interface
//#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 2

// set up the LED matrix
#define CS_PIN    13

// set up the display
//MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_MAX72XX myDisplay = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


// parameters: type, data in, clock, load, number of devices

// This needs to be an existing endpoint (smartphone hotspot)
const char* ssid = "Casa Mob";
const char* password = "zenray123";
const char* WEBSITE = "<!-- ZENRAY A portable light therapy device that uses researched frequencies to lessen users' anxiety, depression and insomnia symptoms. We will use a device consisting of 9-12 white led lights, controlled by arduino and program 2-3 presets for our MVP that focus on different areas (amusement and stress relief, insomnia relief). The programmes will be based on extensive research in the area that has been carried out since the 70s, our unique selling point is that the device is affordable and portable (similar solutions cost up to 2000 euros on the market right now and are tedious to set up), possibly syncable with music. This is a web interface where the user can select a certain program and a function with that program name will then be called. The user can also see a dashboard of the device's current status and the current program running. The user can also see a log of the device's activity. This is pure HTML, CSS and JS, no PHP or SQL. This website will always be displayed on a phone screen --><html><head> <title>ZenRay</title> <link rel=\"stylesheet\" href=\"style.css\"> <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js\"></script> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"></head><body onload=\"getProgram()\"><div class=\"container\"> <div class=\"header\"> <h1>ZenRay</h1> </div><div class=\"content\"> <div class=\"dashboard\"> <h2>Dashboard</h2> <div class=\"dashboard-content\"> <div class=\"dashboard-item\"> <h3>Current program</h3> <p id=\"current-program\">None</p></div><div class=\"dashboard-item\"> <h3>Current status</h3> <p id=\"current-status\">Off</p></div><div class=\"dashboard-item\"> <h3>Log</h3> <p id=\"log\">None</p></div></div></div><div class=\"program\"> <h2>Program</h2> <div class=\"program-content\"> <div class=\"program-item\"> <h3>Programs</h3> <div class=\"program-item-content\"> <button class=\"program-button\" onclick=\"setProgram('amusement')\">Amusement</button> <button class=\"program-button\" onclick=\"setProgram('stress')\">Stress relief</button> <button class=\"program-button\" onclick=\"setProgram('insomnia')\">Insomnia relief</button> </div></div><div class=\"program-item\"> <h3>Functions</h3> <div class=\"program-item-content\"> <button class=\"program-button\" onclick=\"setFunction('on')\">On</button> <button class=\"program-button\" onclick=\"setFunction('off')\">Off</button> </div></div></div></div></div></div><script>function addToLog(message){// add to local storage (add message) function setProgram(program){document.getElementById(\"current-program\").innerHTML=program; // redirect to /runProgram/1 window.location.href=\"/runProgram/\" + program;}function setFunction(func){}function getProgram(){// get program from /getProgram let runningProgram=window.location.href.split(\"/\").pop(); document.getElementById(\"current-program\").innerHTML=runningProgram;}// document on load document.addEventListener(\"DOMContentLoaded\", function(event){getProgram();});</script></body></html><style>/* Simple and minimal style for the web interface of ZenRay */ body{background-color: #f2f2f2; font-family: \"Helvetica Neue\", Helvetica, Arial, sans-serif;}.container{width: 100%; max-width: 800px; margin: 0 auto;}.header{background-color: #333; color: #fff; padding: 20px; text-align: center;}.header h1{margin: 0;}.content{padding: 20px;}.dashboard{background-color: #fff; padding: 20px; margin-bottom: 20px;}.dashboard h2{margin: 0;}.dashboard-content{display: flex; flex-wrap: wrap;}.dashboard-item{flex: 1 1 300px; margin: 10px; padding: 20px; background-color: #f2f2f2;}.dashboard-item h3{margin: 0;}.program{background-color: #fff; padding: 20px;}.program h2{margin: 0;}.program-content{display: flex; flex-wrap: wrap;}.program-item{flex: 1 1 300px; margin: 10px; padding: 20px; background-color: #f2f2f2;}.program-item h3{margin: 0;}.program-item-content{display: flex; flex-wrap: wrap;}.program-button{flex: 1 1 100px; margin: 10px; padding: 20px; background-color: #333; color: #fff; border: none; cursor: pointer;}.program-button:hover{background-color: #555;}</style>";



WiFiServer server(80);


// define the amusement program
// list of arrays (x,y) that will be lit up in a loop
// the first element is the x coordinate, the second is the y coordinate

int AMUSEMENT[50][2] = {
  {1,1}, {1,2}, {1,3}, {1,4}, {1,5},
  {2,1}, {2,2}, {2,3}, {2,4}, {2,5},
  {3,1}, {3,2}, {3,3}, {3,4}, {3,5},
  {4,1}, {4,2}, {4,3}, {4,4}, {4,5},
  {5,1}, {5,2}, {5,3}, {5,4}, {5,5},
  {1,1}, {2,1}, {3,1}, {4,1}, {5,1},
  {1,2}, {2,2}, {3,2}, {4,2}, {5,2},
  {1,3}, {2,3}, {3,3}, {4,3}, {5,3},
  {1,4}, {2,4}, {3,4}, {4,4}, {5,4},
  {1,5}, {2,5}, {3,5}, {4,5}, {5,5}
};

bool RUNNING = false;
int increment = 0;
void sendData() {
  // go sending the data to the device
  // go over the array and light up the leds
  // for each element in the array, light up the corresponding led
  Serial.print(increment);
  myDisplay.setPoint(increment, 3, true);
  delay(1000);
}

bool runProgram(){
  RUNNING = true;
  Serial.println("running program");
  return RUNNING;
}

bool stopProgram(){
  // we need to stop the program that is currently running
  RUNNING = false;
  Serial.println("stopping program");
  // clear the display and turn off the lights

  return RUNNING;
}

#include <cstdlib>
#include <ctime>

int getRandomInt(int min, int max) {
    // Generate a random number between min and max inclusive
    int randomNum = std::rand() % (max - min + 1) + min;

    return randomNum;
}



/* void defineInterfaceEndpoints(server) {
   Has to take the following parameters:
   - server object
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);
  Serial.println("");

  // setup pin 12
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
}

bool CONNECTED = false;

void onConnect() {
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("HTTP server started");
  CONNECTED = true;
}

void displayGreet() {
  // initialize the display
  myDisplay.begin();


  // create a line along the first and second dispay
  // X [0-7] Y[0-16]
  for (int i = 0; i < 5000; i++) {
    int randX = getRandomInt(0,7);
    int randY = getRandomInt(0,16);
    myDisplay.setPoint(randX, randY, !myDisplay.getPoint(randX, randY));
    delay(10);
  }
}

void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    // flash the led on pin 12
    analogWrite(12, 255);
    delay(1000);
    analogWrite(12, 0);
    delay(500);
    Serial.write(".");
    return;
  }
  if (!CONNECTED && WiFi.status() == WL_CONNECTED) {
    onConnect();
  }




  if (RUNNING) {
    if (increment < 8) {
      increment += 1;
      Serial.print(increment);
      Serial.write(" Was the increment\n");
    } else {
      stopProgram();
    }
  }
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            client.println(WEBSITE);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /runProgram/1")) {
          runProgram();
        } else if (currentLine.endsWith("GET /runProgram/2")) {
          runProgram();
        } else if (currentLine.endsWith("GET /stopProgram")) {
          stopProgram();
        }

      }
    }


  }

}
