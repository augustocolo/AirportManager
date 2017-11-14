#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define true 1
#define false 0
#define MAXLENGTHOFARRAY 2500

// Airport Info Variables&Types&Functions
int nair=0;
typedef struct gI{
    char type;
    int number;
    char assignedPlaneReg [6 + 1];
    char accType [3] [2 + 1];
    char nodeEnter [2 + 1];
    char nodeExit [2 + 1];
}gatesInfo;
gatesInfo gate[MAXLENGTHOFARRAY];

int nnod=0;
typedef struct nI{
    char name [2 + 1];
    int x;
    int y;
    char adjlist [4] [2 + 1];
}nodesInfo;
nodesInfo node[MAXLENGTHOFARRAY];
int importAirportFile(char);

//Planes Database Variables&Types&Functions
typedef struct pDb{
    char model [4 + 1];
    char type [2 + 1];
}planeDB;
planeDB plane[MAXLENGTHOFARRAY];

//Traffic Database Variables&Types&Functions
typedef struct tDb{
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
}trafficDatabase;
trafficDatabase traffic[MAXLENGTHOFARRAY];
int importTrafficDatabase (char);

int main() {
    char filename[16];
    printf("AIRPORT MANAGER v2.0 by Augusto Colongo\nType the airport that you'd like to use: ");
    gets(filename);
    strcat(filename,".dat");
    if (importAirportFile(filename)!=0){
        printf("ERROR WHILE IMPORTING AIRPORT & NODES FILE");
        return 1;
    }
    printf("Now type the traffic database that you'd like to use: ");
    gets(filename);
    strcat(filename,".dat");
    if (importTrafficDatabase(filename)!=0){
        printf("ERROR WHILE IMPORTING TRAFFIC DATABASE");
        return 1;
    }



    return 0;
}

int importAirportFile(char name){
    //opening airport file
    int i=0;
    // test
    FILE *fp_airportinfo;
    if((fp_airportinfo=fopen(name, "r"))==NULL) {
        return 1;
    }
    fscanf(fp_airportinfo, "%d\t\t\t\t\t\t\n", &nair);
            //printf("%d gates\n",nair);
    for (i=0;i<nair;i++){
        scanf(fp_airportinfo,"%c\t%d\t%s\t%s\t%s\t%s\t%s\n",
              &gate[i].type,
              &gate[i].number,
              &gate[i].accType[0],
              &gate[i].accType[1],
              &gate[i].accType[2],
              &gate[i].nodeEnter,
              &gate[i].nodeExit);
        strcpy(&gate[i].assignedPlaneReg,"NULLNU");
    }
    fscanf(fp_airportinfo, "%d\t\t\t\t\t\t\t\n", &nnod);
    for (i=0;i<nnod;i++){
        fscanf(fp_airportinfo,"%s\t%d\t%d\t%s\t%s\t%s\t%s\n"),
        &node[i].name,
        &node[i].x,
        &node[i].y,
        &node[i].adjlist[0],
        &node[i].adjlist[1],
        &node[i].adjlist[2],
        &node[i].adjlist[3]);
    }
    fclose(fp_airportinfo);
    return 0;
}

int importTrafficDatabase(char name){
    int i=0;
    
}