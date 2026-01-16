#ifndef magneet.h
#define magneet.h

void magneetconfic() // magneet ports output en uit zetten
{
    DDRK &= ~(1 << PK6);
    PORTK &= ~(1 << PK6);
}
void magneetaan() //magneet aanzetten
{
    PORTK |= (1 << PK6);
}
void magneetuit() //magneet uitzetten
{
    PORTK &= ~(1 << PK6);
}

#endif

