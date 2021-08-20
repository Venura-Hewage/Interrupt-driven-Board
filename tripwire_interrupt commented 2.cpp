//Github link : https://github.com/Venura-Hewage/Interrupt-driven-Board

int red_light_pin= 11;
int ldr_sensor = A0;
int ldr_value=0;
int laser_diode=9;
int buzzer=10;
int button =2;


const long interval = 500;
void setup() {
	//initialises components specified pin that is connected to the arduino board.
  pinMode(red_light_pin, OUTPUT);
  pinMode(laser_diode,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  Serial.begin(9600);

//attaches interrupt this is there to shut down the alarm which consists of the red LED as well as the buzzer.

  attachInterrupt(digitalPinToInterrupt(button),shutdown_lasertrip_alarm,CHANGE);

}

void loop() {

 //This measures time from the begining of the loop.
unsigned long currentMillis = millis();
//Activates the laser diode. Laser is pointed at the LDR(light dependent resistor).
digitalWrite(laser_diode, HIGH);

//Reads out ldr values . The higher the value the stronger the amount of light that the  LDR is  detecting.
ldr_value =analogRead(ldr_sensor);


//A threshold of less than  800 is set for the ldr_Value(This is an arbitary amount we guess is enough when we block the laser beam from reaching the LDR that will result in the ldr values to drop off from   constantly going beyond our threshold value).
//we put another condition where currentMillis must be greater than our interval time(we set at 500ms here). We do this  because when the loop is starting up intially the ldr values will be below the threshold because the laser diode needs a bit of time to start up.
if(ldr_value < 800 && currentMillis > interval)
{
 //The LED turns on as well as the buzzer if the ldr is below the threshold as well when the time passed between the loop starting is greater than the interval(500ms).
 digitalWrite(red_light_pin, HIGH);
 tone(buzzer,1000);


}


}

//The method is used for the interrupt. It is triggered when the button is pushed.
void shutdown_lasertrip_alarm()
{
  Serial.println("Shut down laser trip alarm interrupt triggered");
  //Turns off the LED light and buzzer
  digitalWrite(red_light_pin, LOW); 
  noTone(buzzer);

}
