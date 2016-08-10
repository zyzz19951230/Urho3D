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

    // [Constant] unsigned BONECOLLISION_NONE
    lua["BONECOLLISION_NONE"] = BONECOLLISION_NONE;
    // [Constant] unsigned BONECOLLISION_SPHERE
    lua["BONECOLLISION_SPHERE"] = BONECOLLISION_SPHERE;
    // [Constant] unsigned BONECOLLISION_BOX
    lua["BONECOLLISION_BOX"] = BONECOLLISION_BOX;

    // [Class] Bone
	lua["Bone"].setClass(UserdataMetatable<Bone>()
        // [Constructor] Bone()
		.setConstructors<Bone()>()
        
        // [Field] String name
        .addProperty("name", &Bone::name_)
        // [Field] StringHash nameHash
        .addProperty("nameHash", &Bone::nameHash_)
        // [Field] unsigned parentIndex
        .addProperty("parentIndex", &Bone::parentIndex_)
        // [Field] Vector3 initialPosition
        .addProperty("initialPosition", &Bone::initialPosition_)
        // [Field] Quaternion initialRotation
        .addProperty("initialRotation", &Bone::initialRotation_)
        // [Field] Vector3 initialScale
        .addProperty("initialScale", &Bone::initialScale_)
        // [Field] Matrix3x4 offsetMatrix
        .addProperty("offsetMatrix", &Bone::offsetMatrix_)
        // [Field] bool animated
        .addProperty("animated", &Bone::animated_)
        // [Field] unsigned char collisionMask
        .addProperty("collisionMask", &Bone::collisionMask_)
        // [Field] float radius
        .addProperty("radius", &Bone::radius_)
        // [Field] BoundingBox boundingBox
        .addProperty("boundingBox", &Bone::boundingBox_)
        // [Field] WeakPtr<Node> node
        .addProperty("node", &Bone::node_)
		);

    // [Class] Skeleton
    lua["Skeleton"].setClass(UserdataMetatable<Skeleton>()
        .setConstructors<Skeleton()>()

        // [Method] unsigned GetNumBones() const
        .addFunction("GetNumBones", &Skeleton::GetNumBones)
        // [Method] Bone* GetRootBone()
        .addFunction("GetRootBone", &Skeleton::GetRootBone)

        .addOverloadedFunctions("GetBone",
            // [Method] Bone* GetBone(unsigned index)
            static_cast<Bone*(Skeleton::*)(unsigned)>(&Skeleton::GetBone),
            // [Method] Bone* GetBone(const char* name)
            static_cast<Bone*(Skeleton::*)(const char*)>(&Skeleton::GetBone),
            // [Method] Bone* GetBone(StringHash nameHash)
            static_cast<Bone*(Skeleton::*)(StringHash)>(&Skeleton::GetBone))

        // [Property(Readonly)] unsigned numBones
        .addProperty("numBones", &Skeleton::GetNumBones)
        // [Property(Readonly)] Bone* rootBone
        .addProperty("rootBone", &Skeleton::GetRootBone)
        );
}
}

