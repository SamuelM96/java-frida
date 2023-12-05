#include "frida-core.h"

#include <jni.h>
#include <stdio.h>
#include <unistd.h>

static void on_message(FridaScript *script, const char *message, GBytes *data, gpointer user_data) {
	printf("Message from Frida: %s\n", message);
}

JNIEXPORT void JNICALL Java_FridaExample_executeFridaScript(JNIEnv *env, jobject obj,
							    jstring jscript, jint pid) {
	GError *error = NULL;

	printf("[*] Converting Java string to const char*\n");
	const char *script = (*env)->GetStringUTFChars(env, jscript, 0);

	printf("[*] Initialising frida\n");
	frida_init();

	printf("[*] Frida manager creation\n");
	FridaDeviceManager *manager = frida_device_manager_new();

	printf("[*] Getting a Frida device");
	FridaDevice *device = frida_device_manager_get_device_by_type_sync(
		manager, FRIDA_DEVICE_TYPE_LOCAL, 0, NULL, &error);
	if (error != NULL) {
		printf("Error getting device: %s\n", error->message);
		g_clear_error(&error);
		goto cleanup;
	}

	printf("[*] Frida session creation\n");
	FridaSessionOptions *sessionOptions = frida_session_options_new();
	FridaSession *session = frida_device_attach_sync(device, pid, sessionOptions, NULL, &error);
	if (error != NULL) {
		printf("Error attaching to device: %s\n", error->message);
		g_clear_error(&error);
		goto device_cleanup;
	}

	printf("[*] Frida script creation\n");
	FridaScript *frida_script =
		frida_session_create_script_sync(session, script, NULL, NULL, &error);
	if (error != NULL) {
		printf("Error creating script: %s\n", error->message);
		g_clear_error(&error);
		goto session_cleanup;
	}

	printf("[*] Connecting message callback\n");
	g_signal_connect(frida_script, "message", G_CALLBACK(on_message), NULL);

	printf("[*] Loading the following Frida script\n");
	printf("%s\n", script);

	frida_script_load_sync(frida_script, NULL, &error);
	if (error != NULL) {
		printf("Error loading script: %s\n", error->message);
		g_clear_error(&error);
		goto script_cleanup;
	}

	printf("Press Enter to exit...\n");
	getchar();

script_cleanup:
	g_object_unref(frida_script);

session_cleanup:
	g_object_unref(session);
	g_object_unref(sessionOptions);

device_cleanup:
	g_object_unref(device);

cleanup:
	g_object_unref(manager);
	frida_shutdown();

	printf("[*] Native string cleanup\n");
	(*env)->ReleaseStringUTFChars(env, jscript, script);

	fflush(stdout);
}
