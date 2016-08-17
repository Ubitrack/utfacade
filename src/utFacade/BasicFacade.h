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

        void UTFACADE_EXPORT initUbitrackLogging(const char* filename);

        void UTFACADE_EXPORT initGPU();

        class UTFACADE_EXPORT BasicFacade
        {
        public:
            /*
            * Initializes the Ubitrack library.
            *
            * @param sComponentPath Path to component directory. Uses default directory if none is specified
            */
            BasicFacade( const char* sComponentPath, bool dropEvents=true ) throw();

            /** destroys the data flow */
            ~BasicFacade();

            static unsigned long long int now();


            /**
            * Loads and instantiates a dataflow network from an XML file
            *
            * @param sDfSrg filename of dataflow description
            * @return true if successful
            */
            bool loadDataflow( const char* sDfSrg ) throw();

            /**
            * Loads and instantiates a dataflow network from a string
            *
            * @param sDataflow string containing the actual XML dataflow
            * @return true if successful
            */
            bool loadDataflowString( const char* sDataflow ) throw();

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
            void connectToServer( const char* sAddress ) throw();

            /**
            * sends the contents of a file to a connected ubitrack server.
            */
            void sendUtqlToServer( const char* sUtqlFile ) throw();

            /**
            * sends a string to a connected ubitrack server.
            */
            void sendUtqlToServerString( const char* buffer ) throw();


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
            BasicPullSink< BMT >* getPullSink( const char* sName ) throw();

            /** returns a wrapper for an ApplicationPushSink with a type defined via BMT **/
            template< class BMT >
            BasicPushSink< BMT >* getPushSink( const char* sName ) throw();

            /** returns a wrapper for an ApplicationPullsource with a type defined via BMT **/
            template< class BMT >
            BasicPullSource< BMT >* getPullSource( const char* sName ) throw();

            /** returns a wrapper for an ApplicationPushSource with a type defined via BMT **/
            template< class BMT >
            BasicPushSource< BMT >* getPushSource( const char* sName ) throw();

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

#ifdef _WIN32

#ifdef UTFACADE_DLL
  #define UTFACADE_DLL_TCM template UTFACADE_EXPORT
#else
  #define UTFACADE_DLL_TCM extern template UTFACADE_EXPORT
#endif

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicScalarIntMeasurement >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicScalarIntMeasurement >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicScalarIntMeasurement >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicScalarIntMeasurement >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicScalarDoubleMeasurement >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicScalarDoubleMeasurement >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicScalarDoubleMeasurement >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicScalarDoubleMeasurement >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicVectorMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicVectorMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicVectorMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicVectorMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicVectorMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicVectorMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicVectorMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicVectorMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicVectorMeasurement< 4 > >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicVectorMeasurement< 4 > >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicVectorMeasurement< 4 > >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicVectorMeasurement< 4 > >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicVectorMeasurement< 8 > >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicVectorMeasurement< 8 > >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicVectorMeasurement< 8 > >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicVectorMeasurement< 8 > >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicMatrixMeasurement< 3, 3 > >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicMatrixMeasurement< 3, 3 > >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicMatrixMeasurement< 3, 3 > >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicMatrixMeasurement< 3, 3 > >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicMatrixMeasurement< 3, 4 > >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicMatrixMeasurement< 3, 4 > >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicMatrixMeasurement< 3, 4 > >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicMatrixMeasurement< 3, 4 > >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicMatrixMeasurement< 4, 4 > >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicMatrixMeasurement< 4, 4 > >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicMatrixMeasurement< 4, 4 > >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicMatrixMeasurement< 4, 4 > >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicPoseMeasurement >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicPoseMeasurement >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicPoseMeasurement >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicPoseMeasurement >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicRotationMeasurement >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicRotationMeasurement >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicRotationMeasurement >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicRotationMeasurement >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicErrorVectorMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicErrorVectorMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicErrorVectorMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicErrorVectorMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicErrorVectorMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicErrorVectorMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicErrorVectorMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicErrorVectorMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicErrorPoseMeasurement >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicErrorPoseMeasurement >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicErrorPoseMeasurement >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicErrorPoseMeasurement >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicCameraIntrinsicsMeasurement >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicCameraIntrinsicsMeasurement >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicCameraIntrinsicsMeasurement >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicCameraIntrinsicsMeasurement >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

#ifdef HAVE_OPENCV
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicImageMeasurement >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicImageMeasurement >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicImageMeasurement >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicImageMeasurement >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);
#endif

	// List Measurements
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicScalarIntListMeasurement >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicScalarIntListMeasurement >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicScalarIntListMeasurement >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicScalarIntListMeasurement >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicScalarDoubleListMeasurement >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicScalarDoubleListMeasurement >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicScalarDoubleListMeasurement >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicScalarDoubleListMeasurement >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicVectorListMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicVectorListMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicVectorListMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicVectorListMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicVectorListMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicVectorListMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicVectorListMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicVectorListMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicErrorVectorListMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicErrorVectorListMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicErrorVectorListMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicErrorVectorListMeasurement< 2 > >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicErrorVectorListMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicErrorVectorListMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicErrorVectorListMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicErrorVectorListMeasurement< 3 > >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicPoseListMeasurement >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicPoseListMeasurement >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicPoseListMeasurement >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicPoseListMeasurement >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSink  < Ubitrack::Facade::BasicErrorPoseListMeasurement >* Ubitrack::Facade::BasicFacade::getPullSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSink  < Ubitrack::Facade::BasicErrorPoseListMeasurement >* Ubitrack::Facade::BasicFacade::getPushSink(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPullSource< Ubitrack::Facade::BasicErrorPoseListMeasurement >* Ubitrack::Facade::BasicFacade::getPullSource(const char*);
UTFACADE_DLL_TCM Ubitrack::Facade::BasicPushSource< Ubitrack::Facade::BasicErrorPoseListMeasurement >* Ubitrack::Facade::BasicFacade::getPushSource(const char*);

#endif

#endif
