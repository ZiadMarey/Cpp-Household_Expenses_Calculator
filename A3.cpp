/***********************************************************************
Nachname/Surname:             Marey
Vorname/Given name:           Ziad
Studiengang/Course of studis: ISE Software Engineering
***********************************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int Total_Days = 10;
const int Total_Time = 12;

enum Use
{
   monday,
   tuesday,
   wednesday,
   thursday,
   friday,
   saturday,
   sunday,
   once,
   daily,
   mo_fr,
   sa_su

};

struct year
{
   int year;
   Use first_day;
   string unit;
   float year_arr[Total_Days][Total_Time];
};

ostream &operator<<(ostream &u, Use &use)
{
   switch (use)
   {
   case monday:
      u << "Monday";
      break;
   case tuesday:
      u << "Tuesday";
      break;
   case wednesday:
      u << "Wednesday";
      break;
   case thursday:
      u << "Thursday";
      break;
   case friday:
      u << "Friday";
      break;
   case saturday:
      u << "Saturday";
      break;
   case sunday:
      u << "Sunday";
      break;
   case once:
      u << "Once";
      break;
   case daily:
      u << "Daily";
      break;
   case mo_fr:
      u << "Monday to Friday";
      break;
   case sa_su:
      u << "Saturday and Sunday";
      break;
   }
   return u;
}

Use operator++(Use &use)
{

   return Use((int(use) + 1));
}

ostream &operator<<(ostream &o, year &y)
{
   Use first_day = y.first_day;
   o << "year: " << y.year << " (unit: "<< y.unit << ")"<< "\n";
   for (int dayNum = 0; dayNum < Total_Days; dayNum++)
   {  
      o << "day " << dayNum << ": " << first_day;
      for (int n = 0; n < (Total_Time /4); n++)
      {
         o << "\n"<< n << ":00";

         for (int i = 0; i < 4; i++)
         {

            o << "       " << setw(2) << fixed << setprecision(2) << y.year_arr[dayNum][i];
         }
      }
      o << "\n";
      if (int(first_day) == 6)
      {
         first_day = monday;
      }
      else
      {
         first_day = ++(first_day);
      }
   }
   return o;
}

year operator+(year &year2, year &year1)
{
   
   if (year1.year != year2.year)
   {

      cout << "The years do not match" << endl;
      
   }
   else if (year1.unit != year2.unit)
   {

      cout << "The units do not match" << endl;
      
   }
   else if (year1.first_day != year2.first_day)
   {

      cout << "The First days of the year do not match";
      
   }
   else
   {
      year y;
      y.unit = year2.unit;
      y.year = year2.year;
      y.first_day = year2.first_day;

      for (int dayNum = 0; dayNum < Total_Days; dayNum++)
      {
         for (int n = 0; n < Total_Time; n++)
         {
               y.year_arr[dayNum][n] = year1.year_arr[dayNum][n] + year2.year_arr[dayNum][n];

         }
      }
      return y;
   }
   
}

year operator-(year &big_year, year &small_year){

   if (big_year.year != small_year.year)
   {

      cerr << "The years do not match" << endl;
      
   }
   else if (big_year.unit != small_year.unit)
   {

      cerr << "The units do not match" << endl;

   }
   else if (big_year.first_day != small_year.first_day)
   {

      cerr << "The First days of the year do not match";
      
   }
   else{
      year Subtract;
      Subtract.year = big_year.year;
      Subtract.first_day = big_year.first_day;
      Subtract.unit = big_year.unit;
      for (int dayNum = 0; dayNum < Total_Days; dayNum++)
      {
         for (int n = 0; n < Total_Time; n++)
         {
               Subtract.year_arr[dayNum][n] = big_year.year_arr[dayNum][n] - small_year.year_arr[dayNum][n];

         }
      }
      return Subtract;
   }
      
}

year operator*(float num, year& y){

      year Multiply;
      Multiply.year = y.year;
      Multiply.first_day = y.first_day;
      Multiply.unit = y.unit;
      for (int dayNum = 0; dayNum < Total_Days; dayNum++)
      {
         for (int n = 0; n < Total_Time; n++)
         {
              Multiply.year_arr[dayNum][n] = y.year_arr[dayNum][n] * num;

         }
      }
      return Multiply;

}


void add_consumption(year &y, int day, int from_min, int to_min, float wattage)
{
    
   int begin_quarter = from_min / 15;
   int begin_min = from_min % 15;
   
   y.year_arr[day][begin_quarter] += (wattage / 60.0) * (15 - begin_min);

   int last_quarter = to_min / 15;
   int n = begin_quarter + 1;
   for (; n < last_quarter; n++){
      y.year_arr[day][n] += (wattage / 60.0) * 15;

   }
   int last_min = to_min % 15;
   y.year_arr[day][last_quarter] += (wattage / 60.0) * last_min;
}
        

void add_consumption(year &y, Use use, int from_min, int to_min, float wattage)
{

   Use now_day = y.first_day;
   int days = Total_Days;

   switch (use)
   {
   case mo_fr:
   {
      for (int i = 0; i < Total_Days; i++)
      {
         if (now_day != sunday && now_day != saturday)
         {
            add_consumption(y, int(now_day), from_min, to_min, wattage);
         }
         if (now_day == sunday)
         {
            now_day = monday;
         }
         else
         {
            now_day = ++now_day;
         }
      }
   }
   break;
   case daily:
   {
      for (int i = 0; i < Total_Days; i++)
      {
         add_consumption(y, int(now_day), from_min, to_min, wattage);
         if (now_day == sunday)
         {
            now_day = monday;
         }
         else
         {
            now_day = ++now_day;
         }
      }
   }
   break;

   case sa_su:
   {
      for (int i = 0; i < Total_Days; i++)
      {
         if (now_day == sunday && now_day == saturday)
         {
            add_consumption(y, int(now_day), from_min, to_min, wattage);
         }
         if (now_day == sunday)
         {
            now_day = monday;
         }
         else
         {
            now_day = ++now_day;
         }
      }
   }
   break;

   default:
   {
      for (int i = 0; i < Total_Days; i++)
      {
         if (now_day == use)
         {
            cout<<"The output works";
            add_consumption(y, int(now_day), from_min, to_min, wattage);
         }
         if (now_day == sunday)
         {
            now_day = monday;
         }
         else
         {
            now_day = ++now_day;
         }
      }
   }
   break;
   }
}

void input_use(char choice, Use &ref)
{
   cout << "how often it will be used?" << endl;
   cout << "Monday    (0)" << endl;
   cout << "Tuesday   (1)" << endl;
   cout << "Wednesday (2)" << endl;
   cout << "Thursday  (3)" << endl;
   cout << "Friday    (4)" << endl;
   cout << "Saturday  (5)" << endl;
   cout << "Sunday    (6)" << endl;
   cout << "daily     (d)" << endl;
   cout << "mo_fr     (m)" << endl;
   cout << "once      (o)" << endl;
   cout << "sa_su     (s)?" << endl;
   cin >> choice;

   switch (choice)
   {
   case '0':
      ref = monday;
      break;
   case '1':
      ref = tuesday;
      break;
   case '2':
      ref = wednesday;
      break;
   case '3':
      ref = thursday;
      break;
   case '4':
      ref = friday;
      break;
   case '5':
      ref = saturday;
      break;
   case '6':
      ref = sunday;
      break;
   case 'd':
      ref = daily;
      break;
   case 'm':
      ref = mo_fr;
      break;
   case 'o':
      ref = once;
      break;
   case 's':
      ref = sa_su;
      break;
   }
}

string set_unit (year &y ,string new_unit){

      y.unit = new_unit;
      return y.unit;
}

inline year zeros(year &y)
{
   for (int dayNum = 0; dayNum < Total_Days; dayNum++)
   {
      for (int n = 0; n < Total_Time; n++)
      {
            y.year_arr[dayNum][n] = 0.0;
         }
      }
   
   return y;
}


inline float sum(year &y)
{

   float sum = 0;
   for (int dayNum = 0; dayNum < Total_Days; dayNum++)
   {
      for (int n = 0; n < Total_Time; n++)
      {

            sum += y.year_arr[dayNum][n];
      }
   }
   return sum;
}

inline int time(int h, int m)
{
   return (h * 60 + m);
}

inline year& ones(year &y){

      for (int dayNum = 0; dayNum < Total_Days; dayNum++)
   {
      for (int n = 0; n < Total_Time; n++)
      {

            y.year_arr[dayNum][n] = 1;
      }
   }
   return y;
   
}

int main()
{

   float price_kwh = 0.3;
   year actual;
   year total;
   Use use;
   bool is_quit = false;
   float watt = 0;
   cout << "YEARLY CONSUMPTION QUARTER HOUR" << endl;

   actual.first_day = monday;
   actual.year = 2024;
   actual.unit = "Watt";
   zeros(actual);

   total.first_day = monday;
   total.year = 2024;
   total.unit = "Watt";
   zeros(total);
   do
   {
      cout << "q quit\na add actual to total (using operator +)\nm subtract actual from total (using operator -)\ns scalar multiplication\nc change unit\nv sum up values\no output actual (using operator <<)\nt output total (using operator <<)\nu add consumption according to frequency of use (call functions add_consumption)\ny set actual to ones (call function ones)\nz set actual to zeros (call function zeros)\n>> ";
      char v;
      cin >> v;
      if (cin.fail())
      {
         cout << "You have entered a wrong choice";
         continue;
      }

      switch (v)
      {
      case 'q':
      {
         is_quit = true;
         break;
      }
      case 'm':
      {
         total = total - actual;
         break;
      }
      case 's':
      {
         float Coefficient;
         char user_choice;
         cout<<"a for actual\nt for total"<<endl;
         cin>> user_choice;
         cout<<"value of scalar? ";
         cin>>Coefficient;
         if(user_choice == 'a'){
            actual = Coefficient * actual;
         }else if(user_choice == 't'){
            total = Coefficient * total;
         }else {
            cerr<<"Wrong Input";
            
         }
         break;
      }
      case 'c':
      {
         char unit_choice;
         string new_unit;
         cout<<"a for actual\nt for total"<<endl;
         cin>> unit_choice;
         cout<<"what is the new unit? ";
         cin>>new_unit;

         switch(unit_choice){
            case 'a':
            actual.unit = set_unit(actual, new_unit);
            break;
            case 't':
            total.unit = set_unit(total , new_unit);
            default:
            cout<<"Wrong Input";
            break;
         } 
         break;
      }
      case 'a':
      {
         total = total + actual;
         break;
      }
      case 'v':
      {
         float sum_total, sum_actual;
         sum_actual = sum(actual);
         sum_total = sum(total);
         cout << "sum actual = " << fixed << setprecision(2) << sum_actual << " " <<actual.unit << endl;
         cout << "sum_total = " << fixed << setprecision(2) << sum_total<< " "<< total.unit<<endl;
         break;
      }
      case 'o':
      {
         cout << actual;
         break;
      }
      case 't':
      {
         cout << total;
         break;
      }
      case 'u':
      {
         int from_hour, from_min, to_hour, to_min, once_day;
         char c, use_choice = '\0';
         input_use(use_choice, use);
         if (use == once)
         {
            cout << "on which day? ";
            cin >> once_day;
            cout << "from hour:minute? ";
            cin >> from_hour >> c >> from_min;
            cout << "to hour:minute? ";
            cin >> to_hour >> c >> to_min;
            cout << "how many watt it will have? ";
            cin >> watt;
            add_consumption(actual, once_day, time(from_hour, from_min), time(to_hour, to_min), watt);
            break;
         }
         else
         {
            cout << "from hour:minute? ";
            cin >> from_hour >> c >> from_min;
            cout << "to hour:minute? ";
            cin >> to_hour >> c >> to_min;
            cout << "how many watt it will have? ";
            cin >> watt;
            add_consumption(actual, use, time(from_hour, from_min), time(to_hour, to_min), watt);
            break;
         }
      }
      case 'y':
      {
         ones(actual);
         break;
      }
      case 'z':
      {
         zeros(actual);
         break;
      }
      default:
      {
         cout << "You have entered an invalid input, please try again\n";
         break;
      }
      }
   } while (is_quit == false);

   return 0;
}
