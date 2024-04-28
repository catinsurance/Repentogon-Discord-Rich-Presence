# Lua API Docs
This mod comes with a Lua API that allows you to create your own custom Rich Presence.

## Globals

- `_DISCORDRPC` - A simple `true` value denoting if the mod is active.
- `Activity` - A static class with functions that allow you to modify the default Activity, or create your own.
- `Timestamp` - A constructor for the Timestamp object.

## Enums

- `ActivityAssets` - An enumerator with every default image you can use for an Activity. [You can see the full list of enums here](https://github.com/catinsurance/Repentogon-Discord-Rich-Presence/blob/main/src/scripts/Enums.lua)

## Activity

The Activity class lets you create your own custom Activity (discord rich presence status), and also lets you integrate into the default Activity.

### SetLargeImage()
`Activity.SetLargeImage(string imagePath, string? caption): void`

Sets the large image in the Activity. `imagePath` should be either an `ActivityAssets` enumerator or a direct URL to an image.

Optionally, provide a caption to be displayed when the large image is hovered over. Omit to leave the caption unchanged, or set to an empty string to remove it.

### GetLargeImage()
`Activity.GetLargeImage(): string`

Gets the string path to the large image, or an empty string if there is none.

### SetSmallImage()
`Activity.SetSmallImage(string imagePath, string? caption): void`

Sets the small image in the Activity. `imagePath` should be either an `ActivityAssets` enumerator or a direct URL to an image.

Optionally, provide a caption to be displayed when the large image is hovered over. Omit to leave the caption unchanged, or set to `""` to remove it.

### GetSmallImage()
`Activity.GetSmallImage(): string`

Gets the string path to the small image, or an empty string if there is none.

### SetLargeCaption()
`Activity.SetLargeCaption(string caption): void`

Sets the caption to be displayed when hovering over the large image. Set to an empty string to remove the caption.

### GetLargeCaption()
`Activity.GetLargeCaption(): string`

Gets the caption that's displayed when hovering over the large image, or an empty string if there is none.

### SetSmallCaption()
`Activity.SetSmallCaption(string caption): void`

Sets the caption to be displayed when hovering over the small image. Set to an empty string to remove the caption.

### GetSmallCaption()
`Activity.GetSmallCaption(): string`

Gets the caption that's displayed when hovering over the small image, or an empty string if there is none.

### SetTitle()
`Activity.SetTitle(string title): void`

Sets the title text for the Activity, also known as the details. Set to an empty string to remove the title.

### GetTitle()
`Activity.GetTitle(): string`

Gets the title text for the Activity, also known as the details. Returns an empty string if there is no title.

### SetSubtitle()
`Activity.SetSubtitle(): void`

Sets the subtitle text for the Activity, also known as the state. Set to an empty string to remove the subtitle.

### GetSubtitle()
`Activity.GetSubtitle(): string`

Gets the subtitle text for the Activity, also known as the state. Returns an empty string if there is no subtitle.

### SetStartTimestamp():
`Activity.SetStartTimestamp(Timestamp timestamp): void`

Sets start timer (time elapsed) based on the provided Timestamp object. Clears the end timer (time left).

### GetStartTimestamp()
`Activity.GetStartTimestamp(): Timestamp?`

Returns a Timestamp object for the start timer (time elapsed). If there is no start timer, returns `nil`.

### SetEndTimestamp():
`Activity.SetEndTimestamp(Timestamp timestamp): void`

Sets end timer (time left) based on the provided Timestamp object. Clears the start timer (time elapsed).

### GetEndTimestamp()
`Activity.GetEndTimestamp(): Timestamp?`

Returns a Timestamp object for the end timer (time left). If there is no end timer, returns `nil`.

### ClearTimestamp()
`Activity.ClearTimestamp(): void`

Clears both the start timer (time elapsed) and end timer (time left).

### SetDefaultActivity()
`Activity.SetDefaultActivity(boolean disabled): void`

Provide `true` to disable the default activity. The activity will enable itself again after entering a new run or entering the main menu. If you are making a custom Activity and don't want your values overwritten, set this on run start.

### SetCharacterPortrait()
`Activity.SetCharacterPortrait(int playerType, string imagePath): void`

Sets the portrait of the given [PlayerType](https://wofsauge.github.io/IsaacDocs/rep/enums/PlayerType.html) to `imagePath`, which should be an `ActivityAssets` enumerator or a direct url to an image.

### Update()
`Activity.Update(): void`

Updates the activity immediately. The activity is also automatically updated when entering a new room or starting a new run.

## Timestamp

### Timestamp() (constructor)
`Timestamp(int? offsetSeconds): Timestamp`

Returns a timestamp object representing the seconds since the Unix epoch. You can optionally provide an integer offset to add to the timestamp, assumed to be seconds. For example, setting an offset of -10 will provide a timestamp starting from 10 seconds ago. Setting an offset of 20 will provide a timestamp starting 20 seconds in the future.

### Offset()
`Timestamp:Offset(int offsetSeconds): void`

Offsets the current timestamp by `offsetSeconds` seconds.