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
#include "../../Network/Connection.h"
#include "../../Scene/Scene.h"
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

    // [Class] RemoteEvent
    lua["RemoteEvent"].setClass(UserdataMetatable<RemoteEvent>()
        .addProperty("senderID", &RemoteEvent::senderID_)
        .addProperty("eventType", &RemoteEvent::eventType_)
        .addProperty("eventData", &RemoteEvent::eventData_)
        .addProperty("inOrder", &RemoteEvent::inOrder_)
        );

    // [Class] Connection : Object
    lua["Connection"].setClass(UserdataMetatable<Connection, Object>()

        .addOverloadedFunctions("SendMessage", 
            ConnectionSendMessage0(),
            ConnectionSendMessage1())

        .addOverloadedFunctions("SendRemoteEvent", 
            ConnectionSendRemoteEvent0(), 
            ConnectionSendRemoteEvent1())

        // [Method] void SetScene(Scene* newScene)
        .addFunction("SetScene", &Connection::SetScene)
        // [Method] void SetIdentity(const VariantMap& identity)
        .addFunction("SetIdentity", &Connection::SetIdentity)
        // [Method] void SetControls(const Controls& newControls)
        .addFunction("SetControls", &Connection::SetControls)
        // [Method] void SetPosition(const Vector3& position)
        .addFunction("SetPosition", &Connection::SetPosition)
        // [Method] void SetRotation(const Quaternion& rotation)
        .addFunction("SetRotation", &Connection::SetRotation)
        // [Method] void SetConnectPending(bool connectPending)
        .addFunction("SetConnectPending", &Connection::SetConnectPending)
        // [Method] void SetLogStatistics(bool enable)
        .addFunction("SetLogStatistics", &Connection::SetLogStatistics)

        // [Method] void Disconnect(int waitMSec = 0)
        .addFunction("Disconnect", ConnectionDisconnect())

        // [Method] VariantMap& GetIdentity()
        .addFunction("GetIdentity", &Connection::GetIdentity)
        // [Method] Scene* GetScene() const
        .addFunction("GetScene", &Connection::GetScene)
        // [Method] const Controls& GetControls() const
        .addFunction("GetControls", &Connection::GetControls)
        // [Method] unsigned char GetTimeStamp() const
        .addFunction("GetTimeStamp", &Connection::GetTimeStamp)
        // [Method] const Vector3& GetPosition() const
        .addFunction("GetPosition", &Connection::GetPosition)
        // [Method] const Quaternion& GetRotation() const
        .addFunction("GetRotation", &Connection::GetRotation)
        // [Method] bool IsClient() const
        .addFunction("IsClient", &Connection::IsClient)
        // [Method] bool IsConnected() const
        .addFunction("IsConnected", &Connection::IsConnected)
        // [Method] bool IsConnectPending() const
        .addFunction("IsConnectPending", &Connection::IsConnectPending)
        // [Method] bool IsSceneLoaded() const
        .addFunction("IsSceneLoaded", &Connection::IsSceneLoaded)
        // [Method] bool GetLogStatistics() const
        .addFunction("GetLogStatistics", &Connection::GetLogStatistics)
        // [Method] String GetAddress() const
        .addFunction("GetAddress", &Connection::GetAddress)
        // [Method] unsigned short GetPort() const
        .addFunction("GetPort", &Connection::GetPort)
        // [Method] float GetRoundTripTime() const
        .addFunction("GetRoundTripTime", &Connection::GetRoundTripTime)
        // [Method] float GetLastHeardTime() const
        .addFunction("GetLastHeardTime", &Connection::GetLastHeardTime)
        // [Method] float GetBytesInPerSec() const
        .addFunction("GetBytesInPerSec", &Connection::GetBytesInPerSec)
        // [Method] float GetBytesOutPerSec() const
        .addFunction("GetBytesOutPerSec", &Connection::GetBytesOutPerSec)
        // [Method] float GetPacketsInPerSec() const
        .addFunction("GetPacketsInPerSec", &Connection::GetPacketsInPerSec)
        // [Method] float GetPacketsOutPerSec() const
        .addFunction("GetPacketsOutPerSec", &Connection::GetPacketsOutPerSec)
        // [Method] String ToString() const
        .addFunction("ToString", &Connection::ToString)
        // [Method] unsigned GetNumDownloads() const
        .addFunction("GetNumDownloads", &Connection::GetNumDownloads)
        // [Method] const String& GetDownloadName() const
        .addFunction("GetDownloadName", &Connection::GetDownloadName)
        // [Method] float GetDownloadProgress() const
        .addFunction("GetDownloadProgress", &Connection::GetDownloadProgress)
        // [Method] void SendPackageToClient(PackageFile* package)
        .addFunction("SendPackageToClient", &Connection::SendPackageToClient)
        
        // [Property(ReadOnly)] VariantMap& identity
        .addProperty("identity", &Connection::GetIdentity)
        // [Property] Scene* scene
        .addProperty("scene", &Connection::GetScene, &Connection::SetScene)
        // [Property] const Controls& controls
        .addProperty("controls", &Connection::GetControls, &Connection::SetControls)
        // [Property(ReadOnly)] unsigned char timeStamp
        .addProperty("timeStamp", &Connection::GetTimeStamp)
        // [Property] const Vector3& position
        .addProperty("position", &Connection::GetPosition, &Connection::SetPosition)
        // [Property] const Quaternion& rotation
        .addProperty("rotation", &Connection::GetRotation, &Connection::SetRotation)
        // [Property(ReadOnly)] bool client
        .addProperty("client", &Connection::IsClient)
        // [Property(ReadOnly)] bool connected
        .addProperty("connected", &Connection::IsConnected)
        // [Property] bool connectPending
        .addProperty("connectPending", &Connection::IsConnectPending, &Connection::SetConnectPending)
        // [Property(ReadOnly)] bool sceneLoaded
        .addProperty("sceneLoaded", &Connection::IsSceneLoaded)
        // [Property] bool logStatistics
        .addProperty("logStatistics", &Connection::GetLogStatistics, &Connection::SetLogStatistics)
        // [Property(ReadOnly)] String address
        .addProperty("address", &Connection::GetAddress)
        // [Property(ReadOnly)] unsigned short port
        .addProperty("port", &Connection::GetPort)
        // [Property(ReadOnly)] float roundTripTime
        .addProperty("roundTripTime", &Connection::GetRoundTripTime)
        // [Property(ReadOnly)] float lastHeardTime
        .addProperty("lastHeardTime", &Connection::GetLastHeardTime)
        // [Property(ReadOnly)] float bytesInPerSec
        .addProperty("bytesInPerSec", &Connection::GetBytesInPerSec)
        // [Property(ReadOnly)] float bytesOutPerSec
        .addProperty("bytesOutPerSec", &Connection::GetBytesOutPerSec)
        // [Property(ReadOnly)] float packetsInPerSec
        .addProperty("packetsInPerSec", &Connection::GetPacketsInPerSec)
        // [Property(ReadOnly)] float packetsOutPerSec
        .addProperty("packetsOutPerSec", &Connection::GetPacketsOutPerSec)
        // [Property(ReadOnly)] unsigned numDownloads
        .addProperty("numDownloads", &Connection::GetNumDownloads)
        // [Property(ReadOnly)] const String& downloadName
        .addProperty("downloadName", &Connection::GetDownloadName)
        // [Property(ReadOnly)] float downloadProgress
        .addProperty("downloadProgress", &Connection::GetDownloadProgress)
        );
}
}

#endif
