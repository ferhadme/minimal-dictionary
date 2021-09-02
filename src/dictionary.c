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
    return NULL;
}

bool put(dictionary *dict, const char *key, const char *data)
{
    unsigned int index = hash(key);
    node *head = dict->table[index];

    node *new_node = malloc(sizeof(node));
    new_node->key = malloc(strlen(key));
    new_node->data = malloc(strlen(data));
    if (new_node->key == NULL || new_node->data == NULL)
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
    unsigned int index = hash(key);
    node *head = dict->table[index];
    while (head != NULL) {
        if (strcmp(head->key, key) == 0)
            return head->data;
        head = head->next;
    }
    return NULL;
}

bool delete(dictionary *dict, const char *key)
{
    return false;
}

void clear(dictionary *dict)
{
    return;
}

bool contains_key(dictionary *dict, const char *key)
{
    return false;
}

bool contains_value(dictionary *dict, const char *value)
{
    return false;
}

char *get_or_default(dictionary *dict, const char *key, const char *default_val)
{
    char *data = get(dict, key);
    return data == NULL ? default_val : data;
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
        while (head != NULL) {
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
