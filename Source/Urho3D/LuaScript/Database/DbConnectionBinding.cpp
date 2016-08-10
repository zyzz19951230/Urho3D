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

#ifdef URHO3D_DATABASE

#include "../../Precompiled.h"

#include "../../Database/DbConnection.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(DbConnectionExecute, DbConnection, Execute, 1, 2);

void RegisterDbConnection(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] DbConnection : Object
    lua["DbConnection"].setClass(UserdataMetatable<DbConnection, Object>()
        // [Method] void Finalize()
        .addFunction("Finalize", &DbConnection::Finalize)
        // [Method] DbResult Execute(const String& sql, bool useCursorEvent = false)
        .addFunction("Execute", DbConnectionExecute())
        // [Method] const String& GetConnectionString() const
        .addFunction("GetConnectionString", &DbConnection::GetConnectionString)
        // [Method] bool IsConnected() const
        .addFunction("IsConnected", &DbConnection::IsConnected)

        // [Property] const String& connectionString
        .addProperty("connectionString", &DbConnection::GetConnectionString)
        // [Property] bool connected
        .addProperty("connected", &DbConnection::IsConnected)
    );
}
}

#endif
