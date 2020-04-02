#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <pthread.h>

#include "com_example_ObjectManipulation_MainActivity.h"

#define TAG "ObjectManipulation"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG, __VA_ARGS__)

/**
 * 四个函数实例化一个类
 * NewObject, NewObjectA, and NewObjectV. AllocObject
 *
 * 实例化一个未初始化的对象
 * jobject AllocObject(JNIEnv *env, jclass clazz);
 *
 * jobject NewObject(JNIEnv *env, jclass clazz,jmethodID methodID,...);
 *
 * jobject NewObjectA(JNIEnv *env, jclass clazz,jmethodID methodID,jvalue *args);
 *
 * jobject NewObjectV(JNIEnv *env, jclass clazz,jmethodID methodID,va_list args);
 * /

/*
 * Class:     com_example_ObjectManipulation_MainActivity
 * Method:    GetObjectClassDemo
 * Signature: (Lcom/example/ObjectManipulation/Persion;)Lcom/example/ObjectManipulation/Persion;
 */
JNIEXPORT jobject JNICALL Java_com_example_ObjectManipulation_MainActivity_GetObjectClassDemo
  (JNIEnv *env, jobject jobj, jobject persion)
{
	//jclass (*GetObjectClass)(JNIEnv*, jobject);
	jclass persionCls = (*env)->GetObjectClass(env,persion);
	jmethodID persion_construct = (*env)->GetMethodID(env,persionCls,"<init>","(Ljava/lang/String;I)V");
	jobject allocObj = (*env)->AllocObject(env, persionCls);
	return allocObj;
}

/*
 * Class:     com_example_ObjectManipulation_MainActivity
 * Method:    IsInstanceOfDemo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ObjectManipulation_MainActivity_IsInstanceOfDemo
  (JNIEnv *env, jobject jobj)
{
	jclass dummy = (*env)->FindClass(env,"com/example/ObjectManipulation/Dummy");
	jclass dummySub = (*env)->FindClass(env,"com/example/ObjectManipulation/DummySub");

	jmethodID dummy_construct = (*env)->GetMethodID(env,dummy,"<init>","()V");
	jmethodID dummySub_construct = (*env)->GetMethodID(env,dummySub,"<init>","()V");

    jobject dummy_obj = (*env)->NewObject(env,dummy,dummy_construct);
    jobject dummySub_obj = (*env)->NewObject(env,dummySub,dummySub_construct);

    LOGI("dummy_obj--->dummy %d",(*env)->IsInstanceOf(env,dummy_obj,dummy));                // 1
    LOGI("dummySub_obj--->dummySub %d",(*env)->IsInstanceOf(env,dummySub_obj,dummySub));    // 1
    LOGI("dummy_obj--->dummySub %d",(*env)->IsInstanceOf(env,dummy_obj,dummySub));          // 0
    LOGI("dummySub_obj--->dummy %d",(*env)->IsInstanceOf(env,dummySub_obj,dummy));          // 1
}

/*
 * Class:     com_example_ObjectManipulation_MainActivity
 * Method:    AllocObjectDemo
 * Signature: ()Lcom/example/ObjectManipulation/Persion;
 */
JNIEXPORT jobject JNICALL Java_com_example_ObjectManipulation_MainActivity_AllocObjectDemo
  (JNIEnv *env, jobject jobj)
{
	//jobject     (*AllocObject)(JNIEnv*, jclass);
	jclass persion = (*env)->FindClass(env,"com/example/ObjectManipulation/Persion");
    jobject persion_obj = (*env)->AllocObject(env,persion);
    return persion_obj;
}

/*
 * Class:     com_example_ObjectManipulation_MainActivity
 * Method:    NewObjectDemo
 * Signature: (Ljava/lang/String;I)Lcom/example/ObjectManipulation/Persion;
 */
JNIEXPORT jobject JNICALL Java_com_example_ObjectManipulation_MainActivity_NewObjectDemo
  (JNIEnv *env, jobject jobj, jstring jstr, jint age)
{
	jclass persion = (*env)->FindClass(env,"com/example/ObjectManipulation/Persion");
	jmethodID persion_construct = (*env)->GetMethodID(env,persion,"<init>","(Ljava/lang/String;I)V");
	jobject persion_obj = (*env)->NewObject(env,persion,persion_construct,jstr,age);

	return persion_obj;
}

/*
 * Class:     com_example_ObjectManipulation_MainActivity
 * Method:    NewObjectADemo
 * Signature: (Ljava/lang/String;I)Lcom/example/ObjectManipulation/Persion;
 */
JNIEXPORT jobject JNICALL Java_com_example_ObjectManipulation_MainActivity_NewObjectADemo
  (JNIEnv *env, jobject jobj, jstring jname, jint age)
{
	jclass persion = (*env)->FindClass(env,"com/example/ObjectManipulation/Persion");
	jmethodID persion_construct = (*env)->GetMethodID(env,persion,"<init>","(Ljava/lang/String;I)V");
	/**
	 * typedef union jvalue {
			jboolean    z;
			jbyte       b;
			jchar       c;
			jshort      s;
			jint        i;
			jlong       j;
			jfloat      f;
			jdouble     d;
			jobject     l;
		} jvalue;
	 * */
	//jobject (*NewObjectA)(JNIEnv*, jclass, jmethodID, jvalue*);
	jvalue args[2]; //定义union
	args[0].l = jname;
	args[1].i = age;
	jobject newObjA = (*env)->NewObjectA(env, persion, persion_construct, args);
	return newObjA;
}

static jobject newObjectVUtil(JNIEnv *env, ...)
{
  jclass persionCls = (*env)->FindClass(env,"com/example/ObjectManipulation/Persion");
  jmethodID persion_construct = (*env)->GetMethodID(env,persionCls,"<init>","(Ljava/lang/String;I)V");
  va_list arList;
  va_start(arList, env);
  //jobject (*NewObjectV)(JNIEnv*, jclass, jmethodID, va_list);
  jobject newObjV = (*env)->NewObjectV(env,persionCls,persion_construct, arList);
  va_end(arList);

  return newObjV;
}

/*
 * Class:     com_example_ObjectManipulation_MainActivity
 * Method:    NewObjectVDemo
 * Signature: (Ljava/lang/String;I)Lcom/example/ObjectManipulation/Persion;
 */
JNIEXPORT jobject JNICALL Java_com_example_ObjectManipulation_MainActivity_NewObjectVDemo
  (JNIEnv *env, jobject jobj, jstring jName, jint age)
{
	return newObjectVUtil(env, jName, age);
}

