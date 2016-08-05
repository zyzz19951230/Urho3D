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

#include "../../Resource/PListFile.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

//void RegisterPListFile(kaguya::State& lua)
//{
//    using namespace kaguya;

//    // enum PListValueType;
//    lua["PLVT_NONE"] = PLVT_NONE;
//    lua["PLVT_INT"] = PLVT_INT;
//    lua["PLVT_BOOL"] = PLVT_BOOL;
//    lua["PLVT_FLOAT"] = PLVT_FLOAT;
//    lua["PLVT_STRING"] = PLVT_STRING;
//    lua["PLVT_VALUEMAP"] = PLVT_VALUEMAP;
//    lua["PLVT_VALUEVECTOR"] = PLVT_VALUEVECTOR;

//    lua["PListValue"].setClass(UserdataMetatable<PListValue>()
//        .setConstructors<PListValue(),
//        PListValue(int),
//        PListValue(bool),
//        PListValue(float),
//        PListValue(const String&),
//        PListValue(PListValueMap&),
//        PListValue(PListValueVector&),
//        PListValue(const PListValue&)>()

//        .addFunction("SetInt", &PListValue::SetInt)
//        .addFunction("SetBool", &PListValue::SetBool)
//        .addFunction("SetFloat", &PListValue::SetFloat)
//        .addFunction("SetString", &PListValue::SetString)
//        .addFunction("SetValueMap", &PListValue::SetValueMap)
//        .addFunction("SetValueVector", &PListValue::SetValueVector)

//        .addFunction("GetType", &PListValue::GetType)

//        .addFunction("GetInt", &PListValue::GetInt)
//        .addFunction("GetBool", &PListValue::GetBool)
//        .addFunction("GetFloat", &PListValue::GetFloat)
//        .addFunction("GetString", &PListValue::GetString)
//        .addFunction("GetIntRect", &PListValue::GetIntRect)
//        .addFunction("GetIntVector2", &PListValue::GetIntVector2)
//        .addFunction("GetValueMap", &PListValue::GetValueMap)
//        .addFunction("GetValueVector", &PListValue::GetValueVector)

//        .addProperty("type", &PListValue::GetType)
//    );

//    lua["PListFile"].setClass(UserdataMetatable<PListFile, Resource>()
//        .addStaticFunction("new", &CreateObject<PListFile>)

//        .addFunction("GetRoot", &PListFile::GetRoot)
//        .addProperty("root", &PListFile::GetRoot)
//    );
//}


}

