#include <OneWire.h>

//iButton Variables
OneWire  ds(7);
byte addr[8];
int but[6] = {0,149,107,48,13,0};
String keyStatus = "";


void setup()  
{
  Serial.begin(9600);
  //Set up iButton
  pinMode(11, OUTPUT);
  //Print a ready message
  //Serial.println("ready");
}

//The char in iButton
char c;

void loop(){
  //Checks OneWire for iButton info
  checkiButton();
  
}

void checkiButton() {
  digitalWrite(11, HIGH);
  //Get info on the key
  getKeyCode();
  //if the key is good go through this
  if(keyStatus=="ok"){
      int i;
      //For CSH iButtons there are 7 code segments in hexidecimal 
      for( i = 7; i >= 0; i--) {
        
        //Adds leading zeros to hex if only one character long
        if( addr[i] < 0x10){ 
        Serial.print("0");
        }
        
        //Prints rest of hex
       Serial.print(addr[i], HEX);
       
      }
      
      //Keep a delay so that it doesn't mistakenly read the same iButton more than once
      digitalWrite(11, LOW);
      delay(3000);
      //Makes a new line
      Serial.println();
      
  }
  else if (keyStatus!="") {
    Serial.print(keyStatus);
  }
  }

//This does a lot of weird stuff about seeing if the data in the iButton is worth getting
void getKeyCode(){
  byte present = 0;
  byte data[12];
  keyStatus="";
  if ( !ds.search(addr)) {
      Serial.print("");
      ds.reset_search();
      return;
  }
  keyStatus="ok";
  ds.reset();
}
