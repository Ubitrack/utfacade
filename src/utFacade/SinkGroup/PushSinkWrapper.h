//
// Created by Ulrich Eck on 2019-08-08.
//

#ifndef UBITRACK_FACADE_PUSHSINKWRAPPER_H
#define UBITRACK_FACADE_PUSHSINKWRAPPER_H

#include <map>
#include <string>
#include <memory>
#include <utility>
#include <vector>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

#include <utMeasurement/Measurement.h>
#include <utFacade/utFacade.h>
#include <utDataflow/PushConsumer.h>
#include <utComponents/ApplicationComponent.h>
#include <utComponents/ApplicationPushSink.h>


namespace Ubitrack {
    namespace Facade {

        class UTFACADE_EXPORT PushSinkWrapperBase {
        public:

            typedef boost::function< void ( const std::string&, const Ubitrack::Measurement::Timestamp& ) > SlotType;

            explicit PushSinkWrapperBase(std::string  sComponentName) : m_componentName(std::move(sComponentName)), m_callback(NULL) {}

            void setCallback ( SlotType slot )
            {
                m_callback = std::move(slot);
            }

        protected:
            /** Type of the callback functions */
            SlotType m_callback;
            std::string m_componentName;
        };

        template<typename EventType>
        class UTFACADE_EXPORT PushSinkWrapper : public PushSinkWrapperBase {
        public:
            explicit PushSinkWrapper(const std::string& sComponentName, boost::shared_ptr<Ubitrack::Components::ApplicationPushSink<EventType>>& sink)
                    : PushSinkWrapperBase(sComponentName), m_sink(sink) {
                if (m_sink) {
                    m_sink->setCallback(boost::bind( &PushSinkWrapper<EventType>::receiveMeasurement, this, _1 ));
                }
            }

            ~PushSinkWrapper() {
                if (m_sink) {
                    m_sink->setCallback(NULL);
                }
            }

            void receiveMeasurement(const EventType& m) {
                // store the measurement as in a buffer component
                m_event = m;
                // notify SinkGroup on message arrival
                if (m_callback) {
                    m_callback(m_componentName, m.time());
                } else {
                    // LOG WARNING .. no callback supplied
                }
            }

            EventType& getMeasurement() {
                return m_event;
            }

        protected:
            /** Buffer variable containing the last received event. */
            EventType m_event;
            // we might want to use a ring-buffer here to allow aligning multiple received frames in case of measurements arrive with too much delay/variance

            boost::shared_ptr<Ubitrack::Components::ApplicationPushSink<EventType>> m_sink;
        };

    }
}

#endif //UBITRACK_FACADE_PUSHSINKWRAPPER_H
