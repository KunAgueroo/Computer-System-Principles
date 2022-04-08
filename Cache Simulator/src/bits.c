#include "bits.h"
#include "cache.h"
//Harshavardhan Reddipalli
//CS 230
//Project #4
//cache Simulation
//I have written comments for each function as to how it works.

//|Block Address| - Remember!
//Tag|Set index|Block offset

int get_set(Cache *cache, address_type address) {
//TODO:
//Extract the set bits from a 32-bit address.
//Set bits are located between tag and block offset so we have to perform multiple shift operations to be able to get to those.
int varx;//I created a new variable to keep up with the changing value of bits.
address_type tempadd;//I created a temporary variable to hold the values of the address as it changes when we perform the operations.
varx = (*cache).block_bits;
tempadd = address >> varx;//Now right shift our address by our variable that holds the block bits.
varx = 32 - ((*cache).set_bits);//We subract it from 32 as it is a 32 bit address space.
tempadd = tempadd << varx;
return tempadd >> varx;//Now we right shift as our set bits are in between tag and the block offset and return the value.
}

int get_line(Cache *cache, address_type address) {
//TODO:
//Extract the tag bits from a 32-bit address.
//This function follows the same method but it gets easier as all we have to extract are in the far left.
int vary;//I created a new variable to keep the value of the "or" operation perfomed on the set and block bits.
vary = (*cache).set_bits | (*cache).block_bits;//We could use "+" but I changed it as the question asked to use "|"
return address >> vary;//Tag bits are on the far left of the address so we right shift it with our variable.
}

int get_byte(Cache *cache, address_type address) {
//TODO
//Extract the block offset (byte index) bits from a 32-bit address.
//This function bascially works as our first one but instead of the values being in the middle,they are on the far right.
int varz;//I created a new variable to keep the values of the address space.
address_type tempadd;//I created a temporary variable to hold the values of the address as it changes when we perform the operations.
varz = 32 - (*cache).block_bits;//We subract it from 32 as it is a 32 bit address space.
tempadd = address << varz;
return tempadd >> varz;//Now we right shift as our set bits are in between tag and the block offset and return the value.
}
