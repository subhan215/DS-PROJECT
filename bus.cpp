#include <iostream>
using namespace std;

class IntersectionPoint {
public:
    string name;
    IntersectionPoint(string n) : name(n) {}
    IntersectionPoint() {}
};

class Bus {
public:
    IntersectionPoint *points;
    int size;

    Bus(int s) : size(s), points(new IntersectionPoint[s]) {}

    void addRoutes(IntersectionPoint *p) {
        for (int i = 0; i < size; i++) {
            points[i] = p[i];
        }
    }

    void showRoutes() {
        for (int i = 0; i < size; i++) {
            cout << "\nPoint " << i + 1 << ": " << points[i].name;
        }
    }
};

int main() {
    int size1 = 25;
    IntersectionPoint pointsForR2[size1] = { IntersectionPoint("Power House")   ,    IntersectionPoint("UP Mor"), 
	IntersectionPoint("Nagan Chowrangi"), IntersectionPoint("Shafiq Mor"), 
	IntersectionPoint("Sohrab Goth"), IntersectionPoint("Lucky One Mall"), 
	IntersectionPoint("Imtiaz Mega Store"), IntersectionPoint("Gulshan Chowrangi"),
	 IntersectionPoint("NIPA"), IntersectionPoint("Aladin park"), IntersectionPoint("Millenium Mall") ,
	 IntersectionPoint("Army Public School"), IntersectionPoint("Drigh Road"), 
	 IntersectionPoint("Shama Shopping Center"), IntersectionPoint("Shah Faisal Colony 2"), 
	 IntersectionPoint("Singer Chowrangi"), IntersectionPoint("Khaddi Stop"), 
	IntersectionPoint("Sector 36 Landhi"), IntersectionPoint("Sector 35 Landhi"),
	 IntersectionPoint("Sector 36 Korangi"), IntersectionPoint("Sector 32 Landhi"),
	 IntersectionPoint("Gulzar Colony"), IntersectionPoint("Nasir Jump"), 
	 IntersectionPoint("District Court Korangi"),
	 IntersectionPoint("Indus Hospital")};
	 
    Bus R2(size1);
    R2.addRoutes(pointsForR2);
    R2.showRoutes();
    int size2 = 34 ; 
    IntersectionPoint pointsForR3[size2] = { IntersectionPoint("Power House")   ,   
	 IntersectionPoint("UP Mor"), 
	IntersectionPoint("Nagan Chowrangi"), IntersectionPoint("Erum Shopping"), 
	IntersectionPoint("Sakhi Hasan Chowrangi"), IntersectionPoint("Five Start Chowrangi"), 
	IntersectionPoint("Hyderi Bus/ Market"), IntersectionPoint("KDA Chowrangi"),
	 IntersectionPoint("Board Office"), IntersectionPoint("Nazimabad No. 7"), 
	 IntersectionPoint("Nazimabad No. 6") ,
	 IntersectionPoint("Eidgah Nazimabad"), IntersectionPoint("Liaquatabad-10"), 
	 IntersectionPoint("Essa Nagri"), IntersectionPoint("Hassan Square"), 
	 IntersectionPoint("National Stadium"), IntersectionPoint("Maritime Musuem"), 
	IntersectionPoint("KDA Scheme 1"), IntersectionPoint("PFA Museum"),
	 IntersectionPoint("Awami Markaz"), IntersectionPoint("Baloch Colony"),
	 IntersectionPoint("Fine House"), IntersectionPoint("Lal Kothi"), 
	 IntersectionPoint("Nursery"),
	 IntersectionPoint("FTC") , IntersectionPoint("Kalapul") ,IntersectionPoint("NMC Hospital") , 
	 IntersectionPoint("Sunset Boulevard") , IntersectionPoint("Sunset Boulevard") , 
	 IntersectionPoint("KPT Interchange") , IntersectionPoint("Imtiaz Store") , 
	 IntersectionPoint("Brookes Chowrangi") , IntersectionPoint("Surti Factory") , 
	 IntersectionPoint("Shaan Chowrangi") };
	Bus R3(size2);
    R3.addRoutes(pointsForR3);
    R3.showRoutes();
     int size3 = 21; 
    IntersectionPoint pointsForR4[size3] = { IntersectionPoint("Power House")   ,   
	 IntersectionPoint("UP Mor"), 
	IntersectionPoint("Nagan Chowrangi") , IntersectionPoint("Shafiq Mor"), 
	IntersectionPoint("Sohrab Goth"), IntersectionPoint("Water Pump"), 
	IntersectionPoint("Ayesha Manzil"), IntersectionPoint("Karimabad"),
	 IntersectionPoint("Liaquatabad-10"), IntersectionPoint("Daak Khana"), 
	 IntersectionPoint("Teen Hatti") ,
	 IntersectionPoint("Jehangir Road"), IntersectionPoint("Numaish Chowrangi"), 
	 IntersectionPoint("Tibet Center"), IntersectionPoint("Mobile Market"), 
	 IntersectionPoint("Urdu Bazar"), IntersectionPoint("Jama Cloth Market"), 
	IntersectionPoint("Civil Hospital"), IntersectionPoint("City Court"),
	 IntersectionPoint("Bolton Market"), IntersectionPoint("Tower")} ; 
	Bus R4(size3);
    R4.addRoutes(pointsForR4);
    R4.showRoutes();
    
    
}

