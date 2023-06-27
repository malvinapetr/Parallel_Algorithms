#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <vector>
#include <string>
using namespace std;
 
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

bool checkUniquePos(packet array[],int value, int N){   // elegxei tin monadikotita twn arxikwn thesewn
int count = 0;
  #pragma omp parallel for
  for (int i=1; i<=N;i++){
	if(array[i-1].pos == value)
       count++;  
	 }
	
    if(count == 1)
	   return true;
return false;	    	
}

bool checkUniqueDest(packet array[],int value, int N){   // elegxei tin monadikotita twn proorismwn
int count = 0;
  #pragma omp parallel for
  for (int i=1; i<=N;i++){
	if(array[i-1].dest == value)
       count++;  
	 }
	
    if(count == 1)
	   return true;
return false;	    	
}



int main(){

int N; //arithmos epeksergastwn
int num_of_packets; //arithmos paketwn
int choice;

cout<< "Enter number of processors (it needs to be > 0 !): ";
cin>>N;
while(N<=0){    
cin.clear();
cin.ignore(10, '\n');
cout<<"Input was invalid! Please choose again: ";
cin>> N;	
}

cin.clear();
cin.ignore(10, '\n');

cout<<"Enter number of packets to route (it needs to be > 0 and <= number of processors!): ";
cin >> num_of_packets;
while(num_of_packets <=0 || num_of_packets > N){
cin.clear();
cin.ignore(10, '\n');	
cout<<"Input was invalid! Please choose again: ";
cin>> num_of_packets;	
}

cin.clear();
cin.ignore(10, '\n');
 
cout<< "Do you want to create an instance of your own? Press 1 for yes, 2 for no: "<<endl;
cin >> choice;
while(choice != 1 && choice != 2){
cin.clear();
cin.ignore(10, '\n');	
cout<<"Input was invalid! Please choose again: ";
cin>> choice;	
} 
  
	
packet packets[num_of_packets];	

if(choice == 1){  //an epilegei nai lambanetai i eisodos tou xristi
cout<<"You have chosen to create your own instance. The values you give must be in range [1, number of processors] \nand you are not allowed to pick a starting position or a destination more than once!"<<endl;
cin.clear();
cin.ignore(10, '\n');
# pragma omp parallel for
for (int i=1; i<=num_of_packets;i++){
	cout<<"Choose starting position of packet "<<i<<":"<<endl;   // anathesi arxikis thesis se kathe paketo
	cin >> packets[i-1].pos;
	while(packets[i-1].pos < 1 || packets[i-1].pos > N || checkUniquePos(packets, packets[i-1].pos, i) == false){
	 cin.clear();
     cin.ignore(10, '\n');	
     cout<<"Input was invalid! Please choose again: ";
     cin>> packets[i-1].pos;
	 }
	 
	cin.clear();
    cin.ignore(10, '\n');
	
	cout<<"Choose destination of packet "<<i<<":"<<endl;   // anathesi proorismou se kathe paketo
	cin >> packets[i-1].dest;
	while(packets[i-1].dest < 1 || packets[i-1].dest > N || checkUniqueDest(packets, packets[i-1].dest, i) == false) {
	 cin.clear();
     cin.ignore(10, '\n');	
     cout<<"Input was invalid! Please choose again: ";
     cin>> packets[i-1].dest;
	 }

    }

}
else if(choice == 2){    // an epilegei oxi, ginetai automati paragwgi timwn

cout<<"You have chosen to run a code-generated instance!"<<endl;
//arxikopoiisi twn paketwn me tuxaies arxikes theseis kai tuxaious proorismous
vector <int> init_positions;
vector <int> destinations;
 
//xrisi vectors gia na eksasfalistei oti o proorismos kathe paketou tha einai diaforetikos
#pragma omp parallel for
for (int i=1; i<=N;i++){
	init_positions.push_back(i);
    destinations.push_back(i);}
    
//epilogi tuxaias arxikis thesis
srand(time(0)+500);	 
#pragma omp parallel for
for (int i=1; i<=num_of_packets;i++){
	int index =  rand() % init_positions.size();  
	packets[i-1].pos = init_positions[index];
	//afairesi tou epilegmenou proorismou apo tin lista
	init_positions.erase(init_positions.begin() + index);
    }
 
//epilogi tuxaiou proorismou 
srand(time(0));	 
#pragma omp parallel for
for (int i=1; i<=num_of_packets;i++){
	int index =  rand() % destinations.size();  
	packets[i-1].dest = destinations[index];
	//afairesi tou epilegmenou proorismou apo tin lista
	destinations.erase(destinations.begin() + index);
    }
}

// koinos kwdikas kai ton 2 periptwsewn:
//emfanisi id, thesis kai proorismou 
cout<<"Initial positions: "<<endl<<endl; 
#pragma omp parallel for
for (int i=1; i<=num_of_packets;i++)
	cout << "I'm packet " << i << " in " << packets[i-1].pos << " for " << packets[i-1].dest <<"."<<endl; 

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
