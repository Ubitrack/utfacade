//
// Created by Ulrich Eck on 2019-08-06.
//

#include "SinkGroup.h"

#include <utility>

using namespace Ubitrack::Facade;


void SinkGroup::checkFrameReceived() {
    bool frameComplete = true;
    Measurement::Timestamp ts = 0;

    // primitive implementation:
    // only checks if all frames were received for now.
    // and uses the last timestamp found as reference.
    for (auto& it : m_frameReceivedInfo) {
        auto& fri = it.second;
        if (!fri.valid) {
            frameComplete = false;
            ts = fri.timestamp;
        }
    }

    if (frameComplete) {
        std::unique_lock<std::mutex> ul(m_waitMutex);
        m_lastTimestamp = ts;
        m_haveNewFrame = true;
        m_waitCondition.notify_one();

        // reset frame
        for (auto &it : m_frameReceivedInfo) {
            it.second.reset();
        }
    }
}


void SinkGroup::removeSinkComponent(const std::string& sComponentName) {
    if (!hasSinkComponent(sComponentName)) {
        UBITRACK_THROW("Invalid component name");
    }
    auto bc = m_components[sComponentName];
    if (bc->getComponentType() == Components::ApplicationComponentType::ApplicationComponentTypePushSink) {
        // do we need to verify this exists here ?
        auto psw = m_pushsink_wrappers[sComponentName];
        m_pushsink_wrappers.erase(sComponentName);
        psw->setCallback(NULL);
    }
    m_frameReceivedInfo.erase(sComponentName);
    m_components.erase(sComponentName);
}

bool SinkGroup::hasSinkComponent(const std::string& sComponentName) {
    auto it = m_components.find(sComponentName);
    if ( it == m_components.end()) {
        return false;
    }
    return true;
}

boost::shared_ptr<Ubitrack::Components::ApplicationComponentBase>& SinkGroup::getSinkComponent(const std::string& sComponentName) {
    if (!hasSinkComponent(sComponentName)) {
        UBITRACK_THROW("Invalid component name");
    }
    return m_components[sComponentName];
}

WaitForFrameResult SinkGroup::waitForCompleteFrameTimeout(unsigned int timeout_ms) {
    auto timeout = std::chrono::milliseconds(timeout_ms);

    std::unique_lock<std::mutex> ul( m_waitMutex );
    if(m_waitCondition.wait_for( ul , timeout) == std::cv_status::no_timeout) {
        if (m_haveNewFrame) {
            return WaitForFrameResult ::NewFrame;
        } else {
            // no new frame
            return WaitForFrameResult ::NoUpdate;
        }
    } else {
        // timeout
        return WaitForFrameResult ::Timeout;
    }
}

void SinkGroup::onMeasurementReceived(const std::string& sComponentName, Ubitrack::Measurement::Timestamp ts) {
    if (hasSinkComponent(sComponentName)) {
        auto bc = getSinkComponent(sComponentName);
        if (bc->getComponentType() == Components::ApplicationComponentType::ApplicationComponentTypePushSink) {
            auto& fri = m_frameReceivedInfo[sComponentName];
            fri.timestamp = ts;
            fri.valid = true;
        }
    }
    checkFrameReceived();
}



