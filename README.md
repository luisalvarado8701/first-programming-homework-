# first-programming-homework-
1- To compile the source code and make the executable, go to ./source and do 'make' from the terminal

      make
      
2- To run the program, execute the following command from the terminal:

      zcat memory-trace-gcc.trace.gz | head -n 10000 | ./main <cahce size> <block size> <associative level>

	where:
      
		<cache size> = Is the cache size in KB (example: 32, 64, 128)
		<block size> = Is block size in bits (example 16, 32)
		<associative level> = 	1 : directed mapped
								2 : two-way set associative
								4 : four-way set associative
      
3- Wait for a few senconds, then the program will show the reslt for miss rate.

NOTE: The "memory-trace-gcc.trace.gz" file isn't included in this repository, so you need to add it to the directory of your cloned repository.
