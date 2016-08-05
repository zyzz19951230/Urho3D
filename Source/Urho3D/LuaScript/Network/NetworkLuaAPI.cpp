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

    lua["Network"].setClass(UserdataMetatable<Network, Object>()

        .addFunction("Connect", NetworkConnect())
        .addFunction("Disconnect", NetworkDisconnect())

        .addFunction("StartServer", &Network::StartServer)
        .addFunction("StopServer", &Network::StopServer)

        .addOverloadedFunctions("BroadcastMessage", 
            NetworkBroadcastMessage0(),
            NetworkBroadcastMessage1())

        .addOverloadedFunctions("BroadcastRemoteEvent", 
            NetworkBroadcastRemoteEvent0(),
            NetworkBroadcastRemoteEvent1(),
            NetworkBroadcastRemoteEvent2())

        .addFunction("SetUpdateFps", &Network::SetUpdateFps)
        .addFunction("SetSimulatedLatency", &Network::SetSimulatedLatency)
        .addFunction("SetSimulatedPacketLoss", &Network::SetSimulatedPacketLoss)

        .addFunction("RegisterRemoteEvent", &Network::RegisterRemoteEvent)
        .addFunction("UnregisterRemoteEvent", &Network::UnregisterRemoteEvent)
        .addFunction("UnregisterAllRemoteEvents", &Network::UnregisterAllRemoteEvents)
        
        .addFunction("SetPackageCacheDir", &Network::SetPackageCacheDir)
        .addFunction("SendPackageToClients", &Network::SendPackageToClients)

        .addFunction("MakeHttpRequest", NetworkMakeHttpRequest())

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
}

#endif
