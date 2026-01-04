/*
 */

#include <avr/io.h>

int main(void) // PK7 = Port K met bit 7 en is ervoor de schakelaaar, PK6 = Port K met bit 6 is er voor de Elektromagneet
{
    DDRK &= ~(1 << PK7); // input van de arduino op PK7

    PORTK |= (1 << PK7); // Pull - up weerstand op PK7

    DDRK |= (1 << PK6); // output van de arduino op PK6


    while (1)
    {
        if ((PINK & (1 << PK7)) == 0) // controleerd of de schakelaar ingedrukt is
        {
            PORTK |= (1 << PK6); // zet de schakelaar aan zodat er over de Elektro Magneet elektrisiteit kan lopen
        }
        else
        {
             PORTK &= ~(1 << PK6); // zet de uit zodat er geen elektrisiteit meer over de Elektro Magneet kan lopen
        }
    }
}
