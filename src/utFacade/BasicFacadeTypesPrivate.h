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
#ifndef __UBITRACK_FACADE_BASICDATATYPESPRIVATE_H_INCLUDED__
#define __UBITRACK_FACADE_BASICDATATYPESPRIVATE_H_INCLUDED__

#include "BasicFacadeTypes.h"

#include "utMeasurement/Measurement.h"

namespace Ubitrack {
    namespace Facade {
        /**
        * taken from: http://www.sitmo.com/article/a-simple-and-extremely-fast-c-template-for-matrices-and-tensors/
        */
        template <int d1,int d2=1,int d3=1>
        class TensorIndex {
        public:
            enum {SIZE = d1*d2*d3 };
            enum {LEN1 = d1 };
            enum {LEN2 = d2 };
            enum {LEN3 = d3 };

            static int indexOf(const int i) {
                return i;
            }
            static int indexOf(const int i,const int j) {
                return j*d1 + i;
            }
            static int indexOf(const int i,const int j, const int k) {
                return (k*d2 + j)*d1 + i;
            }
        };

        template< typename BMT >
        struct BasicMeasurementTypeTrait {
            static const bool supported = false;
        };

        // ScalarInt
        struct BasicScalarIntMeasurementPrivate {

            BasicScalarIntMeasurementPrivate(unsigned long long int const ts, const int v)
            : m_measurement(Measurement::Button(ts, Math::Scalar< int >(v) )) {}

            BasicScalarIntMeasurementPrivate(const Measurement::Button& m) : m_measurement(m) {}

            void clear() {
                m_measurement.reset();
            }

            Measurement::Button m_measurement;

        };

        template<>
        struct BasicMeasurementTypeTrait< BasicScalarIntMeasurement > {
            static const bool supported = true;
            typedef BasicScalarIntMeasurementPrivate private_measurement_type;
            typedef Measurement::Button ubitrack_measurement_type;
        };

        // ScalarDouble
        struct BasicScalarDoubleMeasurementPrivate {

            BasicScalarDoubleMeasurementPrivate(unsigned long long int const ts, const double v)
               : m_measurement(Measurement::Distance(ts, Math::Scalar< double >(v) )) {}

            BasicScalarDoubleMeasurementPrivate(const Measurement::Distance& m) : m_measurement(m) {}

            void clear() {
                m_measurement.reset();
            }

            Measurement::Distance m_measurement;

        };

        template<>
        struct BasicMeasurementTypeTrait< BasicScalarDoubleMeasurement > {
            static const bool supported = true;
            typedef BasicScalarDoubleMeasurementPrivate private_measurement_type;
            typedef Measurement::Distance ubitrack_measurement_type;
        };

        struct BasicVector2MeasurementPrivate {

            BasicVector2MeasurementPrivate(unsigned long long int const ts, const std::vector<double>& v)
            : m_measurement(Measurement::Position2D(ts, Math::Vector< double, 2>(&v.front()))) {}

            BasicVector2MeasurementPrivate(const Measurement::Position2D& m) : m_measurement(m) {}

            void clear() {
                m_measurement.reset();
            }

            Measurement::Position2D m_measurement;

        };

        template<>
        struct BasicMeasurementTypeTrait< BasicVector2Measurement > {
            static const bool supported = true;
            typedef BasicVector2MeasurementPrivate private_measurement_type;
            typedef Measurement::Position2D ubitrack_measurement_type;
        };

        /**
        * M*N elements (row-major)
        */
        struct BasicMatrix33MeasurementPrivate {

            BasicMatrix33MeasurementPrivate(unsigned long long int const ts, const std::vector<double>& v)
            : m_measurement(Measurement::Matrix3x3(ts, Math::Matrix< double, 3, 3 >(&v.front()))) {}

            BasicMatrix33MeasurementPrivate(const Measurement::Matrix3x3& m) : m_measurement(m) {}

            void clear() {
                m_measurement.reset();
            }

            Measurement::Matrix3x3 m_measurement;

        };

        template<>
        struct BasicMeasurementTypeTrait< BasicMatrix33Measurement > {
            static const bool supported = true;
            typedef BasicMatrix33MeasurementPrivate private_measurement_type;
            typedef Measurement::Matrix3x3 ubitrack_measurement_type;
        };


        /**
        * Pose measurement as vector [x, y, z, rx, ry, rz, rw]
        */
        struct BasicPoseMeasurementPrivate {

            BasicPoseMeasurementPrivate(unsigned long long int const ts, const std::vector<double>& v)
               : m_measurement(Measurement::Pose(ts,
                        Math::Pose(
                                Math::Quaternion(v[3], v[4], v[5], v[6]),
                                Math::Vector< double, 3 >(v[0], v[1], v[2] )
                        ))) {}

            BasicPoseMeasurementPrivate(const Measurement::Pose& m) {
                m_measurement = m;
            }

            void clear() {
                m_measurement.reset();
            }

            Measurement::Pose m_measurement;

        };

        template<>
        struct BasicMeasurementTypeTrait< BasicPoseMeasurement > {
            static const bool supported = true;
            typedef BasicPoseMeasurementPrivate private_measurement_type;
            typedef Measurement::Pose ubitrack_measurement_type;
        };

    }
} // namespace Ubitrack::Facade

#endif
