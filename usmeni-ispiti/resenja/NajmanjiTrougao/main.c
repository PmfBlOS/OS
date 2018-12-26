#include <stdio.h>
#include <stdlib.h>

#include <math.h>

double rastojanje(double xA, double yA,
                  double xB, double yB)
{
    return sqrt( (xB-xA)*(xB-xA) + (yB-yA)*(yB-yA) );
}

double povrsinaTrougla( double a, double b, double c)
{
    double s;
    s = (a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

int main()
{
    double xKoordinate[6];
    double yKoordinate[6];
    int n; // broj tacaka

    int i,j,k;
    double povrsinaNajmanjeg;
    double novaProvrsina;

    // provera da li dobro radi rastojanje
    //printf("%lf", rastojanje(2, 0, 3, 1 ));

    // provera da li dobro radi povrsinaTrougla
    //printf("%lf\n", povrsinaTrougla(1,1,1 ));
    //printf("%lf\n", povrsinaTrougla(3,4,5 ));

    // Ucitavanje nizova
    printf("Unesite broj tacaka:\n");
    scanf("%d", &n);
    if( (n<3) || (n>6) )
    {
        printf("Broj tacaka mora biti izmedju 3 i 6. \n");
        return 42;
    }
    for(i=0; i<n; i++)
    {
        printf(" Unesite x i y koordinatu tacke:\n");
        scanf("%lf %lf", &(xKoordinate[i]), &(yKoordinate[i]));
    }
    // Provera da li dobro radi unos tacaka
    //for(i=0; i<n; i++)
    //    printf( "(%lf, %lf) ", xKoordinate[i], yKoordinate[i]);

    povrsinaNajmanjeg = povrsinaTrougla(
        rastojanje(xKoordinate[0], yKoordinate[0], xKoordinate[1], yKoordinate[1]),
        rastojanje(xKoordinate[0], yKoordinate[0], xKoordinate[2], yKoordinate[2]),
        rastojanje(xKoordinate[1], yKoordinate[1], xKoordinate[2], yKoordinate[2]) );
    for( i=0; i< n; i++)
        for( j=i+1; j<n; j++)
            for( k= j+1; k<n; k++)
            {
                novaProvrsina = povrsinaTrougla(
                    rastojanje(xKoordinate[i], yKoordinate[i], xKoordinate[j], yKoordinate[j]),
                    rastojanje(xKoordinate[i], yKoordinate[i], xKoordinate[k], yKoordinate[k]),
                    rastojanje(xKoordinate[j], yKoordinate[j], xKoordinate[k], yKoordinate[k]) );
                if( novaProvrsina < povrsinaNajmanjeg )
                    povrsinaNajmanjeg = novaProvrsina;
            }
    printf("Povrsina najmanjeg trougla je %lf", povrsinaNajmanjeg);
    return 0;
}
