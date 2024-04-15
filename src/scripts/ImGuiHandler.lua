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
        Description = "Show the timer denoting how long you've been on the menu/in a run. Requires restart when disabling for changes to take effect."
    }
}

function DiscordRichPresence_Set(category, name, value)
    DiscordRichPresenceConfig[category][name] = value
    ImGui.UpdateData(name, ImGuiData.Value, value)
end

-- Menu and tab setup
ImGui.CreateMenu("DiscordRPCMenu", "\u{f007} DiscordRPC")

ImGui.AddElement("DiscordRPCMenu", "ConfigMenuMenuItem", ImGuiElement.MenuItem, "\u{f013} Config")

-- Config menu
ImGui.CreateWindow("ConfigMenuWindow", "Discord RPC Config")
ImGui.LinkWindowToElement("ConfigMenuWindow", "DiscordRPCMenu")

-- Create buttons

local function makeBool(category, option)
    local info = settingInformation[option]
    ImGui.AddCheckbox("ConfigMenuWindow", option, info.Name, function (newValue)
        DiscordRichPresence_Set(category, option, newValue)
    end)

    ImGui.SetHelpmarker(option, info.Description)
end

ImGui.AddElement("ConfigMenuWindow", "", ImGuiElement.SeparatorText, "Customization")

makeBool("Customization", "ShowModdedCharacters")
makeBool("Customization", "ShowModdedStages")
makeBool("Customization", "ShowTimer")

ImGui.AddButton("ConfigMenuWindow", "SaveReloadButton", "Apply", function (clickCount)
    ---@diagnostic disable-next-line: undefined-global
    DiscordRichPresence_SaveAndReload()
    ImGui.PushNotification("DiscordRPC settings saved!")
end)