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

#include "../Precompiled.h"

#include <kaguya.hpp>

namespace Urho3D
{

extern void RegisterBoundingBox(kaguya::State& lua);
extern void RegisterColor(kaguya::State& lua);
extern void RegisterFrustum(kaguya::State& lua);
extern void RegisterMathDefs(kaguya::State& lua);
extern void RegisterMatrix2(kaguya::State& lua);
extern void RegisterMatrix3(kaguya::State& lua);
extern void RegisterMatrix3x4(kaguya::State& lua);
extern void RegisterMatrix4(kaguya::State& lua);
extern void RegisterPlane(kaguya::State& lua);
extern void RegisterPolyhedron(kaguya::State& lua);
extern void RegisterQuaternion(kaguya::State& lua);
extern void RegisterRandom(kaguya::State& lua);
extern void RegisterRay(kaguya::State& lua);
extern void RegisterRect(kaguya::State& lua);
extern void RegisterSphere(kaguya::State& lua);
extern void RegisterStringHash(kaguya::State& lua);
extern void RegisterVector2(kaguya::State& lua);
extern void RegisterVector3(kaguya::State& lua);
extern void RegisterVector4(kaguya::State& lua);

void RegisterMathLuaAPI(kaguya::State& lua)
{
    RegisterBoundingBox(lua);
    RegisterColor(lua);
    RegisterFrustum(lua);
    RegisterMathDefs(lua);
    RegisterMatrix2(lua);
    RegisterMatrix3(lua);
    RegisterMatrix3x4(lua);
    RegisterMatrix4(lua);
    RegisterPlane(lua);
    RegisterPolyhedron(lua);
    RegisterQuaternion(lua);
    RegisterRandom(lua);
    RegisterRay(lua);
    RegisterRect(lua);
    RegisterSphere(lua);
    RegisterStringHash(lua);
    RegisterVector2(lua);
    RegisterVector3(lua);
    RegisterVector4(lua);
}
}
