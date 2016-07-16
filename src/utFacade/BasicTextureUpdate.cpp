/*
 * Ubitrack - Library for Ubiquitous Tracking
 * Copyright 2006, Technische Universitaet Muenchen, and individual
 * contributors as indicated by the @authors tag. See the
 * copyright.txt in the distribution for a full listing of individual
 * contributors.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA, or see the FSF site: http://www.fsf.org.
 */

/**
* @ingroup api
* @file
* Simple datatypes for the \c SimpleFacade
*
* @author Ulrich Eck <ueck@net-labs.de>
*/

#include <utFacade/Config.h>
#ifdef ENABLE_BASICFACADE

#ifdef WIN32
#include <utUtil/CleanWindows.h>
#endif

#include "utFacade/BasicTextureUpdate.h"

#include <utVision/Image.h>
#include <utVision/OpenCLManager.h>
#include <utUtil/Exception.h>

#include <utFacade/BasicFacadeTypesPrivate.h>

#include <log4cpp/Category.hh>

#ifdef HAVE_OPENCL
#include <opencv2/core/ocl.hpp>
#ifdef __APPLE__
#include "OpenCL/opencl.h"
#include "OpenCL/cl_gl.h"
#else
#include "CL/cl.h"
#include "CL/cl_gl.h"
#endif
#endif

#include <GL/glut.h>

// get a logger
static log4cpp::Category& logger( log4cpp::Category::getInstance( "Ubitrack.Facade.BasicTextureUpdate" ) );

namespace Ubitrack {
namespace Facade {

/** private things */
class BasicTextureUpdatePrivate {
public:
    BasicTextureUpdatePrivate()
    : m_bTextureInitialized(false)
    , m_texture(0)
    , m_pow2Width(0)
    , m_pow2Height(0)
    {}

    bool m_bTextureInitialized;
    GLuint m_texture;

#ifdef HAVE_OPENCL
    //OpenCL
    cl_mem m_clImage;
    cv::UMat m_convertedImage;
#endif

    unsigned m_pow2Width;
    unsigned m_pow2Height;

};

bool getImageFormat(std::shared_ptr<BasicImageMeasurement>& image, bool use_gpu, int& umatConvertCode, GLenum& imgFormat, int& numOfChannels) {
    bool ret = true;
    switch ( image->getPixelFormat() ) {
    case BasicImageMeasurement::LUMINANCE:
        imgFormat = GL_LUMINANCE;
        numOfChannels = 1;
        break;
    case BasicImageMeasurement::RGB:
        numOfChannels = use_gpu ? 4 : 3;
        imgFormat = use_gpu ? GL_RGBA : GL_RGB;
        umatConvertCode = cv::COLOR_RGB2RGBA;
        break;
#ifndef GL_BGR_EXT
        case BasicImageMeasurement::BGR:
			imgFormat = image_isOnGPU ? GL_RGBA : GL_RGB;
			numOfChannels = use_gpu ? 4 : 3;
			umatConvertCode = cv::COLOR_BGR2RGBA;
			break;
#else
    case BasicImageMeasurement::BGR:
        numOfChannels = use_gpu ? 4 : 3;
        imgFormat = use_gpu ? GL_RGBA : GL_BGR_EXT;
        umatConvertCode = cv::COLOR_BGR2RGBA;
        break;
#endif
    case BasicImageMeasurement::RGBA:
        numOfChannels = 4;
        imgFormat = GL_RGBA;
        break;
    case BasicImageMeasurement::BGRA:
        numOfChannels = 4;
        imgFormat = use_gpu ? GL_RGBA : GL_BGRA;
        umatConvertCode = cv::COLOR_BGRA2RGBA;
        break;
    default:
        // Log Error ?
        ret = false;
        break;
    }
    return ret;
}




BasicTextureUpdate::BasicTextureUpdate() throw() : m_pPrivate( 0 )
{
    try
    {
        m_pPrivate = new BasicTextureUpdatePrivate();
        LOG4CPP_TRACE( logger, "BasicTextureUpdatePrivate created successfully" );
    }
    catch ( const Ubitrack::Util::Exception& e )
    {
        LOG4CPP_ERROR( logger, "Caught exception constructing BasicTextureUpdate: " << e );
    }
}


/*
 * Is Initialized ?
 */
bool BasicTextureUpdate::isInitialized() {
    if (m_pPrivate) {
        return m_pPrivate->m_bTextureInitialized;
    }
    return false;
}


/*
 * Get Texture ID
 */
unsigned int BasicTextureUpdate::getTextureId() {
    if (m_pPrivate) {
        return (unsigned int)m_pPrivate->m_texture;
    }
    return 0;
}


/*
 * Cleanup Texture - requires valid OpenGL Context
 */
void BasicTextureUpdate::cleanupTexture() {
    if (m_pPrivate) {
        if ( m_pPrivate->m_bTextureInitialized ) {
            glBindTexture( GL_TEXTURE_2D, 0 );
            glDisable( GL_TEXTURE_2D );
            glDeleteTextures( 1, &(m_pPrivate->m_texture) );
        }
    }
}

/*
 * Initialize Texture - requires valid OpenGL Context
 */
void BasicTextureUpdate::initializeTexture(std::shared_ptr<BasicImageMeasurement>& image) {
#ifdef HAVE_OPENCV
    if (m_pPrivate) {
       // access OCL Manager and initialize if needed
        Vision::OpenCLManager& oclManager = Vision::OpenCLManager::singleton();

        if (!image->m_pPrivate) {
            // LOG4CPP_WARN ??
            return;
        }

        // if OpenCL is enabled and image is on GPU, then use OCL codepath
        bool image_isOnGPU = oclManager.isEnabled() & image->m_pPrivate->m_measurement->isOnGPU();

        // find out texture format
        int umatConvertCode = -1;
        GLenum imgFormat = GL_LUMINANCE;
        int numOfChannels = 1;
        getImageFormat(image, image_isOnGPU, umatConvertCode, imgFormat, numOfChannels);

        if ( !m_pPrivate->m_bTextureInitialized )
        {


            // generate power-of-two sizes
            m_pPrivate->m_pow2Width = 1;
            while ( m_pPrivate->m_pow2Width < (unsigned)image->m_pPrivate->m_measurement->width() )
                m_pPrivate->m_pow2Width <<= 1;

            m_pPrivate->m_pow2Height = 1;
            while ( m_pPrivate->m_pow2Height < (unsigned)image->m_pPrivate->m_measurement->height() )
                m_pPrivate->m_pow2Height <<= 1;

            glGenTextures( 1, &(m_pPrivate->m_texture) );
            glBindTexture( GL_TEXTURE_2D, m_pPrivate->m_texture );

            // define texture parameters
            glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );

            // load empty texture image (defines texture size)
            glTexImage2D( GL_TEXTURE_2D, 0, numOfChannels, m_pPrivate->m_pow2Width, m_pPrivate->m_pow2Height, 0, imgFormat, GL_UNSIGNED_BYTE, 0 );
            LOG4CPP_DEBUG( logger, "glTexImage2D( width=" << m_pPrivate->m_pow2Width << ", height=" << m_pPrivate->m_pow2Height << " ): " << glGetError() );
            LOG4CPP_INFO( logger, "initalized texture ( " << imgFormat << " ) OnGPU: " << image_isOnGPU);


            if (oclManager.isInitialized()) {

#ifdef HAVE_OPENCL
                //Get an image Object from the OpenGL texture
                cl_int err;
                m_pPrivate->m_clImage = clCreateFromGLTexture( oclManager.getContext(), CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, m_pPrivate->m_texture, &err);
                if (err != CL_SUCCESS)
                {
                    LOG4CPP_ERROR( logger, "error at  clCreateFromGLTexture2D:" << err );
                }
#endif
            }
            m_pPrivate->m_bTextureInitialized = true;
        }
    }
#endif // HAVE_OPENCV
}

/*
 * Update Texture - requires valid OpenGL Context
 */
void BasicTextureUpdate::updateTexture(std::shared_ptr<BasicImageMeasurement>& image) {
#ifdef HAVE_OPENCV
    if (m_pPrivate) {
        // access OCL Manager and initialize if needed
        Vision::OpenCLManager& oclManager = Vision::OpenCLManager::singleton();

        if (!image->m_pPrivate) {
            // LOG4CPP_WARN ??
            return;
        }

        // if OpenCL is enabled and image is on GPU, then use OCL codepath
        bool image_isOnGPU = oclManager.isInitialized() & image->m_pPrivate->m_measurement->isOnGPU();

        if ( m_pPrivate->m_bTextureInitialized )
        {

            // find out texture format
            int umatConvertCode = -1;
            GLenum imgFormat = GL_LUMINANCE;
            int numOfChannels = 1;
            getImageFormat(image, image_isOnGPU, umatConvertCode, imgFormat, numOfChannels);

            if (image_isOnGPU) {
#ifdef HAVE_OPENCL

                glBindTexture( GL_TEXTURE_2D, m_pPrivate->m_texture );

                if (umatConvertCode != -1) {
                    cv::cvtColor(image->m_pPrivate->m_measurement->uMat(), m_pPrivate->m_convertedImage, umatConvertCode );
                } else {
                    m_pPrivate->m_convertedImage = image->m_pPrivate->m_measurement->uMat();
                }

                cv::ocl::finish();
                glFinish();

                cl_command_queue commandQueue = oclManager.getCommandQueue();
                cl_int err;

                clFinish(commandQueue);

                err = clEnqueueAcquireGLObjects(commandQueue, 1, &(m_pPrivate->m_clImage), 0, NULL, NULL);
                if(err != CL_SUCCESS)
                {
                    LOG4CPP_ERROR( logger, "error at  clEnqueueAcquireGLObjects:" << err );
                }

                cl_mem clBuffer = (cl_mem) m_pPrivate->m_convertedImage.handle(cv::ACCESS_READ);
                cl_command_queue cv_ocl_queue = (cl_command_queue)cv::ocl::Queue::getDefault().ptr();

                size_t offset = 0;
                size_t dst_origin[3] = {0, 0, 0};
                size_t region[3] = {static_cast<size_t>(m_pPrivate->m_convertedImage.cols), static_cast<size_t>(m_pPrivate->m_convertedImage.rows), 1};

                err = clEnqueueCopyBufferToImage(cv_ocl_queue, clBuffer, m_pPrivate->m_clImage, offset, dst_origin, region, 0, NULL, NULL);
                if (err != CL_SUCCESS)
                {
                    LOG4CPP_ERROR( logger, "error at  clEnqueueCopyBufferToImage:" << err );
                }

                err = clEnqueueReleaseGLObjects(commandQueue, 1, &m_pPrivate->m_clImage, 0, NULL, NULL);
                if(err != CL_SUCCESS)
                {
                    LOG4CPP_ERROR( logger, "error at  clEnqueueReleaseGLObjects:" << err );
                }
                cv::ocl::finish();


#else // HAVE_OPENCL
                LOG4CPP_ERROR( logger, "Image isOnGPU but OpenCL is disabled!!");
#endif // HAVE_OPENCL
            } else {
                // load image from CPU buffer into texture
                glBindTexture( GL_TEXTURE_2D, m_pPrivate->m_texture );
                glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, image->m_pPrivate->m_measurement->width(), image->m_pPrivate->m_measurement->height(),
                        imgFormat, GL_UNSIGNED_BYTE, image->m_pPrivate->m_measurement->Mat().data );

            }

        }
    }
#endif // HAVE_OPENCV
}

}
} // namespace Ubitrack::Facade

#endif // ENABLE_BASICFACADE