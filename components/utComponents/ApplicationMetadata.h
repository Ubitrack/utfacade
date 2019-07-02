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
#include <map>
#include <vector>

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
            ApplicationMetadata( boost::shared_ptr< Graph::UTQLSubgraph> pConfig)
            {
                // For now just copies all dataflow attributes from the component
                // it's up to the UTQL Pattern to define a standard/schema
                // once we know a good schema - we can enforce it.
                auto& attribute_map = pConfig->m_DataflowAttributes.map();
                for (auto it = attribute_map.begin(); it != attribute_map.end(); it++ ) {
                    m_metadata[it->first] = it->second.getText();
                }
            }

            /**
             * Get the metadata attribute for a key
             * This method returns the value associated to a specified key.
             *
             * @param key the key of the attribute
             * @return the value associated to the key
             * @throws Ubitrack::Util::Exception if no such key is known.
             */
            std::string getMetadataAttribute ( const std::string& key ) const  {
                auto it = m_metadata.find( key );
                if ( it == m_metadata.end() )
                    return m_metadata[key];
                UBITRACK_THROW("Invalid Metadata Attribute Key");
            }


            /**
             * Tests if the metadata attribute for a key is present
             * This method returns if for a given key there is
             * an attribute available.
             *
             * @param key the key of the attribute
             * @returns true if an attribute for that key is available. false otherwise
             */
            bool hasMetadataAttribute( const std::string& key ) {
                auto it = m_metadata.find( key );
                if ( it == m_metadata.end() )
                    return false;
                return true;
            }


            /**
             * Lista all registered metadata attribute keys.
             *
             * @param
             * @returns vector of strings containing the registered keys
             */
            std::vector<std::string> listMetadataAttributes( ) const {
                std::vector<std::string> result;
                for (auto it = m_metadata.begin(); it != m_metadata.end(); it++ ) {
                    result.emplace_back(it->first);
                }
                return std::move(result);
            }

        protected:
            /**
             * Metadata map (string:key => string:value).
             */
            std::map<std::string, std::string> m_metadata;
        };


    } } // namespace Ubitrack::Components

#endif //UBITRACK_FACADE_APPLICATIONMETADATAHELPER_H
