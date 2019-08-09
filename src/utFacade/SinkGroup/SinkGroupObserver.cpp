//
// Created by Ulrich Eck on 2019-08-08.
//

#include "SinkGroupObserver.h"


using namespace Ubitrack::Facade;

SinkGroupObserver::SinkGroupObserver(Ubitrack::Facade::AdvancedFacade& facade, SinkGroup& cmpsink, std::string  sDomainAttribute, std::string  sDomainValue)
        : m_domainAttribute(std::move(sDomainAttribute)), m_domainValue(std::move(sDomainValue))
        , m_compoundSink(cmpsink), m_facade(facade)
{
}

void SinkGroupObserver::notifyAddComponent(const std::string& sPatternName, const std::string& sComponentName, const Graph::UTQLSubgraph& pattern ) {
    auto bc = m_facade.componentByName<Ubitrack::Components::ApplicationComponentBase>(sComponentName);
    if (!bc->hasMetadataAttribute(m_domainAttribute)) {
        // component is missing the required domainAttribute
        return;
    }
    if (bc->getMetadataAttribute(m_domainAttribute) != m_domainValue) {
        // component does not belong to this domain
        return;
    }

    auto ct = bc->getComponentType();

    if ((ct == Components::ApplicationComponentType::ApplicationComponentTypePushSource) || (ct == Components::ApplicationComponentType::ApplicationComponentTypePullSource)) {
        // we do not consider source in a compound sink
        return;
    }

    // this is ugly design !!!
    if (bc->isMeasurementFixedSize()) {
        // Fixed-Size Measurements
        switch(bc->getMeasurementType()) {
            // Button
            case Measurement::Traits::MeasurementType::ScalarInt:
            {
                auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Button>>(bc);
                if ( c ) {
                    m_compoundSink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                }
            }
                break;

            // Distance
            case Measurement::Traits::MeasurementType::ScalarDouble:
            {
                auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Distance>>(bc);
                if ( c ) {
                    m_compoundSink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                }
            }
                break;

            // Position2D
            case Measurement::Traits::MeasurementType::Vector2:
            {
                auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Position2D>>(bc);
                if ( c ) {
                    m_compoundSink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                }
            }
                break;

            // Position
            case Measurement::Traits::MeasurementType::Vector3:
            {
                auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Position>>(bc);
                if ( c ) {
                    m_compoundSink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                }
            }
                break;

            // Vector4D
            case Measurement::Traits::MeasurementType::Vector4:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Vector4D>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // Vector8D
            case Measurement::Traits::MeasurementType::Vector8:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Vector8D>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // Rotation
            case Measurement::Traits::MeasurementType::Quaternion:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Rotation>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // Matrix3x3
            case Measurement::Traits::MeasurementType::Matrix3x3:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Matrix3x3>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // Matrix3x4
            case Measurement::Traits::MeasurementType::Matrix3x4:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Matrix3x4>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // Matrix4x4
            case Measurement::Traits::MeasurementType::Matrix4x4:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Matrix4x4>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // Pose
            case Measurement::Traits::MeasurementType::Pose:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Pose>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // ErrorPose
            case Measurement::Traits::MeasurementType::ErrorPose:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ErrorPose>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // ErrorPosition2
            case Measurement::Traits::MeasurementType::ErrorVector2:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ErrorPosition2>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // ErrorPosition
            case Measurement::Traits::MeasurementType::ErrorVector3:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ErrorPosition>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // RotationVelocity
            case Measurement::Traits::MeasurementType::RotationVelocity:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::RotationVelocity>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // CameraIntrinsics
            case Measurement::Traits::MeasurementType::CameraIntrinsics:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::CameraIntrinsics>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            default:
                // log error: unknown type
                break;
        }
    } else {
        // Vector of Measurements
        switch(bc->getMeasurementType()) {
            // ButtonList
            case Measurement::Traits::MeasurementType::ScalarInt:
            {
                auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ButtonList>>(bc);
                if ( c ) {
                    m_compoundSink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                }
            }

            // DistanceList
            case Measurement::Traits::MeasurementType::ScalarDouble:
            {
                auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::IDList>>(bc);
                if ( c ) {
                    m_compoundSink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                }
            }

            // IDList
            case Measurement::Traits::MeasurementType::ScalarUnsignedLong:
            {
                auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::DistanceList>>(bc);
                if ( c ) {
                    m_compoundSink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                }
            }
                break;

            // PositionList2
            case Measurement::Traits::MeasurementType::Vector2:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::PositionList2>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // PositionList
            case Measurement::Traits::MeasurementType::Vector3:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::PositionList>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // PoseList
            case Measurement::Traits::MeasurementType::Pose:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::PoseList>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // ErrorPoseList
            case Measurement::Traits::MeasurementType::ErrorPose:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ErrorPoseList>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // ErrorPositionList2
            case Measurement::Traits::MeasurementType::ErrorVector2:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ErrorPositionList2>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            // ErrorPositionList
            case Measurement::Traits::MeasurementType::ErrorVector3:
                {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ErrorPositionList>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                }
                break;

            default:
                // log error: unknown type
                break;
        }
    }

}

void SinkGroupObserver::notifyDeleteComponent(const std::string& sPatternName, const std::string& sComponentName ) {
    if (m_compoundSink.hasSinkComponent(sComponentName)) {
        m_compoundSink.removeSinkComponent(sComponentName);
    }
}

