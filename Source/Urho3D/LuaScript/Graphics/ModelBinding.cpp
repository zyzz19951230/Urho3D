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

#include "../../Graphics/Geometry.h"
#include "../../Graphics/Model.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(ModelClone, Model, Clone, 0, 1);

void RegisterModel(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Model : Resource
    lua["Model"].setClass(UserdataMetatable<Model, Resource>()
        // [Constructor] Model()
        .addStaticFunction("new", &CreateObject<Model>)

        // [Method] void SetBoundingBox(const BoundingBox& box)
        .addFunction("SetBoundingBox", &Model::SetBoundingBox)
        
        // [Method] void SetNumGeometries(unsigned num)
        .addFunction("SetNumGeometries", &Model::SetNumGeometries)
        // [Method] bool SetNumGeometryLodLevels(unsigned index, unsigned num)
        .addFunction("SetNumGeometryLodLevels", &Model::SetNumGeometryLodLevels)
        // [Method] bool SetGeometry(unsigned index, unsigned lodLevel, Geometry* geometry)
        .addFunction("SetGeometry", &Model::SetGeometry)
        // [Method] bool SetGeometryCenter(unsigned index, const Vector3& center)
        .addFunction("SetGeometryCenter", &Model::SetGeometryCenter)
        // [Method] void SetSkeleton(const Skeleton& skeleton)
        .addFunction("SetSkeleton", &Model::SetSkeleton)
        
        // [Method] SharedPtr<Model> Clone(const String& cloneName = String::EMPTY) const
        .addFunction("Clone", ModelClone())

        // [Method] const BoundingBox& GetBoundingBox() const
        .addFunction("GetBoundingBox", &Model::GetBoundingBox)
        // [Method] Skeleton& GetSkeleton()
        .addFunction("GetSkeleton", &Model::GetSkeleton)
        // [Method] unsigned GetNumGeometries() const
        .addFunction("GetNumGeometries", &Model::GetNumGeometries)
        // [Method] unsigned GetNumGeometryLodLevels(unsigned index) const
        .addFunction("GetNumGeometryLodLevels", &Model::GetNumGeometryLodLevels)
        // [Method] const Vector<Vector<SharedPtr<Geometry> > >& GetGeometries() const
        .addFunction("GetGeometries", &Model::GetGeometries)
        // [Method] const PODVector<Vector3>& GetGeometryCenters() const
        .addFunction("GetGeometryCenters", &Model::GetGeometryCenters)
        // [Method] Geometry* GetGeometry(unsigned index, unsigned lodLevel) const
        .addFunction("GetGeometry", &Model::GetGeometry)
        // [Method] const Vector3& GetGeometryCenter(unsigned index) const
        .addFunction("GetGeometryCenter", &Model::GetGeometryCenter)
        // [Method] unsigned GetNumMorphs() const
        .addFunction("GetNumMorphs", &Model::GetNumMorphs)

        .addOverloadedFunctions("GetMorph",
            // [Method] const ModelMorph* GetMorph(unsigned index) const
            static_cast<const ModelMorph*(Model::*)(unsigned) const>(&Model::GetMorph),
            // [Method] const ModelMorph* GetMorph(const String& name) const
            static_cast<const ModelMorph*(Model::*)(const String&) const>(&Model::GetMorph),
            // [Method] const ModelMorph* GetMorph(StringHash nameHash) const
            static_cast<const ModelMorph*(Model::*)(StringHash) const>(&Model::GetMorph))

        // [Method] unsigned GetMorphRangeStart(unsigned bufferIndex) const
        .addFunction("GetMorphRangeStart", &Model::GetMorphRangeStart)
        // [Method] unsigned GetMorphRangeCount(unsigned bufferIndex) const
        .addFunction("GetMorphRangeCount", &Model::GetMorphRangeCount)


        // [Property] const BoundingBox& boundingBox
        .addProperty("boundingBox", &Model::GetBoundingBox, &Model::SetBoundingBox)
        // [Property(Readonly)] Skeleton& skeleton
        .addProperty("skeleton", &Model::GetSkeleton)
        // [Property] unsigned numGeometries
        .addProperty("numGeometries", &Model::GetNumGeometries, &Model::SetNumGeometries)
        // [Property(Readonly)] unsigned numMorphs
        .addProperty("numMorphs", &Model::GetNumMorphs)
        );
}
}

