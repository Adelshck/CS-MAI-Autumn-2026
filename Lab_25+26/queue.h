#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h> 

typedef int key_type;
typedef char value_type;

typedef struct {
    key_type key;
    value_type value;
} data_type;

#define MAX_SIZE 100

typedef struct {
    data_type data[MAX_SIZE];
    int front;   
    int rear;    
    size_t size; 
} queue;

void queue_create(queue *q);
bool queue_is_empty(const queue *q);
size_t queue_size(const queue *q);
void queue_print(const queue *q);

void queue_push_back(queue *q, const data_type item);
void queue_pop_front(queue *q);

data_type queue_front(const queue *q);

#endif