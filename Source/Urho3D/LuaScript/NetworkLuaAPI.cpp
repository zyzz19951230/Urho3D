// #include "../Network/Connection.h"
// #include "../Network/HttpRequest.h"
// #include "../Network/Network.h"
// #include "../Network/NetworkEvents.h"
// #include "../Network/NetworkPriority.h"
// #include "../Network/Protocol.h"

// #include "../LuaScript/LuaScriptUtils.h"

// #include <kaguya.hpp>

// namespace Urho3D
// {

// static void RegisterConnection(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KRemoteEvent"].setClass(UserdataMetatable<RemoteEvent>()

//         .addProperty("senderID", &RemoteEvent::senderID_)
//         .addProperty("eventType", &RemoteEvent::eventType_)
//         .addProperty("eventData", &RemoteEvent::eventData_)
//         .addProperty("inOrder", &RemoteEvent::inOrder_)
//     );
//     lua["KPackageDownload"].setClass(UserdataMetatable<PackageDownload>()
//         .setConstructors<PackageDownload()>()

//         .addProperty("file", &PackageDownload::file_)
//         .addProperty("receivedFragments", &PackageDownload::receivedFragments_)
//         .addProperty("name", &PackageDownload::name_)
//         .addProperty("totalFragments", &PackageDownload::totalFragments_)
//         .addProperty("checksum", &PackageDownload::checksum_)
//         .addProperty("initiated", &PackageDownload::initiated_)
//     );
//     lua["KPackageUpload"].setClass(UserdataMetatable<PackageUpload>()
//         .setConstructors<PackageUpload()>()

//         .addProperty("file", &PackageUpload::file_)
//         .addProperty("fragment", &PackageUpload::fragment_)
//         .addProperty("totalFragments", &PackageUpload::totalFragments_)
//     );
//     // enum ObserverPositionSendMode;
//     lua["KOPSM_NONE"] = OPSM_NONE;
//     lua["KOPSM_POSITION"] = OPSM_POSITION;
//     lua["KOPSM_POSITION_ROTATION"] = OPSM_POSITION_ROTATION;

//     lua["KConnection"].setClass(UserdataMetatable<Connection, Object>(false)
//         .addStaticFunction("new", &KCreateObject<Connection>)
//         .addStaticFunction("__gc", &KReleaseObject<Connection>)

//         .addFunction("GetType", &Connection::GetType)
//         .addFunction("GetTypeName", &Connection::GetTypeName)
//         .addFunction("GetTypeInfo", &Connection::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Connection::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Connection::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Connection::GetTypeInfoStatic)

//         .addOverloadedFunctions("SendMessage",
//             static_cast<void(Connection::*)(int, bool, bool, const VectorBuffer&, unsigned int)>(&Connection::SendMessage),
//             static_cast<void(Connection::*)(int, bool, bool, const unsigned char*, unsigned int, unsigned int)>(&Connection::SendMessage))


//         .addOverloadedFunctions("SendRemoteEvent",
//             static_cast<void(Connection::*)(StringHash, bool, const VariantMap&)>(&Connection::SendRemoteEvent),
//             static_cast<void(Connection::*)(Node*, StringHash, bool, const VariantMap&)>(&Connection::SendRemoteEvent))

//         .addFunction("SetScene", &Connection::SetScene)
//         .addFunction("SetIdentity", &Connection::SetIdentity)
//         .addFunction("SetControls", &Connection::SetControls)
//         .addFunction("SetPosition", &Connection::SetPosition)
//         .addFunction("SetRotation", &Connection::SetRotation)
//         .addFunction("SetConnectPending", &Connection::SetConnectPending)
//         .addFunction("SetLogStatistics", &Connection::SetLogStatistics)
//         .addFunction("Disconnect", &Connection::Disconnect)
//         .addFunction("SendServerUpdate", &Connection::SendServerUpdate)
//         .addFunction("SendClientUpdate", &Connection::SendClientUpdate)
//         .addFunction("SendRemoteEvents", &Connection::SendRemoteEvents)
//         .addFunction("SendPackages", &Connection::SendPackages)
//         .addFunction("ProcessPendingLatestData", &Connection::ProcessPendingLatestData)
//         .addFunction("ProcessMessage", &Connection::ProcessMessage)
//         .addFunction("GetMessageConnection", &Connection::GetMessageConnection)
//         .addFunction("GetIdentity", &Connection::GetIdentity)
//         .addFunction("GetScene", &Connection::GetScene)
//         .addFunction("GetControls", &Connection::GetControls)
//         .addFunction("GetTimeStamp", &Connection::GetTimeStamp)
//         .addFunction("GetPosition", &Connection::GetPosition)
//         .addFunction("GetRotation", &Connection::GetRotation)
//         .addFunction("IsClient", &Connection::IsClient)
//         .addFunction("IsConnected", &Connection::IsConnected)
//         .addFunction("IsConnectPending", &Connection::IsConnectPending)
//         .addFunction("IsSceneLoaded", &Connection::IsSceneLoaded)
//         .addFunction("GetLogStatistics", &Connection::GetLogStatistics)
//         .addFunction("GetAddress", &Connection::GetAddress)
//         .addFunction("GetPort", &Connection::GetPort)
//         .addFunction("GetRoundTripTime", &Connection::GetRoundTripTime)
//         .addFunction("GetLastHeardTime", &Connection::GetLastHeardTime)
//         .addFunction("GetBytesInPerSec", &Connection::GetBytesInPerSec)
//         .addFunction("GetBytesOutPerSec", &Connection::GetBytesOutPerSec)
//         .addFunction("GetPacketsInPerSec", &Connection::GetPacketsInPerSec)
//         .addFunction("GetPacketsOutPerSec", &Connection::GetPacketsOutPerSec)
//         .addFunction("ToString", &Connection::ToString)
//         .addFunction("GetNumDownloads", &Connection::GetNumDownloads)
//         .addFunction("GetDownloadName", &Connection::GetDownloadName)
//         .addFunction("GetDownloadProgress", &Connection::GetDownloadProgress)
//         .addFunction("SendPackageToClient", &Connection::SendPackageToClient)
//         .addFunction("ConfigureNetworkSimulator", &Connection::ConfigureNetworkSimulator)

//         .addProperty("type", &Connection::GetType)
//         .addProperty("typeName", &Connection::GetTypeName)
//         .addProperty("typeInfo", &Connection::GetTypeInfo)
//         .addProperty("messageConnection", &Connection::GetMessageConnection)
//         .addProperty("identity", &Connection::GetIdentity, &Connection::SetIdentity)
//         .addProperty("scene", &Connection::GetScene, &Connection::SetScene)
//         .addProperty("controls", &Connection::GetControls, &Connection::SetControls)
//         .addProperty("timeStamp", &Connection::GetTimeStamp)
//         .addProperty("position", &Connection::GetPosition, &Connection::SetPosition)
//         .addProperty("rotation", &Connection::GetRotation, &Connection::SetRotation)
//         .addProperty("client", &Connection::IsClient)
//         .addProperty("connected", &Connection::IsConnected)
//         .addProperty("connectPending", &Connection::IsConnectPending, &Connection::SetConnectPending)
//         .addProperty("sceneLoaded", &Connection::IsSceneLoaded)
//         .addProperty("logStatistics", &Connection::GetLogStatistics, &Connection::SetLogStatistics)
//         .addProperty("address", &Connection::GetAddress)
//         .addProperty("port", &Connection::GetPort)
//         .addProperty("roundTripTime", &Connection::GetRoundTripTime)
//         .addProperty("lastHeardTime", &Connection::GetLastHeardTime)
//         .addProperty("bytesInPerSec", &Connection::GetBytesInPerSec)
//         .addProperty("bytesOutPerSec", &Connection::GetBytesOutPerSec)
//         .addProperty("packetsInPerSec", &Connection::GetPacketsInPerSec)
//         .addProperty("packetsOutPerSec", &Connection::GetPacketsOutPerSec)
//         .addProperty("numDownloads", &Connection::GetNumDownloads)
//         .addProperty("downloadName", &Connection::GetDownloadName)
//         .addProperty("downloadProgress", &Connection::GetDownloadProgress)
//         .addProperty("controls", &Connection::controls_)
//         .addProperty("timeStamp", &Connection::timeStamp_)
//         .addProperty("identity", &Connection::identity_)
//     );
// }

// static void RegisterHttpRequest(kaguya::State& lua)
// {
//     using namespace kaguya;

//     // enum HttpRequestState;
//     lua["KHTTP_INITIALIZING"] = HTTP_INITIALIZING;
//     lua["KHTTP_ERROR"] = HTTP_ERROR;
//     lua["KHTTP_OPEN"] = HTTP_OPEN;
//     lua["KHTTP_CLOSED"] = HTTP_CLOSED;

//     lua["KHttpRequest"].setClass(UserdataMetatable<HttpRequest, RefCounted, Deserializer, Thread>()
//         .setConstructors<HttpRequest(const String&, const String&, const Vector<String>&, const String&)>()

//         .addFunction("ThreadFunction", &HttpRequest::ThreadFunction)
//         .addFunction("Read", &HttpRequest::Read)
//         .addFunction("Seek", &HttpRequest::Seek)
//         .addFunction("IsEof", &HttpRequest::IsEof)
//         .addFunction("GetURL", &HttpRequest::GetURL)
//         .addFunction("GetVerb", &HttpRequest::GetVerb)
//         .addFunction("GetError", &HttpRequest::GetError)
//         .addFunction("GetState", &HttpRequest::GetState)
//         .addFunction("GetAvailableSize", &HttpRequest::GetAvailableSize)
//         .addFunction("IsOpen", &HttpRequest::IsOpen)

//         .addProperty("eof", &HttpRequest::IsEof)
//         .addProperty("uRL", &HttpRequest::GetURL)
//         .addProperty("verb", &HttpRequest::GetVerb)
//         .addProperty("error", &HttpRequest::GetError)
//         .addProperty("state", &HttpRequest::GetState)
//         .addProperty("availableSize", &HttpRequest::GetAvailableSize)
//         .addProperty("open", &HttpRequest::IsOpen)
//     );
// }

// static void RegisterNetwork(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KNetwork"].setClass(UserdataMetatable<Network, Object>(false)
//         .addStaticFunction("new", &KCreateObject<Network>)
//         .addStaticFunction("__gc", &KReleaseObject<Network>)

//         .addFunction("GetType", &Network::GetType)
//         .addFunction("GetTypeName", &Network::GetTypeName)
//         .addFunction("GetTypeInfo", &Network::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &Network::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &Network::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &Network::GetTypeInfoStatic)
//         .addFunction("HandleMessage", &Network::HandleMessage)
//         .addFunction("ComputeContentID", &Network::ComputeContentID)
//         .addFunction("NewConnectionEstablished", &Network::NewConnectionEstablished)
//         .addFunction("ClientDisconnected", &Network::ClientDisconnected)
//         .addFunction("Connect", &Network::Connect)
//         .addFunction("Disconnect", &Network::Disconnect)
//         .addFunction("StartServer", &Network::StartServer)
//         .addFunction("StopServer", &Network::StopServer)

//         .addOverloadedFunctions("BroadcastMessage",
//             static_cast<void(Network::*)(int, bool, bool, const VectorBuffer&, unsigned int)>(&Network::BroadcastMessage),
//             static_cast<void(Network::*)(int, bool, bool, const unsigned char*, unsigned int, unsigned int)>(&Network::BroadcastMessage))


//         .addOverloadedFunctions("BroadcastRemoteEvent",
//             static_cast<void(Network::*)(StringHash, bool, const VariantMap&)>(&Network::BroadcastRemoteEvent),
//             static_cast<void(Network::*)(Scene*, StringHash, bool, const VariantMap&)>(&Network::BroadcastRemoteEvent),
//             static_cast<void(Network::*)(Node*, StringHash, bool, const VariantMap&)>(&Network::BroadcastRemoteEvent))

//         .addFunction("SetUpdateFps", &Network::SetUpdateFps)
//         .addFunction("SetSimulatedLatency", &Network::SetSimulatedLatency)
//         .addFunction("SetSimulatedPacketLoss", &Network::SetSimulatedPacketLoss)
//         .addFunction("RegisterRemoteEvent", &Network::RegisterRemoteEvent)
//         .addFunction("UnregisterRemoteEvent", &Network::UnregisterRemoteEvent)
//         .addFunction("UnregisterAllRemoteEvents", &Network::UnregisterAllRemoteEvents)
//         .addFunction("SetPackageCacheDir", &Network::SetPackageCacheDir)
//         .addFunction("SendPackageToClients", &Network::SendPackageToClients)
//         .addFunction("MakeHttpRequest", &Network::MakeHttpRequest)
//         .addFunction("GetUpdateFps", &Network::GetUpdateFps)
//         .addFunction("GetSimulatedLatency", &Network::GetSimulatedLatency)
//         .addFunction("GetSimulatedPacketLoss", &Network::GetSimulatedPacketLoss)
//         .addFunction("GetConnection", &Network::GetConnection)
//         .addFunction("GetServerConnection", &Network::GetServerConnection)
//         .addFunction("GetClientConnections", &Network::GetClientConnections)
//         .addFunction("IsServerRunning", &Network::IsServerRunning)
//         .addFunction("CheckRemoteEvent", &Network::CheckRemoteEvent)
//         .addFunction("GetPackageCacheDir", &Network::GetPackageCacheDir)
//         .addFunction("Update", &Network::Update)
//         .addFunction("PostUpdate", &Network::PostUpdate)

//         .addProperty("type", &Network::GetType)
//         .addProperty("typeName", &Network::GetTypeName)
//         .addProperty("typeInfo", &Network::GetTypeInfo)
//         .addProperty("updateFps", &Network::GetUpdateFps, &Network::SetUpdateFps)
//         .addProperty("simulatedLatency", &Network::GetSimulatedLatency, &Network::SetSimulatedLatency)
//         .addProperty("simulatedPacketLoss", &Network::GetSimulatedPacketLoss, &Network::SetSimulatedPacketLoss)
//         .addProperty("serverConnection", &Network::GetServerConnection)
//         .addProperty("clientConnections", &Network::GetClientConnections)
//         .addProperty("serverRunning", &Network::IsServerRunning)
//         .addProperty("packageCacheDir", &Network::GetPackageCacheDir, &Network::SetPackageCacheDir)
//     );
//     lua["KRegisterNetworkLibrary"] = function(&RegisterNetworkLibrary);
// }

// static void RegisterNetworkEvents(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KE_SERVERCONNECTED"] = E_SERVERCONNECTED;
//     lua["KE_SERVERDISCONNECTED"] = E_SERVERDISCONNECTED;
//     lua["KE_CONNECTFAILED"] = E_CONNECTFAILED;
//     lua["KE_CLIENTCONNECTED"] = E_CLIENTCONNECTED;
//     lua["KE_CLIENTDISCONNECTED"] = E_CLIENTDISCONNECTED;
//     lua["KE_CLIENTIDENTITY"] = E_CLIENTIDENTITY;
//     lua["KE_CLIENTSCENELOADED"] = E_CLIENTSCENELOADED;
//     lua["KE_NETWORKMESSAGE"] = E_NETWORKMESSAGE;
//     lua["KE_NETWORKUPDATE"] = E_NETWORKUPDATE;
//     lua["KE_NETWORKUPDATESENT"] = E_NETWORKUPDATESENT;
//     lua["KE_NETWORKSCENELOADFAILED"] = E_NETWORKSCENELOADFAILED;
//     lua["KE_REMOTEEVENTDATA"] = E_REMOTEEVENTDATA;
// }

// static void RegisterNetworkPriority(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KNetworkPriority"].setClass(UserdataMetatable<NetworkPriority, Component>(false)
//         .addStaticFunction("new", &KCreateObject<NetworkPriority>)
//         .addStaticFunction("__gc", &KReleaseObject<NetworkPriority>)

//         .addFunction("GetType", &NetworkPriority::GetType)
//         .addFunction("GetTypeName", &NetworkPriority::GetTypeName)
//         .addFunction("GetTypeInfo", &NetworkPriority::GetTypeInfo)
//         .addStaticFunction("GetTypeStatic", &NetworkPriority::GetTypeStatic)
//         .addStaticFunction("GetTypeNameStatic", &NetworkPriority::GetTypeNameStatic)
//         .addStaticFunction("GetTypeInfoStatic", &NetworkPriority::GetTypeInfoStatic)
//         .addFunction("SetBasePriority", &NetworkPriority::SetBasePriority)
//         .addFunction("SetDistanceFactor", &NetworkPriority::SetDistanceFactor)
//         .addFunction("SetMinPriority", &NetworkPriority::SetMinPriority)
//         .addFunction("SetAlwaysUpdateOwner", &NetworkPriority::SetAlwaysUpdateOwner)
//         .addFunction("GetBasePriority", &NetworkPriority::GetBasePriority)
//         .addFunction("GetDistanceFactor", &NetworkPriority::GetDistanceFactor)
//         .addFunction("GetMinPriority", &NetworkPriority::GetMinPriority)
//         .addFunction("GetAlwaysUpdateOwner", &NetworkPriority::GetAlwaysUpdateOwner)
//         .addFunction("CheckUpdate", &NetworkPriority::CheckUpdate)

//         .addProperty("type", &NetworkPriority::GetType)
//         .addProperty("typeName", &NetworkPriority::GetTypeName)
//         .addProperty("typeInfo", &NetworkPriority::GetTypeInfo)
//         .addProperty("basePriority", &NetworkPriority::GetBasePriority, &NetworkPriority::SetBasePriority)
//         .addProperty("distanceFactor", &NetworkPriority::GetDistanceFactor, &NetworkPriority::SetDistanceFactor)
//         .addProperty("minPriority", &NetworkPriority::GetMinPriority, &NetworkPriority::SetMinPriority)
//         .addProperty("alwaysUpdateOwner", &NetworkPriority::GetAlwaysUpdateOwner, &NetworkPriority::SetAlwaysUpdateOwner)
//     );
// }

// static void RegisterProtocol(kaguya::State& lua)
// {
//     using namespace kaguya;

//     lua["KMSG_IDENTITY"] = MSG_IDENTITY;
//     lua["KMSG_CONTROLS"] = MSG_CONTROLS;
//     lua["KMSG_SCENELOADED"] = MSG_SCENELOADED;
//     lua["KMSG_REQUESTPACKAGE"] = MSG_REQUESTPACKAGE;
//     lua["KMSG_PACKAGEDATA"] = MSG_PACKAGEDATA;
//     lua["KMSG_LOADSCENE"] = MSG_LOADSCENE;
//     lua["KMSG_SCENECHECKSUMERROR"] = MSG_SCENECHECKSUMERROR;
//     lua["KMSG_CREATENODE"] = MSG_CREATENODE;
//     lua["KMSG_NODEDELTAUPDATE"] = MSG_NODEDELTAUPDATE;
//     lua["KMSG_NODELATESTDATA"] = MSG_NODELATESTDATA;
//     lua["KMSG_REMOVENODE"] = MSG_REMOVENODE;
//     lua["KMSG_CREATECOMPONENT"] = MSG_CREATECOMPONENT;
//     lua["KMSG_COMPONENTDELTAUPDATE"] = MSG_COMPONENTDELTAUPDATE;
//     lua["KMSG_COMPONENTLATESTDATA"] = MSG_COMPONENTLATESTDATA;
//     lua["KMSG_REMOVECOMPONENT"] = MSG_REMOVECOMPONENT;
//     lua["KMSG_REMOTEEVENT"] = MSG_REMOTEEVENT;
//     lua["KMSG_REMOTENODEEVENT"] = MSG_REMOTENODEEVENT;
//     lua["KMSG_PACKAGEINFO"] = MSG_PACKAGEINFO;
//     lua["KCONTROLS_CONTENT_ID"] = CONTROLS_CONTENT_ID;
//     lua["KPACKAGE_FRAGMENT_SIZE"] = PACKAGE_FRAGMENT_SIZE;
// }

// void RegisterNetworkLuaAPI(kaguya::State& lua)
// {
//     RegisterConnection(lua);
//     RegisterHttpRequest(lua);
//     RegisterNetwork(lua);
//     RegisterNetworkEvents(lua);
//     RegisterNetworkPriority(lua);
//     RegisterProtocol(lua);
// }
// }
