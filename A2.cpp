/***********************************************************************
Nachname/Surname:             Marey
Vorname/Given name:           Ziad
Studiengang/Course of studis: ISE Software Engineering
***********************************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

int const avgcons_person = 200;
int const avgcons_meter = 9;
int const avgcons_major = 200;
int const avgcons_water = 550;
int const ColumnWidth = 35;
float Global_price_kWh = 0;
bool isAllPrint = false;
string water_question;

enum Use
{
   once,
   daily,
   mo_fr,
   sa_su,
   weekly
};

struct consumer
{
   string description;
   float watt;
   float watt_standby;
   float hours;
   Use use;
   consumer *next;
};

consumer *head = nullptr;

struct household
{
   string city;
   int meters, persons, devices;
   bool water;
   consumer *consumers = head;
};

void input_use(char choice, Use &ref)
{
   cout << "how often it will be used?" << endl;
   cout << "daily  (d)" << endl;
   cout << "mo_fr  (m)" << endl;
   cout << "once   (o)" << endl;
   cout << "sa_su  (s)" << endl;
   cout << "weekly (w)";
   cin >> choice;

   switch (choice)
   {
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
   case 'w':
      ref = weekly;
      break;
   }
}
void add_consumer_to_household(household *house_ptr, consumer *consumer_ptr)
{
   consumer_ptr = new consumer;
   consumer_ptr->next = house_ptr->consumers;
   house_ptr->consumers = consumer_ptr;

   cout << "what is the description of the power consumer? ";
   cin >> consumer_ptr->description;

   cout << "how many watt it will have? ";
   cin >> consumer_ptr->watt;

   cout << "how many watt standby it will have? ";
   cin >> consumer_ptr->watt_standby;

   int choice;
   input_use(choice, consumer_ptr->use);

   cout << "how many hours it will be operating then? ";
   cin >> consumer_ptr->hours;
}

float annual_hours_of_use(consumer *ptr)
{

   float use;
   switch (ptr->use)
   {
   case daily:
      use = ptr->hours * 365;
      break;
   case weekly:
      use = ptr->hours * 52;
      break;
   case sa_su:
      use = ptr->hours * 104;
      break;
   case mo_fr:
      use = ptr->hours * 260;
      break;
   case once:
      use = ptr->hours;
      break;
   }
   return use;
}

float annual_hours_of_standby(consumer *ptr)
{
   return 8760 - annual_hours_of_use(ptr);
}

float annual_kWh(consumer *ptr)
{
   return (ptr->watt * annual_hours_of_use(ptr) + ptr->watt_standby * annual_hours_of_standby(ptr));
}

consumer *move_up(consumer *&head, int k)
{
   consumer *length = head;
   int list_size = 0;
   if (length != nullptr) // 1 3 2
   {
      while (length != nullptr)
      {
         list_size += 1;
         length = length->next;
      }
   }

   bool isTrue = false;
   int i = 3;
   consumer *follower = head;
   consumer *iterator = follower->next;

   if (k > 1 && list_size > 1)
   {

      if (k == 2)
      {

         follower->next = iterator->next;
         iterator->next = follower;
         head = iterator;
         isTrue = true;
      }
      else
      {
         if (k <= list_size)
         {
            do
            {

               consumer *c = iterator->next;
               if (i == k)
               {
                  iterator->next = c->next;
                  c->next = iterator;
                  follower->next = c;

                  isTrue = true;
               }

               if (isTrue == true)
               {
                  break;
               }
               iterator = iterator->next;
               follower = follower->next;
               i++;
            } while (i < list_size);
         }
      }
   }
   return iterator;
}
void print_consumer(consumer *ptr, int n)
{
   cout << right << setw(ColumnWidth - 2) << n << ": " << ptr->description << " (at address: " << &ptr->description << " )" << setw(ColumnWidth) << left << endl; // not sure about the ptr
   cout << right << setw(ColumnWidth) << "power consumption: " << ptr->watt << " W" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "power consumption standby: " << ptr->watt_standby << " W" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual hours of use: " << annual_hours_of_use(ptr) << " h" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual houseof standby: " << annual_hours_of_standby(ptr) << " h" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual power consumption: " << annual_kWh(ptr) / 1000 << " kWh" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual power costs: " << annual_kWh(ptr) * Global_price_kWh / 1000 << " EUR" << setw(ColumnWidth) << left << endl;
}

void input_city(string &city)
{
   cout << "in which city is the household located? ";
   cin >> city;
}
void input_integer(string word, int &integer)
{
   cout << word;
   cin >> integer;
}

void input_float(string word, float &floating)
{
   cout << word;
   cin >> floating;
}
void input_numberOfHouses(int &houses_number)
{
   cout << "how many households does the house have? ";
   cin >> houses_number;
}

int power_consumption(household h)
{
   float x;

   if (h.water)
   {
      x = (avgcons_water * h.persons) + (avgcons_meter * h.meters);
   }
   else
   {
      x = (avgcons_person * h.persons) + (avgcons_meter * h.meters);
   }
   return x;
}

void input_electric_water_heating(bool elecWater)
{
   do
   {
      cout << "is hot water heated using electricity? (y(es) or n(o)) ";
      cin >> water_question;

      if (water_question == "yes" || water_question == "y")
      {
         elecWater = true;
         if (water_question == "y")
         {
            water_question = "yes";
         }
      }
      else if (water_question == "no" || water_question == "n")
      {
         elecWater = false;
         if (water_question == "n")
         {
            water_question = "no";
         }
      }
   } while (water_question != "y" && water_question != "yes" && water_question != "n" && water_question != "no");
}

float power_cost(household h, float price_kwh)
{
   float consumption = power_consumption(h);
   return consumption * price_kwh;
}

void input_household(household *h)
{

   input_integer("how many square metres does the household have? ", h->meters);

   input_integer("how many persons live in this household? ", h->persons);

   input_electric_water_heating(h->water);

   h->consumers = nullptr;
   // h->consumers = nullptr;
}

household *copy_consumers(household *Original, household *Copy)
{
   consumer *O = new consumer;
   consumer *C = new consumer;
   consumer *iterator = new consumer;
   O = Original -> consumers;
   *C=* O;
   iterator=C;
    while(O != nullptr){
   C->next = new consumer;
   O=O->next;
   C= C-> next;
   C->description = O->description;
   C->watt = O->watt;
   C->watt_standby = O->watt_standby;
   C->use = O->use;
   C->hours = O->hours;

   }
   C->next = Copy->consumers;
   Copy->consumers = iterator;
   return Copy;
   //
}

void print_household(household *h, float price_kwh, int houseNumber)
{

   string water_answer;
   if (water_question == "yes" || water_question == "y")
   {
      water_answer = "yes";
   }
   else if (water_question == "no" || water_question == "n")
   {
      water_answer = "no";
   }
   consumer *storing = h->consumers;
   float annual_total_consumption = 0;

   while (storing != nullptr)
   {

      annual_total_consumption += annual_kWh(storing) / 1000;
      storing = storing->next;
   }

   cout << " H O U S E H O L D  N O  " << houseNumber << "  P O W E R  C O N S U M P T I O N" << endl;
   cout << "----------------------------------------------------------------------" << endl;
   cout << right << setw(ColumnWidth) << "household in: " << h->city << " (at address: " << &(h->city) << ")" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "price for one kWh: " << price_kwh * 100 << " ct/kWh" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "square meters:  " << h->meters << " qm" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "persons: " << h->persons << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "water heated using electricity: " << water_answer << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "list of consumers  " << endl;
   cout << "----------------------------------------------------------------------" << endl;
   int i = 1;
   consumer *ptr = h->consumers;
   while (ptr != nullptr)
   {
      print_consumer(ptr, i);
      ptr = ptr->next;
      i += 1;
   }

   cout << "----------------------------------------------------------------------" << endl;
   cout << right << setw(ColumnWidth) << "power consumption square meters: " << h->meters * avgcons_meter << " kWh" << setw(ColumnWidth) << left << endl;
   if (h->water == true)
   {
      cout << right << setw(ColumnWidth) << "power consumption all persons: " << h->persons * avgcons_water << " kWh" << setw(ColumnWidth) << left << endl;
   }
   else
   {
      cout << right << setw(ColumnWidth) << "power consumption all persons: " << h->persons * avgcons_person << " kWh" << setw(ColumnWidth) << left << endl;
   }
   cout << right << setw(ColumnWidth) << "total annual power consumption: " << power_consumption(*h) + annual_total_consumption << " kWh" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "total annual power costs: " << power_cost(*h, Global_price_kWh) + annual_total_consumption * Global_price_kWh << " EUR" << setw(ColumnWidth) << left << endl;
}

int main()
{
   float price_kwh;
   int n = 1;

   string elecWater;
   household *houseptr = new household;
   consumer *consumerptr = new consumer;

   cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSE" << endl;

   // input_numberOfHouses(n);
   cout << "how many households does the house have? ";
   cin >> n;

   household *ptr_array[n];

   for (int i = 0; i < n; i++)
   {
      ptr_array[i] = nullptr;
   }

   input_city(houseptr->city);

   input_float("what is the price for one kWh in EUR? ", price_kwh);

   Global_price_kWh = price_kwh;

   bool quit = false;
   do
   {
      cout << "q quit\ni input power consumer\nu move up power consumer\np print household\na print all households\nn new household\nc copy all consumers (added to already existing ones)\n>>";

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
         quit = true;
         break;
      case 'i':
         int house_number;
         cout << "number of household? ";
         cin >> house_number;
         add_consumer_to_household(ptr_array[house_number - 1], consumerptr);
         break;
      case 'u':
      {
         int j;
         cin >> j;
         int k;
         cout << "which one? ";
         cin >> k;
         move_up(ptr_array[j]->consumers, k);
      }
      break;
      case 'p':
      {
         int house_number;
         cout << "number of household? ";
         cin >> house_number;
         print_household(ptr_array[house_number - 1], price_kwh, house_number);
      }
      break;

      case 'a':
      {
         for (int p = 0; p < n; p++)
         {
            ptr_array[p]->city = houseptr->city;
         }
         for (int i = 1; i <= n; i++)
         {
            if (ptr_array[i - 1] != nullptr)
            {
               isAllPrint = true;
               print_household(ptr_array[i - 1], price_kwh, i);
            }
         }
      }
      break;
      case 'n':
      {
         int house_number;
         cout << "number of household? ";
         cin >> house_number;

         // kwh
         if (ptr_array[house_number - 1] == nullptr)
         {
            // missing

            ptr_array[house_number - 1] = new household;
            input_household(ptr_array[house_number - 1]);
         }
         else
         {
            cerr << "House Number is already in the list" << endl;
         }
      }
      break;
      case 'c':
      {
         int copy, original;
         do
         {
            cout << "number of household from which to copy consumers? ";
            cin >> original;
            if (original < 0 || original > n)
            {
               cout << "The Number you entered is out of range, please enter a valid one";
            }
         } while (original < 0 || original > n);
         do
         {
            cout << "number of household to copy to? ";
            cin >> copy;
            if (copy < 0 || copy > n)
            {
               cout << "The Number you entered is out of range, please enter a valid one";
            }
         } while (copy < 0 || copy > n);
         copy_consumers(ptr_array[original - 1], ptr_array[copy - 1]);
      }
      break;
      default:
      {
         cout << "sorry wrong choice" << endl;
      }
      break;
      }
   } while (quit != true);

   return 0;
}
