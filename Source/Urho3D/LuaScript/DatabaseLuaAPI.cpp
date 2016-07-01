// #include "../Database/Database.h"
// #include "../Database/DatabaseEvents.h"
// #include "../Database/DbConnection.h"
// #include "../Database/DbResult.h"
// #include "../Database/ODBC"
// #include "../Database/SQLite"

// #include "../LuaScript/LuaScriptUtils.h"

// #include <kaguya.hpp>

// namespace Urho3D
// {

// static void RegisterDatabase(kaguya::State& lua)
// {
//     using namespace kaguya;

//     // enum DBAPI;
//     lua["KDBAPI_SQLITE"] = DBAPI_SQLITE;
//     lua["KDBAPI_ODBC"] = DBAPI_ODBC;

//     lua["KDatabase"].setClass(UserdataMetatable<Database, Object>(false)
//         .addStaticFunction("new", &KCreateObject<Database>)
//         .addStaticFunction("__gc", &KReleaseObject<Database>)

//         .addFunction("GetType", &Database::GetType)
//         .addFunction("GetTypeName", &Database::GetTypeName)
//         .addFunction("GetTypeInfo", &Database::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Database::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Database::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Database::GetTypeInfoStatic)
//         .addStaticFunction("GetAPI", &Database::GetAPI)
//         .addFunction("Connect", &Database::Connect)
//         .addFunction("Disconnect", &Database::Disconnect)
//         .addFunction("IsPooling", &Database::IsPooling)
//         .addFunction("GetPoolSize", &Database::GetPoolSize)
//         .addFunction("SetPoolSize", &Database::SetPoolSize)

//         .addProperty("type", &Database::GetType)
//         .addProperty("typeName", &Database::GetTypeName)
//         .addProperty("typeInfo", &Database::GetTypeInfo)
//         .addProperty("pooling", &Database::IsPooling)
//         .addProperty("poolSize", &Database::GetPoolSize, &Database::SetPoolSize)
//     );
// }

// static void RegisterDatabaseEvents(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KE_DBCURSOR"] = E_DBCURSOR;
// }

// static void RegisterDbConnection(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KDbConnection"].setClass(UserdataMetatable<DbConnection, Object>()
//         .setConstructors<DbConnection(Context*, const String&)>()

//         .addFunction("GetType", &DbConnection::GetType)
//         .addFunction("GetTypeName", &DbConnection::GetTypeName)
//         .addFunction("GetTypeInfo", &DbConnection::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &DbConnection::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &DbConnection::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &DbConnection::GetTypeInfoStatic)
//         .addFunction("Finalize", &DbConnection::Finalize)
//         .addFunction("Execute", &DbConnection::Execute)
//         .addFunction("GetConnectionString", &DbConnection::GetConnectionString)
//         .addFunction("GetConnectionImpl", &DbConnection::GetConnectionImpl)
//         .addFunction("IsConnected", &DbConnection::IsConnected)

//         .addProperty("type", &DbConnection::GetType)
//         .addProperty("typeName", &DbConnection::GetTypeName)
//         .addProperty("typeInfo", &DbConnection::GetTypeInfo)
//         .addProperty("connectionString", &DbConnection::GetConnectionString)
//         .addProperty("connectionImpl", &DbConnection::GetConnectionImpl)
//         .addProperty("connected", &DbConnection::IsConnected)
//     );
// }

// static void RegisterDbResult(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KDbResult"].setClass(UserdataMetatable<DbResult>()
//         .setConstructors<DbResult()>()

//         .addFunction("GetNumColumns", &DbResult::GetNumColumns)
//         .addFunction("GetNumRows", &DbResult::GetNumRows)
//         .addFunction("GetNumAffectedRows", &DbResult::GetNumAffectedRows)
//         .addFunction("GetResultImpl", &DbResult::GetResultImpl)
//         .addFunction("GetColumns", &DbResult::GetColumns)
//         .addFunction("GetRows", &DbResult::GetRows)

//         .addProperty("numColumns", &DbResult::GetNumColumns)
//         .addProperty("numRows", &DbResult::GetNumRows)
//         .addProperty("numAffectedRows", &DbResult::GetNumAffectedRows)
//         .addProperty("resultImpl", &DbResult::GetResultImpl)
//         .addProperty("columns", &DbResult::GetColumns)
//         .addProperty("rows", &DbResult::GetRows)
//     );
// }

// void RegisterDatabaseLuaAPI(kaguya::State& lua)
// {
//     RegisterDatabase(lua);
//     RegisterDatabaseEvents(lua);
//     RegisterDbConnection(lua);
//     RegisterDbResult(lua);
// }
// }
