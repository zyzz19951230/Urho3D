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

#include "../../Graphics/DebugRenderer.h"
#include "../../Graphics/Octree.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static PODVector<RayQueryResult> OctreeRaycast(const Octree* self, const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags, unsigned viewMask = DEFAULT_VIEWMASK)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags, viewMask);
    self->Raycast(query);
    return result;
}

static RayQueryResult OctreeRaycastSingle0(const Octree* self, const Ray& ray)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray);
    self->RaycastSingle(query);
    if (result.Size() == 0)
        return RayQueryResult();

    return result[0];
}

static RayQueryResult OctreeRaycastSingle1(const Octree* self, const Ray& ray, RayQueryLevel level)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level);
    self->RaycastSingle(query);
    if (result.Size() == 0)
        return RayQueryResult();

    return result[0];
}

static RayQueryResult OctreeRaycastSingle2(const Octree* self, const Ray& ray, RayQueryLevel level, float maxDistance)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance);
    self->RaycastSingle(query);
    if (result.Size() == 0)
        return RayQueryResult();

    return result[0];
}

static RayQueryResult OctreeRaycastSingle3(const Octree* self, const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags);
    self->RaycastSingle(query);
    if (result.Size() == 0)
        return RayQueryResult();
    return result[0];
}

static RayQueryResult OctreeRaycastSingle4(const Octree* self, const Ray& ray, RayQueryLevel level, float maxDistance, unsigned char drawableFlags, unsigned viewMask)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags, viewMask);
    self->RaycastSingle(query);
    if (result.Size() == 0)
        return RayQueryResult();

    return result[0];
}

void RegisterOctree(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Octree"].setClass(UserdataMetatable<Octree, Component>()
        .addStaticFunction("new", &CreateObject<Octree>)

        .addOverloadedFunctions("DrawDebugGeometry",
            static_cast<void(Octree::*)(DebugRenderer*, bool)>(&Octree::DrawDebugGeometry),
            static_cast<void(Octree::*)(bool)>(&Octree::DrawDebugGeometry))

        .addFunction("SetSize", &Octree::SetSize)
        .addFunction("Update", &Octree::Update)
        .addFunction("AddManualDrawable", &Octree::AddManualDrawable)
        .addFunction("RemoveManualDrawable", &Octree::RemoveManualDrawable)

        // .addStaticFunction("GetDrawables", &Octree::GetDrawables)

        .addStaticFunction("Raycast", &OctreeRaycast)
        
        ADD_OVERLOADED_FUNCTIONS_5(Octree, RaycastSingle)

        .addFunction("GetNumLevels", &Octree::GetNumLevels)
        .addFunction("QueueUpdate", &Octree::QueueUpdate)
        
        .addProperty("numLevels", &Octree::GetNumLevels)
        );
}
}

