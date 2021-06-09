#include "mc.h"

#ifdef MODULE_CURR
#undef MODULE_CURR
#define MODULE_CURR MODULE_DT
#endif

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

int timeval_diff(struct timeval *tv0,struct timeval *tv1,double *diff){
    int ret = 0;
    R(NULL == tv0);
    R(NULL == tv1);
    double time1, time2;

    time1 = tv0->tv_sec + (tv0->tv_usec / 1000000.0);
    time2 = tv1->tv_sec + (tv1->tv_usec / 1000000.0);

    (*diff) = time1 - time2;
    if((*diff) < 0) (*diff) = -1 * (*diff);

    return ret;
} 
