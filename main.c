#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define true 1
#define false 0
#define MAXLENGTHOFARRAY 2500

int imain=0;

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
int importAirportFile(char*);

//Planes Database Variables&Types&Functions
int npldb=0;
typedef struct pDb{
    char model [4 + 1];
    char type [2 + 1];
}planeDB;
planeDB plane[MAXLENGTHOFARRAY];
int importPlaneDatabase ();

//Traffic Database Variables&Types&Functions
int ntra=0;
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
int importTrafficDatabase (char *);

//Time Variables&Functions
int calcMonoTime(int, int, int);
void timeTicker();
struct Timer {
    int hh;
    int mm;
    int ss;
}time;
/*time.hh= 0;
time.mm= 0;
time.ss= 0;*/

//Movements functions declarations
int arrivalMovt();
int departureMovt();
int taxiMovt();

int main() {
    char filename[64];
    if (importPlaneDatabase() != 0) {
        printf("ERROR WHILE IMPORTING PLANES DATABASE");
        return 1;
    }
    printf("AIRPORT MANAGER v2.0 by Augusto Colongo\nType the airport that you'd like to use: ");
    gets(filename);
    strcat(filename, "airport.dat");
    if (importAirportFile(filename) != 0) {
        printf("ERROR WHILE IMPORTING AIRPORT & NODES FILE");
        return 1;
    }
    printf("Now type the traffic database that you'd like to use: ");
    gets(filename);
    strcat(filename, "traffic.dat");
    if (importTrafficDatabase(filename) != 0) {
        printf("ERROR WHILE IMPORTING TRAFFIC DATABASE");
        return 1;
    }
    printf("Done importing, now let's start!\n");
    system("cls"); //is this working? IDK
    while (time.hh!=24){
        timeTicker();
        for (imain=0;imain<ntra;imain++){
            if (time.hh == traffic[imain].event_hh &&
                    time.mm == traffic[imain].event_mm &&
                    time.ss == traffic[imain].event_ss){
               switch (traffic[imain].event_action){
                   case 'A':
                       if (arrivalMovt()!=0){
                           printf("Plane %s could not be assigned to any gate\n", traffic[imain].plane_regNum);
                           return 1;
                       };
                       break;
                   case 'D':
                       if (departureMovt()!=0){
                           //add text
                           return 1;
                       }
                       break;
                   case 'T':
                       if (taxiMovt()!=0){
                           //add text
                           return 1;
                       }
                       break;
                   default:
                       printf("ERROR WHILE READING TRAFFIC ACTION");
                       return 1;
               }
            }
        }
    }




    return 0;
}

int importTrafficDatabase(char name [64]){
    int i=0, j=0;
    int planefound=false;
    FILE *fp_trafficinfo;
    if((fp_trafficinfo=fopen(name, "r")) == NULL){
        return 1;
    }
    fscanf(fp_trafficinfo, "%d\t\t\t\t\n", &ntra);
    for (i=0; i<ntra;i++) {
        fscanf(fp_trafficinfo,"%d:%d:%d\t%c\t%s\t%s\t%s\t\n",
               &traffic[i].first_hh,
               &traffic[i].first_mm,
               &traffic[i].first_ss,
               &traffic[i].event_action,
               traffic[i].plane_regNum,
               traffic[i].plane_model,
               traffic[i].airport);
        traffic[i].plane_alreadyBeen=0;
        for (j=0;j<i;j++){
            if (strcmp(traffic[i].plane_regNum,traffic[j].plane_regNum)==0) {
                traffic[i].plane_alreadyBeen++;
            }
        }
        for (j=0;j<npldb && planefound==false;j++){
            if (strcmp(traffic[i].plane_model,plane[j].model)==0){
                strcpy(traffic[i].plane_type,plane[j].type);
                planefound=true;
            } else if (j==npldb-1){
                printf("error while comparing traffic database with plane database: model %s not found\n", traffic[i].plane_model);
                return 1;
            }
        }
        //event time = first time
        traffic[i].event_hh= traffic[i].first_hh;
        traffic[i].event_mm= traffic[i].first_mm;
        traffic[i].event_ss= traffic[i].first_ss;
        traffic[i].first_time= calcMonoTime(traffic[i].first_hh,
                                            traffic[i].first_mm,
                                            traffic[i].first_ss);
        traffic[i].event_time= traffic[i].first_time;
    }
    fclose(fp_trafficinfo);
    return 0;
}

int importPlaneDatabase (){
    int i=0;
    FILE *fp_planedatabase;
    if((fp_planedatabase=fopen("PlaneDB.dat","r"))==NULL){
        return 1;
    }
    fscanf(fp_planedatabase, "%d\t\n", &npldb);
    for (i=0;i<npldb;i++){
        fscanf(fp_planedatabase,"%s\t%s\n",
        plane[i].model,
        plane[i].type);
    }
    fclose(fp_planedatabase);
}

int calcMonoTime(int hh, int mm, int ss){
    int monotime;
    monotime= (hh*100000)+(mm*1000)+ss;
    return monotime;
}

int importAirportFile(char name [64]) {
    //opening airport file
    int i=0;
    // test
    FILE *fp_airportinfo;
    if((fp_airportinfo=fopen(name, "r")) == NULL){
        return 1;
    }
    fscanf(fp_airportinfo, "%d\t\t\t\t\t\t\n", &nair);
    //printf("%d gates\n",nair);
    for (i=0;i<nair;i++){
        scanf((const char *) fp_airportinfo, "%c\t%d\t%s\t%s\t%s\t%s\t%s\n",
              &gate[i].type,
              &gate[i].number,
              gate[i].accType[0],
              gate[i].accType[1],
              gate[i].accType[2],
              gate[i].nodeEnter,
              gate[i].nodeExit);
        strcpy(gate[i].assignedPlaneReg,"NULLNU");
    }
    fscanf(fp_airportinfo, "%d\t\t\t\t\t\t\t\n", &nnod);
    for (i=0;i<nnod;i++){
        fscanf(fp_airportinfo,"%s\t%d\t%d\t%s\t%s\t%s\t%s\n",
               node[i].name,
               &node[i].x,
               &node[i].y,
               node[i].adjlist[0],
               node[i].adjlist[1],
               node[i].adjlist[2],
               node[i].adjlist[3]);
    }
    fclose(fp_airportinfo);
    return 0;
}

void timeTicker (){
   time.ss++;
    if (time.ss==60){
        time.ss=0;
        time.mm++;
    }
    if (time.mm==60) {
        time.mm = 0;
        time.hh++;
    }
}

int arrivalMovt(){
    int iair=0;
    int checkArr=false;
    for (iair=0;iair<nair && checkArr==false;iair++){
        if (strcmp(gate[iair].assignedPlaneReg,"NULLNU")==0 &&
                strcmp(gate[iair].accType[0],traffic[imain].plane_type)==0 ||
                strcmp(gate[iair].accType[1],traffic[imain].plane_type)==0 ||
                strcmp(gate[iair].accType[2],traffic[imain].plane_type)==0){
            strcpy(gate[iair].assignedPlaneReg,traffic[imain].plane_regNum);
            checkArr=true;
            //PATHFINDER
        } else if (iair==nair-1){
            return 1;
        }
    }
    return 0;
}

int departureMovt(){
    int iair=0;
    for (iair=0;iair<nair;iair++){
        if(strcmp(gate[iair].assignedPlaneReg,traffic[imain].plane_regNum)==0){
            strcpy(gate[iair].assignedPlaneReg,"NULLNU");
            //PATHFINDER
        } else if (iair==nair){
            return 1;
        }
    }
    return 0;
}

