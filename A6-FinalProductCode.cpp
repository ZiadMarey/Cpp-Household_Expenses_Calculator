/***********************************************************************
Nachname/Surname:             Marey
Vorname/Given name:           Ziad
Studiengang/Course of studis: ISE Software Engineering
***********************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
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

class Device{
    private:
        string description;
        Device *next;
        
    public:
        Device(Device *);
        virtual ~Device();
        string get_description();
        Device* get_next();
        void set_description(string);
        void set_next(Device*);
        void virtual input();
        string use_to_string(Use);
        Use input_use();
        void virtual print(int,float) = 0;
        float virtual annual_kWh() = 0;
        virtual Device* get_a_copy() = 0;
        string virtual get_string_for_file(char) = 0;

};

Device::Device(Device* r = nullptr): next(r){}

Device::~Device(){
    cout<<"Device "<< this->get_description() << " at address "<< this << " deleted"<<endl;
}

//getters
string Device::get_description(){
    return this->description;
}
Device* Device::get_next(){
    return this->next;
}

//setters
void Device::set_description(string description){
    this->description = description;
}
void Device::set_next(Device* next){
    this->next = next;
}
void Device::input(){
    cout<<"what is the description of the power consumer? ";
   cin.ignore();
   getline(cin,this->description);

}

class consumer : public Device
{
   private:
      float watt;
      Use use;
      static unsigned int total_number;
      
   public:
      consumer(Device*);
      virtual ~consumer();

      float get_watt();
      Use get_use();

      void set_watt(float);
      void set_use(Use);

      void virtual input() override;  // Virtual means that this function is dynamically binded, even in any class that inherits it
      static int get_total_number();
      static void increment_total_number();
      static void decrement_total_number();

};



unsigned int consumer::total_number = 0;

consumer::consumer(Device* r = nullptr) : Device(r){
         total_number += 1;
}

consumer::~consumer(){
         cout<<"Consumer "<< this->get_description() << " at address "<< this << " deleted"<<endl;
        this->total_number --;
      }

void consumer::input(){
   Device::input();
   cout<<"how many watt it will have?";
   cin>>this->watt;
   char user_use;
   cout<<"How often will it be used ? ";
   this->use = input_use();
}

// getters
float consumer::get_watt(){
   return this->watt;
}

Use consumer::get_use(){
   return this->use;
}

int consumer::get_total_number(){
   return total_number;
}
//setters
void consumer::set_watt(float watt){
   this->watt = watt;
}
void consumer::set_use(Use use){
   this->use = use;
}

void consumer::increment_total_number(){
   total_number ++;
}
void consumer::decrement_total_number(){
   total_number--;
}


consumer *head = nullptr;

class household
{
   private:
      string power_suplier;
      int meters;
      int persons;
      int num_devices;
      bool water;
      float power_price;
      Device* devices;
      static unsigned int household_instances;

   public:
      household() : devices(nullptr){
         household_instances += 1;
      }
      ~household(){

         Device *next;
         while( this->devices != nullptr){
            
            next = this->devices->get_next();
            this->devices->~Device();
            this->devices = next;
            
         }
         cout<< "Household at address "<< this <<" deleted"<<endl;
         
         
      }
      string get_power_supplier();
      int get_meters();
      int get_persons();
      int get_num_devices();
      bool get_water();
      float get_power_price();
      Device* get_devices();
      void set_power_supplier(string);
      void set_meters(int);
      void set_persons(int);
      void set_num_devices(int);
      void set_water(bool);
      void set_power_price(float);
      void set_devices(Device *);
      void input(string power_suplier,int meters,int persons, int num_devices, bool water,float power_price);
      void print();
      void add_devices_to_household(Device*);
      int count_devices(household*);
      household*copy_devices(household*);
      Device* move_up(Device *, int);
      float power_consumption();
      void print_household(int);
      float power_cost(float);
      void input_household();
      void input_integer(string word, int &integer);

};
void household::input(string power_suplier,int meters,int persons, int num_devices, bool water,float power_price){
   this->power_suplier = power_suplier;
   this->meters = meters;
   this->persons = persons;
   this->num_devices = num_devices;
   this->water = water;
   this->power_price = power_price;
}
void household::print(){
   
}

//getters
string household::get_power_supplier(){
   return this->power_suplier;
}
int household::get_meters(){
   return this->meters;
}
int household::get_persons(){
   return this->persons;
}
int household::get_num_devices(){
   return this->num_devices;
}
bool household::get_water(){
   return this->water;
}
float household::get_power_price(){
   return this->power_price;
}
Device* household::get_devices(){
   return this->devices;
}
//setters
void household::set_power_supplier(string power_suplier){
   this->power_suplier = power_suplier;
}
void household::set_meters(int meters){
   this->meters = meters;
}
void household::set_persons(int persons){
   this->persons = persons;
}
void household::set_num_devices(int num_devices){
   this->num_devices = num_devices;
}
void household::set_water(bool water){
   this->water= water;
}
void household::set_power_price(float power_price){
   this->power_price= power_price;
}
void household::set_devices(Device* devices){
   this->devices = devices;
}

class Address
{
   private:
      string street, no, zip,city;
   public:
      Address();
      ~Address(){
                  cout<<"Address " << this->print() << " at address "<< this << " deleted"<<endl;
      }
      string get_street();
      string get_no();
      string get_zip();
      string get_city();
      void input(string,string,string,string);
      string print();
      void input_user_address();
      string to_String();
};

Address::Address(): street(""),no(""),zip(""),city(""){}
//getters
string Address::get_street(){
   return this->street;
}
string Address::get_no(){
   return this->no;
}
string Address::get_zip(){
   return this->zip;
}
string Address::get_city(){
   return this->city;
}
string Address::to_String(){
   return (this->street + ", " + this->no + ", " + this->zip + ", " + this->city);
}
void Address::input(string street,string no,string zip,string city){
   this->street = street;
   this->no = no;
   this->zip = zip;
   this->city = city;
}
string Address::print(){
   string sentence;
   sentence = this->get_street() + " " + this->get_no() + ", " + this->get_zip() + " " + this->get_city();
   return sentence;
}
void Address::input_user_address(){
   string street,no,zip,city;
   cout<<"what is the street name? ";
   cin>>this->street;
   cout<<"what is house number? ";
   cin>>this->no;
   cout<<"what is zip code? ";
   cin>>this->zip;
   cout<<"what is the city name? ";
   cin>>this->city;
}

class House
{
   private:
      int number_of_households;
      household **Household;
      Address address; // remove the pointer and try without it if the code is wrong somehwere
   public:
      House(int n,Address address): number_of_households(n), address(address)
      {
         Household = new household*[number_of_households];
         for (int i = 0; i < number_of_households; i++){
            Household[i] = nullptr;
         }
      }
      ~House(){
         for (int i = 0; i < number_of_households; i++){
            if(Household[i] != nullptr ){
               Household[i]->~household();
            }
         }
         cout<<"House at address " << this << " deleted"<<endl;
         delete [] Household;

         address.~Address(); 
      }
      household* get_household(int);
      household* operator[](unsigned int);
      void set_household(household*,int);
      void print_all();
      void write_to_file(string &filename, char separator , string identifier, int num_of_houses, House* );
      void static read_from_file(string &filename, char separator , string identifier,House*& );
      void static read_first_line(ifstream &, char separator, char c, House* &);
      char static read_household(ifstream &, char separator, char c,int &index,House*&);

};


unsigned int household::household_instances = 0;


household* House::get_household(int n){ // check here if random values
   return this->Household[n];
}
household* House::operator[](unsigned int n){
   return this->Household[n];
}
void House::set_household(household* new_house, int n){
   this->Household[n] = new_house;
}
void House::print_all(){
        
        cout << "===========================================================" << endl;
        
        cout << right <<setw(ColumnWidth) << "H O U S E" << left << setw(ColumnWidth) << endl;
        
        cout << "===========================================================" << endl;
        
        
        cout << right << setw(ColumnWidth) << "(this : " << this << ")" << left << setw(ColumnWidth) << endl;
        cout << right <<  setw(ColumnWidth) << "address: " << address.get_street() << " " << address.get_no() << ", " << address.get_zip() << " " << address.get_city() << left << setw(ColumnWidth) << endl;
        cout << right << setw(ColumnWidth) << "number of households: " << number_of_households << left << setw(ColumnWidth) << endl;
        cout << right << setw(ColumnWidth) << "total number of all consumers: " << consumer::get_total_number()  << left << setw(ColumnWidth) << endl;

        cout << "===========================================================" << endl;
        
        for (int i  = 0 ; i < this->number_of_households ; i++){
            
            household* h1 = this->get_household(i);
            
            if(h1 != nullptr){
                h1->print_household(i);
            }
            
        }
        cout << "===========================================================" << endl;
}



class Immobile : public consumer
{
      private:
         float watt_standby;
         float hours;
      public:
         Immobile(Device*);
         virtual ~Immobile();
         float get_watt_standby();
         float get_hours();
         void set_watt_standby(float);
         void set_hours(float);
         float annual_hours_of_use();
         float annual_hours_of_standby();
         float virtual annual_kWh() override;
         void print(int,float) override;
         void input() override;
         virtual Device* get_a_copy() override;
         virtual string get_string_for_file(char) override;
};

Immobile::~Immobile(){
   cout << "Immobile " << this->get_description() << " at address " << this << " deleted " << endl;
}

Immobile::Immobile(Device* d = nullptr) : consumer(d){}

//getters
float Immobile::get_watt_standby(){
   return this->watt_standby;
}
float Immobile::get_hours(){
   return this->hours;
}

//setters
void Immobile::set_watt_standby(float watt_standby){
   this->watt_standby = watt_standby;
}
void Immobile::set_hours(float hours){
   this->hours = hours;
}

void Immobile::input(){
   Device::input();

   cout << "How many watts? " ;
   float watt;
   cin>>watt;
   this->set_watt(watt);

   cout<<"How many watt standby? " ;
   cin>>this->watt_standby;

   this->set_use(input_use());

   cout<<"Enter number of hours: ";
   cin>>hours;

}

Device* Immobile::get_a_copy(){
   Device* immobile_object = new Immobile();

   * immobile_object = * this;

   return new Immobile(*this);

}

string Immobile::get_string_for_file(char separator){
   string immobile_word = "Immobile";
   string for_file = immobile_word + this->get_description() + separator + to_string(this->get_hours()) + separator + use_to_string(this->get_use()) +separator+ to_string(this->get_watt()) + separator + to_string(this->get_watt_standby()) ;
   return for_file;
}


void Immobile::print(int n,float power_price){
   cout << right << setw(ColumnWidth - 2) << n << ": " << this->get_description() << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) <<"(this: " << this << ")" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "power consumption: " <<fixed<<setprecision(2)<< this->get_watt() << " W" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "power consumption standby: " <<fixed<<setprecision(2)<< this->watt_standby << " W" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual hours of use: " <<fixed<<setprecision(2)<< annual_hours_of_use() << " h" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual house of standby: " <<fixed<<setprecision(2)<< annual_hours_of_standby() << " h" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual consumption: " <<fixed<<setprecision(1)<< annual_kWh() / 1000 << " kWh" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual costs: " <<fixed<<setprecision(2)<< annual_kWh() * power_price / 1000 << " EUR" << setw(ColumnWidth) << left << endl;
}

class Mobile : public consumer
{
   private:
      float km;
   public:
      Mobile(Device*);
      virtual ~Mobile();
      float get_km();
      void set_km(float);
      void input() override;
      float annual_kWh() override;
      void print(int,float) override;
      float yearly_km_travel();
      virtual Device* get_a_copy() override;
      virtual string  get_string_for_file(char) override;
};

Mobile::Mobile(Device* r = nullptr): consumer(r){}

Mobile::~Mobile(){
   cout << "Mobile " << this->get_description() << " at address " << this << " deleted " << endl;
}

float Mobile::get_km(){
   return this->km;
}

void Mobile::set_km(float km){
   this->km = km;
}

void Mobile::input(){
   consumer::input();

   // cout << "How many watts? " ;
   // float watt;
   // cin>>watt;
   // this->set_watt(watt);

   // this->set_use(input_use());


   cout << "how many km will be driven? ";
   cin >> this->km;

}

// float Mobile::annual_kWh(){
//    float use_deci =  stod(use_to_string(this->get_use()));
//    return use_deci * this->km * this->get_watt(); // add /100 if necissary
// }
void Mobile::print(int n, float power_price){

   cout << right << setw(ColumnWidth - 2) << n << ": " << this->get_description() << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) <<"(this: " << this << ")" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "power consumption 100km: " <<fixed<<setprecision(2) << this->get_watt() / 1000  << " W" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "km driven: " << this->km <<fixed<<setprecision(2)<< " km " << use_to_string(this->get_use()) << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual consumption: " <<fixed<<setprecision(1)<< annual_kWh() / 1000  << " kWh" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual costs: " <<fixed<<setprecision(2)<< annual_kWh() * power_price / 1000 <<" EUR" << setw(ColumnWidth) << left << endl;
}

Device* Mobile::get_a_copy(){
   Device* mobile_object = new Mobile;

   * mobile_object = * this;

   return new Mobile(*this);

}

string Mobile::get_string_for_file(char separator){
   string mobile_word = "Mobile";
   string for_file = mobile_word + separator + this->get_description() + separator + to_string(km) + separator + use_to_string(this->get_use()) + separator + to_string(this->get_watt());
   return for_file;
}

float Mobile::yearly_km_travel()
{

   float hours_year;
   switch (this->get_use())
   {
   case daily:
      hours_year = this->km * 365;
      break;
   case weekly:
      hours_year = this->km * 52;
      break;
   case sa_su:
      hours_year = this->km * 104;
      break;
   case mo_fr:
      hours_year = this->km * 260;
      break;
   case once:
      hours_year = this->km;
      break;
   default:
      hours_year = 0;
      break;
   }
   return hours_year;
}

float Mobile::annual_kWh(){
   return this->get_watt() * yearly_km_travel() / 100;
}


class Producer : public Device{
   public:
      Producer(Device*);
      virtual ~Producer();
      void input() override;

};

Producer::Producer(Device* r = nullptr) : Device(r){}

Producer::~Producer(){
   cout << "Producer " << this->get_description() << " at address " << this << " deleted" << endl;
}

void Producer::input(){
   Device::input();
}

class Solar : public Producer{
   private:
      float watt_peak;
      int year;
   public:
      Solar(Device*);
      ~Solar();
      float get_watt_peak();
      int get_year();
      void set_watt_peak(float);
      void set_year(int);
      void input()override;
      float virtual annual_kWh()override;
      void virtual print(int , float)override;
      virtual Device* get_a_copy()override;
      string virtual get_string_for_file(char)override;

};

Solar::Solar(Device* r = nullptr): Producer(r) {}

Solar::~Solar(){
   cout << "Solar " << this->get_description() << " at address " << this << " deleted" << endl;
}

//getters
float Solar::get_watt_peak(){
   return this->watt_peak;
}
int Solar::get_year(){
   return this->year;
}

//setters
void Solar::set_watt_peak(float x){
   this->watt_peak = x;
}
void Solar::set_year(int x){
   this->year = x;
}

void Solar::input(){
   Producer::input();

   cout << "how many watt peak have been installed? ";
   cin >> this->watt_peak;

   cout << "in which year were the solar modules installed? " ;
   cin >> this->year;
}

float Solar::annual_kWh(){
   float total_reduced = this->watt_peak * ((2024-this->year) * 0.005);
   
   return total_reduced + ( -1* this->watt_peak);

}

void Solar::print(int x, float power_price){
   cout << right << setw(ColumnWidth - 2) << x << ": " << this->get_description() << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) <<"(this: " << this << ")" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "solar cells installed power : " <<fixed<<setprecision(2)<< this->watt_peak << " watt peak" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "age of solar cells : " <<fixed<<setprecision(2)<< 2024 - this->year << " years" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual production : " <<fixed<<setprecision(1)<< annual_kWh()  << " kWh" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual costs: " << fixed<<setprecision(2)<< annual_kWh() * power_price << " EUR" << setw(ColumnWidth) << left << endl;

}

Device* Solar::get_a_copy(){
   Device* solar_object = new Solar();

   * solar_object = * this;

   return new Solar(*this);

}

string Solar::get_string_for_file(char separator){
   string solar_word = "Solar";
   string for_file = solar_word + separator + this->get_description() + separator + to_string(this->year) + separator + to_string(this->watt_peak);
   return for_file;
}



Use Device::input_use()
{
   char choice;
   Use ref; // check this
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
   return ref;
}
void household::add_devices_to_household(Device* added_device)
{     
      if (Solar* solar_device = dynamic_cast<Solar*>(added_device))
       {
         Solar* solar_object = new Solar(*solar_device);
            solar_object->set_next(this->devices);
            this->devices = solar_object;
      } else if (Mobile* mobile_device = dynamic_cast<Mobile*>(added_device)) {
            Mobile* mobile_object = new Mobile(*mobile_device);
            mobile_object->set_next(this->devices);
            this->devices = mobile_object;
      } else if (Immobile* immobile_device = dynamic_cast<Immobile*>(added_device)) {
            Immobile* immobile_object = new Immobile(*immobile_device);
            immobile_object->set_next(this->devices);
            this->devices = immobile_object;

      }
}

float Immobile::annual_hours_of_use()
{

   float hours_year;
   switch (this->get_use())
   {
   case daily:
      hours_year = hours * 365;
      break;
   case weekly:
      hours_year = hours * 52;
      break;
   case sa_su:
      hours_year = hours * 104;
      break;
   case mo_fr:
      hours_year = hours * 260;
      break;
   case once:
      hours_year = hours;
      break;
   default:
      hours_year = 0;
      break;
   }
   return hours_year;
}

float Immobile::annual_hours_of_standby()
{
   return 8760 - annual_hours_of_use();
}

int count_devices(household* house_ptr){ // not an important function I think
   Device *length = house_ptr->get_devices();
   int list_size = 0;
   if (length != nullptr)  
   {
      while (length != nullptr)
      {
         list_size += 1;
         length = length->get_next();
      }
   }
   return list_size;
}



float Immobile::annual_kWh()
{
   return (this->get_watt() * annual_hours_of_use() + this->watt_standby * annual_hours_of_standby());
}

Device* household::move_up(Device * head, int k)
{
   Device *length = head;
   int list_size = 1;
   if (length != nullptr) // 1 3 2
   {
      while (length != nullptr)
      {
         
         list_size += 1;
         length = length->get_next();         
      }
   }

   bool isTrue = false;
   int i = 3;
   Device *follower = head;
   Device *iterator = follower->get_next();

   if (k > 1 && list_size > 1)
   {

      if (k == 2)
      {

         follower->set_next(iterator->get_next());
         iterator->set_next(follower);
         head = iterator;
         isTrue = true;
      }
      else
      {
         if (k <= list_size)
         {
            do
            {

               Device *c = iterator->get_next();
               if (i == k)
               {
                  iterator->set_next(c->get_next());
                  c->set_next(iterator);
                  follower->set_next(c);

                  isTrue = true;
               }

               if (isTrue == true)
               {
                  break;
               }
               iterator = iterator->get_next();
               follower = follower->get_next();
               i++;
            } while (i < list_size);
         }
      }
   }
   return iterator;
}


void input_city(string &city)
{
   cout << "in which city is the household located? ";
   cin >> city;
}
void household::input_integer(string word, int &integer)
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

float household::power_consumption()
{
   float x;

   if (water)
   {
      x = (avgcons_water * persons) + (avgcons_meter * meters);
   }
   else
   {
      x = (avgcons_person * persons) + (avgcons_meter * meters);
   }
   return x;
}

void input_electric_water_heating(bool &elecWater)
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

float household::power_cost(float price_kwh)
{
   float consumption = this->power_consumption();
   return consumption * price_kwh;
}

void household::input_household()
{

   input_integer("how many square metres does the household have? ", this->meters);

   input_integer("how many persons live in this household? ", this->persons);

   input_electric_water_heating(this->water);

   cout<<"what is the price for one kWh in EUR? ";
   cin >> this->power_price;

   cout<<"who is the power supplier? ";

   cin.ignore();
   getline(cin,this->power_suplier);

   this->devices = nullptr;

}

string Device::use_to_string(Use use){

   switch (use){
      case once:
      {
         return "Once";
      }break;
      case daily:
      {
         return "daily";
      }break;
      case mo_fr:
      {
         return "Monday to Friday";
      }break;
      case sa_su:
      {
         return "Saturday and Sunday";
      }break;
      default:
      {
         return "weekly";
      }break;
   }
}

Use string_to_use(string use_string){
   
   if(use_string == "Once"){
      return once;
   }else if(use_string == "daily"){
      return daily;
   }else if(use_string == "Monday to Friday"){
      return mo_fr;
   }else if(use_string == "Saturday and Sunday"){
      return sa_su;
   }else{
      return weekly;
   }
   
}

household *household::copy_devices( household *Copy)
{
//    Device *O = this->devices;
//    while(O != nullptr) {
//       Device *C = Copy->devices;
      
//       Device *C_new_head = new Device();
//       C_new_head->set_description(O->get_description());
//       C_new_head->set_watt(O->get_watt());
//       C_new_head->set_watt_standby(O->get_watt_standby());
//       C_new_head->set_use(O->get_use());
//       C_new_head->set_hours(O->get_hours());

//       C_new_head->set_next(C);
//       Copy->devices = C_new_head;

//       O = O->get_next();
// }



// Device *O = this->devices;
//    while(O != nullptr) {
//       Device *C = Copy->devices;
// C_new_head->set_next(C);
//       Copy->devices = C_new_head;

//       O = O->get_next();
// }


Device* O = this->get_devices();
        
        
        while(O != nullptr){
            
            Device* C = O->get_a_copy();
            
            Copy->add_devices_to_household(C);
            
           O = O->get_next();
            
        }
   return Copy;
}



void household::print_household(int houseNumber)
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
   Device *storing = this->get_devices();
   float annual_total_consumption = 0;

   while (storing != nullptr)
   {

      annual_total_consumption += storing -> annual_kWh() / 1000;
      storing = storing->get_next();
   }

   cout << " H O U S E H O L D  N O  " << houseNumber << "  P O W E R  C O N S U M P T I O N" << endl;
   cout << "----------------------------------------------------------------------" << endl;
   cout << right << setw(ColumnWidth) << "(this: " << this << ")" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "price for one kWh: " << this->power_price * 100 << " ct/kWh" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "power supplier: " << this->power_suplier << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "square meters: " << this->meters << " qm" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "persons: " << this->persons << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "water heated using electricity: " << water_answer << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "list of consumers  " << endl;
   cout << "----------------------------------------------------------------------" << endl;
   int i = 1;
   Device *ptr = this->devices;
   while (ptr != nullptr)
   {
      ptr-> print(i,this->power_price);
      ptr = ptr->get_next();
      i += 1;
   }

   cout << "----------------------------------------------------------------------" << endl;
   cout << right << setw(ColumnWidth) << "power consumption square meters: " <<fixed<<setprecision(1)<< this->meters * avgcons_meter << " kWh" << setw(ColumnWidth) << left << endl;
   if (this->water)
   {
      cout << right << setw(ColumnWidth) << "power consumption all persons: " <<fixed<<setprecision(1)<< this->persons * avgcons_water << " kWh" << setw(ColumnWidth) << left << endl;
   }
   else
   {
      cout << right << setw(ColumnWidth) << "power consumption all persons: " <<fixed<<setprecision(1)<< this->persons * avgcons_person << " kWh" << setw(ColumnWidth) << left << endl;
   }
   cout << right << setw(ColumnWidth) << "total annual power consumption: " <<fixed<<setprecision(1)<< power_consumption() + annual_total_consumption << " kWh" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "total annual power costs: " <<fixed<<setprecision(2)<< power_cost(this->power_price) + annual_total_consumption * power_price << " EUR" << setw(ColumnWidth) << left << endl;
}


void House::read_first_line(ifstream &in_file, char separator, char c, House* &house){

      string Identifier ="";
      while(c != separator){
             
         Identifier = Identifier + c;
         c = in_file.get();
      }

      c = in_file.get();

      int max_houses = 0;
      while(c!=EOF && c!=separator && (c!='\n')){
         
         max_houses = max_houses * 10 + (c-'0');
         c = in_file.get();

      }
      house->number_of_households = max_houses;
      
      c = in_file.get();

      string street="";
      while(c!=EOF && c!=separator && (c!='\n')){
             
         street = street + c;
         c = in_file.get();
      }
      
      c = in_file.get();
      string no="";
      while(c!=EOF && c!=separator && (c!='\n')){
             
         no = no + c;
         c = in_file.get();
      }

      c = in_file.get();
      string zip="";
      while(c!=EOF && c!=separator && (c!='\n')){
             
         zip = zip + c;
         c = in_file.get();
      }

      c = in_file.get();
      string city = "";
      while(c!=EOF && c!=separator && (c!='\n')){

         city = city + c;
         c = in_file.get();
      }

      house->address.input(street,no,zip,city);

      if(c!=EOF){
         c = in_file.get();
      }

}
char House::read_household(ifstream &in_file, char separator, char c,int &index,House* &house){
      

      while(c!=EOF && c!=separator && (c!='\n')){ //household
         c = in_file.get();
      }
      c = in_file.get();

      while(c!=EOF && c!=separator && (c!='\n')){ //index
         index = index * 10 + (c-'0');
         c = in_file.get();
      }
      


      household* h2 = new household;
      house->set_household(h2,index);


      c = in_file.get();
      string water_string = "";
      while(c!=EOF && c!=separator && (c!='\n')){//water
         water_string = water_string + c;
         c = in_file.get();
      }
      if(water_string == "true"){
         h2->set_water(true);
         water_question = "yes";
      }else{
         h2->set_water(false);
         water_question = "no";
      }
      c = in_file.get();

      int persons=0;
      while(c!=EOF && c!=separator && (c!='\n')){//persons
         persons = persons * 10 + (c-'0');
         c = in_file.get();
      }
      h2->set_persons(persons);
      c = in_file.get();

      int square_meters = 0;
      while(c!=EOF && c!=separator && (c!='\n')){ //meters
         square_meters = square_meters * 10 + (c-'0');
         c = in_file.get();
      }
      h2->set_meters(square_meters);
      c = in_file.get();

      string price_string ="";
      while(c!=EOF && c!=separator && (c!='\n')){ // power_price
         price_string = price_string + c;
         c = in_file.get();
      }
      h2->set_power_price(stod(price_string));
      c = in_file.get();

      string suplier_string = "";
      while(c!=EOF && c!=separator && (c!='\n')){ // suplier
         suplier_string = suplier_string + c;
         c = in_file.get();
      }
      h2->set_power_supplier(suplier_string);

      if(c!=EOF){
         c = in_file.get();
      }
      return c;
}


char read_Immobile(ifstream &in_file, char separator, char c, int index, household* house_ptr){
      
      
      Immobile* immobile_ptr = new Immobile;
      immobile_ptr->set_next(house_ptr->get_devices());
      house_ptr->set_devices(immobile_ptr);

      while(c!=EOF && c!=separator && (c!='\n')){// consumer
         c = in_file.get();
      }

      c = in_file.get();
      string description = "";
      while(c!=EOF && c!=separator && (c!='\n')){ //description
         description = description + c;
         c = in_file.get();
      }
      immobile_ptr ->set_description(description);

      c = in_file.get();
      string hours_string = "";
      while(c!=EOF && c!=separator && (c!='\n')){ //hours
         hours_string = hours_string + c;
         c = in_file.get();
      }
      immobile_ptr ->set_hours(stod(hours_string));
      c = in_file.get();
      string use_string = "";
      while(c!=EOF && c!=separator && (c!='\n')){//use_string
         use_string = use_string + c;
         c = in_file.get();
      }
      immobile_ptr->set_use(string_to_use(use_string));

      c = in_file.get();
      string watt_string= "" ;
      while(c!=EOF && c!=separator && (c!='\n')){ // watt
         watt_string = watt_string + c;
         c = in_file.get();
      }
      immobile_ptr->set_watt(stod(watt_string));

      c = in_file.get();
      string watt_standby_string = "" ;
      while(c!=EOF && c!=separator && (c!='\n')){ // watt_standby
         watt_standby_string = watt_standby_string + c;
         c = in_file.get();
      }
      immobile_ptr->set_watt_standby(stod(watt_standby_string));
      
      if(c!=EOF){
         c = in_file.get();
      }
      return c;
}

char read_Mobile(ifstream &in_file, char separator, char c, int index, household* house_ptr){
      
      Mobile* mobile_ptr = new Mobile;


      while(c!=EOF && c!=separator && (c!='\n')){// consumer
         c = in_file.get();
      }
      c = in_file.get();

      string description = "";
      while(c!=EOF && c!=separator && (c!='\n')){ //description
         description = description + c;
         c = in_file.get();
      }
      mobile_ptr ->set_description(description);

      c = in_file.get();

      string km_string ="";
      while(c!=EOF && c!=separator && (c!='\n')){ // km
         km_string = km_string + c;
         c = in_file.get();
      }
      mobile_ptr->set_km(stod(km_string));

      c = in_file.get();

      string use_string= "";
      while(c!=EOF && c!=separator && (c!='\n')){//use_string
         use_string = use_string + c;
         c = in_file.get();
      }
      mobile_ptr->set_use(string_to_use(use_string));

      c= in_file.get();

      string watt_string = "" ;
      while(c!=EOF && c!=separator && (c!='\n')){ // watt
         watt_string = watt_string + c;
         c = in_file.get();
      }
      mobile_ptr->set_watt(stod(watt_string));
      

      mobile_ptr->set_next(house_ptr->get_devices());
      house_ptr->set_devices(mobile_ptr);

      if(c!=EOF){
         c = in_file.get();
      }
      return c;
}

char read_Solar(ifstream &in_file, char separator, char c, int index, household* house_ptr){
   
      Solar* solar_ptr = new Solar;
      solar_ptr->set_next(house_ptr->get_devices());
      house_ptr->set_devices(solar_ptr);

      while(c!=EOF && c!=separator && (c!='\n')){// Solar
         c = in_file.get();
      }
      c = in_file.get();

      string description = "";
      while(c!=EOF && c!=separator && (c!='\n')){ //description
         description = description + c;
         c = in_file.get();
      }
      solar_ptr ->set_description(description);

      c = in_file.get();

      int year = 0;
      while(c!=EOF && c!=separator && (c!='\n')){ //year
         year = year * 10 + (c-'0');
         c = in_file.get();
      }
      solar_ptr->set_year(year);
      c = in_file.get();

      string watt_peak_string = "" ;
      while(c!=EOF && c!=separator && (c!='\n')){ // watt
         watt_peak_string = watt_peak_string + c;
         c = in_file.get();
      }
      solar_ptr->set_watt_peak(stod(watt_peak_string));
      
      if(c!=EOF){
         c = in_file.get();
      }
      return c;

}

void House::read_from_file(string &filename, char separator , string identifier, House* &house){

   ifstream in_file;
   in_file.open(filename);
   char c;


   if(in_file.is_open() == true){
      cout<<"input file " << filename <<" opened..."<< endl;

      House::read_first_line(in_file, separator, c, house);

       while(c != EOF && (c!='\n') ){
         
         int index = 0;
         c = read_household(in_file, separator , c , index, house);
         
         
         // consumer::decrement_instances();
         
         while(c != 'H' && c!= EOF && (c!='\n')){
            if(c == 'I'){
               c = read_Immobile(in_file, separator , c , index, house->get_household(index));
            } else if(c == 'M'){
               c = read_Mobile(in_file, separator, c, index,house->get_household(index));
            } else if(c=='S'){
               c = read_Solar(in_file,separator, c, index, house->get_household(index));
            }
         }


            // for(int i=0; i<list_size;i++){
            //    move_up(ptr_arr[index - 1] -> consumers, i);
            // }
   }
   
   in_file.close();
   cout << "input file " <<filename<< " closed" << endl;

   }else{cerr<<"error file " << filename <<"can't be opened"<<endl;}
}

void House::write_to_file(string &filename, char separator , string identifier, int num_of_houses,House* house){ // if error, replace this->number with num_of_houses
   
   Address adddress = house->address;
   int device_count = 1;
   ofstream outfile;
   outfile.open(filename);

   if(outfile.is_open() == true){
      
      cout<<"output file " << filename << " opened..." << endl;
      outfile << identifier<< separator << this->number_of_households << separator <<address.get_street()<< separator <<address.get_no()
                  << separator <<address.get_zip()<< separator<<address.get_city()<<endl;

      for(int i = 0; i<this->number_of_households; i++){

         
         
         if(house->get_household(i) != nullptr){
            
            household* h1 = house->get_household(i);


            outfile << "household" << separator << i+1 << separator<< (h1->get_water() ? "true" : "false")
               << separator <<h1->get_persons() << separator << h1->get_meters() 
               << separator <<h1->get_power_price() <<separator << h1->get_power_supplier() <<endl;

            Device *device_ptr = h1 ->get_devices();
            // device_count = count_devices(house->get_household(i));

            // for(int n=0; n<device_count; n++){
               
            //    outfile << "consumer" << separator << device_ptr->get_description() << separator 
            //       << device_ptr -> get_hours() << separator << use_to_string(device_ptr->get_use()) << separator <<device_ptr->get_watt() 
            //          << separator << device_ptr->get_watt_standby() <<endl;
               
            //    device_ptr = device_ptr ->get_next();
            
            // }

            while(device_ptr != nullptr){
               outfile << device_ptr->get_string_for_file(separator) << endl;
               device_ptr = device_ptr->get_next();

            }
         }
      }

   outfile.close();
   cout<<"output file " << filename << " closed" << endl;

   
   }else{cerr<<"error file\"" << filename <<"can't be opened"<<endl;}
}




int main()
{

   int n = 1;

   string elecWater;



   cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSE - CLASS VERSION" << endl;

   // input_numberOfHouses(n);


   House* house = nullptr;


   bool quit = false;
   do
   {
      cout << "q quit\nd delete house\nh house initialisation\ni input immobile consumer\nm input mobile consumer\ns input solar producer\nu move up device\np print household\na print all households\nn new household\nc copy all devices (added to already existing ones)\nr read data from file\nw write data into file\n>>";

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
         quit = true;
         break;
      }
      case 'h':
      {
         Address new_Address;
         string street,no,zip,city;
         cout<<"how many households does the house have? ";
         cin>>n;
         new_Address.input_user_address();
         house = new House(n,new_Address);

      } break;
      case 'i':
         {
            int house_number;
            cout << "number of household? ";
            cin >> house_number;
            if(house->get_household(house_number) != nullptr){
               Immobile* immobile1 = new Immobile;
               immobile1->input();

               house->get_household(house_number)->add_devices_to_household(immobile1);
            }
         }
         break;
      case 'm':
         {
            int house_number;
            cout << "number of household? ";
            cin >> house_number;
            if(house->get_household(house_number) != nullptr){
            

               Mobile* mobile1 = new Mobile;
               mobile1->input();

               house->get_household(house_number)->add_devices_to_household(mobile1);
            }

         }break;
      case 's':
         {
            int house_number;
            cout << "number of household? ";
            cin >> house_number;
            if(house->get_household(house_number) != nullptr){
            

               Solar* solar1 = new Solar;
               solar1->input();

               house->get_household(house_number)->add_devices_to_household(solar1);
            }           


         }break;
      case 'u':
         {
            int j = 0;
            cout<<"number of household? ";
            cin >> j;
            int k;
            cout << "which one? ";
            cin >> k;
            household* h1 = house->get_household(j);

            if(h1->get_devices() != nullptr){
               h1->move_up(h1->get_devices(), k);
            }
         }
         break;
      case 'p':
      {
         int house_number;
         cout << "number of household? ";
         cin >> house_number;
         
         house->get_household(house_number)->print_household( house_number);
      }
      break;

      case 'a':
      {

           
            if (house != nullptr)
            {
               isAllPrint = true;
               house->print_all();
            }
            
         
         if(isAllPrint == false){
               cout<<"house is a nullptr, please first choose h to initialise a new house or r to read from file"<<endl;
               break;
            }
            
      }
      cout<<"case a break"<< endl;
      break;
      case 'n':
      {
         int house_number;
         cout << "number of household? ";
         cin >> house_number;

         if (house->get_household(house_number) == nullptr)
         {

            household *h1 = new household;
            
            house->set_household(h1,house_number);
            h1->input_household();
            
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
         // do
         // {
            cout << "number of household from which to copy consumers? ";
            cin >> original;
            // if (original < 0 || original > n)
            // {
            //    cout << "The Number you entered is out of range, please enter a valid one";
            // }
         // } while (original < 0 || original > n);
         // do
         // {
            cout << "number of household to copy to? ";
            cin >> copy;
         //    if (copy < 0 || copy > n)
         //    {
         //       cout << "The Number you entered is out of range, please enter a valid one";
         //    }
         // } while (copy < 0 || copy > n);

         house->get_household(original)-> copy_devices( house->get_household(copy));
      
      }
      break;

      case 'w':
      {
         string file_name;
         char separator;

         cout<<"input file name: ";
         cin>> file_name;
         cout<< "input separator character: ";
         cin>> separator;
            
         house->write_to_file(file_name ,separator,"A6",n,house);
         
      }
      break;
      case 'r':
      {
         string file_name;
         char separator;

         cout<<"input file name: ";
         cin>> file_name;
         cout<< "input separator character: ";
         cin>> separator;

         // House* house_clone = new House(0,Address());
         house = new House(6,Address());

         House::read_from_file(file_name ,separator, "A6",house);

         // if(house != nullptr){
         //    delete house;
         // }
                      
         // house = house_clone;

      } break;
      
      default:
      {
         cout << "sorry wrong choice" << endl;
      }
      break;
      case 'd':
      {
         house->~House();
         house = nullptr;

      }break;
      }
   } while (quit != true);

   return 0;
}
