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
#ifndef __UBITRACK_FACADE_BASICDATATYPES_H_INCLUDED__
#define __UBITRACK_FACADE_BASICDATATYPES_H_INCLUDED__

#include <vector>

namespace Ubitrack {
    namespace Facade {

#define BASICFACADE_USE_STRING_ARGUMENTS
#ifdef BASICFACADE_USE_STRING_ARGUMENTS
        typedef const std::string basic_facade_string_type;
#else
        typedef const char* basic_facade_string_type;
#endif


        // forward declarations
        struct BasicScalarIntMeasurementPrivate;
        struct BasicScalarDoubleMeasurementPrivate;
        struct BasicVector2MeasurementPrivate;
        struct BasicMatrix33MeasurementPrivate;
        struct BasicPoseMeasurementPrivate;


        class BasicMeasurement {
        public:

            enum DataType {
                SCALARI = 0,
                SCALARD,
                VECTOR2D,
                VECTOR3D,
                VECTOR4D,
                MATRIX33D,
                MATRIX34D,
                MATRIX44D,
                POSE,
                QUATERNION,
                ERROR_VECTOR,
                ERROR_POSE,
                IMAGE
            };
            BasicMeasurement() : m_timestamp(0), m_valid(false) {};
            BasicMeasurement(unsigned long long int ts) : m_timestamp(ts), m_valid(true) {};
            virtual ~BasicMeasurement() {};

            unsigned long long int const time();
            bool is_valid() const { return m_valid; };

            virtual DataType getDataType() = 0;
            virtual int getDimX() = 0;
            virtual int getDimY() = 0;
            virtual int getDimZ() = 0;

        protected:
            unsigned long long int m_timestamp;
            bool m_valid;
        };

        /** wrapper for scalar measurement **/
        class BasicScalarIntMeasurement : public BasicMeasurement {
        public:
            BasicScalarIntMeasurement() : BasicMeasurement(), m_pPrivate(NULL) {};
            BasicScalarIntMeasurement(unsigned long long int const ts, const int value);
            BasicScalarIntMeasurement(unsigned long long int const ts, BasicScalarIntMeasurementPrivate* _pPrivate);
            ~BasicScalarIntMeasurement();

            virtual DataType getDataType() { return SCALARI; }
            virtual int getDimX() { return 1; }
            virtual int getDimY() { return 1; }
            virtual int getDimZ() { return 1; }

            /* get int v */
            bool get(int& v);

//        private:
            BasicScalarIntMeasurementPrivate* m_pPrivate;
        };

        class BasicScalarDoubleMeasurement : public BasicMeasurement {
        public:
            BasicScalarDoubleMeasurement() : BasicMeasurement(), m_pPrivate(NULL) {};
            BasicScalarDoubleMeasurement(unsigned long long int const ts, const double value);
            BasicScalarDoubleMeasurement(unsigned long long int const ts, BasicScalarDoubleMeasurementPrivate* _pPrivate);
            ~BasicScalarDoubleMeasurement();

            virtual DataType getDataType() { return SCALARI; }
            virtual int getDimX() { return 1; }
            virtual int getDimY() { return 1; }
            virtual int getDimZ() { return 1; }

            /* get int v */
            bool get(double& v);

//        private:
            BasicScalarDoubleMeasurementPrivate* m_pPrivate;
        };


        /** wrapper for vector2 measurement **/
        class BasicVector2Measurement : public BasicMeasurement {
        public:
            BasicVector2Measurement() : BasicMeasurement(), m_pPrivate(NULL) {};
            BasicVector2Measurement(unsigned long long int const ts, const std::vector<double>& v);
            BasicVector2Measurement(unsigned long long int const ts, BasicVector2MeasurementPrivate* _pPrivate);
            ~BasicVector2Measurement();

            virtual DataType getDataType() { return VECTOR2D; }
            virtual int getDimX() { return 2; }
            virtual int getDimY() { return 1; }
            virtual int getDimZ() { return 1; }

            /* get vec2 v */
            bool get( std::vector<double>& v );

//        private:
            BasicVector2MeasurementPrivate* m_pPrivate;
        };
        // Vector3
        // Vector4

        /** wrapper for matrix33 measurement **/
        class BasicMatrix33Measurement : public BasicMeasurement {
        public:
            BasicMatrix33Measurement() : BasicMeasurement(), m_pPrivate(NULL) {};
            /* set mat33 rows from vector M*N row-major */
            BasicMatrix33Measurement(unsigned long long int const ts, const std::vector<double>& v);
            BasicMatrix33Measurement(unsigned long long int const ts, BasicMatrix33MeasurementPrivate* _pPrivate);
            ~BasicMatrix33Measurement();

            virtual DataType getDataType() { return MATRIX33D; }
            virtual int getDimX() { return 3; }
            virtual int getDimY() { return 3; }
            virtual int getDimZ() { return 1; }

            /* get mat33 rows as vector M*N row-major */
            bool get( std::vector<double>& v );

//        private:
            BasicMatrix33MeasurementPrivate* m_pPrivate;
        };
        // Matrix34
        // Matrix44

        /** wrapper for pose measurement **/
        class BasicPoseMeasurement : public BasicMeasurement {
        public:
            BasicPoseMeasurement() : BasicMeasurement(), m_pPrivate(NULL) {};
            /* set pose from vector [x, y, z, rx, ry, rz, rw] */
            BasicPoseMeasurement(unsigned long long int const ts, const std::vector<double>& v);
            BasicPoseMeasurement(unsigned long long int const ts, BasicPoseMeasurementPrivate* _pPrivate);
            ~BasicPoseMeasurement();

            virtual DataType getDataType() { return POSE; }
            virtual int getDimX() { return 7; }
            virtual int getDimY() { return 1; }
            virtual int getDimZ() { return 1; }

            /* get pose as vector [x, y, z, rx, ry, rz, rw] */
            bool get( std::vector<double>& v );

//        private:
            BasicPoseMeasurementPrivate* m_pPrivate;
        };
        // Rotation

        // ErrorVector2
        // ErrorVector3
        // ErrorVector4
        // ErrorPose

        // Image


        /**
        * A Basic data flow observer
        */
        class BasicDataflowObserver
        {
        public:
            /** called when a component is added */
            virtual void notifyAddComponent( const char* sPatternName, const char* sComponentName ) throw() = 0;

            /** called when a component is removed */
            virtual void notifyDeleteComponent( const char* sPatternName, const char* sComponentName ) throw() = 0;

            /** virtual destructor */
            virtual ~BasicDataflowObserver()
            {}
        };
    }
} // namespace Ubitrack::Facade

#endif
