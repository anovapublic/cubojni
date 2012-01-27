LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := cubojni
LOCAL_SRC_FILES := cube.c cuberenderer.c
LOCAL_LDLIBS    := -lEGL -lGLESv1_CM
include $(BUILD_SHARED_LIBRARY)
