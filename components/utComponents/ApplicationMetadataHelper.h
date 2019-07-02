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
 * @ingroup dataflow_components
 * @file
 * helper class to support metadata for sink/source components
 *
 * @author ulrich eck <ulrich.eck@tum.de>
 */

#ifndef UBITRACK_FACADE_APPLICATIONMETADATAHELPER_H
#define UBITRACK_FACADE_APPLICATIONMETADATAHELPER_H

#include <string>
#include <iostream>

#include <utDataflow/Component.h>
#include <utDataflow/ComponentFactory.h>

namespace Ubitrack { namespace Components {

        using namespace Dataflow;

/**
 * @ingroup dataflow_components
 * This helper class is used to parse and provide access to sink/source metadata
 *
 */
        class ApplicationMetadata
        {
        public:
            /**
             * ApplicationMetaData constructor.
             *
             * @param subgraph UTQL subgraph
             */
            ApplicationMetadata( boost::shared_ptr< Graph::UTQLSubgraph> )
            {
            }


            const std::string& get_metadata_usage() {
                return m_metadata_usage;
            }

        protected:
            /**
             * Usage (free string).
             */
            std:string m_metadata_usage;

            /**
             * Domain (e.g. all objects belonging to the same domain are represented in the same coordinate space).
             */
            std:string m_metadata_domain;
        };


    } } // namespace Ubitrack::Components

#endif //UBITRACK_FACADE_APPLICATIONMETADATAHELPER_H
