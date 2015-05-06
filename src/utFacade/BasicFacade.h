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
* Defines a basic interface to the ubitrack dataflow network.
* The main goal is making wrapping easy.
*
* @author Ulrich Eck <ueck@net-labs.de>
*/
#ifndef __UBITRACK_FACADE_BASICFACADE_H_INCLUDED__
#define __UBITRACK_FACADE_BASICFACADE_H_INCLUDED__
#include <utFacade/utFacade.h>
#include <utFacade/Config.h>

#include <string>
#include <memory>

#include "BasicFacadeTypes.h"
#include "BasicFacadeComponents.h"
// Do not add additional includes here

namespace Ubitrack {
    namespace Facade {


/**
* Provides a much simplified interface to the ubitrack library in a facade software design
* pattern fashion.
*
* The goal is to reduce dependencies on compiler-specific implementation details and to allow
* straightforward wrapping in host applications outside of C++3, like boost-python, julia, fabric-engine.
*
* This is an improved version of SimpleFacade
*
*/

        void initUbitrackLogging(basic_facade_string_type filename);

        class UTFACADE_EXPORT BasicFacade
        {
        public:
            /**
            * Initializes the Ubitrack library.
            *
            * @param sComponentPath Path to component directory. Uses default directory if none is specified
            */
            BasicFacade( basic_facade_string_type sComponentPath ) throw();

            /** destroys the data flow */
            ~BasicFacade();

            static unsigned long long int now();


            /**
            * Loads and instantiates a dataflow network from an XML file
            *
            * @param sDfSrg filename of dataflow description
            * @return true if successful
            */
            bool loadDataflow( basic_facade_string_type sDfSrg ) throw();

            /**
            * Loads and instantiates a dataflow network from a string
            *
            * @param sDataflow string containing the actual XML dataflow
            * @return true if successful
            */
            bool loadDataflowString( basic_facade_string_type sDataflow ) throw();

            /** removes all dataflow component instances */
            void clearDataflow() throw();


            /** starts components and the event queue */
            void startDataflow() throw();

            /** stops components and the event queue */
            void stopDataflow() throw();


            /**
            * connect to a ubitrack server.
            * @param sAddress format: <hostname> [":" <port>]
            */
            void connectToServer( basic_facade_string_type sAddress ) throw();

            /**
            * sends the contents of a file to a connected ubitrack server.
            */
            void sendUtqlToServer( basic_facade_string_type sUtqlFile ) throw();

            /**
            * sends a string to a connected ubitrack server.
            */
            void sendUtqlToServerString( basic_facade_string_type buffer ) throw();


            /**
            * Get notifications when new dataflow components are created or deleted
            *
            * @param pObserver pointer to a BasicDataflowObserver
            */
            void setDataflowObserver( BasicDataflowObserver* pObserver ) throw();

            /**
            * remove notifications when new dataflow components are created or deleted
            */
            void removeDataflowObserver() throw();

            /** returns the description of the last error or 0 if there was no error so far. */
            const char* getLastError() throw();


            /** returns a wrapper for an ApplicationPullSink with a type defined via BMT **/
            template< class BMT >
            std::shared_ptr<BasicPullSink< BMT > > getPullSink( basic_facade_string_type sName ) throw();

            /** returns a wrapper for an ApplicationPushSink with a type defined via BMT **/
            template< class BMT >
            std::shared_ptr<BasicPushSink< BMT > > getPushSink( basic_facade_string_type sName ) throw();

            /** returns a wrapper for an ApplicationPullsource with a type defined via BMT **/
            template< class BMT >
            std::shared_ptr<BasicPullSource< BMT > > getPullSource( basic_facade_string_type sName ) throw();

            /** returns a wrapper for an ApplicationPushSource with a type defined via BMT **/
            template< class BMT >
            std::shared_ptr<BasicPushSource< BMT > > getPushSource( basic_facade_string_type sName ) throw();

            void killEverything();

        protected:
            /**
            * Pointer to private data.
            *
            * The actual content is not declared here in order to avoid exposing the bad things (boost,
            * stl, etc.) to the application
            */
            BasicFacadePrivate* m_pPrivate;

            /** content of the last error message */
            char* m_sError;

            /** sets the internal error string */
            void setError( const char* sMsg ) throw();

        };


    } } // namespace Ubitrack::Facade

#endif
