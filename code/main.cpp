#include "cache.hh"

int main(int argc, char *argv[]){
	float access_counter = 0; //variable usada para calcular el miss rate
	srand (time(NULL));
	if(argc != 4 || atoi(argv[3])>4 || atoi(argv[3])<0 ){
		cout<<"\"Error: invalid arguments\" \n";
		cout<<"see README file on how to pass valid arguments ";
		}
	else{
	string instr; //contendrá el string de la dirección
	unsigned int addr; //contendrá la dirección en hexadecimal
	Cache mycache(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
	//Este while recorre la cantidad de instrucciones que se pasa por command line
	while(getline(cin,instr)){
		access_counter++;
		instr = instr.substr(0,8);
		stringstream ss;
		ss<<hex<<instr;
		ss>>addr; //ahora addr contiene la dirección en hexadecimal
		mycache.dataReq(addr);
		}
	float misses = (float)mycache.getMissCount();
	float mism_rate = misses / access_counter;//se calcula el miss rate
	cout<<"Final Miss Rate: "<<mism_rate<<endl;
	return 0;
	}
}
