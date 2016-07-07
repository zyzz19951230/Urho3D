#include "../Core/Context.h"
#include "../Network/Connection.h"
#include "../Network/HttpRequest.h"
#include "../Network/Network.h"
#include "../Network/NetworkEvents.h"
#include "../Network/NetworkPriority.h"
#include "../Network/Protocol.h"

#include "../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void RegisterConnection(kaguya::State& lua)
{
	using namespace kaguya;

	// enum ObserverPositionSendMode;
	lua["OPSM_NONE"] = OPSM_NONE;
	lua["OPSM_POSITION"] = OPSM_POSITION;
	lua["OPSM_POSITION_ROTATION"] = OPSM_POSITION_ROTATION;

	lua["Connection"].setClass(UserdataMetatable<Connection, Object>()

		.addOverloadedFunctions("SendMessage",
			static_cast<void(Connection::*)(int, bool, bool, const VectorBuffer&, unsigned)>(&Connection::SendMessage),
			static_cast<void(Connection::*)(int, bool, bool, const unsigned char*, unsigned, unsigned)>(&Connection::SendMessage))


		.addOverloadedFunctions("SendRemoteEvent",
			static_cast<void(Connection::*)(StringHash, bool, const VariantMap&)>(&Connection::SendRemoteEvent),
			static_cast<void(Connection::*)(Node*, StringHash, bool, const VariantMap&)>(&Connection::SendRemoteEvent))

		.addFunction("SetScene", &Connection::SetScene)
		.addFunction("SetControls", &Connection::SetControls)
		.addFunction("SetPosition", &Connection::SetPosition)
		.addFunction("SetRotation", &Connection::SetRotation)
		.addFunction("SetConnectPending", &Connection::SetConnectPending)
		.addFunction("SetLogStatistics", &Connection::SetLogStatistics)
		.addFunction("Disconnect", &Connection::Disconnect)
		.addFunction("SendServerUpdate", &Connection::SendServerUpdate)
		.addFunction("SendClientUpdate", &Connection::SendClientUpdate)
		.addFunction("SendRemoteEvents", &Connection::SendRemoteEvents)
		.addFunction("SendPackages", &Connection::SendPackages)
		.addFunction("ProcessPendingLatestData", &Connection::ProcessPendingLatestData)
		.addFunction("ProcessMessage", &Connection::ProcessMessage)

		.addFunction("GetScene", &Connection::GetScene)
		.addFunction("GetControls", &Connection::GetControls)
		.addFunction("GetTimeStamp", &Connection::GetTimeStamp)
		.addFunction("GetPosition", &Connection::GetPosition)
		.addFunction("GetRotation", &Connection::GetRotation)
		.addFunction("IsClient", &Connection::IsClient)
		.addFunction("IsConnected", &Connection::IsConnected)
		.addFunction("IsConnectPending", &Connection::IsConnectPending)
		.addFunction("IsSceneLoaded", &Connection::IsSceneLoaded)
		.addFunction("GetLogStatistics", &Connection::GetLogStatistics)
		.addFunction("GetAddress", &Connection::GetAddress)
		.addFunction("GetPort", &Connection::GetPort)
		.addFunction("GetRoundTripTime", &Connection::GetRoundTripTime)
		.addFunction("GetLastHeardTime", &Connection::GetLastHeardTime)
		.addFunction("GetBytesInPerSec", &Connection::GetBytesInPerSec)
		.addFunction("GetBytesOutPerSec", &Connection::GetBytesOutPerSec)
		.addFunction("GetPacketsInPerSec", &Connection::GetPacketsInPerSec)
		.addFunction("GetPacketsOutPerSec", &Connection::GetPacketsOutPerSec)
		.addFunction("ToString", &Connection::ToString)
		.addFunction("GetNumDownloads", &Connection::GetNumDownloads)
		.addFunction("GetDownloadName", &Connection::GetDownloadName)
		.addFunction("GetDownloadProgress", &Connection::GetDownloadProgress)
		.addFunction("SendPackageToClient", &Connection::SendPackageToClient)
		.addFunction("ConfigureNetworkSimulator", &Connection::ConfigureNetworkSimulator)

		// .addProperty("identity", &Connection::GetIdentity, &Connection::SetIdentity)
		.addProperty("scene", &Connection::GetScene, &Connection::SetScene)
		.addProperty("controls", &Connection::GetControls, &Connection::SetControls)
		.addProperty("timeStamp", &Connection::GetTimeStamp)
		.addProperty("position", &Connection::GetPosition, &Connection::SetPosition)
		.addProperty("rotation", &Connection::GetRotation, &Connection::SetRotation)
		.addProperty("client", &Connection::IsClient)
		.addProperty("connected", &Connection::IsConnected)
		.addProperty("connectPending", &Connection::IsConnectPending, &Connection::SetConnectPending)
		.addProperty("sceneLoaded", &Connection::IsSceneLoaded)
		.addProperty("logStatistics", &Connection::GetLogStatistics, &Connection::SetLogStatistics)
		.addProperty("address", &Connection::GetAddress)
		.addProperty("port", &Connection::GetPort)
		.addProperty("roundTripTime", &Connection::GetRoundTripTime)
		.addProperty("lastHeardTime", &Connection::GetLastHeardTime)
		.addProperty("bytesInPerSec", &Connection::GetBytesInPerSec)
		.addProperty("bytesOutPerSec", &Connection::GetBytesOutPerSec)
		.addProperty("packetsInPerSec", &Connection::GetPacketsInPerSec)
		.addProperty("packetsOutPerSec", &Connection::GetPacketsOutPerSec)
		.addProperty("numDownloads", &Connection::GetNumDownloads)
		.addProperty("downloadName", &Connection::GetDownloadName)
		.addProperty("downloadProgress", &Connection::GetDownloadProgress)
		/*
        .addProperty("controls", &Connection::controls_)
		.addProperty("timeStamp", &Connection::timeStamp_)
		.addProperty("identity", &Connection::identity_)
        */
	);
}

static void RegisterHttpRequest(kaguya::State& lua)
{
	using namespace kaguya;

	// enum HttpRequestState;
	lua["HTTP_INITIALIZING"] = HTTP_INITIALIZING;
	lua["HTTP_ERROR"] = HTTP_ERROR;
	lua["HTTP_OPEN"] = HTTP_OPEN;
	lua["HTTP_CLOSED"] = HTTP_CLOSED;

	// Deserializer
	lua["HttpRequest"].setClass(UserdataMetatable<HttpRequest, RefCounted>()
		.setConstructors<HttpRequest(const String&, const String&, const Vector<String>&, const String&)>()

		.addFunction("GetURL", &HttpRequest::GetURL)
		.addFunction("GetVerb", &HttpRequest::GetVerb)
		.addFunction("GetError", &HttpRequest::GetError)
		.addFunction("GetState", &HttpRequest::GetState)
		.addFunction("GetAvailableSize", &HttpRequest::GetAvailableSize)
		.addFunction("IsOpen", &HttpRequest::IsOpen)

		.addProperty("URL", &HttpRequest::GetURL)
		.addProperty("verb", &HttpRequest::GetVerb)
		.addProperty("error", &HttpRequest::GetError)
		.addProperty("state", &HttpRequest::GetState)
		.addProperty("availableSize", &HttpRequest::GetAvailableSize)
		.addProperty("open", &HttpRequest::IsOpen)
	);
}

static void RegisterNetwork(kaguya::State& lua)
{
	using namespace kaguya;

    lua["Network"].setClass(UserdataMetatable<Network, Object>()

		.addFunction("Connect", &Network::Connect)
		.addFunction("Disconnect", &Network::Disconnect)
		.addFunction("StartServer", &Network::StartServer)
		.addFunction("StopServer", &Network::StopServer)

		.addOverloadedFunctions("BroadcastMessage",
			static_cast<void(Network::*)(int, bool, bool, const VectorBuffer&, unsigned)>(&Network::BroadcastMessage),
			static_cast<void(Network::*)(int, bool, bool, const unsigned char*, unsigned, unsigned)>(&Network::BroadcastMessage))


		.addOverloadedFunctions("BroadcastRemoteEvent",
			static_cast<void(Network::*)(StringHash, bool, const VariantMap&)>(&Network::BroadcastRemoteEvent),
			static_cast<void(Network::*)(Scene*, StringHash, bool, const VariantMap&)>(&Network::BroadcastRemoteEvent),
			static_cast<void(Network::*)(Node*, StringHash, bool, const VariantMap&)>(&Network::BroadcastRemoteEvent))

		.addFunction("SetUpdateFps", &Network::SetUpdateFps)
		.addFunction("SetSimulatedLatency", &Network::SetSimulatedLatency)
		.addFunction("SetSimulatedPacketLoss", &Network::SetSimulatedPacketLoss)
		.addFunction("RegisterRemoteEvent", &Network::RegisterRemoteEvent)
		.addFunction("UnregisterRemoteEvent", &Network::UnregisterRemoteEvent)
		.addFunction("UnregisterAllRemoteEvents", &Network::UnregisterAllRemoteEvents)
		.addFunction("SetPackageCacheDir", &Network::SetPackageCacheDir)
		.addFunction("SendPackageToClients", &Network::SendPackageToClients)
		.addFunction("MakeHttpRequest", &Network::MakeHttpRequest)
		.addFunction("GetUpdateFps", &Network::GetUpdateFps)
		.addFunction("GetSimulatedLatency", &Network::GetSimulatedLatency)
		.addFunction("GetSimulatedPacketLoss", &Network::GetSimulatedPacketLoss)
		.addFunction("GetConnection", &Network::GetConnection)
		.addFunction("GetServerConnection", &Network::GetServerConnection)
		.addFunction("GetClientConnections", &Network::GetClientConnections)
		.addFunction("IsServerRunning", &Network::IsServerRunning)
		.addFunction("CheckRemoteEvent", &Network::CheckRemoteEvent)
		.addFunction("GetPackageCacheDir", &Network::GetPackageCacheDir)
		.addFunction("Update", &Network::Update)
		.addFunction("PostUpdate", &Network::PostUpdate)

		.addProperty("updateFps", &Network::GetUpdateFps, &Network::SetUpdateFps)
		.addProperty("simulatedLatency", &Network::GetSimulatedLatency, &Network::SetSimulatedLatency)
		.addProperty("simulatedPacketLoss", &Network::GetSimulatedPacketLoss, &Network::SetSimulatedPacketLoss)
		.addProperty("serverConnection", &Network::GetServerConnection)
		.addProperty("clientConnections", &Network::GetClientConnections)
		.addProperty("serverRunning", &Network::IsServerRunning)
		.addProperty("packageCacheDir", &Network::GetPackageCacheDir, &Network::SetPackageCacheDir)
	);
}

static void RegisterNetworkEvents(kaguya::State& lua)
{
	using namespace kaguya;

	lua["E_SERVERCONNECTED"] = E_SERVERCONNECTED;
	lua["E_SERVERDISCONNECTED"] = E_SERVERDISCONNECTED;
	lua["E_CONNECTFAILED"] = E_CONNECTFAILED;
	lua["E_CLIENTCONNECTED"] = E_CLIENTCONNECTED;
	lua["E_CLIENTDISCONNECTED"] = E_CLIENTDISCONNECTED;
	lua["E_CLIENTIDENTITY"] = E_CLIENTIDENTITY;
	lua["E_CLIENTSCENELOADED"] = E_CLIENTSCENELOADED;
	lua["E_NETWORKMESSAGE"] = E_NETWORKMESSAGE;
	lua["E_NETWORKUPDATE"] = E_NETWORKUPDATE;
	lua["E_NETWORKUPDATESENT"] = E_NETWORKUPDATESENT;
	lua["E_NETWORKSCENELOADFAILED"] = E_NETWORKSCENELOADFAILED;
	lua["E_REMOTEEVENTDATA"] = E_REMOTEEVENTDATA;
}

static void RegisterNetworkPriority(kaguya::State& lua)
{
	using namespace kaguya;

	lua["NetworkPriority"].setClass(UserdataMetatable<NetworkPriority, Component>()
		.addStaticFunction("new", &KCreateObject<NetworkPriority>)
		
		.addFunction("SetBasePriority", &NetworkPriority::SetBasePriority)
		.addFunction("SetDistanceFactor", &NetworkPriority::SetDistanceFactor)
		.addFunction("SetMinPriority", &NetworkPriority::SetMinPriority)
		.addFunction("SetAlwaysUpdateOwner", &NetworkPriority::SetAlwaysUpdateOwner)
		.addFunction("GetBasePriority", &NetworkPriority::GetBasePriority)
		.addFunction("GetDistanceFactor", &NetworkPriority::GetDistanceFactor)
		.addFunction("GetMinPriority", &NetworkPriority::GetMinPriority)
		.addFunction("GetAlwaysUpdateOwner", &NetworkPriority::GetAlwaysUpdateOwner)
		.addFunction("CheckUpdate", &NetworkPriority::CheckUpdate)

		.addProperty("basePriority", &NetworkPriority::GetBasePriority, &NetworkPriority::SetBasePriority)
		.addProperty("distanceFactor", &NetworkPriority::GetDistanceFactor, &NetworkPriority::SetDistanceFactor)
		.addProperty("minPriority", &NetworkPriority::GetMinPriority, &NetworkPriority::SetMinPriority)
		.addProperty("alwaysUpdateOwner", &NetworkPriority::GetAlwaysUpdateOwner, &NetworkPriority::SetAlwaysUpdateOwner)
	);
}

static void RegisterProtocol(kaguya::State& lua)
{
	using namespace kaguya;

	lua["MSG_IDENTITY"] = MSG_IDENTITY;
	lua["MSG_CONTROLS"] = MSG_CONTROLS;
	lua["MSG_SCENELOADED"] = MSG_SCENELOADED;
	lua["MSG_REQUESTPACKAGE"] = MSG_REQUESTPACKAGE;
	lua["MSG_PACKAGEDATA"] = MSG_PACKAGEDATA;
	lua["MSG_LOADSCENE"] = MSG_LOADSCENE;
	lua["MSG_SCENECHECKSUMERROR"] = MSG_SCENECHECKSUMERROR;
	lua["MSG_CREATENODE"] = MSG_CREATENODE;
	lua["MSG_NODEDELTAUPDATE"] = MSG_NODEDELTAUPDATE;
	lua["MSG_NODELATESTDATA"] = MSG_NODELATESTDATA;
	lua["MSG_REMOVENODE"] = MSG_REMOVENODE;
	lua["MSG_CREATECOMPONENT"] = MSG_CREATECOMPONENT;
	lua["MSG_COMPONENTDELTAUPDATE"] = MSG_COMPONENTDELTAUPDATE;
	lua["MSG_COMPONENTLATESTDATA"] = MSG_COMPONENTLATESTDATA;
	lua["MSG_REMOVECOMPONENT"] = MSG_REMOVECOMPONENT;
	lua["MSG_REMOTEEVENT"] = MSG_REMOTEEVENT;
	lua["MSG_REMOTENODEEVENT"] = MSG_REMOTENODEEVENT;
	lua["MSG_PACKAGEINFO"] = MSG_PACKAGEINFO;
	lua["CONTROLS_CONTENT_ID"] = CONTROLS_CONTENT_ID;
	lua["PACKAGE_FRAGMENT_SIZE"] = PACKAGE_FRAGMENT_SIZE;
}

void RegisterNetworkLuaAPI(kaguya::State& lua)
{
	RegisterConnection(lua);
	RegisterHttpRequest(lua);
	RegisterNetwork(lua);
	RegisterNetworkEvents(lua);
	RegisterNetworkPriority(lua);
	RegisterProtocol(lua);

    lua["network"] = KGetSubsystem<Network>();
    lua["GetNetwork"] = KGetSubsystem<Network>;
}
}
