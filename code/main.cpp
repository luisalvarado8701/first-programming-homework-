#include "cache.hh"

int main(int argc, char *argv[]){
	srand (time(NULL));
	if(argc != 4 || atoi(argv[3])>4 || atoi(argv[3])<0 ){
		cout<<"\"Error: invalid arguments\" \n";
		cout<<"see README file on how to pass valid arguments ";
		}
	else{
	string instr;
	unsigned int addr;
	Cache mycache(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
	while(getline(cin,instr)){
		instr = instr.substr(0,8);
		cout<<"reading line --" <<instr<<endl;
		stringstream ss;
		ss<<hex<<instr;
		ss>>addr;
		cout<<"int addr: "<<addr<<endl;
		mycache.dataReq(addr);
		}
	}
	return 0;
}
