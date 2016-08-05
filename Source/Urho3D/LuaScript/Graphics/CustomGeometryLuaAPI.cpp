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

    lua["CustomGeometryVertex"].setClass(UserdataMetatable<CustomGeometryVertex>()
    
    .addProperty("position", &CustomGeometryVertex::position_)
    .addProperty("normal", &CustomGeometryVertex::normal_)
    .addProperty("color", &CustomGeometryVertex::color_)
    .addProperty("texCoord", &CustomGeometryVertex::texCoord_)
    .addProperty("tangent", &CustomGeometryVertex::tangent_)
    );

    lua["CustomGeometry"].setClass(UserdataMetatable<CustomGeometry, Drawable>()
        .addStaticFunction("new", &CreateObject<CustomGeometry>)

        .addFunction("Clear", &CustomGeometry::Clear)
        .addFunction("SetNumGeometries", &CustomGeometry::SetNumGeometries)
        .addFunction("SetDynamic", &CustomGeometry::SetDynamic)
        .addFunction("BeginGeometry", &CustomGeometry::BeginGeometry)
        .addFunction("DefineVertex", &CustomGeometry::DefineVertex)
        .addFunction("DefineNormal", &CustomGeometry::DefineNormal)
        .addFunction("DefineColor", &CustomGeometry::DefineColor)
        .addFunction("DefineTexCoord", &CustomGeometry::DefineTexCoord)
        .addFunction("DefineTangent", &CustomGeometry::DefineTangent)
        .addFunction("DefineGeometry", &CustomGeometry::DefineGeometry)
        .addFunction("Commit", &CustomGeometry::Commit)

        .addOverloadedFunctions("SetMaterial",
            static_cast<void(CustomGeometry::*)(Material*)>(&CustomGeometry::SetMaterial),
            static_cast<bool(CustomGeometry::*)(unsigned, Material*)>(&CustomGeometry::SetMaterial))

        .addFunction("GetNumGeometries", &CustomGeometry::GetNumGeometries)
        .addFunction("GetNumVertices", &CustomGeometry::GetNumVertices)
        .addFunction("IsDynamic", &CustomGeometry::IsDynamic)
        
        .addFunction("GetMaterial", CustomGeometryGetMaterial())

        .addFunction("GetVertex", &CustomGeometry::GetVertex)

        .addProperty("numGeometries", &CustomGeometry::GetNumGeometries, &CustomGeometry::SetNumGeometries)
        .addProperty("dynamic", &CustomGeometry::IsDynamic, &CustomGeometry::SetDynamic)
        .addProperty("material", &CustomGeometryMaterialGetter, &CustomGeometryMaterialSetter)
        );
}
}

