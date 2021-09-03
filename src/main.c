#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

int main(void)
{
    dictionary *dict = create_dictionary();
    
    put(dict, "USA", "Wasington");
    put(dict, "Canada", "Ottawa");
    put(dict, "Austria", "Vienna");
    put(dict, "Azerbaijan", "Baki");

    char **key_s = key_set(dict);
    char **value_s = value_set(dict);
    for (int i = 0; i < dict->size; i++) {
        printf("KEY%i -> %s : VALUE%i -> %s\n", i, key_s[i], i, value_s[i]);
    }
    free_set(key_s, dict->size);
    free_set(value_s, dict->size);

    print_dict(dict);
    /* printf("%u\n", dict->size); */

    delete(dict, "Canada");
    delete(dict, "France");
    delete(dict, "USA");

    /* print_dict(dict); */
    /* printf("%u\n", dict->size); */

    put(dict, "Russia", "Moscow");
    put(dict, "Italy", "Rome");
    /* print_dict(dict); */

    
    /* printf("%s\n", get(dict, "Russia")); */
    
    /* printf("%i\n", contains_key(dict, "Italy")); */
    /* printf("%i\n", contains_value(dict, "Rome")); */

    /* printf("%i\n", contains_key(dict, "Japan")); */
    /* printf("%i\n", contains_value(dict, "Tokyo")); */

    put(dict, "Portugal", "Lisbon");
    
    /* printf("%s\n", get_or_default(dict, "Portugal", "Lisbon_d")); */
    /* printf("%s\n", get_or_default(dict, "Portu", "Lisbon_d")); */

    /* printf("%s\n", get(dict, "Portugal")); */
    replace(dict, "Portugal", "Lisbon_new");
    /* printf("%s\n", get(dict, "Portugal")); */

    free_dict(dict);
    return 0;
}


/*
  For testing:
  ------------
  USA -> Wasington,
  Russia -> Moscow,
  Austria -> Vienna,
  Brazil -> Brasilia,
  Portugal -> Lisbon
  England -> London,
  Canada -> Ottawa,
  France -> Paris,
  Italy -> Rome,
  Japan -> Tokyo
 */
