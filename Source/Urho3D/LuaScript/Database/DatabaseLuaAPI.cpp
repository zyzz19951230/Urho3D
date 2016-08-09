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

#include "../../Database/Database.h"
#include "../../Database/DbConnection.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

void RegisterDatabase(kaguya::State& lua)
{
    using namespace kaguya;

    // [Enum] DBAPI
    // [Variable] DBAPI_SQLITE
    lua["DBAPI_SQLITE"] = DBAPI_SQLITE;
    // [Variable] DBAPI_ODBC
    lua["DBAPI_ODBC"] = DBAPI_ODBC;

    // [Class] Database : Object
    lua["Database"].setClass(UserdataMetatable<Database, Object>()

        .addStaticFunction("GetAPI", &Database::GetAPI)

        // [Method] DbConnection* Connect(const String& connectionString)
        .addFunction("Connect", &Database::Connect)
        // [Method] void Disconnect(DbConnection* connection)
        .addFunction("Disconnect", &Database::Disconnect)
        // [Method] bool IsPooling() const
        .addFunction("IsPooling", &Database::IsPooling)
        // [Method] unsigned GetPoolSize() const
        .addFunction("GetPoolSize", &Database::GetPoolSize)
        // [Method] void SetPoolSize(unsigned poolSize)
        .addFunction("SetPoolSize", &Database::SetPoolSize)

        // [Property(ReadOnly)] bool pooling
        .addProperty("pooling", &Database::IsPooling)
        // [Property] unsigned poolSize
        .addProperty("poolSize", &Database::GetPoolSize, &Database::SetPoolSize)
    );

    // lua["GetDBAPI"] = function(&Database::GetAPI)
}
}

#endif
