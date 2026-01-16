#ifndef motorconfic.h
#define motorconfic.h

//define x motor h brug ports
#define x_R_EN PA4
#define x_L_EN PA5
#define x_RPWM PH3
#define x_LPWM PH4

//define y motor h brug ports
#define y_R_EN PA2
#define y_L_EN PA3
#define y_RPWM PE3
#define y_LPWM PG5

//define z motor h brug ports
#define z_R_EN PK4
#define z_L_EN PK5
#define z_RPWM PE4
#define z_LPWM PE5

void xmotorconfic(void)
{
    //maak EN and PWM ports output
    DDRA |= (1 << x_R_EN);
    DDRA |= (1 << x_L_EN);
    DDRH |= (1 << x_RPWM);
    DDRH |= (1 << x_LPWM);

    //maak alles bij start uit
    PORTA &= ~(1 << x_R_EN);
    PORTA &= ~(1 << x_L_EN);
    PORTH &= ~(1 << x_RPWM);
    PORTH &= ~(1 << x_LPWM);
}
void ymotorconfic(void)
{
    //maak EN and PWM ports output
    DDRA |= (1 << y_R_EN);
    DDRA |= (1 << y_L_EN);
    DDRE |= (1 << y_RPWM);
    DDRG |= (1 << y_LPWM);

    //maak alles bij start uit
    PORTA &= ~(1 << y_R_EN);
    PORTA &= ~(1 << y_L_EN);
    PORTE &= ~(1 << y_RPWM);
    PORTG &= ~(1 << y_LPWM);
}
void zmotorconfic(void)
{
    //maak EN and PWM ports output
    DDRK |= (1 << z_R_EN);
    DDRK |= (1 << z_L_EN);
    DDRE |= (1 << z_RPWM);
    DDRE |= (1 << z_LPWM);

    //maak alles bij start uit
    PORTK &= ~(1 << z_R_EN);
    PORTK &= ~(1 << z_L_EN);
    PORTE &= ~(1 << z_RPWM);
    PORTE &= ~(1 << z_LPWM);
}

#endif

