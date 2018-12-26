#include <stdio.h>
#include <stdlib.h>

double udaljenost(double a, double b)
{
    double x;
    x = a-b;
    if( x >= 0 )
        return x;
    else
        return -x;
}

double udaljenost2(double a, double b)
{
    return (a-b>=0)?(a-b):(b-a);
}

int main()
{
    double elementi[15];
    int n; // broj elemenate
    int i; // brojac u cikljusima
    double aritmetickaSredina;
    double najviseUdaljen;

    // 1. Ucitavanje u niz
    printf("Koliko clanova?\n");
    scanf("%d", &n);
    for(i=0; i<n; i++)
    {
        printf("Unesi clan: ");
        scanf("%lf", &(elementi[i]));
    }
    //provera uspesnosti ucitavanja
    //for(i=0; i<n; i++)
    //    printf("%lf\n", elementi[i]);

    // 2. Odredjivanje aritmeticke sredine niza
    aritmetickaSredina = 0;
    for(i=0; i<n; i++)
        aritmetickaSredina += elementi[i];
    aritmetickaSredina /= n;
    // provera uspesnosti racunanja aritmeticke sredine
    //printf("%lf", aritmetickaSredina);

    // 3. Odredjivanje najudaljenijeg elementa
    najviseUdaljen = elementi[0];
    for(i=1; i<n; i++)
        if(udaljenost2(elementi[i], aritmetickaSredina) >
             udaljenost2(najviseUdaljen, aritmetickaSredina))
                najviseUdaljen = elementi[i];
    printf("%lf", najviseUdaljen);
    return 0;
}
