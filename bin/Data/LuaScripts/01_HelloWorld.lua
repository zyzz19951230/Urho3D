-- This first example, maintaining tradition, prints a "Hello World" message.
-- Furthermore it shows:
--     - Using the Sample utility functions as a base for the application
--     - Adding a Text element to the graphical user interface
--     - Subscribing to and handling of update events

require "LuaScripts/Utilities/Sample"

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create "Hello World" Text
    CreateText()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)

    -- Finally, hook-up this HelloWorld instance to handle update events
    SubscribeToEvents()
end

function CreateText()
    -- Construct new Text object
    local helloText = Text:new()

    -- Set String to display
    helloText.text = "Hello World from Urho3D!"

    -- Set font and text color
    helloText:SetFont(cache:GetResource("Font", "Fonts/Anonymous Pro.ttf"), 30)
    helloText.color = Color(0.0, 1.0, 0.0)

    -- Align Text center-screen
    helloText.horizontalAlignment = HA_CENTER
    helloText.verticalAlignment = VA_CENTER

    -- Add Text instance to the UI root element
    ui.root:AddChild(helloText)
end

function SubscribeToEvents()
    -- Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate")
end

function HandleUpdate(eventType, eventData)
    -- Do nothing for now, could be extended to eg. animate the display
    
    -- TestKaguyaImage() -- result: no memory leak
    -- TestSolImage() -- result: no memory leak, can not work with shared ptr
    -- TestToluaImage() -- result: memory leak

    -- TestKaguyaVector3() -- fps: 36
    -- TestSolVector3() -- fps: 34
    -- TestToluaVector3() -- fps: 20
end

function TestKaguyaImage()
    local image = KImage.new()
    image:SetSize(1024, 1024, 4)
    image = nil
end

function TestSolImage()
    local image = SImage.new()
    image:SetSize(1024, 1024, 4)
    image = nil
end

function TestToluaImage()
    local image = Image:new()
    image:SetSize(1024, 1024, 4)
    image = nil
end

local COUNT = 10000

function TestKaguyaVector3()
    for i=1,COUNT do
        local a = KVector3.new(1, 2, 3)
        local b = KVector3.new(9, 8, 7)
        c = a * b
    end
    print(c.x, c.y, c.z)
end

function TestSolVector3()
    for i=1,COUNT do
        local a = SVector3.new(1, 2, 3)
        local b = SVector3.new(9, 8, 7)
        c = a * b
    end
    print(c.x, c.y, c.z)
end

function TestToluaVector3()
    for i=1,COUNT do
        local a = Vector3:new(1, 2, 3)
        local b = Vector3:new(9, 8, 7)
        c = a * b
    end
    print(c.x, c.y, c.z)
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "</patch>"
end
