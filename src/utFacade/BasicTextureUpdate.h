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
* Texture Update for ImageMeasurements
*
* @author Ulrich Eck <ueck@net-labs.de>
*/
#ifndef UBITACK_BASICTEXTUREUPDATE_H
#define UBITACK_BASICTEXTUREUPDATE_H

#include <memory>
#include <vector>

#include <utFacade/utFacade.h>
#include <utFacade/Config.h>
#include <utFacade/BasicFacadeTypes.h>

namespace Ubitrack {
namespace Facade {

// forward declarations
class BasicTextureUpdatePrivate;

/*
 * Texture Update Helper
 */
class UTFACADE_EXPORT BasicTextureUpdate {
public:

    BasicTextureUpdate() throw() ;

    /*
     * Get Texture ID
     */
    unsigned int getTextureId();

    /*
     * Is Initialized ?
     */
    bool isInitialized();

    unsigned int getPow2Width();
    unsigned int getPow2Height();

    /*
     * Cleanup Texture - requires valid OpenGL Context
     */
    void cleanupTexture();

    /*
     * Initialize Texture - requires valid OpenGL Context
     */
    void initializeTexture(std::shared_ptr<BasicImageMeasurement>& image);

    /*
     * Update Texture - requires valid OpenGL Context
     */
    void updateTexture(std::shared_ptr<BasicImageMeasurement>& image);

private:
    BasicTextureUpdatePrivate* m_pPrivate;
};

}
}// namespace Ubitrack::Facade

#endif //UBITACK_BASICTEXTUREUPDATE_H
