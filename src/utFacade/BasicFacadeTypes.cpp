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

#include "BasicFacadeTypesPrivate.h"
#include <algorithm>

namespace Ubitrack {
    namespace Facade {

        // ScalarInt
        BasicScalarIntMeasurement::BasicScalarIntMeasurement(unsigned long long int const ts, BasicScalarIntMeasurementPrivate* _pPrivate)
                : BasicMeasurement(ts)
                , m_pPrivate(_pPrivate) {}

        BasicScalarIntMeasurement::BasicScalarIntMeasurement(unsigned long long int const ts, const int value)
                : BasicMeasurement(ts)
                , m_pPrivate(new BasicScalarIntMeasurementPrivate(ts, value)) {}


        BasicScalarIntMeasurement::~BasicScalarIntMeasurement() {
            if (m_pPrivate) {
                delete(m_pPrivate);
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
                : BasicMeasurement(ts)
                , m_pPrivate(new BasicScalarDoubleMeasurementPrivate(ts, value)) {}

        BasicScalarDoubleMeasurement::~BasicScalarDoubleMeasurement() {
            if (m_pPrivate) {
                delete(m_pPrivate);
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

        bool BasicScalarDoubleMeasurement::get(float& v) {
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    v = (float)(*(m_pPrivate->m_measurement.get()));
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
                : BasicMeasurement(ts)
                , m_pPrivate(new BasicVectorMeasurementPrivate< LEN >(ts, value)) {}

        template< int LEN >
        BasicVectorMeasurement< LEN >::~BasicVectorMeasurement() {
            if (m_pPrivate) {
                delete(m_pPrivate);
            }
        }

        template< int LEN >
        bool BasicVectorMeasurement< LEN >::get(std::vector<double>& v) {
            typedef TensorIndex< LEN > TI;

            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    Math::Vector< double, LEN>* m = m_pPrivate->m_measurement.get();
                    v.reserve(TI::SIZE);
                    for (unsigned int i = 0; i < TI::SIZE; i++) {
                        v.at(i) = (*m)(i);
                    }
                    return true;
                }
            }
            return false;
        }

        template< int LEN >
        bool BasicVectorMeasurement< LEN >::get(std::vector<float>& v) {
            typedef TensorIndex< LEN > TI;

            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    Math::Vector< double, LEN>* m = m_pPrivate->m_measurement.get();
                    v.reserve(TI::SIZE);
                    for (unsigned int i = 0; i < TI::SIZE; i++) {
                        v.at(i) = (float)((*m)(i));
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
                : BasicMeasurement(ts)
                , m_pPrivate(new BasicMatrixMeasurementPrivate< ROWS, COLS >(ts, value)) {}

        template< int ROWS, int COLS >
        BasicMatrixMeasurement< ROWS, COLS >::~BasicMatrixMeasurement() {
            if (m_pPrivate) {
                delete(m_pPrivate);
            }
        }

        template< int ROWS, int COLS >
        bool BasicMatrixMeasurement< ROWS, COLS >::get(std::vector<double>& v) {
            typedef TensorIndex< ROWS, COLS > TI;
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    Math::Matrix< double, ROWS, COLS >* m = m_pPrivate->m_measurement.get();
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

        template< int ROWS, int COLS >
        bool BasicMatrixMeasurement< ROWS, COLS >::get(std::vector<float>& v) {
            typedef TensorIndex< ROWS, COLS > TI;
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    Math::Matrix< double, ROWS, COLS >* m = m_pPrivate->m_measurement.get();
                    v.reserve(TI::SIZE);
                    for (unsigned int i = 0; i < TI::LEN1; i++) {
                        for (unsigned int j = 0; j < TI::LEN2; j++) {
                            v.at(TI::indexOf(i, j)) = (float)((*m)(i, j));
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
                : BasicMeasurement(ts)
                , m_pPrivate(new BasicPoseMeasurementPrivate(ts, value)) {}

        BasicPoseMeasurement::~BasicPoseMeasurement() {
            if (m_pPrivate) {
                delete(m_pPrivate);
            }
        }

        bool BasicPoseMeasurement::get(std::vector<double>& v) {
            typedef TensorIndex< 7 > TI;
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    Math::Pose* m = m_pPrivate->m_measurement.get();
                    v.reserve(TI::SIZE);

                    const Math::Vector< double, 3 >& t = m->translation();
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

        bool BasicPoseMeasurement::get(std::vector<float>& v) {
            typedef TensorIndex< 7 > TI;
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    Math::Pose* m = m_pPrivate->m_measurement.get();
                    v.reserve(TI::SIZE);

                    const Math::Vector< double, 3 >& t = m->translation();
                    v.at(0) = (float)(t(0));
                    v.at(1) = (float)(t(1));
                    v.at(2) = (float)(t(2));

                    const Math::Quaternion& r = m->rotation();
                    v.at(3) = (float)(r.x());
                    v.at(4) = (float)(r.y());
                    v.at(5) = (float)(r.z());
                    v.at(6) = (float)(r.w());
                    return true;
                }
            }
            return false;
        }

        // Rotation
        BasicRotationMeasurement::BasicRotationMeasurement(unsigned long long int const ts, BasicRotationMeasurementPrivate* _pPrivate)
                : BasicMeasurement(ts)
                , m_pPrivate(_pPrivate) {}

        BasicRotationMeasurement::BasicRotationMeasurement(unsigned long long int const ts, const std::vector<double>& value)
                : BasicMeasurement(ts)
                , m_pPrivate(new BasicRotationMeasurementPrivate(ts, value)) {}

        BasicRotationMeasurement::~BasicRotationMeasurement() {
            if (m_pPrivate) {
                delete(m_pPrivate);
            }
        }

        bool BasicRotationMeasurement::get(std::vector<double>& v) {
            typedef TensorIndex< 4 > TI;
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

        bool BasicRotationMeasurement::get(std::vector<float>& v) {
            typedef TensorIndex< 4 > TI;
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    Math::Quaternion* m = m_pPrivate->m_measurement.get();
                    v.reserve(TI::SIZE);

                    v.at(3) = (float)(m->x());
                    v.at(4) = (float)(m->y());
                    v.at(5) = (float)(m->z());
                    v.at(6) = (float)(m->w());

                    return true;
                }
            }
            return false;
        }

        // ErrorVec
        template< int LEN >
        BasicErrorVectorMeasurement< LEN >::BasicErrorVectorMeasurement(unsigned long long int const ts, BasicErrorVectorMeasurementPrivate< LEN >* _pPrivate)
                : BasicMeasurement(ts)
                , m_pPrivate(_pPrivate) {}

        template< int LEN >
        BasicErrorVectorMeasurement< LEN >::BasicErrorVectorMeasurement(unsigned long long int const ts, const std::vector<double>& value, const std::vector<double>& cov)
                : BasicMeasurement(ts)
                , m_pPrivate(new BasicErrorVectorMeasurementPrivate< LEN >(ts, value, cov)) {}

        template< int LEN >
        BasicErrorVectorMeasurement< LEN >::~BasicErrorVectorMeasurement() {
            if (m_pPrivate) {
                delete(m_pPrivate);
            }
        }

        template< int LEN >
        bool BasicErrorVectorMeasurement< LEN >::get(std::vector<double>& v) {
            typedef TensorIndex< LEN > TI;

            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    Math::ErrorVector< double, LEN>* m = m_pPrivate->m_measurement.get();
                    v.reserve(TI::SIZE);
                    for (unsigned int i = 0; i < TI::SIZE; i++) {
                        v.at(i) = m->value(i);
                    }
                    return true;
                }
            }
            return false;
        }

        template< int LEN >
        bool BasicErrorVectorMeasurement< LEN >::getCovariance(std::vector<double>& v) {
            typedef TensorIndex< LEN, LEN > TI;
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    Math::ErrorVector< double, LEN>* m = m_pPrivate->m_measurement.get();
                    v.reserve(TI::SIZE);
                    for (unsigned int i = 0; i < TI::LEN1; i++) {
                        for (unsigned int j = 0; j < TI::LEN2; j++) {
                            v.at(TI::indexOf(i, j)) = m->covariance(i, j);
                        }
                    }
                    return true;
                }
            }
            return false;
        }

        // ErrorPose (TBD)

        // CameraIntrinsics
        BasicCameraIntrinsicsMeasurement::BasicCameraIntrinsicsMeasurement(unsigned long long int const ts, BasicCameraIntrinsicsMeasurementPrivate* _pPrivate)
                : BasicMeasurement(ts)
                , m_pPrivate(_pPrivate) {}

        BasicCameraIntrinsicsMeasurement::BasicCameraIntrinsicsMeasurement(unsigned long long int const ts, const std::vector<double>& intrinsics, const std::vector<double>& radial, const std::vector<double>& tangential)
                : BasicMeasurement(ts)
                , m_pPrivate(new BasicCameraIntrinsicsMeasurementPrivate(ts, intrinsics, radial, tangential)) {}

        BasicCameraIntrinsicsMeasurement::~BasicCameraIntrinsicsMeasurement() {
            if (m_pPrivate) {
                delete(m_pPrivate);
            }
        }

		bool BasicCameraIntrinsicsMeasurement::get(std::vector<double>& v) {
            typedef TensorIndex< 3, 3 > TI;
            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
					Math::CameraIntrinsics<double>* m = m_pPrivate->m_measurement.get();
                    v.reserve(TI::SIZE);
                    for (unsigned int i = 0; i < TI::LEN1; i++) {
                        for (unsigned int j = 0; j < TI::LEN2; j++) {
							v.at(TI::indexOf(i, j)) = (*m).matrix(i, j);
                        }
                    }
                    return true;
                }
            }
            return false;
        }

        bool BasicCameraIntrinsicsMeasurement::getResolution(std::vector<double>& v) {
            typedef TensorIndex< 2 > TI;

            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    Math::CameraIntrinsics<double>* m = m_pPrivate->m_measurement.get();
                    v.reserve(TI::SIZE);
                    for (unsigned int i = 0; i < TI::SIZE; i++) {
                        v.at(i) = m->dimension(i);
                    }
                    return true;
                }
            }
            return false;
        }

        bool BasicCameraIntrinsicsMeasurement::getDistortion(std::vector<double>& radial, std::vector<double>& tangential) {
            typedef TensorIndex< 6 > TI1;
            typedef TensorIndex< 2 > TI2;

            if (m_pPrivate) {
                if (m_pPrivate->m_measurement) {
                    Math::CameraIntrinsics<double>* m = m_pPrivate->m_measurement.get();
                    radial.reserve(TI1::SIZE);
                    for (unsigned int i = 0; i < TI1::SIZE; i++) {
						radial.at(i) = m->radial_params(i);
                    }
                    tangential.reserve(TI2::SIZE);
                    for (unsigned int i = 0; i < TI2::SIZE; i++) {
						tangential.at(i) = m->tangential_params(i);
                    }
                    return true;
                }
            }
            return false;
        }
		
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
                    return m->depth();
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

        unsigned int BasicImageMeasurement::getByteCount() const {
            return size() * getPixelSize();
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


    }
}



template class Ubitrack::Facade::BasicVectorMeasurement< 2 >;
template class Ubitrack::Facade::BasicVectorMeasurement< 3 >;
template class Ubitrack::Facade::BasicVectorMeasurement< 4 >;
template class Ubitrack::Facade::BasicVectorMeasurement< 8 >;

template class Ubitrack::Facade::BasicMatrixMeasurement< 3, 3 >;
template class Ubitrack::Facade::BasicMatrixMeasurement< 3, 4 >;
template class Ubitrack::Facade::BasicMatrixMeasurement< 4, 4 >;

template class Ubitrack::Facade::BasicErrorVectorMeasurement< 2 >;
template class Ubitrack::Facade::BasicErrorVectorMeasurement< 3 >;

#endif // ENABLE_BASICFACADE