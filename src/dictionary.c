#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

dictionary *create_dictionary()
{
    dictionary *dict = malloc(sizeof(dictionary));
    dict->size = 0;
    return dict;
}

bool put(dictionary *dict, const char *key, const char *data)
{
    if (contains_key(dict, key))
        return true;
    unsigned int index = hash(key);
    node *head = dict->table[index];

    node *new_node = malloc(sizeof(node));
    new_node->key = malloc(strlen(key));
    new_node->data = malloc(strlen(data));
    if (!new_node->key || !new_node->data)
        return false;

    strcpy(new_node->key, key);
    strcpy(new_node->data, data);

    new_node->next = head;
    dict->table[index] = new_node;
    dict->size++;
    return true;
}

char *get(dictionary *dict, const char *key)
{
    node *n = find_node(dict, key);
    return n ? n->data : NULL;
}

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

static node *find_node(dictionary *dict, const char *key)
{
    unsigned int index = hash(key);
    node *head = dict->table[index];

    while (head) {
        if (strcmp(head->key, key))
            return head;
        head = head->next;
    }

    return head;
}

void clean_node_from_mem(node *n)
{
    free(n->key);
    free(n->data);
    free(n);
}

void clear(dictionary *dict)
{
    
    return;
}

bool contains_key(dictionary *dict, const char *key)
{
    char *data = get(dict, key);
    return !data ? false : true;
}

bool contains_value(dictionary *dict, const char *value)
{
    for (int i = 0; i < BUCKET_SIZE; i++) {
        node *head = dict->table[i];
        while (!head) {
            if (strcmp(head->data, value) == 0)
                return true;
            head = head->next;
        }
    }
    return false;
}

char *get_or_default(dictionary *dict, const char *key, const char *default_val)
{
    char *data = get(dict, key);
    return !data ? (char *) default_val : data;
}

char *replace_if_exists(dictionary *dict, const char *new_value)
{
    return NULL;
}

bool replace(dictionary *dict, const char *old_value, const char *new_value)
{
    return false;
}

bool empty(dictionary *dict)
{
    return dict->size == 0;
}

char **to_array(dictionary *dict)
{
    return NULL;
}

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
