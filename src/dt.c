#include <stdio.h>
#include <string.h>
#include <time.h>

char _time_str_[64] = {0};
char *now_str(){
    time_t now = time(NULL);
    strftime(_time_str_,63,"%F %T",gmtime(&now));
    return _time_str_;
}

int get_days_of_month(int year,int month){
    if( 2 == month){
        if(0 == year % 4){
            if( 0 == year % 100 ){
                return 0 == year % 400 ? 29 : 28;
            }else{
                return 29;
            }
        }else{
            return 28;
        }
    }

    if(4 == month || 6 == month || 9 == month || 11 == month){
        return 30;
    }else{
        return 31;
    }
}
