//
// Created by Ulrich Eck on 2019-08-05.
//

#ifndef UBITRACK_FACADE_APPLICATIONCOMPONENT_H
#define UBITRACK_FACADE_APPLICATIONCOMPONENT_H


#include <string>
#include <iostream>

#include <boost/bind.hpp>

#include <utDataflow/Component.h>
#include <utDataflow/ComponentFactory.h>

namespace Ubitrack { namespace Components {

        using namespace Dataflow;

/**
 * @ingroup dataflow_components
 * This is an base class for components which may be used to interface
 * the dataflow network to an user application.
 *
 * This component exposes basic / common information on the components for generic access / inspection of components.
 *
 * @par Input Ports
 * None.
 *
 * @par Output Ports
 * None.
 *
 * @par Configuration
 * TBD
 *
 * @par Operation
 * This base class provides access to attributes of the derived Push/Pull Sink/Source Components.
 *
 * @par Instances
 * None
 */
        class ApplicationComponent
                : public Component
        {
        public:
            /**
             * UTQL component constructor.
             *
             * @param sName Unique name of the component.
             * @param subgraph UTQL subgraph
             */
            ApplicationComponent( const std::string& nm, boost::shared_ptr< Graph::UTQLSubgraph> subgraph )
                    : Component( nm )
            {
                // For now just copies all dataflow attributes from the component
                // it's up to the UTQL Pattern to define a standard/schema
                // once we know a good schema - we can enforce it.
                auto& attribute_map = subgraph->m_DataflowAttributes.map();
                for (const auto & it : attribute_map) {
                    m_metadata[it.first] = it.second.getText();
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
                    UBITRACK_THROW("Invalid Metadata Attribute Key");
                return it->second;
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


            /** return a read-only version of the metadata attribute map for iterating */
            const std::map<std::string, std::string>& metadata_map() const
            { return m_metadata; }

            /**
             * Lists all registered metadata attribute keys.
             *
             * @param
             * @returns vector of strings containing the registered keys
             */
            std::vector<std::string> listMetadataAttributes( ) const {
                std::vector<std::string> result;
                for (const auto & it : m_metadata) {
                    result.emplace_back(it.first);
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

#endif //UBITRACK_FACADE_APPLICATIONCOMPONENT_H
