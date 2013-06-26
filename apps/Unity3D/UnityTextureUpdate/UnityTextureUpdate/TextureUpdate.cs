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

    }

    

}
