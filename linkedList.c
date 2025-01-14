#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "./modules/system_env/system_env.h"
#include "./linkedList.h"


__Node *__node_init(size_t element_size) {
    __Node *node = malloc(sizeof(__Node) + element_size);
    assert(node != NULL);
    node->next = NULL;
    node->previous = NULL;
    return node;
}

LinkedList *__linkedlist_init(size_t element_size) {
    LinkedList *list = malloc(sizeof(LinkedList));
    assert(list != NULL);
    list->head = NULL;
    list->tail = NULL;
    list->cached = NULL;
    list->length = 0;
    list->element_size = element_size;
    list->cached_index = 0;
    return list;
}

size_t LinkedList_length(void *list_ptr) {
    LinkedList **temp_list = list_ptr;
    assert((temp_list != NULL) && (*temp_list != NULL));
    return (*temp_list)->length;
}

size_t LinkedList_element_size(void *list_ptr) {
    LinkedList **temp_list = list_ptr;
    assert((temp_list != NULL) && (*temp_list != NULL));
    return (*temp_list)->element_size;
}

size_t LinkedList_cached_index(void *list_ptr) {
    LinkedList **temp_list = list_ptr;
    assert((temp_list != NULL) && (*temp_list != NULL));
    assert((*temp_list)->cached != NULL);
    return (*temp_list)->cached_index;
}

bool LinkedList_is_empty(void *list_ptr) {
    LinkedList **temp_list = list_ptr;
    assert((temp_list != NULL) && (*temp_list != NULL));
    return (*temp_list)->length == 0;
}

void __linkedlist_locate_nearest_node(void *list_ptr, size_t index, __Node **result, int *direction, size_t *result_index) {
    LinkedList **temp_list = list_ptr;
    assert(temp_list != NULL && *temp_list != NULL);
    assert(index >= 0 && index < (*temp_list)->length);
    assert((*temp_list)->head != NULL && (*temp_list)->tail != NULL);
    assert(result != NULL && direction != NULL);

    size_t distance_to_head = index;
    size_t distance_to_tail = (*temp_list)->length - 1 - index;
    if ((*temp_list)->cached == NULL) {
        if (distance_to_head <= distance_to_tail) {
            *result = (*temp_list)->head;
            if (result_index != NULL) { *result_index = 0; }
            *direction = 1;
        } else {
            *result = (*temp_list)->tail;
            if (result_index != NULL) { *result_index = (*temp_list)->length - 1; }
            *direction = -1;
        }
        return;
    }

    size_t distance_to_cached = ((*temp_list)->cached_index >= index) ? ((*temp_list)->cached_index - index) : (index - (*temp_list)->cached_index);
    if (distance_to_head <= distance_to_cached) {
        *result = (*temp_list)->head;
        if (result_index != NULL) { *result_index = 0; }
        *direction = 1;
        return;
    }
    if (distance_to_tail <= distance_to_cached) {
        *result = (*temp_list)->tail;
        if (result_index != NULL) { *result_index = (*temp_list)->length - 1; }
        *direction = -1;
        return;
    }
    *result = (*temp_list)->cached;
    if (result_index != NULL) { *result_index = (*temp_list)->cached_index; }
    *direction = index >= (*temp_list)->cached_index ? 1 : -1;
}
