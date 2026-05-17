#include <stdio.h>
#include "queue.h"

bool bubble_pass_recursive(queue *q, size_t elements_left, data_type current_item, bool swapped) {
    if (elements_left == 1) {
        queue_push_back(q, current_item);
        return swapped;
    }

    data_type next_item = queue_front(q);

    if (current_item.key > next_item.key) {
        queue_pop_front(q);
        queue_push_back(q, next_item);
        return bubble_pass_recursive(q, elements_left - 1, current_item, true);
    } else {
        queue_push_back(q, current_item);
        queue_pop_front(q);
        return bubble_pass_recursive(q, elements_left - 1, next_item, swapped);
    }
}

bool queue_bubble_pass(queue *q) {
    if (queue_size(q) < 2) return false;

    data_type first = queue_front(q);
    queue_pop_front(q);

    return bubble_pass_recursive(q, queue_size(q) + 1, first, false);
}

void queue_sort_bubble(queue *q) {
    if (queue_bubble_pass(q)) {
        queue_sort_bubble(q);
    }
}

int main() {
    queue q;
    queue_create(&q);

    data_type item1 = {45, 'A'};
    data_type item2 = {12, 'B'};
    data_type item3 = {89, 'C'};
    data_type item4 = {23, 'D'};
    data_type item5 = {7,  'E'};

    queue_push_back(&q, item1);
    queue_push_back(&q, item2);
    queue_push_back(&q, item3);
    queue_push_back(&q, item4);
    queue_push_back(&q, item5);

    printf("Start\n");
    queue_print(&q);

    queue_sort_bubble(&q);

    printf("\nSorted queue\n");
    queue_print(&q);

    return 0;
}