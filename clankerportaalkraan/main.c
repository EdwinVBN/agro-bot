#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Y motor defines
#define R_EN_Y PA0 //pin 22
#define L_EN_Y PA1 //pin 23
#define R_PWM_Y PE4 // pin 2
#define L_PWM_Y PE5 // pin 3

#define DDR_R_EN_Y DDRA
#define DDR_L_EN_Y DDRA
#define DDR_R_PWM_Y DDRE
#define DDR_L_PWM_Y DDRE

#define PORT_R_EN_Y PORTA
#define PORT_L_EN_Y PORTA
#define PORT_R_PWM_Y PORTE
#define PORT_L_PWM_Y PORTE

// y knoppen defines
#define PIN_Y1 PINB
#define PIN_Y2 PINB
#define PIN_Y3 PINB
#define PIN_Y4 PINB
#define PIN_Y5 PINB

#define KNOP_Y1 PB0 // pin 53
#define KNOP_Y2 PB1 //pin 52
#define KNOP_Y3 PB2 //pin 51
#define KNOP_Y4 PB3 //pin 50
#define KNOP_Y5 PB4 //pin 10

#define PORT_KNOP_Y1 PORTB
#define PORT_KNOP_Y2 PORTB
#define PORT_KNOP_Y3 PORTB
#define PORT_KNOP_Y4 PORTB
#define PORT_KNOP_Y5 PORTB

#define DDR_KNOP_Y1 DDRB
#define DDR_KNOP_Y2 DDRB
#define DDR_KNOP_Y3 DDRB
#define DDR_KNOP_Y4 DDRB
#define DDR_KNOP_Y5 DDRB

// z motor defines
#define R_EN_Z PA2 //pin D24
#define L_EN_Z PA3 //pin D25
#define R_PWM_Z PE3 // pin D5
#define L_PWM_Z PG5 // pin D4

#define DDR_R_EN_Z DDRA
#define DDR_L_EN_Z DDRA
#define DDR_R_PWM_Z DDRE
#define DDR_L_PWM_Z DDRG

#define PORT_R_EN_Z PORTA
#define PORT_L_EN_Z PORTA
#define PORT_R_PWM_Z PORTE
#define PORT_L_PWM_Z PORTG

// z knoppen defines
#define PIN_Z1 PINC
#define PIN_Z0 PINC

#define KNOP_Z1 PC0 // pin 37
#define KNOP_Z0 PC1 //pin 36

#define PORT_KNOP_Z1 PORTC
#define PORT_KNOP_Z0 PORTC

#define DDR_KNOP_Z1 DDRC
#define DDR_KNOP_Z0 DDRC

//magneet defines
#define MAGNEET PK6 //a14

#define PORT_MAGNEET PORTK

#define DDR_MAGNEET DDRK

//delay defines
#define DEBOUNCE_MS 15
#define DEBOUNCE 10

void config(void)// zorgt ervoor dat alles goed geconfigureerd wordt.
{
    zmotorconfig();
    magneetconfig();
    zknoppenconfig();
    yknoppenconfig();
    ymotorconfig();
    timer0config();
    interruptconfig();
}

// globale integeres
volatile uint16_t millisec = 0;
volatile uint16_t last_pcint_time = 0;
volatile int ybereikt = 0;
volatile int knopy;

//interrupts
ISR(TIMER0_COMPA_vect)
{
    millisec++;
}

ISR(PCINT0_vect)
{
    uint16_t now = millisec;

    if ((now - last_pcint_time) < DEBOUNCE_MS)
        return;                     // te snel → bounce

    last_pcint_time = now;


        if (knopy == 1 && (!(PIN_Y1 & (1 << KNOP_Y1)))){ybereikt = 1;}
        else if (knopy == 2 && (!(PIN_Y2 & (1 << KNOP_Y2)))){ybereikt = 1;}
        else if (knopy == 3 && (!(PIN_Y3 & (1 << KNOP_Y3)))){ybereikt = 1;}
        else if (knopy == 4 && (!(PIN_Y4 & (1 << KNOP_Y4)))){ybereikt = 1;}
        else if (knopy == 5 && (!(PIN_Y5 & (1 << KNOP_Y5)))){ybereikt = 1;}

}

void timer0config(void)
{
    TCCR0A = (1 << WGM01);          // CTC mode
    TCCR0B = (1 << CS01) | (1 << CS00); // prescaler 64
    OCR0A = 249;                   // 1 ms @ 16 MHz
    TIMSK0 |= (1 << OCIE0A);        // compare interrupt

}

void interruptconfig(void)
{

    PCMSK0 |= (1 << PCINT4) | (1 << PCINT3) | (1 << PCINT2) | (1 << PCINT1) | (1 << PCINT0);
    PCICR |= (1 << PCIE0);
    PCIFR |= (1 << PCIF0);
    sei();


}

void zknoppenconfig(void)
{
    DDR_KNOP_Z1 &= ~(1 << KNOP_Z1);
    DDR_KNOP_Z0 &= ~(1 << KNOP_Z0);

    PORT_KNOP_Z1 |= (1 << KNOP_Z1);
    PORT_KNOP_Z0 |= (1 << KNOP_Z0);
}




void yknoppenconfig(void)
{
    DDR_KNOP_Y1 &= ~(1 << KNOP_Y1); // knoppen Y as input
    DDR_KNOP_Y2 &= ~(1 << KNOP_Y2);
    DDR_KNOP_Y3 &= ~(1 << KNOP_Y3);
    DDR_KNOP_Y4 &= ~(1 << KNOP_Y4);
    DDR_KNOP_Y5 &= ~(1 << KNOP_Y5);

    PORT_KNOP_Y1 |= (1 << KNOP_Y1); // knoppen Y as pullup
    PORT_KNOP_Y2 |= (1 << KNOP_Y2);
    PORT_KNOP_Y3 |= (1 << KNOP_Y3);
    PORT_KNOP_Y4 |= (1 << KNOP_Y4);
    PORT_KNOP_Y5 |= (1 << KNOP_Y5);
}

void zmotorconfig(void)
{
    /* H-brug PORTS als OUTPUT instellen*/
    DDR_R_EN_Z |= (1 << R_EN_Z);
    DDR_L_EN_Z |= (1 << L_EN_Z);
    DDR_R_PWM_Z |= (1 << R_PWM_Z);
    DDR_L_PWM_Z |= (1 << L_PWM_Z);

    /* Alles uit bij start */
    PORT_R_EN_Z &= ~(1 << R_EN_Z);
    PORT_L_EN_Z &= ~(1 << L_EN_Z);
    PORT_R_PWM_Z &= ~(1 << R_PWM_Z);
    PORT_L_PWM_Z &= ~(1 << L_PWM_Z);
}

void ymotorconfig(void)
{
    /* H-brug PORTS als OUTPUT instellen*/
    DDR_R_EN_Y |= (1 << R_EN_Y);
    DDR_L_EN_Y |= (1 << L_EN_Y);
    DDR_R_PWM_Y |= (1 << R_PWM_Y);
    DDR_L_PWM_Y |= (1 << L_PWM_Y);

    /* Alles uit bij start */
    PORT_R_EN_Y &= ~(1 << R_EN_Y);
    PORT_L_EN_Y &= ~(1 << L_EN_Y);
    PORT_R_PWM_Y &= ~(1 << R_PWM_Y);
    PORT_L_PWM_Y &= ~(1 << L_PWM_Y);
}

void magneetconfig(void)
{
    DDR_MAGNEET |= (1 << MAGNEET);     // magneet als output
    PORT_MAGNEET &= ~(1 << MAGNEET);  // magneet uit bij start
}
void magneetaan(void)
{
    PORT_MAGNEET |= (1 << MAGNEET); // magneet aan
}

void magneetuit(void)
{
    PORT_MAGNEET &= ~(1 << MAGNEET); // magneet uit
}

void ymotorpositief(void)
{
    /* MOTOR AAN (negatief) */
        PORT_R_EN_Y |= (1 << R_EN_Y);   // R_EN = 1
        PORT_L_EN_Y |= (1 << L_EN_Y);   // L_EN = 1
        PORT_R_PWM_Y |= (1 << R_PWM_Y);   // RPWM = 1
        PORT_L_PWM_Y &= ~(1 << L_PWM_Y);  // LPWM = 0
}

void ymotoruit(void)
{
      /* MOTOR UIT */
        PORT_R_EN_Y &= ~(1 << R_EN_Y);
        PORT_L_EN_Y &= ~(1 << L_EN_Y); // enables uit
        PORT_R_PWM_Y &= ~(1 << R_PWM_Y);
        PORT_L_PWM_Y &= ~(1 << L_PWM_Y); // richtingen uit
}

void ymotornegatief(void)
{
    /*MOTOR AAN (positief)*/
        PORT_R_EN_Y |= (1 << R_EN_Y);   // R_EN = 1
        PORT_L_EN_Y |= (1 << L_EN_Y);   // L_EN = 1
        PORT_R_PWM_Y &= ~(1 << R_PWM_Y);   // RPWM = 1
        PORT_L_PWM_Y |= (1 << L_PWM_Y);  // LPWM = 0

}

void zmotorpositief(void)
{
    /* MOTOR AAN (positief) */
        PORT_R_EN_Z |= (1 << R_EN_Z);   // R_EN = 1
        PORT_L_EN_Z |= (1 << L_EN_Z);   // L_EN = 1
        PORT_R_PWM_Z |= (1 << R_PWM_Z);   // RPWM = 1
        PORT_L_PWM_Z &= ~(1 << L_PWM_Z);  // LPWM = 0
}

void zmotoruit(void)
{
      /* MOTOR UIT */
        PORT_R_EN_Z &= ~(1 << R_EN_Z);
        PORT_L_EN_Z &= ~(1 << L_EN_Z); // enables uit
        PORT_R_PWM_Z &= ~(1 << R_PWM_Z);
        PORT_L_PWM_Z &= ~(1 << L_PWM_Z); // richtingen uit
}

void zmotornegatief(void)
{
    /*MOTOR AAN (negatief)*/
        PORT_R_EN_Z |= (1 << R_EN_Z);   // R_EN = 1
        PORT_L_EN_Z |= (1 << L_EN_Z);   // L_EN = 1
        PORT_R_PWM_Z &= ~(1 << R_PWM_Z);   // RPWM = 1
        PORT_L_PWM_Z |= (1 << L_PWM_Z);  // LPWM = 0

}

void ybeweging(int locatie)
{

    static int vorigestaatknopy = 0;

    knopy = locatie;
    ybereikt = 0;

    if (knopy > vorigestaatknopy)
    {
        ymotorpositief();
        while (ybereikt == 0){}
    }
    else if (knopy < vorigestaatknopy)
    {
        ymotornegatief();
        while (ybereikt == 0){}
    }
    ymotoruit();
    vorigestaatknopy = knopy;

}

void bewegingoppak(void)
{
    uint8_t z1_gebruikt = 0;
    uint8_t z0_gebruikt = 0;

    // Stap 1: Z-as omlaag
    zmotorpositief();

    while (1)
    {
        if (!z1_gebruikt && !(PIN_Z1 & (1 << KNOP_Z1)))
        {
            _delay_ms(DEBOUNCE);
            if (!(PIN_Z1 & (1 << KNOP_Z1)))
            {
                zmotoruit();
                magneetaan();
                z1_gebruikt = 1;   //knop genegeerd vanaf nu
                break;
            }
        }
    }

    // Stap 2: Z-as omhoog
    zmotornegatief();

    while (1)
    {
        if (!z0_gebruikt && !(PIN_Z0 & (1 << KNOP_Z0)))
        {
            _delay_ms(DEBOUNCE);
            if (!(PIN_Z0 & (1 << KNOP_Z0)))
            {
                zmotoruit();
                z0_gebruikt = 1;   //knop genegeerd vanaf nu
                break;
            }
        }
    }
}

void bewegingneerzet(void)
{
    uint8_t z1_gebruikt = 0;
    uint8_t z0_gebruikt = 0;

    //Stap 1: Z-as omlaag
    zmotorpositief();

    while (1)
    {
        if (!z1_gebruikt && !(PIN_Z1 & (1 << KNOP_Z1)))
        {
            _delay_ms(DEBOUNCE);
            if (!(PIN_Z1 & (1 << KNOP_Z1)))
            {
                zmotoruit();
                magneetuit();
                z1_gebruikt = 1;   //knop genegeerd vanaf nu
                break;
            }
        }
    }

    // Stap 2: Z-as omhoog
    zmotornegatief();

    while (1)
    {
        if (!z0_gebruikt && !(PIN_Z0 & (1 << KNOP_Z0)))
        {
            _delay_ms(DEBOUNCE);
            if (!(PIN_Z0 & (1 << KNOP_Z0)))
            {
                zmotoruit();
                z0_gebruikt = 1; //knop genegeerd vannaf nu
                break;
            }
        }
    }
}

int main(void)
{
    config();
    ybeweging(2);
    bewegingoppak();
    ybeweging(4);
    bewegingneerzet();
    while(1){};
    return 0;

}
