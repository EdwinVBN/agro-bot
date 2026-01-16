#include <avr/io.h>
#ifndef humaninterface.h
#define humaninterface.h


//variabelen

int invoer = 0;
int LOCATIE1 = 0;
int LOCATIE2 = 0;
int stap = 0;          // 0 = eerste locatie, 1 = tweede locatie
char toets;


//KEYPAD LAYOUT (4x4)
char keypad[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};


/*
   KEYPAD SCANNEN
   PORTK:
   PK0–PK3 = rijen (output)
   PK4–PK7 = kolommen (input + pull-up)
*/
char scanKeypad(void)
{
    for (int rij = 0; rij < 4; rij++)
    {
        PORTK |= 0x0F;          // alle rijen hoog
        PORTK &= ~(1 << rij);  // één rij laag

        for (int kolom = 0; kolom < 4; kolom++)
        {
            if ((PINK & (1 << (kolom + 4))) == 0)
            {
                return keypad[rij][kolom];
            }
        }
    }
    return 0;   // geen toets ingedrukt
}


/*
   TOETS VERWERKEN
*/

void verwerkToets(char t)
{
    if (t >= '0' && t <= '9')
    {
        invoer = invoer * 10 + (t - '0');

    }
    else if (t == 'C' && stap < 2)   // confirm
    {
        if (stap == 0)
            LOCATIE1 = invoer;
        else if (stap == 1)
            LOCATIE2 = invoer;

        invoer = 0;
        stap++;
    }
}

//main
int mainhumaninterface(void) // display code
{

    DDRA = 0x7F;      // output

    // Keypad invoer
    DDRK = 0x0F;      // output rijen
    PORTK = 0xF0;     // pull-up van kolommen

    while (1)
    {
        toets = scanKeypad();
        if (toets != 0)
        {
            verwerkToets(toets);
        }
    }
}
#endif

