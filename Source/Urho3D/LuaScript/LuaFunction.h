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

#pragma once

#include "../Container/RefCounted.h"
#include "../Core/Variant.h"
#include "../Math/StringHash.h"

struct lua_State;
typedef int (*lua_CFunction) (lua_State *L);

namespace Urho3D
{

class Deserializer; 
class LuaScript;
class LuaScriptInstance;
class Serializer; 
class Variant;

/// C++ representation of Lua function object.
class URHO3D_API LuaFunction : public RefCounted
{
public:
    /// Construct from a Lua function object at the specified stack index.
    LuaFunction(lua_State* L, int index);
    /// Destruct.
    ~LuaFunction();

    /// Check that function is valid.
    bool IsValid() const;
    /// Begin function call. When a script object is given then pass it as self argument (first parameter) to the function call.
    bool BeginCall(const LuaScriptInstance* instance = 0);
    /// End call and actually execute the function. The return values, if any, are still left in the stack when this call returns.
    bool EndCall(int numReturns = 0);

    /// Push int to stack.
    void PushInt(int value);
    /// Push bool to stack.
    void PushBool(bool value);
    /// Push float to stack.
    void PushFloat(float value);
    /// Push string to stack.
    void PushString(const String& string);
	/// Push StringHash to stack.
	void PushStringHash(StringHash stringHash);

	/// Push Vector2 to stack.
	void PushVector2(const Vector2& vector);
	/// Push Vector3 to stack.
	void PushVector3(const Vector3& vector);
	/// Push Vector4 to stack.
	void PushVector4(const Vector4& vector);
	/// Push Quaternion to stack.
	void PushQuaternion(const Quaternion& quaternion);

	/// Push Variant to stack.
	void PushVariant(const Variant& variant);
	/// Push VariantMap to stack.
	void PushVariantMap(const VariantMap& variantMap);

	/// Push Lua table to stack. When the specified table is not found then a nil is pushed instead.
    void PushLuaTable(const char* tableName);
    /// Push Lua table to stack. When the specified table is not found then a nil is pushed instead.
    void PushLuaTable(const String& tableName) { PushLuaTable(tableName.CString()); }
    
    /// Push Deserializer to stack.
    void PushDeserializer(Deserializer* deserializer);
    /// Push Serializer to stack.
    void PushSerializer(Serializer* serializer);
    /// Push LuaScriptInstance to stack.
    void PushLuaScriptInstance(LuaScriptInstance* instance);

	/// Return lua state.
    lua_State* GetLuaState() const { return luaState_; }
    /// Return function ref.
    int GetFunctionRef() const { return functionRef_; }

private:
    /// Lua state.
    lua_State* luaState_;
    /// Number of arguments being pushed so far. For internal use only.
    int numArguments_;
    /// Lua reference to function object.
    int functionRef_;
};

}
