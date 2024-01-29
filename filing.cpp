#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <algorithm>
#include <string.h>

using namespace std;
struct busRoute
{
public:
    char point1[100], point2[100];
    int distance;
    char bus[100];
};

int main()
{
    // R9 ka bilkul sahi sahi ha distance baki sab ka random input kia ha //
    /*busRoute R9[3] = { {"Gulshan-e-Hadeed" , "National Highway" , 1.5 , "R9"},
    {"Salahuddin Ayubi Road" , "National Highway" , 9 , "R9"}
    , {"National Highway" , "Steel Mill Mor" , 1 , "R3"}
     , {"Stell Mill Mor" , "Port Qasim" , 11 , "R9"}
     , {"Port Qasim" , "Razzakabad" , 15 , "R9"}
     , {"Razzakabad" , "Abdullah Goth" , 1.6 , "R9"} ,
        {"Abdullah Goth" , "Chowkundi Mor" ,3.4 , "R9" } ,
        {"Chowkandi Mor" , "FAST University" , 2.1 , "R9"} ,
        {"Fast University" , "Bhains Colony Mor" , 6.6 , "R9"} ,
        {"Manzil Pump" , "Bhains Colony Mor" , 9 , "R9"} ,
        {"Manzil Pump" , "Quaidabad" , 3.9 , "R9" } ,
        } ;  */
    busRoute R_1[] = {{"Model Colony", "Model Clony Mor", 3, "R1"}, {"Model Clony Mor", "Security Printing Press", 2, "R1"}, {"Security Printing Press", "Wireless Gate Bus Stop", 2, "R1"}, {"Wireless Gate Bus Stop", "Chhota Gate", 4, "R1"}, {"Chhota Gate", "Shah Faisal Colony Gate", 3, "R1"}, {"Shah Faisal Colony Gate", "Natha Khan", 2, "R1"}, {"Natha Khan", "Drigh Road", 4, "R1"}, {"Drigh Road", "PAF Base Faisal", 1, "R1"}, {"PAF Base Faisal", "Karsaz", 4, "R1"}, {"Karsaz", "PAF Museum", 6, "R1"}, {"PAF Museum", "Awami Markaz", 2, "R1"}, {"Awami Markaz", "Baloch Colony", 1, "R1"}, {"Baloch Colony", "Fine House", 3, "R1"}, {"Fine House", "Lal Kothi", 2, "R1"}, {"Lal Kothi", "Nursery", 3, "R1"}, {"Nursery", "FTC", 4, "R1"} , {"FTC" , "Aisha Bawany College" , 10, "R1"} , {"Aisha Bawany College" , "Regent Plaza" , 8 , "R1"} , {"Regent Plaza" , "Metropole" , 7 , "R1"} , {"Metropole" , "Shaheen Complex Arts Council" , 15 , "R1"} , {"Shaheen Complex Arts Council" , "City Railway" , 6 , "R1"} , {"City Railway" , "I.I. Chundrigar" , 9 , "R1"} , {"I.I. Chundrigar" , "Tower" , 10 , "R1"}};
    int r1Size = 23; 
    busRoute R_2[] = {{"Power House", "UP Mor", 3, "R2"}, {"UP Mor", "Nagan Chowrangi", 2, "R2"}, {"Nagan Chowrangi", "Shafiq Mor", 5, "R2"}, {"Shafiq Mor", "Sohrab Goth", 2, "R2"}, {"Sohrab Goth", "Lucky One", 6, "R2"}, {"Lucky One", "Imtiaz Mega Store", 4, "R2"}, {"Imtiaz Mega Store", "Gulshan Chowrangi", 3, "R2"}, {"Gulshan Chowrangi", "NIPA", 2, "R2"}, {"NIPA", "Aladin Park", 2, "R2"}, {"Aladin Park", "Millennium Mall", 2, "R2"}, {"Millennium Mall", "Army Public School", 3, "R2"}, {"Army Public School", "Drigh Road", 2, "R2"}, {"Drigh Road", "Shama Shopping Center", 2, "R2"}, {"Shama Shopping Center", "Shah Faisal Colony 2", 1, "R2"}, {"Shah Faisal Colony 2", "Singer Chowrang", 3, "R2"}, {"Singer Chowrang", "Khaddi Stop", 4, "R2"}, {"Khaddi Stop", "Sector 36 Landhi", 5, "R2"}, {"Sector 36 Landhi", "Sector 35 Landhi", 4, "R2"}, {"Sector 35 Landhi", "Sector 33 Korangi", 1, "R2"}, {"Sector 33 Korangi", "Sector 32 Landhi", 4, "R2"}, {"Sector 32 Landhi", "Gulzar Colony", 3, "R2"}, {"Gulzar Colony", "Nasir Jump", 2, "R2"}, {"Nasir Jump", "District Court Korangi", 2, "R2"}, {"District Court Korang", "Indus Hospital", 1, "R2"}};
    int r2Size = 24 ;
    busRoute R_3[] = {{"Power House", "UP Mor", 2, "R3"}, {"UP Mor", "Nagan Chowrangi", 2, "R3"}, {"Nagan Chowrangi", "Erum Shopping", 1, "R3"}, {"Erum Shopping", "Sakhi Hasan Chowrangi", 2, "R3"}, {"Sakhi Hasan Chowrangi", "Five Start Chowrangi", 3, "R3"}, {"Five Start Chowrangi", "Hyderi Bus/ Market", 2, "R3"}, {"Hyderi Bus/ Market", "KDA Chowrangi", 2, "R3"}, {"KDA Chowrangi", "Board Office", 1, "R3"}, {"Board Office", "Nazimabad No. 7", 1, "R3"}, {"Nazimabad No. 7", "Nazimabad No. 6", 2, "R3"},{"Nazimabad No. 6","Eidgah Nazimabad",2,"R3"},{"Eidgah Nazimabad","Liaquatabad-10",3,"R3"},{"Liaquatabad-10","Essa Nagri",4,"R3"},{"Essa Nagri","Hasan Square",2,"R3"},{"Hasan Square","National Stadium",2,"R3"},{"National Stadium","Maritime Museum",4,"R3"},{"Maritime Museum","KDA Scheme 1",3,"R3"},{"KDA Scheme 1","PAF Museum",3,"R3"},{"PAF Museum","Awami Markaz",4,"R3"},{"Awami Markaz","Baloch Colony",2,"R3"},{"Baloch Colony","Fine House",3,"R3"},{"Fine House","Lal Kothi",3,"R3"},{"Lal Kothi","Nursery",4,"R3"},{"Nursery","FTC",5,"R3"},{"FTC","Kalapul",4,"R3"},{"Kalapul","NMC Hospital",4,"R3"},{"NMC Hospital","Sunset Boulevard",3,"R3"},{"Sunset Boulevard","KPT Interchange",2,"R3"},{"KPT Interchange","Imtiaz Store",4,"R3"},{"Imtiaz Store","Brookes Chowrangi",3,"R3"},{"Brookes Chowrangi","Soorty Factor",3,"R3"},{"Soorty Factor","Shaan Chowrangi",5,"R3"}};
    int r3Size = 34 ; 
    busRoute R_4[] = {{"Power House", "UP Mor", 5, "R4"}, {"UP Mor", "Nagan Chowrangi", 4, "R4"}, {"Nagan Chowrangi", "Shafiq Mor", 2, "R4"}, {"Shafiq Mor", "Sohrab Goth", 1, "R4"}, {"Sohrab Goth", "Water Pump", 4, "R4"}, {"Water Pump", "Ayesha Manzil", 2, "R4"}, {"Ayesha Manzil", "Karimabad", 4, "R4"}, {"Karimabad", "Liaquatabad-10", 2, "R4"}, {"Liaquatabad-10", "Daak Khana", 3, "R4"}, {"Daak Khana", "Teen Hatti", 4, "R4"}, {"Teen Hatti", "Jehangir Road", 6, "R4"}, {"Jehangir Road", "Numaish Chowrangi", 5, "R4"}, {"Numaish Chowrangi", "Tibet Center", 2, "R4"}, {"Tibet Center", "Mobile Market", 1, "R4"}, {"Mobile Market", "Urdu Bazar", 5, "R4"}, {"Urdu Bazar", "Jama Cloth Market", 4, "R4"}, {"Jama Cloth Market", "Civil Hospital", 3, "R4"}, {"Civil Hospital", "City Court", 2, "R4"}, {"City Court", "Bolton Market", 2, "R4"}, {"Bolton Market", "Tower", 2, "R4"}};

    busRoute green[]={{"Power House Chowrangi","Abdullah Chowk",2,"Green Line"},{"Abdullah Chowk","Surjani KDA",2,"Green Line"},{"Surjani KDA","Karimi Chowrangi",2,"Green Line"},{"Karimi Chowrangi","4K Chowrangi",3,"Green Line"},{"4K Chowrangi","2 Mint Chowrangi",3,"Green Line"},{"2 Mint Chowrangi","Aisha Complex",2,"Green Line"},{"Aisha Complex","Power House",1,"Green Line"},{"Power House","UP Mor",4,"Green Line"},{"UP Mor","Nagan Chowrangi",3,"Green Line"},{"Nagan Chowrangi","Erum Shopping",2,"Green Line"},{"Erum Shopping","Sakhi Hasan Chowrangi",1,"Green Line"},{"Sakhi Hasan Chowrangi","Five Start Chowrangi",3,"Green Line"},{"Five Start Chowrangi","Hyderi Bus/ Market",2,"Green Line"},{"Hyderi Bus/ Market","KDA Chowrangi",3,"Green Line"},{"KDA Chowrangi","Board Office",5,"Green Line"},{"Board Office","Nazimabad No. 7",2,"Green Line"},{"Nazimabad No. 7","Nazimabad No. 6",1,"Green Line"},{"Nazimabad No. 6","Annu Bhai Park",2,"Green Line"},{"Annu Bhai Park","Model Park",2,"Green Line"},{"Model Park","Nazimabad No. 1",1,"Green Line"},{"Nazimabad No. 1","Lasbela",1,"Green Line"},{"Lasbela","Guru Mandir",2,"Green Line"},{"Guru Mandir","Numaish Chowrangi",3,"Green Line"}};
    int greensize=24;

    

    int r4Size = 20; 
    FILE *fp;
    int retVal;
    fp = fopen("routes.bin", "wb");
    for (int i = 0; i < r1Size; i++)
    {
        retVal = fwrite(&R_1[i], sizeof(busRoute), 1, fp);
    }
    for (int i = 0; i < r2Size; i++)
    {
        retVal = fwrite(&R_2[i], sizeof(busRoute), 1, fp);
    }
    /*for (int i = 0; i < r3Size; i++)
    {
        retVal = fwrite(&R_3[i], sizeof(busRoute), 1, fp);
    } */
    for (int i = 0; i < r4Size; i++)
    {
        retVal = fwrite(&R_4[i], sizeof(busRoute), 1, fp);
    }
     for (int i = 0; i < greensize; i++)
    {
        retVal = fwrite(&green[i], sizeof(busRoute), 1, fp);
    }
    fclose(fp); 
    ofstream WriteRoutesNo("noOfRoutes.txt" , std::ios::binary) ; 
    if(WriteRoutesNo.is_open()) {
        WriteRoutesNo << r1Size + r2Size + r3Size + r4Size ; 
        WriteRoutesNo.close() ; 
    }

   // a.deleteRoute() ; 
    busRoute temp;
    fp = fopen("routes.bin", "rb");
    while (fread(&temp, sizeof(busRoute), 1, fp))
    {
        std::cout << "\nPoint 1: " << temp.point1 << ", Point 2: " << temp.point2;
        std::cout << " , Distance: " << temp.distance << ", Bus: " << temp.bus;
    }
    fclose(fp);
}