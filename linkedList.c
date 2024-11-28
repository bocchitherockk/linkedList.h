#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "./linkedList.h"

#include <system_env.h>


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
    list->length = 0;
    list->element_size = element_size;
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

bool LinkedList_is_empty(void *list_ptr) {
    LinkedList **temp_list = list_ptr;
    assert((temp_list != NULL) && (*temp_list != NULL));
    return (*temp_list)->length == 0;
}
