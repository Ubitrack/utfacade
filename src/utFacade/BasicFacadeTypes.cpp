/*
 * Ubitrack - Library for Ubiquitous Tracking
 * Copyright 2006, Technische Universitaet Muenchen, and individual
 * contributors as indicated by the @authors tag. See the
 * copyright.txt in the distribution for a full listing of individual
 * contributors.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA, or see the FSF site: http://www.fsf.org.
 */

/**
* @ingroup api
* @file
* Simple datatypes for the \c SimpleFacade
*
* @author Ulrich Eck <ueck@net-labs.de>
*/
#include <utFacade/Config.h>
#ifdef ENABLE_BASICFACADE

#include <utAlgorithm/Projection.h>

#include "BasicFacadeTypesPrivate.h"
#include <algorithm>

namespace Ubitrack {
namespace Facade {

/*
 * Single Measurements
 */

// ScalarInt
BasicScalarIntMeasurement::BasicScalarIntMeasurement(unsigned long long int const ts,
        BasicScalarIntMeasurementPrivate* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

BasicScalarIntMeasurement::BasicScalarIntMeasurement(unsigned long long int const ts, const int value)
        :BasicMeasurement(ts), m_pPrivate(new BasicScalarIntMeasurementPrivate(ts, value)) { }

BasicScalarIntMeasurement::~BasicScalarIntMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

bool BasicScalarIntMeasurement::get(int& v)
{
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            v = *(m_pPrivate->m_measurement.get());
            return true;
        }
    }
    return false;
}

// ScalarDouble
BasicScalarDoubleMeasurement::BasicScalarDoubleMeasurement(unsigned long long int const ts,
        BasicScalarDoubleMeasurementPrivate* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

BasicScalarDoubleMeasurement::BasicScalarDoubleMeasurement(unsigned long long int const ts, const double value)
        :BasicMeasurement(ts), m_pPrivate(new BasicScalarDoubleMeasurementPrivate(ts, value)) { }

BasicScalarDoubleMeasurement::~BasicScalarDoubleMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

bool BasicScalarDoubleMeasurement::get(double& v)
{
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            v = *(m_pPrivate->m_measurement.get());
            return true;
        }
    }
    return false;
}

bool BasicScalarDoubleMeasurement::get(float& v)
{
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            v = (float) (*(m_pPrivate->m_measurement.get()));
            return true;
        }
    }
    return false;
}

// Vec
template<int LEN>
BasicVectorMeasurement<LEN>::BasicVectorMeasurement(unsigned long long int const ts,
        BasicVectorMeasurementPrivate<LEN>* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

template<int LEN>
BasicVectorMeasurement<LEN>::BasicVectorMeasurement(unsigned long long int const ts, const std::vector<double>& value)
        :BasicMeasurement(ts), m_pPrivate(new BasicVectorMeasurementPrivate<LEN>(ts, value)) { }

template<int LEN>
BasicVectorMeasurement<LEN>::~BasicVectorMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

template<int LEN>
bool BasicVectorMeasurement<LEN>::get(std::vector<double>& v)
{
    typedef TensorIndex<LEN> TI;

    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::Vector<double, LEN>* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);
            for (unsigned int i = 0; i<TI::SIZE; i++) {
                v.at(i) = (*m)(i);
            }
            return true;
        }
    }
    return false;
}

template<int LEN>
bool BasicVectorMeasurement<LEN>::get(std::vector<float>& v)
{
    typedef TensorIndex<LEN> TI;

    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::Vector<double, LEN>* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);
            for (unsigned int i = 0; i<TI::SIZE; i++) {
                v.at(i) = (float) ((*m)(i));
            }
            return true;
        }
    }
    return false;
}

// Mat
template<int ROWS, int COLS>
BasicMatrixMeasurement<ROWS, COLS>::BasicMatrixMeasurement(unsigned long long int const ts,
        BasicMatrixMeasurementPrivate<ROWS, COLS>* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

template<int ROWS, int COLS>
BasicMatrixMeasurement<ROWS, COLS>::BasicMatrixMeasurement(unsigned long long int const ts,
        const std::vector<double>& value)
        :BasicMeasurement(ts), m_pPrivate(new BasicMatrixMeasurementPrivate<ROWS, COLS>(ts, value)) { }

template<int ROWS, int COLS>
BasicMatrixMeasurement<ROWS, COLS>::~BasicMatrixMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

template<int ROWS, int COLS>
bool BasicMatrixMeasurement<ROWS, COLS>::get(std::vector<double>& v)
{
    typedef TensorIndex<ROWS, COLS> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::Matrix<double, ROWS, COLS>* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);
            for (unsigned int i = 0; i<TI::LEN1; i++) {
                for (unsigned int j = 0; j<TI::LEN2; j++) {
                    v.at(TI::indexOf(i, j)) = (*m)(i, j);
                }
            }
            return true;
        }
    }
    return false;
}

template<int ROWS, int COLS>
bool BasicMatrixMeasurement<ROWS, COLS>::get(std::vector<float>& v)
{
    typedef TensorIndex<ROWS, COLS> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::Matrix<double, ROWS, COLS>* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);
            for (unsigned int i = 0; i<TI::LEN1; i++) {
                for (unsigned int j = 0; j<TI::LEN2; j++) {
                    v.at(TI::indexOf(i, j)) = (float) ((*m)(i, j));
                }
            }
            return true;
        }
    }
    return false;
}

// Pose
BasicPoseMeasurement::BasicPoseMeasurement(unsigned long long int const ts, BasicPoseMeasurementPrivate* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

BasicPoseMeasurement::BasicPoseMeasurement(unsigned long long int const ts, const std::vector<double>& value)
        :BasicMeasurement(ts), m_pPrivate(new BasicPoseMeasurementPrivate(ts, value)) { }

BasicPoseMeasurement::~BasicPoseMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

bool BasicPoseMeasurement::get(std::vector<double>& v)
{
    typedef TensorIndex<7> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::Pose* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);

            const Math::Vector<double, 3>& t = m->translation();
            v.at(0) = t(0);
            v.at(1) = t(1);
            v.at(2) = t(2);

            const Math::Quaternion& r = m->rotation();
            v.at(3) = r.x();
            v.at(4) = r.y();
            v.at(5) = r.z();
            v.at(6) = r.w();
            return true;
        }
    }
    return false;
}

bool BasicPoseMeasurement::get(std::vector<float>& v)
{
    typedef TensorIndex<7> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::Pose* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);

            const Math::Vector<double, 3>& t = m->translation();
            v.at(0) = (float) (t(0));
            v.at(1) = (float) (t(1));
            v.at(2) = (float) (t(2));

            const Math::Quaternion& r = m->rotation();
            v.at(3) = (float) (r.x());
            v.at(4) = (float) (r.y());
            v.at(5) = (float) (r.z());
            v.at(6) = (float) (r.w());
            return true;
        }
    }
    return false;
}

// Rotation
BasicRotationMeasurement::BasicRotationMeasurement(unsigned long long int const ts,
        BasicRotationMeasurementPrivate* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

BasicRotationMeasurement::BasicRotationMeasurement(unsigned long long int const ts, const std::vector<double>& value)
        :BasicMeasurement(ts), m_pPrivate(new BasicRotationMeasurementPrivate(ts, value)) { }

BasicRotationMeasurement::~BasicRotationMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

bool BasicRotationMeasurement::get(std::vector<double>& v)
{
    typedef TensorIndex<4> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::Quaternion* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);

            v.at(3) = m->x();
            v.at(4) = m->y();
            v.at(5) = m->z();
            v.at(6) = m->w();

            return true;
        }
    }
    return false;
}

bool BasicRotationMeasurement::get(std::vector<float>& v)
{
    typedef TensorIndex<4> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::Quaternion* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);

            v.at(3) = (float) (m->x());
            v.at(4) = (float) (m->y());
            v.at(5) = (float) (m->z());
            v.at(6) = (float) (m->w());

            return true;
        }
    }
    return false;
}

// ErrorVec
template<int LEN>
BasicErrorVectorMeasurement<LEN>::BasicErrorVectorMeasurement(unsigned long long int const ts,
        BasicErrorVectorMeasurementPrivate<LEN>* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

template<int LEN>
BasicErrorVectorMeasurement<LEN>::BasicErrorVectorMeasurement(unsigned long long int const ts,
        const std::vector<double>& value, const std::vector<double>& cov)
        :BasicMeasurement(ts), m_pPrivate(new BasicErrorVectorMeasurementPrivate<LEN>(ts, value, cov)) { }

template<int LEN>
BasicErrorVectorMeasurement<LEN>::~BasicErrorVectorMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

template<int LEN>
bool BasicErrorVectorMeasurement<LEN>::get(std::vector<double>& v)
{
    typedef TensorIndex<LEN> TI;

    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::ErrorVector<double, LEN>* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);
            for (unsigned int i = 0; i<TI::SIZE; i++) {
                v.at(i) = m->value(i);
            }
            return true;
        }
    }
    return false;
}

template<int LEN>
bool BasicErrorVectorMeasurement<LEN>::getCovariance(std::vector<double>& v)
{
    typedef TensorIndex<LEN, LEN> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::ErrorVector<double, LEN>* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);
            for (unsigned int i = 0; i<TI::LEN1; i++) {
                for (unsigned int j = 0; j<TI::LEN2; j++) {
                    v.at(TI::indexOf(i, j)) = m->covariance(i, j);
                }
            }
            return true;
        }
    }
    return false;
}

// ErrorPose
BasicErrorPoseMeasurement::BasicErrorPoseMeasurement(unsigned long long int const ts,
        BasicErrorPoseMeasurementPrivate* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

BasicErrorPoseMeasurement::BasicErrorPoseMeasurement(unsigned long long int const ts, const std::vector<double>& value,
        const std::vector<double>& c)
        :BasicMeasurement(ts), m_pPrivate(new BasicErrorPoseMeasurementPrivate(ts, value, c)) { }

BasicErrorPoseMeasurement::~BasicErrorPoseMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

bool BasicErrorPoseMeasurement::get(std::vector<double>& v)
{
    typedef TensorIndex<7> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::Pose* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);

            const Math::Vector<double, 3>& t = m->translation();
            v.at(0) = t(0);
            v.at(1) = t(1);
            v.at(2) = t(2);

            const Math::Quaternion& r = m->rotation();
            v.at(3) = r.x();
            v.at(4) = r.y();
            v.at(5) = r.z();
            v.at(6) = r.w();
            return true;
        }
    }
    return false;
}

bool BasicErrorPoseMeasurement::get(std::vector<float>& v)
{
    typedef TensorIndex<7> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::Pose* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);

            const Math::Vector<double, 3>& t = m->translation();
            v.at(0) = (float) (t(0));
            v.at(1) = (float) (t(1));
            v.at(2) = (float) (t(2));

            const Math::Quaternion& r = m->rotation();
            v.at(3) = (float) (r.x());
            v.at(4) = (float) (r.y());
            v.at(5) = (float) (r.z());
            v.at(6) = (float) (r.w());
            return true;
        }
    }
    return false;
}

bool BasicErrorPoseMeasurement::getCovariance(std::vector<double>& v)
{
    typedef TensorIndex<7, 7> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::ErrorPose* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);
            for (unsigned int i = 0; i<TI::LEN1; i++) {
                for (unsigned int j = 0; j<TI::LEN2; j++) {
                    v.at(TI::indexOf(i, j)) = m->covariance()(i, j);
                }
            }
            return true;
        }
    }
    return false;
}


/*
 * List Measurements
 */



// ScalarInt
BasicScalarIntListMeasurement::BasicScalarIntListMeasurement(unsigned long long int const ts,
        BasicScalarIntListMeasurementPrivate* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

BasicScalarIntListMeasurement::BasicScalarIntListMeasurement(unsigned long long int const ts, const std::vector<int>& value)
        :BasicMeasurement(ts), m_pPrivate(new BasicScalarIntListMeasurementPrivate(ts, value)) { }

BasicScalarIntListMeasurement::~BasicScalarIntListMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

bool BasicScalarIntListMeasurement::get(std::vector<int>& v)
{
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            std::vector< Math::Scalar<int> >* m = m_pPrivate->m_measurement.get();
            v.resize(m->size());
            for (unsigned int i = 0; i < m->size(); ++i) {
                v.at(i) = m->at(i);
            }
            return true;
        }
    }
    return false;
}

unsigned int BasicScalarIntListMeasurement::elementCount(){
    if (m_pPrivate) {
        return m_pPrivate->elementCount();
    }
    return 0;
}

// ScalarDouble
BasicScalarDoubleListMeasurement::BasicScalarDoubleListMeasurement(unsigned long long int const ts,
        BasicScalarDoubleListMeasurementPrivate* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

BasicScalarDoubleListMeasurement::BasicScalarDoubleListMeasurement(unsigned long long int const ts, const std::vector<double>& value)
        :BasicMeasurement(ts), m_pPrivate(new BasicScalarDoubleListMeasurementPrivate(ts, value)) { }

BasicScalarDoubleListMeasurement::~BasicScalarDoubleListMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

bool BasicScalarDoubleListMeasurement::get(std::vector<double>& v)
{
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            std::vector< Math::Scalar<double> >* m = m_pPrivate->m_measurement.get();
            v.resize(m->size());
            for (unsigned int i = 0; i < m->size(); ++i) {
                v.at(i) = m->at(i);
            }
            return true;
        }
    }
    return false;
}

bool BasicScalarDoubleListMeasurement::get(std::vector<float>& v)
{
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            std::vector< Math::Scalar<double> >* m = m_pPrivate->m_measurement.get();
            v.resize(m->size());
            for (unsigned int i = 0; i < m->size(); ++i) {
                v.at(i) = (float)m->at(i);
            }
            return true;
        }
    }
    return false;
}

unsigned int BasicScalarDoubleListMeasurement::elementCount(){
    if (m_pPrivate) {
        return m_pPrivate->elementCount();
    }
    return 0;
}

// Vec
template<int LEN>
BasicVectorListMeasurement<LEN>::BasicVectorListMeasurement(unsigned long long int const ts,
        BasicVectorListMeasurementPrivate<LEN>* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

template<int LEN>
BasicVectorListMeasurement<LEN>::BasicVectorListMeasurement(unsigned long long int const ts, const std::vector< std::vector<double> >& value)
        :BasicMeasurement(ts), m_pPrivate(new BasicVectorListMeasurementPrivate<LEN>(ts, value)) { }

template<int LEN>
BasicVectorListMeasurement<LEN>::~BasicVectorListMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

template<int LEN>
bool BasicVectorListMeasurement<LEN>::get(std::vector< std::vector<double> >& v)
{
    typedef TensorIndex<LEN> TI;

    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            std::vector< Math::Vector<double, LEN> >* m = m_pPrivate->m_measurement.get();
            v.reserve(v.size());
            for (unsigned int i = 0; i < v.size(); ++i) {
                v.at(i).reserve(TI::SIZE);
                for (unsigned int j = 0; j<TI::SIZE; j++) {
                    v.at(i).at(j) = (*m).at(i)(j);
                }
            }
            return true;
        }
    }
    return false;
}

template<int LEN>
bool BasicVectorListMeasurement<LEN>::get(std::vector< std::vector<float> >& v)
{
    typedef TensorIndex<LEN> TI;

    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            std::vector< Math::Vector<double, LEN> >* m = m_pPrivate->m_measurement.get();
            v.reserve(m->size());
            for (unsigned int i = 0; i < m->size(); ++i) {
                v.at(i).reserve(TI::SIZE);
                for (unsigned int j = 0; j<TI::SIZE; j++) {
                    v.at(i).at(j) = (float) m->at(i)(j);
                }
            }
            return true;
        }
    }
    return false;
}

template<int LEN>
unsigned int BasicVectorListMeasurement<LEN>::elementCount(){
    if (m_pPrivate) {
        return m_pPrivate->elementCount();
    }
    return 0;
}

// Pose
BasicPoseListMeasurement::BasicPoseListMeasurement(unsigned long long int const ts, BasicPoseListMeasurementPrivate* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

BasicPoseListMeasurement::BasicPoseListMeasurement(unsigned long long int const ts, const std::vector< std::vector<double> >& value)
        :BasicMeasurement(ts), m_pPrivate(new BasicPoseListMeasurementPrivate(ts, value)) { }

BasicPoseListMeasurement::~BasicPoseListMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

bool BasicPoseListMeasurement::get(std::vector< std::vector<double> >& v)
{
    typedef TensorIndex<7> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            std::vector< Math::Pose >* m = m_pPrivate->m_measurement.get();
            v.reserve(m->size());
            for (unsigned int i = 0; i < m->size(); ++i) {
                v.at(i).reserve(TI::SIZE);

                const Math::Vector<double, 3>& t = m->at(i).translation();
                v.at(i).at(0) = t(0);
                v.at(i).at(1) = t(1);
                v.at(i).at(2) = t(2);

                const Math::Quaternion& r = m->at(i).rotation();
                v.at(i).at(3) = r.x();
                v.at(i).at(4) = r.y();
                v.at(i).at(5) = r.z();
                v.at(i).at(6) = r.w();
            }
            return true;
        }
    }
    return false;
}

bool BasicPoseListMeasurement::get(std::vector< std::vector<float> >& v)
{
    typedef TensorIndex<7> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            std::vector< Math::Pose >* m = m_pPrivate->m_measurement.get();
            v.reserve(m->size());
            for (unsigned int i = 0; i < m->size(); ++i) {
                v.at(i).reserve(TI::SIZE);

                const Math::Vector<double, 3>& t = m->at(i).translation();
                v.at(i).at(0) = (float) t(0);
                v.at(i).at(1) = (float) t(1);
                v.at(i).at(2) = (float) t(2);

                const Math::Quaternion& r = m->at(i).rotation();
                v.at(i).at(3) = (float) r.x();
                v.at(i).at(4) = (float) r.y();
                v.at(i).at(5) = (float) r.z();
                v.at(i).at(6) = (float) r.w();
            }
            return true;
        }
    }
    return false;
}

unsigned int BasicPoseListMeasurement::elementCount(){
    if (m_pPrivate) {
        return m_pPrivate->elementCount();
    }
    return 0;
}

// ErrorVec
template<int LEN>
BasicErrorVectorListMeasurement<LEN>::BasicErrorVectorListMeasurement(unsigned long long int const ts,
        BasicErrorVectorListMeasurementPrivate<LEN>* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

template<int LEN>
BasicErrorVectorListMeasurement<LEN>::BasicErrorVectorListMeasurement(unsigned long long int const ts,
        const std::vector< std::vector<double> >& value, const std::vector< std::vector<double> >& cov)
        :BasicMeasurement(ts), m_pPrivate(new BasicErrorVectorListMeasurementPrivate<LEN>(ts, value, cov)) { }

template<int LEN>
BasicErrorVectorListMeasurement<LEN>::~BasicErrorVectorListMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

template<int LEN>
bool BasicErrorVectorListMeasurement<LEN>::get(std::vector< std::vector<double> >& v)
{
    typedef TensorIndex<LEN> TI;

    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            std::vector< Math::ErrorVector<double, LEN> >* m = m_pPrivate->m_measurement.get();
            v.reserve(m->size());
            for (unsigned int i = 0; i < m->size(); ++i) {
                v.at(i).reserve(TI::SIZE);
                for (unsigned int j = 0; j<TI::SIZE; j++) {
                    v.at(i).at(j) = m->at(i).value(j);
                }
            }
            return true;
        }
    }
    return false;
}

template<int LEN>
bool BasicErrorVectorListMeasurement<LEN>::getCovariance(std::vector< std::vector<double> >& v)
{
    typedef TensorIndex<LEN, LEN> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            std::vector< Math::ErrorVector<double, LEN> >* m = m_pPrivate->m_measurement.get();
            v.reserve(m->size());
            for (unsigned int i = 0; i < m->size(); ++i) {
                v.at(i).reserve(TI::SIZE);
                for (unsigned int j = 0; j<TI::SIZE; j++) {
                    for (unsigned int k = 0; k<TI::LEN2; k++) {
                        v.at(i).at(TI::indexOf(j, k)) = m->at(i).covariance(j, k);
                    }
                }
            }
            return true;
        }
    }
    return false;
}

template<int LEN>
unsigned int BasicErrorVectorListMeasurement<LEN>::elementCount(){
    if (m_pPrivate) {
        return m_pPrivate->elementCount();
    }
    return 0;
}

// ErrorPose
BasicErrorPoseListMeasurement::BasicErrorPoseListMeasurement(unsigned long long int const ts,
        BasicErrorPoseListMeasurementPrivate* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

BasicErrorPoseListMeasurement::BasicErrorPoseListMeasurement(unsigned long long int const ts, const std::vector< std::vector<double> >& value,
        const std::vector< std::vector<double> >& c)
        :BasicMeasurement(ts), m_pPrivate(new BasicErrorPoseListMeasurementPrivate(ts, value, c)) { }

BasicErrorPoseListMeasurement::~BasicErrorPoseListMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

bool BasicErrorPoseListMeasurement::get(std::vector< std::vector<double> >& v)
{
    typedef TensorIndex<7> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            std::vector< Math::ErrorPose >* m = m_pPrivate->m_measurement.get();
            v.reserve(m->size());
            for (unsigned int i = 0; i < m->size(); ++i) {
                v.at(i).reserve(TI::SIZE);

                const Math::Vector<double, 3>& t = m->at(i).translation();
                v.at(i).at(0) = t(0);
                v.at(i).at(1) = t(1);
                v.at(i).at(2) = t(2);

                const Math::Quaternion& r = m->at(i).rotation();
                v.at(i).at(3) = r.x();
                v.at(i).at(4) = r.y();
                v.at(i).at(5) = r.z();
                v.at(i).at(6) = r.w();
            }
            return true;
        }
    }
    return false;
}

bool BasicErrorPoseListMeasurement::get(std::vector< std::vector<float> >& v)
{
    typedef TensorIndex<7> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            std::vector< Math::ErrorPose >* m = m_pPrivate->m_measurement.get();
            v.reserve(m->size());
            for (unsigned int i = 0; i < m->size(); ++i) {
                v.at(i).reserve(TI::SIZE);

                const Math::Vector<double, 3>& t = m->at(i).translation();
                v.at(i).at(0) = (float) t(0);
                v.at(i).at(1) = (float) t(1);
                v.at(i).at(2) = (float) t(2);

                const Math::Quaternion& r = m->at(i).rotation();
                v.at(i).at(3) = (float) r.x();
                v.at(i).at(4) = (float) r.y();
                v.at(i).at(5) = (float) r.z();
                v.at(i).at(6) = (float) r.w();
            }
            return true;
        }
    }
    return false;
}

bool BasicErrorPoseListMeasurement::getCovariance(std::vector< std::vector<double> >& v)
{
    typedef TensorIndex<7, 7> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            std::vector< Math::ErrorPose >* m = m_pPrivate->m_measurement.get();
            v.reserve(m->size());
            for (unsigned int i = 0; i < m->size(); ++i) {
                v.at(i).reserve(TI::SIZE);
                const Math::Matrix< double, 6, 6 >&cv = m->at(i).covariance();
                for (unsigned int j = 0; j<TI::SIZE; j++) {
                    for (unsigned int k = 0; k<TI::LEN2; k++) {
                        v.at(i).at(TI::indexOf(j, k)) = cv(j, k);
                    }
                }
            }
            return true;
        }
    }
    return false;
}

unsigned int BasicErrorPoseListMeasurement::elementCount(){
    if (m_pPrivate) {
        return m_pPrivate->elementCount();
    }
    return 0;
}


/*
 * Composite Measurements
 */


// CameraIntrinsics
BasicCameraIntrinsicsMeasurement::BasicCameraIntrinsicsMeasurement(unsigned long long int const ts,
        BasicCameraIntrinsicsMeasurementPrivate* _pPrivate)
        :BasicMeasurement(ts), m_pPrivate(_pPrivate) { }

BasicCameraIntrinsicsMeasurement::BasicCameraIntrinsicsMeasurement(unsigned long long int const ts,
        const std::vector<double>& intrinsics, const std::vector<double>& radial, const std::vector<double>& tangential)
        :BasicMeasurement(ts),
         m_pPrivate(new BasicCameraIntrinsicsMeasurementPrivate(ts, intrinsics, radial, tangential)) { }

BasicCameraIntrinsicsMeasurement::~BasicCameraIntrinsicsMeasurement()
{
    if (m_pPrivate) {
        delete (m_pPrivate);
    }
}

bool BasicCameraIntrinsicsMeasurement::get(std::vector<double>& v)
{
    typedef TensorIndex<3, 3> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::CameraIntrinsics<double>* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);
            for (unsigned int i = 0; i<TI::LEN1; i++) {
                for (unsigned int j = 0; j<TI::LEN2; j++) {
                    v.at(TI::indexOf(i, j)) = (*m).matrix(i, j);
                }
            }
            return true;
        }
    }
    return false;
}

bool BasicCameraIntrinsicsMeasurement::getResolution(std::vector<double>& v)
{
    typedef TensorIndex<2> TI;

    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::CameraIntrinsics<double>* m = m_pPrivate->m_measurement.get();
            v.reserve(TI::SIZE);
            for (unsigned int i = 0; i<TI::SIZE; i++) {
                v.at(i) = m->dimension(i);
            }
            return true;
        }
    }
    return false;
}

bool BasicCameraIntrinsicsMeasurement::getDistortion(std::vector<double>& radial, std::vector<double>& tangential)
{
    typedef TensorIndex<6> TI1;
    typedef TensorIndex<2> TI2;

    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::CameraIntrinsics<double>* m = m_pPrivate->m_measurement.get();
            radial.reserve(TI1::SIZE);
            for (unsigned int i = 0; i<TI1::SIZE; i++) {
                radial.at(i) = m->radial_params(i);
            }
            tangential.reserve(TI2::SIZE);
            for (unsigned int i = 0; i<TI2::SIZE; i++) {
                tangential.at(i) = m->tangential_params(i);
            }
            return true;
        }
    }
    return false;
}

bool BasicCameraIntrinsicsMeasurement::getOpenGLProjectionMatrix(double l, double r, double b, double t, double n, double f, std::vector<double>& v)
{
    typedef TensorIndex<4, 4> TI;
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Math::CameraIntrinsics<double>* m = m_pPrivate->m_measurement.get();
            Math::Matrix< double, 4, 4> proj_mat = Algorithm::projectionMatrixToOpenGL(l, r, b, t, n, f, (*m).matrix);

            v.reserve(TI::SIZE);
            for (unsigned int i = 0; i<TI::LEN1; i++) {
                for (unsigned int j = 0; j<TI::LEN2; j++) {
                    v.at(TI::indexOf(i, j)) = proj_mat(i, j);
                }
            }
            return true;
        }
    }
    return false;
}

#ifdef HAVE_OPENCV
// Image
BasicImageMeasurement::BasicImageMeasurement(unsigned long long int const ts, BasicImageMeasurementPrivate* _pPrivate)
        : BasicMeasurement(ts)
        , m_pPrivate(_pPrivate) {}

BasicImageMeasurement::BasicImageMeasurement(unsigned long long int const ts, int width, int height, int depth, int channels, unsigned char* data, PixelFormat pixel_format, bool copy_data)
        : BasicMeasurement(ts)
        , m_pPrivate(new BasicImageMeasurementPrivate(ts, width, height, depth, channels, data, (Vision::Image::PixelFormat)pixel_format, copy_data)) {}

BasicImageMeasurement::~BasicImageMeasurement() {
    if (m_pPrivate) {
        delete(m_pPrivate);
    }
}

int BasicImageMeasurement::getDimX() const {
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            return m_pPrivate->m_measurement->width();
        }
    }
    return 0;
}

int BasicImageMeasurement::getDimY() const {
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            return m_pPrivate->m_measurement->height();
        }
    }
    return 0;
}

int BasicImageMeasurement::getDimZ() const {
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            return m_pPrivate->m_measurement->channels();
        }
    }
    return 0;
}

unsigned int BasicImageMeasurement::getPixelSize() const {
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Measurement::ImageMeasurement& m = m_pPrivate->m_measurement;
            return m->bitsPerPixel();
        }
    }
    return 0;
}

BasicImageMeasurement::PixelFormat BasicImageMeasurement::getPixelFormat() const {
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Measurement::ImageMeasurement& m = m_pPrivate->m_measurement;
            return (PixelFormat)m->pixelFormat();
        }
    }
    return BasicImageMeasurement::UNKNOWN_PIXELFORMAT;
}

unsigned int BasicImageMeasurement::getOrigin() const {
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Measurement::ImageMeasurement& m = m_pPrivate->m_measurement;
            return m->origin();
        }
    }
    return 0;
}

unsigned int BasicImageMeasurement::getChannels() const {
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Measurement::ImageMeasurement& m = m_pPrivate->m_measurement;
            return m->channels();
        }
    }
    return 0;
}

unsigned int BasicImageMeasurement::getByteCount() const {
    return size() * getPixelSize();
}

unsigned int BasicImageMeasurement::getStep() const {
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            return m_pPrivate->m_measurement->Mat().step;
        }
    }
    return 0;
}

unsigned char* BasicImageMeasurement::getDataPtr() const {
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            return (unsigned char *) m_pPrivate->m_measurement->Mat().data;
        }
    }
    return NULL;
}

bool BasicImageMeasurement::get(unsigned int size, unsigned char* data) {
    if (m_pPrivate) {
        if (m_pPrivate->m_measurement) {
            Measurement::ImageMeasurement& m = m_pPrivate->m_measurement;
            unsigned int frame_bytes = getByteCount();

            if (size < frame_bytes) {
                frame_bytes = size;
            }

            unsigned char* srcData = (unsigned char*) m->Mat().data;
            unsigned char* dstData = (unsigned char*) data;
            memcpy(dstData, srcData, sizeof(unsigned char)*frame_bytes);

            return true;
        }
    }
    return false;
}
#endif

}
}

template class Ubitrack::Facade::BasicVectorMeasurement<2>;
template class Ubitrack::Facade::BasicVectorMeasurement<3>;
template class Ubitrack::Facade::BasicVectorMeasurement<4>;
template class Ubitrack::Facade::BasicVectorMeasurement<8>;

template class Ubitrack::Facade::BasicMatrixMeasurement<3, 3>;
template class Ubitrack::Facade::BasicMatrixMeasurement<3, 4>;
template class Ubitrack::Facade::BasicMatrixMeasurement<4, 4>;

template class Ubitrack::Facade::BasicErrorVectorMeasurement<2>;
template class Ubitrack::Facade::BasicErrorVectorMeasurement<3>;


template class Ubitrack::Facade::BasicVectorListMeasurement<2>;
template class Ubitrack::Facade::BasicVectorListMeasurement<3>;

template class Ubitrack::Facade::BasicErrorVectorListMeasurement<2>;
template class Ubitrack::Facade::BasicErrorVectorListMeasurement<3>;

#endif // ENABLE_BASICFACADE