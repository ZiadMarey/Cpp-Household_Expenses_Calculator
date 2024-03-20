/***********************************************************************
Matr.-Nr:                     3173482
Nachname/Surname:             Marey
Vorname/Given name:           Ziad
Uni-Email:                    ziad.marey@stud.uni-due.de
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

class consumer
{
   private:
      string description;
      float watt;
      float watt_standby;
      float hours;
      Use use;
      consumer *next;
      static unsigned int consumer_instances;
      
   public:
      consumer() : next(nullptr){
         consumer_instances += 1;
      }
      ~consumer(){
         cout<<"Consumer "<< this->description << " at address "<< this << " deleted"<<endl;

      }
      string get_description();
      float get_watt();
      float get_watt_standby();
      float get_hours();
      Use get_use();
      static int get_instances();
      consumer* get_next();
      void set_description(string);
      void set_watt(float);
      void set_watt_standby(float);
      void set_hours(float);
      void set_use(Use);
      void set_next(consumer*);
      static void increment_instances();
      static void decrement_instances();
      void input(string description,float watt,float watt_standby,float hours,Use use);
      void print_consumer(int,float);
      float annual_hours_of_use();
      float annual_hours_of_standby();
      float annual_kWh();
      
   
};

unsigned int consumer::consumer_instances = 0;

void consumer::input(string description,float watt,float watt_standby,float hours,Use use){
   this->description = description;
   this->watt = watt;
   this->watt_standby = watt_standby;
   this->hours = hours;
   this->use = use;
}

void consumer::print_consumer(int n,float power_price){
   cout << right << setw(ColumnWidth - 2) << n << ": " << this->description << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) <<"(this:" << this << ")" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "power consumption: " << this->watt << " W" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "power consumption standby: " << this->watt_standby << " W" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual hours of use: " << annual_hours_of_use() << " h" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual house of standby: " << annual_hours_of_standby() << " h" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual consumption: " << annual_kWh() / 1000 << " kWh" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "annual costs: " << annual_kWh() * power_price / 1000 << " EUR" << setw(ColumnWidth) << left << endl;
}

// getters
string consumer::get_description(){
   return this->description;
}
float consumer::get_watt(){
   return this->watt;
}
float consumer::get_watt_standby(){
   return this->watt_standby;
}
float consumer::get_hours(){
   return this->hours;
}
Use consumer::get_use(){
   return this->use;
}
consumer* consumer::get_next(){
   return this->next;
}
int consumer::get_instances(){
   return consumer_instances;
}
//setters
void consumer::set_description(string description){
   this->description = description;
}
void consumer::set_watt(float watt){
   this->watt = watt;
}
void consumer::set_watt_standby(float watt_standby){
   this->watt_standby = watt_standby;
}
void consumer::set_hours(float hours){
   this->hours = hours;
}
void consumer::set_use(Use use){
   this->use = use;
}
void consumer::set_next(consumer *next){
   this->next = next;
}
void consumer::increment_instances(){
   consumer_instances ++;
}
void consumer::decrement_instances(){
   consumer_instances --;
}


consumer *head = nullptr;

class household
{
   private:
      string power_suplier;
      int meters;
      int persons;
      int devices;
      bool water;
      float power_price;
      consumer *consumers;
      static unsigned int household_instances;

   public:
      household() : consumers(nullptr){
         household_instances += 1;
      }
      ~household(){
         consumer *next;
         while( this->consumers != nullptr){
            
            next = this->consumers->get_next();
            this->consumers->~consumer();
            this->consumers = next;
            
         }
         cout<< "Household at address "<< this <<" deleted"<<endl;
         
         
      }
      string get_power_supplier();
      int get_meters();
      int get_persons();
      int get_devices();
      bool get_water();
      float get_power_price();
      consumer* get_consumers();
      void set_power_supplier(string);
      void set_meters(int);
      void set_persons(int);
      void set_devices(int);
      void set_water(bool);
      void set_power_price(float);
      void set_consumers(consumer *);
      void input(string power_suplier,int meters,int persons, int devices, bool water,float power_price);
      void print();
      void add_consumer_to_household();
      household*copy_consumers(household*);
      consumer* move_up(consumer *, int);
      float power_consumption();
      void print_household(int);
      float power_cost(float);
      void input_household();

};
void household::input(string power_suplier,int meters,int persons, int devices, bool water,float power_price){
   this->power_suplier = power_suplier;
   this->meters = meters;
   this->persons = persons;
   this->devices = devices;
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
int household::get_devices(){
   return this->devices;
}
bool household::get_water(){
   return this->water;
}
float household::get_power_price(){
   return this->power_price;
}
consumer* household::get_consumers(){
   return this->consumers;
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
void household::set_devices(int devices){
   this->devices = devices;
}
void household::set_water(bool water){
   this->water= water;
}
void household::set_power_price(float power_price){
   this->power_price= power_price;
}
void household::set_consumers(consumer * consumers){
   this->consumers = consumers;
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
         Household = new household*[n];
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
      void read_from_file(string &filename, char separator , string identifier, int num_of_houses,House* );
      void read_first_line(ifstream &,string Identifier, int &max_houses, Address address, char separator, char c, House* &);
      char read_household(ifstream &, char separator, char c,int &index,House*);

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
        cout << right << setw(ColumnWidth) << "total number of all consumers: " << consumer::get_instances() - 1 << left << setw(ColumnWidth) << endl;

        cout << "===========================================================" << endl;
        
        for (int i  = 0 ; i < number_of_households - 1 ; i++){
            
            household* h1 = this->get_household(i);
            
            if(h1 != nullptr){
                h1->print_household(i);
            }
            
        }
}

Use input_use(char choice)
{
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
void household::add_consumer_to_household()
{
   consumer *consumer_ptr = new consumer;
   consumer_ptr->set_next(consumers);
   consumers = consumer_ptr;

   string description;
   cout << "what is the description of the power consumer? ";
   cin >> description;
   consumer_ptr->set_description(description);

   float watt;
   cout << "how many watt it will have? ";
   cin >> watt;
   consumer_ptr->set_watt(watt);

   float watt_standby;
   cout << "how many watt standby it will have? ";
   cin >> watt_standby;
   consumer_ptr->set_watt_standby(watt_standby);

   int choice;
   consumer_ptr->set_use(input_use(choice));

   float hours;
   cout << "how many hours it will be operating then? ";
   cin >> hours;
   consumer_ptr->set_hours(hours);
}

float consumer::annual_hours_of_use()
{

   float hours_year;
   switch (this->use)
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

float consumer::annual_hours_of_standby()
{
   return 8760 - annual_hours_of_use();
}

int count_consumers(household* house_ptr){
   consumer *length = house_ptr->get_consumers();
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



float consumer::annual_kWh()
{
   return (watt * annual_hours_of_use() + watt_standby * annual_hours_of_standby());
}

consumer* household::move_up(consumer * head, int k)
{
   consumer *length = head;
   int list_size = 0;
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
   consumer *follower = head;
   consumer *iterator = follower->get_next();

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

               consumer *c = iterator->get_next();
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

   input_float("what is the price for one kWh in EUR? ", this->power_price);

   cout<<"who is the power supplier? ";

   cin.ignore();
   getline(cin,this->power_suplier);

   this->consumers = nullptr;

}

string use_to_string(Use use){

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

household *household::copy_consumers( household *Copy)
{
   consumer *O = this->consumers;
   while(O != nullptr) {
      consumer *C = Copy->consumers;
      
      consumer *C_new_head = new consumer;
      C_new_head->set_description(O->get_description());
      C_new_head->set_watt(O->get_watt());
      C_new_head->set_watt_standby(O->get_watt_standby());
      C_new_head->set_use(O->get_use());
      C_new_head->set_hours(O->get_hours());

      C_new_head->set_next(C);
      Copy->consumers = C_new_head;

      O = O->get_next();
}
consumer *length = Copy->consumers;
   int list_size = 0;
   if (length != nullptr)
   {
      while (length != nullptr)
      {
         list_size += 1;
         length = length->get_next();
            
      }
   }
   
   // for(int i=0; i<list_size;i++){
   //    move_up(Copy -> consumers, i );
   // }
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
   consumer *storing = this->get_consumers();
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
   consumer *ptr = this->consumers;
   while (ptr != nullptr)
   {
      ptr-> print_consumer(i,this->power_price);
      ptr = ptr->get_next();
      i += 1;
   }

   cout << "----------------------------------------------------------------------" << endl;
   cout << right << setw(ColumnWidth) << "power consumption square meters: " << this->meters * avgcons_meter << " kWh" << setw(ColumnWidth) << left << endl;
   if (this->water)
   {
      cout << right << setw(ColumnWidth) << "power consumption all persons: " << this->persons * avgcons_water << " kWh" << setw(ColumnWidth) << left << endl;
   }
   else
   {
      cout << right << setw(ColumnWidth) << "power consumption all persons: " << this->persons * avgcons_person << " kWh" << setw(ColumnWidth) << left << endl;
   }
   cout << right << setw(ColumnWidth) << "total annual power consumption: " << power_consumption() + annual_total_consumption << " kWh" << setw(ColumnWidth) << left << endl;
   cout << right << setw(ColumnWidth) << "total annual power costs: " << power_cost(this->power_price) + annual_total_consumption * power_price << " EUR" << setw(ColumnWidth) << left << endl;
}


void House::read_first_line(ifstream &in_file,string Identifier, int &max_houses, Address address, char separator, char c, House* &house){

      while(c != separator){
             
         Identifier = Identifier + c;
         c = in_file.get();
      }

      c = in_file.get();

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

      address.input(street,no,zip,city);

      if(c!=EOF){
         c = in_file.get();
      }

}
char House::read_household(ifstream &in_file, char separator, char c,int &index,House *house){
      

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


char read_consumer(ifstream &in_file, char separator, char c, consumer *consumer_ptr, household* house_ptr){
      
      
      consumer_ptr = new consumer;
      consumer_ptr->set_next(house_ptr->get_consumers());
      house_ptr->set_consumers(consumer_ptr);

      while(c!=EOF && c!=separator && (c!='\n')){// consumer
         c = in_file.get();
      }

      c = in_file.get();
      string description = "";
      while(c!=EOF && c!=separator && (c!='\n')){ //description
         description = description + c;
         c = in_file.get();
      }
      consumer_ptr ->set_description(description);

      c = in_file.get();
      string hours_string = "";
      while(c!=EOF && c!=separator && (c!='\n')){ //hours
         hours_string = hours_string + c;
         c = in_file.get();
      }
      consumer_ptr ->set_hours(stod(hours_string));
      c = in_file.get();
      string use_string;
      while(c!=EOF && c!=separator && (c!='\n')){//use_string
         use_string = use_string + c;
         c = in_file.get();
      }
      consumer_ptr->set_use(string_to_use(use_string));

      c = in_file.get();
      string watt_string ;
      while(c!=EOF && c!=separator && (c!='\n')){ // watt
         watt_string = watt_string + c;
         c = in_file.get();
      }
      consumer_ptr->set_watt(stod(watt_string));

      c = in_file.get();
      string watt_standby_string ;
      while(c!=EOF && c!=separator && (c!='\n')){ // watt_standby
         watt_standby_string = watt_standby_string + c;
         c = in_file.get();
      }
      consumer_ptr->set_watt_standby(stod(watt_standby_string));
      
      if(c!=EOF){
         c = in_file.get();
      }
      return c;
}

void House::read_from_file(string &filename, char separator , string identifier, int num_of_houses,House* house){

   ifstream in_file;
   in_file.open(filename);
   char c;
   int max_houses = 0;

   if(in_file.is_open() == true){
      cout<<"input file " << filename <<" opened..."<< endl;

      read_first_line(in_file, identifier, max_houses, address, separator, c, house);

      // if(max_houses>num_of_houses){
      // cout << "file contains up to " << max_houses << ", but here only " << num_of_houses << " are supported" << endl;
      // }
       while(c != EOF){
         
         int index = 0;
         c = read_household(in_file, separator , c , index, house);
         
         consumer *cons_ptr = new consumer;
         consumer::decrement_instances();
         cons_ptr = house->get_household(index) -> get_consumers();
         while(c != 'h' && c!= EOF){
            c = read_consumer(in_file, separator , c , cons_ptr, house->get_household(index));
         }
            // consumer *length = ptr_arr[index - 1]->consumers;
            // int list_size = 0;
            // if (length != nullptr)
            // {
            //    while (length != nullptr)
            //    {
            //       list_size += 1;
            //       length = length->next;
            //    }
            // }

            // for(int i=0; i<list_size;i++){
            //    move_up(ptr_arr[index - 1] -> consumers, i);
            // }
   }
   
   in_file.close();
   cout << "input file " <<filename<< " closed" << endl;

   }else{cerr<<"error file " << filename <<"can't be opened"<<endl;}
}

void House::write_to_file(string &filename, char separator , string identifier, int num_of_houses,House* house){
   
   Address adddress = house->address;
   int consumers_count = 0;
   ofstream outfile;
   outfile.open(filename);

   if(outfile.is_open() == true){
      
      cout<<"output file " << filename << " opened..." << endl;
      outfile << identifier<< separator << num_of_houses << separator <<address.get_street()<< separator <<address.get_no()
                  << separator <<address.get_zip()<< separator<<address.get_city()<<endl;

      for(int i = 0; i<num_of_houses; i++){

         
         
         if(house->get_household(i) != nullptr){
            
            household* h1 = house->get_household(i);

            consumer *cons_ptr = h1 ->get_consumers();
            consumers_count = count_consumers(house->get_household(i));
            outfile << "household" << separator << i+1 << separator<< (h1->get_water() ? "true" : "false")
               << separator <<h1->get_persons() << separator << h1->get_meters() 
               << separator <<h1->get_power_price() <<separator << h1->get_power_supplier() <<endl;

            for(int n=0; n<consumers_count; n++){
               
               outfile << "consumer" << separator << cons_ptr->get_description() << separator 
                  << cons_ptr -> get_hours() << separator << use_to_string(cons_ptr->get_use()) << separator <<cons_ptr->get_watt() 
                     << separator << cons_ptr->get_watt_standby() <<endl;
               
               cons_ptr = cons_ptr ->get_next();
            
            }
         }
      }

   outfile.close();
   cout<<"output file " << filename << " closed" << endl;

   
   }else{cerr<<"error file\"" << filename <<"can't be opened"<<endl;}
}




int main()
{
   //float price_kwh;
   int n = 1;

   string elecWater;
   household *houseptr = new household;
   consumer *consumerptr = new consumer;

   cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSE - CLASS VERSION" << endl;

   // input_numberOfHouses(n);


   House* house = nullptr;


   bool quit = false;
   do
   {
      cout << "q quit\nd delete house\nh house initialisation\ni input power consumer\nu move up power consumer\np print household\na print all households\nn new household\nc copy all consumers (added to already existing ones)\nr read data from file\nw write data into file\n>>";

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
            household* h1 = house->get_household(house_number);
            h1->add_consumer_to_household();
         }
         break;
      case 'u':
         {
            int j = 0;
            cout<<"number of household? ";
            cin >> j;
            int k;
            cout << "which one? ";
            cin >> k;
            household* h1 = house->get_household(j);

            if(h1->get_consumers() != nullptr){
               h1->move_up(h1->get_consumers(), k);
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
               cout<<"house is a nullptr, please first choose h to initialise a new house"<<endl;
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

         house->get_household(original)-> copy_consumers( house->get_household(copy));
      
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
            
         house->write_to_file(file_name ,separator,"A5",n,house);
         
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

         house->read_from_file(file_name ,separator, "A5",n,house);

      } break;
      
      default:
      {
         cout << "sorry wrong choice" << endl;
      }
      break;
      case 'd':
      {
         house->~House();

      }break;
      }
   } while (quit != true);

   return 0;
}
