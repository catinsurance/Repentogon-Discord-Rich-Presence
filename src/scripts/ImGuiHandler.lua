-- can't use enums since this loads before mainex.lua

_G.DiscordRichPresenceConfig = {
    Customization = {
        ShowModdedCharacters = false,
        ShowModdedStages = false,
        ShowTimer = true,
    }
}

local settingInformation = {
    ShowModdedCharacters = {
        Name = "Show Modded Characters",
        Description = "Show modded character names. Portraits will only show for supported characters."
    },

    ShowModdedStages = {
        Name = "Show Modded Stages",
        Description = "Shows the name of StageAPI stages in a generic title. Custom titles will show only for supported stages."
    },

    ShowTimer = {
        Name = "Show Timer",
        Description = "Show the timer denoting how long you've been on the menu/in a run. Requires restart after applying for changes to take effect."
    }
}

function DiscordRichPresence_Set(category, name, value)
    DiscordRichPresenceConfig[category][name] = value
    ImGui.UpdateData(name, ImGuiData.Value, value)
end

-- Menu and tab setup
ImGui.CreateMenu("DiscordRPCMenu", "\u{f007} DiscordRPC")

ImGui.AddElement("DiscordRPCMenu", "ConfigMenuMenuItem", 2, "\u{f013} Config") -- ImGuiElement.MenuItem

-- Config menu
ImGui.CreateWindow("ConfigMenuWindow", "Discord RPC Config")
ImGui.LinkWindowToElement("ConfigMenuWindow", "DiscordRPCMenu")

-- Create buttons

for category, options in pairs(DiscordRichPresenceConfig) do
    ImGui.AddElement("ConfigMenuWindow", "", 7, category) -- ImGuiElement.SeparatorText

    for option, value in pairs(options) do
        if type(value) == "boolean" then
            local info = settingInformation[option]
            ImGui.AddCheckbox("ConfigMenuWindow", option, info.Name, function (newValue)
                DiscordRichPresence_Set(category, option, newValue)
            end)

            ImGui.SetHelpmarker(option, info.Description)
        end
    end

    ImGui.AddButton("ConfigMenuWindow", "SaveReloadButton", "Apply", function (clickCount)
        DiscordRichPresence_SaveAndReload()
        ImGui.PushNotification("DiscordRPC settings saved!")
    end)
end