

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

int valid(char *a){
	if((*a >= 'A') && (*a <= 'Z'))
		return 1;
	else if((*a >= 'a') && (*a <= 'z'))
		return 2;
	else
		return 0;
}


int matching(char *list, char *word, int len){
	for(int i = 0; i < len; i++){
		if(valid(list + i) == 1){
			*(list + i) += 32;
		}
		if(valid(word + i) == 1){
			*(word + i) += 32;
		}
		if(*(list + i) != *(word + i)){
			return 0;
		}
	}
	return 1;
}


int incorrect(char *dic, char *start, int len){
	int same; 
	int result;
	for(int i = 0; *(dic + i) != '\0'; i++){
		int first = i;
		same = 0;
		while(*(dic + i) != '\n'){
			i++;
			same++;
		}
		if(len == same){
			result = matching((dic + first), start, len);
			if(result)
				return 0;
		}
	}
	return 1;


}


void spellCheck(char article[], char dictionary[]) {

	char *first = article;			
	while(*first != '\0'){	 
		char *locate = first;
		int len = 0;
		int wrong = 0;
			while(valid(locate)){	
				len++;
				locate++;
			}
			if(len > 1){	
				char *back = first + len;
				wrong = incorrect(dictionary, first, len);
				if(wrong){	
					for (int i = 0; i < (back - first); i++){
						printf("%c", *(first + i));
					}
					printf("\n");
				}
			}
		first = locate + 1;
	}
}
