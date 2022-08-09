// Microcontrollers Laboratory
// Practice 5
// Esteban Lavín Treviño

// Libraries and Headers
#include "Config_header.h" // Include the config header file
#include <math.h>          // Include math library

// Directives
#define _XTAL_FREQ 10000000 // frequency
#define DELAY_SWEEP 300  // delay for sweep effect 300 ms
#define DELAY_TARGET 500 // delay for target 500 ms
#define DELAY_PRESS 250  // delay for switch press 250 ms



// Constants
enum exponent{ bbase = 2, // base 2
               limit = 8 }; // limit 8
               
enum loop { init = 0, // min exponent 0
            max = 7}; //  max exponent 7
 
enum port { digital = 0b000000000, // digital port 
            input = 0b111111111, // input port
            output = 0b000000000 // output port
                    };
        
        
// Global Variables - Function Declarations
Ports_configuration();                              // Ports configuration.
void sweep (void);                                  // Sweep function
void __interrupt (high_priority) high_isr(void);    // High priority Interrupt Service Request.
void __interrupt (low_priority) low_isr(void);      // Low priority Interrupt Service Request.


// Main Functions
void main(void){
    char notPort;                           // create variable to monitor port state
    Ports_configuration();                  //Ports configuration.
            
    while (1) {                             // Infinite cycle
        LATB = pow(bbase, rand()%limit);    // activate random LED
        __delay_ms(DELAY_TARGET);           // 500 ms delay
        notPort = ~LATB;                    // Negar el puerto
        
        if(PORTD == notPort)                // if push button is the same as LED
            sweep();                        // Knight Rider Effect
        else {
            __delay_ms(DELAY_PRESS);        // 250 ms delay
            if(PORTD == notPort)            // check again button and LED
                sweep();                    // Knight Rider Effect
        }
    }
}

// Function Definitions
Ports_configuration(){//            Ports configuration.
    // PORTB 
    ANSELB = digital;    // Digital
    TRISB = output;    // Output
    
    // PORTD
    ANSELD = digital; // Digital
    TRISD = input; // Input
}
void sweep(void){ 
    for(int i = init; i <= max; i++){ // for loop increasing part Knight rider effect
        LATB = pow(bbase,i); // powers output B  equals base (2) to the i (random 0-7)
        __delay_ms(DELAY_SWEEP); // delay sweep effect 300 ms
    }
    
    for(int i = max; i >= init; i--){ // for loop increasing part Knight rider effect
        LATB = pow(bbase,i);  // powers output B  equals base (2) to the i (random 0-7)
        __delay_ms(DELAY_SWEEP); // delay sweep effect 300 ms
    }
}
void __interrupt (high_priority) high_isr(void){//  High priority Interrupt Service Request.
    Nop();
}
void __interrupt (low_priority)  low_isr(void){//   Low priority Interrupt Service Request.
    Nop();
}
