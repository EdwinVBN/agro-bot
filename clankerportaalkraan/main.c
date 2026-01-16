#include <avr/io.h>
#include "motorconfic.h"
#include "motoraansturing.h"
#include "magneet.h"
#include "humaninterface.h"


void confic(void) // Laat alle confics runnen om PORTS en DDRS te veranderen
{
    knopconfic();
    xmotorconfic();
    ymotorconfic();
    zmotorconfic();
    magneetconfic();
}

void knopconfic(void)// maakt alle knoppen inputs
{
DDRK &= ~(1 << PK1); // knoppen x as
DDRK &= ~(1 << PK2);
DDRK &= ~(1 << PK3);
DDRK &= ~(1 << PK4);
DDRK &= ~(1 << PK5);

DDRE &= ~(1 << PL0); // knoppen y as
DDRE &= ~(1 << PB3);
DDRE &= ~(1 << PB2);
DDRE &= ~(1 << PB1);
DDRE &= ~(1 << PB0);

}


int xbereikt = 0;
int ybereikt = 0;
int START = 1;

void bewegingx(int LOCATIE) // brengt de x as naar de goede coordinaat
{
    int arrayknopx[25] =
    {
        1,1,1,1,1,
        2,2,2,2,2,
        3,3,3,3,3,
        4,4,4,4,4,
        5,5,5,5,5
    };

    int knopx = arrayknopx[LOCATIE - 1];
    static int vorigestaatknopx = 0;

    // MOTOR POSITIEF
    if (knopx > vorigestaatknopx)

    {
        xbereikt = 0;
        while(xbereikt == 0)
        {
        xmotorpositief();

        if (knopx == 1 && (PINK & (1 << PK1))){xmotoruit(); xbereikt = 1;}
        if (knopx == 2 && (PINK & (1 << PK2))){xmotoruit(); xbereikt = 1;}
        if (knopx == 3 && (PINK & (1 << PK3))){xmotoruit(); xbereikt = 1;}
        if (knopx == 4 && (PINK & (1 << PK4))){xmotoruit(); xbereikt = 1;}
        if (knopx == 5 && (PINK & (1 << PK5))){xmotoruit(); xbereikt = 1;}
        }
        vorigestaatknopx = knopx;
    }

    // MOTOR NEGATIEF
    if (knopx < vorigestaatknopx)
    {
        xbereikt = 0;
        while(xbereikt == 0)
        {
        xmotornegatief();
        if (knopx == 1 && (PINK & (1 << PK1))){xmotoruit(); xbereikt = 1;}
        if (knopx == 2 && (PINK & (1 << PK2))){xmotoruit(); xbereikt = 1;}
        if (knopx == 3 && (PINK & (1 << PK3))){xmotoruit(); xbereikt = 1;}
        if (knopx == 4 && (PINK & (1 << PK4))){xmotoruit(); xbereikt = 1;}
        if (knopx == 5 && (PINK & (1 << PK5))){xmotoruit(); xbereikt = 1;}
        }
        vorigestaatknopx = knopx;
    }
}



void bewegingy(int LOCATIE) // brengt de y as naar de goede coordinaat
{
    int arrayknopy[25] = {
        1,2,3,4,5,
        1,2,3,4,5,
        1,2,3,4,5,
        1,2,3,4,5,
        1,2,3,4,5
    };

    int knopy = arrayknopy[LOCATIE - 1];
    static int vorigestaatknopy = 0;

    // MOTOR POSITIEF
    if (knopy > vorigestaatknopy)
    {
        ybereikt = 0;
        while(ybereikt == 0)
        {
        ymotorpositief();

        if (knopy == 1 && (PINL & (1 << PL0))){ymotoruit(); ybereikt = 1;}
        if (knopy == 2 && (PINB & (1 << PB3))){ymotoruit(); ybereikt = 1;}
        if (knopy == 3 && (PINB & (1 << PB2))){ymotoruit(); ybereikt = 1;}
        if (knopy == 4 && (PINB & (1 << PB1))){ymotoruit(); ybereikt = 1;}
        if (knopy == 5 && (PINB & (1 << PB0))){ymotoruit(); ybereikt = 1;}
        }

        vorigestaatknopy = knopy;
    }

    // MOTOR NEGATIEF
    if (knopy < vorigestaatknopy)
    {
        ybereikt = 0;
        while(ybereikt == 0)
        {
        ymotornegatief();
        if (knopy == 1 && (PINL & (1 << PL0))){ymotoruit(); ybereikt = 1;}
        if (knopy == 2 && (PINB & (1 << PB3))){ymotoruit(); ybereikt = 1;}
        if (knopy == 3 && (PINB & (1 << PB2))){ymotoruit(); ybereikt = 1;}
        if (knopy == 4 && (PINB & (1 << PB1))){ymotoruit(); ybereikt = 1;}
        if (knopy == 5 && (PINB & (1 << PB0))){ymotoruit(); ybereikt = 1;}
        }

        vorigestaatknopy = knopy;
    }

}

void bewegingzoppak(void) // beweging met z as en magneet aan zetten om bakje op te pakken en naar boven te brengen.
{
    int vorigestaatknopz = 0;
    int knopz0 = 1;
    int knopz1 = 1;
    int eenkeer = 0;
    if ((vorigestaatknopz == 0) && (eenkeer == 0))
    {
        zmotorpositief();
        if(knopz1 == 1)
        {
        zmotoruit();
        magneetaan();
        vorigestaatknopz = 1;
        eenkeer++;
        }
    }
    if ((vorigestaatknopz == 1) && (eenkeer == 1))
    {
        zmotornegatief();
        if(knopz0 == 1)
        {
        zmotoruit();
        vorigestaatknopz = 0;
        }

    }
}



void bewegingzneerzet(void) // beweging met z as en magneet uit zetten om bakje neer te zetten en arm weer terug naar start positie
{
    int vorigestaatknopz = 0;
    int knopz0 = 1;
    int knopz1 = 1;
    int eenkeer = 0;
    if ((vorigestaatknopz == 0) && (eenkeer == 0))
    {
        zmotorpositief();
        if(knopz1 == 1)
        {
        zmotoruit();
        magneetuit();
        vorigestaatknopz = 1;
        eenkeer++;
        }
    }
    if ((vorigestaatknopz == 1) && (eenkeer == 1))
    {
        zmotornegatief();
        if(knopz0 == 1)
        {
        zmotoruit();
        vorigestaatknopz = 0;
        }

    }
}


int main() //
{
    confic();
    mainhumaninterface();
    int LOCATIE;
    while (START == 1)
    {
        LOCATIE = LOCATIE1;

        bewegingx(LOCATIE);
        bewegingy(LOCATIE);
        bewegingzoppak();


        LOCATIE = LOCATIE2;

        bewegingx(LOCATIE);
        bewegingy(LOCATIE);
        bewegingzneerzet();


    }

}
