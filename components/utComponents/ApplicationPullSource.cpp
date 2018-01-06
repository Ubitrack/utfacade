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

}

} } // namespace Ubitrack::Components
