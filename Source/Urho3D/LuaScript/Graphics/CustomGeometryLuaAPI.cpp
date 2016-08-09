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

#include "../../Graphics/CustomGeometry.h"
#include "../../Graphics/Material.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(CustomGeometryGetMaterial, CustomGeometry, GetMaterial, 0, 1);

static void CustomGeometryMaterialSetter(CustomGeometry* self, Material* material)
{
    self->SetMaterial(material);
}

static Material* CustomGeometryMaterialGetter(const CustomGeometry* self)
{
    return self->GetMaterial();
}

void RegisterCustomGeometry(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] CustomGeometryVertex
    lua["CustomGeometryVertex"].setClass(UserdataMetatable<CustomGeometryVertex>()

        // [Field] Vector3 position
        .addProperty("position", &CustomGeometryVertex::position_)
        // [Field] Vector3 normal
        .addProperty("normal", &CustomGeometryVertex::normal_)
        // [Field] Color color
        .addProperty("color", &CustomGeometryVertex::color_)
        // [Field] Vector2 texCoord
        .addProperty("texCoord", &CustomGeometryVertex::texCoord_)
        // [Field] Vector4 tangent
        .addProperty("tangent", &CustomGeometryVertex::tangent_)
        );

    // [Class] CustomGeometry : Drawable
    lua["CustomGeometry"].setClass(UserdataMetatable<CustomGeometry, Drawable>()
        // [Constructor] CustomGeometry()
        .addStaticFunction("new", &CreateObject<CustomGeometry>)

        // [Method] void Clear()
        .addFunction("Clear", &CustomGeometry::Clear)
        // [Method] void SetNumGeometries(unsigned num)
        .addFunction("SetNumGeometries", &CustomGeometry::SetNumGeometries)
        // [Method] void SetDynamic(bool enable)
        .addFunction("SetDynamic", &CustomGeometry::SetDynamic)
        // [Method] void BeginGeometry(unsigned index, PrimitiveType type)
        .addFunction("BeginGeometry", &CustomGeometry::BeginGeometry)
        // [Method] void DefineVertex(const Vector3& position)
        .addFunction("DefineVertex", &CustomGeometry::DefineVertex)
        // [Method] void DefineNormal(const Vector3& normal)
        .addFunction("DefineNormal", &CustomGeometry::DefineNormal)
        // [Method] void DefineColor(const Color& color)
        .addFunction("DefineColor", &CustomGeometry::DefineColor)
        // [Method] void DefineTexCoord(const Vector2& texCoord)
        .addFunction("DefineTexCoord", &CustomGeometry::DefineTexCoord)
        // [Method] void DefineTangent(const Vector4& tangent)
        .addFunction("DefineTangent", &CustomGeometry::DefineTangent)
        .addFunction("DefineGeometry", &CustomGeometry::DefineGeometry)
        // [Method] void Commit()
        .addFunction("Commit", &CustomGeometry::Commit)

        .addOverloadedFunctions("SetMaterial",
            // [Method] void SetMaterial(Material* material)
            static_cast<void(CustomGeometry::*)(Material*)>(&CustomGeometry::SetMaterial),
            // [Method] bool SetMaterial(unsigned index, Material* material)
            static_cast<bool(CustomGeometry::*)(unsigned, Material*)>(&CustomGeometry::SetMaterial))

        // [Method] unsigned GetNumGeometries() const
        .addFunction("GetNumGeometries", &CustomGeometry::GetNumGeometries)
        // [Method] unsigned GetNumVertices(unsigned index) const
        .addFunction("GetNumVertices", &CustomGeometry::GetNumVertices)
        // [Method] bool IsDynamic() const
        .addFunction("IsDynamic", &CustomGeometry::IsDynamic)

        // [Method] Material* GetMaterial(unsigned index = 0) const
        .addFunction("GetMaterial", CustomGeometryGetMaterial())

        // [Method] CustomGeometryVertex* GetVertex(unsigned geometryIndex, unsigned vertexNum)
        .addFunction("GetVertex", &CustomGeometry::GetVertex)

        // [Property] unsigned numGeometries
        .addProperty("numGeometries", &CustomGeometry::GetNumGeometries, &CustomGeometry::SetNumGeometries)
        // [Property] bool dynamic
        .addProperty("dynamic", &CustomGeometry::IsDynamic, &CustomGeometry::SetDynamic)
        // [Property] Material* material
        .addProperty("material", &CustomGeometryMaterialGetter, &CustomGeometryMaterialSetter)
        );
}
}

