#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

#ifndef BLOCKCLASS
#define BLOCKCLASS

class Block{							
private:
	unsigned int tag, valid;
public:
	Block(){tag =0; valid=0;last_used=0;}
	~Block(){};
	bool isValid() {return valid==1;}
	bool cmpTag(unsigned int dirTag) {return tag == dirTag;}
	void setAsValid() {this->valid=1;}
	void setLastUsed() {this->last_used=1;}
	void clearLastUsed() {this->last_used=0;}
	void setTag(unsigned int dirTag){ tag=dirTag;}
	};
	
#endif

#ifndef CACHECLASS
#define CACHECLASS

class Cache{
private:
	unsigned int set, tag;
	unsigned int offset_bits, sets_bits;
	int asso_level, cache_size, block_size, sets_num, set_size, hit_count, miss_count;
	int * fifo_index;
	Block * iterator;
public:
	Cache(int, int, int);
	~Cache(void);
	int getMissRate(void){return miss_count ;}
	void dataReq(unsigned int);
	};

#endif
