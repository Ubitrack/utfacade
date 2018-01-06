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
 * ApplicationPushSink implementation
 *
 * @author Manuel Huber <huberma@in.tum.de>
 */

#include <utDataflow/ComponentFactory.h>

#include "ApplicationPushSink.h"

namespace Ubitrack { namespace Components {

UBITRACK_REGISTER_COMPONENT( ComponentFactory* const cf ) {

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
//	cf->registerComponent< ApplicationPushSinkCameraIntrinsics > ("ApplicationPushSinkCameraIntrinsics");
}

} } // namespace Ubitrack::Components
