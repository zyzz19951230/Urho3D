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

#include "../../Network/Connection.h"
#include "../../LuaScript/LuaScriptUtils.h"

#include <kaguya.hpp>

namespace Urho3D
{

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(ConnectionSendMessage0, Connection, SendMessage, 4, 5, void(Connection::*)(int, bool, bool, const VectorBuffer&, unsigned));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(ConnectionSendMessage1, Connection, SendMessage, 5, 6, void(Connection::*)(int, bool, bool, const unsigned char*, unsigned, unsigned));

KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(ConnectionSendRemoteEvent0, Connection, SendRemoteEvent, 2, 3, void(Connection::*)(StringHash, bool, const VariantMap&));
KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(ConnectionSendRemoteEvent1, Connection, SendRemoteEvent, 3, 4, void(Connection::*)(Node*, StringHash, bool, const VariantMap&));

KAGUYA_MEMBER_FUNCTION_OVERLOADS(ConnectionDisconnect, Connection, Disconnect, 0, 1);

void RegisterConnection(kaguya::State& lua)
{
    using namespace kaguya;

    lua["RemoteEvent"].setClass(UserdataMetatable<RemoteEvent>()
        .addProperty("senderID", &RemoteEvent::senderID_)
        .addProperty("eventType", &RemoteEvent::eventType_)
        .addProperty("eventData", &RemoteEvent::eventData_)
        .addProperty("inOrder", &RemoteEvent::inOrder_)
        );

    lua["Connection"].setClass(UserdataMetatable<Connection, Object>()

        .addOverloadedFunctions("SendMessage", 
            ConnectionSendMessage0(),
            ConnectionSendMessage1())

        .addOverloadedFunctions("SendRemoteEvent", 
            ConnectionSendRemoteEvent0(), 
            ConnectionSendRemoteEvent1())

        .addFunction("SetScene", &Connection::SetScene)
        .addFunction("SetIdentity", &Connection::SetIdentity)
        .addFunction("SetControls", &Connection::SetControls)
        .addFunction("SetPosition", &Connection::SetPosition)
        .addFunction("SetRotation", &Connection::SetRotation)
        .addFunction("SetConnectPending", &Connection::SetConnectPending)
        .addFunction("SetLogStatistics", &Connection::SetLogStatistics)

        .addFunction("Disconnect", ConnectionDisconnect())

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
}

#endif
