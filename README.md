Repository created for the optional programming exercise. The assigned algorithm is Greedy Routing Algorithm on a Linear Array. The size N of the array is hard-coded (not given as input), so users will have to change its value manually in line 8 ("#define N 6"). The same goes for the number of packets. The random initialization of packets (random initial position - random final destination) is also implemented in the code. 

## Note!
This implementation is only suited for one-to-one routing, meaning that in order to run entirely correctly the number of processors should be greater or equal to the number of packets. If the number of packets is greater than the number of processors the packets will still be sorted correctly, however any potential conflicts will not be taken into consideration.
