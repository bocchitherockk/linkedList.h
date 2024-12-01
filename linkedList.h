#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#if LANGUAGE_CPP // C++ support
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "./modules/system_env/system_env.h"

typedef struct __Node {
    struct __Node *next;
    struct __Node *previous;
    char element[];
} __Node;

/**
 * Private
 * 
 * Initializes a new node.
 * @param element_size [size_t] The size of the element in the node.
 * @return [__Node *] A reference to the new node.
 * @throw [assert] If malloc fails.
 */
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
 * @throw [assert] If malloc fails.
 */
LinkedList *__linkedlist_init(size_t element_size);

/**
 * Public
 * 
 * Returns the number of elements in the list.
 * @param list_ptr [T **] A reference to the list.
 * @return [size_t] The length of the list.
 * @throw [assert] If the reference to the list is NULL.
 * @throw [assert] If the list is NULL.
 */
size_t LinkedList_length(void *list_ptr);

/**
 * Public
 * 
 * Returns the size of the elements in the list.
 * @param list_ptr [T **] A reference to the list.
 * @return [size_t] The size of the elements in the list.
 * @throw [assert] If the reference to the list is NULL.
 * @throw [assert] If the list is NULL.
 */
size_t LinkedList_element_size(void *list_ptr);

/**
 * Public
 * 
 * Returns whether the list is empty.
 * @param list_ptr [T **] A reference to the list.
 * @return [bool] Whether the list is empty.
 * @throw [assert] If the reference to the list is NULL.
 * @throw [assert] If the list is NULL.
 */
bool LinkedList_is_empty(void *list_ptr);

/**
 * Public
 * 
 * Initializes a new list.
 * @param __T__ [type] The type of the elements in the list.
 * @return [__T__ *] The new list.
 * @throw [assert] If malloc fails.
 */
#define LinkedList_init(__T__) (__T__ *)__linkedlist_init(sizeof(__T__))

/**
 * Public
 * 
 * Destroys the list.
 * @param __list_ptr__ [T **] A reference to the list.
 * @throw [assert] If the reference to the list is NULL.
 * @throw [assert] If the list is NULL.
 */
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
        /**
         * Public
         * 
         * Gets the element at the specified index.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __index__ [size_t] The index of the element.
         * @return [T] The element at the specified index.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         */
        #define LinkedList_get(__list_ptr__, __index__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = NULL; \
            if (__index__ < __temp_list__->length / 2) { \
                __node__ = __temp_list__->head; \
                for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                    __node__ = __node__->next; \
                } \
            } else { \
                __node__ = __temp_list__->tail; \
                for (size_t __i__ = __temp_list__->length - 1; __i__ > __index__; __i__--) { \
                    __node__ = __node__->previous; \
                } \
            } \
            *((typeof(**(__list_ptr__)) *)__node__->element); \
        })
    #else
        /**
         * Public
         * 
         * Gets the element at the specified index.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __index__ [size_t] The index of the element.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [T] The element at the specified index.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         */
        #define LinkedList_get(__list_ptr__, __index__,__list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = NULL; \
            if (__index__ < __temp_list__->length / 2) { \
                __node__ = __temp_list__->head; \
                for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                    __node__ = __node__->next; \
                } \
            } else { \
                __node__ = __temp_list__->tail; \
                for (size_t __i__ = __temp_list__->length - 1; __i__ > __index__; __i__--) { \
                    __node__ = __node__->previous; \
                } \
            } \
            *(((__list_element_type__) *)__node__->element); \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        /**
         * Public
         * 
         * Gets the element at the specified index.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __index__ [size_t] The index of the element.
         * @param __result_ptr__ [T *] A reference to the result.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the index is out of bounds.
         * @throw [assert] If the result reference is NULL.
         */
        #define LinkedList_get(__list_ptr__, __index__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = NULL; \
            if (__index__ < __temp_list__->length / 2) { \
                __node__ = __temp_list__->head; \
                for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                    __node__ = __node__->next; \
                } \
            } else { \
                __node__ = __temp_list__->tail; \
                for (size_t __i__ = __temp_list__->length - 1; __i__ > __index__; __i__--) { \
                    __node__ = __node__->previous; \
                } \
            } \
            *(__result_ptr__) = *((typeof(**(__list_ptr__)) *)__node__->element); \
        } while(0)
    #else
        /**
         * Public
         * 
         * Gets the element at the specified index.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __index__ [size_t] The index of the element.
         * @param __result_ptr__ [T *] A reference to the result.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the index is out of bounds.
         * @throw [assert] If the result reference is NULL.
         */
        #define LinkedList_get(__list_ptr__, __index__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            assert((__result_ptr__) != NULL); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = NULL; \
            if (__index__ < __temp_list__->length / 2) { \
                __node__ = __temp_list__->head; \
                for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                    __node__ = __node__->next; \
                } \
            } else { \
                __node__ = __temp_list__->tail; \
                for (size_t __i__ = __temp_list__->length - 1; __i__ > __index__; __i__--) { \
                    __node__ = __node__->previous; \
                } \
            } \
            *(__result_ptr__) = *(((__list_element_type__) *)__node__->element); \
        } while (0)
    #endif
#endif

#if COMPILER_SUPPORTS_TYPEOF
    /**
     * Public
     * 
     * Sets the element at the specified index.
     * @param __list_ptr__ [T **] A reference to the list.
     * @param __index__ [size_t] The index of the element.
     * @param __element__ [T] The new element.
     * @throw [assert] If the reference to the list is NULL.
     * @throw [assert] If the list is NULL.
     * @throw [assert] If the index is out of bounds.
     * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
     */
    #define LinkedList_set(__list_ptr__, __index__, __element__) do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
        assert(__temp_list__->element_size == sizeof(__element__)); \
        __Node *__node__ = NULL; \
        if (__index__ < __temp_list__->length / 2) { \
            __node__ = __temp_list__->head; \
            for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                __node__ = __node__->next; \
            } \
        } else { \
            __node__ = __temp_list__->tail; \
            for (size_t __i__ = __temp_list__->length - 1; __i__ > __index__; __i__--) { \
                __node__ = __node__->previous; \
            } \
        } \
        typeof(**(__list_ptr__)) __temp_var__ = (__element__); \
        memcpy(__node__->element, &__temp_var__, sizeof(__temp_var__)); \
    } while(0)

#else
    /**
     * Public
     * 
     * Sets the element at the specified index.
     * @param __list_ptr__ [T **] A reference to the list.
     * @param __index__ [size_t] The index of the element.
     * @param __element__ [T] The new element.
     * @param __list_element_type__ [type] The type of the elements in the list.
     * @throw [assert] If the reference to the list is NULL.
     * @throw [assert] If the list is NULL.
     * @throw [assert] If the index is out of bounds.
     * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
     */
    #define LinkedList_set(__list_ptr__, __index__, __element__, __list_element_type__) do { \
        assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
        LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
        assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
        assert(__temp_list__->element_size == sizeof(__element__)); \
        __Node *__node__ = NULL; \
        if (__index__ < __temp_list__->length / 2) { \
            __node__ = __temp_list__->head; \
            for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                __node__ = __node__->next; \
            } \
        } else { \
            __node__ = __temp_list__->tail; \
            for (size_t __i__ = __temp_list__->length - 1; __i__ > __index__; __i__--) { \
                __node__ = __node__->previous; \
            } \
        } \
        __list_element_type__ __temp_var__ = (__element__); \
        memcpy(__node__->element, &__temp_var__, sizeof(__temp_var)); \
    } while(0)
#endif

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        /**
         * Public
         * 
         * Gets the index of the first element that satisfies the boolean comparator.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to search for.
         * @param __boolean_comparator__ [bool (*)(T, T)] The boolean comparator.
         * @return [size_t] The index of the element.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If the element is not found.
         */
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
        /**
         * Public
         * 
         * Gets the index of the first element that satisfies the boolean comparator.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to search for.
         * @param __boolean_comparator__ [bool (*)(T, T)] The boolean comparator.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [size_t] The index of the element.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If the element is not found.
         */
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
        /**
         * Public
         * 
         * Gets the index of the first element that satisfies the boolean comparator.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to search for.
         * @param __boolean_comparator__ [bool (*)(T, T)] The boolean comparator.
         * @param __result_ptr__ [size_t *] A reference to the result.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If the element is not found.
         */
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
        /**
         * Public
         * 
         * Gets the index of the first element that satisfies the boolean comparator.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to search for.
         * @param __boolean_comparator__ [bool (*)(T, T)] The boolean comparator.
         * @param __result_ptr__ [size_t *] A reference to the result.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If the element is not found.
         */
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
        /**
         * Public
         * 
         * Counts the elements that satisfy the boolean comparator.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to search for.
         * @param __boolean_comparator__ [bool (*)(T, T)] The boolean comparator.
         * @return [size_t] The count of the elements.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         */
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
        /**
         * Public
         * 
         * Counts the elements that satisfy the boolean comparator.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to search for.
         * @param __boolean_comparator__ [bool (*)(T, T)] The boolean comparator.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [size_t] The count of the elements.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         */
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
        /**
         * Public
         * 
         * Counts the elements that satisfy the boolean comparator.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to search for.
         * @param __boolean_comparator__ [bool (*)(T, T)] The boolean comparator.
         * @param __result_ptr__ [size_t *] A reference to the result.
         * @return [size_t] The count of the elements.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If the result reference is NULL.
         */
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
        /**
         * Public
         * 
         * Counts the elements that satisfy the boolean comparator.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to search for.
         * @param __boolean_comparator__ [bool (*)(T, T)] The boolean comparator.
         * @param __result_ptr__ [size_t *] A reference to the result.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [size_t] The count of the elements.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If the result reference is NULL.
         */
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
    /**
     * Public
     * 
     * Pushes an element to the end of the list.
     * @param __list_ptr__ [T **] A reference to the list.
     * @param __element__ [T] The element to push.
     * @throw [assert] If the reference to the list is NULL.
     * @throw [assert] If the list is NULL.
     * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
     * @throw [assert] If malloc fails.
     */
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
    /**
     * Public
     * 
     * Pushes an element to the end of the list.
     * @param __list_ptr__ [T **] A reference to the list.
     * @param __element__ [T] The element to push.
     * @param __list_element_type__ [type] The type of the elements in the list.
     * @throw [assert] If the reference to the list is NULL.
     * @throw [assert] If the list is NULL.
     * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
     * @throw [assert] If malloc fails.
     */
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

#if COMPILER_SUPPORTS_TYPEOF
    /**
     * Public
     * 
     * Inserts an element at the specified index.
     * @param __list_ptr__ [T **] A reference to the list.
     * @param __index__ [size_t] The index to insert the element at.
     * @param __element__ [T] The element to insert.
     * @throw [assert] If the reference to the list is NULL.
     * @throw [assert] If the list is NULL.
     * @throw [assert] If the index is out of bounds.
     * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
     * @throw [assert] If malloc fails.
     */
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
            if (__temp_list__->head) { \
                __temp_list__->head->previous = __node__; \
            } \
            __temp_list__->head = __node__; \
            if (!__temp_list__->tail) { \
                __temp_list__->tail = __node__; \
            } \
        } else if (__index__ == __temp_list__->length) { \
            __node__->previous = __temp_list__->tail; \
            if (__temp_list__->tail) { \
                __temp_list__->tail->next = __node__; \
            } \
            __temp_list__->tail = __node__; \
            if (!__temp_list__->head) { \
                __temp_list__->head = __node__; \
            } \
        } else { \
            __Node *__current_node__ = NULL; \
            if (__index__ < __temp_list__->length / 2) { \
                __current_node__ = __temp_list__->head; \
                for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                    __current_node__ = __current_node__->next; \
                } \
            } else { \
                __current_node__ = __temp_list__->tail; \
                for (size_t __i__ = __temp_list__->length; __i__ > __index__; __i__--) { \
                    __current_node__ = __current_node__->previous; \
                } \
            } \
            __node__->next = __current_node__; \
            __node__->previous = __current_node__->previous; \
            if (__current_node__->previous) { \
                __current_node__->previous->next = __node__; \
            } \
            __current_node__->previous = __node__; \
        } \
        __temp_list__->length++; \
    } while(0)

#else
    /**
     * Public
     * 
     * Inserts an element at the specified index.
     * @param __list_ptr__ [T **] A reference to the list.
     * @param __index__ [size_t] The index to insert the element at.
     * @param __element__ [T] The element to insert.
     * @param __list_element_type__ [type] The type of the elements in the list.
     * @throw [assert] If the reference to the list is NULL.
     * @throw [assert] If the list is NULL.
     * @throw [assert] If the index is out of bounds.
     * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
     * @throw [assert] If malloc fails.
     */
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
            if (__temp_list__->head) { \
                __temp_list__->head->previous = __node__; \
            } \
            __temp_list__->head = __node__; \
            if (!__temp_list__->tail) { \
                __temp_list__->tail = __node__; \
            } \
        } else if (__index__ == __temp_list__->length) { \
            __node__->previous = __temp_list__->tail; \
            if (__temp_list__->tail) { \
                __temp_list__->tail->next = __node__; \
            } \
            __temp_list__->tail = __node__; \
            if (!__temp_list__->head) { \
                __temp_list__->head = __node__; \
            } \
        } else { \
            __Node *__current_node__ = NULL; \
            if (__index__ < __temp_list__->length / 2) { \
                __current_node__ = __temp_list__->head; \
                for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                    __current_node__ = __current_node__->next; \
                } \
            } else { \
                __current_node__ = __temp_list__->tail; \
                for (size_t __i__ = __temp_list__->length; __i__ > __index__; __i__--) { \
                    __current_node__ = __current_node__->previous; \
                } \
            } \
            __node__->next = __current_node__; \
            __node__->previous = __current_node__->previous; \
            if (__current_node__->previous) { \
                __current_node__->previous->next = __node__; \
            } \
            __current_node__->previous = __node__; \
        } \
        __temp_list__->length++; \
    } while(0)
#endif

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        /**
         * Public
         * 
         * Inserts an element at the correct position given an ordered list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to insert.
         * @param __ordering_comparator__ [int (*)(T, T)] The ordering comparator.
         * @return [size_t] The index where the element was inserted.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If malloc fails.
         */
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
        /**
         * Public
         * 
         * Inserts an element at the correct position given an ordered list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to insert.
         * @param __ordering_comparator__ [int (*)(T, T)] The ordering comparator.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [size_t] The index where the element was inserted.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If malloc fails.
         */
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
        /**
         * Public
         * 
         * Inserts an element at the correct position given an ordered list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to insert.
         * @param __ordering_comparator__ [int (*)(T, T)] The ordering comparator.
         * @param __result_ptr__ [size_t *] A reference to the variable to store the index where the element was inserted, if NULL the result will not be stored but the function will execute normally
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If malloc fails.
         */
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
        /**
         * Public
         * 
         * Inserts an element at the correct position given an ordered list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to insert.
         * @param __ordering_comparator__ [int (*)(T, T)] The ordering comparator.
         * @param __result_ptr__ [size_t *] A reference to the variable to store the index where the element was inserted, if NULL the result will not be stored but the function will execute normally
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If malloc fails.
         */
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

/**
 * Public
 * 
 * Concatenates two lists.
 * @param __list_ptr1__ [T **] A reference to the first list.
 * @param __list_ptr2__ [T **] A reference to the second list.
 * @throw [assert] If the reference to the first list is NULL.
 * @throw [assert] If the first list is NULL.
 * @throw [assert] If the reference to the second list is NULL.
 * @throw [assert] If the second list is NULL.
 * @throw [assert] If the element sizes of the lists are not the same.
 * @throw [assert] If malloc fails.
 */
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

#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        /**
         * Public
         * 
         * Removes the last element from the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @return [T] The removed element.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the list is empty.
         */
        #define LinkedList_pop(__list_ptr__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->length > 0); \
            __Node *__node__ = __temp_list__->tail; \
            typeof(**(__list_ptr__)) __element__ = *((typeof(**(__list_ptr__)) *)__node__->element); \
            if (__node__->previous != NULL) { \
                __node__->previous->next = NULL; \
                __temp_list__->tail = __node__->previous; \
            } else { \
                __temp_list__->head = NULL; \
                __temp_list__->tail = NULL; \
            } \
            __temp_list__->length--; \
            free(__node__); \
            __element__; \
        })
    #else
        /**
         * Public
         * 
         * Removes the last element from the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [T] The removed element.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the list is empty.
         */
        #define LinkedList_pop(__list_ptr__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->length > 0); \
            __Node *__node__ = __temp_list__->tail; \
            __list_element_type__ __element__ = *((__list_element_type__) __node__->element); \
            if (__node__->previous != NULL) { \
                __node__->previous->next = NULL; \
                __temp_list__->tail = __node__->previous; \
            } else { \
                __temp_list__->head = NULL; \
                __temp_list__->tail = NULL; \
            } \
            __temp_list__->length--; \
            free(__node__); \
            __element__; \
        })
    #endif
#else
    #if COMPILER_SUPPORTS_TYPEOF
        /**
         * Public
         * 
         * Removes the last element from the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __result_ptr__ [T *] A reference to the variable to store the removed element, if NULL the result will not be stored but the function will execute normally
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the list is empty.
         */
        #define LinkedList_pop(__list_ptr__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->length > 0); \
            __Node *__node__ = __temp_list__->tail; \
            if (__result_ptr__ != NULL) { \
                *(__result_ptr__) = *((typeof(**(__list_ptr__)) *)__node__->element); \
            } \
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
        /**
         * Public
         * 
         * Removes the last element from the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __result_ptr__ [T *] A reference to the variable to store the removed element, if NULL the result will not be stored but the function will execute normally
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the list is empty.
         */
        #define LinkedList_pop(__list_ptr__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert(__temp_list__->length > 0); \
            __Node *__node__ = __temp_list__->tail; \
            if (__result_ptr__ != NULL) { \
                *(__result_ptr__) = *(((__list_element_type__) *) __node__->element); \
            } \
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
#endif

// in here i cannot use the same trick as list_pop because i don't have direct access to the element
#if COMPILER_SUPPORTS_STATEMENT_EXPRESSIONS
    #if COMPILER_SUPPORTS_TYPEOF
        /**
         * Public
         * 
         * Removes the element at the specified index.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __index__ [size_t] The index to remove the element from.
         * @return [T] The removed element.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the index is out of bounds.
         */
        #define LinkedList_remove_at(__list_ptr__, __index__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = NULL; \
            if (__index__ < __temp_list__->length / 2) { \
                __node__ = __temp_list__->head; \
                for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                    __node__ = __node__->next; \
                } \
            } else { \
                __node__ = __temp_list__->tail; \
                for (size_t __i__ = __temp_list__->length - 1; __i__ > __index__; __i__--) { \
                    __node__ = __node__->previous; \
                } \
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
        /**
         * Public
         * 
         * Removes the element at the specified index.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __index__ [size_t] The index to remove the element from.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [T] The removed element.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the index is out of bounds.
         */
        #define LinkedList_remove_at(__list_ptr__, __index__, __list_element_type__) ({ \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = NULL; \
            if (__index__ < __temp_list__->length / 2) { \
                __node__ = __temp_list__->head; \
                for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                    __node__ = __node__->next; \
                } \
            } else { \
                __node__ = __temp_list__->tail; \
                for (size_t __i__ = __temp_list__->length - 1; __i__ > __index__; __i__--) { \
                    __node__ = __node__->previous; \
                } \
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
        /**
         * Public
         * 
         * Removes the element at the specified index.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __index__ [size_t] The index to remove the element from.
         * @param __result_ptr__ [T *] A reference to the variable to store the removed element, if NULL the result will not be stored but the function will execute normally
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the index is out of bounds.
         */
        #define LinkedList_remove_at(__list_ptr__, __index__, __result_ptr__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = NULL; \
            if (__index__ < __temp_list__->length / 2) { \
                __node__ = __temp_list__->head; \
                for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                    __node__ = __node__->next; \
                } \
            } else { \
                __node__ = __temp_list__->tail; \
                for (size_t __i__ = __temp_list__->length - 1; __i__ > __index__; __i__--) { \
                    __node__ = __node__->previous; \
                } \
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
        /**
         * Public
         * 
         * Removes the element at the specified index.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __index__ [size_t] The index to remove the element from.
         * @param __result_ptr__ [T *] A reference to the variable to store the removed element, if NULL the result will not be stored but the function will execute normally
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the index is out of bounds.
         */
        #define LinkedList_remove_at(__list_ptr__, __index__, __result_ptr__, __list_element_type__) do { \
            assert(((__list_ptr__) != NULL) && (*(__list_ptr__) != NULL)); \
            LinkedList *__temp_list__ = (LinkedList *)(*(__list_ptr__)); \
            assert((__index__ >= 0) && (__index__ < __temp_list__->length)); \
            __Node *__node__ = NULL; \
            if (__index__ < __temp_list__->length / 2) { \
                __node__ = __temp_list__->head; \
                for (size_t __i__ = 0; __i__ < __index__; __i__++) { \
                    __node__ = __node__->next; \
                } \
            } else { \
                __node__ = __temp_list__->tail; \
                for (size_t __i__ = __temp_list__->length - 1; __i__ > __index__; __i__--) { \
                    __node__ = __node__->previous; \
                } \
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
        /**
         * Public
         * 
         * Removes the first element that satisfies the boolean comparator.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to remove.
         * @param __boolean_comparator__ [bool (*)(T, T)] The boolean comparator.
         * @return [size_t] The index where the element was removed.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If the element was not found.
         */
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
        /**
         * Public
         * 
         * Removes the first element that satisfies the boolean comparator.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to remove.
         * @param __boolean_comparator__ [bool (*)(T, T)] The boolean comparator.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [size_t] The index where the element was removed.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If the element was not found.
         */
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
        /**
         * Public
         * 
         * Removes the first element that satisfies the boolean comparator.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to remove.
         * @param __boolean_comparator__ [bool (*)(T, T)] The boolean comparator.
         * @param __result_ptr__ [size_t *] A reference to the variable to store the index where the element was removed, if NULL the result will not be stored but the function will execute normally
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If the element was not found.
         */
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
        /**
         * Public
         * 
         * Removes the first element that satisfies the boolean comparator.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __element__ [T] The element to remove.
         * @param __boolean_comparator__ [bool (*)(T, T)] The boolean comparator.
         * @param __result_ptr__ [size_t *] A reference to the variable to store the index where the element was removed, if NULL the result will not be stored but the function will execute normally
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the element is not of the same type as the elements in the list. (gets checked by comparing the sizes)
         * @throw [assert] If the element was not found.
         */
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

/**
 * Public
 * 
 * Clears the list.
 * @param __list_ptr__ [T **] A reference to the list.
 * @throw [assert] If the reference to the list is NULL.
 * @throw [assert] If the list is NULL.
 */
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
        /**
         * Public
         * 
         * Copies the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @return [T *] The copied list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If malloc fails.
         */
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
        /**
         * Public
         * 
         * Copies the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [T *] The copied list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If malloc fails.
         */
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
        /**
         * Public
         * 
         * Copies the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __result_ptr__ [T **] A reference to the variable to store the copied list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If malloc fails.
         * @throw [assert] If the result pointer is NULL.
         */
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
        /**
         * Public
         * 
         * Copies the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __result_ptr__ [T **] A reference to the variable to store the copied list.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If malloc fails.
         * @throw [assert] If the result pointer is NULL.
         */
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

/**
 * Public
 * 
 * Reverses the list in place.
 * @param __list_ptr__ [T **] A reference to the list.
 * @throw [assert] If the reference to the list is NULL.
 * @throw [assert] If the list is NULL.
 * TODO: this function errors if the list is empty, check it out
 */
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
    /**
     * Public
     * 
     * Sorts the list in place.
     * @param __list_ptr__ [T **] A reference to the list.
     * @param __ordering_comparator__ [int (*)(T, T)] The ordering comparator.
     * @throw [assert] If the reference to the list is NULL.
     * @throw [assert] If the list is NULL.
     */
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
    /**
     * Public
     * 
     * Sorts the list in place.
     * @param __list_ptr__ [T **] A reference to the list.
     * @param __ordering_comparator__ [int (*)(T, T)] The ordering comparator.
     * @param __list_element_type__ [type] The type of the elements in the list.
     * @throw [assert] If the reference to the list is NULL.
     * @throw [assert] If the list is NULL.
     */
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
        /**
         * Public
         * 
         * Filters the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __filter__ [bool (*)(T)] The filter.
         * @return [T *] The filtered list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If malloc fails.
         */
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
        /**
         * Public
         * 
         * Filters the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __filter__ [bool (*)(T)] The filter.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [T *] The filtered list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If malloc fails.
         */
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
        /**
         * Public
         * 
         * Filters the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __filter__ [bool (*)(T)] The filter.
         * @param __result_ptr__ [T **] A reference to the variable to store the filtered list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If malloc fails.
         * @throw [assert] If the result pointer is NULL.
         */
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
        /**
         * Public
         * 
         * Filters the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __filter__ [bool (*)(T)] The filter.
         * @param __result_ptr__ [T **] A reference to the variable to store the filtered list.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If malloc fails.
         * @throw [assert] If the result pointer is NULL.
         */
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
    /**
     * Public
     * 
     * Executes a function for each element in the list.
     * @param __list_ptr__ [T **] A reference to the list.
     * @param __func__ [void (*)(T)] The function to execute.
     * @throw [assert] If the reference to the list is NULL.
     * @throw [assert] If the list is NULL.
     */
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
    /**
     * Public
     * 
     * Executes a function for each element in the list.
     * @param __list_ptr__ [T **] A reference to the list.
     * @param __func__ [void (*)(T)] The function to execute.
     * @param __list_element_type__ [type] The type of the elements in the list.
     * @throw [assert] If the reference to the list is NULL.
     * @throw [assert] If the list is NULL.
     */
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
        /**
         * Public
         * 
         * Maps the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __mapper__ [U (*)(T)] The mapper.
         * @return [U *] The mapped list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If malloc fails.
         */
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
        /**
         * Public
         * 
         * Maps the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __mapper__ [U (*)(T)] The mapper.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [U *] The mapped list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If malloc fails.
         */
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
        /**
         * Public
         * 
         * Maps the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __mapper__ [U (*)(T)] The mapper.
         * @param __result_ptr__ [T **] A reference to the variable to store the mapped list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If malloc fails.
         * @throw [assert] If the result pointer is NULL.
         */
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
        /**
         * Public
         * 
         * Maps the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __mapper__ [U (*)(T)] The mapper.
         * @param __result_ptr__ [T **] A reference to the variable to store the mapped list.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If malloc fails.
         * @throw [assert] If the result pointer is NULL.
         */
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
        /**
         * Public
         * 
         * Reduces the list to a single value.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __reducer__ [U (*)(U, T)] The reducer.
         * @param __initial_value__ [U] The initial value.
         * @return [U] The reduced value.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         */
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
        /**
         * Public
         * 
         * Reduces the list to a single value.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __reducer__ [U (*)(U, T)] The reducer.
         * @param __initial_value__ [U] The initial value.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [U] The reduced value.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         */
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
        /**
         * Public
         * 
         * Reduces the list to a single value.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __reducer__ [U (*)(U, T)] The reducer.
         * @param __initial_value__ [U] The initial value.
         * @param __result_ptr__ [U *] A reference to the variable to store the reduced value.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the result pointer is NULL.
         */
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
        /**
         * Public
         * 
         * Reduces the list to a single value.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __reducer__ [U (*)(U, T)] The reducer.
         * @param __initial_value__ [U] The initial value.
         * @param __result_ptr__ [U *] A reference to the variable to store the reduced value.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the result pointer is NULL.
         */
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
        /**
         * Public
         * 
         * Checks if any element in the list satisfies the condition.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __func__ [bool (*)(T)] The condition.
         * @return [bool] True if any element satisfies the condition, false otherwise.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         */
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
        /**
         * Public
         * 
         * Checks if any element in the list satisfies the condition.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __func__ [bool (*)(T)] The condition.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [bool] True if any element satisfies the condition, false otherwise.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         */
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
        /**
         * Public
         * 
         * Checks if any element in the list satisfies the condition.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __func__ [bool (*)(T)] The condition.
         * @param __result_ptr__ [bool *] A reference to the variable to store the result.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the result pointer is NULL.
         */
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
        /**
         * Public
         * 
         * Checks if any element in the list satisfies the condition.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __func__ [bool (*)(T)] The condition.
         * @param __result_ptr__ [bool *] A reference to the variable to store the result.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the result pointer is NULL.
         */
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
        /**
         * Public
         * 
         * Checks if all elements in the list satisfy the condition.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __func__ [bool (*)(T)] The condition.
         * @return [bool] True if all elements satisfy the condition, false otherwise.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         */
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
        /**
         * Public
         * 
         * Checks if all elements in the list satisfy the condition.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __func__ [bool (*)(T)] The condition.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [bool] True if all elements satisfy the condition, false otherwise.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         */
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
        /**
         * Public
         * 
         * Checks if all elements in the list satisfy the condition.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __func__ [bool (*)(T)] The condition.
         * @param __result_ptr__ [bool *] A reference to the variable to store the result.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the result pointer is NULL.
         */
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
        /**
         * Public
         * 
         * Checks if all elements in the list satisfy the condition.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __func__ [bool (*)(T)] The condition.
         * @param __result_ptr__ [bool *] A reference to the variable to store the result.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the result pointer is NULL.
         */
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
        /**
         * Public
         * 
         * Slices the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __start__ [size_t] The start index.
         * @param __end__ [size_t] The end index.
         * @param __step__ [size_t] The step.
         * @return [T *] The sliced list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the start index is out of bounds.
         * @throw [assert] If the end index is out of bounds.
         * @throw [assert] If the start index is greater than or equal to the end index.
         * @throw [assert] If the step is less than or equal to 0.
         */
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
        /**
         * Public
         * 
         * Slices the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __start__ [size_t] The start index.
         * @param __end__ [size_t] The end index.
         * @param __step__ [size_t] The step.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @return [T *] The sliced list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the start index is out of bounds.
         * @throw [assert] If the end index is out of bounds.
         * @throw [assert] If the start index is greater than or equal to the end index.
         * @throw [assert] If the step is less than or equal to 0.
         */
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
        /**
         * Public
         * 
         * Slices the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __start__ [size_t] The start index.
         * @param __end__ [size_t] The end index.
         * @param __step__ [size_t] The step.
         * @param __result_ptr__ [T **] A reference to the variable to store the sliced list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the start index is out of bounds.
         * @throw [assert] If the end index is out of bounds.
         * @throw [assert] If the start index is greater than or equal to the end index.
         * @throw [assert] If the step is less than or equal to 0.
         * @throw [assert] If the result pointer is NULL.
         */
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
        /**
         * Public
         * 
         * Slices the list.
         * @param __list_ptr__ [T **] A reference to the list.
         * @param __start__ [size_t] The start index.
         * @param __end__ [size_t] The end index.
         * @param __step__ [size_t] The step.
         * @param __result_ptr__ [T **] A reference to the variable to store the sliced list.
         * @param __list_element_type__ [type] The type of the elements in the list.
         * @throw [assert] If the reference to the list is NULL.
         * @throw [assert] If the list is NULL.
         * @throw [assert] If the start index is out of bounds.
         * @throw [assert] If the end index is out of bounds.
         * @throw [assert] If the start index is greater than or equal to the end index.
         * @throw [assert] If the step is less than or equal to 0.
         * @throw [assert] If the result pointer is NULL.
         */
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
