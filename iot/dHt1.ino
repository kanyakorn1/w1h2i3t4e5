#include <dhtnew.h>

DHTNEW mySensor(5); 

void setup() {
  Serial.begin(115200);
}

void loop() {
  mySensor.read();
  Serial.print("ค่าความชื้นในอากาศ: ");
  Serial.print(mySensor.getHumidity(), 2);
  Serial.println(" %");
  Serial.print("ค่าอุณหภูมิของอากาศ: ");
  Serial.print(mySensor.getTemperature(), 2);
  Serial.println(" องศา");
  delay(1000);

}
