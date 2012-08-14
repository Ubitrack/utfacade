%module UbitrackMath

%include "std_vector.i"
%include "std_string.i"

/*
New approach to make an ubitrack wrapper for the algorithmic parts of the library.
The main motivation for me is to get python access to the absolute orientation algorithm.
Thus, there are many things remaining to be done.
*/

%{
#include <sstream>
#include <utMath/Vector.h>
#include <utMath/Matrix.h>
#include <utMath/Quaternion.h>
#include <utMeasurement/Measurement.h>
#include <utUtil/CalibFile.h>
#include <utCalibration/AbsoluteOrientation.h>
#include <utCalibration/HandEyeCalibration.h>

namespace Ubitrack { namespace Math {

// replacements for constructors
Vector< 2 > newVector2( double x, double y )
{ return Vector< 2 >( x, y ); }

Vector< 3 > newVector3( double x, double y, double z )
{ return Vector< 3 >( x, y, z ); }

// replacement for operator~
Pose invert( const Pose& p )
{ return ~p; }

Quaternion invert( const Quaternion& q )
{ return ~q; }

} } // namespace Ubitrack::Math
%}	

namespace Ubitrack { namespace Math {

// Vector wrapper

template< unsigned N, class T = double >
class Vector
{
public:
	Vector();
};

%extend Vector
{
	// add ordinary getter and setter methods
	T get( unsigned i )
	{ return (*$self)( i ); }
	
	void set( unsigned i, T x )
	{ (*$self)( i ) = x; }
	
	// some operations
	Vector operator+( const Vector& b )
	{ return *$self + b; }
	
	Vector operator-( const Vector& b )
	{ return *$self - b; }
	
	Vector operator*( double b )
	{ return *$self * b; }
	
	Vector operator/( double b )
	{ return *$self / b; }
	
	// printing for python
	std::string __str__()
	{
		std::ostringstream ss;
		ss << "Vector" << *$self;
		return ss.str();
	}
}

Vector< 2 > newVector2( double x, double y );
Vector< 3 > newVector3( double x, double y, double z );

%template( Vector2 ) Vector< 2 >;
%template( Vector3 ) Vector< 3 >;

// vector operations
Vector< 3 > cross_prod( const Vector< 3 >& a, const Vector< 3 >& b );


// Matrix wrapper

template< unsigned M, unsigned N, class T = double >
class Matrix
{
public:
	Matrix();
};

%extend Matrix
{
	// add ordinary getter and setter methods
	T get( unsigned r, unsigned c )
	{ return (*$self)( r, c ); }
	
	void set( unsigned r, unsigned c, T x )
	{ (*$self)( r, c ) = x; }
	
	// some operations
	Matrix operator+( const Matrix& b )
	{ return *$self + b; }
	
	Matrix operator-( const Matrix& b )
	{ return *$self - b; }
	
	Matrix operator*( double b )
	{ return *$self * b; }
	
	Matrix operator/( double b )
	{ return *$self / b; }
	
	// printing for python
	std::string __str__()
	{
		std::ostringstream ss;
		ss << "Matrix" << *$self;
		return ss.str();
	}
}

%template( Matrix3x3 ) Matrix< 3, 3 >;
%template( Matrix3x4 ) Matrix< 3, 4 >;
%template( Matrix4x4 ) Matrix< 4, 4 >;


// Quaternion wrapper
class Quaternion
{
public:
	Quaternion( double x, double y, double z, double w );
	
	double x() const;
	double y() const;
	double z() const;
	double w() const;
	
	// transformations
	Vector< 3 > operator*( const Vector< 3 >& x ) const;
};

%extend Quaternion
{
	// In c++, the boost::math::quaternion operator* is used with implicit back-conversion to Math::Quaternion
	// For swig, we need a more explicit version
	Quaternion operator*( const Quaternion& q )
	{ return *$self * q; }
	
	Matrix< 3, 3 > toMatrix()
	{ return Ubitrack::Math::Matrix< 3, 3 >( *$self ); }
	
	// printing for python
	std::string __str__()
	{
		std::ostringstream ss;
		ss << "Quaternion" << *$self;
		return ss.str();
	}
}

Quaternion invert( const Quaternion& q );


// pose wrapper

class Pose
{
public:
	Pose();
	Pose( const Quaternion& r, const Vector< 3 >& t );
	const Quaternion& rotation() const;
	const Vector< 3 >& translation() const;
	
	// transformations
	Vector< 3 > operator*( const Vector< 3 >& x ) const;
	Pose operator*( const Pose& Q ) const;
};

%extend Pose
{
	Matrix< 4, 4 > toMatrix()
	{ return Ubitrack::Math::Matrix< 4, 4 >( *$self ); }
	
	// printing for python
	std::string __str__()
	{
		std::ostringstream ss;
		ss << "Pose" << *$self;
		return ss.str();
	}
}

Pose invert( const Pose& p );

} } // namespace Ubitrack::Math


namespace std {
// define frequently used vector types
%template( Vector3Array ) vector< Ubitrack::Math::Vector< 3 > >;
%template( Vector2Array ) vector< Ubitrack::Math::Vector< 2 > >;
%template( PoseArray ) vector< Ubitrack::Math::Pose >;

}

// some useful boost matrix/vector operations
namespace boost { namespace numeric { namespace ublas {

double inner_prod( const Ubitrack::Math::Vector< 3 >& a, const Ubitrack::Math::Vector< 3 >& b );
double inner_prod( const Ubitrack::Math::Vector< 2 >& a, const Ubitrack::Math::Vector< 2 >& b );
double norm_2( const Ubitrack::Math::Vector< 3 >& a );
double norm_2( const Ubitrack::Math::Vector< 2 >& a );

} } }

// define measurements
namespace Ubitrack { namespace Measurement {

template< class Type >
class Measurement
{
public:
	Measurement();
	explicit Measurement( const Type& m );
	explicit Measurement( unsigned long long ts, const Type& m );
	unsigned long long time() const;
	Type* get();
};

%template( PoseMeasurement ) Measurement< Ubitrack::Math::Pose >;
%template( PositionMeasurement ) Measurement< Ubitrack::Math::Vector< 3 > >;

} }


// reading calibration files
namespace Ubitrack { namespace Util {

void readCalibFile( const std::string& sFile, Ubitrack::Measurement::Measurement< Ubitrack::Math::Pose >& result );
void readCalibFile( const std::string& sFile, Ubitrack::Measurement::Measurement< Ubitrack::Math::Vector< 3 > >& result );

} }

// In the long term, this has to be moved to a separate calibration module

namespace Ubitrack { namespace Calibration {
Math::Pose calculateAbsoluteOrientation ( const std::vector< Math::Vector< 3 > >& left, 
	const std::vector< Math::Vector< 3 > >& right);
	
Math::Pose performHandEyeCalibration( const std::vector< Math::Pose >& hand,  
	const std::vector< Math::Pose >& eye, bool bUseAllPairs = true );
} }

