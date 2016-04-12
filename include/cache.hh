#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

#ifndef BLOCKCLASS
#define BLOCKCLASS

class Block{							
private:
	unsigned int tag, valid;			
public:
	Block(){tag = 0; valid = 0;}		
	~Block(){};
	bool isValid() {return valid==1;}
	bool cmpTag(unsigned int dirTag) {return tag == dirTag;}
	void setAsValid() {this->valid=1;}
	void setTag(unsigned int dirTag){ tag=dirTag;}
	};
	
#endif

#ifndef CACHECLASS
#define CACHECLASS

class Cache{
private:
	unsigned int index, tag;
	int cache_size, block_size, blocks_num, hit_count, miss_count;
	Block * iterator;
public:
	Cache(int, int);
	~Cache(void);
	int getMisses(void){return miss_count;};
	int getHits(void){return hit_count;};
	void dataReq(unsigned int);
	};

#endif
