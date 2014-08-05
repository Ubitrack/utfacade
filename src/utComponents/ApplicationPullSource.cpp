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
 * @ingroup dataflow_components
 * @file
 * ApplicationPullSource implementation
 *
 * @author Ulrich Eck <ueck@net-labs.de>
 */

#include <utDataflow/ComponentFactory.h>

#include "ApplicationPullSource.h"

namespace Ubitrack { namespace Components {

UBITRACK_REGISTER_COMPONENT( ComponentFactory* const cf ) {
	cf->registerComponent< ApplicationPullSource< int > > ( "ApplicationPullSourceInt" );
	cf->registerComponent< ApplicationPullSourceButton > ( "ApplicationPullSourceButton" );
	cf->registerComponent< ApplicationPullSourcePose > ( "ApplicationPullSourcePose" );
	cf->registerComponent< ApplicationPullSourceErrorPose > ( "ApplicationPullSourceErrorPose" );

	cf->registerComponent< ApplicationPullSourcePosition > ( "ApplicationPullSourcePosition" );
	cf->registerComponent< ApplicationPullSourcePosition2D > ( "ApplicationPullSourcePosition2D" );
	cf->registerComponent< ApplicationPullSourceErrorPosition > ( "ApplicationPullSourceErrorPosition" );
	cf->registerComponent< ApplicationPullSourceErrorPosition2D > ( "ApplicationPullSourceErrorPosition2D" );
	cf->registerComponent< ApplicationPullSourceRotation > ( "ApplicationPullSourceRotation" );
	cf->registerComponent< ApplicationPullSourcePositionList > ( "ApplicationPullSourcePositionList" );
	cf->registerComponent< ApplicationPullSourcePositionList2 > ( "ApplicationPullSourcePosition2DList" );
	cf->registerComponent< ApplicationPullSourceErrorPositionList > ( "ApplicationPullSourceErrorPositionList" );
	cf->registerComponent< ApplicationPullSourceErrorPositionList2 > ( "ApplicationPullSourceErrorPosition2DList" );
	cf->registerComponent< ApplicationPullSource< Measurement::Matrix3x4 > > ( "ApplicationPullSourceMatrix3x4" );
	cf->registerComponent< ApplicationPullSource< Measurement::Matrix3x3 > > ( "ApplicationPullSourceMatrix3x3" );
	cf->registerComponent< ApplicationPullSource< Measurement::Matrix4x4 > > ( "ApplicationPullSourceMatrix4x4" );
	cf->registerComponent< ApplicationPullSource< Measurement::Distance > > ( "ApplicationPullSourceDistance" );
	
}

} } // namespace Ubitrack::Components
