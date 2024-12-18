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
        #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
            #if COMPILER_SUPPORTS_TYPEOF
                int element = LinkedList_get(list_ptr, i);
            #else
                int element = LinkedList_get(list_ptr, i, int);
            #endif
        #else
            int element;
            #if COMPILER_SUPPORTS_TYPEOF
                LinkedList_get(list_ptr, i, &element);
            #else
                LinkedList_get(list_ptr, i, &element, int);
            #endif
        #endif
        printf("%d ", element);
    }
    printf("\n");
    printf("}\n");
}

int main(void) {
    // srand(time(NULL));

    printf("initializing linkedlist list 1 ...\n");
    int* list_1 = LinkedList_init(int);
    printf("list 1 initialized\n");

    printf("list 1 : ");
    print_list_int(&list_1);

    printf("pushing 20 random numbers to list 1 ...\n");
    for (size_t i = 0; i < 20; i++) {
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_push(&list_1, rand() % 10);
        #else
            LinkedList_push(&list_1, rand() % 10, int);
        #endif
    }

    printf("20 random numbers pushed to list 1\n");
    printf("list 1 : ");
    print_list_int(&list_1);


    printf("getting the index of the first 5 in list 1 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            size_t index = LinkedList_index(&list_1, 5, int_boolean_comparator);
        #else
            size_t index = LinkedList_index(&list_1, 5, int_boolean_comparator, int);
        #endif
    #else
        size_t index;
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_index(&list_1, 5, int_boolean_comparator, &index);
        #else
            LinkedList_index(&list_1, 5, int_boolean_comparator, &index, int);
        #endif
    #endif

    printf("index of the first 5 in list 1: %lu\n", index);

    printf("getting the count of 5s in vec1 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            size_t count = LinkedList_count(&list_1, 5, int_boolean_comparator);
        #else
            size_t count = LinkedList_count(&list_1, 5, int_boolean_comparator, int);
        #endif
    #else
        size_t count;
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_count(&list_1, 5, int_boolean_comparator, &count);
        #else
            LinkedList_count(&list_1, 5, int_boolean_comparator, &count, int);
        #endif
    #endif



    printf("count of 5s in list 1: %lu\n", count);

    printf("inserting 100 at index 5 in list 1 ...\n");
    #if COMPILER_SUPPORTS_TYPEOF
        LinkedList_insert_at(&list_1, 5, 100);
    #else
        LinkedList_insert_at(&list_1, 5, 100, int);
    #endif
    printf("100 inserted at index 5 in list 1\n");
    printf("list 1 : ");
    print_list_int(&list_1);

    printf("popping the last value from list 1 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            int popped_value = LinkedList_pop(&list_1);
        #else
            int popped_value = LinkedList_pop(&list_1, int);
        #endif
    #else
        int popped_value;
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_pop(&list_1, &popped_value);
        #else
            LinkedList_pop(&list_1, &popped_value, int);
        #endif
    #endif
    printf("popped value: %d\n", popped_value);
    printf("list 1 : ");
    print_list_int(&list_1);

    printf("removing the value at index 0 from list 1 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            int removed_value = LinkedList_remove_at(&list_1, 0);
        #else
            int removed_value = LinkedList_remove_at(&list_1, 0, int);
        #endif
    #else
        int removed_value;
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_remove_at(&list_1, 0, &removed_value);
        #else
            LinkedList_remove_at(&list_1, 0, &removed_value, int);
        #endif
    #endif
    printf("removed value: %d\n", removed_value);
    printf("list 1 : ");
    print_list_int(&list_1);

    printf("removing the first 5 from list 1 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            index = LinkedList_remove_value(&list_1, 5, int_boolean_comparator);
        #else
            index = LinkedList_remove_value(&list_1, 5, int_boolean_comparator, int);
        #endif
    #else
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_remove_value(&list_1, 5, int_boolean_comparator, &index);
        #else
            LinkedList_remove_value(&list_1, 5, int_boolean_comparator, &index, int);
        #endif
    #endif
    printf("index of the removed 5: %lu\n", index);
    printf("list 1 : ");
    print_list_int(&list_1);

    printf("copying list 1 to list 2 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            int* list_2 = LinkedList_copy(&list_1);
        #else
            int* list_2 = LinkedList_copy(&list_1, int);
        #endif
    #else
        int* list_2;
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_copy(&list_1, &list_2);
        #else
            LinkedList_copy(&list_1, &list_2, int);
        #endif
    #endif
    printf("list 1 copied to list 2\n");
    printf("list 2 : ");
    print_list_int(&list_2);

    printf("sorting list 2 ...\n");
    #if COMPILER_SUPPORTS_TYPEOF
        LinkedList_sort(&list_2, int_ordering_comparator);
    #else
        LinkedList_sort(&list_2, int_ordering_comparator, int);
    #endif
    printf("list 2 sorted\n");
    printf("list 2 : ");
    print_list_int(&list_2);

    printf("inserting 5 in its sorted position in list 2 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            index = LinkedList_insert_sorted(&list_2, 5, int_ordering_comparator);
        #else
            index = LinkedList_insert_sorted(&list_2, 5, int_ordering_comparator, int);
        #endif
    #else
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_insert_sorted(&list_2, 5, int_ordering_comparator, &index);
        #else
            LinkedList_insert_sorted(&list_2, 5, int_ordering_comparator, &index, int);
        #endif
    #endif
    printf("index of the inserted 5: %lu\n", index);
    printf("list 2 : ");
    print_list_int(&list_2);

    printf("reversing list 2 ...\n");
    LinkedList_reverse(&list_2);
    printf("list 2 reversed\n");
    printf("list 2 : ");
    print_list_int(&list_2);

    printf("filtering list 2 for even numbers and storing the result in list 3 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            int* list_3 = LinkedList_filter(&list_2, filter);
        #else
            int* list_3 = LinkedList_filter(&list_2, filter, int);
        #endif
    #else
        int *list_3;
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_filter(&list_2, filter, &list_3);
        #else
            LinkedList_filter(&list_2, filter, &list_3, int);
        #endif
    #endif
    printf("list 2 filtered for even numbers and stored in list 3\n");
    printf("list 3 : ");
    print_list_int(&list_3);

    printf("doubling the values in list 3 ...\n");
    #if COMPILER_SUPPORTS_TYPEOF
        LinkedList_foreach(&list_3, for_each);
    #else
        LinkedList_foreach(&list_3, for_each, int);
    #endif
    printf("values in list 3 doubled\n");
    printf("list 3 : ");
    print_list_int(&list_3);

    printf("mapping list 3 by adding 2 to each value and storing the result in list 4 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            int* list_4 = LinkedList_map(&list_3, map);
        #else
            int* list_4 = LinkedList_map(&list_3, map, int);
        #endif
    #else
        int *list_4;
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_map(&list_3, map, &list_4);
        #else
            LinkedList_map(&list_3, map, &list_4, int);
        #endif
    #endif
    printf("list 3 mapped by adding 2 to each value and stored in list 4\n");
    printf("list 4 : ");
    print_list_int(&list_4);

    printf("calculating the sum of list 4 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            int sum = LinkedList_reduce(&list_4, sum_reducer, 0);
        #else
            int sum = LinkedList_reduce(&list_4, sum_reducer, 0, int);
        #endif
    #else
        int sum;
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_reduce(&list_4, sum_reducer, 0, &sum);
        #else
            LinkedList_reduce(&list_4, sum_reducer, 0, &sum, int);
        #endif
    #endif
    printf("sum of list 4: %d\n", sum);

    printf("checking if any value in list 4 is equal to 10 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            bool any = LinkedList_any(&list_4, any_all);
        #else
            bool any = LinkedList_any(&list_4, any_all, int);
        #endif
    #else
        bool any;
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_any(&list_4, any_all, &any);
        #else
            LinkedList_any(&list_4, any_all, &any, int);
        #endif
    #endif
    printf("any value in list 4 is equal to 10: %s\n", any ? "true" : "false");

    printf("checking if all values in list 4 are equal to 10 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            bool all = LinkedList_all(&list_4, any_all);
        #else
            bool all = LinkedList_all(&list_4, any_all, int);
        #endif
    #else
        bool all;
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_all(&list_4, any_all, &all);
        #else
            LinkedList_all(&list_4, any_all, &all, int);
        #endif
    #endif
    printf("all values in list 4 are equal to 10: %s\n", all ? "true" : "false");

    printf("slicing list 4 from index 0 to 10 with a step of 2 and storing the result in list 5 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            int* list_5 = LinkedList_slice(&list_4, 0, 10, 2);
        #else
            int* list_5 = LinkedList_slice(&list_4, 0, 10, 2, int);
        #endif
    #else
        int *list_5;
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_slice(&list_4, 0, 10, 2, &list_5);
        #else
            LinkedList_slice(&list_4, 0, 10, 2, &list_5, int);
        #endif
    #endif
    printf("list 4 sliced from index 0 to 10 with a step of 2 and stored in list 5\n");
    printf("list 5 : ");
    print_list_int(&list_5);

    printf("setting all values in list 5 to 10 ...\n");
    #if COMPILER_SUPPORTS_TYPEOF
        LinkedList_foreach(&list_5, set_all_to_10);
    #else
        LinkedList_foreach(&list_5, set_all_to_10, int);
    #endif
    printf("all values in list 5 set to 10\n");
    printf("list 5 : ");
    print_list_int(&list_5);


    printf("checking if all values in list 5 are equal to 10 ...\n");
    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
            all = LinkedList_all(&list_5, any_all);
        #else
            all = LinkedList_all(&list_5, any_all, int);
        #endif
    #else
        #if COMPILER_SUPPORTS_TYPEOF
            LinkedList_all(&list_5, any_all, &all);
        #else
            LinkedList_all(&list_5, any_all, &all, int);
        #endif
    #endif
    printf("all values in list 5 are equal to 10: %s\n", all ? "true" : "false");

    LinkedList_destroy(&list_1);
    LinkedList_destroy(&list_2);
    LinkedList_destroy(&list_3);
    LinkedList_destroy(&list_4);
    LinkedList_destroy(&list_5);

    return 0;
}

    #if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
        #if COMPILER_SUPPORTS_TYPEOF
        #else
        #endif
    #else
        #if COMPILER_SUPPORTS_TYPEOF
        #else
        #endif
    #endif