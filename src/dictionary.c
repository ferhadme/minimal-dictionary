#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

/*
 * Creates new dictionary
 * Can return NULL in case of memory allocation problem
 */
dictionary *create_dictionary()
{
    dictionary *dict = malloc(sizeof(dictionary));
    if (!dict)
        return NULL;
    
    for (int i = 0; i < BUCKET_SIZE; i++)
        dict->table[i] = NULL;
    
    dict->size = 0;
    return dict;
}

/*
 * Puts value with specified key into dictionary
 * Key duplications are ignored
 * Returns true if put is successful, otherwise (memory allocation problem) false
 */
bool put(dictionary *dict, const char *key, const char *data)
{
    if (contains_key(dict, key))
        return true;
    unsigned int index = hash(key);
    node *head = dict->table[index];

    node *new_node = malloc(sizeof(node));
    if (!new_node)
        return false;
    new_node->key = malloc(strlen(key) + 1);
    new_node->data = malloc(strlen(data) + 1);
    if (!new_node->key || !new_node->data)
        return false;

    strcpy(new_node->key, key);
    strcpy(new_node->data, data);

    new_node->next = head;
    dict->table[index] = new_node;
    dict->size++;
    return true;
}

/*
 * Gets value from dictionary with specified key
 * Returns NULL if there is no such key in dictionary
 */
char *get(dictionary *dict, const char *key)
{
    node *n = find_node(dict, key);
    return n ? n->data : NULL;
}

/*
 * Deletes value from dictionary with specified key
 * Returns true if deletion is successful, otherwise (no such key) false
 */
bool delete(dictionary *dict, const char *key)
{
    unsigned int index = hash(key);
    node *walker = dict->table[index];
    node *target = NULL;
    node *prev = NULL;

    while (walker) {
        if (strcmp(walker->key, key) == 0) {
            target = walker;
            break;
        }
        prev = walker;
        walker = walker->next;
    }

    if (!target)
        return false;
    
    // target - ...
    // ... - target - ...
    // ... - target
    walker = target->next;
    if (prev) {
        clean_node_from_mem(target);
        prev->next = walker;
    } else {
        clean_node_from_mem(target);
        dict->table[index] = walker;
    }
    dict->size--;
    
    return true;
}

/*
 * Finds node in dictionary with specified key
 */
static node *find_node(dictionary *dict, const char *key)
{
    unsigned int index = hash(key);
    node *head = dict->table[index];

    while (head) {
        if (strcmp(head->key, key) == 0)
            return head;
        head = head->next;
    }
    
    return head;
}

/*
 * Finds node in dictionary with specified value
 */
static node *find_node_v(dictionary *dict, const char *value)
{
    
    for (int i = 0; i < BUCKET_SIZE; i++) {
        node *head = dict->table[i];
        while (head) {
            if (strcmp(head->data, value) == 0)
                return head;
            head = head->next;
        }
    }

    return NULL;
}

/*
 * Clean node related data from memory
 */
static void clean_node_from_mem(node *n)
{
    free(n->key);
    free(n->data);
    free(n);
}

/*
 * Deletes all data from dictionary and memory
 */
void clear(dictionary *dict)
{
    for (int i = 0; i < BUCKET_SIZE; i++) {
        node *head = dict->table[i];
        while (head) {
            node *tmp = head;
            head = head->next;
            free(tmp->key);
            free(tmp->data);
            free(tmp);
        }
        dict->table[i] = NULL;
    }
    dict->size = 0;
}

/*
 * Checks whether dictionary contains specified key
 */
bool contains_key(dictionary *dict, const char *key)
{
    char *data = get(dict, key);
    return !data ? false : true;
}

/*
 * Checks whether dictionary contains at least one specified value (the same values can be stored with different keys)
 */
bool contains_value(dictionary *dict, const char *value)
{
    node *n = find_node_v(dict, value);
    return n ? true : false;
}

/*
 * Gets value from dictionary with specified key
 * Returns default_val if there is no such key in dictionary
 */
char *get_or_default(dictionary *dict, const char *key, const char *default_val)
{
    char *data = get(dict, key);
    return !data ? (char *) default_val : data;
}

/* 
 * Sets or replaces old value (paired with key) with new value
 * Returns old value if key is available, otherwise NULL
 */
char* replace(dictionary *dict, const char *key, const char *new_value)
{
    node *n = find_node(dict, key);
    if (!n)
        return NULL;
    
    n->data = realloc(n->data, strlen(new_value) + 1);
    strcpy(n->data, new_value);
    
    return n->key;
}

/*
 * Checks whether dictionary is empty or not
 */
bool empty(dictionary *dict)
{
    return dict->size == 0;
}

/*
 * Prints dictionary in JSON (almost) format
 */
void print_dict(dictionary *dict)
{
    printf("{\n");
    for (int i = 0; i < BUCKET_SIZE; i++) {
        node *head = dict->table[i];
        while (head) {
            printf("\t\"%s\": %s\n", head->key, head->data);
            head = head->next;
        }
    }
    printf("}\n");
}

/*
 * Hash function called djb2 for choosing slot in table
 * Source -> http://www.cse.yorku.ca/~oz/hash.html
 */
static unsigned int hash(const char *key)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % BUCKET_SIZE;
}
