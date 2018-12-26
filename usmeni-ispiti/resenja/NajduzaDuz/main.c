#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double rastojanje(double xA, double yA, double xB, double yB)
{
    return sqrt((xB-xA)*(xB-xA)+(yB-yA)*(yB-yA));
}

int main()
{
    double xkoordinate[20];
    double ykoordinate[20];
    int n;
    int i,j;
    double xA,yA,xB,yB;
    double duzinaNajvece, novaDuzina;
    printf("Unesite broj tacaka: \n");
    scanf("%d", &n);
    if(n>20)
    {
        printf("Broj tacaka mora biti manji od 20. \n");
        return 5;
    }
    for(i=0; i<n; i++)
    {
        printf("Unesite x i y koordinate %d. tacke:\n ", i+1);
        scanf("%lf %lf", &(xkoordinate[i]), &(ykoordinate[i]));
    }
    duzinaNajvece= rastojanje(xkoordinate[0], ykoordinate[0], xkoordinate[1], ykoordinate[1]);
    xA=xkoordinate[0];
    yA=ykoordinate[0];
    xB=xkoordinate[1];
    yB=ykoordinate[1];
    for(i=0; i<n; i++)
        for(j=i+1; j<n; j++)
        {
          novaDuzina= rastojanje(xkoordinate[i], ykoordinate[i], xkoordinate[j], ykoordinate[j]);
          if(novaDuzina>duzinaNajvece)
          {
               duzinaNajvece=novaDuzina;
               xA=xkoordinate[i];
               yA=ykoordinate[i];
               xB=xkoordinate[j];
               yB=ykoordinate[j];
          }
        }
    printf("Duzina najvece duzi je: %lf, a njene koordinate su: (%lf,%lf),(%lf,%lf) \n", duzinaNajvece,xA,yA,xB,yB);
    return 0;
}
