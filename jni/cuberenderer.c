/*
 *
 * Copyright 2006, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES/glext.h>

#include "include/es_anovagroup_moviles_modulo4_cubojni_jni_Natives.h"

// protos
void jni_printf(char *format, ...);
void jni_gl_swap_buffers ();


static void init_scene(void) {
    glDisable(GL_DITHER);

    /*
     * Some one-time OpenGL initialization can be made here
     * probably based on features of this particular context
     */
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_FASTEST);

    glClearColor(.5f, .5f, .5f, 1);

	glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
}

// Rotation Angle
static float mAngle = 0.0;

extern void Cube_draw();

static void drawFrame() {
    /*
	 * By default, OpenGL enables features that improve quality
	 * but reduce performance. One might want to tweak that
	 * especially on software renderer.
	 */
	glDisable(GL_DITHER);
	glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);

	/*
	 * Usually, the first thing one might want to do is to clear
	 * the screen. The most efficient way of doing this is to use
	 * glClear().
	 */

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	 * Now we're ready to draw some 3D objects
	 */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -3.0f);
	glRotatef(mAngle, 0, 0, 1.0f);
	glRotatef(mAngle*0.25f, 1, 0, 0);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	Cube_draw();

	glRotatef(mAngle*2.0f, 0, 1, 1);
	glTranslatef(0.5f, 0.5f, 0.5f);

	Cube_draw();

	mAngle += 1.2f;
}

/**
 * Send a string back to Java
 */
static jmethodID mSendStr;
static jclass jNativesCls;
static JavaVM *g_VM;

void jni_send_str(const char * text) {
	JNIEnv *env;

	if (!g_VM) {
		return;
	}

	(*g_VM)->AttachCurrentThread(g_VM, &env, NULL);

	if (!jNativesCls) {
		jNativesCls = (*env)->FindClass(env,
			"es/anovagroup/moviles/modulo4/cubojni/jni/Natives");

	}
	if (jNativesCls == 0) {
    		return;
	}

	// Call opengl.jni.Natives.OnMessage(String)
	if (! mSendStr) {
		mSendStr = (*env)->GetStaticMethodID(env, jNativesCls
			, "OnMessage"
			, "(Ljava/lang/String;)V");
	}
	if (mSendStr) {
	    (*env)->CallStaticVoidMethod(
				env, jNativesCls, mSendStr, (*env)->NewStringUTF(env, text));
	}
}

void jni_gl_swap_buffers () {
	JNIEnv *env;

	if (!g_VM) {
		return;
	}

	(*g_VM)->AttachCurrentThread(g_VM, &env, NULL);


	if (!jNativesCls) {
		jNativesCls = (*env)->FindClass(env, 
			"es/anovagroup/moviles/modulo4/cubojni/jni/Natives");

	}
	if (jNativesCls == 0) {
    		return;
	}

	// Call opengl.jni.Natives.OnMessage(String)
	jmethodID mid = (*env)->GetStaticMethodID(
			env, jNativesCls, "GLSwapBuffers", "()V");

	if (mid) {
		(*env)->CallStaticVoidMethod(env, jNativesCls, mid);
	}
}

void jni_printf(char *format, ...) {
	va_list argptr;
	static char string[1024];

	va_start (argptr, format);
	vsprintf (string, format,argptr);
	va_end (argptr);

	jni_send_str (string);
}

JNIEXPORT jint JNICALL 
Java_es_anovagroup_moviles_modulo4_cubojni_jni_Natives_NativeRender(
	JNIEnv * env, jclass cls) {

	(*env)->GetJavaVM(env, &g_VM);
	static int initialized = 0;

	if (!initialized) {
		jni_printf("Native:RenderTest initscene");
		init_scene();

		initialized = 1;
	}

	drawFrame();
	return 1;
}


