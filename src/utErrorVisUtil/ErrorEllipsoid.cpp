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
 * @file
 * Implementation 3x3 covariance visualization
 *
 * @author Daniel Pustka <daniel.pustka@in.tum.de>
 */

#ifdef HAVE_LAPACK
#include "ErrorEllipsoid.h"
#include <math.h>
#include <utMath/Matrix.h>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/bindings/lapack/syev.hpp>
#include <log4cpp/Category.hh>

using namespace Ubitrack;
namespace ublas = boost::numeric::ublas;
namespace lapack = boost::numeric::bindings::lapack;



void calculatePositionEllipsoid3x3( float* covar, float* rotation, float* scale  )
{
	
	Math::Matrix< 3, 3, float > covariance( covar );

	Math::Vector< 3, float > m_sizes;
	Math::Matrix< 4, 4, float > m_rotation;

	ublas::subrange( m_rotation, 0, 3, 0, 3 ) = covariance;
	ublas::matrix_range< Math::Matrix< 4, 4, float > > upperLeft( m_rotation, ublas::range( 0, 3 ), ublas::range( 0, 3 ) );
	lapack::syev( 'V', 'U', upperLeft, m_sizes, lapack::minimal_workspace() );
	for ( unsigned i = 0; i < 3; i++ )
		if ( m_sizes( i ) > 0 )
			m_sizes( i ) = sqrt( m_sizes( i ) );
		else
			m_sizes( i )  = 0;
	Math::Quaternion q(m_rotation);
	//memcpy(rotation, m_rotation.content(), 4*4*sizeof(float));
	rotation[0] = (float)q.x();
	rotation[1] = (float)q.y();
	rotation[2] = (float)q.z();
	rotation[3] = (float)q.w();
	scale[0] = m_sizes[0];
	scale[1] = m_sizes[1];
	scale[2] = m_sizes[2];	
	
}

void calculatePositionEllipsoid6x6( float* covar, float* rotation, float* scale  ){
	Math::Matrix< 6, 6, float > covariance( covar );
	Math::Matrix< 3, 3, float > covariance3x3 = ublas::subrange( covariance, 0, 3, 0, 3 ) ;
	calculatePositionEllipsoid3x3(covariance3x3.content(), rotation, scale);
}


#endif // HAVE_LAPACK
