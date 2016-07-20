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
#include "utMath/CameraIntrinsics.h"
#include <utVision/Image.h>

namespace Ubitrack {
namespace Facade {
/**
* taken from: http://www.sitmo.com/article/a-simple-and-extremely-fast-c-template-for-matrices-and-tensors/
*/
template<int d1, int d2 = 1, int d3 = 1>
class TensorIndex {
public:
    enum { SIZE = d1*d2*d3 };
    enum { LEN1 = d1 };
    enum { LEN2 = d2 };
    enum { LEN3 = d3 };

    static int indexOf(const int i)
    {
        return i;
    }
    static int indexOf(const int i, const int j)
    {
        return j*d1+i;
    }
    static int indexOf(const int i, const int j, const int k)
    {
        return (k*d2+j)*d1+i;
    }
};

// implementation of private measurement types
template<typename BMT>
struct BasicMeasurementTypeTrait {
  static const bool supported = false;
};


/*
 * Single Measurements
 */

// ScalarInt
struct BasicScalarIntMeasurementPrivate {

  BasicScalarIntMeasurementPrivate(unsigned long long int const ts, const int v)
          :m_measurement(Measurement::Button(ts, Math::Scalar<int>(v))) { }

  BasicScalarIntMeasurementPrivate(const Measurement::Button& m)
          :m_measurement(m) { }

  void clear()
  {
      m_measurement.reset();
  }

  Measurement::Button m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicScalarIntMeasurement> {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicScalarIntMeasurementPrivate private_measurement_type;
  typedef Measurement::Button ubitrack_measurement_type;
};

// ScalarDouble
struct BasicScalarDoubleMeasurementPrivate {

  BasicScalarDoubleMeasurementPrivate(unsigned long long int const ts, const double v)
          :m_measurement(Measurement::Distance(ts, Math::Scalar<double>(v))) { }

  BasicScalarDoubleMeasurementPrivate(const Measurement::Distance& m)
          :m_measurement(m) { }

  void clear()
  {
      m_measurement.reset();
  }

  Measurement::Distance m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicScalarDoubleMeasurement> {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicScalarDoubleMeasurementPrivate private_measurement_type;
  typedef Measurement::Distance ubitrack_measurement_type;
};

// Vectors
template<int LEN>
struct BasicVectorMeasurementPrivate {
  typedef Math::Vector<double, LEN> ValueType;
  typedef Measurement::Measurement<ValueType> MeasurementType;
  BasicVectorMeasurementPrivate(unsigned long long int const ts, const std::vector<double>& v)
          :m_measurement(MeasurementType(ts, ValueType(&v.front()))) { }

  BasicVectorMeasurementPrivate(const MeasurementType& m)
          :m_measurement(m) { }

  void clear()
  {
      m_measurement.reset();
  }

  MeasurementType m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicVectorMeasurement<2> > {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicVectorMeasurementPrivate<2> private_measurement_type;
  typedef Measurement::Position2D ubitrack_measurement_type;
};

template<>
struct BasicMeasurementTypeTrait<BasicVectorMeasurement<3> > {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicVectorMeasurementPrivate<3> private_measurement_type;
  typedef Measurement::Position ubitrack_measurement_type;
};

template<>
struct BasicMeasurementTypeTrait<BasicVectorMeasurement<4> > {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicVectorMeasurementPrivate<4> private_measurement_type;
  typedef Measurement::Vector4D ubitrack_measurement_type;
};

template<>
struct BasicMeasurementTypeTrait<BasicVectorMeasurement<8> > {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicVectorMeasurementPrivate<8> private_measurement_type;
  typedef Measurement::Vector8D ubitrack_measurement_type;
};

/**
* M*N elements (row-major)
*/
template<int ROWS, int COLS>
struct BasicMatrixMeasurementPrivate {
  typedef Math::Matrix<double, ROWS, COLS> ValueType;
  typedef Measurement::Measurement<ValueType> MeasurementType;
  BasicMatrixMeasurementPrivate(unsigned long long int const ts, const std::vector<double>& v)
          :m_measurement(MeasurementType(ts, ValueType(&v.front()))) { }

  BasicMatrixMeasurementPrivate(const MeasurementType& m)
          :m_measurement(m) { }

  void clear()
  {
      m_measurement.reset();
  }

  MeasurementType m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicMatrixMeasurement<3, 3> > {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicMatrixMeasurementPrivate<3, 3> private_measurement_type;
  typedef Measurement::Matrix3x3 ubitrack_measurement_type;
};

template<>
struct BasicMeasurementTypeTrait<BasicMatrixMeasurement<3, 4> > {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicMatrixMeasurementPrivate<3, 4> private_measurement_type;
  typedef Measurement::Matrix3x4 ubitrack_measurement_type;
};

template<>
struct BasicMeasurementTypeTrait<BasicMatrixMeasurement<4, 4> > {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicMatrixMeasurementPrivate<4, 4> private_measurement_type;
  typedef Measurement::Matrix4x4 ubitrack_measurement_type;
};

/**
* Pose measurement as vector [x, y, z, rx, ry, rz, rw]
*/
struct BasicPoseMeasurementPrivate {

  BasicPoseMeasurementPrivate(unsigned long long int const ts, const std::vector<double>& v)
          :m_measurement(Measurement::Pose(ts,
          Math::Pose(
                  Math::Quaternion(v[3], v[4], v[5], v[6]),
                  Math::Vector<double, 3>(v[0], v[1], v[2])
          ))) { }

  BasicPoseMeasurementPrivate(const Measurement::Pose& m)
  {
      m_measurement = m;
  }

  void clear()
  {
      m_measurement.reset();
  }

  Measurement::Pose m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicPoseMeasurement> {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicPoseMeasurementPrivate private_measurement_type;
  typedef Measurement::Pose ubitrack_measurement_type;
};

/**
* Rotation measurement as vector [rx, ry, rz, rw]
*/
struct BasicRotationMeasurementPrivate {

  BasicRotationMeasurementPrivate(unsigned long long int const ts, const std::vector<double>& v)
          :m_measurement(Measurement::Rotation(ts, Math::Quaternion(v[0], v[1], v[2], v[3]))) { }

  BasicRotationMeasurementPrivate(const Measurement::Rotation& m)
  {
      m_measurement = m;
  }

  void clear()
  {
      m_measurement.reset();
  }

  Measurement::Rotation m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicRotationMeasurement> {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicRotationMeasurementPrivate private_measurement_type;
  typedef Measurement::Rotation ubitrack_measurement_type;
};

// ErrorVectors
template<int LEN>
struct BasicErrorVectorMeasurementPrivate {
  typedef Math::ErrorVector<double, LEN> ValueType;
  typedef Measurement::Measurement<ValueType> MeasurementType;
  BasicErrorVectorMeasurementPrivate(unsigned long long int const ts,
          const std::vector<double>& v, const std::vector<double>& c)
  {
      Math::Vector<double, LEN> vec(&v.front());
      Math::Matrix<double, LEN, LEN> mat(&c.front());
      m_measurement = MeasurementType(ts, ValueType(vec, mat));
  }

  BasicErrorVectorMeasurementPrivate(const MeasurementType& m)
          :m_measurement(m) { }

  void clear()
  {
      m_measurement.reset();
  }

  MeasurementType m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicErrorVectorMeasurement<2> > {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicErrorVectorMeasurementPrivate<2> private_measurement_type;
  typedef Measurement::ErrorPosition2 ubitrack_measurement_type;
};

template<>
struct BasicMeasurementTypeTrait<BasicErrorVectorMeasurement<3> > {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicErrorVectorMeasurementPrivate<3> private_measurement_type;
  typedef Measurement::ErrorPosition ubitrack_measurement_type;
};

// ErrorPose
/**
* ErrorPose measurement as vector [x, y, z, rx, ry, rz, rw]
*/
struct BasicErrorPoseMeasurementPrivate {

  BasicErrorPoseMeasurementPrivate(unsigned long long int const ts, const std::vector<double>& v,
          const std::vector<double>& cov)
  {
      Math::Matrix<double, 7, 7> co_mat(&cov.front());
      m_measurement = Measurement::ErrorPose(ts,
              Math::ErrorPose(
                      Math::Quaternion(v[3], v[4], v[5], v[6]),
                      Math::Vector<double, 3>(v[0], v[1], v[2]),
                      co_mat
              ));
  }

  BasicErrorPoseMeasurementPrivate(const Measurement::ErrorPose& m)
  {
      m_measurement = m;
  }

  void clear()
  {
      m_measurement.reset();
  }

  Measurement::ErrorPose m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicErrorPoseMeasurement> {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicErrorPoseMeasurementPrivate private_measurement_type;
  typedef Measurement::ErrorPose ubitrack_measurement_type;
};

/*
 * List Measurements
 */

// ScalarInt
struct BasicScalarIntListMeasurementPrivate {

  BasicScalarIntListMeasurementPrivate(unsigned long long int const ts, const std::vector<int>& v) {
      std::vector< Math::Scalar<int> > val(v.size());
      for (unsigned int i = 0; i < val.size(); ++i) {
          val.at(i) = v.at(i);
      }
      m_measurement = Measurement::ButtonList(ts, val);
  }

  BasicScalarIntListMeasurementPrivate(const Measurement::ButtonList& m)
          :m_measurement(m) { }

  void clear()
  {
      m_measurement.reset();
  }

  size_t elementCount() {
      if (m_measurement) {
          return m_measurement->size();
      }
      return 0;
  }

  Measurement::ButtonList m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicScalarIntListMeasurement> {
  static const bool supported = true;
  static const bool is_list = true;
  typedef BasicScalarIntListMeasurementPrivate private_measurement_type;
  typedef Measurement::ButtonList ubitrack_measurement_type;
};

// ScalarDouble
struct BasicScalarDoubleListMeasurementPrivate {

  BasicScalarDoubleListMeasurementPrivate(unsigned long long int const ts, const std::vector<double>& v) {
      std::vector< Math::Scalar<double> > val(v.size());
      for (unsigned int i = 0; i < val.size(); ++i) {
          val.at(i) = v.at(i);
      }
      m_measurement = Measurement::DistanceList(ts, val);
  }

  BasicScalarDoubleListMeasurementPrivate(const Measurement::DistanceList& m)
          :m_measurement(m) { }

  void clear()
  {
      m_measurement.reset();
  }

  size_t elementCount() {
      if (m_measurement) {
          return m_measurement->size();
      }
      return 0;
  }

  Measurement::DistanceList m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicScalarDoubleListMeasurement> {
  static const bool supported = true;
  static const bool is_list = true;
  typedef BasicScalarDoubleListMeasurementPrivate private_measurement_type;
  typedef Measurement::DistanceList ubitrack_measurement_type;
};

// Vectors
template<int LEN>
struct BasicVectorListMeasurementPrivate {
  typedef Math::Vector<double, LEN> ValueType;
  typedef Measurement::Measurement< std::vector< ValueType > > MeasurementType;
  BasicVectorListMeasurementPrivate(unsigned long long int const ts, const std::vector< std::vector<double> >& v)  {
      std::vector< ValueType > val(v.size());
      for (unsigned int i = 0; i < val.size(); ++i) {
          val.at(i) = ValueType(&(v.at(i).front()));
      }
      m_measurement = MeasurementType(ts, val);
  }

  BasicVectorListMeasurementPrivate(const MeasurementType& m)
          :m_measurement(m) { }

  void clear()
  {
      m_measurement.reset();
  }

  size_t elementCount() {
      if (m_measurement) {
          return m_measurement->size();
      }
      return 0;
  }

  MeasurementType m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicVectorListMeasurement<2> > {
  static const bool supported = true;
  static const bool is_list = true;
  typedef BasicVectorMeasurementPrivate<2> private_measurement_type;
  typedef Measurement::PositionList2 ubitrack_measurement_type;
};

template<>
struct BasicMeasurementTypeTrait<BasicVectorListMeasurement<3> > {
  static const bool supported = true;
  static const bool is_list = true;
  typedef BasicVectorMeasurementPrivate<3> private_measurement_type;
  typedef Measurement::PositionList ubitrack_measurement_type;
};

/**
* Pose measurement as vector [x, y, z, rx, ry, rz, rw]
*/
struct BasicPoseListMeasurementPrivate {

  BasicPoseListMeasurementPrivate(unsigned long long int const ts, const std::vector< std::vector<double> >& v) {
      std::vector< Math::Pose > val(v.size());
      for (unsigned int i = 0; i < val.size(); ++i) {
          val.at(i) = Math::Pose(
                  Math::Quaternion(v.at(i)[3], v.at(i)[4], v.at(i)[5], v.at(i)[6]),
                  Math::Vector<double, 3>(v.at(i)[0], v.at(i)[1], v.at(i)[2])
          );
      }
      m_measurement = Measurement::PoseList(ts, val);
  }

  BasicPoseListMeasurementPrivate(const Measurement::PoseList& m)
  {
      m_measurement = m;
  }

  void clear()
  {
      m_measurement.reset();
  }

  size_t elementCount() {
      if (m_measurement) {
          return m_measurement->size();
      }
      return 0;
  }

  Measurement::PoseList m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicPoseListMeasurement> {
  static const bool supported = true;
  static const bool is_list = true;
  typedef BasicPoseListMeasurementPrivate private_measurement_type;
  typedef Measurement::PoseList ubitrack_measurement_type;
};

// ErrorVectors
template<int LEN>
struct BasicErrorVectorListMeasurementPrivate {
  typedef Math::ErrorVector<double, LEN> ValueType;
  typedef Measurement::Measurement< std::vector< ValueType > > MeasurementType;
  BasicErrorVectorListMeasurementPrivate(unsigned long long int const ts,
          const std::vector< std::vector<double> >& v, const std::vector< std::vector<double> >& c)
  {
      std::vector< ValueType > val(v.size());
      for (unsigned int i = 0; i < val.size(); ++i) {
          Math::Vector<double, LEN> vec(&(v.at(i).front()));
          Math::Matrix<double, LEN, LEN> mat(&(c.at(i).front()));
          val.at(i) = ValueType(vec, mat);
      }
      m_measurement = MeasurementType(ts, val);
  }

  BasicErrorVectorListMeasurementPrivate(const MeasurementType& m)
          :m_measurement(m) { }

  void clear()
  {
      m_measurement.reset();
  }

  size_t elementCount() {
      if (m_measurement) {
          return m_measurement->size();
      }
      return 0;
  }

  MeasurementType m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicErrorVectorListMeasurement<2> > {
  static const bool supported = true;
  static const bool is_list = true;
  typedef BasicErrorVectorListMeasurementPrivate<2> private_measurement_type;
  typedef Measurement::ErrorPositionList2 ubitrack_measurement_type;
};

template<>
struct BasicMeasurementTypeTrait<BasicErrorVectorListMeasurement<3> > {
  static const bool supported = true;
  static const bool is_list = true;
  typedef BasicErrorVectorListMeasurementPrivate<3> private_measurement_type;
  typedef Measurement::ErrorPositionList ubitrack_measurement_type;
};

// ErrorPose
/**
* ErrorPose measurement as vector [x, y, z, rx, ry, rz, rw]
*/
struct BasicErrorPoseListMeasurementPrivate {

  BasicErrorPoseListMeasurementPrivate(unsigned long long int const ts, const std::vector< std::vector<double> >& v,
          const std::vector< std::vector<double> >& cov)
  {
      std::vector< Math::ErrorPose > val(v.size());
      for (unsigned int i = 0; i < val.size(); ++i) {
          Math::Matrix<double, 7, 7> co_mat(&(cov.at(i).front()));

          val.at(i) = Math::ErrorPose(
                  Math::Quaternion(v.at(i)[3], v.at(i)[4], v.at(i)[5], v.at(i)[6]),
                  Math::Vector<double, 3>(v.at(i)[0], v.at(i)[1], v.at(i)[2]),
                  co_mat
          );
      }
      m_measurement = Measurement::ErrorPoseList(ts, val);
  }

  BasicErrorPoseListMeasurementPrivate(const Measurement::ErrorPoseList& m)
  {
      m_measurement = m;
  }

  void clear()
  {
      m_measurement.reset();
  }

  size_t elementCount() {
      if (m_measurement) {
          return m_measurement->size();
      }
      return 0;
  }

  Measurement::ErrorPoseList m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicErrorPoseListMeasurement> {
  static const bool supported = true;
  static const bool is_list = true;
  typedef BasicErrorPoseListMeasurementPrivate private_measurement_type;
  typedef Measurement::ErrorPoseList ubitrack_measurement_type;
};





/*
 * Composite Measurements
 */

// CameraIntrinsics
struct BasicCameraIntrinsicsMeasurementPrivate {
  typedef Math::CameraIntrinsics<double> ValueType;
  typedef Measurement::Measurement<ValueType> MeasurementType;
  BasicCameraIntrinsicsMeasurementPrivate(unsigned long long int const ts,
          const std::vector<double>& intrinsics, const std::vector<double>& radial,
          const std::vector<double>& tangential)
  {
      Math::Matrix<double, 3, 3> _intrinsics(&intrinsics.front());
      Math::Vector<double, 6> _radial(&radial.front());
      Math::Vector<double, 2> _tangential(&tangential.front());
      m_measurement = MeasurementType(ts, ValueType(_intrinsics, _radial, _tangential));
  }

  BasicCameraIntrinsicsMeasurementPrivate(const MeasurementType& m)
          :m_measurement(m) { }

  void clear()
  {
      m_measurement.reset();
  }

  MeasurementType m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicCameraIntrinsicsMeasurement> {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicCameraIntrinsicsMeasurementPrivate private_measurement_type;
  typedef Measurement::CameraIntrinsics ubitrack_measurement_type;
};

/**
* image measurement buffer
*/
struct BasicImageMeasurementPrivate {

  BasicImageMeasurementPrivate(unsigned long long int const ts,
          int width, int height, int depth, int channels, unsigned char* data,
          Vision::Image::PixelFormat pixel_format = Vision::Image::RGB,
          bool copy_data = true)
  {

      unsigned int pixel_size = sizeof(unsigned char);
      switch (depth) {
      case CV_16U:
          pixel_size = sizeof(unsigned short);
          break;
      case CV_32F:
          pixel_size = sizeof(float);
          break;
      default:
          // assume CV8U is the default
          break;
      }
      unsigned int frame_bytes = width*height*channels*pixel_size;

      boost::shared_ptr<Vision::Image> pImage;
      if (copy_data) {
          pImage.reset(new Vision::Image(width, height, channels, depth));

          // what about images other than CV8U
          // copy data
          unsigned char* srcData = (unsigned char*) data;
          unsigned char* dstData = (unsigned char*) pImage->Mat().data;
          memcpy(dstData, srcData, sizeof(unsigned char)*frame_bytes);

      }
      else {
          pImage.reset(new Vision::Image(width, height, channels, (void*) (data), depth));
      }

      pImage->set_pixelFormat(pixel_format);
      m_measurement = Measurement::ImageMeasurement(pImage);
  }

  BasicImageMeasurementPrivate(const Measurement::ImageMeasurement& m)
  {
      m_measurement = m;
  }

  void clear()
  {
      m_measurement.reset();
  }

  Measurement::ImageMeasurement m_measurement;

};

template<>
struct BasicMeasurementTypeTrait<BasicImageMeasurement> {
  static const bool supported = true;
  static const bool is_list = false;
  typedef BasicImageMeasurementPrivate private_measurement_type;
  typedef Measurement::ImageMeasurement ubitrack_measurement_type;
};
}
} // namespace Ubitrack::Facade

#endif
