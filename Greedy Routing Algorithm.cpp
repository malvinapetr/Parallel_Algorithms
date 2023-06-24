#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;
 
#define N 6 //arithmos epeksergastwn
#define num_of_packets 6 //arithmos paketwn, gia na exw one-to-one routing prepei na einai <= apo ton arithmo epeksergastwn
 
//orismos klasis paketwn, pos = arxiki thesi, dest = proorismos
class packet{
public:	
int pos;
int dest;	
 
//constructor	
packet() 	
   {this->pos=pos;
   this->dest=dest;} 	
};
 
int main(){
 
//arxikopoiisi twn paketwn me tuxaies arxikes theseis kai tuxaious proorismous	
packet packets[num_of_packets];	
vector <int> destinations;
 
//xrisi vectors gia na eksasfalistei oti o proorismos kathe paketou tha einai diaforetikos
#pragma omp parallel for
for (int i=1; i<=num_of_packets;i++)
    destinations.push_back(i);            
 
srand(time(0));	
cout<<"Initial positions: "<<endl<<endl; 
#pragma omp parallel for
for (int i=1; i<=num_of_packets;i++){
	packets[i-1].pos = i;
	//epilogi tuxaiou proorismou
	int index =  rand() % destinations.size();  
	packets[i-1].dest = destinations[index];
	//afairesi tou epilegmenou proorismou apo tin lista
	destinations.erase(destinations.begin() + index);
	//emfanisi id, thesis kai proorismou  
	cout << "I'm packet " << i << " in " << packets[i-1].pos << " for " << packets[i-1].dest <<"."<<endl; 
    }
 
//metakinisi pros ton swsto proorismo, trexei mexri na ftasoun ola ta paketa ston proorismo tous
int steps = 1;
int not_done = 1;
while(not_done != 0){
not_done=0;	
cout<<endl<<"This is step "<<steps<<":"<<endl<<endl; 
  for(int i=1; i<=num_of_packets;i++){
  	// metakinisi pros ta aristera
  	if(packets[i-1].pos > packets[i-1].dest)        
  	   packets[i-1].pos = packets[i-1].pos - 1;
  	// metakinisi pros ta deksia   
  	else if(packets[i-1].pos < packets[i-1].dest)  
  	   packets[i-1].pos = packets[i-1].pos + 1;
  	//emfanisi id, thesis kai proorismou   
  	cout << "I'm packet " << i << " in " << packets[i-1].pos << " for " << packets[i-1].dest <<"."<<endl;} 
 
  	//elegxos an exoun ftasei ola ston proorismo tous
  	for(int i=1; i<=num_of_packets;i++){
  	   if(packets[i-1].pos != packets[i-1].dest) not_done++;}
 
steps++; 
}
 
return 0;	
}
