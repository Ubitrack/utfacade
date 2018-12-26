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
#include <utFacade/utFacade.h>
#include <utFacade/Config.h>
#include <memory>
#include <vector>

namespace Ubitrack {
namespace Facade {

// forward declarations
struct BasicScalarIntMeasurementPrivate;
struct BasicScalarDoubleMeasurementPrivate;

template<int LEN>
struct BasicVectorMeasurementPrivate;

template<int ROWS, int COLS>
struct BasicMatrixMeasurementPrivate;

struct BasicPoseMeasurementPrivate;

template<int LEN>
struct BasicErrorVectorMeasurementPrivate;
struct BasicErrorPoseMeasurementPrivate;

struct BasicRotationMeasurementPrivate;

struct BasicScalarIntListMeasurementPrivate;
struct BasicScalarDoubleListMeasurementPrivate;

template<int LEN>
struct BasicVectorListMeasurementPrivate;

template<int ROWS, int COLS>
struct BasicMatrixListMeasurementPrivate;

struct BasicPoseListMeasurementPrivate;

template<int LEN>
struct BasicErrorVectorListMeasurementPrivate;
struct BasicErrorPoseListMeasurementPrivate;

struct BasicRotationListMeasurementPrivate;

#ifdef HAVE_OPENCV
struct BasicImageMeasurementPrivate;
#endif 

struct BasicCameraIntrinsicsMeasurementPrivate;

class UTFACADE_EXPORT BasicMeasurement {
public:

    enum DataType {
      SCALARI = 0,
      SCALARD,
      VECTORD,
      MATRIXD,
      POSE,
      QUATERNION,
      ERROR_VECTOR,
      ERROR_POSE,
      CAMERA_INTRINSICS,
#ifdef HAVE_OPENCV
      IMAGE,
#endif
      SCALARI_LIST,
      SCALARD_LIST,
      VECTORD_LIST,
      MATRIXD_LIST,
      POSE_LIST,
      QUATERNION_LIST,
      ERROR_VECTOR_LIST,
      ERROR_POSE_LIST,

    };

    BasicMeasurement()
            :m_timestamp(0), m_valid(false) { };
    BasicMeasurement(unsigned long long int ts)
            :m_timestamp(ts), m_valid(true) { };
    virtual ~BasicMeasurement() { };

    unsigned long long int const time() { return m_timestamp; };
    bool isValid() const { return m_valid; };

    virtual int size() const { return getDimX()*getDimY()*getDimZ(); }
    virtual DataType getDataType() const = 0;
    virtual int getDimX() const = 0;
    virtual int getDimY() const = 0;
    virtual int getDimZ() const = 0;

    virtual unsigned int elementCount() { return 1; }

protected:
    unsigned long long int m_timestamp;
    bool m_valid;
};

/*
 * Single Measurements
 */

/** wrapper for scalar measurement **/
class UTFACADE_EXPORT BasicScalarIntMeasurement: public BasicMeasurement {
public:
    BasicScalarIntMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    BasicScalarIntMeasurement(unsigned long long int const ts, const int value);
    BasicScalarIntMeasurement(unsigned long long int const ts, BasicScalarIntMeasurementPrivate* _pPrivate);
    ~BasicScalarIntMeasurement();

    virtual DataType getDataType() const { return SCALARI; }
    virtual int getDimX() const { return 1; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get int v */
    bool get(int& v);

//        private:
    BasicScalarIntMeasurementPrivate* m_pPrivate;
};

class UTFACADE_EXPORT BasicScalarDoubleMeasurement: public BasicMeasurement {
public:
    BasicScalarDoubleMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    BasicScalarDoubleMeasurement(unsigned long long int const ts, const double value);
    BasicScalarDoubleMeasurement(unsigned long long int const ts, BasicScalarDoubleMeasurementPrivate* _pPrivate);
    ~BasicScalarDoubleMeasurement();

    virtual DataType getDataType() const { return SCALARD; }
    virtual int getDimX() const { return 1; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get int v */
    bool get(double& v);
    bool get(float& v);

//        private:
    BasicScalarDoubleMeasurementPrivate* m_pPrivate;
};

/** wrapper for vector2 measurement **/
template<int LEN = 2>
class UTFACADE_EXPORT BasicVectorMeasurement: public BasicMeasurement {
public:
    BasicVectorMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    BasicVectorMeasurement(unsigned long long int const ts, const std::vector<double>& v);
    BasicVectorMeasurement(unsigned long long int const ts, BasicVectorMeasurementPrivate<LEN>* _pPrivate);
    ~BasicVectorMeasurement();

    virtual DataType getDataType() const { return VECTORD; }
    virtual int getDimX() const { return LEN; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get vec2 v */
    bool get(std::vector<double>& v);
    bool get(std::vector<float>& v);

//        private:
    BasicVectorMeasurementPrivate<LEN>* m_pPrivate;
};

/** wrapper for matrix33 measurement **/
template<int ROWS = 3, int COLS = 3>
class UTFACADE_EXPORT BasicMatrixMeasurement: public BasicMeasurement {
public:
    BasicMatrixMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    /* set mat rows from vector M*N row-major */
    BasicMatrixMeasurement(unsigned long long int const ts, const std::vector<double>& v);
    BasicMatrixMeasurement(unsigned long long int const ts, BasicMatrixMeasurementPrivate<ROWS, COLS>* _pPrivate);
    ~BasicMatrixMeasurement();

    virtual DataType getDataType() const { return MATRIXD; }
    virtual int getDimX() const { return ROWS; }
    virtual int getDimY() const { return COLS; }
    virtual int getDimZ() const { return 1; }

    /* get mat33 rows as vector M*N row-major */
    bool get(std::vector<double>& v);
    bool get(std::vector<float>& v);

//        private:
    BasicMatrixMeasurementPrivate<ROWS, COLS>* m_pPrivate;
};

/** wrapper for pose measurement **/
class UTFACADE_EXPORT BasicPoseMeasurement: public BasicMeasurement {
public:
    BasicPoseMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    /* set pose from vector [x, y, z, rx, ry, rz, rw] */
    BasicPoseMeasurement(unsigned long long int const ts, const std::vector<double>& v);
    BasicPoseMeasurement(unsigned long long int const ts, BasicPoseMeasurementPrivate* _pPrivate);
    ~BasicPoseMeasurement();

    virtual DataType getDataType() const { return POSE; }
    virtual int getDimX() const { return 7; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get pose as vector [x, y, z, rx, ry, rz, rw] */
    bool get(std::vector<double>& v);
    bool get(std::vector<float>& v);

//        private:
    BasicPoseMeasurementPrivate* m_pPrivate;
};

/** wrapper for rotation measurement **/
class UTFACADE_EXPORT BasicRotationMeasurement: public BasicMeasurement {
public:
    BasicRotationMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    /* set pose from vector [x, y, z, rx, ry, rz, rw] */
    BasicRotationMeasurement(unsigned long long int const ts, const std::vector<double>& v);
    BasicRotationMeasurement(unsigned long long int const ts, BasicRotationMeasurementPrivate* _pPrivate);
    ~BasicRotationMeasurement();

    virtual DataType getDataType() const { return QUATERNION; }
    virtual int getDimX() const { return 4; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get pose as vector [rx, ry, rz, rw] */
    bool get(std::vector<double>& v);
    bool get(std::vector<float>& v);

//        private:
    BasicRotationMeasurementPrivate* m_pPrivate;
};

// ErrorVector
/** wrapper for errorvector measurement **/
template<int LEN = 2>
class UTFACADE_EXPORT BasicErrorVectorMeasurement: public BasicMeasurement {
public:
    BasicErrorVectorMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    BasicErrorVectorMeasurement(unsigned long long int const ts, const std::vector<double>& v,
            const std::vector<double>& c);
    BasicErrorVectorMeasurement(unsigned long long int const ts, BasicErrorVectorMeasurementPrivate<LEN>* _pPrivate);
    ~BasicErrorVectorMeasurement();

    virtual DataType getDataType() const { return ERROR_VECTOR; }
    virtual int getDimX() const { return LEN; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get vec2 v */
    bool get(std::vector<double>& v);

    /* get NxN covariance-matrix as vector N*N row-major */
    bool getCovariance(std::vector<double>& v);

//        private:
    BasicErrorVectorMeasurementPrivate<LEN>* m_pPrivate;
};

/** wrapper for errorpose measurement **/
class UTFACADE_EXPORT BasicErrorPoseMeasurement: public BasicMeasurement {
public:
    BasicErrorPoseMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    /* set pose from vector [x, y, z, rx, ry, rz, rw] */
    BasicErrorPoseMeasurement(unsigned long long int const ts, const std::vector<double>& v,
            const std::vector<double>& c);
    BasicErrorPoseMeasurement(unsigned long long int const ts, BasicErrorPoseMeasurementPrivate* _pPrivate);
    ~BasicErrorPoseMeasurement();

    virtual DataType getDataType() const { return ERROR_POSE; }
    virtual int getDimX() const { return 7; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get pose as vector [x, y, z, rx, ry, rz, rw] */
    bool get(std::vector<double>& v);
    bool get(std::vector<float>& v);

    /* get 7x7 covariance-matrix as vector N*N row-major */
    bool getCovariance(std::vector<double>& v);

    //        private:
    BasicErrorPoseMeasurementPrivate* m_pPrivate;
};


/*
 *  List Measurements
 */


/** wrapper for scalar measurement **/
class UTFACADE_EXPORT BasicScalarIntListMeasurement: public BasicMeasurement {
public:
    BasicScalarIntListMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    BasicScalarIntListMeasurement(unsigned long long int const ts, const std::vector< int >& value);
    BasicScalarIntListMeasurement(unsigned long long int const ts, BasicScalarIntListMeasurementPrivate* _pPrivate);
    ~BasicScalarIntListMeasurement();

    virtual DataType getDataType() const { return SCALARI_LIST; }
    virtual int getDimX() const { return 1; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get int v */
    bool get(std::vector< int >& v);
    virtual unsigned int elementCount();

//        private:
    BasicScalarIntListMeasurementPrivate* m_pPrivate;
};

class UTFACADE_EXPORT BasicScalarDoubleListMeasurement: public BasicMeasurement {
public:
    BasicScalarDoubleListMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    BasicScalarDoubleListMeasurement(unsigned long long int const ts, const std::vector< double >& value);
    BasicScalarDoubleListMeasurement(unsigned long long int const ts, BasicScalarDoubleListMeasurementPrivate* _pPrivate);
    ~BasicScalarDoubleListMeasurement();

    virtual DataType getDataType() const { return SCALARD_LIST; }
    virtual int getDimX() const { return 1; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get int v */
    bool get(std::vector<double>& v);
    bool get(std::vector<float>& v);
    virtual unsigned int elementCount();

//        private:
    BasicScalarDoubleListMeasurementPrivate* m_pPrivate;
};

/** wrapper for vector2 measurement **/
template<int LEN = 2>
class UTFACADE_EXPORT BasicVectorListMeasurement: public BasicMeasurement {
public:
    BasicVectorListMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    BasicVectorListMeasurement(unsigned long long int const ts, const std::vector< std::vector<double> >& v);
    BasicVectorListMeasurement(unsigned long long int const ts, BasicVectorListMeasurementPrivate<LEN>* _pPrivate);
    ~BasicVectorListMeasurement();

    virtual DataType getDataType() const { return VECTORD_LIST; }
    virtual int getDimX() const { return LEN; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get vec2 v */
    bool get(std::vector< std::vector<double> >& v);
    bool get(std::vector< std::vector<float> >& v);
    virtual unsigned int elementCount();

//        private:
    BasicVectorListMeasurementPrivate<LEN>* m_pPrivate;
};

/** wrapper for pose measurement **/
class UTFACADE_EXPORT BasicPoseListMeasurement: public BasicMeasurement {
public:
    BasicPoseListMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    /* set pose from vector [x, y, z, rx, ry, rz, rw] */
    BasicPoseListMeasurement(unsigned long long int const ts, const std::vector< std::vector<double> >& v);
    BasicPoseListMeasurement(unsigned long long int const ts, BasicPoseListMeasurementPrivate* _pPrivate);
    ~BasicPoseListMeasurement();

    virtual DataType getDataType() const { return POSE_LIST; }
    virtual int getDimX() const { return 7; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get pose as vector [x, y, z, rx, ry, rz, rw] */
    bool get(std::vector< std::vector<double> >& v);
    bool get(std::vector< std::vector<float> >& v);
    virtual unsigned int elementCount();

//        private:
    BasicPoseListMeasurementPrivate* m_pPrivate;
};

// ErrorVector
/** wrapper for errorvector measurement **/
template<int LEN = 2>
class UTFACADE_EXPORT BasicErrorVectorListMeasurement: public BasicMeasurement {
public:
    BasicErrorVectorListMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    BasicErrorVectorListMeasurement(unsigned long long int const ts, const std::vector< std::vector<double> >& v,
            const std::vector< std::vector<double> >& c);
    BasicErrorVectorListMeasurement(unsigned long long int const ts, BasicErrorVectorListMeasurementPrivate<LEN>* _pPrivate);
    ~BasicErrorVectorListMeasurement();

    virtual DataType getDataType() const { return ERROR_VECTOR_LIST; }
    virtual int getDimX() const { return LEN; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get vec2 v */
    bool get(std::vector< std::vector<double> >& v);

    /* get NxN covariance-matrix as vector N*N row-major */
    bool getCovariance(std::vector< std::vector<double> >& v);
    virtual unsigned int elementCount();

//        private:
    BasicErrorVectorListMeasurementPrivate<LEN>* m_pPrivate;
};

/** wrapper for errorpose measurement **/
class UTFACADE_EXPORT BasicErrorPoseListMeasurement: public BasicMeasurement {
public:
    BasicErrorPoseListMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    /* set pose from vector [x, y, z, rx, ry, rz, rw] */
    BasicErrorPoseListMeasurement(unsigned long long int const ts, const std::vector< std::vector<double> >& v,
            const std::vector< std::vector<double> >& c);
    BasicErrorPoseListMeasurement(unsigned long long int const ts, BasicErrorPoseListMeasurementPrivate* _pPrivate);
    ~BasicErrorPoseListMeasurement();

    virtual DataType getDataType() const { return ERROR_POSE_LIST; }
    virtual int getDimX() const { return 7; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get pose as vector [x, y, z, rx, ry, rz, rw] */
    bool get(std::vector< std::vector<double> >& v);
    bool get(std::vector< std::vector<float> >& v);

    /* get 7x7 covariance-matrix as vector N*N row-major */
    bool getCovariance(std::vector< std::vector<double> >& v);
    virtual unsigned int elementCount();

    //        private:
    BasicErrorPoseListMeasurementPrivate* m_pPrivate;
};


/*
 * Composite Measurements
 */

/** wrapper for cameraintrinsics measurement **/
class UTFACADE_EXPORT BasicCameraIntrinsicsMeasurement: public BasicMeasurement {
public:
    BasicCameraIntrinsicsMeasurement()
            :BasicMeasurement(), m_pPrivate(nullptr) { };
    // set from intrinsics matrix33 (as vector) / distortion / resolution
    BasicCameraIntrinsicsMeasurement(unsigned long long int const ts, const std::vector<double>& intrinsics,
            const std::vector<double>& radial, const std::vector<double>& tangential);
    BasicCameraIntrinsicsMeasurement(unsigned long long int const ts,
            BasicCameraIntrinsicsMeasurementPrivate* _pPrivate);
    ~BasicCameraIntrinsicsMeasurement();

    virtual DataType getDataType() const { return CAMERA_INTRINSICS; }
    virtual int getDimX() const { return 1; }
    virtual int getDimY() const { return 1; }
    virtual int getDimZ() const { return 1; }

    /* get camera intrinsics matrix 3x3 */
    bool get(std::vector<double>& v);
    bool getResolution(std::vector<double>& v);
    bool getDistortion(std::vector<double>& radial, std::vector<double>& tangential);

    /* get OpenGL projection matrix 4x4 */
    bool getOpenGLProjectionMatrix(double l, double r, double b, double t, double n, double f, std::vector<double>& v);


//        private:
    BasicCameraIntrinsicsMeasurementPrivate* m_pPrivate;
};

#ifdef HAVE_OPENCV
/** wrapper for image measurement **/
class UTFACADE_EXPORT BasicImageMeasurement : public BasicMeasurement {
public:

    // must be in sync with utVision::Image::PixelFormat
    enum PixelFormat {
      UNKNOWN_PIXELFORMAT = 0,
      LUMINANCE,
      RGB,
      BGR,
      RGBA,
      BGRA,
      YUV422,
      YUV411,
      RAW,
      DEPTH
    };


    BasicImageMeasurement() : BasicMeasurement(), m_pPrivate(nullptr) {};
    /* set (copy) image from buffer */
    BasicImageMeasurement(unsigned long long int const ts, int width, int height, int depth, int channels, unsigned char* data, PixelFormat pixel_format = RGB, bool copy_data = true);
    BasicImageMeasurement(unsigned long long int const ts, BasicImageMeasurementPrivate* _pPrivate);
    ~BasicImageMeasurement();

    virtual DataType getDataType() const { return IMAGE; }
    virtual int getDimX() const;
    virtual int getDimY() const;
    virtual int getDimZ() const;

    unsigned int getPixelSize() const;
    PixelFormat getPixelFormat() const;
    unsigned int getOrigin() const;
    unsigned int getChannels() const;
    unsigned int getByteCount() const;
    unsigned int getStep() const;

    unsigned char* getDataPtr() const;

    /* get copy into buffer */
    bool get( unsigned int size, unsigned char* data );

    BasicImageMeasurementPrivate* m_pPrivate;
private:
};
#endif

/**
* A Basic data flow observer
*/
class UTFACADE_EXPORT BasicDataflowObserver
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