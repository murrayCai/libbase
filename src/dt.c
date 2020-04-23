#include <stdio.h>
#include <string.h>
#include <time.h>

char _time_str_[64] = {0};
char *now_str(){
    time_t now = time(NULL);
    strftime(_time_str_,63,"%F %T",gmtime(&now));
    return _time_str_;
}
