#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <linkedList.h>

// selects the numbers that are equal to the given value
int int_boolean_comparator(int a, int b) { return a == b; }
// sorts in ascending order
int int_ordering_comparator(int a, int b) { return a - b; }
// selects even numbers
bool filter(int value) { return value % 2 == 0; }
// doubles the value
void for_each(int *value) { *value *= 2; }
// adds 2 to the value
int map(int x) { return x + 2; }
// calculates the sum
int sum_reducer(int acc, int x) { return acc + x; }
// checks if the value is equal to 10
bool any_all(int value) { return value == 10; }
// sets the value to 10
void set_all_to_10(int *value) { *value = 10; }


void print_list_int(int **list_ptr) {
    printf("{\n");
    printf("    length: %zu\n", LinkedList_length(list_ptr));
    printf("    element size: %zu\n", LinkedList_element_size(list_ptr));
    printf("    is empty: %s\n", LinkedList_is_empty(list_ptr) ? "true" : "false");
    printf("    elements: ");
    size_t length = LinkedList_length(list_ptr);
    for (size_t i = 0; i < length; i++) {
        int element = LinkedList_get(list_ptr, i);
        printf("%d ", element);
    }
    printf("\n");
    printf("}\n");
}

int main(void) {
    srand(time(NULL));

    printf("initializing linkedlist list 1 ...\n");
    int* list_1 = LinkedList_init(int);
    printf("list 1 initialized\n");

    printf("list 1 : ");
    print_list_int(&list_1);

    printf("pushing 20 random numbers to list 1 ...\n");
    for (size_t i = 0; i < 20; i++) {
        LinkedList_push(&list_1, rand() % 10);
    }

    printf("20 random numbers pushed to list 1\n");
    printf("list 1 : ");
    print_list_int(&list_1);


    printf("getting the index of the first 5 in list 1 ...\n");
    size_t index = LinkedList_index(&list_1, 5, int_boolean_comparator);
    printf("index of the first 5 in list 1: %lu\n", index);

    printf("getting the count of 5s in vec1 ...\n");
    size_t count = LinkedList_count(&list_1, 5, int_boolean_comparator);
    printf("count of 5s in list 1: %lu\n", count);

    printf("inserting 100 at index 5 in list 1 ...\n");
    LinkedList_insert_at(&list_1, 5, 100);
    printf("100 inserted at index 5 in list 1\n");
    printf("list 1 : ");
    print_list_int(&list_1);

    printf("popping the last value from list 1 ...\n");
    int popped_value = LinkedList_pop(&list_1);
    printf("popped value: %d\n", popped_value);
    printf("list 1 : ");
    print_list_int(&list_1);

    printf("removing the value at index 0 from list 1 ...\n");
    int removed_value = LinkedList_remove_at(&list_1, 0);
    printf("removed value: %d\n", removed_value);
    printf("list 1 : ");
    print_list_int(&list_1);

    printf("removing the first 5 from list 1 ...\n");
    index = LinkedList_remove_value(&list_1, 5, int_boolean_comparator);
    printf("index of the removed 5: %lu\n", index);
    printf("list 1 : ");
    print_list_int(&list_1);

    printf("copying list 1 to list 2 ...\n");
    int* list_2 = LinkedList_copy(&list_1);
    printf("list 1 copied to list 2\n");
    printf("list 2 : ");
    print_list_int(&list_2);

    printf("sorting list 2 ...\n");
    LinkedList_sort(&list_2, int_ordering_comparator);
    printf("list 2 sorted\n");
    printf("list 2 : ");
    print_list_int(&list_2);

    printf("inserting 5 in its sorted position in list 2 ...\n");
    index = LinkedList_insert_sorted(&list_2, 5, int_ordering_comparator);
    printf("index of the inserted 5: %lu\n", index);
    printf("list 2 : ");
    print_list_int(&list_2);

    printf("reversing list 2 ...\n");
    LinkedList_reverse(&list_2);
    printf("list 2 reversed\n");
    printf("list 2 : ");
    print_list_int(&list_2);

    printf("filtering list 2 for even numbers and storing the result in list 3 ...\n");
    int* list_3 = LinkedList_filter(&list_2, filter);
    printf("list 2 filtered for even numbers and stored in list 3\n");
    printf("list 3 : ");
    print_list_int(&list_3);

    printf("doubling the values in list 3 ...\n");
    LinkedList_foreach(&list_3, for_each);
    printf("values in list 3 doubled\n");
    printf("list 3 : ");
    print_list_int(&list_3);

    printf("mapping list 3 by adding 2 to each value and storing the result in list 4 ...\n");
    int* list_4 = LinkedList_map(&list_3, map);
    printf("list 3 mapped by adding 2 to each value and stored in list 4\n");
    printf("list 4 : ");
    print_list_int(&list_4);

    printf("calculating the sum of list 4 ...\n");
    int sum = LinkedList_reduce(&list_4, sum_reducer, 0);
    printf("sum of list 4: %d\n", sum);

    printf("checking if any value in list 4 is equal to 10 ...\n");
    bool any = LinkedList_any(&list_4, any_all);
    printf("any value in list 4 is equal to 10: %s\n", any ? "true" : "false");

    printf("checking if all values in list 4 are equal to 10 ...\n");
    bool all = LinkedList_all(&list_4, any_all);
    printf("all values in list 4 are equal to 10: %s\n", all ? "true" : "false");

    printf("slicing list 4 from index 0 to 10 with a step of 2 and storing the result in list 5 ...\n");
    int* list_5 = LinkedList_slice(&list_4, 0, 10, 2);
    printf("list 4 sliced from index 0 to 10 with a step of 2 and stored in list 5\n");
    printf("list 5 : ");
    print_list_int(&list_5);

    printf("setting all values in list 5 to 10 ...\n");
    LinkedList_foreach(&list_5, set_all_to_10);
    printf("all values in list 5 set to 10\n");
    printf("list 5 : ");
    print_list_int(&list_5);


    printf("checking if all values in list 5 are equal to 10 ...\n");
    all = LinkedList_all(&list_5, any_all);
    printf("all values in list 5 are equal to 10: %s\n", all ? "true" : "false");

    LinkedList_destroy(&list_1);
    LinkedList_destroy(&list_2);
    LinkedList_destroy(&list_3);
    LinkedList_destroy(&list_4);
    LinkedList_destroy(&list_5);

    return 0;
}