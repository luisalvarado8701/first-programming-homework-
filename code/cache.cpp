#include "cache.hh"

Cache::Cache(int cache_size, int block_size, int cache_type){
	cout<<"cache size: "<<cache_size<<" MB -- block size: "<<block_size<<" bytes"<<endl;
	this->tag = this->set = 0;
	this->hit_count = this->miss_count = 0;
	this->asso_level = cache_type;
	this->block_size = block_size;
	this->cache_size = cache_size;
	this->offset_bits = log2 (block_size);
	//the count of "sets" will depend of the associativity and the count of "blocks"
	this->sets_num = ((cache_size*1024)/block_size) / cache_type;
	//here we are calculating how many "bits" that we'll need to select the "set"
	this->sets_bits = log2 (this->sets_num);
	//We will need to know the size of the "set" in bits
	this->set_size = (this->block_size * cache_type);
	//This pointer will be used in the replacement policy
	fifo_index = new int[this->sets_num] ();//itinitializes the array with zeros
	iterator = new Block[(this->sets_num * cache_type)];//pointer to scroll through the "blocks"
	cout<<"Associative level = "<<cache_type<<"   --   offset bits = "<<offset_bits<<"   --  index bits = "<<sets_bits<<endl;
	}
Cache::~Cache(void){
	delete [] iterator;
	}
void Cache::dataReq(unsigned int addr){
     //looking for the "set" from the block size and number of sets
	this->set=(addr/this->block_size) % this->sets_num;
	cout<<"Set where find a block: "<<this->set<<endl;
	//displace the bits to obtain only the "tag"
	this->tag = addr >> (this->offset_bits + this->sets_bits);
	cout<<"Tag to verify: "<<tag<<endl;
	switch(this->asso_level){
		case 0:
			//cout<<"direct mapped cache";
			if((iterator[set].isValid()) && (iterator[set].cmpTag(this->tag))){
            //if valid bit is set to 1 and the "tag" matches
				this->hit_count++;
				cout<<" -- hit"<<endl;
				} else{
                    //if don't, count 1 miss and brings the "block"
					this->miss_count++;
					cout<<" -- miss"<<endl;
					iterator[set].setAsValid();
					iterator[set].setTag(this->tag);
			}
			break;
		case 2:
			//cout<<"cache asociativa 2 vías";
			if((iterator[this->asso_level*set].isValid()) && (iterator[this->asso_level*set].cmpTag(this->tag))){
            //if valid bit is set to 1 and the "tag" matches
				this->hit_count++;
				cout<<" -- hit"<<endl;
			//if don't, count 1 miss and brings the "block"
			} else if((iterator[(this->asso_level*set + 1)].isValid()) && (iterator[(this->asso_level*set + 1)].cmpTag(this->tag))){
				this->hit_count++;
				cout<<" -- hit"<<endl;
			} else{
                //if we don't have any matches, we count 1 miss and brings the "block" 
				this->miss_count++;
				cout<<"-- miss"<<endl;
				//brings the "block", applying the FIFO policy
				iterator[this->asso_level*set + this->fifo_index[this->set]].setAsValid();
				iterator[this->asso_level*set + this->fifo_index[this->set]].setTag(this->tag);
				cout<<"fifo: "<<fifo_index[this->set]<<endl;
				//increase the point to indicates that a "block" is already filled
				//so we just left a "block" available within the set 
				fifo_index[this->set]++;
				//if the two "blocks" are already filled, the counter is reset
				//so that now it will replace the first one had entered
				if(fifo_index[this->set] == this->asso_level){fifo_index[this->set] = 0;}
			}
			break;
		case 4:
			if((iterator[this->asso_level*set].isValid()) && (iterator[this->asso_level*set].cmpTag(this->tag))){
            //if valid bit is set to 1 and the "tag" matches
				this->hit_count++;
				cout<<" -- hit"<<endl;
			//if don't, I have to go to the next "block", I should looking into the all "blocks"
			} else if((iterator[(this->asso_level*set + 1)].isValid()) && (iterator[(this->asso_level*set + 1)].cmpTag(this->tag))){
				this->hit_count++;
				cout<<" -- hit"<<endl;
			} else if((iterator[(this->asso_level*set + 2)].isValid()) && (iterator[(this->asso_level*set + 2)].cmpTag(this->tag))){
				this->hit_count++;
				cout<<" -- hit"<<endl;
			} else if((iterator[(this->asso_level*set + 3)].isValid()) && (iterator[(this->asso_level*set + 3)].cmpTag(this->tag))){
				this->hit_count++;
				cout<<" -- hit"<<endl;
			} else{
                //if don't, count 1 miss and brings the "block"
				this->miss_count++;
				cout<<"-- miss"<<endl;
				iterator[this->asso_level*set + this->fifo_index[this->set]].setAsValid();
				iterator[this->asso_level*set + this->fifo_index[this->set]].setTag(this->tag);
				cout<<"fifo: "<<fifo_index[this->set]<<endl;
				//increase the point to indicates that a "block" is already filled
				//so we just left a "block" available within the set
				fifo_index[this->set]++;
				//if the two "blocks" are already filled, the counter is reset
				//so that now it will replace the first one had entered
				if(fifo_index[this->set] == this->asso_level){fifo_index[this->set] = 0;}
			}
			break;
	}
}
