/*
 * Created by: Kenneth Lee (KALee)
 * Created on: May, 1993
 * jumble - finds permutations of letters
 *
 * Updated by: KALee
 * Updated on: 20-Apr-2009
 * Added ability to only display correctly spelled words by running each
 * word through the aspell spell checker available on Linux distibutions.
 * To compile, needed to get the aspell-devel libs to have the aspell.h 
 * header files available. 
 * 
 *
 */
 
#include <stdio.h>
#include <string.h>
#include "aspell.h"


void perm(char temp[], int r_value) {
  int count;
  char temp1[20];
  char temporary;
  int correct;

	// int correct = aspell_speller_check(spell_checker, word, size);
	AspellConfig * spell_config = new_aspell_config();
	aspell_config_replace(spell_config, "lang", "en_US");
  AspellCanHaveError * possible_err = new_aspell_speller(spell_config);
  AspellSpeller * spell_checker = 0;
  if (aspell_error_number(possible_err) != 0) {
    puts(aspell_error_message(possible_err));
  } else {
    spell_checker = to_aspell_speller(possible_err);
  }  

  // prints first case
  if (r_value==(strlen(temp)-1)) {
     correct = aspell_speller_check(spell_checker, temp, strlen(temp));
     if (correct > 0) {
	     printf("%s\n", temp);
	   }
	}
	
  for (count=r_value;count>=0;count--) {
     strcpy(temp1, temp);
     if (r_value != count) {
        temporary=temp1[count];
        temp1[count]=temp1[r_value];
        temp1[r_value]=temporary;
		    correct = aspell_speller_check(spell_checker, temp1, strlen(temp1));
		    if (correct > 0) {
	        printf("%s\n", temp1);
	      }  
     }
     if ((r_value-1)>0)
        perm(temp1,r_value-1);
  }
}

int main() {
  char data[20];
  printf("\nEnter letters to be unscrambled: ");
  scanf("%s", data);
  perm(data,strlen(data)-1);
  printf("\n");
}

