#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#if LANGUAGE_CPP // C++ support
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "./modules/system_env/system_env.h"

typedef struct __Node {
    struct __Node *next;
    struct __Node *previous;
    char element[];
} __Node;

__Node *__node_init(size_t element_size);

typedef struct LinkedList {
    __Node *head;
    __Node *tail;
    size_t length;
    size_t element_size;
} LinkedList;

/**
 * Private
 * 
 * Initializes a new list.
 * @param element_size [size_t] The size of the elements in the list.
 * @return [LinkedList *] The new list.
 */
LinkedList *__linkedlist_init(size_t element_size);

size_t LinkedList_length(void *list_ptr);

size_t LinkedList_element_size(void *list_ptr);

bool LinkedList_is_empty(void *list_ptr);

#define LinkedList_init(__T__) (__T__ *)__linkedlist_init(sizeof(__T__))

#define LinkedList_destroy(__list_ptr__) do { \
    assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
    LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
    __Node *__current_node__ = __temp_list__->head; \
    while (__current_node__ != NULL) { \
        __Node *__next_node__ = __current_node__->next; \
        free(__current_node__); \
        __current_node__ = __next_node__; \
    } \
    free(__temp_list__); \
    *(__list_ptr__) = NULL; \
} while(0)

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_get(__list_ptr__, __index__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = __temp_list__->head; \
            for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                __node__ = __node__->next; \
            } \
            *((typeof(**(__list_ptr__)) *)__node__->element); \
        })
    #else
        #define LinkedList_get(__list_ptr__, __index__,__list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = __temp_list__->head; \
            for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                __node__ = __node__->next; \
            } \
            *(((__list_element_type__) *)__node__->element); \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_get(__list_ptr__, __index__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = __temp_list__->head; \
            for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                __node__ = __node__->next; \
            } \
            *(__result_ptr__) = *((typeof(**(__list_ptr__)) *)__node__->element); \
        } while(0)
    #else
        #define LinkedList_get(__list_ptr__, __index__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = __temp_list__->head; \
            for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                __node__ = __node__->next; \
            } \
            *(__result_ptr__) = *(((__list_element_type__) *)__node__->element); \
        } while (0)
    #endif
#endif

#if COMPILER_SUPPORTS_TYPEOF
    #define LinkedList_set(__list_ptr__, __index__, __element__) do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
        assert(__temp_list__->element_size == sizeof(__element__)); \
        __Node *__node__ = __temp_list__->head; \
        for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
            __node__ = __node__->next; \
        } \
        typeof(**(__list_ptr__)) __temp_var__ = (__element__); \
        memcpy(__node__->element, &__temp_var__, sizeof(__temp_var__)); \
    } while(0)
#else
    #define LinkedList_set(__list_ptr__, __index__, __element__, __list_element_type__) do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
        assert(__temp_list__->element_size == sizeof(__element__)); \
        __Node *__node__ = __temp_list__->head; \
        for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
            __node__ = __node__->next; \
        } \
        __list_element_type__ __temp_var__ = (__element__); \
        memcpy(__node__->element, &__temp_var__, sizeof(__temp_var)); \
    } while(0)
#endif

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_index(__list_ptr__, __element__, __boolean_comparator__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __temp_list__->head; \
            bool __found__ = false; \
            size_t __i__ = 0; \
            for ( ; __i__ < __temp_list__->length; __i__++) { \
                if ((__boolean_comparator__)(*((typeof(**(__list_ptr__)) *)__node__->element), (__element__))) { \
                    __found__ = true; \
                    break; \
                } \
                __node__ = __node__->next; \
            } \
            assert(__found__); \
            __i__; \
        })
    #else
        #define LinkedList_index(__list_ptr__, __element__, __boolean_comparator__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __temp_list__->head; \
            bool __found__ = false; \
            size_t __i__ = 0; \
            for ( ; __i__ < __temp_list__->length; __i__++) { \
                if ((__boolean_comparator__)(*(((__list_element_type__) *)__node__->element), (__element__))) { \
                    __found__ = true; \
                    break; \
                } \
                __node__ = __node__->next; \
            } \
            assert(__found__); \
            __i__; \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_index(__list_ptr__, __element__, __boolean_comparator__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __temp_list__->head; \
            bool __found__ = false; \
            size_t __i__ = 0; \
            for ( ; __i__ < __temp_list__->length; __i__++) { \
                if ((__boolean_comparator__)(*((typeof(**(__list_ptr__)) *)__node__->element), (__element__))) { \
                    __found__ = true; \
                    break; \
                } \
                __node__ = __node__->next; \
            } \
            assert(__found__); \
            *(__result_ptr__) = __i__; \
        } while(0)
    #else
        #define LinkedList_index(__list_ptr__, __element__, __boolean_comparator__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __temp_list__->head; \
            bool __found__ = false; \
            size_t __i__ = 0; \
            for ( ; __i__ < __temp_list__->length; __i__++) { \
                if ((__boolean_comparator__)(*(((__list_element_type__) *)__node__->element), (__element__))) { \
                    __found__ = true; \
                    break; \
                } \
                __node__ = __node__->next; \
            } \
            assert(__found__); \
            *(__result_ptr__) = __i__; \
        } while(0)
    #endif
#endif

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_count(__list_ptr__, __element__, __boolean_comparator__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __temp_list__->head; \
            size_t __count__ = 0; \
            for (size_t __i__ = 0; __i__ < __temp_list__->length; __i__++) { \
                if ((__boolean_comparator__)(*((typeof(**(__list_ptr__)) *)__node__->element), (__element__))) { \
                    __count__++; \
                } \
                __node__ = __node__->next; \
            } \
            __count__; \
        })
    #else
        #define LinkedList_count(__list_ptr__, __element__, __boolean_comparator__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __temp_list__->head; \
            size_t __count__ = 0; \
            for (size_t __i__ = 0; __i__ < __temp_list__->length; __i__++) { \
                if ((__boolean_comparator__)(*(((__list_element_type__) *)__node__->element), (__element__))) { \
                    __count__++; \
                } \
                __node__ = __node__->next; \
            } \
            __count__; \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_count(__list_ptr__, __element__, __boolean_comparator__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __temp_list__->head; \
            size_t __count__ = 0; \
            for (size_t __i__ = 0; __i__ < __temp_list__->length; __i__++) { \
                if ((__boolean_comparator__)(*((typeof(**(__list_ptr__)) *)__node__->element), (__element__))) { \
                    __count__++; \
                } \
                __node__ = __node__->next; \
            } \
            *(__result_ptr__) = __count__; \
        } while(0)
    #else
        #define LinkedList_count(__list_ptr__, __element__, __boolean_comparator__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __temp_list__->head; \
            size_t __count__ = 0; \
            for (size_t __i__ = 0; __i__ < __temp_list__->length; __i__++) { \
                if ((__boolean_comparator__)(*(((__list_element_type__) *)__node__->element), (__element__))) { \
                    __count__++; \
                } \
                __node__ = __node__->next; \
            } \
            *(__result_ptr__) = __count__; \
        } while(0)
    #endif
#endif

#if COMPILER_SUPPORTS_TYPEOF
    #define LinkedList_push(__list_ptr__, __element__) do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        assert(__temp_list__->element_size == sizeof(__element__)); \
        __Node *__node__ = __node_init(__temp_list__->element_size); \
        __node__->previous = __temp_list__->tail; \
        typeof(**(__list_ptr__)) __temp_var__ = (__element__); \
        memcpy(__node__->element, &__temp_var__, sizeof(__temp_var__)); \
        if (__temp_list__->head == NULL) { \
            __temp_list__->head = __node__; \
        } else { \
            __temp_list__->tail->next = __node__; \
        } \
        __temp_list__->tail = __node__; \
        __temp_list__->length++; \
    } while(0)
#else
    #define LinkedList_push(__list_ptr__, __element__, __list_element_type__) do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        assert(__temp_list__->element_size == sizeof(__element__)); \
        __Node *__node__ = __node_init(__temp_list__->element_size); \
        __node__->previous = __temp_list__->tail; \
        __list_element_type__ __temp_var__ = (__element__); \
        memcpy(__node__->element, &__temp_var__, sizeof(__temp_var)); \
        if (__temp_list__->head == NULL) { \
            __temp_list__->head = __node__; \
        } else { \
            __temp_list__->tail->next = __node__; \
        } \
        __temp_list__->tail = __node__; \
        __temp_list__->length++; \
    } while(0)
#endif

// TODO: improve complexity by checking if index is closer to head or tail
#if COMPILER_SUPPORTS_TYPEOF
    #define LinkedList_insert_at(__list_ptr__, __index__, __element__) do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        assert((__index__ >= 0) && (__index__ <= __temp_list__->length)); \
        assert(__temp_list__->element_size == sizeof(__element__)); \
        __Node *__node__ = __node_init(__temp_list__->element_size); \
        typeof(**(__list_ptr__)) __temp_var__ = (__element__); \
        memcpy(__node__->element, &__temp_var__, sizeof(__temp_var__)); \
        if (__index__ == 0) { \
            __node__->next = __temp_list__->head; \
            __temp_list__->head->previous = __node__; \
            __temp_list__->head = __node__; \
        } else if (__index__ == __temp_list__->length) { \
            __node__->previous = __temp_list__->tail; \
            __temp_list__->tail->next = __node__; \
            __temp_list__->tail = __node__; \
        } else { \
            __Node *__current_node__ = __temp_list__->head; \
            for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                __current_node__ = __current_node__->next; \
            } \
            __node__->next = __current_node__; \
            __node__->previous = __current_node__->previous; \
            __current_node__->previous->next = __node__; \
            __current_node__->previous = __node__; \
        } \
        __temp_list__->length++; \
    } while(0)
#else
    #define LinkedList_insert_at(__list_ptr__, __index__, __element__, __list_element_type__) do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        assert((__index__ >= 0) && (__index__ <= __temp_list__->length)); \
        assert(__temp_list__->element_size == sizeof(__element__)); \
        __Node *__node__ = __node_init(__temp_list__->element_size); \
        __list_element_type__ __temp_var__ = (__element__); \
        memcpy(__node__->element, &__temp_var__, sizeof(__temp_var)); \
        if (__index__ == 0) { \
            __node__->next = __temp_list__->head; \
            __temp_list__->head->previous = __node__; \
            __temp_list__->head = __node__; \
        } else if (__index__ == __temp_list__->length) { \
            __node__->previous = __temp_list__->tail; \
            __temp_list__->tail->next = __node__; \
            __temp_list__->tail = __node__; \
        } else { \
            __Node *__current_node__ = __temp_list__->head; \
            for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                __current_node__ = __current_node__->next; \
            } \
            __node__->next = __current_node__; \
            __node__->previous = __current_node__->previous; \
            __current_node__->previous->next = __node__; \
            __current_node__->previous = __node__; \
        } \
        __temp_list__->length++; \
    } while(0)
#endif

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_insert_sorted(__list_ptr__, __element__, __ordering_comparator__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __node_init(__temp_list__->element_size); \
            typeof(**(__list_ptr__)) __temp_var__ = (__element__); \
            memcpy(__node__->element, &__temp_var__, sizeof(__temp_var__)); \
            size_t __insert_index__ = 0; \
            if (__temp_list__->head == NULL) { \
                __temp_list__->head = __node__; \
                __temp_list__->tail = __node__; \
            } else { \
                __Node *__current_node__ = __temp_list__->head; \
                while (__current_node__ != NULL) { \
                    if ((__ordering_comparator__)(*((typeof(**(__list_ptr__)) *)__current_node__->element), (__element__)) >= 0) { \
                        if (__current_node__->previous != NULL) { \
                            __current_node__->previous->next = __node__; \
                            __node__->previous = __current_node__->previous; \
                        } else { \
                            __temp_list__->head = __node__; \
                        } \
                        __node__->next = __current_node__; \
                        __current_node__->previous = __node__; \
                        break; \
                    } \
                    __current_node__ = __current_node__->next; \
                    __insert_index__++; \
                } \
                if (__current_node__ == NULL) { \
                    __temp_list__->tail->next = __node__; \
                    __node__->previous = __temp_list__->tail; \
                    __temp_list__->tail = __node__; \
                } \
            } \
            __temp_list__->length++; \
            __insert_index__; \
        })
    #else
        #define LinkedList_insert_sorted(__list_ptr__, __element__, __ordering_comparator__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __node_init(__temp_list__->element_size); \
            __list_element_type__ __temp_var__ = (__element__); \
            memcpy(__node__->element, &__temp_var__, sizeof(__temp_var)); \
            size_t __insert_index__ = 0; \
            if (__temp_list__->head == NULL) { \
                __temp_list__->head = __node__; \
                __temp_list__->tail = __node__; \
            } else { \
                __Node *__current_node__ = __temp_list__->head; \
                while (__current_node__ != NULL) { \
                    if ((__ordering_comparator__)(*(((__list_element_type__) *)__current_node__->element), (__element__)) >= 0) { \
                        if (__current_node__->previous != NULL) { \
                            __current_node__->previous->next = __node__; \
                            __node__->previous = __current_node__->previous; \
                        } else { \
                            __temp_list__->head = __node__; \
                        } \
                        __node__->next = __current_node__; \
                        __current_node__->previous = __node__; \
                        break; \
                    } \
                    __current_node__ = __current_node__->next; \
                    __insert_index__++; \
                } \
                if (__current_node__ == NULL) { \
                    __temp_list__->tail->next = __node__; \
                    __node__->previous = __temp_list__->tail; \
                    __temp_list__->tail = __node__; \
                } \
            } \
            __temp_list__->length++; \
            __insert_index__; \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_insert_sorted(__list_ptr__, __element__, __ordering_comparator__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __node_init(__temp_list__->element_size); \
            typeof(**(__list_ptr__)) __temp_var__ = (__element__); \
            memcpy(__node__->element, &__temp_var__, sizeof(__temp_var)); \
            size_t __insert_index__ = 0; \
            if (__temp_list__->head == NULL) { \
                __temp_list__->head = __node__; \
                __temp_list__->tail = __node__; \
            } else { \
                __Node *__current_node__ = __temp_list__->head; \
                while (__current_node__ != NULL) { \
                    if ((__ordering_comparator__)(*((typeof(**(__list_ptr__)) *)__current_node__->element), (__element__)) >= 0) { \
                        if (__current_node__->previous != NULL) { \
                            __current_node__->previous->next = __node__; \
                            __node__->previous = __current_node__->previous; \
                        } else { \
                            __temp_list__->head = __node__; \
                        } \
                        __node__->next = __current_node__; \
                        __current_node__->previous = __node__; \
                        break; \
                    } \
                    __current_node__ = __current_node__->next; \
                    __insert_index__++; \
                } \
                if (__current_node__ == NULL) { \
                    __temp_list__->tail->next = __node__; \
                    __node__->previous = __temp_list__->tail; \
                    __temp_list__->tail = __node__; \
                } \
            } \
            __temp_list__->length++; \
            if ((__result_ptr__) != NULL) { *(__result_ptr__) = __insert_index__; } \
        } while(0)
    #else
        #define LinkedList_insert_sorted(__list_ptr__, __element__, __ordering_comparator__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __node_init(__temp_list__->element_size); \
            __list_element_type__ __temp_var__ = (__element__); \
            memcpy(__node__->element, &__temp_var__, sizeof(__temp_var)); \
            size_t __insert_index__ = 0; \
            if (__temp_list__->head == NULL) { \
                __temp_list__->head = __node__; \
                __temp_list__->tail = __node__; \
            } else { \
                __Node *__current_node__ = __temp_list__->head; \
                while (__current_node__ != NULL) { \
                    if ((__ordering_comparator__)(*(((__list_element_type__) *)__current_node__->element), (__element__)) >= 0) { \
                        if (__current_node__->previous != NULL) { \
                            __current_node__->previous->next = __node__; \
                            __node__->previous = __current_node__->previous; \
                        } else { \
                            __temp_list__->head = __node__; \
                        } \
                        __node__->next = __current_node__; \
                        __current_node__->previous = __node__; \
                        break; \
                    } \
                    __current_node__ = __current_node__->next; \
                    __insert_index__++; \
                } \
                if (__current_node__ == NULL) { \
                    __temp_list__->tail->next = __node__; \
                    __node__->previous = __temp_list__->tail; \
                    __temp_list__->tail = __node__; \
                } \
            } \
            __temp_list__->length++; \
            if ((__result_ptr__) != NULL) { *(__result_ptr__) = __insert_index__; } \
        } while(0)
    #endif
#endif

#define LinkedList_concat(__list_ptr1__, __list_ptr2__) do { \
    assert(((__list_ptr1__) != NULL) && (*(__list_ptr1__) != NULL)); \
    assert(((__list_ptr2__) != NULL) && (*(__list_ptr2__) != NULL)); \
    LinkedList *__temp_list1__ = (LinkedList *)(*(__list_ptr1__)); \
    LinkedList *__temp_list2__ = (LinkedList *)(*(__list_ptr2__)); \
    assert(__temp_list1__->element_size == __temp_list2__->element_size); \
    __Node *__current_node__ = __temp_list2__->head; \
    while (__current_node__ != NULL) { \
        __Node *__node__ = __node_init(__temp_list1__->element_size); \
        memcpy(__node__->element, __current_node__->element, __temp_list1__->element_size); \
        if (__temp_list1__->head == NULL) { \
            __temp_list1__->head = __node__; \
        } else { \
            __temp_list1__->tail->next = __node__; \
            __node__->previous = __temp_list1__->tail; \
        } \
        __temp_list1__->tail = __node__; \
        __temp_list1__->length++; \
        __current_node__ = __current_node__->next; \
    } \
} while(0)

#if COMPILER_SUPPORTS_TYPEOF
    #define LinkedList_pop(__list_ptr__) *((typeof(**(__list_ptr__)) *) (((LinkedList *)(*(__list_ptr__)))->tail->element)); do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        assert(__temp_list__->length > 0); \
        __Node *__node__ = __temp_list__->tail; \
        if (__node__->previous != NULL) { \
            __node__->previous->next = NULL; \
            __temp_list__->tail = __node__->previous; \
        } else { \
            __temp_list__->head = NULL; \
            __temp_list__->tail = NULL; \
        } \
        __temp_list__->length--; \
        free(__node__); \
    } while(0)
#else
    #define LinkedList_pop(__list_ptr__, __list_element_type__) *((__list_element_type__) (((LinkedList *)(*(__list_ptr__)))->tail->element)); do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        assert(__temp_list__->length > 0); \
        __Node *__node__ = __temp_list__->tail; \
        if (__node__->previous != NULL) { \
            __node__->previous->next = NULL; \
            __temp_list__->tail = __node__->previous; \
        } else { \
            __temp_list__->head = NULL; \
            __temp_list__->tail = NULL; \
        } \
        __temp_list__->length--; \
        free(__node__); \
    } while(0)
#endif

// in here i cannot use the same trick as list_pop because i don't have direct access to the element
#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_remove_at(__list_ptr__, __index__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = __temp_list__->head; \
            for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                __node__ = __node__->next; \
            } \
            if (__node__->previous != NULL) { \
                __node__->previous->next = __node__->next; \
            } else { \
                __temp_list__->head = __node__->next; \
            } \
            if (__node__->next != NULL) { \
                __node__->next->previous = __node__->previous; \
            } else { \
                __temp_list__->tail = __node__->previous; \
            } \
            __temp_list__->length--; \
            typeof(**(__list_ptr__)) __element__ = *((typeof(**(__list_ptr__)) *)__node__->element); \
            free(__node__); \
            __element__; \
        })
    #else
        #define LinkedList_remove_at(__list_ptr__, __index__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = __temp_list__->head; \
            for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                __node__ = __node__->next; \
            } \
            if (__node__->previous != NULL) { \
                __node__->previous->next = __node__->next; \
            } else { \
                __temp_list__->head = __node__->next; \
            } \
            if (__node__->next != NULL) { \
                __node__->next->previous = __node__->previous; \
            } else { \
                __temp_list__->tail = __node__->previous; \
            } \
            __temp_list__->length--; \
            __list_element_type__ __element__ = *((__list_element_type__) __node__->element); \
            free(__node__); \
            __element__; \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_remove_at(__list_ptr__, __index__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = __temp_list__->head; \
            for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                __node__ = __node__->next; \
            } \
            if (__node__->previous != NULL) { \
                __node__->previous->next = __node__->next; \
            } else { \
                __temp_list__->head = __node__->next; \
            } \
            if (__node__->next != NULL) { \
                __node__->next->previous = __node__->previous; \
            } else { \
                __temp_list__->tail = __node__->previous; \
            } \
            __temp_list__->length--; \
            if ((__result_ptr__) != NULL) { *(__result_ptr__) = *((typeof(**(__list_ptr__)) *)__node__->element); } \
            free(__node__); \
        } while(0)
    #else
        #define LinkedList_remove_at(__list_ptr__, __index__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = __temp_list__->head; \
            for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                __node__ = __node__->next; \
            } \
            if (__node__->previous != NULL) { \
                __node__->previous->next = __node__->next; \
            } else { \
                __temp_list__->head = __node__->next; \
            } \
            if (__node__->next != NULL) { \
                __node__->next->previous = __node__->previous; \
            } else { \
                __temp_list__->tail = __node__->previous; \
            } \
            __temp_list__->length--; \
            if ((__result_ptr__) != NULL) { *(__result_ptr__) = *((__list_element_type__) __node__->element); } \
            free(__node__); \
        } while(0)
    #endif
#endif

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_remove_value(__list_ptr__, __element__, __boolean_comparator__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __temp_list__->head; \
            bool __found__ = false; \
            size_t __i__ = 0; \
            for ( ; __i__ < __temp_list__->length; __i__++) { \
                if ((__boolean_comparator__)(*((typeof(**(__list_ptr__)) *)__node__->element), (__element__))) { \
                    if (__node__->previous != NULL) { \
                        __node__->previous->next = __node__->next; \
                    } else { \
                        __temp_list__->head = __node__->next; \
                    } \
                    if (__node__->next != NULL) { \
                        __node__->next->previous = __node__->previous; \
                    } else { \
                        __temp_list__->tail = __node__->previous; \
                    } \
                    __temp_list__->length--; \
                    __found__ = true; \
                    break; \
                } \
                __node__ = __node__->next; \
            } \
            assert(__found__); \
            __i__; \
        })
    #else
        #define LinkedList_remove_value(__list_ptr__, __element__, __boolean_comparator__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __temp_list__->head; \
            bool __found__ = false; \
            size_t __i__ = 0; \
            for ( ; __i__ < __temp_list__->length; __i__++) { \
                if ((__boolean_comparator__)(*(((__list_element_type__) *)__node__->element), (__element__))) { \
                    if (__node__->previous != NULL) { \
                        __node__->previous->next = __node__->next; \
                    } else { \
                        __temp_list__->head = __node__->next; \
                    } \
                    if (__node__->next != NULL) { \
                        __node__->next->previous = __node__->previous; \
                    } else { \
                        __temp_list__->tail = __node__->previous; \
                    } \
                    __temp_list__->length--; \
                    __found__ = true; \
                    break; \
                } \
                __node__ = __node__->next; \
            } \
            assert(__found__); \
            __i__; \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_remove_value(__list_ptr__, __element__, __boolean_comparator__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __temp_list__->head; \
            bool __found__ = false; \
            size_t __i__ = 0; \
            for ( ; __i__ < __temp_list__->length; __i__++) { \
                if ((__boolean_comparator__)(*((typeof(**(__list_ptr__)) *)__node__->element), (__element__))) { \
                    if (__node__->previous != NULL) { \
                        __node__->previous->next = __node__->next; \
                    } else { \
                        __temp_list__->head = __node__->next; \
                    } \
                    if (__node__->next != NULL) { \
                        __node__->next->previous = __node__->previous; \
                    } else { \
                        __temp_list__->tail = __node__->previous; \
                    } \
                    __temp_list__->length--; \
                    __found__ = true; \
                    break; \
                } \
                __node__ = __node__->next; \
            } \
            assert(__found); \
            if ((__result_ptr__) != NULL) { *(__result_ptr__) = __i__; } \
        } while(0)
    #else
        #define LinkedList_remove_value(__list_ptr__, __element__, __boolean_comparator__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->element_size == sizeof(__element__)); \
            __Node *__node__ = __temp_list__->head; \
            bool __found__ = false; \
            size_t __i__ = 0; \
            for ( ; __i__ < __temp_list__->length; __i__++) { \
                if ((__boolean_comparator__)(*(((__list_element_type__) *)__node__->element), (__element__))) { \
                    if (__node__->previous != NULL) { \
                        __node__->previous->next = __node__->next; \
                    } else { \
                        __temp_list__->head = __node__->next; \
                    } \
                    if (__node__->next != NULL) { \
                        __node__->next->previous = __node__->previous; \
                    } else { \
                        __temp_list__->tail = __node__->previous; \
                    } \
                    __temp_list__->length--; \
                    __found__ = true; \
                    break; \
                } \
                __node__ = __node__->next; \
            } \
            assert(__found); \
            if ((__result_ptr__) != NULL) { *(__result_ptr__) = __i__; } \
        } while(0)
    #endif
#endif

#define LinkedList_clear(__list_ptr__) do { \
    assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
    LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
    __Node *__current_node__ = __temp_list__->head; \
    while (__current_node__ != NULL) { \
        __Node *__next_node__ = __current_node__->next; \
        free(__current_node__); \
        __current_node__ = __next_node__; \
    } \
    __temp_list__->head = NULL; \
    __temp_list__->tail = NULL; \
    __temp_list__->length = 0; \
} while(0)

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_copy(__list_ptr__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            typeof(**(__list_ptr__)) *__new_list__ = LinkedList_init(typeof(**(__list_ptr__))); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                __Node *__node__ = __node_init(__temp_list__->element_size); \
                memcpy(__node__->element, __current_node__->element, __temp_list__->element_size); \
                if (__temp_new_list__->head == NULL) { \
                    __temp_new_list__->head = __node__; \
                } else { \
                    __temp_new_list__->tail->next = __node__; \
                    __node__->previous = __temp_new_list__->tail; \
                } \
                __temp_new_list__->tail = __node__; \
                __temp_new_list__->length++; \
                __current_node__ = __current_node__->next; \
            } \
            __new_list__; \
        })
    #else
        #define LinkedList_copy(__list_ptr__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __list_element_type__ *__new_list__ = LinkedList_init(__list_element_type__); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                __Node *__node__ = __node_init(__temp_list__->element_size); \
                memcpy(__node__->element, __current_node__->element, __temp_list__->element_size); \
                if (__temp_new_list__->head == NULL) { \
                    __temp_new_list__->head = __node__; \
                } else { \
                    __temp_new_list__->tail->next = __node__; \
                    __node__->previous = __temp_new_list__->tail; \
                } \
                __temp_new_list__->tail = __node__; \
                __temp_new_list__->length++; \
                __current_node__ = __current_node__->next; \
            } \
            __new_list__; \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_copy(__list_ptr__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            typeof(**(__list_ptr__)) *__new_list__ = LinkedList_init(typeof(**(__list_ptr__))); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                __Node *__node__ = __node_init(__temp_list__->element_size); \
                memcpy(__node__->element, __current_node__->element, __temp_list__->element_size); \
                if (__temp_new_list__->head == NULL) { \
                    __temp_new_list__->head = __node__; \
                } else { \
                    __temp_new_list__->tail->next = __node__; \
                    __node__->previous = __temp_new_list__->tail; \
                } \
                __temp_new_list__->tail = __node__; \
                __temp_new_list__->length++; \
                __current_node__ = __current_node__->next; \
            } \
            *(__result_ptr__) = __new_list__; \
        } while(0)
    #else
        #define LinkedList_copy(__list_ptr__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __list_element_type__ *__new_list__ = LinkedList_init(__list_element_type__); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                __Node *__node__ = __node_init(__temp_list__->element_size); \
                memcpy(__node__->element, __current_node__->element, __temp_list__->element_size); \
                if (__temp_new_list__->head == NULL) { \
                    __temp_new_list__->head = __node__; \
                } else { \
                    __temp_new_list__->tail->next = __node__; \
                    __node__->previous = __temp_new_list__->tail; \
                } \
                __temp_new_list__->tail = __node__; \
                __temp_new_list__->length++; \
                __current_node__ = __current_node__->next; \
            } \
            *(__result_ptr__) = __new_list__; \
        } while(0)
    #endif
#endif

#define LinkedList_reverse(__list_ptr__) do { \
    assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
    LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
    __Node *__current_node__ = __temp_list__->head; \
    while (__current_node__ != NULL) { \
        __Node *__next_node__ = __current_node__->next; \
        __current_node__->next = __current_node__->previous; \
        __current_node__->previous = __next_node__; \
        __current_node__ = __next_node__; \
    } \
    __Node *__temp_node__ = __temp_list__->head; \
    __temp_list__->head = __temp_list__->tail; \
    __temp_list__->tail = __temp_node__; \
} while(0)

#if COMPILER_SUPPORTS_TYPEOF
    #define LinkedList_sort(__list_ptr__, __ordering_comparator__) do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        __Node *__current_node__ = __temp_list__->head; \
        while (__current_node__ != NULL) { \
            __Node *__next_node__ = __current_node__->next; \
            while (__next_node__ != NULL) { \
                if (__ordering_comparator__(*((typeof(**(__list_ptr__)) *)__current_node__->element), *((typeof(**(__list_ptr__)) *)__next_node__->element)) > 0) { \
                    void *__temp_element__ = malloc(__temp_list__->element_size); \
                    memcpy(__temp_element__, __current_node__->element, __temp_list__->element_size); \
                    memcpy(__current_node__->element, __next_node__->element, __temp_list__->element_size); \
                    memcpy(__next_node__->element, __temp_element__, __temp_list__->element_size); \
                    free(__temp_element__); \
                } \
                __next_node__ = __next_node__->next; \
            } \
            __current_node__ = __current_node__->next; \
        } \
    } while(0)
#else
    #define LinkedList_sort(__list_ptr__, __ordering_comparator__, __list_element_type__) do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        __Node *__current_node__ = __temp_list__->head; \
        while (__current_node__ != NULL) { \
            __Node *__next_node__ = __current_node__->next; \
            while (__next_node__ != NULL) { \
                if (__ordering_comparator__(*((__list_element_type__) __current_node__->element), *((__list_element_type__) __next_node__->element)) > 0) { \
                    void *__temp_element__ = malloc(__temp_list__->element_size); \
                    memcpy(__temp_element__, __current_node__->element, __temp_list__->element_size); \
                    memcpy(__current_node__->element, __next_node__->element, __temp_list__->element_size); \
                    memcpy(__next_node__->element, __temp_element__, __temp_list__->element_size); \
                    free(__temp_element__); \
                } \
                __next_node__ = __next_node__->next; \
            } \
            __current_node__ = __current_node__->next; \
        } \
    } while(0)
#endif

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_filter(__list_ptr__, __filter__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            typeof(**(__list_ptr__)) *__new_list__ = LinkedList_init(typeof(**(__list_ptr__))); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                if ((__filter__)(*((typeof(**(__list_ptr__)) *)__current_node__->element))) { \
                    __Node *__node__ = __node_init(__temp_list__->element_size); \
                    memcpy(__node__->element, __current_node__->element, __temp_list__->element_size); \
                    if (__temp_new_list__->head == NULL) { \
                        __temp_new_list__->head = __node__; \
                    } else { \
                        __temp_new_list__->tail->next = __node__; \
                        __node__->previous = __temp_new_list__->tail; \
                    } \
                    __temp_new_list__->tail = __node__; \
                    __temp_new_list__->length++; \
                } \
                __current_node__ = __current_node__->next; \
            } \
            __new_list__; \
        })
    #else
        #define LinkedList_filter(__list_ptr__, __filter__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __list_element_type__ *__new_list__ = LinkedList_init(__list_element_type__); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                if ((__filter__)(*((__list_element_type__) __current_node__->element))) { \
                    __Node *__node__ = __node_init(__temp_list__->element_size); \
                    memcpy(__node__->element, __current_node__->element, __temp_list__->element_size); \
                    if (__temp_new_list__->head == NULL) { \
                        __temp_new_list__->head = __node__; \
                    } else { \
                        __temp_new_list__->tail->next = __node__; \
                        __node__->previous = __temp_new_list__->tail; \
                    } \
                    __temp_new_list__->tail = __node__; \
                    __temp_new_list__->length++; \
                } \
                __current_node__ = __current_node__->next; \
            } \
            __new_list__; \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_filter(__list_ptr__, __filter__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            typeof(**(__list_ptr__)) *__new_list__ = LinkedList_init(typeof(**(__list_ptr__))); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                if ((__filter__)(*((typeof(**(__list_ptr__)) *)__current_node__->element))) { \
                    __Node *__node__ = __node_init(__temp_list__->element_size); \
                    memcpy(__node__->element, __current_node__->element, __temp_list__->element_size); \
                    if (__temp_new_list__->head == NULL) { \
                        __temp_new_list__->head = __node__; \
                    } else { \
                        __temp_new_list__->tail->next = __node__; \
                        __node__->previous = __temp_new_list__->tail; \
                    } \
                    __temp_new_list__->tail = __node__; \
                    __temp_new_list__->length++; \
                } \
                __current_node__ = __current_node__->next; \
            } \
            *(__result_ptr__) = __new_list__; \
        } while(0)
    #else
        #define LinkedList_filter(__list_ptr__, __filter__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __list_element_type__ *__new_list__ = LinkedList_init(__list_element_type__); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                if ((__filter__)(*((__list_element_type__) __current_node__->element))) { \
                    __Node *__node__ = __node_init(__temp_list__->element_size); \
                    memcpy(__node__->element, __current_node__->element, __temp_list__->element_size); \
                    if (__temp_new_list__->head == NULL) { \
                        __temp_new_list__->head = __node__; \
                    } else { \
                        __temp_new_list__->tail->next = __node__; \
                        __node__->previous = __temp_new_list__->tail; \
                    } \
                    __temp_new_list__->tail = __node__; \
                    __temp_new_list__->length++; \
                } \
                __current_node__ = __current_node__->next; \
            } \
            *(__result_ptr__) = __new_list__; \
        } while(0)
    #endif
#endif

#if COMPILER_SUPPORTS_TYPEOF
    #define LinkedList_foreach(__list_ptr__, __func__) do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        __Node *__current_node__ = __temp_list__->head; \
        while (__current_node__ != NULL) { \
            (__func__)((typeof(**(__list_ptr__)) *)__current_node__->element); \
            __current_node__ = __current_node__->next; \
        } \
    } while(0)
#else
    #define LinkedList_foreach(__list_ptr__, __func__, __list_element_type__) do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        __Node *__current_node__ = __temp_list__->head; \
        while (__current_node__ != NULL) { \
            (__func__)((__list_element_type__) __current_node__->element); \
            __current_node__ = __current_node__->next; \
        } \
    } while(0)
#endif

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_map(__list_ptr__, __mapper__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            typeof(**(__list_ptr__)) *__new_list__ = LinkedList_init(typeof(**(__list_ptr__))); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                typeof(**(__list_ptr__)) __element__ = (__mapper__)(*((typeof(**(__list_ptr__)) *)__current_node__->element)); \
                __Node *__node__ = __node_init(__temp_list__->element_size); \
                memcpy(__node__->element, &__element__, __temp_list__->element_size); \
                if (__temp_new_list__->head == NULL) { \
                    __temp_new_list__->head = __node__; \
                } else { \
                    __temp_new_list__->tail->next = __node__; \
                    __node__->previous = __temp_new_list__->tail; \
                } \
                __temp_new_list__->tail = __node__; \
                __temp_new_list__->length++; \
                __current_node__ = __current_node__->next; \
            } \
            __new_list__; \
        })
    #else
        #define LinkedList_map(__list_ptr__, __mapper__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __list_element_type__ *__new_list__ = LinkedList_init(__list_element_type__); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                __list_element_type__ __element__ = (__mapper__)(*((__list_element_type__) __current_node__->element)); \
                __Node *__node__ = __node_init(__temp_list__->element_size); \
                memcpy(__node__->element, &__element__, __temp_list__->element_size); \
                if (__temp_new_list__->head == NULL) { \
                    __temp_new_list__->head = __node__; \
                } else { \
                    __temp_new_list__->tail->next = __node__; \
                    __node__->previous = __temp_new_list__->tail; \
                } \
                __temp_new_list__->tail = __node__; \
                __temp_new_list__->length++; \
                __current_node__ = __current_node__->next; \
            } \
            __new_list__; \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_map(__list_ptr__, __mapper__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            typeof(**(__list_ptr__)) *__new_list__ = LinkedList_init(typeof(**(__list_ptr__))); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                typeof(**(__list_ptr__)) __element__ = (__mapper__)(*((typeof(**(__list_ptr__)) *)__current_node__->element)); \
                __Node *__node__ = __node_init(__temp_list__->element_size); \
                memcpy(__node__->element, &__element__, __temp_list__->element_size); \
                if (__temp_new_list__->head == NULL) { \
                    __temp_new_list__->head = __node__; \
                } else { \
                    __temp_new_list__->tail->next = __node__; \
                    __node__->previous = __temp_new_list__->tail; \
                } \
                __temp_new_list__->tail = __node__; \
                __temp_new_list__->length++; \
                __current_node__ = __current_node__->next; \
            } \
            *(__result_ptr__) = __new_list__; \
        } while(0)
    #else
        #define LinkedList_map(__list_ptr__, __mapper__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __list_element_type__ *__new_list__ = LinkedList_init(__list_element_type__); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                __list_element_type__ __element__ = (__mapper__)(*((__list_element_type__) __current_node__->element)); \
                __Node *__node__ = __node_init(__temp_list__->element_size); \
                memcpy(__node__->element, &__element__, __temp_list__->element_size); \
                if (__temp_new_list__->head == NULL) { \
                    __temp_new_list__->head = __node__; \
                } else { \
                    __temp_new_list__->tail->next = __node__; \
                    __node__->previous = __temp_new_list__->tail; \
                } \
                __temp_new_list__->tail = __node__; \
                __temp_new_list__->length++; \
                __current_node__ = __current_node__->next; \
            } \
            *(__result_ptr__) = __new_list__; \
        } while(0)
    #endif
#endif

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_reduce(__list_ptr__, __reducer__, __initial_value__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            typeof(__initial_value__) __accumulator__ = (__initial_value__); \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                __accumulator__ = (__reducer__)(__accumulator__, *((typeof(**(__list_ptr__)) *)__current_node__->element)); \
                __current_node__ = __current_node__->next; \
            } \
            __accumulator__; \
        })
    #else
        #define LinkedList_reduce(__list_ptr__, __reducer__, __initial_value__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __list_element_type__ __accumulator__ = (__initial_value__); \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                __accumulator__ = (__reducer__)(__accumulator__, *((__list_element_type__) __current_node__->element)); \
                __current_node__ = __current_node__->next; \
            } \
            __accumulator__; \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_reduce(__list_ptr__, __reducer__, __initial_value__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            typeof(__initial_value__) __accumulator__ = (__initial_value__); \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                __accumulator__ = (__reducer__)(__accumulator__, *((typeof(**(__list_ptr__)) *)__current_node__->element)); \
                __current_node__ = __current_node__->next; \
            } \
            *(__result_ptr__) = __accumulator__; \
        } while(0)
    #else
        #define LinkedList_reduce(__list_ptr__, __reducer__, __initial_value__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __list_element_type__ __accumulator__ = (__initial_value__); \
            __Node *__current_node__ = __temp_list__->head; \
            while (__current_node__ != NULL) { \
                __accumulator__ = (__reducer__)(__accumulator__, *((__list_element_type__) __current_node__->element)); \
                __current_node__ = __current_node__->next; \
            } \
            *(__result_ptr__) = __accumulator__; \
        } while(0)
    #endif
#endif

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_any(__list_ptr__, __func__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __Node *__current_node__ = __temp_list__->head; \
            bool __result__ = false; \
            while (__current_node__ != NULL) { \
                if ((__func__)(*((typeof(**(__list_ptr__)) *)__current_node__->element))) { \
                    __result__ = true; \
                    break; \
                } \
                __current_node__ = __current_node__->next; \
            } \
            __result__; \
        })
    #else
        #define LinkedList_any(__list_ptr__, __func__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __Node *__current_node__ = __temp_list__->head; \
            bool __result__ = false; \
            while (__current_node__ != NULL) { \
                if ((__func__)(*((__list_element_type__) __current_node__->element))) { \
                    __result__ = true; \
                    break; \
                } \
                __current_node__ = __current_node__->next; \
            } \
            __result__; \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_any(__list_ptr__, __func__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __Node *__current_node__ = __temp_list__->head; \
            bool __result__ = false; \
            while (__current_node__ != NULL) { \
                if ((__func__)(*((typeof(**(__list_ptr__)) *)__current_node__->element))) { \
                    __result__ = true; \
                    break; \
                } \
                __current_node__ = __current_node__->next; \
            } \
            *(__result_ptr__) = __result__; \
        } while(0)
    #else
        #define LinkedList_any(__list_ptr__, __func__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __Node *__current_node__ = __temp_list__->head; \
            bool __result__ = false; \
            while (__current_node__ != NULL) { \
                if ((__func__)(*((__list_element_type__) __current_node__->element))) { \
                    __result__ = true; \
                    break; \
                } \
                __current_node__ = __current_node__->next; \
            } \
            *(__result_ptr__) = __result__; \
        } while(0)
    #endif
#endif

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_all(__list_ptr__, __func__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __Node *__current_node__ = __temp_list__->head; \
            bool __result__ = true; \
            while (__current_node__ != NULL) { \
                if (!(__func__)(*((typeof(**(__list_ptr__)) *)__current_node__->element))) { \
                    __result__ = false; \
                    break; \
                } \
                __current_node__ = __current_node__->next; \
            } \
            __result__; \
        })
    #else
        #define LinkedList_all(__list_ptr__, __func__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __Node *__current_node__ = __temp_list__->head; \
            bool __result__ = true; \
            while (__current_node__ != NULL) { \
                if (!(__func__)(*((__list_element_type__) __current_node__->element))) { \
                    __result__ = false; \
                    break; \
                } \
                __current_node__ = __current_node__->next; \
            } \
            __result__; \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_all(__list_ptr__, __func__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __Node *__current_node__ = __temp_list__->head; \
            bool __result__ = true; \
            while (__current_node__ != NULL) { \
                if (!(__func__)(*((typeof(**(__list_ptr__)) *)__current_node__->element))) { \
                    __result__ = false; \
                    break; \
                } \
                __current_node__ = __current_node__->next; \
            } \
            *(__result_ptr__) = __result__; \
        } while(0)
    #else
        #define LinkedList_all(__list_ptr__, __func__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            __Node *__current_node__ = __temp_list__->head; \
            bool __result__ = true; \
            while (__current_node__ != NULL) { \
                if (!(__func__)(*((__list_element_type__) __current_node__->element))) { \
                    __result__ = false; \
                    break; \
                } \
                __current_node__ = __current_node__->next; \
            } \
            *(__result_ptr__) = __result__; \
        } while(0)
    #endif
#endif

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_slice(__list_ptr__, __start__, __end__, __step__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__start__ >= 0) && (__start__ < __temp_list__->length)); \
            assert((__end__ >= 0) && (__end__ <= __temp_list__->length)); \
            assert(__start__ < __end__); \
            assert(__step__ > 0); \
            typeof(**(__list_ptr__)) *__new_list__ = LinkedList_init(typeof(**(__list_ptr__))); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            size_t __i__ = 0; \
            for ( ; __i__ < __start__; __i__++) { \
                __current_node__ = __current_node__->next; \
            } \
            while (__i__ < __end__) { \
                __Node *__node__ = __node_init(__temp_list__->element_size); \
                memcpy(__node__->element, __current_node__->element, __temp_list__->element_size); \
                if (__temp_new_list__->head == NULL) { \
                    __temp_new_list__->head = __node__; \
                } else { \
                    __temp_new_list__->tail->next = __node__; \
                    __node__->previous = __temp_new_list__->tail; \
                } \
                __temp_new_list__->tail = __node__; \
                __temp_new_list__->length++; \
                for (size_t __j__ = 0; __j__ < __step__; __j__++) { \
                    __current_node__ = __current_node__->next; \
                    __i__++; \
                    if (__i__ >= __end__) { \
                        break; \
                    } \
                } \
            } \
            __new_list__; \
        })
    #else
        #define LinkedList_slice(__list_ptr__, __start__, __end__, __step__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__start__ >= 0) && (__start__ < __temp_list__->length)); \
            assert((__end__ >= 0) && (__end__ <= __temp_list__->length)); \
            assert(__start__ < __end__); \
            assert(__step__ > 0); \
            __list_element_type__ *__new_list__ = LinkedList_init(__list_element_type__); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            size_t __i__ = 0; \
            for ( ; __i__ < __start__; __i__++) { \
                __current_node__ = __current_node__->next; \
            } \
            while (__i__ < __end__) { \
                __Node *__node__ = __node_init(__temp_list__->element_size); \
                memcpy(__node__->element, __current_node__->element, __temp_list__->element_size); \
                if (__temp_new_list__->head == NULL) { \
                    __temp_new_list__->head = __node__; \
                } else { \
                    __temp_new_list__->tail->next = __node__; \
                    __node__->previous = __temp_new_list__->tail; \
                } \
                __temp_new_list__->tail = __node__; \
                __temp_new_list__->length++; \
                for (size_t __j__ = 0; __j__ < __step__; __j__++) { \
                    __current_node__ = __current_node__->next; \
                    __i__++; \
                    if (__i__ >= __end__) { \
                        break; \
                    } \
                } \
            } \
            __new_list__; \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        #define LinkedList_slice(__list_ptr__, __start__, __end__, __step__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__start__ >= 0) && (__start__ < __temp_list__->length)); \
            assert((__end__ >= 0) && (__end__ <= __temp_list__->length)); \
            assert(__start__ < __end__); \
            assert(__step__ > 0); \
            typeof(**(__list_ptr__)) *__new_list__ = LinkedList_init(typeof(**(__list_ptr__))); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            size_t __i__ = 0; \
            for ( ; __i__ < __start__; __i__++) { \
                __current_node__ = __current_node__->next; \
            } \
            while (__i__ < __end__) { \
                __Node *__node__ = __node_init(__temp_list__->element_size); \
                memcpy(__node__->element, __current_node__->element, __temp_list__->element_size); \
                if (__temp_new_list__->head == NULL) { \
                    __temp_new_list__->head = __node__; \
                } else { \
                    __temp_new_list__->tail->next = __node__; \
                    __node__->previous = __temp_new_list__->tail; \
                } \
                __temp_new_list__->tail = __node__; \
                __temp_new_list__->length++; \
                for (size_t __j__ = 0; __j__ < __step__; __j__++) { \
                    __current_node__ = __current_node__->next; \
                    __i__++; \
                    if (__i__ >= __end__) { \
                        break; \
                    } \
                } \
            } \
            *(__result_ptr__) = __new_list__; \
        } while(0)
    #else
        #define LinkedList_slice(__list_ptr__, __start__, __end__, __step__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__start__ >= 0) && (__start__ < __temp_list__->length)); \
            assert((__end__ >= 0) && (__end__ <= __temp_list__->length)); \
            assert(__start__ < __end__); \
            assert(__step__ > 0); \
            __list_element_type__ *__new_list__ = LinkedList_init(__list_element_type); \
            LinkedList *__temp_new_list__ = (LinkedList *)__new_list__; \
            __Node *__current_node__ = __temp_list__->head; \
            size_t __i__ = 0; \
            for ( ; __i__ < __start__; __i__++) { \
                __current_node__ = __current_node__->next; \
            } \
            while (__i__ < __end__) { \
                __Node *__node__ = __node_init(__temp_list__->element_size); \
                memcpy(__node__->element, __current_node__->element, __temp_list__->element_size); \
                if (__temp_new_list__->head == NULL) { \
                    __temp_new_list__->head = __node__; \
                } else { \
                    __temp_new_list__->tail->next = __node__; \
                    __node__->previous = __temp_new_list__->tail; \
                } \
                __temp_new_list__->tail = __node__; \
                __temp_new_list__->length++; \
                for (size_t __j__ = 0; __j__ < __step__; __j__++) { \
                    __current_node__ = __current_node__->next; \
                    __i__++; \
                    if (__i__ >= __end__) { \
                        break; \
                    } \
                } \
            } \
            *(__result_ptr__) = __new_list__; \
        } while(0)
    #endif
#endif


#if LANGUAGE_CPP // C++ support
}
#endif

#endif // LINKEDLIST_H
