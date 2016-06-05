int slide_g = 8;
int slide_y = 7;
int reset = 6;
int panic = 5;
int red_led = 11;
int blue_led = 10;
int green_led = 9;

void setup() {                
  pinMode(slide_g, INPUT);
  pinMode(slide_y, INPUT);  
  pinMode(reset, INPUT);
  pinMode(panic, INPUT);
  pinMode(red_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  pinMode(green_led, OUTPUT);

}

void loop() {

}

void setColor(int red, int green, int blue)
{
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
  analogWrite(red_led, red);
  analogWrite(green_led, green);
  analogWrite(blue_led, blue);  
}

void test_led() {
  setColor(255, 0, 0);  // red
  delay(1000);
  setColor(0, 255, 0);  // green
  delay(1000);
  setColor(0, 0, 255);  // blue
  delay(1000);
  setColor(255, 255, 0);  // yellow
  delay(1000);  
  setColor(80, 0, 80);  // purple
  delay(1000);
  setColor(0, 255, 255);  // aqua
  delay(1000); 
}

void test_push_buttons() {
  if (digitalRead(reset) == LOW) {
    digitalWrite(13, HIGH);
  }else{
    digitalWrite(13, LOW);
  }
  
  if (digitalRead(panic) == LOW) {
    digitalWrite(13, HIGH);
  }else{
    digitalWrite(13, LOW);
  } 
}

void test_slide() {
   if (digitalRead(slide_g) == LOW){
    digitalWrite(13, HIGH);
  }else if (digitalRead(slide_y) == LOW){
    digitalWrite(13, LOW);
  } 
}
