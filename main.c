#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define true 1
#define false 0

typedef struct gatesInfo{
    char type;
    int number;
    char assignedPlaneReg [6 + 1];
    char accType [3] [2 + 1];
}gate;

typedef struct nodesInfo{
    char name [2 + 1];
    int x;
    int y;
    char adjlist [4] [2 + 1];
}node;

typedef struct planeDatabase{
    char model [4 + 1];
    char type [2 + 1];
}plane;

typedef struct trafficDatabase{
    int first_hh;
    int first_mm;
    int first_ss;
    int first_time;
    int event_hh;
    int event_mm;
    int event_ss;
    int event_time;
    char event_action;
    char plane_regNum[6 + 1];
    char plane_model[4 + 1];
    char plane_type[2 + 1];
    int plane_alreadyBeen;
    char airport [3 + 1];
}traffic;

int importAirportFile(char);
//int import

int main() {
    char filename;
    printf("AIRPORT MANAGER v2.0 by Augusto Colongo\nType the airport that you'd like to use: ");
    gets(filename);
    strcat(filename,".dat");
    if ((importAirportFile(filename))==1){
        printf("ERROR WHILE IMPORTING AIRPORT & NODES FILE");
        return 1;
    }
    printf("Now type the traffic that you'd like to use: ");
    gets(filename);
    strcat(filename,".dat");
//    if



    return 0;
}

int importAirportFile(char name){
    //opening airport file
    int nair=0;
    FILE *fp_airportinfo;
    if((fp_airportinfo=fopen(name, "r"))==NULL) {
        return 1;
    }
    fscanf(fp_airportinfo, "%d\t\t\t\t\t\t\n", &nair);
    printf("%d gates\n",nair);

}