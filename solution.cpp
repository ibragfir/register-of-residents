#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#endif /* __PROGTEST__ */

struct Node{
   //bool is_orig;
   char* m_date;
   char* m_street;
   char* m_city;
   Node* next;
   Node(){next=NULL;m_date=NULL;m_street=NULL;m_city=NULL;}//is_orig=1;}
   Node(const char* date,const char* street,const char* city){
      m_date=new char[strlen(date)+1];strcpy(m_date,date);
      m_street=new char[strlen(street)+1];strcpy(m_street,street);
      m_city=new char[strlen(city)+1];strcpy(m_city,city);
      next=NULL;
   }
   ~Node(){
      //cout<<"~node\n";
      //if(is_orig){
         delete [] m_date;
         delete [] m_street;
         delete [] m_city;
         //is_orig=0;
      //}
   }
};

struct Data{
   //bool  is_orig;
   char* id;
   char* name;
   char* surname;
   char* date;
   char* street;
   char* city;
   Node* replace;
   Data(){id=NULL;name=NULL;surname=NULL;date=NULL;street=NULL;city=NULL;replace=NULL;}//is_orig=1;}
   Data(const char* nid,const char* nname,const char* nsurname,const char* ndate,const char* nstreet,const char* ncity){
      id=new char[strlen(nid)+1];strcpy(id,nid);
      name=new char[strlen(nname)+1];strcpy(name,nname);
      surname=new char[strlen(nsurname)+1];strcpy(surname,nsurname);
      date=new char[strlen(ndate)+1];strcpy(date,ndate);
      street=new char[strlen(nstreet)+1];strcpy(street,nstreet);
      city=new char[strlen(ncity)+1];strcpy(city,ncity);
      replace=NULL;
   }
   
   ~Data(){
      //cout<<"~data\n";
      //if(is_orig){
         delete [] id;
         delete [] name;
         delete [] surname;
         delete [] date;
         delete [] street;
         delete [] city;
         //is_orig=0;
      //}
      Node* tmp;
      Node* rep;
      rep=replace;
      while(rep){
         //cout<<"while replace\n";
         tmp=rep;
         rep=rep->next;
         delete tmp;
      }
      rep=NULL;
      //delete replace;
   }
};
      

class CRegister{
   bool is_orig;
   int flag;
   int max;
   int amount;
   Data** base;
public:
   void deep_copy(){
      is_orig=1;
      Data** tmp;
      Node* src;
      Node* curr;
      Node* head;
      tmp=base;
      base=new Data* [max];
      for(int i=0;i<amount;i++){
         //tmp=base[i];
         base[i]=new Data;
         base[i]->id=new char[strlen(tmp[i]->id)+1];strcpy(base[i]->id,tmp[i]->id);
         base[i]->name=new char[strlen(tmp[i]->name)+1];strcpy(base[i]->name,tmp[i]->name);
         base[i]->surname=new char[strlen(tmp[i]->surname)+1];strcpy(base[i]->surname,tmp[i]->surname);
         base[i]->date=new char[strlen(tmp[i]->date)+1];strcpy(base[i]->date,tmp[i]->date);
         base[i]->street=new char[strlen(tmp[i]->street)+1];strcpy(base[i]->street,tmp[i]->street);
         base[i]->city=new char[strlen(tmp[i]->city)+1];strcpy(base[i]->city,tmp[i]->city);
         src=tmp[i]->replace;
         head=base[i]->replace;
         if(src){
            curr=new Node(src->m_date,src->m_street,src->m_city);
            curr->next=head;
            head=curr;
            src=src->next;
         }
         while(src){
            curr->next=new Node(src->m_date,src->m_street,src->m_city);         
            curr=curr->next;
            src=src->next;
         }
         base[i]->replace=head;
      }
   }
   void operator=(const CRegister&);
   bool add_node(int index,const char* date,const char* street,const char* city){
      Node* head;
      Node* curr;
      Node* end;
      Node* tmp;
      Node* prev;
      int  stat=0;
      head=base[index]->replace;
      while (head){
         if(strcmp(head->m_date,date)==0)
            return false;
         if(!head->next)
            end=head;
         head=head->next;
      }
      if(base[index]->replace){
         //cout<<"FUCK\n";
         head=base[index]->replace;
         prev=head;
         stat=0;
         while(head){
            //cout<<"add_while\n";
            if(strcmp(head->m_date,date)>0){
               //cout<<">>>>>>>>>\n";
               //cout<<head->m_date<<" >> "<<date<<endl;
               curr=new Node(date,street,city);
               //curr->is_orig=1;
               tmp=head;
               if(!stat){
                  //cout<<endl<<endl<<"date= "<<date<<endl;
                  base[index]->replace=curr;
                  curr->next=tmp;
                  return true;
               }
               prev->next=curr;
               //cout<<"prev= "<<prev->m_date<<endl;
               curr->next=tmp;
               stat++;
               return true;
            }
            stat++;
            prev=head;
            head=head->next;
         }
      }
      curr=new Node(date,street,city);
      //curr->is_orig=1;
      curr->next=NULL;
      //base[index]->replace=curr;
      if(!base[index]->replace){
         base[index]->replace=curr;
         //cout<<"first\n";
      }
      else
         end->next=curr;

      return true;
   }
   int find(const char* id){
      if(amount==0)
         return 0;
      int low=0;
      int high=amount-1;
      int mid;
      while(low<=high){
         mid=(low+high)/2;
         if(strcmp(id,base[mid]->id)==0)
            return -1;
         else if(strcmp(id,base[mid]->id)>0)
            low=mid+1;
         else
            high=mid-1;
      }
      for(int i=amount;i>low;i--)
         base[i]=base[i-1];
      base[low]=NULL;
      return low;
   }
   int is_here(const char* id)const{
      int low=0;
      int high=amount-1;
      int mid;
      while(low<=high){
         mid=(low+high)/2;
         if(strcmp(id,base[mid]->id)==0)
            return mid;
         else if(strcmp(id,base[mid]->id)>0)
            low=mid+1;
         else
            high=mid-1;
      }
      return -1;
   }
   CRegister(){
      flag=0;
      max=2;//--------------------------------------------------------------------------------------------------- DEFAULT CONSTRUCTOR
      amount=0;
      base=NULL;
      is_orig=1;
   }            
   CRegister(const CRegister& b){
      base=b.base;
      is_orig=0;
      max=b.max;
      flag=b.flag;
      amount=b.amount; 
   }  
   ~CRegister(){
      //cout<<"~register\n";
      if(is_orig){
         cout<<"destructing\n";
         for(int i=0;i<amount;i++)
            delete base[i];
         delete [] base;
      }
   }
   bool 			Add( const char* id,const char* name,const char* surname,const char* date,const char* street,const char* city);
   bool        Resettle( const char* id,const char* date,const char* street,const char* city );
   bool        Print   (ostream& os, const char* id )const;
};
void CRegister::operator=(const CRegister& b){
   if(is_orig){
      //cout<<"destructing\n";
      for(int i=0;i<amount;i++)
         delete base[i];
      delete [] base;   
   }
   base=b.base;
   is_orig=0;
   max=b.max;
   flag=b.flag;
   amount=b.amount; 
}
bool CRegister::Add(const char* id,const char* name,const char* surname,const char* date,const char* street,const char* city){
   if(!flag){
      base=new Data* [max];
      flag=1;
   }
   if(amount==max-1){
      Data** tmp;
      tmp = new Data* [max];
      for(int i=0;i<amount;i++)
         tmp[i] = base[i];
      delete [] base;
      max*=2.5;
      base = new Data* [max];
      for(int i=0;i<amount;i++)
         base[i] = tmp[i];  
      delete [] tmp; 
   }
   int index;
   if(is_orig==false){
      cout<<"deep_copy will run\n";
      deep_copy();
   }
   index=find(id);
   if(index<0)
      return false;
   base[index]=new Data(id,name,surname,date,street,city);
   //base[index]->is_orig=1;
   amount++;
   return true;
}
bool CRegister::Resettle(const char* id,const char* date,const char* street,const char* city){
   if(amount==0)
      return false;
   if(!is_orig){
      deep_copy();
      cout<<"deep_copy will run\n";
   }
   int index=is_here(id);
   if(index<0){
      //cout<<"is_here -1\n";
      return false;
   }
   if(strcmp(base[index]->date,date)==0)
      return false;
   if(!add_node(index,date,street,city)){
      //cout<<"!add_node\n";
      return false;
   }
   return true;
}
bool CRegister::Print(ostream& os,const char* id )const{
   if(amount==0)
      return false;
   int index=is_here(id);
   if (index<0)
      return false;
   int stat=0;
   os<<base[index]->id<<' '<<base[index]->name<<' '<<base[index]->surname<<endl;
   Node* head;
   head=base[index]->replace;
   while(head){
      if(!stat){
         if(strcmp(base[index]->date,head->m_date)<0){
            os<<base[index]->date<<' '<<base[index]->street<<' '<<base[index]->city<<endl;
            stat++;
            continue;
         }
      }
      os<<head->m_date<<' '<<head->m_street<<" "<<head->m_city<<endl;
      head=head->next;
   }
   if(!stat)
      os<<base[index]->date<<' '<<base[index]->street<<' '<<base[index]->city<<endl;  
   return true;
}
#ifndef __PROGTEST__

int main(){
   CRegister  a;
   bool status;
   char   lID[12], lDate[12], lName[50], lSurname[50], lStreet[50], lCity[50];
   cout<<"-------------------------------------------------------------------\n";
   a.Add ( "123456/7890", "John", "Smith", "2000-01-01", "Main street", "Seattle" );
   a.Add ( "987654/3210", "Freddy", "Kruger", "2001-02-03", "Elm street", "Sacramento" );
   a.Resettle ( "123456/7890", "2003-05-12", "Elm street", "Atlanta" );
   a.Resettle ( "123456/7890", "2002-12-05", "Sunset boulevard", "Los Angeles" );
   a.Print ( cout, "123456/7890" );
   cout<<"-------------------------------------------------------------------\n";
   CRegister b(a);
   a.Print ( cout, "987654/3210" );
   cout<<"-------------------------------------------------------------------\n";
   b.Resettle ( "987654/3210", "2008-04-12", "Elm street", "Cinccinati" );
   a.Resettle ( "987654/3210", "2007-02-11", "Elm street", "Indianapolis" );
   a.Print ( cout, "987654/3210" );
   cout<<"-------------------------------------------------------------------\n";
   b.Print ( cout, "987654/3210" );
   cout<<"-------------------------------------------------------------------\n";
   a=b;
   a . Resettle ( "987654/3210", "2011-05-05", "Elm street", "Salt Lake City" );
   a . Print ( cout, "987654/3210" );
   cout<<"-------------------------------------------------------------------\n";
   b . Print ( cout, "987654/3210" );
   cout<<"-------------------------------------------------------------------\n";
   status = b . Add ( "987654/3210", "Joe", "Lee", "2010-03-17", "Abbey road", "London" );
   cout<<"false "<<status<<endl;
   status = a . Resettle ( "987654/3210", "2001-02-03", "Second street", "Milwaukee" );
   cout<<"false "<<status<<endl;
   status = a . Print ( cout, "666666/6666" );
   cout<<"false "<<status<<endl;
   cout<<"-------------------------------------------------------------------\n";
   CRegister  c;
   strncpy ( lID, "123456/7890", sizeof ( lID ) );
   strncpy ( lName, "John", sizeof ( lName ) );
   strncpy ( lSurname, "Smith", sizeof ( lSurname ) );
   strncpy ( lDate, "2000-01-01", sizeof ( lDate) );
   strncpy ( lStreet, "Main street", sizeof ( lStreet ) );
   strncpy ( lCity, "Seattle", sizeof ( lCity ) );
   status = c . Add ( lID, lName, lSurname, lDate, lStreet, lCity );
   cout<<"true "<<status<<endl;
   strncpy ( lID, "987654/3210", sizeof ( lID ) );
   strncpy ( lName, "Freddy", sizeof ( lName ) );
   strncpy ( lSurname, "Kruger", sizeof ( lSurname ) );
   strncpy ( lDate, "2001-02-03", sizeof ( lDate) );
   strncpy ( lStreet, "Elm street", sizeof ( lStreet ) );
   strncpy ( lCity, "Sacramento", sizeof ( lCity ) );
   status = c . Add ( lID, lName, lSurname, lDate, lStreet, lCity );
   cout<<"true "<<status<<endl;
   strncpy ( lID, "123456/7890", sizeof ( lID ) );
   strncpy ( lDate, "2003-05-12", sizeof ( lDate) );
   strncpy ( lStreet, "Elm street", sizeof ( lStreet ) );
   strncpy ( lCity, "Atlanta", sizeof ( lCity ) );
   status = c . Resettle ( lID, lDate, lStreet, lCity );
   cout<<"true "<<status<<endl;
   strncpy ( lID, "123456/7890", sizeof ( lID ) );
   strncpy ( lDate, "2002-12-05", sizeof ( lDate) );
   strncpy ( lStreet, "Sunset boulevard", sizeof ( lStreet ) );
   strncpy ( lCity, "Los Angeles", sizeof ( lCity ) );
   status = c . Resettle ( lID, lDate, lStreet, lCity );
   cout<<"true "<<status<<endl;
   status = c . Print ( cout, "123456/7890" );
   cout<<"-------------------------------------------------------------------\n";
}
#endif /* __PROGTEST__ */
