#include "OpenGLTextureUpdate.h"

#include <GLES2/gl2.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define  LOG_TAG    "NDKImageRecorder"

#ifdef LOGI
#undef LOGI
#endif

#ifndef LOGE
#undef LOGE
#endif

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

void updateSubTextureRGBA32(int textureID, int xOffset, int yOffset, int width, int height, void* buffer){
		
		glBindTexture(GL_TEXTURE_2D, textureID);

	 // Update texture
	 //LOGE("glTexSubImage2D : %d , %d",, );
	 glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, width, height,
			 GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)buffer);
}

void updateTextureRGBA32(int textureID, int width, int height, void* buffer){

		glBindTexture(GL_TEXTURE_2D, textureID);

	 // Update texture
	 //LOGE("glTexSubImage2D : %d , %d",, );
		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)buffer);
}
