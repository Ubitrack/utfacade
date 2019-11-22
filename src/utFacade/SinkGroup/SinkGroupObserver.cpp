//
// Created by Ulrich Eck on 2019-08-08.
//

#include "SinkGroupObserver.h"
#include <log4cpp/Category.hh>


static log4cpp::Category& logger( log4cpp::Category::getInstance( "Ubitrack.Facade.SinkGroupObserver" ) );


using namespace Ubitrack::Facade;

bool Ubitrack::Facade::addApplicationSinkComponentToGroup(SinkGroup& cmpsink, const std::string& sComponentName, boost::shared_ptr<Ubitrack::Components::ApplicationComponentBase> bc) {

    auto ct = bc->getComponentType();

    if ((ct == Ubitrack::Components::ApplicationComponentType::ApplicationComponentTypePushSource) || (ct == Ubitrack::Components::ApplicationComponentType::ApplicationComponentTypePullSource)) {
        // we do not consider source in a compound sink
        LOG4CPP_DEBUG(logger, "Component " << sComponentName << " is not a sink." );
        return false;
    }

    // this is ugly design !!!
    if (bc->isMeasurementFixedSize()) {
        // Fixed-Size Measurements
        switch(bc->getMeasurementType()) {
            // Button
            case Ubitrack::Measurement::Traits::MeasurementType::ScalarInt:
            {
                auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::Button>>(bc);
                if ( c ) {
                    cmpsink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                    LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                    return false;
                }
            }
                break;

            // Distance
            case Ubitrack::Measurement::Traits::MeasurementType::ScalarDouble:
            {
                auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::Distance>>(bc);
                if ( c ) {
                    cmpsink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                    LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                    return false;
                }
            }
                break;

            // Position2D
            case Ubitrack::Measurement::Traits::MeasurementType::Vector2:
            {
                auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::Position2D>>(bc);
                if ( c ) {
                    cmpsink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                    LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                    return false;
                }
            }
                break;

            // Position
            case Ubitrack::Measurement::Traits::MeasurementType::Vector3:
            {
                auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::Position>>(bc);
                if ( c ) {
                    cmpsink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                    LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                    return false;
                }
            }
                break;

            // Vector4D
            case Ubitrack::Measurement::Traits::MeasurementType::Vector4:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::Vector4D>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // Vector8D
            case Ubitrack::Measurement::Traits::MeasurementType::Vector8:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::Vector8D>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // Rotation
            case Ubitrack::Measurement::Traits::MeasurementType::Quaternion:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::Rotation>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // Matrix3x3
            case Ubitrack::Measurement::Traits::MeasurementType::Matrix3x3:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::Matrix3x3>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // Matrix3x4
            case Ubitrack::Measurement::Traits::MeasurementType::Matrix3x4:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::Matrix3x4>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // Matrix4x4
            case Ubitrack::Measurement::Traits::MeasurementType::Matrix4x4:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::Matrix4x4>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // Pose
            case Ubitrack::Measurement::Traits::MeasurementType::Pose:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::Pose>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // ErrorPose
            case Ubitrack::Measurement::Traits::MeasurementType::ErrorPose:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::ErrorPose>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // ErrorPosition2
            case Ubitrack::Measurement::Traits::MeasurementType::ErrorVector2:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::ErrorPosition2>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // ErrorPosition
            case Ubitrack::Measurement::Traits::MeasurementType::ErrorVector3:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::ErrorPosition>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // RotationVelocity
            case Ubitrack::Measurement::Traits::MeasurementType::RotationVelocity:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::RotationVelocity>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // CameraIntrinsics
            case Ubitrack::Measurement::Traits::MeasurementType::CameraIntrinsics:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::CameraIntrinsics>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            default:
                // log error: unknown type
                return false;
        }
    } else {
        // Vector of Measurements
        switch(bc->getMeasurementType()) {
            // ButtonList
            case Ubitrack::Measurement::Traits::MeasurementType::ScalarInt:
            {
                auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::ButtonList>>(bc);
                if ( c ) {
                    cmpsink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                    LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                    return false;
                }
            }

            // DistanceList
            case Ubitrack::Measurement::Traits::MeasurementType::ScalarDouble:
            {
                auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::IDList>>(bc);
                if ( c ) {
                    cmpsink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                    LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                    return false;
                }
            }

            // IDList
            case Ubitrack::Measurement::Traits::MeasurementType::ScalarUnsignedLong:
            {
                auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::DistanceList>>(bc);
                if ( c ) {
                    cmpsink.addSinkComponent(sComponentName, c);
                } else {
                    // log error: invalid cast - check implementation as this should never happen
                    LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                    return false;
                }
            }
                break;

            // PositionList2
            case Ubitrack::Measurement::Traits::MeasurementType::Vector2:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::PositionList2>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // PositionList
            case Ubitrack::Measurement::Traits::MeasurementType::Vector3:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::PositionList>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // PoseList
            case Ubitrack::Measurement::Traits::MeasurementType::Pose:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::PoseList>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // ErrorPoseList
            case Ubitrack::Measurement::Traits::MeasurementType::ErrorPose:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::ErrorPoseList>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // ErrorPositionList2
            case Ubitrack::Measurement::Traits::MeasurementType::ErrorVector2:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::ErrorPositionList2>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            // ErrorPositionList
            case Ubitrack::Measurement::Traits::MeasurementType::ErrorVector3:
                {
                    auto c = boost::dynamic_pointer_cast<Ubitrack::Components::ApplicationComponent<Ubitrack::Measurement::ErrorPositionList>>(bc);
                    if ( c ) {
                        cmpsink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                        LOG4CPP_ERROR(logger, "Component " << sComponentName << " invalid cast - should never happen" );
                        return false;
                    }
                }
                break;

            default:
                // log error: unknown type
                return false;
        }
    }
    return true;
}



SinkGroupObserver::SinkGroupObserver(Ubitrack::Facade::AdvancedFacade& facade, SinkGroup& cmpsink, std::string  sDomainAttribute, std::string  sDomainValue)
        : m_domainAttribute(std::move(sDomainAttribute)), m_domainValue(std::move(sDomainValue))
        , m_compoundSink(cmpsink), m_facade(facade)
{
}

void SinkGroupObserver::notifyAddComponent(const std::string& sPatternName, const std::string& sComponentName, const Ubitrack::Graph::UTQLSubgraph& pattern ) {
    auto bc = m_facade.componentByName<Ubitrack::Components::ApplicationComponentBase>(sComponentName);
    if (!bc) {
        // not an application component
        return;
    }
    if (!bc->hasMetadataAttribute(m_domainAttribute)) {
        // component is missing the required domainAttribute
        LOG4CPP_DEBUG(logger, "Component " << sComponentName << " is missing required domain attribute: " << m_domainAttribute);
        return;
    }
    if (bc->getMetadataAttribute(m_domainAttribute) != m_domainValue) {
        // component does not belong to this domain
        LOG4CPP_DEBUG(logger, "Component " << sComponentName << " domain attribute does not match provided value: " << m_domainValue);
        return;
    }

    addApplicationSinkComponentToGroup(m_compoundSink, sComponentName, bc);

}

void SinkGroupObserver::notifyDeleteComponent(const std::string& sPatternName, const std::string& sComponentName ) {
    if (m_compoundSink.hasSinkComponent(sComponentName)) {
        m_compoundSink.removeSinkComponent(sComponentName);
    }
}

