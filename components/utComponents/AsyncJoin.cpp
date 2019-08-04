//
// Created by netlabs on 8/1/19.
//

#include "AsyncJoin.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <utDataflow/ComponentFactory.h>
#include <utMath/Vector.h>
#include <utMath/Quaternion.h>
#include <utMath/Pose.h>
#include <utMath/Matrix.h>
#include <utUtil/TracingProvider.h>

#include <boost/array.hpp>

#include <log4cpp/Category.hh>



namespace Ubitrack { namespace Components {

        static log4cpp::Category& logger( log4cpp::Category::getInstance( "Components.AsyncJoin" ) );


        AsyncJoinModule::AsyncJoinModule( const AsyncJoinModuleKey& moduleKey, boost::shared_ptr< Graph::UTQLSubgraph >, FactoryHelper* pFactory )
                : Module< AsyncJoinModuleKey, AsyncJoinComponentKey, AsyncJoinModule, AsyncJoinComponentBase >( moduleKey, pFactory )
                , m_synchronizer( 60 ) // assume 60 Hz for timestamp synchronization
        {}


        AsyncJoinComponentBase::~AsyncJoinComponentBase()
        {
            LOG4CPP_INFO( logger, "Destroying AsyncJoin component" );
        }


        void AsyncJoinModule::startModule()
        {
            LOG4CPP_INFO( logger, "Creating AsyncJoin Component " << m_moduleKey.get() );

            // initialize data structures

            Module<AsyncJoinModuleKey, AsyncJoinComponentKey, AsyncJoinModule, AsyncJoinComponentBase>::startModule();
        }


        void AsyncJoinModule::stopModule()
        {
            LOG4CPP_INFO( logger, "Stopping AsyncJoin Component " << m_moduleKey.get() );

            Module<AsyncJoinModuleKey, AsyncJoinComponentKey, AsyncJoinModule, AsyncJoinComponentBase>::stopModule();

            // anything to do for teardown ?

        }


        void AsyncJoinModule::notifyIncomingMeasurement(const std::string& component_name, Ubitrack::Measurement::Timestamp ts) {

        }


        /* send Signmal */
        void AsyncJoinModule::sendSignal( int value, Ubitrack::Measurement::Timestamp ts)
        {

            // on the network the IDs are 0 based, in the DTrack software they are 1 based..
            AsyncJoinComponentKey key("notifier", AsyncJoinComponentKey::ComponentType::signal );

            // check for component
            if ( hasComponent( key ) )
            {
                getComponent( key )->getSignalPort( key ).send( pose );
            }
        }

        void AsyncJoinModule::setLatency(long int latency){
            m_latency = latency;
        }

        void AsyncJoinComponent::receiveLatency( const Measurement::Distance& m ) {
            double l = *m;
            LOG4CPP_INFO( logger , "AsyncJoinComponent received new latency measurement in ms: " << l );
            // convert ms to timestamp offset
            long int latency = (long int)(1000000.0 * l);
            getModule().setLatency(latency);
        };

        std::ostream& operator<<( std::ostream& s, const AsyncJoinComponentKey& k )
        {
            s << "AsyncJoinComponent[ " << k.getBody() << " "
              << k.getTargetType() << " ]";
            return s;
        }

// register module at factory
        UBITRACK_REGISTER_COMPONENT( ComponentFactory* const cf ) {
            cf->registerModule< AsyncJoinModule > ( "ArtTracker" );
        }

    } } // namespace Ubitrack::Drivers
