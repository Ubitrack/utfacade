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
 * Sink component with push input port
 * This files contains an sink component with which the application
 * can interface which uses an PushConsumer input port and calls
 * an application registered callback.
 *
 * @author Ulrich Eck <ueck@net-labs.de>
 */
#ifndef __UBITRACK_COMPONENTS_APPLICATIONPULLSOURCE_H_INCLUDED__
#define __UBITRACK_COMPONENTS_APPLICATIONPULLSOURCE_H_INCLUDED__

// does not require applications to know log4cpp then
#define APPLICATIONPULLSOURCE_NOLOGGING

#include <string>
#include <iostream>

#include <boost/bind.hpp>

#include <utDataflow/PullSupplier.h>
#include <utDataflow/Component.h>
#include <utMeasurement/Measurement.h>
#include <utUtil/SimpleStringOArchive.h>
#include <utUtil/TracingProvider.h>

// no counterpart in SimpleFacade yet
//#include <utFacade/SimpleDatatypes.h>
#ifndef APPLICATIONPUSHSINK_NOLOGGING
#include <log4cpp/Category.hh>
#endif

// forward decls
namespace Ubitrack {
	namespace Graph {
		class UTQLSubgraph;
	}
}


namespace Ubitrack { namespace Components {

using namespace Dataflow;

/**
 * Common base class for application push sinks.
 * Allows setting string receivers.
 */
class ApplicationPullSourceBase
{
public:
	/** sets a SimplePoseReceiver */
	// no counterpart in SimpleFacade yet
	//virtual void setStringCallback( Facade::SimpleStringReceiver* pReceiver ) = 0;

	/** virtual destructor. always good to have one. */
	virtual ~ApplicationPullSourceBase()
	{}
};


/**
 * @ingroup dataflow_components
 * This is an source component which may be used to interface
 * the dataflow network to an user application.
 *
 * This source uses a pull output port and calls a callback
 * function supplied by the application upon the request of
 * a new event.
 *
 * @par Input Ports
 * None.
 *
 * @par Output Ports
 * PullSupplier<EventType> port with name "Output".
 *
 * @par Configuration
 * None.
 *
 * @par Operation
 * Whenever the dataflow network pulls a new event from the
 * PullSupplier of the ApplicationPullSource the class calls
 * the callback the user application has registered via
 * setCallback.
 *
 */
template <class EventType>
class ApplicationPullSource
	: public Component
	, public ApplicationPullSourceBase
{
public:
	/**
	 * UTQL component constructor.
	 *
	 * @param sName Unique name of the component.
	 * @param subgraph UTQL subgraph
	 */
	ApplicationPullSource( const std::string& nm, boost::shared_ptr< Graph::UTQLSubgraph >  )
		: Ubitrack::Dataflow::Component( nm )
		, m_OutPort( "Output", *this, boost::bind( &ApplicationPullSource::request, this, _1 ) )
		, m_callback( 0 )
#ifndef APPLICATIONPULLSOURCE_NOLOGGING
		, m_logger( log4cpp::Category::getInstance( "Ubitrack.Components.ApplicationPullSource" ) )
#endif
	{
	}

	/**
	 * Set the callback.
	 * Set the callback in the user application which will be called for
	 * requested events.
	 * @param slot callback function of the user application.
	 */
	void setCallback ( typename PullSupplier< EventType >::FunctionType cb )
	{
		m_callback = cb;
	}

	/** sets a string receiver */
	// no counterpart in SimpleFacade yet
	// void setStringCallback( Facade::SimpleStringReceiver* pReceiver )
	// {
	// 	m_callback = boost::bind( &ApplicationPullSource< EventType >::sendString, _1, pReceiver );
	// }

protected:
	/**
	 * Handler method for pull supplier
	 * This is the handler method for the output port.
	 * Pulls any incoming event from the application if callback is
	 * already registered.
	 * @param t timestamp of requested event.
	 * @todo calls user code. wrap with try{} block..
	 */
	EventType request( Measurement::Timestamp t )
	{ 
#ifndef APPLICATIONPULLSOURCE_NOLOGGING
		LOG4CPP_DEBUG( m_logger, getName() << " requested event" );
#endif
		if( m_callback ) {
#ifdef ENABLE_EVENT_TRACING
			TRACEPOINT_MEASUREMENT_CREATE(getEventDomain(), t, getName().c_str(), "PullSource")
#endif

			return m_callback( t );
		}

#ifndef APPLICATIONPULLSOURCE_NOLOGGING
		else
			LOG4CPP_INFO( m_logger, "ApplicationPullSource " << getName() << " has no consumer connected" );
#endif
		UBITRACK_THROW( "ApplicationPullSource has no consumer connected" );
	}	
	
	/** converts events to string */
	// no counterpart in SimpleFacade yet
	// static void sendString( const EventType& m, Facade::SimpleStringReceiver* pReceiver )
	// {
	// 	Util::SimpleStringOArchive ar;
	// 	ar << m;
	// 	std::string s( ar.str() );
	// 	pReceiver->receiveString( s.c_str() );
	// }
	
	/** Input port of the function. */
	PullSupplier< EventType > m_OutPort;

	/** Type of the callback functions */
	typename PullSupplier< EventType >::FunctionType m_callback;

#ifndef APPLICATIONPULLSOURCE_NOLOGGING
	/** reference to logger */
	log4cpp::Category& m_logger;
#endif
};


// @ todo complete ApplicationPullSource definitions
typedef ApplicationPullSource< Measurement::Button > ApplicationPullSourceButton;
typedef ApplicationPullSource< Measurement::Pose > ApplicationPullSourcePose;
typedef ApplicationPullSource< Measurement::ErrorPose > ApplicationPullSourceErrorPose;
typedef ApplicationPullSource< Measurement::Position > ApplicationPullSourcePosition;
typedef ApplicationPullSource< Measurement::Position2D > ApplicationPullSourcePosition2D;
typedef ApplicationPullSource< Measurement::Position > ApplicationPullSourceErrorPosition;
typedef ApplicationPullSource< Measurement::Position2D > ApplicationPullSourceErrorPosition2D;
typedef ApplicationPullSource< Measurement::Rotation > ApplicationPullSourceRotation;
typedef ApplicationPullSource< Measurement::PositionList > ApplicationPullSourcePositionList;
typedef ApplicationPullSource< Measurement::PositionList2 > ApplicationPullSourcePositionList2;
typedef ApplicationPullSource< Measurement::Matrix4x4 > ApplicationPullSourceMatrix4x4;
typedef ApplicationPullSource< Measurement::Matrix3x3 > ApplicationPullSourceMatrix3x3;
typedef ApplicationPullSource< Measurement::Matrix3x4 > ApplicationPullSourceMatrix3x4;
typedef ApplicationPullSource< Measurement::ErrorPositionList > ApplicationPullSourceErrorPositionList;
typedef ApplicationPullSource< Measurement::ErrorPositionList2 > ApplicationPullSourceErrorPositionList2;
} } // namespace Ubitrack::Components
#endif //__UBITRACK_COMPONENTS_APPLICATIONPULLSOURCE_H_INCLUDED__

