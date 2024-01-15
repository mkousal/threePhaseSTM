#include <Arduino.h>

void setup()
{
  
  pinMode(3, INPUT);   //PWM is set to input before PWM initialized to prevent start up short circuit
  pinMode(5, INPUT);   //PWM is set to input before PWM initialized to prevent start up short circuit
  pinMode(6, INPUT);   //PWM is set to input before PWM initialized to prevent start up short circuit
  pinMode(9, INPUT);   //PWM is set to input before PWM initialized to prevent start up short circuit
  pinMode(10, INPUT);   //PWM is set to input before PWM initialized to prevent start up short circuit
  pinMode(11, INPUT);   //PWM is set to input before PWM initialized to prevent start up short circuit
  pinMode(13, OUTPUT);  //TRIG vystup pro oscilo
 }

uint8_t pwm_ph0H=0;
uint8_t pwm_ph1H=0;
uint8_t pwm_ph2H=0;
uint8_t pwm_ph0L=0;
uint8_t pwm_ph1L=0;
uint8_t pwm_ph2L=0;

int x0H=0;
int x1H=0;
int x2H=0;
int x0L=0;
int x1L=0;
int x2L=0;

int x=1;
int pwm=0;

uint8_t sinPWM[]={0,2,6,12,20,29,40,53,66,81,96,112,128,143,159,174,189,202,215,226,235,243,249,253,255,255,253,249,243,235,226,215,202,189,174,159,143,
128,112,96,81,66,53,40,29,20,12,6,2,0,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0,2,6,12,20,29,40,53,66,81,96,112,128,143,159,174,189,202,215,226,235,243,249,253,255,255,253,249,243,235,226,215,202,189,174,159,143,
128,112,96,81,66,53,40,29,20,12,6,2,0,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};



void update_pwm(void)
{
   while(TCNT0 > 0x7F)
 {
 }
 //Now it's safe to update OCR0x pair (connect to same transistor pair)
  OCR0A = (~pwm_ph0L);//~6 TL PH0 TMR0
  OCR0B = (pwm_ph0H);//~5 TH PH0 TMR0
 while(TCNT1 > 0x7F)
 {
 }
 //Now it's safe to update OCR1x pair (connect to same transistor pair)
  OCR1A = (~pwm_ph1L);//~9 TL PH1 TMR1
  OCR1B = (pwm_ph1H);//~10 TH PH1 TMR1
 while(TCNT2 > 0x7F)
 {
 }
 //Now it's safe to update OCR2x pair (connect to same transistor pair)
  OCR2A = (~pwm_ph2H);//~3 TH PH2 TMR2
  OCR2B = (pwm_ph2L);//~11 TL PH2 TMR2
}

void sync_pwm_timers(void)
{
  GTCCR = (GTCCR & 0xFF) | 0x81;// Set bit Bit 7 – TSM: Timer/Counter Synchronization Mode
  //Writing the TSM bit to one activates the Timer/Counter Synchronization mode. In this mode, the value that is written
  //to the PSRASY and PSRSYNC bits is kept, hence keeping the corresponding prescaler reset signals asserted.
  //This ensures that the corresponding Timer/Counters are halted and can be configured to the same value without
  //the risk of one of them advancing during configuration. When the TSM bit is written to zero, the PSRASY and
  //PSRSYNC bits are cleared by hardware, and the Timer/Counters start counting simultaneously.
  TCNT0 = 00;//Syncronize PWM timers
  TCNT1 = 0x0000;//Syncronize PWM timers
  TCNT2 = 0x00;//Syncronize PWM timers
  GTCCR = (GTCCR & 0x7E);// Rest bit Bit 7 – TSM: Timer/Counter Synchronization Mode
}

void loop()
{

  TCCR1A = 0xe1;//PWM, Phase Correct 8-bit TOP at 0xFF 
  TCCR0A = 0xe1;//PWM, Phase Correct 8-bit TOP at 0xFF 
  TCCR2A = 0xe1;//PWM, Phase Correct 8-bit TOP at 0xFF 
  TCCR2B = 0x01;//clkI/O/1 (No prescaling) 31.25kHz PWM frequency
  TCCR1B = 0x01;//clkI/O/1 (No prescaling) 31.25kHz PWM frequency
  TCCR0B = 0x01;//clkI/O/1 (No prescaling) 31.25kHz PWM frequency
  sync_pwm_timers();

 pinMode(3, OUTPUT);   //PWM output
  pinMode(5, OUTPUT);   //PWM output
  pinMode(6, OUTPUT);   //PWM output
  pinMode(9, OUTPUT);   //PWM output
  pinMode(10, OUTPUT);   //PWM output
  pinMode(11, OUTPUT);   //PWM output

   while(1)
  { x++;
    
   if(x==50) {

digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
 // delay(1);                       // wait for a second
 }

if(x==100) {
x=0;
digitalWrite(13, HIGH);    // turn the LED off by making the voltage LOW
 // delay(1);                       // wait for a second
  } 
    

    pwm_ph0H=sinPWM[x]-1;
    pwm_ph1H=sinPWM[x+16]-1;
    pwm_ph2H=sinPWM[x+33]-1;
    pwm_ph0L=sinPWM[x+50]-1;
    pwm_ph1L=sinPWM[x+66]-1;
    pwm_ph2L=sinPWM[x+83]-1;
    update_pwm();
delayMicroseconds(149);
     }
}