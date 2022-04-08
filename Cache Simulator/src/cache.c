#include "cache.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "bits.h"
#include "cpu.h"
#include "lru.h"
//Harshavardhan Reddipalli
//CS 230
//Project #4
//cache Simulation
//I have written comments for each function as to how it works.

char *make_block(int block_size) {
//TODO:
//Make and initialize a block's accessed bits given the block_size.
//HINT: if it wasn't clear already, this gets put in the "accessed" field
//This function is pretty forward,it can be done in a single statement too,but
// I created a variable to hold the block size just so it looks better.
int bsize;
bsize = block_size;//I assigned bsize to block size here.
return (char*) malloc(bsize*sizeof(char));//I used the basic malloc structure here (type*)malloc(x*sizeof(type)).
}

Line *make_lines(int line_count, int block_size) {
//TODO:
//Make and initialize the lines given the line count. Then
//make and initialize the blocks.
//HINT: this will be placed in the "accessed" field of a Line
//This function basically asks us to assign the fields of the struct lines to their given values.
// I created a variable to hold the block size and the line count just so it looks better.
int lcount;
int bsize;
lcount = line_count;//I assigned lcount to line count here.
bsize = block_size;//I assigned bsize to block size here.
Line*lines = (Line*) malloc(lcount*sizeof(Line));//I used the basic malloc structure here (type*)malloc(x*sizeof(type)).
int i = 0;//This was created for the do-while loop.
do{//The beginning of a basic do-while loop.
lines[i].valid = NULL;//It is null or 0 as it isn't valid.
lines[i].tag = 0;//I assigned it to 0 as it is an unsigned integer.
lines[i].accessed = make_block(bsize);//This calls the make block function and the "accessed" field is assigned based on the block size.
lines[i].block_size = bsize;//Straighforward,just the block size.
i++;
}while(i<lcount);//This should loop until the condition,it is less than the line count is not satisfied.
return lines;
}

Set *make_sets(int set_count, int line_count, int block_size) {
//TODO:
//Make and initialize the sets given the set count. Then
//make and initialize the line and blocks.
//This function basically works as the previous one but we initialize the set struct here.
// I created a variable to hold the block size,set count and line count just so it looks better.
int scount;
int lcount;
int bsize;
scount = set_count;//I assigned scount to set count here.
lcount = line_count;//I assigned lcount to line count here.
bsize = block_size;//I assigned bsize to block size here.
Set*set = (Set*) malloc(scount*sizeof(Set));//I used the basic malloc structure here (type*)malloc(x*sizeof(type)).
int j = 0;//This was created for the do-while loop.
do{//The beginning of a basic do-while loop.
set[j].lines = make_lines(lcount,bsize);//This calls the previous function with line count and block size as arguements.
set[j].line_count = lcount;//Straighforward,just the line count.
set[j].lru_queue = 0;//Doesn't need initialization but kept it here for consistency.
j++;
}while(j<scount);//This should loop until the condition,it is less than the set count is not satisfied.
return set;
}

Cache *make_cache(int set_bits, int line_count, int block_bits) {
Cache *cache = NULL;
//TODO:
//Make and initialize the cache, sets, lines, and blocks.
//You should use the `exp2` function to determine the
//set_count and block_count from the set_bits and block_bits
//respectively (use `man exp2` from the command line).
//First we initiliaze the arguements and then we make the set.
//We can't do it the other way around as it doesn't work.
//I created a variable to hold the block bits,set bits and line count just so it looks better.
int sbits;
int lcount;
int bbits;
sbits = set_bits;//I assigned sbits to set bits here.
lcount = line_count;//I assigned lcount to line count here.
bbits = block_bits;//I assigned bbits to block bits here.
cache = (Cache*) malloc(1*sizeof(Cache));//I used the basic malloc structure here (type*)malloc(x*sizeof(type)).
(*cache).set_count = exp2(sbits);//I initilaized the set count using the exp2 function as asked.
(*cache).line_count = lcount;//Straighforward,just the line count.
(*cache).block_size = exp2(bbits);//I initilaized the block size using the exp2 function as asked.
(*cache).set_bits = sbits;//Straighforward,just the set bits,no really required by kept it for consistency.
(*cache).block_bits = bbits;//Straighforward,just the block bits,no really required by kept it for consistency.

(*cache).sets = make_sets(((*cache).set_count),(*cache).line_count,((*cache).block_size));//Here we make the set by calling the make sets function and we use our arguements we created before. 


//Create LRU queues for sets:
if (cache != NULL) {
lru_init(cache);
}
return cache;
}

void delete_block(char *accessed) { free(accessed); }

void delete_lines(Line *lines, int line_count) {
for (int i = 0; i < line_count; i++) {
delete_block(lines[i].accessed);
}
free(lines);
}

void delete_sets(Set *sets, int set_count) {
for (int i = 0; i < set_count; i++) {
delete_lines(sets[i].lines, sets[i].line_count);
}
free(sets);
}

void delete_cache(Cache *cache) {
lru_destroy(cache);
delete_sets(cache->sets, cache->set_count);
free(cache);
}

AccessResult cache_access(Cache *cache, TraceLine *trace_line) {
unsigned int s = get_set(cache, trace_line->address);
unsigned int t = get_line(cache, trace_line->address);
unsigned int b = get_byte(cache, trace_line->address);

//Get the set:
Set *set = &cache->sets[s];

//Get the line:
LRUResult result;
lru_fetch(set, t, &result);

Line *line = result.line;



//If it was a miss we will clear the accessed bits:
if (result.access != HIT) {
for (int i = 0; i < cache->block_size; i++) {

line->accessed[i] = 0;

}
}

//Then set the accessed byte to 1:
line->accessed[b] = 1;
return result.access;
}
