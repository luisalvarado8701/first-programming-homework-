#include "cache.hh"

int main(int argc, char *argv[]){
	float access_counter = 0; //variable was used to estimate the miss-rate
	srand (time(NULL));
	if(argc != 4 || ( atoi(argv[3]) !=1 && atoi(argv[3]) != 2 && atoi(argv[3]) != 4 )){
		cout<<"\"Error: invalid arguments\" \n";
		cout<<"see README file on how to pass valid arguments\n ";
		}
	else{
	string instr; //it will contain the address string
	unsigned int addr; //it will contain the address in hexadecimal format
	Cache mycache(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
	//This "While" will be to scroll through the instructions list
	while(getline(cin,instr)){
		access_counter++;
		instr = instr.substr(0,8);
		stringstream ss;
		ss<<hex<<instr;
		ss>>addr; //now, "addr" contain the address in hexadecimal format
		mycache.dataReq(addr);
		}
	float misses = (float)mycache.getMissCount();
	float mism_rate = misses / access_counter;//calculating the miss-rate
	cout<<"Final Miss Rate: "<<mism_rate<<endl;
	return 0;
	}
}
