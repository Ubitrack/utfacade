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
 * Sink component with pull input port
 * This files containes an sink component with which the application
 * can interface which uses an PullConsumer input port.
 *
 * @author Benjamin Becker <benjamin.becker@eads.net>
 */

#include <utDataflow/ComponentFactory.h>

#ifdef HAVE_OPENCV
#include "ApplicationEndpointsVision.h"
#endif // HAVE_OPENCV
#include "ApplicationPullSink.h"
#include "ApplicationPullSource.h"
#include "ApplicationPushSink.h"
#include "ApplicationPushSource.h"

namespace Ubitrack { namespace Components {

UBITRACK_REGISTER_COMPONENT( ComponentFactory* const cf ) {
#ifdef HAVE_OPENCV
	cf->registerComponent< ApplicationPushSinkVisionImage > ( "ApplicationPushSinkVisionImage" );
	cf->registerComponent< ApplicationPullSinkVisionImage > ( "ApplicationPullSinkVisionImage" );
	cf->registerComponent< ApplicationPushSourceVisionImage > ( "ApplicationPushSourceVisionImage" );
	cf->registerComponent< ApplicationPullSourceVisionImage > ( "ApplicationPullSourceVisionImage" );
#endif // HAVE_OPENCV

	cf->registerComponent< ApplicationPullSinkButton > ("ApplicationPullSinkButton");
	cf->registerComponent< ApplicationPullSinkSkalar > ("ApplicationPullSinkSkalar");
	cf->registerComponent< ApplicationPullSinkDistance > ("ApplicationPullSinkDistance");
	cf->registerComponent< ApplicationPullSinkPosition2D > ("ApplicationPullSinkPosition2D");
	cf->registerComponent< ApplicationPullSinkPosition > ("ApplicationPullSinkPosition");
	cf->registerComponent< ApplicationPullSinkPose > ("ApplicationPullSinkPose");
	cf->registerComponent< ApplicationPullSinkErrorPosition2 > ( "ApplicationPullSinkErrorPosition2" );
	cf->registerComponent< ApplicationPullSinkErrorPosition > ("ApplicationPullSinkErrorPosition");
	cf->registerComponent< ApplicationPullSinkErrorPose > ("ApplicationPullSinkErrorPose");
	cf->registerComponent< ApplicationPullSinkRotation > ("ApplicationPullSinkRotation");
	cf->registerComponent< ApplicationPullSinkMatrix3x3 > ("ApplicationPullSinkMatrix3x3");
	cf->registerComponent< ApplicationPullSinkMatrix3x4 > ("ApplicationPullSinkMatrix3x4");
	cf->registerComponent< ApplicationPullSinkMatrix4x4 > ("ApplicationPullSinkMatrix4x4");
	cf->registerComponent< ApplicationPullSinkVector4D > ("ApplicationPullSinkVector4D");
	cf->registerComponent< ApplicationPullSinkButtonList > ("ApplicationPullSinkButtonList");
	cf->registerComponent< ApplicationPullSinkDistanceList > ("ApplicationPullSinkDistanceList");
	cf->registerComponent< ApplicationPullSinkPositionList2 > ("ApplicationPullSinkPositionList2");
	cf->registerComponent< ApplicationPullSinkPositionList > ("ApplicationPullSinkPositionList");
	cf->registerComponent< ApplicationPullSinkPoseList > ("ApplicationPullSinkPoseList");
	cf->registerComponent< ApplicationPullSinkErrorPositionList2 > ("ApplicationPullSinkErrorPositionList2");
	cf->registerComponent< ApplicationPullSinkErrorPositionList > ("ApplicationPullSinkErrorPositionList");
	cf->registerComponent< ApplicationPullSinkErrorPoseList > ("ApplicationPullSinkErrorPoseList");
	cf->registerComponent< ApplicationPullSinkCameraIntrinsics > ("ApplicationPullSinkCameraIntrinsics");


	cf->registerComponent< ApplicationPullSourceButton > ("ApplicationPullSourceButton");
	cf->registerComponent< ApplicationPullSourceSkalar > ("ApplicationPullSourceSkalar");
	cf->registerComponent< ApplicationPullSourceDistance > ("ApplicationPullSourceDistance"); // new
	cf->registerComponent< ApplicationPullSourcePosition2D > ("ApplicationPullSourcePosition2D");
	cf->registerComponent< ApplicationPullSourcePosition > ("ApplicationPullSourcePosition");
	cf->registerComponent< ApplicationPullSourcePose > ("ApplicationPullSourcePose");
	cf->registerComponent< ApplicationPullSourceErrorPosition2 > ("ApplicationPullSourceErrorPosition2");
	cf->registerComponent< ApplicationPullSourceErrorPosition > ("ApplicationPullSourceErrorPosition");
	cf->registerComponent< ApplicationPullSourceErrorPose > ("ApplicationPullSourceErrorPose");
	cf->registerComponent< ApplicationPullSourceRotation > ("ApplicationPullSourceRotation");
	cf->registerComponent< ApplicationPullSourceMatrix3x3 > ("ApplicationPullSourceMatrix3x3");
	cf->registerComponent< ApplicationPullSourceMatrix3x4 > ("ApplicationPullSourceMatrix3x4");
	cf->registerComponent< ApplicationPullSourceMatrix4x4 > ("ApplicationPullSourceMatrix4x4");
	cf->registerComponent< ApplicationPullSourceVector4D > ("ApplicationPullSourceVector4D");
	cf->registerComponent< ApplicationPullSourceButtonList > ("ApplicationPullSourceButtonList"); //new
	cf->registerComponent< ApplicationPullSourceDistanceList > ("ApplicationPullSourceDistanceList"); //new
	cf->registerComponent< ApplicationPullSourcePositionList2 > ("ApplicationPullSourcePositionList2");
	cf->registerComponent< ApplicationPullSourcePositionList > ("ApplicationPullSourcePositionList");
	cf->registerComponent< ApplicationPullSourcePoseList > ("ApplicationPullSourcePoseList"); //new
	cf->registerComponent< ApplicationPullSourceErrorPositionList2 > ("ApplicationPullSourceErrorPositionList2"); //new
	cf->registerComponent< ApplicationPullSourceErrorPositionList > ("ApplicationPullSourceErrorPositionList");
	cf->registerComponent< ApplicationPullSourceErrorPoseList > ("ApplicationPullSourceErrorPoseList"); //new	
	cf->registerComponent< ApplicationPullSourceCameraIntrinsics > ("ApplicationPullSourceCameraIntrinsics");

	cf->registerComponent< ApplicationPushSinkButton > ("ApplicationPushSinkButton");
	cf->registerComponent< ApplicationPushSinkSkalar > ("ApplicationPushSinkSkalar");
	cf->registerComponent< ApplicationPushSinkDistance > ("ApplicationPushSinkDistance"); // new
	cf->registerComponent< ApplicationPushSinkPosition2D > ("ApplicationPushSinkPosition2D");
	cf->registerComponent< ApplicationPushSinkPosition > ("ApplicationPushSinkPosition");
	cf->registerComponent< ApplicationPushSinkPose > ("ApplicationPushSinkPose");
	cf->registerComponent< ApplicationPushSinkErrorPosition2 > ("ApplicationPushSinkErrorPosition2");
	cf->registerComponent< ApplicationPushSinkErrorPosition > ("ApplicationPushSinkErrorPosition");
	cf->registerComponent< ApplicationPushSinkErrorPose > ("ApplicationPushSinkErrorPose");
	cf->registerComponent< ApplicationPushSinkRotation > ("ApplicationPushSinkRotation");
	cf->registerComponent< ApplicationPushSinkMatrix3x3 > ("ApplicationPushSinkMatrix3x3");
	cf->registerComponent< ApplicationPushSinkMatrix3x4 > ("ApplicationPushSinkMatrix3x4");
	cf->registerComponent< ApplicationPushSinkMatrix4x4 > ("ApplicationPushSinkMatrix4x4");
	cf->registerComponent< ApplicationPushSinkVector4D > ("ApplicationPushSinkVector4D");
	cf->registerComponent< ApplicationPushSinkButtonList > ("ApplicationPushSinkButtonList"); //new
	cf->registerComponent< ApplicationPushSinkDistanceList > ("ApplicationPushSinkDistanceList"); //new
	cf->registerComponent< ApplicationPushSinkPositionList2 > ("ApplicationPushSinkPositionList2");
	cf->registerComponent< ApplicationPushSinkPositionList > ("ApplicationPushSinkPositionList");
	cf->registerComponent< ApplicationPushSinkPoseList > ("ApplicationPushSinkPoseList"); //new
	cf->registerComponent< ApplicationPushSinkErrorPositionList2 > ("ApplicationPushSinkErrorPositionList2"); //new
	cf->registerComponent< ApplicationPushSinkErrorPositionList > ("ApplicationPushSinkErrorPositionList");
	cf->registerComponent< ApplicationPushSinkErrorPoseList > ("ApplicationPushSinkErrorPoseList"); //new

	// incompatible with simplefacade
	// cf->registerComponent< ApplicationPushSinkCameraIntrinsics > ("ApplicationPushSinkCameraIntrinsics");

	cf->registerComponent< ApplicationPushSourceButton > ("ApplicationPushSourceButton");
	cf->registerComponent< ApplicationPushSourceSkalar > ("ApplicationPushSourceSkalar");
	cf->registerComponent< ApplicationPushSourceDistance > ("ApplicationPushSourceDistance"); // new
	cf->registerComponent< ApplicationPushSourcePosition2D > ("ApplicationPushSourcePosition2D");
	cf->registerComponent< ApplicationPushSourcePosition > ("ApplicationPushSourcePosition");
	cf->registerComponent< ApplicationPushSourcePose > ("ApplicationPushSourcePose");
	cf->registerComponent< ApplicationPushSourceErrorPosition2 > ("ApplicationPushSourceErrorPosition2");
	cf->registerComponent< ApplicationPushSourceErrorPosition > ("ApplicationPushSourceErrorPosition");
	cf->registerComponent< ApplicationPushSourceErrorPose > ("ApplicationPushSourceErrorPose");
	cf->registerComponent< ApplicationPushSourceRotation > ("ApplicationPushSourceRotation");
	cf->registerComponent< ApplicationPushSourceMatrix3x3 > ("ApplicationPushSourceMatrix3x3");
	cf->registerComponent< ApplicationPushSourceMatrix3x4 > ("ApplicationPushSourceMatrix3x4");
	cf->registerComponent< ApplicationPushSourceMatrix4x4 > ("ApplicationPushSourceMatrix4x4");
	cf->registerComponent< ApplicationPushSourceVector4D > ("ApplicationPushSourceVector4D");
	cf->registerComponent< ApplicationPushSourceButtonList > ("ApplicationPushSourceButtonList"); //new
	cf->registerComponent< ApplicationPushSourceDistanceList > ("ApplicationPushSourceDistanceList"); //new
	cf->registerComponent< ApplicationPushSourcePositionList2 > ("ApplicationPushSourcePositionList2");
	cf->registerComponent< ApplicationPushSourcePositionList > ("ApplicationPushSourcePositionList");
	cf->registerComponent< ApplicationPushSourcePoseList > ("ApplicationPushSourcePoseList"); //new
	cf->registerComponent< ApplicationPushSourceErrorPositionList2 > ("ApplicationPushSourceErrorPositionList2"); //new
	cf->registerComponent< ApplicationPushSourceErrorPositionList > ("ApplicationPushSourceErrorPositionList");
	cf->registerComponent< ApplicationPushSourceErrorPoseList > ("ApplicationPushSourceErrorPoseList"); //new
	// backward compatibility
	//cf->registerComponent< ApplicationPushSourceErrorPositionList2 > ( "ApplicationPushSourcePositionList2" );
	cf->registerComponent< ApplicationPushSourceVector4D > ( "ApplicationPushSourceVector4" );

	// incompatible with simplefacade
	// cf->registerComponent< ApplicationPushSourceCameraIntrinsics > ("ApplicationPushSourceCameraIntrinsics");

}

} } // namespace Ubitrack::Components







