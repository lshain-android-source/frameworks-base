
#define LOG_TAG "FregService"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <stdlib.h>
#include <utils/misc.h>
#include <utils/Log.h>
#include <hardware/hardware.h>
#include <hardware/freg.h>

namespace android {

int fregInit( JNIEnv* env, jobject jclsss ){
	struct freg_module_t* module = NULL;
	int re = hw_get_module( FREG_HARDWARE_DEVICE_ID, (const struct hw_module_t**)&module );
	if( re != 0 ){
		ALOGE( "fregInit get module faild!\n" );
		return 0;
	}

	struct freg_device_t* device = NULL;
	re = module->common.methods->open( (struct hw_module_t*)module, FREG_HARDWARE_DEVICE_ID, (struct hw_device_t**)&device );
	if( re != 0 ){
		ALOGE( "fregInit open device faild!\n" );
		return 0;
	}

	return (int)device;
}

void fregSetVal( JNIEnv* env, jobject jclsss, jint device, jint val ){
    if( device != 0 ){
		freg_device_t* dev = (freg_device_t*)device;

		ALOGE( "fregSetVal val = %d\n", val );
		dev->setVal( dev, val );
	}
}

jint fregGetVal( JNIEnv* env, jobject jclsss, jint device ){
    if( device == 0 ){
		ALOGE( "fregGetVal faild!\n ");
		return 0;
	}

	freg_device_t* dev = (freg_device_t*)device;

	int val = 0;
	dev->getVal( dev, &val );

	ALOGE( "fregGetVal val = %d\n", val );

	return val;
}

static JNINativeMethod method_table[] = {
    { "initNative", "()I", (void *)fregInit },
    { "setValNative", "(II)V", (void *)fregSetVal },
    { "getValNative", "(I)I", (void *)fregGetVal },
};

int register_android_server_FregService(JNIEnv *env) {
    return jniRegisterNativeMethods(env, "com/android/server/FregService",
									method_table, NELEM(method_table));
}

}
