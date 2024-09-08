/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA2 encryption. For insecure
 WEP or WPA, change the Wifi.begin() call and use Wifi.setMinSecurity() accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32
31.01.2017 by Jan Hendrik Berlin

 */

#include <WiFi.h>

const char* ssid     = "yourssid";
const char* password = "yourpasswd";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);  // set the LED pin mode
  pinMode(4, OUTPUT);  // set the LED pin mode

  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print(" กำลังเชื่อมต่อ ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("เชื่อมต่อไวไฟสำเร็จ.");
  Serial.println("เบอร์ IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

}

void loop() {
  WiFiClient client = server.accept();  // listen for incoming clients

  if (client) {                     // if you get a client,
    Serial.println("เชื่อมต่อกับอุปกรณ์.");  // print a message out the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        Serial.write(c);            // print it out the serial monitor
        if (c == '\n') {            // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head>");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("</head>");

            client.println("</body>");
            client.println("<h1>University of Phayao</h1>");
            client.println("<p>Computer Engineering Department");
            client.println("</body>");
            
            

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

            client.print("Click <a href=\"/A\">here</a> to turn the LED on pin 4 on.<br>");
            client.print("Click <a href=\"/B\">here</a> to turn the LED on pin 4 off.<br>");

            client.print("Click <a href=\"/C\">here</a> to turn the LED on pin 3 on.<br>");
            client.print("Click <a href=\"/D\">here</a> to turn the LED on pin 3 off.<br>");

            client.print("Click <a href=\"/X\">here</a> to turn the LED on pin 2 on.<br>");
            client.print("Click <a href=\"/Y\">here</a> to turn the LED on pin 2 off.<br>");




            // The HTTP response ends with another blank line:
            client.println();
            client.println("</html>");
            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(5, HIGH);  // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(5, LOW);  // GET /L turns the LED off
        }
         if (currentLine.endsWith("GET /A")) {
          digitalWrite(4, HIGH);  // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /B")) {
          digitalWrite(4, LOW);  // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /C")) {
          digitalWrite(3, HIGH);  // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /D")) {
          digitalWrite(3, LOW);  // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /X")) {
          digitalWrite(2, HIGH);  // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /Y")) {
          digitalWrite(2, LOW);  // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("ยกเลิกการเชื่อมต่อกับอุปกรณ์.");
  }
}