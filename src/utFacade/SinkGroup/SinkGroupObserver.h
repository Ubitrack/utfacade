//
// Created by Ulrich Eck on 2019-08-08.
//

#ifndef UBITRACK_FACADE_SINKGROUPOBSERVER_H
#define UBITRACK_FACADE_SINKGROUPOBSERVER_H

#include <map>
#include <string>
#include <memory>
#include <utility>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

#include <utFacade/utFacade.h>
#include <utDataflow/PushConsumer.h>
#include <utComponents/ApplicationComponent.h>
#include <utComponents/ApplicationPushSink.h>
#include <utComponents/ApplicationPullSink.h>
#include <utFacade/DataflowObserver.h>
#include <utFacade/AdvancedFacade.h>

#include <utFacade/SinkGroup/SinkGroup.h>


namespace Ubitrack {
    namespace Facade {


        class UTFACADE_EXPORT SinkGroupObserver  : public DataflowObserver {
        public:

            SinkGroupObserver(Ubitrack::Facade::AdvancedFacade& facade, SinkGroup& cmpsink, std::string  sDomainAttribute, std::string  sDomainValue);

            void notifyAddComponent( const std::string& sPatternName, const std::string& sComponentName, const Graph::UTQLSubgraph& pattern );

            void notifyDeleteComponent( const std::string& sPatternName, const std::string& sComponentName );

        private:
            std::string m_domainAttribute;
            std::string m_domainValue;

            SinkGroup& m_compoundSink;
            Ubitrack::Facade::AdvancedFacade& m_facade;
        };

        template < class EventType >
        void SinkGroup::addSinkComponent(const std::string& sComponentName, boost::shared_ptr<Components::ApplicationComponent<EventType>>& pComponent) {
            if (hasSinkComponent(sComponentName)) {
                UBITRACK_THROW("Component already registered");
            }

            m_components.emplace(sComponentName, pComponent);

            if (pComponent->getComponentType() == Components::ApplicationComponentType::ApplicationComponentTypePushSink) {
                auto c = boost::dynamic_pointer_cast<Components::ApplicationPushSink<EventType>>(pComponent);
                auto psw = new PushSinkWrapper<EventType>(sComponentName, c);
                m_pushsink_wrappers.emplace(sComponentName, psw);
                psw->setCallback(boost::bind(&SinkGroup::onMeasurementReceived, this, _1, _2));
                m_frameReceivedInfo.emplace(sComponentName, std::move(FrameReceivedInfo()));
            }
        }


    }
}

#endif //UBITRACK_FACADE_SINKGROUPOBSERVER_H
