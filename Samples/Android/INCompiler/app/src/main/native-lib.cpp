#include <jni.h>
#include <string>
#include <ostream>
#include <iostream>

#include "../../../../../../Source/lib_math/lib_math.hpp"
#include "../../../../../../Source/compiler/compiler.hpp"

std::string jstring2str(JNIEnv* env, jstring jstr)
{
    char*   rtn   =   NULL;
    jclass   clsstring   =   env->FindClass("java/lang/String");
    jstring   strencode   =   env->NewStringUTF("UTF-8");
    jmethodID   mid   =   env->GetMethodID(clsstring,   "getBytes",   "(Ljava/lang/String;)[B");
    jbyteArray   barr=   (jbyteArray)env->CallObjectMethod(jstr,mid,strencode);
    jsize   alen   =   env->GetArrayLength(barr);
    jbyte*   ba   =   env->GetByteArrayElements(barr,JNI_FALSE);
    if(alen  >  0)
    {
        rtn   =   (char*)malloc(alen+1);
        memcpy(rtn,ba,alen);
        rtn[alen]=0;
    }
    env->ReleaseByteArrayElements(barr,ba,0);
    std::string stemp(rtn);
    free(rtn);
    return   stemp;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_sojex_cIndicator_Indicator_parseIndicator(JNIEnv *env, jclass claz, jobject vetor,
                                                jstring jstr) {
    std::map<string,string> cmap;
    std::vector<map<string,string>> mVector;
    jclass clazz = env->FindClass("java/util/ArrayList");
    jmethodID list_get  = env->GetMethodID(clazz,"get", "(I)Ljava/lang/Object;");
    jmethodID list_size  = env->GetMethodID(clazz,"size", "()I");
    int size = env->CallIntMethod(vetor,list_size);
    for (int i = 0; i < size; ++i) {
        jclass jmapclass = env->FindClass("java/util/HashMap");
        jobject maps = env->CallObjectMethod(vetor,list_get,i);
        jmethodID jkeysetmid = env->GetMethodID(jmapclass, "keySet", "()Ljava/util/Set;");
        jmethodID jgetmid = env->GetMethodID(jmapclass, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
        jobject jsetkey = env->CallObjectMethod(maps,jkeysetmid);
        jclass jsetclass = env->FindClass("java/util/Set");

        jmethodID jtoArraymid = env->GetMethodID(jsetclass, "toArray", "()[Ljava/lang/Object;");
        jobjectArray jobjArray = (jobjectArray)env->CallObjectMethod(jsetkey,jtoArraymid);
        jsize arraysize = env->GetArrayLength(jobjArray);
        int j=0;
        for( j=0; j < arraysize; j++ ){
            jstring jkey = (jstring)env->GetObjectArrayElement(jobjArray, j);
            jstring jvalue = (jstring)env->CallObjectMethod(maps,jgetmid,jkey);
            char* key = (char*)env->GetStringUTFChars(jkey,0);
            char* value = (char*)env->GetStringUTFChars(jvalue,0);
            cmap[key]=value;
            env->DeleteLocalRef(jkey);
            env->DeleteLocalRef(jvalue);
        }
        mVector.push_back(cmap);
        env->DeleteLocalRef(jmapclass);
        env->DeleteLocalRef(maps);
        env->DeleteLocalRef(jsetkey);
        env->DeleteLocalRef(jsetclass);
        env->DeleteLocalRef(jobjArray);
    }
    compiler compile(mVector);
    result result = compile.compile(jstring2str(env,jstr));
    map< string, vector<double> > maps = result.get_digit_values();
    map< string, vector< map<string, string> > > draTextMaps = result.get_draw_text_values();
    jclass hashMapClass = env->FindClass("java/util/HashMap");
    jmethodID hashMapInit = env->GetMethodID(hashMapClass,"<init>","()V");
    jobject  hashMapObj = env->NewObject(hashMapClass,hashMapInit);
    jmethodID  hashMapPut = env->GetMethodID(hashMapClass,"put","(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    for (auto it:maps){
        jclass resutItemLists = env->FindClass("java/util/ArrayList");
        jmethodID resultItemInit = env->GetMethodID(resutItemLists,"<init>","()V");
        jobject  resultListObj = env->NewObject(resutItemLists,resultItemInit);
        jmethodID listAddId = env->GetMethodID(resutItemLists,"add","(Ljava/lang/Object;)Z");
        vector<double> cItemList = it.second;
        int itemSize = cItemList.size();
        for (int i = 0; i < itemSize; ++i) {
            double cValue = cItemList[i];
            jclass doubleClass = env->FindClass("java/lang/Double");
            jmethodID doubleValueOf = env->GetStaticMethodID(doubleClass, "valueOf",
                                                             "(D)Ljava/lang/Double;");

            jobject  jValue = env->CallStaticObjectMethod(doubleClass, doubleValueOf,cValue);
            env->CallBooleanMethod(resultListObj,listAddId,jValue);
            env->DeleteLocalRef(jValue);
            env->DeleteLocalRef(doubleClass);
        }
        std::string key = it.first;
//        jstring jkey = str2jstring(env,key.data());
        jstring jkey = env->NewStringUTF(key.data());
        env->CallObjectMethod(hashMapObj,hashMapPut,jkey,resultListObj);
        env->DeleteLocalRef(jkey);
        env->DeleteLocalRef(resutItemLists);
        env->DeleteLocalRef(resultListObj);
    }

    //draTextValues
    jobject  draMapObject = env->NewObject(hashMapClass,hashMapInit);
    const char *jst = "";
    jstring jstrkey = NULL;
    jstring  jstrValue = NULL;
    for(auto it:draTextMaps){
        jclass resutItemLists = env->FindClass("java/util/ArrayList");
        jmethodID resultItemInit = env->GetMethodID(resutItemLists,"<init>","()V");
        jobject  resultListObj = env->NewObject(resutItemLists,resultItemInit);
        jmethodID listAddId = env->GetMethodID(resutItemLists,"add","(Ljava/lang/Object;)Z");
        vector<map<string, string>> cItemList = it.second;
        int itemSize = cItemList.size();
        string cKey = it.first;
        for (int i = 0; i < itemSize;i++){
            map<string,string> cItemMap = cItemList[i];
            jobject  itemMap = env->NewObject(hashMapClass,hashMapInit);
            for(auto cItValue:cItemMap){
                string cKey = cItValue.first;
                string cValue = cItValue.second;
                jstrkey = env->NewStringUTF(cKey.data());
                jstrValue = env->NewStringUTF(cValue.data());
                env->CallObjectMethod(itemMap,hashMapPut,jstrkey,jstrValue);
                env->DeleteLocalRef(jstrkey);
                env->DeleteLocalRef(jstrValue);
            }
            env->CallBooleanMethod(resultListObj,listAddId,itemMap);
            env->DeleteLocalRef(itemMap);
        }

        env->CallObjectMethod(draMapObject,hashMapPut,env->NewStringUTF(cKey.data()),resultListObj);
        env->DeleteLocalRef(resutItemLists);
        env->DeleteLocalRef(resultListObj);
    }
    jclass jResult = env->FindClass("org/sojex/cIndicator/Result");
    jmethodID jResultId = env->GetMethodID(jResult,"<init>","(Ljava/util/HashMap;Ljava/util/HashMap;)V");
    return env->NewObject(jResult,jResultId,hashMapObj,draMapObject);
}