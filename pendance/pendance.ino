int slide_g = 9;
int slide_y = 8;

void setup() {                
  pinMode(slide_g, INPUT);
  pinMode(slide_y, INPUT);  
  pinMode(13, OUTPUT);
}

void loop() {

    
}

void test_slide() {
   if (digitalRead(slide_g) == LOW){
    digitalWrite(13, HIGH);
  }else if (digitalRead(slide_y) == LOW){
    digitalWrite(13, LOW);
  } 
}
