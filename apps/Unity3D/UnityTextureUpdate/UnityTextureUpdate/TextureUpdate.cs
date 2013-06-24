using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using Ubitrack;

namespace UnityTextureUpdate
{
    public class TextureUpdate
    {

        [DllImport("OpenGLTextureUpdate")]
        private static extern float updateSubTextureRGBA32(int textureID, int xOffset, int yOffset, int width, int height, IntPtr buffer);
        [DllImport("OpenGLTextureUpdate")]
        private static extern float updateTextureRGBA32(int textureID, int width, int height, IntPtr buffer);

        public static unsafe void updateSubTextureRGBA(int textureID, int xOffset, int yOffset, int width, int height, Color32[] buffer)
        {
            fixed (Color32* colorPointer = buffer)
            {
                IntPtr ptr = (IntPtr)colorPointer;
                updateSubTextureRGBA32(textureID, xOffset, yOffset, width, height, ptr);

            }
        }

        public static unsafe void updateTextureRGBA(int textureID, int width, int height, Color32[] buffer)
        {
            fixed (Color32* colorPointer = buffer)
            {
                IntPtr ptr = (IntPtr)colorPointer;
                updateTextureRGBA32(textureID, width, height, ptr);

            }
        }
		


        public static unsafe void updateTextureUsingPointer(Color32[] colors, SimpleImage image, int texWidth, int texHeight, byte alpha)
        {

            fixed (Color32* colorPointer = colors)
            {
                IntPtr ptr = (IntPtr)colorPointer;                
                image.copyImageDataToARGB32Pointer(ptr, texWidth, texHeight, alpha);

            }
        }


        public static unsafe void updateTextureUsingPointerFlipVertical(Color32[] colors, SimpleImage image, int texWidth, int texHeight, byte alpha)
        {
            fixed (Color32* colorPointer = colors)
            {
                IntPtr ptr = (IntPtr)colorPointer;                
                image.copyImageDataToARGB32PointerFlipVertical(ptr, texWidth, texHeight, alpha);
            
            }

        }
/*
        public static unsafe void updateTextureUsingPointerFlipVertical(Color32[] colors, SimpleImage image, int texWidth, int texHeight, byte alpha)
        {
            IntPtr dataPointer = image.getDataPointer();
            byte* bytePointer = (byte*)dataPointer.ToPointer();
            fixed (Color32* colorPointer = colors)
            {
                
                for (int i = 0; i < image.height; i++)
                {
                    int baseStartindex = (image.height - i - 1) * image.width;
                    int baseOtherindex = i * texWidth;

                    for (int j = 0; j < image.width; j++)
                    {
                        int startindex = (baseStartindex + j) * 3;
                        int otherindex = (baseOtherindex + j);                                   

                        colorPointer[otherindex].b = bytePointer[startindex + 2];
                        colorPointer[otherindex].g = bytePointer[startindex + 1];
                        colorPointer[otherindex].r = bytePointer[startindex + 0];
                        colorPointer[otherindex].a = alpha;
                    }
                }
            }

        }*/

        


    }

    

}
