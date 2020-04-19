#include <stdio.h>
#include <iostream>

// will print a messange and exit

[[ noreturn ]] inline void perror(const char* str, const int ret){
	fprintf(stderr, "%s, return = %d\n", str, ret);
}
