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
#ifdef HAVE_OPENCV

#include <utVision/OpenGLPlatform.h>

#include "utFacade/BasicTextureUpdate.h"

#include <utVision/Image.h>
#include <utVision/OpenCLManager.h>
#include <utUtil/Exception.h>
#include <utVision/TextureUpdate.h>

#include <utFacade/BasicFacadeTypesPrivate.h>

#include <log4cpp/Category.hh>


// get a logger
static log4cpp::Category& logger( log4cpp::Category::getInstance( "Ubitrack.Facade.BasicTextureUpdate" ) );

namespace Ubitrack {
namespace Facade {

/** private things */
class BasicTextureUpdatePrivate : public Vision::TextureUpdate {
public:
    BasicTextureUpdatePrivate() : Vision::TextureUpdate() {}
};



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
        return m_pPrivate->isInitialized();
    }
    return false;
}


/*
 * Get Texture ID
 */
unsigned int BasicTextureUpdate::getTextureId() {
    if (m_pPrivate) {
        return (unsigned int)m_pPrivate->textureId();
    }
    return 0;
}


/*
 * Pow2Width
 */
unsigned int BasicTextureUpdate::getPow2Width() {
    if (m_pPrivate) {
        return m_pPrivate->pow2width();
    }
    return 0;
}

/*
 * Pow2Height
 */
unsigned int BasicTextureUpdate::getPow2Height() {
    if (m_pPrivate) {
        return m_pPrivate->pow2height();
    }
    return 0;
}


/*
 * Cleanup Texture - requires valid OpenGL Context
 */
void BasicTextureUpdate::cleanupTexture() {
    if (m_pPrivate) {
        m_pPrivate->cleanupTexture();
    }
}


/*
 * Initialize Texture - requires valid OpenGL Context
 */
void BasicTextureUpdate::initializeTexture(std::shared_ptr<BasicImageMeasurement>& image) {

    if (m_pPrivate && image->m_pPrivate) {
        m_pPrivate->initializeTexture(image->m_pPrivate->m_measurement);
    }
}


/*
 * Update Texture - requires valid OpenGL Context
 */
void BasicTextureUpdate::updateTexture(std::shared_ptr<BasicImageMeasurement>& image) {
    if (m_pPrivate && image->m_pPrivate) {
        m_pPrivate->updateTexture(image->m_pPrivate->m_measurement);
    }
}
}
} // namespace Ubitrack::Facade

#endif // HAVE_OPENCV
#endif // ENABLE_BASICFACADE