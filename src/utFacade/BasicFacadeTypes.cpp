#include <utFacade/Config.h>
#ifdef ENABLE_BASICFACADE

#include "BasicFacadeTypesPrivate.h"
#include <algorithm>

namespace Ubitrack {
    namespace Facade {

        // ScalarInt
        BasicScalarIntMeasurement::BasicScalarIntMeasurement(unsigned long long int const ts, BasicScalarIntMeasurementPrivate* _pPrivate)
                : BasicMeasurement(ts)
                , m_pPrivate(_pPrivate) {}

        BasicScalarIntMeasurement::BasicScalarIntMeasurement(unsigned long long int const ts, const int value)
                : BasicScalarIntMeasurement(ts, new BasicScalarIntMeasurementPrivate(ts, value)) {}


        BasicScalarIntMeasurement::~BasicScalarIntMeasurement() {
            if (m_pPrivate) {
                free(m_pPrivate);
            }
        }

        bool BasicScalarIntMeasurement::get(int& v) {
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    v = *(m_pPrivate->m_measurement.get());
                    return true;
                }
            }
            return false;
        }

        // ScalarDouble
        BasicScalarDoubleMeasurement::BasicScalarDoubleMeasurement(unsigned long long int const ts, BasicScalarDoubleMeasurementPrivate* _pPrivate)
                : BasicMeasurement(ts)
                , m_pPrivate(_pPrivate) {}

        BasicScalarDoubleMeasurement::BasicScalarDoubleMeasurement(unsigned long long int const ts, const double value)
                : BasicScalarDoubleMeasurement(ts, new BasicScalarDoubleMeasurementPrivate(ts, value)) {}

        BasicScalarDoubleMeasurement::~BasicScalarDoubleMeasurement() {
            if (m_pPrivate) {
                free(m_pPrivate);
            }
        }

        bool BasicScalarDoubleMeasurement::get(double& v) {
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    v = *(m_pPrivate->m_measurement.get());
                    return true;
                }
            }
            return false;
        }


        // Vec2
        BasicVector2Measurement::BasicVector2Measurement(unsigned long long int const ts, BasicVector2MeasurementPrivate* _pPrivate)
                : BasicMeasurement(ts)
                , m_pPrivate(_pPrivate) {}

        BasicVector2Measurement::BasicVector2Measurement(unsigned long long int const ts, const std::vector<double>& value)
                : BasicVector2Measurement(ts, new BasicVector2MeasurementPrivate(ts, value)) {}

        BasicVector2Measurement::~BasicVector2Measurement() {
            if (m_pPrivate) {
                free(m_pPrivate);
            }
        }

        bool BasicVector2Measurement::get(std::vector<double>& v) {
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    auto *m = m_pPrivate->m_measurement.get();
                    v.reserve(m->size());
                    std::copy(m->begin(), m->end(), std::back_inserter(v));
                    return true;
                }
            }
            return false;
        }

        // Vec3
        // Vec4

        // Mat33
        BasicMatrix33Measurement::BasicMatrix33Measurement(unsigned long long int const ts, BasicMatrix33MeasurementPrivate* _pPrivate)
                : BasicMeasurement(ts)
                , m_pPrivate(_pPrivate) {}

        BasicMatrix33Measurement::BasicMatrix33Measurement(unsigned long long int const ts, const std::vector<double>& value)
                : BasicMatrix33Measurement(ts, new BasicMatrix33MeasurementPrivate(ts, value)) {}

        BasicMatrix33Measurement::~BasicMatrix33Measurement() {
            if (m_pPrivate) {
                free(m_pPrivate);
            }
        }

        bool BasicMatrix33Measurement::get(std::vector<double>& v) {
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    auto *m = m_pPrivate->m_measurement.get();
                    v.reserve(m->size());
                    std::copy(m->data().begin(), m->data().end(), std::back_inserter(v));
                    return true;
                }
            }
            return false;
        }

        // Mat34
        // Mat44

        // Pose
        BasicPoseMeasurement::BasicPoseMeasurement(unsigned long long int const ts, BasicPoseMeasurementPrivate* _pPrivate)
                : BasicMeasurement(ts)
                , m_pPrivate(_pPrivate) {}

        BasicPoseMeasurement::BasicPoseMeasurement(unsigned long long int const ts, const std::vector<double>& value)
                : BasicPoseMeasurement(ts, new BasicPoseMeasurementPrivate(ts, value)) {}

        BasicPoseMeasurement::~BasicPoseMeasurement() {
            if (m_pPrivate) {
                free(m_pPrivate);
            }
        }

        bool BasicPoseMeasurement::get(std::vector<double>& v) {
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    // copied twice .. needs better implementation .. e.g. TensorIndex ...
                    Math::Vector< double, 7 > vec;
                    m_pPrivate->m_measurement.get()->toVector(vec);

                    v.reserve(vec.size());
                    std::copy(vec.data().begin(),vec.data().end(), std::back_inserter(v));
                    return true;
                }
            }
            return false;
        }

        // Rotation

        // ErrorVector2
        // ErrorVector3
        // ErrorVector4
        // ErrorPose

        // Image


    }
}


#endif // ENABLE_BASICFACADE