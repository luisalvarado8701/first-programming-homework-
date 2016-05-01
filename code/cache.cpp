#include "cache.hh"

Cache::Cache(int cacheSize, int blockSize, int cacheType){
	this->tag = this->set = 0;
	this->hit_count = this->miss_count = 0;
	this->asso_level = cacheType;
	this->block_size = blockSize;
	this->cache_size = cacheSize;
	this->offset_bits = log2 (blockSize);
	//the count of "sets" will depend of the associativity and the count of "blocks"
	this->sets_num = ((cacheSize*1024)/blockSize) / cacheType;
	//here we are calculating how many "bits" that we'll need to select the "set"
	this->sets_bits = log2 (this->sets_num);
	//We will need to know the size of the "set" in bits
	this->set_size = (blockSize * cacheType);
	//This pointer will be used in the replacement policy
	fifo_index = new int[this->sets_num] ();//itinitializes the array with zeros
	iterator = new Block[(this->sets_num * cacheType)];//pointer to scroll through the "blocks"
	cout<<"cache size: "<<cache_size<<" kB -- block size: "<<block_size<<" bytes"<<endl;
	if(cacheType > 1){
		cout<<"Associative level = "<<cacheType<<"   --   offset bits = "<<offset_bits<<"   --  index bits = "<<sets_bits<<endl;
		} else {
			cout<<"Directed Mapped cache   --   offset bits = "<<offset_bits<<"   --  index bits = "<<sets_bits<<endl;
			}
	}
Cache::~Cache(void){
	delete [] iterator;
	}
void Cache::dataReq(unsigned int addr){
     //looking for the "set" from the block size and number of sets
	set=(addr/block_size) % sets_num;
	//cout<<"Set where find a block: "<<set<<endl;
	//displace the bits to obtain only the "tag"
	tag = addr >> (offset_bits + sets_bits);
	//cout<<"Tag to verify: "<<tag<<endl;
	switch(asso_level){
		case 1:
			//cout<<"direct mapped cache";
			if((iterator[set].isValid()) && (iterator[set].cmpTag(tag))){
            //if valid bit is set to 1 and the "tag" matches
				hit_count++;
				//cout<<" -- hit"<<endl;
				} else{
                    //if don't, count 1 miss and brings the "block"
					miss_count++;
					//cout<<" -- miss"<<endl;
					iterator[set].setAsValid();
					iterator[set].setTag(tag);
			}
			break;
		case 2:
			//cout<<"cache asociativa 2 vías";
			if((iterator[asso_level*set].isValid()) && (iterator[asso_level*set].cmpTag(tag))){
            //if valid bit is set to 1 and the "tag" matches
				hit_count++;
				//cout<<" -- hit"<<endl;
			//if don't, count 1 miss and brings the "block"
			} else if((iterator[(asso_level*set + 1)].isValid()) && (iterator[(asso_level*set + 1)].cmpTag(tag))){
				hit_count++;
				//cout<<" -- hit"<<endl;
			} else{
                //if we don't have any matches, we count 1 miss and brings the "block" 
				miss_count++;
				//cout<<"-- miss"<<endl;
				//brings the "block", applying the FIFO policy
				iterator[asso_level*set + fifo_index[set]].setAsValid();
				iterator[asso_level*set + fifo_index[set]].setTag(tag);
				//cout<<"fifo: "<<fifo_index[set]<<endl;
				//increase the point to indicates that a "block" is already filled
				//so we just left a "block" available within the set 
				fifo_index[set]++;
				//if the two "blocks" are already filled, the counter is reset
				//so that now it will replace the first one had entered
				if(fifo_index[set] == asso_level){fifo_index[set] = 0;}
			}
			break;
		case 4:
			if((iterator[asso_level*set].isValid()) && (iterator[asso_level*set].cmpTag(tag))){
            //if valid bit is set to 1 and the "tag" matches
				hit_count++;
				//cout<<" -- hit"<<endl;
			//if don't, I have to go to the next "block", I should looking into the all "blocks"
			} else if((iterator[(asso_level*set + 1)].isValid()) && (iterator[(asso_level*set + 1)].cmpTag(tag))){
				hit_count++;
				//cout<<" -- hit"<<endl;
			} else if((iterator[(asso_level*set + 2)].isValid()) && (iterator[(asso_level*set + 2)].cmpTag(tag))){
				hit_count++;
				//cout<<" -- hit"<<endl;
			} else if((iterator[(asso_level*set + 3)].isValid()) && (iterator[(asso_level*set + 3)].cmpTag(tag))){
				hit_count++;
				//cout<<" -- hit"<<endl;
			} else{
                //if don't, count 1 miss and brings the "block"
				miss_count++;
				//cout<<"-- miss"<<endl;
				iterator[asso_level*set + fifo_index[set]].setAsValid();
				iterator[asso_level*set + fifo_index[set]].setTag(tag);
				//cout<<"fifo: "<<fifo_index[set]<<endl;
				//increase the point to indicates that a "block" is already filled
				//so we just left a "block" available within the set
				fifo_index[set]++;
				//if the two "blocks" are already filled, the counter is reset
				//so that now it will replace the first one had entered
				if(fifo_index[set] == asso_level){fifo_index[set] = 0;}
			}
			break;
	}
}
