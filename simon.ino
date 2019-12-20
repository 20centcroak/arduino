/*
  Simon
  plays a sequence and player has to repeat it.

  
  This example code is in the public domain.

 */
const int LED_G = 2;
const int LED_R = 3;
const int LED_B = 4;
const int LED_Y = 5;
const int BUT_G = 10;  //=LED_B+8
const int BUT_R = 11;  //=LED_R+8
const int BUT_B = 12;  //=LED_B+8
const int BUT_Y = 13;  //=LED_Y+8
const int light = 300;
int nbre_seq = 0;
int nbre_boucle = 0;
long seq[10];
boolean attente = false;


// the setup function runs once when you press reset or power the board
void setup() {  
  Serial.begin(9600);
  // initialize digital pin 2 to 5 as an output and 10 to 13 as input
  for (int i=2; i< 6; i++){
    pinMode(i, OUTPUT);
    pinMode(15-i,INPUT);
  }
  nbre_boucle = 0;
  nbre_seq = 0;
  attente = false;
  initLED();
}

void initLED(){
  digitalWrite(LED_G, HIGH);
  delay(light);
  digitalWrite(LED_R, HIGH);
  delay(light);
  digitalWrite(LED_B, HIGH);
  delay(light);
  digitalWrite(LED_Y, HIGH);
  delay(light*4);
  digitalWrite(LED_Y, LOW);
  delay(light);
  digitalWrite(LED_B, LOW);
  delay(light);
  digitalWrite(LED_R, LOW);
  delay(light);
  digitalWrite(LED_G, LOW);
  delay(light*4);
}

// the loop function runs over and over again forever
void loop() {
  
  if (nbre_boucle==10) return;
  
  if (!attente) {
    sequence();
    nbre_boucle++;
    attente = true;
  }
  else{
    getResult();
  }
}


//ajoute un point aléatoire à la séquence précédente et joue l'ensemble de la séquence
void sequence(){
  
  randomSeed(analogRead(0));
  long randNumber = random(2,6);
  
  seq[nbre_seq] = randNumber;

  Serial.print("seq :");

  for(int i=0; i<nbre_seq+1; i++){
    Serial.print(seq[i]);
    Serial.print(" ");
    digitalWrite(seq[i],HIGH);
    delay(light);
    digitalWrite(seq[i],LOW);
    delay(light);
  }
  Serial.println("-");
  nbre_seq++; 
}

void getResult(){
  
  boolean perdu = false;
  
  Serial.print("Res : ");

    int switchstate=0;    
    int but_Y = 0;
    int but_B = 0;
    int but_R = 0;
    int but_G = 0;
  
  for (int i=0; i<nbre_seq; i++){
    int previous = but_Y*LED_Y + but_B*LED_B + but_R*LED_R + but_G*LED_G;
    
    //while(switchstate != 1){
    while(true){
      but_Y = digitalRead(BUT_Y);
      but_B = digitalRead(BUT_B);
      but_R = digitalRead(BUT_R);
      but_G = digitalRead(BUT_G);
      //switchstate = but_Y +but_B + but_R + but_G;
      switchstate = but_Y*LED_Y + but_B*LED_B + but_R*LED_R + but_G*LED_G;
      if (switchstate==0) previous = 0;
      else{
        if (switchstate == previous) continue;
        else break;
      }
    }
    if (but_Y == 1) {
      Serial.print(LED_Y);
      if (seq[i]!=LED_Y) {
        perdu = true;
        but_Y = 0;
      }
    }
     else if (but_B == 1){
       Serial.print(LED_B);
       if (seq[i]!=LED_B) {
        perdu = true;
        but_B = 0;
      }
     }
     else if (but_R == 1){
       Serial.print(LED_R);
       if (seq[i]!=LED_R) {
        perdu = true;
        but_R = 0;
      }
     }
     else if (but_G==1){
       Serial.print(LED_G);
       if (seq[i]!=LED_G) {
          perdu = true;
          but_G = 0;
        }
     }
     
     if(perdu){
       Serial.println(" ! ");
       fin();
       return;
     }
     Serial.print(" ");
  }
  Serial.println("-");
  delay(1000);
  attente = false;
}

void fin(){
  
  for (int i=0; i<5; i++){
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_Y, HIGH);
    delay(2*light);
    digitalWrite(LED_Y, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    delay(2*light);
  }
  
  setup();
  
}

