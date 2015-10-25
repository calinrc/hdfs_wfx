#include "org_cgc_wfx_NativeProgress.h"
#include "ProgressInfo.h"

void JNICALL Java_org_cgc_wfx_NativeProgress_notifyProgress  (JNIEnv *env , jobject THIS, jlong ptr, jint progress)
{
    ProgressInfo* pregressStructure = (ProgressInfo*) ptr;
    if (pregressStructure != NULL){
        pregressStructure->call(progress);
    }
}
