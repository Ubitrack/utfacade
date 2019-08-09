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

    auto dt = bc->getDataType();

    // this is ugly design !!!
    if (bc->isMeasurementFixedSize()) {
        // Fixed-Size Measurements
        switch(bc->getMeasurementType()) {
            // Scalar Types
            case Measurement::Traits::MeasurementType::MeasurementTypeScalar:
                switch(dt) {
                    // Button
                    case Measurement::Traits::DataType ::DataTypeInteger:
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
                    case Measurement::Traits::DataType::DataTypeDouble:
                    {
                        auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Distance>>(bc);
                        if ( c ) {
                            m_compoundSink.addSinkComponent(sComponentName, c);
                        } else {
                            // log error: invalid cast - check implementation as this should never happen
                        }
                    }
                        break;
                    default:
                        // log error: unknown combination of measurement type and data type
                        break;
                }
                break;

                // Position2D
            case Measurement::Traits::MeasurementType::MeasurementTypeVector2:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Position2D>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // Position
            case Measurement::Traits::MeasurementType::MeasurementTypeVector3:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Position>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // Vector4D
            case Measurement::Traits::MeasurementType::MeasurementTypeVector4:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Vector4D>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // Vector8D
            case Measurement::Traits::MeasurementType::MeasurementTypeVector8:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Vector8D>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // Rotation
            case Measurement::Traits::MeasurementType::MeasurementTypeQuaternion:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Rotation>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // Matrix3x3
            case Measurement::Traits::MeasurementType::MeasurementTypeMatrix3x3:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Matrix3x3>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // Matrix3x4
            case Measurement::Traits::MeasurementType::MeasurementTypeMatrix3x4:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Matrix3x4>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // Matrix4x4
            case Measurement::Traits::MeasurementType::MeasurementTypeMatrix4x4:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Matrix4x4>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // Pose
            case Measurement::Traits::MeasurementType::MeasurementTypePose:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::Pose>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // ErrorPose
            case Measurement::Traits::MeasurementType::MeasurementTypeErrorPose:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ErrorPose>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // ErrorPosition2
            case Measurement::Traits::MeasurementType::MeasurementTypeErrorVector2:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ErrorPosition2>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // ErrorPosition
            case Measurement::Traits::MeasurementType::MeasurementTypeErrorVector3:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ErrorPosition>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // RotationVelocity
            case Measurement::Traits::MeasurementType::MeasurementTypeRotationVelocity:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::RotationVelocity>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // CameraIntrinsics
            case Measurement::Traits::MeasurementType::MeasurementTypeCameraIntrinsics:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::CameraIntrinsics>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
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
            // DistanceList
            // IDList
            case Measurement::Traits::MeasurementType::MeasurementTypeScalar:
                switch(dt) {
                    case Measurement::Traits::DataType ::DataTypeInteger:
                    {
                        auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ButtonList>>(bc);
                        if ( c ) {
                            m_compoundSink.addSinkComponent(sComponentName, c);
                        } else {
                            // log error: invalid cast - check implementation as this should never happen
                        }
                    }
                        break;
                    case Measurement::Traits::DataType::DataTypeUnsignedLong:
                    {
                        auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::IDList>>(bc);
                        if ( c ) {
                            m_compoundSink.addSinkComponent(sComponentName, c);
                        } else {
                            // log error: invalid cast - check implementation as this should never happen
                        }
                    }
                        break;
                    case Measurement::Traits::DataType::DataTypeDouble:
                    {
                        auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::DistanceList>>(bc);
                        if ( c ) {
                            m_compoundSink.addSinkComponent(sComponentName, c);
                        } else {
                            // log error: invalid cast - check implementation as this should never happen
                        }
                    }
                        break;
                    default:
                        // log error: unknown combination of measurement type and data type
                        break;
                }
                break;

                // PositionList2
            case Measurement::Traits::MeasurementType::MeasurementTypeVector2:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::PositionList2>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // PositionList
            case Measurement::Traits::MeasurementType::MeasurementTypeVector3:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::PositionList>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // PoseList
            case Measurement::Traits::MeasurementType::MeasurementTypePose:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::PoseList>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // ErrorPoseList
            case Measurement::Traits::MeasurementType::MeasurementTypeErrorPose:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ErrorPoseList>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // ErrorPositionList2
            case Measurement::Traits::MeasurementType::MeasurementTypeErrorVector2:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ErrorPositionList2>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
                }
                break;
                // ErrorPositionList
            case Measurement::Traits::MeasurementType::MeasurementTypeErrorVector3:
                if (dt == Measurement::Traits::DataType::DataTypeDouble) {
                    auto c = boost::dynamic_pointer_cast<Components::ApplicationComponent<Measurement::ErrorPositionList>>(bc);
                    if ( c ) {
                        m_compoundSink.addSinkComponent(sComponentName, c);
                    } else {
                        // log error: invalid cast - check implementation as this should never happen
                    }
                } else {
                    // log error: unknown combination of measurement type and data type
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

