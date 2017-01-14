
//step size for fading animation
const int INC=5;

const int analogInPin = A3;  // Analog input pin that the potentiometer is attached to
const int bPin = 0; // Blue pin
const int rPin = 4;// Red Pin
const int gPin = 1; //Green Pin
const int button =2 ; // button for turn of the light

int sensorValue = 0;        // value read from the potentiometer


int reedOut=0;
int greenOut=0;
int blueOut=0;

//for the animation
unsigned long timeOld=0;
unsigned long timeNew=201;

int incB=0;
int incR=-INC;
int incG=INC;
boolean first=true;

//////////////

int buttonValue;



void setup() {
  pinMode(button, INPUT_PULLUP); //button pin set to input. using internal pull-up resistor 

}

void loop() {
    // read the analog in value:
  sensorValue = analogRead(analogInPin);
  
  // map it to the range of the analog out:
  //outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:


  //read th button state
  buttonValue=digitalRead(button);

  //if button state is low turn off the light
  if(sensorValue >=0 && buttonValue==HIGH){
      if(sensorValue<=255 && sensorValue>=0){ //from red to green
  
        greenOut=sensorValue;
        reedOut=255-(sensorValue);
        blueOut=0;
      }
      else if( sensorValue>255 && sensorValue<= 510){ //from green to blue
        greenOut=255-(sensorValue-255);
        reedOut=0;
        blueOut=sensorValue-255;
      }
      else if( sensorValue>510 && sensorValue<= 765){ //from blue to red
        greenOut=0;
        reedOut=sensorValue-510;
        blueOut=255-(sensorValue-510);
      }
      else if (sensorValue > 765 && sensorValue <=950){ //white
        
        greenOut=255;
        reedOut=255;
        blueOut=255;
  
        
        first=true;
      }
      else{ //animation, fading through the colours
        
        timeNew = millis();
  
        if(first){
          first=false;
          greenOut=0;
          reedOut=255;
          blueOut=0;
  
          incB=0;
          incR=-INC;
          incG=INC;
        }
  
        if(timeNew-timeOld>1){
          //random(0, 255);
          greenOut=greenOut+incG<=255? greenOut+incG:greenOut;
          reedOut=reedOut+incR<=255? reedOut+incR :reedOut;
          blueOut=blueOut+incB<=255? blueOut+incB :blueOut;
  
          if(reedOut==0 && greenOut==255 && blueOut==0){
            incR=0;
            incG=-INC;
            incB=INC;
          }
          else if(reedOut==0 && greenOut==0 && blueOut==255){
            incR=INC;
            incG=0;
            incB=-INC;
          }
          else if(reedOut==255 && greenOut==0 && blueOut==0){
            incR=-INC;
            incG=INC;
            incB=0;
          }
  
          timeOld=timeNew;
        }
      }

      analogWrite(bPin, blueOut);
      analogWrite(gPin, greenOut);
      analogWrite(rPin, reedOut);
    }
    else{
      analogWrite(bPin, 0);
      analogWrite(gPin, 0);
      analogWrite(rPin, 0);
    }
    
  
    delay(2);
}
