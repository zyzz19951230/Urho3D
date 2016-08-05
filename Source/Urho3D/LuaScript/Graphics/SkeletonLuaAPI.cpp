//
// Copyright (c) 2008-2016 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../../Precompiled.h"

#include "../../Graphics/Skeleton.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterSkeleton(kaguya::State& lua)
{
    using namespace kaguya;

    lua["BONECOLLISION_NONE"] = BONECOLLISION_NONE;
    lua["BONECOLLISION_SPHERE"] = BONECOLLISION_SPHERE;
    lua["BONECOLLISION_BOX"] = BONECOLLISION_BOX;

	lua["Bone"].setClass(UserdataMetatable<Bone>()
		.setConstructors<Bone()>()

		.addProperty("name", &Bone::name_)
    	.addProperty("nameHash", &Bone::nameHash_)
    	.addProperty("parentIndex", &Bone::parentIndex_)
    	.addProperty("initialPosition", &Bone::initialPosition_)
    	.addProperty("initialRotation", &Bone::initialRotation_)
    	.addProperty("initialScale", &Bone::initialScale_)
    	.addProperty("offsetMatrix", &Bone::offsetMatrix_)
    	.addProperty("animated", &Bone::animated_)
    	.addProperty("collisionMask", &Bone::collisionMask_)
    	.addProperty("radius", &Bone::radius_)
    	.addProperty("boundingBox", &Bone::boundingBox_)
    	.addProperty("node", &Bone::node_)
		);

    lua["Skeleton"].setClass(UserdataMetatable<Skeleton>()
        .setConstructors<Skeleton()>()

        .addFunction("GetNumBones", &Skeleton::GetNumBones)
        .addFunction("GetRootBone", &Skeleton::GetRootBone)

        .addOverloadedFunctions("GetBone",
            static_cast<Bone*(Skeleton::*)(unsigned)>(&Skeleton::GetBone),
            static_cast<Bone*(Skeleton::*)(const char*)>(&Skeleton::GetBone),
            static_cast<Bone*(Skeleton::*)(StringHash)>(&Skeleton::GetBone))

        .addProperty("numBones", &Skeleton::GetNumBones)
        .addProperty("rootBone", &Skeleton::GetRootBone)
        );
}
}

