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
