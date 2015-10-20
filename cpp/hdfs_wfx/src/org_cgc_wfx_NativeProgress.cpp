#include "org_cgc_wfx_NativeProgress.h"
#include "gendef.h"
#include "wfxplugin.h"

void JNICALL Java_org_cgc_wfx_NativeProgress_notifyProgress  (JNIEnv *env , jobject THIS, jlong ptr, jint progress)
{
    ProgressStructure* pregressStructure = (ProgressStructure*) ptr;
    if (pregressStructure != NULL){
        ((tProgressProc)pregressStructure->ptr)(pregressStructure->pluginNr, pregressStructure->source, pregressStructure->target, progress);
    }
}
