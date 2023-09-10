#include <stdlib.h>
#include <stdint.h>

uint32_t hash(const char *str)
{
uint32_t hash=5381;
int i =0;
while (str[i]!='\0'){
    hash=(hash*33+str[i])%4294967296;
    i+=1;
}
return hash;
}
