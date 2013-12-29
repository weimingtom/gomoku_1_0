LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

PROJECT_NAME := root

# PROJECT_NAME == root
ifeq ($(PROJECT_NAME),root)
CLASSES_PATH := ../Classes

LOCAL_SRC_FILES := hellocpp/main.cpp \
					$(CLASSES_PATH)/AppDelegate.cpp \
                   $(CLASSES_PATH)/HelloWorldScene.cpp \
                   $(CLASSES_PATH)/GameScene.cpp \
                   $(CLASSES_PATH)/MainmenuScene.cpp \
                   $(CLASSES_PATH)/game.cpp \
                   $(CLASSES_PATH)/chess.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(CLASSES_PATH)    
endif

##############

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
