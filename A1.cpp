/***********************************************************************
Nachname/Surname:             Marey
Vorname/Given name:           Ziad
Studiengang/Course of studis: ISE Software Engineering
***********************************************************************/

#include <iostream>
using namespace std;

int const avgcons_person = 200;
int const avgcons_meter = 9;
int const avgcons_major = 200;
int const avgcons_water = 550;
string water_question;

struct household{
   string city;
   int meters,persons,devices;
   bool water;

};

void input_city(string &city){
   cout<< "in which city is the household located?" << endl;
   cin>> city;
}
void input_integer(string word,int &integer){
   cout<< word << endl;
   cin >> integer;
}

int power_consumption(household h)
{
   float x;
   
    if (h.water){
        x = (avgcons_water * h.persons) + (avgcons_meter * h.meters) + (avgcons_major * h.devices);
    }else {
        x = (avgcons_person * h.persons) + (avgcons_meter * h.meters) + (avgcons_major * h.devices);
    }
   return x;
}

void input_electric_water_heating(bool elecWater){
   cout<<"is hot water heated using electricity? (y(es) or n(o))"<<endl;
   cin>>water_question;
   if (water_question == "yes" || water_question == "y"){
         elecWater = true;
         if (water_question == "y"){
            water_question = "yes";
         }
   }else if(water_question == "no" || water_question == "n"){
         elecWater = false;
         if (water_question == "n"){
            water_question = "no";
         }
   }else {
      cout<<"Invalid answer";
   }
}

float power_cost(household h, float price_kwh){
   float Total_cost;
   int consumption = power_consumption(h);
   return consumption * price_kwh;
}

void print_household(household h, float price_kwh){
   string water_answer;
   if (water_question == "yes" || water_question == "y"){
            water_answer = "yes";
   } else if(water_question == "no" || water_question == "n"){
            water_answer = "no";
   }
   

   cout << "AVERAGE POWER COSTS\n" << "===================\n";
   cout << "household in:                   " << h.city << endl;
   cout << "square meters:                  " << h.meters << endl;
   cout << "persons:                        " << h.persons <<endl;
   cout << "(major)electrical devices:      " << h.devices << endl;
   cout << "price for one kWh               " << price_kwh << endl;
   cout <<"water heated using electricity: " << water_answer << endl;
   cout << "annual power consumption:       " << power_consumption(h) << endl;
   cout << "annual power costs:             " << power_cost(h,price_kwh)<< endl;

   }
int main()
{
   float price_kwh;
   string elecWater;
   household household1;
   cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSEHOLD"<<endl;
   
   input_city(household1.city);

   input_integer("how many square metres does the household have? ", household1.meters);

   input_integer("how many (major) electrical devices does the household have? ", household1.devices);

   input_electric_water_heating(household1.water);



   for(int i=1; i<6 ; i++){
      cout<<i;
      for(price_kwh = 0.3; price_kwh<0.45 ; price_kwh += 0.05){

         household1.persons = i;
         print_household(household1,price_kwh);
      }
   }
return 0;


}
