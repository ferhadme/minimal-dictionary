#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

int main(void)
{
    dictionary *dict = create_dictionary();

    put(dict, "Azerbaijan", "Baki");
    put(dict, "Japan", "Tokyo");
    put(dict, "Canada", "Ottawa");
    print_dict(dict);

    /* printf("%s\n", get(dict, "Japan")); */
    /* printf("%s\n", get_or_default(dict, "Germany", "Berlin")); */

    /* printf("contains_value? %i\n", contains_value(dict, "Baki")); */
    /* printf("contains_value? %i\n", contains_value(dict, "Bak")); */

    printf("delete? -> %i\n", delete(dict, "Japan"));
    printf("delete? -> %i\n", delete(dict, "Canada"));
    printf("delete? -> %i\n", delete(dict, "Germany"));
    print_dict(dict);
    
    free(dict);
    
    return 0;
}


/*
  For testing:
  ------------
  Azerbaijan -> Baki,
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
