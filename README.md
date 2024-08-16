# MidiGenshinMusicPlayer
![输入图片说明](README_Photos/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-08-17%20013542.png)
# Operation Guide
## Key Operations List
### Playback Status
#### Press F8 to toggle between Pause and Play
### Switching Tracks
#### Press F7 to play the previous track
#### Press F9 to play the next track
### Playback Mode
#### Press F10 to switch playback mode:
#### Single Play: Stops after each playback.
#### Track Loop: Loops the current track.
#### Folder Loop: Loops all tracks in the folder.
### Display Settings
#### Press [↑] Up Arrow Key to increase the number of tracks displayed.
#### Press [↓] Down Arrow Key to decrease the number of tracks displayed.
#### Press [←] Left Arrow Key to decrease the current display list of tracks.
#### Press [→] Right Arrow Key to increase the current display list of tracks.
## Command Line Interface
#### Interface Display
#### The program displays the path of the current music folder, the name of the current track, the playback status (Playing/Paused), and the current list of tracks.
#### The interface updates the display state when the playback status changes.
## Usage Instructions
### Preparation Before Playing:
#### Right-click the program
#### Run MidiGenshinMusicPlayer.exe as "Administrator"
#### After launching the program, press F6 to select the folder containing the MIDI files; once selected, the program will list all the MIDI files available for automatic playback. By default, the first .mid file will be marked with "[]" as the "Current Track."
#### Starting Playback:
#### Use F7 or F9 to select a MIDI file
#### Click on the Genshin Impact window to ensure that the Windows focus is on the Genshin Impact game window
#### In Genshin Impact, use the musical instrument you wish to play the track with, such as "Wind-Borne Lyre," "Old Lyre," "Flower Mirror Lyre," "Evening Wind Horn," etc.
#### Press F8 to start playing the current track.
#### //During playback, you can press F8 again to toggle between pause and play states.
#### //In [Single Play] mode, after stopping playback, you need to press F8 twice to re-enter play state (this bug is pending fix).
#### //In [Single Play] mode, the program defaults to pause after playing ends.
## Notes
#### The path of the MIDI files and the filenames must not contain Chinese characters, otherwise it may cause garbled display and program crashes (when attempting to play a garbled filename .mid file or playing any .mid file in a path containing Chinese).
#### The program needs to be run with administrator privileges to correctly capture keyboard events.
#### Keep Genshin Impact running in the foreground during playback to simulate instrument playing actions correctly.
#### If the released version does not work, download the source code locally and compile it using Visual Studio 2022.
#### Compilation settings are as follows:
![输入图片说明](README_Photos/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-07-22%20112814.png)
#### Please refer to the screenshots for the Additional Include Directories configuration. Modify the path to the include folder according to its actual location.
![include文件夹的路径可能需要手动修改](README_Photos/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-07-22%20112849.png)
![res文件夹内的文件如果没有自动导入的话就在资源文件那里手动导入现有项](README_Photos/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-07-22%20113423.png)
#### If resources in the res folder do not import automatically, manually add them under the Resources section.
#### The released version may not work on all versions of Windows.
#### If antivirus software flags the program as malicious, add it to the trusted list. This is normal due to the use of Windows API calls in the code.
## Editing Music Sheets
#### Tips for Editing MIDI Files
#### It's best to convert downloaded MIDI files to the key of C major using MuseScore.
![输入图片说明](README_Photos/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-07-22%20115231.png)
![输入图片说明](README_Photos/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-07-22%20115245.png)
![输入图片说明](README_Photos/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-07-22%20115256.png)
#### Afterwards, make appropriate adjustments. Any sharp or flat notes and notes outside the range of the 21 notes on the Genshin Impact harp will be ignored.
![输入图片说明](README_Photos/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-07-22%20115015.png)
## writer:
[XianRenJESSE in https://gitee.com/xr_jesse](https://gitee.com/xr_jesse)
