#define x_pin A0
#define y_pin A1
#define sw_pin 3

void setup(){
  pinMode(x_pin, INPUT);
  pinMode(y_pin, INPUT);
  pinMode(sw_pin, INPUT);

  Serial.begin(9600);

}

void loop(){
  int x_data = analogRead(x_pin);
  int y_data = analogRead(y_pin);
  int sw_data = digitalRead(sw_pin);

  Serial.print("ข้อมูลแกน x:");
  Serial.println(x_data);

  Serial.print("ข้อมูลแกน y:");
  Serial.println(y_data);

  Serial.print("ข้อมูลป่มสวิตซ์:");
  Serial.println(sw_data);

  delay(100);

}




