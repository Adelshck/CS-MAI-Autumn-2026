#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void queue_create(queue *q) {
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

bool queue_is_empty(const queue *q) {
    return q->size == 0;
}

size_t queue_size(const queue *q) {
    return q->size;
}

void queue_push_back(queue *q, const data_type item) {
    if (q->size >= MAX_SIZE) {
        fprintf(stderr, "Ошибка: Очередь переполнена!\n");
        exit(EXIT_FAILURE);
    }
    
    q->data[q->rear] = item;
    
    q->rear = (q->rear + 1) % MAX_SIZE;
    
    q->size++;
}

void queue_pop_front(queue *q) {
    if (queue_is_empty(q)) {
        fprintf(stderr, "Ошибка: Попытка удалить элемент из пустой очереди!\n");
        exit(EXIT_FAILURE);
    }
    
    q->front = (q->front + 1) % MAX_SIZE;
    
    q->size--;
}

data_type queue_front(const queue *q) {
    if (queue_is_empty(q)) {
        fprintf(stderr, "Error queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return q->data[q->front];
}

void queue_print(const queue *q) {
    if (queue_is_empty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    
    int current = q->front;
    for (size_t i = 0; i < q->size; i++) {
        printf("[%d: '%c'] ", q->data[current].key, q->data[current].value);
        current = (current + 1) % MAX_SIZE;
    }
    printf("\n");
}