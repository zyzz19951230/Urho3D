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

#ifdef URHO3D_NETWORK

#include "../../Precompiled.h"

#include "../../IO/PackageFile.h"
#include "../../Network/HttpRequest.h"
#include "../../Network/Network.h"
#include "../../Scene/Scene.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kNet/kNet.h>
#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS(NetworkConnect, Network, Connect, 3, 4);
KAGUYA_MEMBER_FUNCTION_OVERLOADS(NetworkDisconnect, Network, Disconnect, 0, 1);

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(NetworkBroadcastMessage0, Network, BroadcastMessage, 4, 5, void(Network::*)(int, bool, bool, const VectorBuffer&, unsigned));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(NetworkBroadcastMessage1, Network, BroadcastMessage, 5, 6, void(Network::*)(int, bool, bool, const unsigned char*, unsigned, unsigned));

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(NetworkBroadcastRemoteEvent0, Network, BroadcastRemoteEvent, 2, 3, void(Network::*)(StringHash, bool, const VariantMap&));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(NetworkBroadcastRemoteEvent1, Network, BroadcastRemoteEvent, 3, 4, void(Network::*)(Scene*, StringHash, bool, const VariantMap&));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(NetworkBroadcastRemoteEvent2, Network, BroadcastRemoteEvent, 3, 4, void(Network::*)(Node*, StringHash, bool, const VariantMap&));

KAGUYA_MEMBER_FUNCTION_OVERLOADS(NetworkMakeHttpRequest, Network, MakeHttpRequest, 1, 4);

void RegisterNetwork(kaguya::State& lua)
{
    using namespace kaguya;

    // [Class] Network : Object
    lua["Network"].setClass(UserdataMetatable<Network, Object>()

        // [Method] bool Connect(const String& address, unsigned short port, Scene* scene, const VariantMap& identity = Variant::emptyVariantMap)
        .addFunction("Connect", NetworkConnect())
        // [Method] void Disconnect(int waitMSec = 0)
        .addFunction("Disconnect", NetworkDisconnect())

        // [Method] bool StartServer(unsigned short port)
        .addFunction("StartServer", &Network::StartServer)
        // [Method] void StopServer()
        .addFunction("StopServer", &Network::StopServer)

        .addOverloadedFunctions("BroadcastMessage", 
            // [Method] void BroadcastMessage(int msgID, bool reliable, bool inOrder, const VectorBuffer& msg, unsigned contentID = 0)
            NetworkBroadcastMessage0(),
            // [Method] void BroadcastMessage(int msgID, bool reliable, bool inOrder, const unsigned char* data, unsigned numBytes, unsigned contentID = 0)
            NetworkBroadcastMessage1())

        .addOverloadedFunctions("BroadcastRemoteEvent", 
            // [Method] void BroadcastRemoteEvent(StringHash eventType, bool inOrder, const VariantMap& eventData = Variant::emptyVariantMap)
            NetworkBroadcastRemoteEvent0(),
            // [Method] void BroadcastRemoteEvent(Scene* scene, StringHash eventType, bool inOrder, const VariantMap& eventData = Variant::emptyVariantMap)
            NetworkBroadcastRemoteEvent1(),
            // [Method] void BroadcastRemoteEvent(Node* node, StringHash eventType, bool inOrder, const VariantMap& eventData = Variant::emptyVariantMap)
            NetworkBroadcastRemoteEvent2())

        // [Method] void SetUpdateFps(int fps)
        .addFunction("SetUpdateFps", &Network::SetUpdateFps)
        // [Method] void SetSimulatedLatency(int ms)
        .addFunction("SetSimulatedLatency", &Network::SetSimulatedLatency)
        // [Method] void SetSimulatedPacketLoss(float probability)
        .addFunction("SetSimulatedPacketLoss", &Network::SetSimulatedPacketLoss)

        // [Method] void RegisterRemoteEvent(StringHash eventType)
        .addFunction("RegisterRemoteEvent", &Network::RegisterRemoteEvent)
        // [Method] void UnregisterRemoteEvent(StringHash eventType)
        .addFunction("UnregisterRemoteEvent", &Network::UnregisterRemoteEvent)
        // [Method] void UnregisterAllRemoteEvents()
        .addFunction("UnregisterAllRemoteEvents", &Network::UnregisterAllRemoteEvents)
        
        // [Method] void SetPackageCacheDir(const String& path)
        .addFunction("SetPackageCacheDir", &Network::SetPackageCacheDir)
        // [Method] void SendPackageToClients(Scene* scene, PackageFile* package)
        .addFunction("SendPackageToClients", &Network::SendPackageToClients)

        .addFunction("MakeHttpRequest", NetworkMakeHttpRequest())

        // [Method] int GetUpdateFps() const
        .addFunction("GetUpdateFps", &Network::GetUpdateFps)
        // [Method] int GetSimulatedLatency() const
        .addFunction("GetSimulatedLatency", &Network::GetSimulatedLatency)
        // [Method] float GetSimulatedPacketLoss() const
        .addFunction("GetSimulatedPacketLoss", &Network::GetSimulatedPacketLoss)
        // [Method] Connection* GetConnection(kNet::MessageConnection* connection) const
        .addFunction("GetConnection", &Network::GetConnection)
        // [Method] Connection* GetServerConnection() const
        .addFunction("GetServerConnection", &Network::GetServerConnection)
        
        // [Method] bool IsServerRunning() const
        .addFunction("IsServerRunning", &Network::IsServerRunning)
        // [Method] bool CheckRemoteEvent(StringHash eventType) const
        .addFunction("CheckRemoteEvent", &Network::CheckRemoteEvent)
        // [Method] const String& GetPackageCacheDir() const
        .addFunction("GetPackageCacheDir", &Network::GetPackageCacheDir)

        // [Property] int updateFps
        .addProperty("updateFps", &Network::GetUpdateFps, &Network::SetUpdateFps)
        // [Property] int simulatedLatency
        .addProperty("simulatedLatency", &Network::GetSimulatedLatency, &Network::SetSimulatedLatency)
        // [Property] float simulatedPacketLoss
        .addProperty("simulatedPacketLoss", &Network::GetSimulatedPacketLoss, &Network::SetSimulatedPacketLoss)
        // [Property(Readonly)] Connection* serverConnection
        .addProperty("serverConnection", &Network::GetServerConnection)
        // [Property(Readonly)] bool serverRunning
        .addProperty("serverRunning", &Network::IsServerRunning)
        // [Property] const String& packageCacheDir
        .addProperty("packageCacheDir", &Network::GetPackageCacheDir, &Network::SetPackageCacheDir)
        );
}
}

#endif
