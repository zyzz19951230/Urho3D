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

#include "../Core/Context.h"
#include "../Database/Database.h"
#include "../Database/DatabaseEvents.h"
#include "../Database/DbConnection.h"
#include "../Database/DbResult.h"
#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterDatabase(kaguya::State& lua)
{
    using namespace kaguya;

    // enum DBAPI;
    lua["DBAPI_SQLITE"] = DBAPI_SQLITE;
    lua["DBAPI_ODBC"] = DBAPI_ODBC;

    lua["Database"].setClass(UserdataMetatable<Database, Object>()

        .addStaticFunction("GetAPI", &Database::GetAPI)

        .addFunction("Connect", &Database::Connect)
        .addFunction("Disconnect", &Database::Disconnect)
        .addFunction("IsPooling", &Database::IsPooling)
        .addFunction("GetPoolSize", &Database::GetPoolSize)
        .addFunction("SetPoolSize", &Database::SetPoolSize)

        .addProperty("pooling", &Database::IsPooling)
        .addProperty("poolSize", &Database::GetPoolSize, &Database::SetPoolSize)
    );    
}

static void RegisterDatabaseEvents(kaguya::State& lua)
{
    using namespace kaguya;

    lua["E_DBCURSOR"] = E_DBCURSOR;
}

static void RegisterDbConnection(kaguya::State& lua)
{
    using namespace kaguya;

    lua["DbConnection"].setClass(UserdataMetatable<DbConnection, Object>()
        
        .addFunction("Finalize", &DbConnection::Finalize)
        .addFunction("Execute", &DbConnection::Execute)
        .addFunction("GetConnectionString", &DbConnection::GetConnectionString)
        .addFunction("IsConnected", &DbConnection::IsConnected)

        .addProperty("connectionString", &DbConnection::GetConnectionString)
        .addProperty("connected", &DbConnection::IsConnected)
    );
}

static void RegisterDbResult(kaguya::State& lua)
{
    using namespace kaguya;

    lua["DbResult"].setClass(UserdataMetatable<DbResult>()
        
        .addFunction("GetNumColumns", &DbResult::GetNumColumns)
        .addFunction("GetNumRows", &DbResult::GetNumRows)
        .addFunction("GetNumAffectedRows", &DbResult::GetNumAffectedRows)
        .addFunction("GetColumns", &DbResult::GetColumns)
        .addFunction("GetRows", &DbResult::GetRows)

        .addProperty("numColumns", &DbResult::GetNumColumns)
        .addProperty("numRows", &DbResult::GetNumRows)
        .addProperty("numAffectedRows", &DbResult::GetNumAffectedRows)
    );
}

void RegisterDatabaseLuaAPI(kaguya::State& lua)
{
    RegisterDbResult(lua);
    RegisterDatabaseEvents(lua);
    RegisterDbConnection(lua);
    RegisterDatabase(lua);

    lua["database"] = KGetSubsystem<Database>();
    lua["GetDatabase"] = KGetSubsystem<Database>;
}
}

#endif
