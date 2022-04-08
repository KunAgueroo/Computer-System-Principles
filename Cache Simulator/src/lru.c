#include "lru.h"
#include <stdio.h>
#include <stdlib.h>
#include "cache.h"
//Harshavardhan Reddipalli
//CS 230
//Project #4
//cache Simulation
//I have written comments for each function as to how it works.

void lru_init_queue(Set *set) {
LRUNode *s = NULL;
LRUNode **pp = &s;  // place to chain in the next node
for (int i = 0; i < set->line_count; i++) {
Line *line = &set->lines[i];
LRUNode *node = (LRUNode *)(malloc(sizeof(LRUNode)));
node->line = line;
node->next = NULL;
(*pp) = node;
pp = &((*pp)->next);
}
set->lru_queue = s;
}

void lru_init(Cache *cache) {
Set *sets = cache->sets;
for (int i = 0; i < cache->set_count; i++) {
lru_init_queue(&sets[i]);
}
}

void lru_destroy(Cache *cache) {
Set *sets = cache->sets;
for (int i = 0; i < cache->set_count; i++) {
LRUNode *p = sets[i].lru_queue;
LRUNode *n = p;
while (p != NULL) {
p = p->next;
free(n);
n = p;
}
sets[i].lru_queue = NULL;
}
}

void lru_fetch(Set *set, unsigned int tag, LRUResult *result) {
//TODO:
//Implement the LRU algorithm to determine which line in
//the cache should be accessed.
//In this function you use the method of the least recently used implementation to fetch your values.
for (LRUNode **prevp = &(set->lru_queue);(*prevp) != NULL; prevp = &((*prevp)->next)) {//This part is straight from the question,so I don't need to explain much.
LRUNode *current = *prevp;//You need to declare current here.
Line* line = (*current).line;//You need to declare line here.
if((*line).valid == 1 && tag == (*line).tag){//Here you check if it is valid and if the tag is the same.
(*result).access = HIT;//If it does,we set the result access to HIT.
} 
else if((*line).valid == 0){//Here you check if the line isn't valid.
(*line).valid = 1; //Setting valid to 1.
(*line).tag = tag;//Setting tag to tag.
(*result).access = COLD_MISS;//Here we set the result access to COLD MISS.
}  
else if((*current).next == NULL){//Here you check if it's the last line but seeing if the next is NULL.
(*line).tag = tag;//Setting tag to tag.
(*result).access = CONFLICT_MISS;//Here we set the result access to CONFLICT MISS.
}
else{
continue;//Just continue on with the next element.
}
(*prevp) = (*current).next;//Here we unchain the current from the list.
(*current).next = (*set).lru_queue;
(*set).lru_queue = current;//Place current at the front.
(*result).line = line;//Here we set the result line to line.
return;
}
}

