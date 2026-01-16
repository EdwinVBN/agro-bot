#ifndef motoraansturing.h
#define motoraansturing.h

void xmotorpositief() // x motor postief draaien via Hbrug
{
        PORTA |= (1 << x_R_EN);
        PORTA |= (1 << x_L_EN);
        PORTH |= (1 << x_RPWM);
        PORTH &= ~(1 << x_LPWM);
}
void xmotoruit() // stopt X motor met draaien via H brug
{
    PORTA &= ~((1 << x_R_EN) | (1 << x_L_EN));
    PORTH &= ~((1 << x_RPWM) | (1 << x_LPWM));
}
void xmotornegatief()// x motor negatief draaien via Hbrug
{
    PORTA |= (1 << x_R_EN);
    PORTA |= (1 << x_L_EN);
    PORTH &= ~(1 << x_RPWM);
    PORTH |= (1 << x_LPWM);
}
void ymotorpositief()// y motor postief draaien via Hbrug
{
        PORTA |= (1 << y_R_EN);
        PORTA |= (1 << y_L_EN);
        PORTE |= (1 << y_RPWM);
        PORTG &= ~(1 << y_LPWM);
}
void ymotoruit() //stopt y motor met draaien via H brug
{
    PORTA &= ~((1 << y_R_EN) | (1 << y_L_EN));
    PORTE &= ~(1 << y_RPWM);
    PORTG &= ~(1 << y_LPWM);
}
void ymotornegatief() // y motor negatief draaien via Hbrug
{
    PORTA |= (1 << y_R_EN);
    PORTA |= (1 << y_L_EN);
    PORTE &= ~(1 << y_RPWM);
    PORTG |= (1 << y_LPWM);
}
void zmotorpositief()// z motor postief draaien via Hbrug
{
        PORTK |= (1 << z_R_EN);   // R_EN = 1
        PORTK |= (1 << z_L_EN);   // L_EN = 1
        PORTE |= (1 << z_RPWM);   // RPWM = 1
        PORTE &= ~(1 << z_LPWM);  // LPWM = 0
}
void zmotoruit()//stopt z motor met draaien via H brug
{
    PORTK &= ~((1 << z_R_EN) | (1 << z_L_EN));
    PORTE &= ~((1 << z_RPWM) | (1 << z_LPWM));
}
void zmotornegatief() // z motor negatief draaien via Hbrug

{
    PORTK |= (1 << z_R_EN);
    PORTK |= (1 << z_L_EN);
    PORTE &= ~(1 << z_RPWM);
    PORTE |= (1 << z_LPWM);
}

#endif

