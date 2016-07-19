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
 * Source component with push output port
 * This files contains a source component with which the application
 * can interface which uses an PushSupplier output port
 *
 * @author Daniel Pustka <daniel.pustka@in.tum.de>
 */

#include "ApplicationPushSource.h"
#include <utDataflow/ComponentFactory.h>

namespace Ubitrack { namespace Components {

using namespace Ubitrack::Dataflow;

UBITRACK_REGISTER_COMPONENT( ComponentFactory* const cf ) {

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
	cf->registerComponent< ApplicationPushSourceErrorPositionList2 > ( "ApplicationPushSourcePositionList2" );
	cf->registerComponent< ApplicationPushSourceVector4D > ( "ApplicationPushSourceVector4" );

	cf->registerComponent< ApplicationPushSourceCameraIntrinsics > ("ApplicationPushSourceCameraIntrinsics");

}

} } // namespace Ubitrack::Components
