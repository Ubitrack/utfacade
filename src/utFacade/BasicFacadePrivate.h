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
#ifndef __UBITRACK_FACADE_BASICFACADEPRIVATE_H_INCLUDED__
#define __UBITRACK_FACADE_BASICFACADEPRIVATE_H_INCLUDED__

#include "BasicFacadeTypes.h"
#include "BasicFacade.h"

#include "AdvancedFacade.h"
#include "DataflowObserver.h"
#include "BasicFacadeComponentsPrivate.h"


namespace Ubitrack {
    namespace Facade {
        /** private things */
        class BasicFacadePrivate
                : public AdvancedFacade, public DataflowObserver
        {
        public:
            BasicFacadePrivate( basic_facade_string_type sComponentPath );

            // translate from DataflowObserver to SimpleDataflowObserver
            void notifyAddComponent( const std::string & sPatternName, const std::string & sComponentName, const Graph::UTQLSubgraph& );
            void notifyDeleteComponent( const std::string & sPatternName, const std::string & sComponentName );

            BasicDataflowObserver* m_pBasicObserver;
        };

    }
}


#endif // __UBITRACK_FACADE_BASICFACADEPRIVATE_H_INCLUDED__
