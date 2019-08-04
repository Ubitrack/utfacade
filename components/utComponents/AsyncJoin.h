//
// Created by netlabs on 8/1/19.
//

#ifndef UBITRACK_COMPONENT_CORE_ASYNCJOIN_H
#define UBITRACK_COMPONENT_CORE_ASYNCJOIN_H

#include <string>
#include <cstdlib>

#include <utDataflow/PushSupplier.h>
#include <utDataflow/PushConsumer.h>
#include <utDataflow/Component.h>
#include <utDataflow/Module.h>
#include <utMeasurement/Measurement.h>
#include <utMeasurement/TimestampSync.h>

namespace Ubitrack { namespace Components {

        using namespace Dataflow;

// forward declaration
        class AsyncJoinComponentBase;

/**
 * Domain name - groups components into a domain that is joined.
 */
        MAKE_DATAFLOWCONFIGURATIONATTRIBUTEKEY_DEFAULT( AsyncJoinModuleKey, std::string, "asyncJoinDomain", "domain0" );

/**
 * Component key for art.
 * Represents the body number
 */
        class AsyncJoinComponentKey
        {
        public:
            enum ComponentType { invalid, signal, buffer };

            AsyncJoinComponentKey( boost::shared_ptr< Graph::UTQLSubgraph > subgraph )
                    : m_name( "input_" )
            {
                Graph::UTQLSubgraph::EdgePtr config;
                m_name = config->getAttributeString( "inputName" );
                if ( m_name.empty() )
                {
                    m_name = "input_unknown";
                }
                std::string ct = config->getAttributeString( "componentType" );
                if (ct == "signal") {
                    m_componentType = ComponentType ::signal;
                } else if (ct == "buffer") {
                    m_componentType = ComponentType ::buffer;
                } else {
                    LOG4CPP_WARN(logger, "Unknown componentType: " << ct);
                    m_componentType = ComponentType ::invalid;
                }

            }

            // construct from name, type
            AsyncJoinComponentKey( const std::string& s , ComponentType t)
                    : m_name( s )
                    , m_componentType( t )
            {}

            std::string getName() const
            {
                return m_name;
            }

            ComponentType getComponentType() const
            {
                return m_componentType;
            }

            // less than operator for map
            bool operator<( const AsyncJoinComponentKey& b ) const
            {
               if ( m_componentType == b.m_componentType )
                    return m_name < b.getName();
                else
                    return m_componentType < b.m_componentType;
            }
            
        protected:
            std::string m_name;
            ComponentType m_componentType;
        };

        std::ostream& operator<<( std::ostream& s, const AsyncJoinComponentKey& k );

/**
 * Module for AsyncJoin Logic.
 * Manages the synchronization of incoming messages
 */
        class AsyncJoinModule
                : public Module< AsyncJoinModuleKey, AsyncJoinComponentKey, AsyncJoinModule, AsyncJoinComponentBase >
        {
        public:
            /** UTQL constructor */
            AsyncJoinModule( const AsyncJoinModuleKey& key, boost::shared_ptr< Graph::UTQLSubgraph >, FactoryHelper* pFactory );

            /** destructor */
            ~AsyncJoinModule() = default;

            void startModule() override;

            void stopModule() override;

            void notifyIncomingMeasurement(const std::string& component_name, Ubitrack::Measurement::Timestamp ts);
            
        protected:

            Measurement::TimestampSync m_synchronizer;

        private:
            void sendSignal( int value, Ubitrack::Measurement::Timestamp ts );
        };


/**
 * Component for Async Join logic.
 * Is a buffer, that notifies the Module upon reception of measurement

 */
        class AsyncJoinComponentBase
                : public AsyncJoinModule::Component
        {
        public:
            /** constructor */
            AsyncJoinComponentBase( const std::string& name, boost::shared_ptr< Graph::UTQLSubgraph > subgraph, const AsyncJoinComponentKey& componentKey, AsyncJoinModule* pModule )
                    : AsyncJoinModule::Component( name, componentKey, pModule )
            {}

            /** destructor */
            ~AsyncJoinComponentBase();




            void notifyIncomingMeasurement(Ubitrack::Measurement::Timestamp ts) {
                    getModule().notifyIncomingMeasurement(m_name, ts);
            }
            
        protected:
        };


        template< class EventType >
        class AsyncJoinComponent : public AsyncJoinComponentBase {
        public:
            /**
             * UTQL component constructor.
             *
             * @param nm Unique name of the component.
             * @param cfg UTQL subgraph
             */
            AsyncJoinComponent( const std::string& sName, boost::shared_ptr< Graph::UTQLSubgraph > subgraph, const AsyncJoinComponentKey& componentKey, AsyncJoinModule* pModule )
                    : AsyncJoinComponentBase( subgraph, componentKey, pModule )
                    , m_inPort( "Input", *this, boost::bind( &Buffer< EventType >::eventIn, this, _1 ) )
                    , m_outPort( "Output", *this,boost::bind( &Buffer< EventType >::eventOut, this, _1 ) )
                    , m_eventCounter( 0 )
                    , m_maxAge( 0 )
                    , m_eventsLogger( log4cpp::Category::getInstance( "Ubitrack.Events.Components.Buffer" ) )
            {
                unsigned long ms = 0;
                subgraph->m_DataflowAttributes.getAttributeData( "maxAge", ms );
                ms *= 1000000;
                m_maxAge = ms;
            }

        protected:
            /**
             * Handler method for input port
             * Receives an event and stores it.
             * @param m the received event
             */
            void eventIn( const EventType& m )
            {
                m_event = m;
                if ( m_eventCounter < 1 )
                    m_eventCounter++;
                // notify module about incoming message.
                notifyIncomingMeasurement(m.time());
            }

            /**
             * Handler method for the output port.
             * Sends the last received event as the requested one.
             * @param t the Timestamp of the requested event.
             * @return the requested event.
             * @throws Ubitrack::Util::Exception if buffer is still empty
             */
            EventType eventOut( Ubitrack::Measurement::Timestamp t )
            {
                if ( m_eventCounter < 1 )
                {
                    LOG4CPP_DEBUG( m_eventsLogger, getName() << " not enough data in buffer" );
                    UBITRACK_THROW( "not enough data in buffer" );
                }
                if ( m_maxAge && m_event.time() + m_maxAge < t )
                {
                    LOG4CPP_DEBUG( m_eventsLogger, getName() << " buffered measurement too old" );
                    UBITRACK_THROW( "Buffered measurement too old" );
                }
                return EventType( t, m_event );
            }

            /** Input port of the component. */
            Dataflow::PushConsumer< EventType > m_inPort;
            /** Output port of the component. */
            Dataflow::PullSupplier< EventType > m_outPort;

            /** Buffer variable containing the last received event. */
            EventType m_event;

            /** Counter to check if an event was already received. */
            int m_eventCounter;

            /** maximum age of events in ns */
            Measurement::Timestamp m_maxAge;

            /** logger */
            log4cpp::Category& m_eventsLogger;


        };


        typedef AsyncJoinComponent< Measurement::Button > SkalarAsyncJoinComponent;
        typedef AsyncJoinComponent< Measurement::Distance > DistanceAsyncJoinComponent;

        typedef AsyncJoinComponent< Measurement::Position2D > Position2AsyncJoinComponent;
        typedef AsyncJoinComponent< Measurement::Position > PositionAsyncJoinComponent;
        typedef AsyncJoinComponent< Measurement::Pose > PoseAsyncJoinComponent;

        typedef AsyncJoinComponent< Measurement::ErrorPosition2 > ErrorPosition2AsyncJoinComponent;
        typedef AsyncJoinComponent< Measurement::ErrorPosition > ErrorPositionAsyncJoinComponent;
        typedef AsyncJoinComponent< Measurement::ErrorPose > ErrorPoseAsyncJoinComponent;

        typedef AsyncJoinComponent< Measurement::Rotation > RotationAsyncJoinComponent;

        typedef AsyncJoinComponent< Measurement::Matrix3x3 > Matrix3x3AsyncJoinComponent;
        typedef AsyncJoinComponent< Measurement::Matrix3x4 > Matrix3x4AsyncJoinComponent;
        typedef AsyncJoinComponent< Measurement::Matrix4x4 > Matrix4x4AsyncJoinComponent;

        typedef AsyncJoinComponent< Measurement::Vector4D > Vector4DAsyncJoinComponent;

        typedef AsyncJoinComponent< Measurement::ButtonList > ButtonListAsyncJoinComponent;
        typedef AsyncJoinComponent< Measurement::DistanceList > DistanceListAsyncJoinComponent;

        typedef AsyncJoinComponent< Measurement::PositionList2 > PositionList2AsyncJoinComponent;
        typedef AsyncJoinComponent< Measurement::PositionList > PositionListAsyncJoinComponent;
        typedef AsyncJoinComponent< Measurement::PoseList > PoseListAsyncJoinComponent;

        typedef AsyncJoinComponent< Measurement::ErrorPositionList2 > ErrorPositionList2AsyncJoinComponent;
        typedef AsyncJoinComponent< Measurement::ErrorPositionList > ErrorPositionListAsyncJoinComponent;
        typedef AsyncJoinComponent< Measurement::ErrorPoseList > ErrorPoseListAsyncJoinComponent;

        typedef AsyncJoinComponent< Measurement::CameraIntrinsics > CameraIntrinsicsAsyncJoinComponent;

        typedef AsyncJoinComponent< Measurement::RotationVelocity > RotationVelocityAsyncJoinComponent;



    } } // namespace Ubitrack::Components

#endif //UBITRACK_COMPONENT_CORE_ASYNCJOIN_H
