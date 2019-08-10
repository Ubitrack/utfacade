//
// Created by Ulrich Eck on 2019-08-06.
//

#ifndef UBITRACK_FACADE_SINKGROUP_H
#define UBITRACK_FACADE_SINKGROUP_H

#include <map>
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <condition_variable>
#include <mutex>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

#include <utFacade/utFacade.h>
#include <utDataflow/PushConsumer.h>
#include <utComponents/ApplicationComponent.h>
#include <utComponents/ApplicationPushSink.h>
#include <utComponents/ApplicationPullSink.h>
#include <utFacade/DataflowObserver.h>
#include <utFacade/AdvancedFacade.h>

#include <utFacade/SinkGroup/PushSinkWrapper.h>


namespace Ubitrack {
    namespace Facade {

    enum class UTFACADE_EXPORT WaitForFrameResult {
        Timeout = 0,
        NewFrame,
        NoUpdate
    };

    struct UTFACADE_EXPORT ComponentTypeInfo {
        Ubitrack::Measurement::Traits::MeasurementType measurementType;
        bool isFixedType;
    };

    struct UTFACADE_EXPORT FrameReceivedInfo {

        FrameReceivedInfo() {
            reset();
        }

        FrameReceivedInfo(const FrameReceivedInfo&& other) noexcept {
            valid = other.valid;
            timestamp = other.timestamp;
        }

        void reset() {
            valid = false;
            timestamp = 0;
        }

        bool valid{false};
        Ubitrack::Measurement::Timestamp timestamp{0};
    };

    class UTFACADE_EXPORT SinkGroup {
    public:
        SinkGroup() = default;
        ~SinkGroup() = default;

        // manually add / remove components from compound sink
        template < class EventType >
        void addSinkComponent(const std::string& sComponentName, boost::shared_ptr<Components::ApplicationComponent<EventType>>& pComponent);

        void removeSinkComponent(const std::string& sComponentName);

        bool hasSinkComponent(const std::string& sComponentName);

        boost::shared_ptr<Ubitrack::Components::ApplicationComponentBase>& getSinkComponent(const std::string& sComponentName);

        // async interface

        // @todo not yet implemented

        // sync interface

        /*
         * waits for an complete frame and returns the status
         */
        WaitForFrameResult waitForCompleteFrameTimeout(unsigned int timeout_ms);


        // accessors for data

        std::vector<std::string> getSinkNames() {
            std::vector<std::string> result;
            for ( const auto &it : m_components ) {
                result.push_back(it.first);
            }
            return std::move(result);
        }

        ComponentTypeInfo getMeasurementType(const std::string& sComponentName) {
            auto it = m_components.find(sComponentName);
            if ( it == m_components.end()) {
                // log error: invalid component name
                return ComponentTypeInfo{Ubitrack::Measurement::Traits::MeasurementType::Undefined, true};
            }
            return ComponentTypeInfo{it->second->getMeasurementType(), it->second->isMeasurementFixedSize()};
        }

        template<typename MT>
        bool getMeasurement(const std::string& sComponentName, MT& measurement) {
            auto it = m_components.find(sComponentName);
            if ( it == m_components.end()) {
                // log error: invalid component name
                return false;
            }

            auto bc = it->second;
            if (bc->getComponentType() == Components::ApplicationComponentType::ApplicationComponentTypePullSink) {
                auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationPullSink<MT>>(bc);
                if (c == 0) {
                    // log error: invalid pullsink type
                    return false;
                }
                // pull measurement directly from sink
                measurement = c->get(m_lastTimestamp);
                return true;

            } else if (bc->getComponentType() == Components::ApplicationComponentType::ApplicationComponentTypePushSink) {
                auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationPushSink<MT>>(bc);
                if (c != 0) {
                    // need to check the pushsink wrapper
                    auto it2 = m_pushsink_wrappers.find(sComponentName);
                    if ( it2 == m_pushsink_wrappers.end()) {
                        // log error: invalid pushsink wrapper name
                        return false;
                    }
                    auto pswb = it2->second;
                    auto psw = boost::dynamic_pointer_cast<PushSinkWrapper<MT>>(pswb);
                    if (psw == 0) {
                        // log error: invalid pushsink wrapper type
                        return false;
                    }
                    // pull measurement from the buffered event
                    measurement = psw->getMeasurement();
                    return true;
                }
            }
            // log error: invalid application component
            return false;
        }

        // maybe make protected and friend class PushSink Wrapper
        void onMeasurementReceived(const std::string& sComponentName, Ubitrack::Measurement::Timestamp ts);

    protected:
        virtual void checkFrameReceived();

    private:
        std::mutex m_waitMutex;
        std::condition_variable m_waitCondition;

        bool m_haveNewFrame{false};
        Ubitrack::Measurement::Timestamp m_lastTimestamp{0};

        std::map<std::string, FrameReceivedInfo> m_frameReceivedInfo;
        // is a pointer since we need to cast it to a concrete type...
        std::map<std::string, PushSinkWrapperBase*> m_pushsink_wrappers;
        std::map<std::string, boost::shared_ptr<Ubitrack::Components::ApplicationComponentBase>> m_components;
    };


}} // Ubitrack::Facade

#endif //UBITRACK_FACADE_SINKGROUP_H
