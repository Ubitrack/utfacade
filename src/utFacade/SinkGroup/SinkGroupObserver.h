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
#include <utComponents/ApplicationEndpointsVision.h>
#include <utFacade/DataflowObserver.h>
#include <utFacade/AdvancedFacade.h>

#include <utFacade/SinkGroup/SinkGroup.h>


namespace Ubitrack {
    namespace Facade {



        bool UTFACADE_EXPORT addApplicationSinkComponentToGroup(SinkGroup& cmpsink, const std::string& sComponentName, boost::shared_ptr<Ubitrack::Components::ApplicationComponentBase> bc);

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

    }
}

#endif //UBITRACK_FACADE_SINKGROUPOBSERVER_H
