// // #include <Arduino.h>
// // #include <avr/interrupt.h>

// // const int pwmPin1 = 3;   // PWM pin 1
// // const int pwmPin2 = 5;   // PWM pin 2
// // const int pwmPin3 = 6;   // PWM pin 3
// // const int pwmPin4 = 9;   // PWM pin 4
// // const int pwmPin5 = 10;  // PWM pin 5
// // const int pwmPin6 = 11;  // PWM pin 6

// // void setup() {
// //   // Set the PWM pins as outputs
// //   pinMode(pwmPin1, OUTPUT);
// //   pinMode(pwmPin2, OUTPUT);
// //   pinMode(pwmPin3, OUTPUT);
// //   pinMode(pwmPin4, OUTPUT);
// //   pinMode(pwmPin5, OUTPUT);
// //   pinMode(pwmPin6, OUTPUT);

// //   // Configure Timer1 for PWM generation
// //   // TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1C1) | _BV(WGM10);
// //   TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
// //   TCCR1B = _BV(WGM12) | _BV(CS10);

// //   // Set the PWM frequency to 10 kHz
// //   OCR1A = 79;   // Adjust this value for desired duty cycle (0-255)
// //   OCR1B = 79;
// //   // OCR1C = 79;
// // }

// // void loop() {
// //   // No need for further code in the loop since we're using Timer1 for PWM generation
// // }

#include <Arduino.h>
#include <avr/interrupt.h>
#include <math.h>

#define pi 3.1415926535897932384626433832795
#define TOP0 255
#define TOP1 255
#define TOP2 255
#define M 1.0
#define F 50.0

// PWM 1-2 = PIN 5-6
// PWM 3-4 = PIN 9-10
// PWM 5-6 = PIN 3-11

// PWM pin 10 = 5 = 3
// PWM pin 11 = 9 = 6

// volatile double t = 0.0;
// volatile float data1, data2, data3;
volatile byte TEST = 0;
volatile int i = 0;
// char buf[12];

// ISR (TIMER1_OVF_vect){        //TIMER1_OVF_vect 
//     TCNT0 = 0;
//     TCNT1 = 0;
//     TCNT2 = 0;
    
//     data1 = (M * TOP1 * sin(2.0*PI*F*t/62500.0) + TOP1) / 2;
//     data2 = (M * TOP1 * sin(2.0*PI*F*t/62500.0 + 2.0*PI/3.0) + TOP1) / 2;
//     data3 = (M * TOP1 * sin(2.0*PI*F*t/62500.0 + 4.0*PI/3.0) + TOP1) / 2;
//     // OCR0A = data1;           // PWM Pin 6 
//     // OCR0B = data1;           // PWM Pin 5 inverted
//     // OCR1A = data2;           // PWM Pin 9
//     // OCR1B = data2;           // PWM Pin 10 inverted
//     // OCR2A = data3;           // PWM Pin 11
//     // OCR2B = data3;           // PWM Pin 3 inverted
//     OCR0A = 100;           // PWM Pin 6 
//     OCR0B = 100;           // PWM Pin 5 inverted
//     OCR1A = 100;           // PWM Pin 9
//     OCR1B = 100;           // PWM Pin 10 inverted
//     OCR2A = 100;           // PWM Pin 11
//     OCR2B = 100;           // PWM Pin 3 inverted

//     // Serial.println(data1);
//     // Serial.println(data2);
//     // Serial.println(data3);
//     // f2str(data, buf);
//     // Serial.println(buf);
//     // if (t >= 100)
//     // {
//     //     // TEST = ~TEST;
//         // 
//     // }
//     // else digitalWrite(2, 0);

//     t += 1;          // 1/62500
//     if (t >= 1249){     // 1/Fsin - 1/62500 - 1/62500/4
//         t = 0.0;
//     }
    
// }

// void setup() {
//     // Serial.begin(115200);
//     // pinMode(2, OUTPUT);
//     // PWM by timer 2 and Interrupt ---------------------------------------------------
//     TCNT2 = 0;
//     TCCR2A = 0; TCCR2B = 0;
//     DDRD |= (1 << PD3);   // output Pin 3
//     DDRB |= (1 << PB3);   // output Pin 11
//     TCCR2A |= (1 << COM2A1);    // None-inverted Pin 11
//     TCCR2A |= (1 << COM2B1) | (1 << COM2B0);    // inverted Pin 3
//     TCCR2A |= (1 << WGM21) | (1 << WGM20);      // Xung rang cua
//     TCCR2B |= (0 << CS22) | (0 << CS21) | (1 << CS20);  // Prescaler
//     // OCR2A = TOP2 - 1;              // Frequence = (16000000/((TOP2 + 1) * Prescaler))
    
//     //TIMSK2 |= (1 << OCIE2A);  // Output Compare Match A Interrupt Enable
//                                 // TIMER2_COMPA_vect
            
//     // TIMSK2 |= (1 << TOIE2); // Timer2 Overflow Interrupt Enable
//     // sei();                  // Enable global interrupts   

//     // PWM by timer 0 ---------------------------------------------------
//     TCNT0 = 0;
//     TCCR0A = 0; TCCR0B = 0; // Reset 2 registers
//     DDRD |= (1 << PD5);     // PD5 is OUTPUT (pin 5)
//     DDRD |= (1 << PD6);     // PB1 is OUTPUT (pin 6 )   
    
//     TCCR0A |= (1 << WGM01) | (1 << WGM00);
//     TCCR0A |= (1 << COM0B1);  // Fast mode Pin 5
//     TCCR0A |= (1 << COM0A1);  // Fast mode Pin 6
//     TCCR0A |= (1 << COM0A1);    // None-inverted mode Pin 6
//     TCCR0A |= (1 << COM0B1) | (1 << COM0B0);  // inverted mode Pin 5

//     TCCR0B |= (1 << CS10);   // No Prescaling = F_Clock or F_clock/1=16mhz
//     TCCR0B = TCCR0B & B11111000 | B00000001; // for PWM frequency of 62500.00 Hz
//     // Frequence = Fpwm / 256 = 62500 Hz
//     // Top value = 256


//     // PWM by timer 1 -------------------------------------------------
//     TCNT1 = 0;
//     TCCR1A = 0; TCCR1B = 0; // Reset 2 registers
//     DDRB |= (1 << PB2);     // PB2 is OUTPUT (pin 10)
//     DDRB |= (1 << PB1);     // PB1 is OUTPUT (pin 9 )   
    
//     TCCR1A |= (1 << WGM11);
//     TCCR1B |= (1 << WGM12)|(1 << WGM13); // select Fast PWM mode select TOP_value freely ICR1                     
//     // TCCR1A |= (1 << COM1B1); // None-inverted mode
//     TCCR1A |= (1 << COM1A1);    // None-inverted mode Pin 9
//     TCCR1A |= (1 << COM1B1) | (1 << COM1B0);  // inverted mode Pin 10

//     ICR1 = TOP1 - 1;                // Frequency = 16M / TOP
//     TCCR1B |= (1 << CS10);          // No Prescaling = F_Clock or F_clock/1=16mhz
    
//     TIMSK1 |= (1 << TOIE1);         // Timer1 Overflow Interrupt Enable
//     sei();
// }

// void loop() {
// }



// ------------------------------------------------------------------------------
// #include <Arduino.h>
// #include <avr/interrupt.h>

// int potVal = 0; // pot value for analog read
// int finalVal = 0; // motor revised 0-12 Value
// #define trimPot A0 // motor control 
// int i=0;

// int sensorValue = 0;  // variable to store the value coming from the sensor
// int sensorPin = A0;  
//     int counter=0;
//     int counter2=0;
//     int setting=1;
//     int setting2=1;
//     int directionx=0;
// int buttonState1 = 0;  
// int buttonState2 = 0;  
// int buttonPin1 = 14; // On/Off LHS
// int buttonPin2 = 15; //Pin 15 = RHS Speed Button

// //Unsigned Long
// const uint16_t Datadeg0[] = {128, 128,  129,  130,  130,  131,  132,  132,  133,  134,  134,  135,  136,  137,  137,  138,  139,  139,  140,  141,  141,  142,  143,  143,  144,  145,
//                              145,  146,  147,  148,  148,  149,  150,  150,  151,  152,  152,  153,  154,  154,  155,  156,  156,  157,  158,  158,  159,  160,  160,  161,  162,  162,  163,  164,  164,  165,  166,
//                              166,  167,  168,  168,  169,  169,  170,  171,  171,  172,  173,  173,  174,  175,  175,  176,  176,  177,  178,  178,  179,  180,  180,  181,  181,  182,  183,  183,  184,  184,  185,
//                              186,  186,  187,  187,  188,  189,  189,  190,  190,  191,  192,  192,  193,  193,  194,  194,  195,  196,  196,  197,  197,  198,  198,  199,  199,  200,  200,  201,  201,  202,  203,
//                              203,  204,  204,  205,  205,  206,  206,  207,  207,  208,  208,  209,  209,  210,  210,  211,  211,  212,  212,  212,  213,  213,  214,  214,  215,  215,  216,  216,  217,  217,  217,
//                              218,  218,  219,  219,  220,  220,  220,  221,  221,  222,  222,  222,  223,  223,  223,  224,  224,  225,  225,  225,  226,  226,  226,  227,  227,  227,  228,  228,  228,  229,  229,
//                              229,  230,  230,  230,  231,  231,  231,  232,  232,  232,  232,  233,  233,  233,  234,  234,  234,  234,  235,  235,  235,  235,  236,  236,  236,  236,  236,  237,  237,  237,  237,
//                              237,  238,  238,  238,  238,  238,  239,  239,  239,  239,  239,  239,  240,  240,  240,  240,  240,  240,  240,  240,  241,  241,  241,  241,  241,  241,  241,  241,  241,  241,  242,
//                              242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
//                              242,  242,  242,  242,  242,  241,  241,  241,  241,  241,  241,  241,  241,  241,  241,  240,  240,  240,  240,  240,  240,  240,  240,  239,  239,  239,  239,  239,  239,  238,  238,
//                              238,  238,  238,  237,  237,  237,  237,  237,  236,  236,  236,  236,  236,  235,  235,  235,  235,  234,  234,  234,  234,  233,  233,  233,  232,  232,  232,  232,  231,  231,  231,
//                              230,  230,  230,  229,  229,  229,  228,  228,  228,  227,  227,  227,  226,  226,  226,  225,  225,  225,  224,  224,  223,  223,  223,  222,  222,  222,  221,  221,  220,  220,  220,
//                              219,  219,  218,  218,  217,  217,  217,  216,  216,  215,  215,  214,  214,  213,  213,  212,  212,  212,  211,  211,  210,  210,  209,  209,  208,  208,  207,  207,  206,  206,  205,
//                              205,  204,  204,  203,  203,  202,  201,  201,  200,  200,  199,  199,  198,  198,  197,  197,  196,  196,  195,  194,  194,  193,  193,  192,  192,  191,  190,  190,  189,  189,  188,
//                              187,  187,  186,  186,  185,  184,  184,  183,  183,  182,  181,  181,  180,  180,  179,  178,  178,  177,  176,  176,  175,  175,  174,  173,  173,  172,  171,  171,  170,  169,  169,
//                              168,  168,  167,  166,  166,  165,  164,  164,  163,  162,  162,  161,  160,  160,  159,  158,  158,  157,  156,  156,  155,  154,  154,  153,  152,  152,  151,  150,  150,  149,  148,
//                              148,  147,  146,  145,  145,  144,  143,  143,  142,  141,  141,  140,  139,  139,  138,  137,  137,  136,  135,  134,  134,  133,  132,  132,  131,  130,  130,  129,  128,  128,  127,
//                              126,  125,  125,  124,  123,  123,  122,  121,  121,  120,  119,  118,  118,  117,  116,  116,  115,  114,  114,  113,  112,  112,  111,  110,  110,  109,  108,  107,  107,  106,  105,
//                              105,  104,  103,  103,  102,  101,  101,  100,  99, 99, 98, 97, 97, 96, 95, 95, 94, 93, 93, 92, 91, 91, 90, 89, 89, 88, 87, 87, 86, 86, 85, 84, 84, 83, 82, 82, 81, 80, 80, 79, 79, 78, 77,
//                              77, 76, 75, 75, 74, 74, 73, 72, 72, 71, 71, 70, 69, 69, 68, 68, 67, 66, 66, 65, 65, 64, 63, 63, 62, 62, 61, 61, 60, 59, 59, 58, 58, 57, 57, 56, 56, 55, 55, 54, 54, 53, 52, 52, 51, 51, 50,
//                              50, 49, 49, 48, 48, 47, 47, 46, 46, 45, 45, 44, 44, 43, 43, 43, 42, 42, 41, 41, 40, 40, 39, 39, 38, 38, 38, 37, 37, 36, 36, 35, 35, 35, 34, 34, 33, 33, 33, 32, 32, 32, 31, 31, 30, 30, 30,
//                              29, 29, 29, 28, 28, 28, 27, 27, 27, 26, 26, 26, 25, 25, 25, 24, 24, 24, 23, 23, 23, 23, 22, 22, 22, 21, 21, 21, 21, 20, 20, 20, 20, 19, 19, 19, 19, 19, 18, 18, 18, 18, 18, 17, 17, 17, 17,
//                              17, 16, 16, 16, 16, 16, 16, 15, 15, 15, 15, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
//                              13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 18, 18, 18,
//                              18, 18, 19, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 32, 32,
//                              32, 33, 33, 33, 34, 34, 35, 35, 35, 36, 36, 37, 37, 38, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 48, 48, 49, 49, 50, 50, 51, 51, 52, 52, 53, 54,
//                              54, 55, 55, 56, 56, 57, 57, 58, 58, 59, 59, 60, 61, 61, 62, 62, 63, 63, 64, 65, 65, 66, 66, 67, 68, 68, 69, 69, 70, 71, 71, 72, 72, 73, 74, 74, 75, 75, 76, 77, 77, 78, 79, 79, 80, 80, 81,
//                              82, 82, 83, 84, 84, 85, 86, 86, 87, 87, 88, 89, 89, 90, 91, 91, 92, 93, 93, 94, 95, 95, 96, 97, 97, 98, 99, 99, 100,  101,  101,  102,  103,  103,  104,  105,  105,  106,  107,  107,  108,
//                              109,  110,  110,  111,  112,  112,  113,  114,  114,  115,  116,  116,  117,  118,  118,  119,  120,  121,  121,  122,  123,  123,  124,  125,  125,  126,  127,  128
//                             };

// const uint16_t Datadeg120[] = {227,  226,  226,  226,  225,  225,  225,  224,  224,  223,  223,  223,  222,  222,  222,  221,  221,  220,  220,  220,  219,  219,  218,  218,  217,  217,
//                                217,  216,  216,  215,  215,  214,  214,  213,  213,  212,  212,  212,  211,  211,  210,  210,  209,  209,  208,  208,  207,  207,  206,  206,  205,  205,  204,  204,  203,  203,  202,
//                                201,  201,  200,  200,  199,  199,  198,  198,  197,  197,  196,  196,  195,  194,  194,  193,  193,  192,  192,  191,  190,  190,  189,  189,  188,  187,  187,  186,  186,  185,  184,
//                                184,  183,  183,  182,  181,  181,  180,  180,  179,  178,  178,  177,  176,  176,  175,  175,  174,  173,  173,  172,  171,  171,  170,  169,  169,  168,  168,  167,  166,  166,  165,
//                                164,  164,  163,  162,  162,  161,  160,  160,  159,  158,  158,  157,  156,  156,  155,  154,  154,  153,  152,  152,  151,  150,  150,  149,  148,  148,  147,  146,  145,  145,  144,
//                                143,  143,  142,  141,  141,  140,  139,  139,  138,  137,  137,  136,  135,  134,  134,  133,  132,  132,  131,  130,  130,  129,  128,  128,  127,  126,  125,  125,  124,  123,  123,
//                                122,  121,  121,  120,  119,  118,  118,  117,  116,  116,  115,  114,  114,  113,  112,  112,  111,  110,  110,  109,  108,  107,  107,  106,  105,  105,  104,  103,  103,  102,  101,
//                                101,  100,  99, 99, 98, 97, 97, 96, 95, 95, 94, 93, 93, 92, 91, 91, 90, 89, 89, 88, 87, 87, 86, 86, 85, 84, 84, 83, 82, 82, 81, 80, 80, 79, 79, 78, 77, 77, 76, 75, 75, 74, 74, 73, 72, 72,
//                                71, 71, 70, 69, 69, 68, 68, 67, 66, 66, 65, 65, 64, 63, 63, 62, 62, 61, 61, 60, 59, 59, 58, 58, 57, 57, 56, 56, 55, 55, 54, 54, 53, 52, 52, 51, 51, 50, 50, 49, 49, 48, 48, 47, 47, 46, 46,
//                                45, 45, 44, 44, 43, 43, 43, 42, 42, 41, 41, 40, 40, 39, 39, 38, 38, 38, 37, 37, 36, 36, 35, 35, 35, 34, 34, 33, 33, 33, 32, 32, 32, 31, 31, 30, 30, 30, 29, 29, 29, 28, 28, 28, 27, 27, 27,
//                                26, 26, 26, 25, 25, 25, 24, 24, 24, 23, 23, 23, 23, 22, 22, 22, 21, 21, 21, 21, 20, 20, 20, 20, 19, 19, 19, 19, 19, 18, 18, 18, 18, 18, 17, 17, 17, 17, 17, 16, 16, 16, 16, 16, 16, 15, 15,
//                                15, 15, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
//                                13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 20, 20,
//                                20, 20, 21, 21, 21, 21, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 32, 32, 32, 33, 33, 33, 34, 34, 35, 35, 35,
//                                36, 36, 37, 37, 38, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 48, 48, 49, 49, 50, 50, 51, 51, 52, 52, 53, 54, 54, 55, 55, 56, 56, 57, 57, 58, 58,
//                                59, 59, 60, 61, 61, 62, 62, 63, 63, 64, 65, 65, 66, 66, 67, 68, 68, 69, 69, 70, 71, 71, 72, 72, 73, 74, 74, 75, 75, 76, 77, 77, 78, 79, 79, 80, 80, 81, 82, 82, 83, 84, 84, 85, 86, 86, 87,
//                                87, 88, 89, 89, 90, 91, 91, 92, 93, 93, 94, 95, 95, 96, 97, 97, 98, 99, 99, 100,  101,  101,  102,  103,  103,  104,  105,  105,  106,  107,  107,  108,  109,  110,  110,  111,  112,
//                                112, 113,  114,  114,  115,  116,  116,  117,  118,  118,  119,  120,  121,  121,  122,  123,  123,  124,  125,  125,  126,  127,  128,  128,  128,  129,  130,  130,  131,  132,  132,
//                                133,  134,  134,  135,  136,  137,  137,  138,  139,  139,  140,  141,  141,  142,  143,  143,  144,  145,  145,  146,  147,  148,  148,  149,  150,  150,  151,  152,  152,  153,  154,
//                                154,  155,  156,  156,  157,  158,  158,  159,  160,  160,  161,  162,  162,  163,  164,  164,  165,  166,  166,  167,  168,  168,  169,  169,  170,  171,  171,  172,  173,  173,  174,
//                                175,  175,  176,  176,  177,  178,  178,  179,  180,  180,  181,  181,  182,  183,  183,  184,  184,  185,  186,  186,  187,  187,  188,  189,  189,  190,  190,  191,  192,  192,  193,
//                                193,  194,  194,  195,  196,  196,  197,  197,  198,  198,  199,  199,  200,  200,  201,  201,  202,  203,  203,  204,  204,  205,  205,  206,  206,  207,  207,  208,  208,  209,  209,
//                                210,  210,  211,  211,  212,  212,  212,  213,  213,  214,  214,  215,  215,  216,  216,  217,  217,  217,  218,  218,  219,  219,  220,  220,  220,  221,  221,  222,  222,  222,  223,
//                                223,  223,  224,  224,  225,  225,  225,  226,  226,  226,  227,  227,  227,  228,  228,  228,  229,  229,  229,  230,  230,  230,  231,  231,  231,  232,  232,  232,  232,  233,  233,
//                                233,  234,  234,  234,  234,  235,  235,  235,  235,  236,  236,  236,  236,  236,  237,  237,  237,  237,  237,  238,  238,  238,  238,  238,  239,  239,  239,  239,  239,  239,  240,
//                                240,  240,  240,  240,  240,  240,  240,  241,  241,  241,  241,  241,  241,  241,  241,  241,  241,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
//                                242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  241,  241,  241,  241,  241,  241,  241,  241,
//                                241,  241,  240,  240,  240,  240,  240,  240,  240,  240,  239,  239,  239,  239,  239,  239,  238,  238,  238,  238,  238,  237,  237,  237,  237,  237,  236,  236,  236,  236,  236,
//                                235,  235,  235,  235,  234,  234,  234,  234,  233,  233,  233,  232,  232,  232,  232,  231,  231,  231,  230,  230,  230,  229,  229,  229,  228,  228,  228,  227,  227
//                               };

// const uint16_t Datadeg240[] = {28,  28, 27, 27, 27, 26, 26, 26, 25, 25, 25, 24, 24, 24, 23, 23, 23, 23, 22, 22, 22, 21, 21, 21, 21, 20, 20, 20, 20, 19, 19, 19, 19, 19, 18, 18, 18, 18,
//                                18, 17, 17, 17, 17, 17, 16, 16, 16, 16, 16, 16, 15, 15, 15, 15, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
//                                13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 17,
//                                17, 17, 17, 17, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29,
//                                29, 30, 30, 30, 31, 31, 32, 32, 32, 33, 33, 33, 34, 34, 35, 35, 35, 36, 36, 37, 37, 38, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 48, 48, 49,
//                                49, 50, 50, 51, 51, 52, 52, 53, 54, 54, 55, 55, 56, 56, 57, 57, 58, 58, 59, 59, 60, 61, 61, 62, 62, 63, 63, 64, 65, 65, 66, 66, 67, 68, 68, 69, 69, 70, 71, 71, 72, 72, 73, 74, 74, 75,
//                                75, 76, 77, 77, 78, 79, 79, 80, 80, 81, 82, 82, 83, 84, 84, 85, 86, 86, 87, 87, 88, 89, 89, 90, 91, 91, 92, 93, 93, 94, 95, 95, 96, 97, 97, 98, 99, 99, 100,  101,  101,  102,  103,  103,
//                                104,  105,  105,  106,  107,  107,  108,  109,  110,  110,  111,  112,  112,  113,  114,  114,  115,  116,  116,  117,  118,  118,  119,  120,  121,  121,  122,  123,  123,  124,  125,
//                                125,  126,  127,  128,  128,  128,  129,  130,  130,  131,  132,  132,  133,  134,  134,  135,  136,  137,  137,  138,  139,  139,  140,  141,  141,  142,  143,  143,  144,  145,  145,
//                                146,  147,  148,  148,  149,  150,  150,  151,  152,  152,  153,  154,  154,  155,  156,  156,  157,  158,  158,  159,  160,  160,  161,  162,  162,  163,  164,  164,  165,  166,  166,
//                                167,  168,  168,  169,  169,  170,  171,  171,  172,  173,  173,  174,  175,  175,  176,  176,  177,  178,  178,  179,  180,  180,  181,  181,  182,  183,  183,  184,  184,  185,  186,
//                                186,  187,  187,  188,  189,  189,  190,  190,  191,  192,  192,  193,  193,  194,  194,  195,  196,  196,  197,  197,  198,  198,  199,  199,  200,  200,  201,  201,  202,  203,  203,
//                                204,  204,  205,  205,  206,  206,  207,  207,  208,  208,  209,  209,  210,  210,  211,  211,  212,  212,  212,  213,  213,  214,  214,  215,  215,  216,  216,  217,  217,  217,  218,
//                                218,  219,  219,  220,  220,  220,  221,  221,  222,  222,  222,  223,  223,  223,  224,  224,  225,  225,  225,  226,  226,  226,  227,  227,  227,  228,  228,  228,  229,  229,  229,
//                                230,  230,  230,  231,  231,  231,  232,  232,  232,  232,  233,  233,  233,  234,  234,  234,  234,  235,  235,  235,  235,  236,  236,  236,  236,  236,  237,  237,  237,  237,  237,
//                                238,  238,  238,  238,  238,  239,  239,  239,  239,  239,  239,  240,  240,  240,  240,  240,  240,  240,  240,  241,  241,  241,  241,  241,  241,  241,  241,  241,  241,  242,  242,
//                                242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
//                                242,  242,  242,  242,  241,  241,  241,  241,  241,  241,  241,  241,  241,  241,  240,  240,  240,  240,  240,  240,  240,  240,  239,  239,  239,  239,  239,  239,  238,  238,  238,
//                                238,  238,  237,  237,  237,  237,  237,  236,  236,  236,  236,  236,  235,  235,  235,  235,  234,  234,  234,  234,  233,  233,  233,  232,  232,  232,  232,  231,  231,  231,  230,
//                                230,  230,  229,  229,  229,  228,  228,  228,  227,  227,  227,  226,  226,  226,  225,  225,  225,  224,  224,  223,  223,  223,  222,  222,  222,  221,  221,  220,  220,  220,  219,
//                                219,  218,  218,  217,  217,  217,  216,  216,  215,  215,  214,  214,  213,  213,  212,  212,  212,  211,  211,  210,  210,  209,  209,  208,  208,  207,  207,  206,  206,  205,  205,
//                                204,  204,  203,  203,  202,  201,  201,  200,  200,  199,  199,  198,  198,  197,  197,  196,  196,  195,  194,  194,  193,  193,  192,  192,  191,  190,  190,  189,  189,  188,  187,
//                                187,  186,  186,  185,  184,  184,  183,  183,  182,  181,  181,  180,  180,  179,  178,  178,  177,  176,  176,  175,  175,  174,  173,  173,  172,  171,  171,  170,  169,  169,  168,
//                                168,  167,  166,  166,  165,  164,  164,  163,  162,  162,  161,  160,  160,  159,  158,  158,  157,  156,  156,  155,  154,  154,  153,  152,  152,  151,  150,  150,  149,  148,  148,
//                                147,  146,  145,  145,  144,  143,  143,  142,  141,  141,  140,  139,  139,  138,  137,  137,  136,  135,  134,  134,  133,  132,  132,  131,  130,  130,  129,  128,  128,  127,  126,
//                                125,  125,  124,  123,  123,  122,  121,  121,  120,  119,  118,  118,  117,  116,  116,  115,  114,  114,  113,  112,  112,  111,  110,  110,  109,  108,  107,  107,  106,  105,  105,
//                                104,  103,  103,  102,  101,  101,  100,  99, 99, 98, 97, 97, 96, 95, 95, 94, 93, 93, 92, 91, 91, 90, 89, 89, 88, 87, 87, 86, 86, 85, 84, 84, 83, 82, 82, 81, 80, 80, 79, 79, 78, 77, 77,
//                                76, 75, 75, 74, 74, 73, 72, 72, 71, 71, 70, 69, 69, 68, 68, 67, 66, 66, 65, 65, 64, 63, 63, 62, 62, 61, 61, 60, 59, 59, 58, 58, 57, 57, 56, 56, 55, 55, 54, 54, 53, 52, 52, 51, 51, 50,
//                                50, 49, 49, 48, 48, 47, 47, 46, 46, 45, 45, 44, 44, 43, 43, 43, 42, 42, 41, 41, 40, 40, 39, 39, 38, 38, 38, 37, 37, 36, 36, 35, 35, 35, 34, 34, 33, 33, 33, 32, 32, 32, 31, 31, 30, 30,
//                                30, 29, 29, 29, 28
//                               };
// //-------------------------------------------------------------------------------------------------------                              
// const uint16_t DatadegStop[] = {00,  00,  00,  00,  00,  00,  00};
// void degStopVal(int Low)
// {  
//   OCR1A = Low; 
//   OCR1B = 255;  //255 = Low side drivers OFF
//   OCR3A = Low;
//   OCR3B = 255;  //255 = Low side drivers OFF
//   OCR4A = Low;
//   OCR4B = 255;  //255 = Low side drivers OFF
// }
// //-----------------------------------------------------------------------------------------------------

// void deg0Val(int High)
// {
//   OCR1A = High; // Addition of dead time of 0.46 equating to 0.2% as the range is between 12.75 and 242.45 (5- 95%)
//   OCR1B = (High + 2);
// }

// void deg120Val(int High)
// {
//   OCR3A = High;
//   OCR3B = (High + 2);
// }

// void deg240Val(int High)
// {
//   OCR4A = High;
//   OCR4B = (High + 2);
// }

// void potUpdate() {
// sensorValue = (float)(analogRead(sensorPin) / 170.5);
// }
// //------------------------------------------------------------------------------------
// #include <Wire.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels

// // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

// //-------------------------------------------------------------------------------
// void setup()
// {
//   TCCR4A = 0;
//   TCCR4B = 0;
//   TCCR4C = 0;
//   TCNT4  = 0;

//   TCCR3A = 0;
//   TCCR3B = 0;
//   TCCR3C = 0;
//   TCNT3  = 0;

//   TCCR1A = 0;
//   TCCR1B = 0;
//   TCNT1  = 0;

//   ICR4   = 255;      // sets PWM period frequency to 31.25Hz
//   ICR3   = 255;
//   ICR1   = 255;


//   TCCR4A = _BV(WGM41) | _BV(COM4B0) | _BV(COM4B1) | _BV(COM4A1);
//   TCCR4B = _BV(WGM43) | _BV(CS40);
//   TCCR3A = _BV(WGM31) | _BV(COM3B0) | _BV(COM3B1) | _BV(COM3A1);
//   TCCR3B = _BV(WGM33) | _BV(CS30);
//   TCCR1A = _BV(WGM11) | _BV(COM1B0) | _BV(COM1B1) | _BV(COM1A1);
//   TCCR1B = _BV(WGM13) | _BV(CS10);

// //   Serial.begin(115200); //115200

//   // Set the PWM pin as output.  
//   pinMode( 7, OUTPUT); //OCR4B low side U
//   pinMode( 6, OUTPUT); //OCR4A high side U
//   pinMode( 5, OUTPUT); //OCR3A high side V
  
//   pinMode( 2, OUTPUT); //OCR3B low side V
//   pinMode( 11, OUTPUT); //OCR1A high side W
//   pinMode( 12, OUTPUT); //OCR1B low side W
// //------------------------------------------------------------------------------  
// { 
//   degStopVal(DatadegStop[0]);   // Stop all outputs    
// }  
// //-----------------------------------------------------------------------------
//    pinMode(buttonPin1, INPUT_PULLUP);   
//    pinMode(buttonPin2, INPUT_PULLUP);  
// }
// //---------------------------------OLED DISPLAY---------------------------------------  
  
 
// //================================= MAIN CONTROL LOOP ===================================
// void loop()
// {  

// //    potVal = analogRead(trimPot)/10; // reduce pot sensitivity 
//     for (int H = 0; H < 1040; H++)
//         {
//           deg0Val(Datadeg0[H]);
//           deg120Val(Datadeg120[H]);
//           deg240Val(Datadeg240[H]);
//           delayMicroseconds(18);          
//         }
// } 


//------------------------------------------------------------------------------------

int va[201] = {128, 132, 136, 139, 143, 147, 151, 155, 159, 163, 167, 171, 174, 178, 182, 185, 189, 192, 196, 199, 202, 206, 209, 212, 215, 218, 220, 223, 226, 228, 231, 233, 235, 237, 239, 241, 243, 245, 246, 247, 249, 250, 251, 252, 253, 253, 254, 254, 255, 255, 255, 255, 255, 254, 254, 253, 253, 252, 251, 250, 249, 247, 246, 245, 243, 241, 239, 237, 235, 233, 231, 228, 226, 223, 220, 218, 215, 212, 209, 206, 202, 199, 196, 192, 189, 185, 182, 178, 174, 171, 167, 163, 159, 155, 151, 147, 143, 139, 136, 132, 128, 123, 119, 116, 112, 108, 104, 100, 96, 92, 88, 84, 81, 77, 73, 70, 66, 63, 59, 56, 53, 49, 46, 43, 40, 37, 35, 32, 29, 27, 24, 22, 20, 18, 16, 14, 12, 10, 9, 8, 6, 5, 4, 3, 2, 2, 1, 1, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 4, 5, 6, 8, 9, 10, 12, 14, 16, 18, 20, 22, 24, 27, 29, 32, 35, 37, 40, 43, 46, 49, 53, 56, 59, 63, 66, 70, 73, 77, 81, 84, 88, 92, 96, 100, 104, 108, 112, 116, 119, 123};
int vb[201] = {238, 236, 234, 231, 229, 227, 224, 221, 219, 216, 213, 210, 207, 204, 200, 197, 194, 190, 187, 183, 179, 176, 172, 168, 164, 160, 157, 153, 149, 145, 141, 137, 133, 129, 125, 121, 117, 113, 109, 105, 101, 97, 93, 89, 86, 82, 78, 74, 71, 67, 64, 60, 57, 54, 50, 47, 44, 41, 38, 35, 33, 30, 28, 25, 23, 21, 18, 16, 15, 13, 11, 9, 8, 7, 5, 4, 3, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 13, 15, 17, 19, 21, 24, 26, 28, 31, 34, 36, 39, 42, 45, 48, 51, 55, 58, 61, 65, 68, 72, 76, 79, 83, 87, 91, 95, 98, 102, 106, 110, 114, 118, 122, 126, 130, 134, 138, 142, 146, 150, 154, 158, 162, 166, 169, 173, 177, 181, 184, 188, 191, 195, 198, 201, 205, 208, 211, 214, 217, 220, 222, 225, 227, 230, 232, 234, 237, 239, 240, 242, 244, 246, 247, 248, 250, 251, 252, 252, 253, 254, 254, 255, 255, 255, 255, 255, 255, 254, 254, 253, 252, 251, 250, 249, 248, 247, 245, 243, 242, 240};
int vc[201] = {17, 15, 13, 12, 10, 8, 7, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 7, 8, 9, 11, 13, 15, 16, 18, 21, 23, 25, 28, 30, 33, 35, 38, 41, 44, 47, 50, 54, 57, 60, 64, 67, 71, 74, 78, 82, 86, 89, 93, 97, 101, 105, 109, 113, 117, 121, 125, 129, 133, 137, 141, 145, 149, 153, 157, 160, 164, 168, 172, 176, 179, 183, 187, 190, 194, 197, 200, 204, 207, 210, 213, 216, 219, 221, 224, 227, 229, 231, 234, 236, 238, 240, 242, 243, 245, 247, 248, 249, 250, 251, 252, 253, 254, 254, 255, 255, 255, 255, 255, 255, 254, 254, 253, 252, 252, 251, 250, 248, 247, 246, 244, 242, 240, 239, 237, 234, 232, 230, 227, 225, 222, 220, 217, 214, 211, 208, 205, 201, 198, 195, 191, 188, 184, 181, 177, 173, 169, 166, 162, 158, 154, 150, 146, 142, 138, 134, 130, 126, 122, 118, 114, 110, 106, 102, 98, 95, 91, 87, 83, 79, 76, 72, 68, 65, 61, 58, 55, 51, 48, 45, 42, 39, 36, 34, 31, 28, 26, 24, 21, 19};

ISR (TIMER1_OVF_vect){        //TIMER1_OVF_vect
    TCNT0 = 0;
    TCNT2 = 0;

    // m = analogA0 * PU * 5.0 * K1 * SQRT3 * ONE_by_VDC;
    // m = m > 0.95 ? 0.95 : m;
    // m = m < 0.05 ? 0.05 : m;
    // m = 0.7;

    OCR0A = va[i];           // PWM Pin 6
    OCR0B = vb[i];           // PWM Pin 5
    OCR2A = vc[i];           // PWM Pin 11
    
    i++;
    if (i >= 200){
        i = 0;
        digitalWrite(2, TEST);
        TEST = ~TEST;
    } 
    // // Serial.println(data1);
    // // Serial.println(data2);
    // // Serial.println(data3);

    // t += 0.0005;             // 1/62500
    // if (t >= 0.0194){     // 1/Fsin - 1/62500 - 1/62500/4
    //     t = 0.0;
    // }  
}

void setup() {
    // Serial.begin(115200);
    pinMode(2, OUTPUT);
    // pinMode(A0, INPUT);

    cli();//stop interrupts

    // PWM by timer 0 ---------------------------------------------------
    TCNT0 = 0;
    TCCR0A = 0; TCCR0B = 0; // Reset 2 registers
    DDRD |= (1 << PD5);     // PD5 is OUTPUT (pin 5)
    DDRD |= (1 << PD6);     // PB1 is OUTPUT (pin 6 )   
    
    // TCCR0A |= (1 << WGM01) | (1 << WGM00);   // Fast PWM
    TCCR0A |= (1 << WGM00);   // PWM Phase Corrected - Top = 0xFF
    TCCR0A |= (1 << COM0B1);  // Fast mode Pin 5
    TCCR0A |= (1 << COM0A1);  // Fast mode Pin 6
    TCCR0A |= (1 << COM0A1);  // None-inverted mode Pin 6
    TCCR0A |= (1 << COM0B1);  // None-inverted mode Pin 5
    // TCCR0A |= (1 << COM0B1) | (1 << COM0B0);  // inverted mode Pin 5

    TCCR0B |= (1 << CS10);   // No Prescaling = F_Clock or F_clock/1=16mhz
    // TCCR0B = TCCR0B & B11111000 | B00000001; // for PWM frequency of 62500.00 Hz
    
    
    // PWM by timer 2 and Interrupt ---------------------------------------------------
    TCNT2 = 0;
    TCCR2A = 0; TCCR2B = 0;
    DDRD |= (1 << PD3);   // output Pin 3
    DDRB |= (1 << PB3);   // output Pin 11
    TCCR2A |= (1 << COM2A1);    // None-inverted Pin 11
    TCCR2A |= (1 << COM2B1) | (1 << COM2B0);    // inverted Pin 3
    // TCCR2A |= (1 << WGM21) | (1 << WGM20);      // Fast PWM
    TCCR2A |= (1 << WGM20);      // PWM Phase Corrected - Top = 0xFF
    TCCR2B |= (0 << CS22) | (0 << CS21) | (1 << CS20);  // Prescaler
    // OCR2A = TOP2 - 1;              // Frequence = (16000000/((TOP2 + 1) * Prescaler))
    
    //TIMSK2 |= (1 << OCIE2A);  // Output Compare Match A Interrupt Enable
                                // TIMER2_COMPA_vect
            
    // TIMSK2 |= (1 << TOIE2); // Timer2 Overflow Interrupt Enable
    // sei();                  // Enable global interrupts   


    // PWM by timer 1 & Interrupt-------------------------------------------------
    TCNT1 = 0;
    TCCR1A = 0; TCCR1B = 0; // Reset 2 registers
    DDRB |= (1 << PB2);     // PB2 is OUTPUT (pin 10)
    DDRB |= (1 << PB1);     // PB1 is OUTPUT (pin 9 )   
    
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12)|(1 << WGM13); // select Fast PWM mode select TOP_value freely ICR1                     
    TCCR1A |= (1 << COM1B1); // None-inverted mode
    TCCR1A |= (1 << COM1A1);    // None-inverted mode Pin 9
    // TCCR1A |= (1 << COM1B1) | (1 << COM1B0);  // inverted mode Pin 10
    
    ICR1 = 1599;                // Frequency = 16M / ICR1
    TCCR1B |= (1 << CS10);              // No Prescaling = F_Clock or F_clock/1=16mhz
    
    TIMSK1 |= (1 << TOIE1);         // Timer1 Overflow Interrupt Enable
    sei();
}

void loop() {
    // analogA0 = analogRead(A0);
}