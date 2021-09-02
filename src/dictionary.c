#include <stdlib.h>
#include <stdbool.h>

#include "dictionary.h"

bool put(dictionary *dict, const char *key, const char *data)
{
    return false;
}

char *get(dictionary *dict, const char *key)
{
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
    return NULL;
}

char *replace_if_exists(dictionary *dict, const char *new_value)
{
    return NULL;
}

bool replace(dictionary *dict, const char *old_value, const char *new_value)
{
    return false;
}

char **to_array(dictionary *dict)
{
    return NULL;
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
