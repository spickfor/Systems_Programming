/* table.c: Separate Chaining Hash Table */

#include "table.h"
#include "hash.h"
#include "macros.h"

/**
 * Create Table data structure.
 * @param   capacity        Number of buckets in the hash table.
 * @return  Allocated Table structure.
 */
Table *	    table_create(size_t capacity) {
    Table* t=(Table*)malloc(sizeof(Table));
    if(t==NULL){
        return NULL;
    }

    if(capacity==0){
        t->capacity=DEFAULT_CAPACITY;
    } else {
        t->capacity=capacity;
    }
    t->size=0;
    t->buckets=(Pair*)calloc(t->capacity, sizeof(Pair));

    return t;
}

/**
 * Delete Table data structure.
 * @param   t               Table data structure.
 * @return  NULL.
 */
Table *	    table_delete(Table *t) {
    if(t==NULL){
        return NULL;
    }
    
    for(size_t bucket=0; bucket< t->capacity; bucket++){
        Pair* p=t->buckets[bucket].next;
        pair_delete(p, true);
    }

    free(t->buckets);
    free(t);
    return NULL;
}

/**
 * Insert or update Pair into Table data structure.
 * @param   m               Table data structure.
 * @param   key             Pair's key.
 * @param   value           Pair's value.
 * @param   type            Pair's value's type.
 */
void        table_insert(Table *t, const char *key, const Value value, Type type){
    uint64_t bucket=hash_from_data(key, strlen(key))%t->capacity;
    Pair* p=t->buckets[bucket].next;
    while(p!=NULL){
        if(streq(p->key, key)){
            pair_update(p, value, type);
            return;
        }
        p=p->next;
    }
    
    t->size++;
    t->buckets[bucket].next=pair_create(key, value, t->buckets[bucket].next, type);
}

/**
 * Search Table data structure by key.
 * @param   t               Table data structure.
 * @param   key             Key of the Pair to search for.
 * @return  Pointer to the Value associated with specified key (or NULL if not found).
 */
Value *     table_search(Table *t, const char *key) {
    uint64_t bucket=hash_from_data(key, strlen(key))%t->capacity;
    Pair* p=t->buckets[bucket].next;
    while (p!=NULL){
        if (streq(p->key, key)){
            return &p->value;
        }
        p=p->next;
    }
    return NULL;
}

/**
 * Remove Pair from Table data structure with specified key.
 * @param   t               Table data structure.
 * @param   key             Key of the Pair to remove.
 * return   Whether or not the removal was successful.
 */
bool        table_remove(Table *t, const char *key) {
    uint64_t bucket=hash_from_data(key, strlen(key))%t->capacity;
    Pair* prev=&t->buckets[bucket];
    Pair* curr=t->buckets[bucket].next;
    while(curr!= NULL){
        if(streq(curr->key, key)){
            prev->next=curr->next;
            pair_delete(curr, false);
            t->size--;
            return true;
        }
        prev=curr;
        curr=curr->next;
    }
    return false;
}

/**
 * Format all the entries in the Table data structure.
 * @param   m               Table data structure.
 * @param   stream          File stream to write to.
 */
void	    table_format(Table *t, FILE *stream) {
    for(size_t bucket=0; bucket<t->capacity; bucket++){
        for(Pair *p=t->buckets[bucket].next; p; p=p->next){
            pair_format(p, stream);
        }
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */

