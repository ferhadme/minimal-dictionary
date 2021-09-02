#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

typedef struct node
{
    char *key;
    char *data;
    struct node *next;
} node;

/*
 * I've choosen 50 empty bucket for dictionary
 * But size can be changed without breaking code
 */
#define BUCKET_SIZE 50

typedef struct
{
    node *table[BUCKET_SIZE];
    unsigned int size;
} dictionary;

dictionary *create_dictionary();

bool put(dictionary *, const char *, const char *);

char *get(dictionary *, const char *);

bool delete(dictionary *, const char *);

void clear(dictionary *);

bool contains_key(dictionary *, const char *);

bool contains_value(dictionary *, const char *);

char *get_or_default(dictionary *, const char *, const char *);

char *replace_if_exists(dictionary *, const char *);

bool replace(dictionary *, const char *, const char *);

bool empty(dictionary *);

char **to_array(dictionary *);

void print_dict(dictionary *);

static unsigned int hash(const char *key);

#endif
