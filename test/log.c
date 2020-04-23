#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../src/base.h"

int f1(){
    RETURN_VAL_IF_CHECK_FAIL(1==0,1);
    return 0;
}

int main(int argc,char *argv[]){
    LOGD("test debug!\n");
    LOGI("test info!\n");
    LOGW("test warn!\n");
    LOGE("test error!\n");

    assert(1 == f1());

    return 0;
}
