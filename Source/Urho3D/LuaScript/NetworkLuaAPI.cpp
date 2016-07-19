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

#include "../Core/Context.h"
#include "../LuaScript/LuaScriptUtils.h"
#include "../Network/Connection.h"
#include "../Network/HttpRequest.h"
#include "../Network/Network.h"
#include "../Network/NetworkPriority.h"
#include "../Network/Protocol.h"

#include <kaguya.hpp>

namespace Urho3D
{

static void ConnectionSendMessage0(Connection* self, int msgID, bool reliable, bool inOrder, const VectorBuffer& msg)
{
    self->SendMessage(msgID, reliable, inOrder, msg);
}

static void ConnectionSendMessage1(Connection* self, int msgID, bool reliable, bool inOrder, const VectorBuffer& msg, unsigned int contentID)
{
    self->SendMessage(msgID, reliable, inOrder, msg, contentID);
}

static void ConnectionSendMessage2(Connection* self, int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned int numBytes)
{
    self->SendMessage(msgID, reliable, inOrder, data, numBytes);
}

static void ConnectionSendMessage3(Connection* self, int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned int numBytes, unsigned int contentID)
{
    self->SendMessage(msgID, reliable, inOrder, data, numBytes, contentID);
}

static void ConnectionSendRemoteEvent0(Connection* self, StringHash eventType, bool inOrder)
{
    self->SendRemoteEvent(eventType, inOrder);
}

static void ConnectionSendRemoteEvent1(Connection* self, StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    self->SendRemoteEvent(eventType, inOrder, eventData);
}

static void ConnectionSendRemoteEvent2(Connection* self, Node* node, StringHash eventType, bool inOrder)
{
    self->SendRemoteEvent(node, eventType, inOrder);
}

static void ConnectionSendRemoteEvent3(Connection* self, Node* node, StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    self->SendRemoteEvent(node, eventType, inOrder, eventData);
}

static void ConnectionDisconnect0(Connection* self)
{
    self->Disconnect();
}

static void ConnectionDisconnect1(Connection* self, int waitMSec)
{
    self->Disconnect(waitMSec);
}



static void RegisterConnection(kaguya::State& lua)
{
    using namespace kaguya;

    lua["RemoteEvent"].setClass(UserdataMetatable<RemoteEvent>()
        .addProperty("senderID", &RemoteEvent::senderID_)
        .addProperty("eventType", &RemoteEvent::eventType_)
        .addProperty("eventData", &RemoteEvent::eventData_)
        .addProperty("inOrder", &RemoteEvent::inOrder_)
        );

    lua["Connection"].setClass(UserdataMetatable<Connection, Object>()

        ADD_OVERLOADED_FUNCTIONS_4(Connection, SendMessage)
        ADD_OVERLOADED_FUNCTIONS_4(Connection, SendRemoteEvent)

        .addFunction("SetScene", &Connection::SetScene)
        .addFunction("SetIdentity", &Connection::SetIdentity)
        .addFunction("SetControls", &Connection::SetControls)
        .addFunction("SetPosition", &Connection::SetPosition)
        .addFunction("SetRotation", &Connection::SetRotation)
        .addFunction("SetConnectPending", &Connection::SetConnectPending)
        .addFunction("SetLogStatistics", &Connection::SetLogStatistics)

        ADD_OVERLOADED_FUNCTIONS_2(Connection, Disconnect)

        .addFunction("GetIdentity", &Connection::GetIdentity)
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
        
        .addProperty("identity", &Connection::GetIdentity)
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
        );
}

static VectorBuffer HttpRequestRead(HttpRequest* self, unsigned size)
{
    unsigned char* data = new unsigned char[size];
    self->Read(data, size);
    VectorBuffer buffer(data, size);
    delete[] data;
    return buffer;
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

        .addStaticFunction("Read", &HttpRequestRead)

        .addProperty("URL", &HttpRequest::GetURL)
        .addProperty("verb", &HttpRequest::GetVerb)
        .addProperty("error", &HttpRequest::GetError)
        .addProperty("state", &HttpRequest::GetState)
        .addProperty("availableSize", &HttpRequest::GetAvailableSize)
        .addProperty("open", &HttpRequest::IsOpen)
        );
}

static bool NetworkConnect0(Network* self, const String& address, unsigned short port, Scene* scene)
{
    return self->Connect(address, port, scene);
}

static bool NetworkConnect1(Network* self, const String& address, unsigned short port, Scene* scene, const VariantMap& identity)
{
    return self->Connect(address, port, scene, identity);
}

static void NetworkDisconnect0(Network* self)
{
    self->Disconnect();
}

static void NetworkDisconnect1(Network* self, int waitMSec)
{
    self->Disconnect(waitMSec);
}

static void NetworkBroadcastMessage0(Network* self, int msgID, bool reliable, bool inOrder, const VectorBuffer& msg)
{
    self->BroadcastMessage(msgID, reliable, inOrder, msg);
}

static void NetworkBroadcastMessage1(Network* self, int msgID, bool reliable, bool inOrder, const VectorBuffer& msg, unsigned int contentID)
{
    self->BroadcastMessage(msgID, reliable, inOrder, msg, contentID);
}

static void NetworkBroadcastMessage2(Network* self, int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned int numBytes)
{
    self->BroadcastMessage(msgID, reliable, inOrder, data, numBytes);
}

static void NetworkBroadcastMessage3(Network* self, int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned int numBytes, unsigned int contentID)
{
    self->BroadcastMessage(msgID, reliable, inOrder, data, numBytes, contentID);
}

static void NetworkBroadcastRemoteEvent0(Network* self, StringHash eventType, bool inOrder)
{
    self->BroadcastRemoteEvent(eventType, inOrder);
}

static void NetworkBroadcastRemoteEvent1(Network* self, StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    self->BroadcastRemoteEvent(eventType, inOrder, eventData);
}

static void NetworkBroadcastRemoteEvent2(Network* self, Scene* scene, StringHash eventType, bool inOrder)
{
    self->BroadcastRemoteEvent(scene, eventType, inOrder);
}

static void NetworkBroadcastRemoteEvent3(Network* self, Scene* scene, StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    self->BroadcastRemoteEvent(scene, eventType, inOrder, eventData);
}

static void NetworkBroadcastRemoteEvent4(Network* self, Node* node, StringHash eventType, bool inOrder)
{
    self->BroadcastRemoteEvent(node, eventType, inOrder);
}

static void NetworkBroadcastRemoteEvent5(Network* self, Node* node, StringHash eventType, bool inOrder, const VariantMap& eventData)
{
    self->BroadcastRemoteEvent(node, eventType, inOrder, eventData);
}

static SharedPtr<HttpRequest> NetworkMakeHttpRequest0(Network* self, const String& url)
{
    return self->MakeHttpRequest(url);
}

static SharedPtr<HttpRequest> NetworkMakeHttpRequest1(Network* self, const String& url, const String& verb)
{
    return self->MakeHttpRequest(url, verb);
}

static SharedPtr<HttpRequest> NetworkMakeHttpRequest2(Network* self, const String& url, const String& verb, const Vector<String>& headers)
{
    return self->MakeHttpRequest(url, verb, headers);
}

static SharedPtr<HttpRequest> NetworkMakeHttpRequest3(Network* self, const String& url, const String& verb, const Vector<String>& headers, const String& postData)
{
    return self->MakeHttpRequest(url, verb, headers, postData);
}

static void RegisterNetwork(kaguya::State& lua)
{
    using namespace kaguya;

    lua["Network"].setClass(UserdataMetatable<Network, Object>()

        ADD_OVERLOADED_FUNCTIONS_2(Network, Connect)
        ADD_OVERLOADED_FUNCTIONS_2(Network, Disconnect)

        .addFunction("StartServer", &Network::StartServer)
        .addFunction("StopServer", &Network::StopServer)

        ADD_OVERLOADED_FUNCTIONS_4(Network, BroadcastMessage)
        ADD_OVERLOADED_FUNCTIONS_6(Network, BroadcastRemoteEvent)

        .addFunction("SetUpdateFps", &Network::SetUpdateFps)
        .addFunction("SetSimulatedLatency", &Network::SetSimulatedLatency)
        .addFunction("SetSimulatedPacketLoss", &Network::SetSimulatedPacketLoss)

        .addFunction("RegisterRemoteEvent", &Network::RegisterRemoteEvent)
        .addFunction("UnregisterRemoteEvent", &Network::UnregisterRemoteEvent)
        .addFunction("UnregisterAllRemoteEvents", &Network::UnregisterAllRemoteEvents)
        
        .addFunction("SetPackageCacheDir", &Network::SetPackageCacheDir)
        .addFunction("SendPackageToClients", &Network::SendPackageToClients)

        ADD_OVERLOADED_FUNCTIONS_4(Network, MakeHttpRequest)

        .addFunction("GetUpdateFps", &Network::GetUpdateFps)
        .addFunction("GetSimulatedLatency", &Network::GetSimulatedLatency)
        .addFunction("GetSimulatedPacketLoss", &Network::GetSimulatedPacketLoss)
        .addFunction("GetConnection", &Network::GetConnection)
        .addFunction("GetServerConnection", &Network::GetServerConnection)
        
        .addFunction("IsServerRunning", &Network::IsServerRunning)
        .addFunction("CheckRemoteEvent", &Network::CheckRemoteEvent)
        .addFunction("GetPackageCacheDir", &Network::GetPackageCacheDir)

        .addProperty("updateFps", &Network::GetUpdateFps, &Network::SetUpdateFps)
        .addProperty("simulatedLatency", &Network::GetSimulatedLatency, &Network::SetSimulatedLatency)
        .addProperty("simulatedPacketLoss", &Network::GetSimulatedPacketLoss, &Network::SetSimulatedPacketLoss)
        .addProperty("serverConnection", &Network::GetServerConnection)
        .addProperty("serverRunning", &Network::IsServerRunning)
        .addProperty("packageCacheDir", &Network::GetPackageCacheDir, &Network::SetPackageCacheDir)
        );
}

static void RegisterNetworkPriority(kaguya::State& lua)
{
    using namespace kaguya;
    
    lua["NetworkPriority"].setClass(UserdataMetatable<NetworkPriority, Component>()
        .addStaticFunction("new", &CreateObject<NetworkPriority>)

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

void RegisterNetworkLuaAPI(kaguya::State& lua)
{
    RegisterConnection(lua);
    RegisterHttpRequest(lua);
    RegisterNetwork(lua);
    RegisterNetworkPriority(lua);

    lua["network"] = GetSubsystem<Network>();
    lua["GetNetwork"] = GetSubsystem<Network>;
}
}
