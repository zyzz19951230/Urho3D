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

static PODVector<RayQueryResult> OctreeRaycast(const Octree* self, 
    const Ray& ray,
    RayQueryLevel level = RAY_TRIANGLE,
    float maxDistance = M_INFINITY,
    unsigned char drawableFlags = DRAWABLE_ANY,
    unsigned viewMask = DEFAULT_VIEWMASK)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags, viewMask);
    self->Raycast(query);
    return result;
}

KAGUYA_FUNCTION_OVERLOADS(OctreeRaycastOverloads, OctreeRaycast, 2, 6)

static RayQueryResult OctreeRaycastSingle(const Octree* self, 
    const Ray& ray, 
    RayQueryLevel level = RAY_TRIANGLE,
    float maxDistance = M_INFINITY, 
    unsigned char drawableFlags = DRAWABLE_ANY, 
    unsigned viewMask = DEFAULT_VIEWMASK)
{
    PODVector<RayQueryResult> result;
    RayOctreeQuery query(result, ray, level, maxDistance, drawableFlags, viewMask);
    self->RaycastSingle(query);
    if (result.Size() == 0)
        return RayQueryResult();

    return result[0];
}

KAGUYA_FUNCTION_OVERLOADS(OctreeRaycastSingleOverloads, OctreeRaycastSingle, 2, 6)

void RegisterOctree(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Octree : Component
    lua["Octree"].setClass(UserdataMetatable<Octree, Component>()
        // [Constructor] Octree()
        .addStaticFunction("new", &CreateObject<Octree>)

        .addOverloadedFunctions("DrawDebugGeometry",
            // [Method] void DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
            static_cast<void(Octree::*)(DebugRenderer*, bool)>(&Octree::DrawDebugGeometry),
            // [Method] void DrawDebugGeometry(bool depthTest)
            static_cast<void(Octree::*)(bool)>(&Octree::DrawDebugGeometry))

        // [Method] void SetSize(const BoundingBox& box, unsigned numLevels)
        .addFunction("SetSize", &Octree::SetSize)
        // [Method] void Update(const FrameInfo& frame)
        .addFunction("Update", &Octree::Update)
        // [Method] void AddManualDrawable(Drawable* drawable)
        .addFunction("AddManualDrawable", &Octree::AddManualDrawable)
        // [Method] void RemoveManualDrawable(Drawable* drawable)
        .addFunction("RemoveManualDrawable", &Octree::RemoveManualDrawable)

        // [Method] PODVector<RayQueryResult> Raycast(const Octree* self, const Ray& ray, RayQueryLevel level = RAY_TRIANGLE, float maxDistance = M_INFINITY, unsigned char drawableFlags = DRAWABLE_ANY, unsigned viewMask = DEFAULT_VIEWMASK)
        .addStaticFunction("Raycast", OctreeRaycastOverloads())
        
        // [Method] RayQueryResult RaycastSingle(const Octree* self, const Ray& ray, RayQueryLevel level = RAY_TRIANGLE, float maxDistance = M_INFINITY, unsigned char drawableFlags = DRAWABLE_ANY, unsigned viewMask = DEFAULT_VIEWMASK)
        .addStaticFunction("RaycastSingle", OctreeRaycastSingleOverloads())

        // [Method] unsigned GetNumLevels() const
        .addFunction("GetNumLevels", &Octree::GetNumLevels)
        // [Method] void QueueUpdate(Drawable* drawable)
        .addFunction("QueueUpdate", &Octree::QueueUpdate)
        
        // [Property(ReadOnly)] unsigned numLevels
        .addProperty("numLevels", &Octree::GetNumLevels)
        );
}
}

