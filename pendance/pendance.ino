int slide_g = 9;
int slide_y = 8;
int reset = 7;
int panic = 6;

void setup() {                
  pinMode(slide_g, INPUT);
  pinMode(slide_y, INPUT);  
  pinMode(reset, INPUT);
  pinMode(panic, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {

    
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
