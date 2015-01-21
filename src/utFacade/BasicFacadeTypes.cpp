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


        // Vec
        template< int LEN >
        BasicVectorMeasurement< LEN >::BasicVectorMeasurement(unsigned long long int const ts, BasicVectorMeasurementPrivate< LEN >* _pPrivate)
                : BasicMeasurement(ts)
                , m_pPrivate(_pPrivate) {}

        template< int LEN >
        BasicVectorMeasurement< LEN >::BasicVectorMeasurement(unsigned long long int const ts, const std::vector<double>& value)
                : BasicVectorMeasurement(ts, new BasicVectorMeasurementPrivate< LEN >(ts, value)) {}

        template< int LEN >
        BasicVectorMeasurement< LEN >::~BasicVectorMeasurement() {
            if (m_pPrivate) {
                free(m_pPrivate);
            }
        }

        template< int LEN >
        bool BasicVectorMeasurement< LEN >::get(std::vector<double>& v) {
            typedef TensorIndex< LEN > TI;

            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    auto *m = m_pPrivate->m_measurement.get();
                    v.reserve(TI::SIZE);
                    for (unsigned int i = 0; i < TI::SIZE; i++) {
                        v.at(i) = (*m)(i);
                    }
                    return true;
                }
            }
            return false;
        }


        // Mat
        template< int ROWS, int COLS >
        BasicMatrixMeasurement< ROWS, COLS >::BasicMatrixMeasurement(unsigned long long int const ts, BasicMatrixMeasurementPrivate< ROWS, COLS >* _pPrivate)
                : BasicMeasurement(ts)
                , m_pPrivate(_pPrivate) {}

        template< int ROWS, int COLS >
        BasicMatrixMeasurement< ROWS, COLS >::BasicMatrixMeasurement(unsigned long long int const ts, const std::vector<double>& value)
                : BasicMatrixMeasurement< ROWS, COLS >(ts, new BasicMatrixMeasurementPrivate< ROWS, COLS >(ts, value)) {}

        template< int ROWS, int COLS >
        BasicMatrixMeasurement< ROWS, COLS >::~BasicMatrixMeasurement() {
            if (m_pPrivate) {
                free(m_pPrivate);
            }
        }

        template< int ROWS, int COLS >
        bool BasicMatrixMeasurement< ROWS, COLS >::get(std::vector<double>& v) {
            typedef TensorIndex< ROWS, COLS > TI;
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    auto *m = m_pPrivate->m_measurement.get();
                    v.reserve(TI::SIZE);
                    for (unsigned int i = 0; i < TI::LEN1; i++) {
                        for (unsigned int j = 0; j < TI::LEN2; j++) {
                            v.at(TI::indexOf(i, j)) = (*m)(i, j);
                        }
                    }
                    return true;
                }
            }
            return false;
        }

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
            typedef TensorIndex< 7 > TI;
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    // copied twice .. needs better implementation .. e.g. TensorIndex ...
                    Math::Vector< double, 7 > vec;
                    m_pPrivate->m_measurement.get()->toVector(vec);
                    v.reserve(TI::SIZE);
                    for (unsigned int i = 0; i < TI::SIZE; i++) {
                        v.at(i) = vec(i);
                    }
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



template class Ubitrack::Facade::BasicVectorMeasurement< 2 >;
template class Ubitrack::Facade::BasicVectorMeasurement< 3 >;
template class Ubitrack::Facade::BasicVectorMeasurement< 4 >;
template class Ubitrack::Facade::BasicVectorMeasurement< 8 >;

template class Ubitrack::Facade::BasicMatrixMeasurement< 3, 3 >;
template class Ubitrack::Facade::BasicMatrixMeasurement< 3, 4 >;
template class Ubitrack::Facade::BasicMatrixMeasurement< 4, 4 >;

#endif // ENABLE_BASICFACADE