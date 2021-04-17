#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mc.h"

int f1(){
    int ret = 0;
    M(1 != 0,1);
    return 0;
}


int main(int argc,char *argv[]){
    int ret = 0;
    LOGD("test debug,%d!\n",1==2);
    LOGI("test info!\n");
    LOGW("test warn!\n");
    LOGE("test error!\n");

    int test = 10;
    GC(f1(),end,({printf("test:%d\n",test);}));
    RC(f1(),({printf("test:%d\n",test);}));

end:
    printf("%d\n%d\n",ERRNO(ERR_PARAM,1), f1());

    return 0;
}
