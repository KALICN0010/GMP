// MidiGenshinMusicPlayer.cpp

/* 
This file uses the midifile library (https://github.com/craigsapp/midifile)
which is licensed under the MIT License. Please refer to the LICENSE file 
included with this project for more details.
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <shlobj.h>
#include <locale>
#include <codecvt>
#include <vector>
#include <thread>
#include <string>
#include <iomanip>
#include <bitset>

#include "MidiFile.h"
#include "Options.h"

using namespace std;
using namespace smf;

void sleep(int milliseconds) {
	chrono::milliseconds duration(milliseconds);
	this_thread::sleep_for(duration);
}
void sleep_us(long long int microseconds) {
	auto start = std::chrono::high_resolution_clock::now();
	auto end = start + std::chrono::microseconds(microseconds);

	while (std::chrono::high_resolution_clock::now() < end) {
		// 忙等，不做任何有意义的工作
	}
}
void print(string str, int ENDL = 1) {
	if (ENDL == 1) {
		cout << str << endl;
	}
	else {
		cout << str;
	}
}
void KeyPress(DWORD vkCode, bool keyDown) {
	INPUT input = {}; // 初始化INPUT结构体
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = vkCode; // 设置VK值

	if (keyDown) {
		// 按下键
		input.ki.dwFlags = 0;
	}
	else {
		// 释放键
		input.ki.dwFlags = KEYEVENTF_KEYUP;
	}

	// 发送输入事件，但忽略失败的情况
	SendInput(1, &input, sizeof(INPUT));
}
void KeyBoardAPI(string score, int upOrDown) {
	/*
	.1（即C下方八度）对应键号30
	.2（即D下方八度）对应键号32
	.3（即E下方八度）对应键号34
	.4（即F下方八度）对应键号35
	.5（即G下方八度）对应键号37
	.6（即A下方八度）对应键号39
	.7（即B下方八度）对应键号3B

	1（即C）对应键号3C
	2（即D）对应键号3E
	3（即E）对应键号40
	4（即F）对应键号41
	5（即G）对应键号43
	6（即A）对应键号45
	7（即B）对应键号47

	1.（即C上方八度）对应键号48
	2.（即D上方八度）对应键号4A
	3.（即E上方八度）对应键号4C
	4.（即F上方八度）对应键号4D
	5.（即G上方八度）对应键号4F
	6.（即A上方八度）对应键号51
	7.（即B上方八度）对应键号53
	*/
	if (score == "upAll") {//全部抬起
		KeyPress(0x5A, false);//Z
		KeyPress(0x58, false);//X
		KeyPress(0x43, false);//C
		KeyPress(0x56, false);//V
		KeyPress(0x42, false);//B
		KeyPress(0x4E, false);//N
		KeyPress(0x4D, false);//M

		KeyPress(0x41, false);//A
		KeyPress(0x53, false);//S
		KeyPress(0x44, false);//D
		KeyPress(0x46, false);//F
		KeyPress(0x47, false);//G
		KeyPress(0x48, false);//H
		KeyPress(0x4A, false);//J

		KeyPress(0x51, false);//Q
		KeyPress(0x57, false);//W
		KeyPress(0x45, false);//E
		KeyPress(0x52, false);//R
		KeyPress(0x54, false);//T
		KeyPress(0x59, false);//Y
		KeyPress(0x55, false);//U

	}
	//抬起
	if (upOrDown == 0) {
		if (score == "30")KeyPress(0x5A, false);//Z
		if (score == "32")KeyPress(0x58, false);//X
		if (score == "34")KeyPress(0x43, false);//C
		if (score == "35")KeyPress(0x56, false);//V
		if (score == "37")KeyPress(0x42, false);//B
		if (score == "39")KeyPress(0x4E, false);//N
		if (score == "3B")KeyPress(0x4D, false);//M

		if (score == "3C")KeyPress(0x41, false);//A
		if (score == "3E")KeyPress(0x53, false);//S
		if (score == "40")KeyPress(0x44, false);//D
		if (score == "41")KeyPress(0x46, false);//F
		if (score == "43")KeyPress(0x47, false);//G
		if (score == "45")KeyPress(0x48, false);//H
		if (score == "47")KeyPress(0x4A, false);//J

		if (score == "48")KeyPress(0x51, false);//Q
		if (score == "4A")KeyPress(0x57, false);//W
		if (score == "4C")KeyPress(0x45, false);//E
		if (score == "4D")KeyPress(0x52, false);//R
		if (score == "4F")KeyPress(0x54, false);//T
		if (score == "51")KeyPress(0x59, false);//Y
		if (score == "53")KeyPress(0x55, false);//U
	}
	//按下
	if (upOrDown == 1) {
		if (score == "30")KeyPress(0x5A, true);//Z
		if (score == "32")KeyPress(0x58, true);//X
		if (score == "34")KeyPress(0x43, true);//C
		if (score == "35")KeyPress(0x56, true);//V
		if (score == "37")KeyPress(0x42, true);//B
		if (score == "39")KeyPress(0x4E, true);//N
		if (score == "3B")KeyPress(0x4D, true);//M

		if (score == "3C")KeyPress(0x41, true);//A
		if (score == "3E")KeyPress(0x53, true);//S
		if (score == "40")KeyPress(0x44, true);//D
		if (score == "41")KeyPress(0x46, true);//F
		if (score == "43")KeyPress(0x47, true);//G
		if (score == "45")KeyPress(0x48, true);//H
		if (score == "47")KeyPress(0x4A, true);//J

		if (score == "48")KeyPress(0x51, true);//Q
		if (score == "4A")KeyPress(0x57, true);//W
		if (score == "4C")KeyPress(0x45, true);//E
		if (score == "4D")KeyPress(0x52, true);//R
		if (score == "4F")KeyPress(0x54, true);//T
		if (score == "51")KeyPress(0x59, true);//Y
		if (score == "53")KeyPress(0x55, true);//U
	}
}
//debug函数
void stopPoint() {
	cout << "[断点]输入任意字符以继续:";
	string stop;
	getline(cin, stop); // 使用getline读取完整的行
}
void cls() {
	system("cls");
}
void checkValueStopPoint(string value, string endl = "\n") {
	cls();
	if (endl == "\n") {
		print(value, 1);
	}
	else {
		print(value, 0);
	}
	stopPoint();
}




class CLASS_variableSet {
public:
	string MidiFIlesPaths = "";
	vector<string> MidiFIlesPathsList;
	vector<string> MidiFilesNamesList;
	int NowPlay = 0;//与 乐谱文件夹列表 对应
	int FilesShowNumber = 10;
	int FilesShowStartPlace = 0;//与 乐谱文件夹列表 对应
	int PlayerMode = 1;// 0 == 单次播放，1 == 单曲循环，2 == 目录循环
};
CLASS_variableSet   variableSet;

class CLASS_events {
public:
	int Run = 0;
	//操作信号
	int UpdateTheDisplay = 0;
	int ChoiceFold = 0;
	int playbackState = 0;//0==暂停，1==播放
	int PreviousTrack = 0;
	int NextTrack = 0;
	int UpKeybd = 0;
	//错误信息
	string Error = "";
};
CLASS_events events;

class CLASS_functionSet {
public:

	int listenKeybd(int key) {
		int value;
		value = GetKeyState(key);
		if ((value != 0) and (value != 1))return 1;
		else return 0;
	}

	int choiceFold(HWND ownerWindow) {
		vector<string> mucFilePaths;
		vector<string> mucFileNames;

		wchar_t tempPath[MAX_PATH] = { 0 };
		BROWSEINFO bi = { 0 };
		LPITEMIDLIST pidl = NULL;
		WIN32_FIND_DATA findData;

		bi.hwndOwner = ownerWindow;
		bi.pszDisplayName = tempPath;
		bi.lpszTitle = L"请选择包含乐谱的文件夹(.mid文件)";
		bi.ulFlags = BIF_RETURNONLYFSDIRS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;

		pidl = SHBrowseForFolder(&bi);
		if (pidl != NULL) {
			if (SHGetPathFromIDList(pidl, tempPath)) {
				IMalloc* imalloc = NULL;
				if (SUCCEEDED(SHGetMalloc(&imalloc))) {
					imalloc->Free(pidl);
					imalloc->Release();
				}

				wstring wFolderPath = tempPath;
				string foldPath = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(wFolderPath);
				wstring searchPattern = wFolderPath + L"\\*.mid";
				HANDLE hFind = FindFirstFile(searchPattern.c_str(), &findData);
				if (hFind != INVALID_HANDLE_VALUE) {
					do {
						if (wcscmp(findData.cFileName, L".") != 0 && wcscmp(findData.cFileName, L"..") != 0) {
							wstring filePath = wFolderPath + L'\\' + findData.cFileName;
							wstring_convert<codecvt_utf8<wchar_t>> converter;
							//wstring_convert<wchar_t> converter;
							mucFilePaths.push_back(converter.to_bytes(filePath));

						}
					} while (FindNextFile(hFind, &findData) != 0);
					FindClose(hFind);

					// 找到了至少一个.muc文件，将它们的路径添加到变量集的列表中
					variableSet.MidiFIlesPathsList = mucFilePaths;
					variableSet.MidiFIlesPaths = foldPath;
					int i = 0;
					while (i < mucFilePaths.size()) {
						vector<string> j = split_path(mucFilePaths[i]);
						for (int k = 0; k < j.size(); k++) {
							if (k == (j.size() - 1)) {
								mucFileNames.push_back(j[k]);
							}
						}
						i++;
					}
					variableSet.MidiFilesNamesList = mucFileNames;
				}
				else {
					// 没有找到.muc文件的处理逻辑
					events.Error = "[文件处理][乐谱文件夹选择]选择的文件夹中没有.mid文件";
				}
			}
		}
		return 0;
	}

	vector<string> split_path(const string& path) {
		vector<string> tokens;
		size_t start = 0;
		size_t end = path.find_first_of("/\\");

		while (end != string::npos) {
			tokens.push_back(path.substr(start, end - start));
			start = end + 1;
			end = path.find_first_of("/\\", start);
		}

		// 添加路径的最后一部分
		tokens.push_back(path.substr(start));

		return tokens;
	}

	void cleanTheDisplay() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD dwConSize;

		if (hConsole == INVALID_HANDLE_VALUE) return;

		if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
		if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, { 0,0 }, &dwConSize)) return;
		if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, { 0,0 }, &dwConSize)) return;
		SetConsoleCursorPosition(hConsole, { 0,0 });
	}
};
CLASS_functionSet   functionSet;

void eventCenter() {
	/*按键检测
	 F6_0x75_乐谱文件夹选择
	 F7_0x76_上一曲
	 F8_0x77_播放/暂停
	 F9_0x78_下一曲
	 F10_0x79_播放模式切换 0==单次播放，1==单曲循环，2 == 目录循环
	*/
	events.UpdateTheDisplay = 1;
	while (events.Run == 1) {
		//键盘监听部分

		//F6 文件夹选择
		if (functionSet.listenKeybd(0x75) == 1) {
			events.ChoiceFold = 1;
			sleep(200);
		}
		//F7 上一曲
		if (functionSet.listenKeybd(0x76) == 1) {
			if (variableSet.NowPlay > 0) {
				//暂停时按下上一曲的情况
				if (events.playbackState == 0) {
					events.PreviousTrack = 1;//用于通知播放循环退出
					variableSet.NowPlay -= 1;//选择上一曲
					events.UpdateTheDisplay = 1;
					sleep(200);
				}
				//正在播放时按下上一曲的情况
				else {
					events.playbackState = 0;//暂停
					events.PreviousTrack = 1;//用于通知播放循环退出
					variableSet.NowPlay -= 1;//选择上一曲
					events.playbackState = 1;//播放
					events.UpdateTheDisplay = 1;
					sleep(200);
				}
			}
		}
		//F8 播放/暂停
		if (functionSet.listenKeybd(0x77) == 1) {
			if (events.playbackState == 0) {
				events.UpKeybd = 0;
				events.playbackState = 1;
				events.UpdateTheDisplay = 1;
				sleep(200);
			}
			else {
				events.playbackState = 0;
				events.UpdateTheDisplay = 1;
				sleep(200);
			}
		}
		//F9 下一曲
		if (functionSet.listenKeybd(0x78) == 1) {
			if (variableSet.NowPlay < (variableSet.MidiFIlesPathsList.size() - 1)) {
				//暂停时按下下一曲的情况
				if (events.playbackState == 0) {
					events.NextTrack = 1;//用于通知播放循环退出
					variableSet.NowPlay += 1;//选择下一曲
					events.UpdateTheDisplay = 1;
					sleep(200);
				}
				//正在播放时按下一曲的情况
				else {
					events.playbackState = 0;//暂停
					events.NextTrack = 1;//用于通知播放循环退出
					variableSet.NowPlay += 1;//选择下一曲
					events.playbackState = 1;//播放

					events.UpdateTheDisplay = 1;
					sleep(200);
				}
			}
		}

		//F10 播放模式
		if (functionSet.listenKeybd(0x79) == 1) {
			while (1 == 1) {
				if (variableSet.PlayerMode == 2) {
					variableSet.PlayerMode = 0;
					events.UpdateTheDisplay = 1;
					sleep(200);
					break;
				}
				if (variableSet.PlayerMode == 1) {
					variableSet.PlayerMode = 2;
					events.UpdateTheDisplay = 1;
					sleep(200);
					break;
				}
				if (variableSet.PlayerMode == 0) {
					variableSet.PlayerMode = 1;
					events.UpdateTheDisplay = 1;
					sleep(200);
					break;
				}
			}
		}
		//up   向上滑动乐谱列表
		if (functionSet.listenKeybd(VK_UP) == 1) {
			variableSet.FilesShowStartPlace += 1;
			events.UpdateTheDisplay = 1;
			sleep(200);
		}
		//down 向下滑动乐谱列表
		if (functionSet.listenKeybd(VK_DOWN) == 1) {
			if (variableSet.FilesShowStartPlace > 0) {
				variableSet.FilesShowStartPlace -= 1;
				events.UpdateTheDisplay = 1;
				sleep(200);
			}
		}
		//right 增加乐谱显示数量
		if (functionSet.listenKeybd(VK_RIGHT) == 1) {
			if (variableSet.FilesShowNumber < 50) {
				variableSet.FilesShowNumber += 1;
				events.UpdateTheDisplay = 1;
				sleep(200);
			}
		}
		//left 减少乐谱显示数量
		if (functionSet.listenKeybd(VK_LEFT) == 1) {
			if (variableSet.FilesShowNumber > 1) {
				variableSet.FilesShowNumber -= 1;
				events.UpdateTheDisplay = 1;
				sleep(200);
			}
		}
	}
}

void choiceFold() {
	while (events.Run == 1) {
		if (events.ChoiceFold == 1) {
			events.ChoiceFold = 0;
			functionSet.choiceFold(NULL);
			events.UpdateTheDisplay = 1;
		}
	}
}

void GUI() {
	while (events.Run == 1) {

		if (events.UpdateTheDisplay == 1) {
			events.UpdateTheDisplay = 0;

			// Function set. Clear screen();
			system("cls");

			print("F6: Select music folder, F7: Previous track, F8: Play/Pause, F9: Next track");
			print("Up: Scroll up, Down: Scroll down, Left: Decrease display count, Right: Increase display count, Display count: " + to_string(variableSet.FilesShowNumber));
			print("Music folder path: " + variableSet.MidiFIlesPaths);

			if (variableSet.MidiFilesNamesList.size() != 0) {
				if (variableSet.PlayerMode == 0) {
					print("Current track: [Single Play][" + variableSet.MidiFilesNamesList[variableSet.NowPlay] + "]");
				}
				if (variableSet.PlayerMode == 1) {
					print("Current track: [Track Loop][" + variableSet.MidiFilesNamesList[variableSet.NowPlay] + "]");
				}
				if (variableSet.PlayerMode == 2) {
					print("Current track: [Folder Loop][" + variableSet.MidiFilesNamesList[variableSet.NowPlay] + "]");
				}
			}
			else {
				print("Current track: None");
			}

			if (events.playbackState == 0) {
				print("Status: Paused");
			}
			if (events.playbackState == 1) {
				print("Status: Playing");
			}

			print("Track list:");

			if (variableSet.MidiFilesNamesList.size() > 0) {

				int i = variableSet.FilesShowStartPlace; int n = 0;
				while ((i < variableSet.MidiFilesNamesList.size()) && (n < variableSet.FilesShowNumber)) {
					if (i == variableSet.NowPlay) {
						print(to_string(i + 1) + " [ " + variableSet.MidiFilesNamesList[i] + " ]");
					}
					else {
						print(to_string(i + 1) + "   " + variableSet.MidiFilesNamesList[i]);
					}
					i++; n++;
				}
			}
		}
	}
}

void Player(int ARGC, char** ARGV) {
	while (events.Run == 1) {

		if ((events.playbackState == 1) and (variableSet.MidiFIlesPathsList.size() != 0)) {

			

			vector<vector<string>> MidiEvents;
			vector<vector<string>> MidiScoreEvents;
			vector<vector<vector<string>>> MachineCode;
			long long int US_Tick;

			Options options;
			options.process(ARGC, ARGV);
			MidiFile midifile;
			if (options.getArgCount() > 0) midifile.read(options.getArg(1));
			else midifile.read(variableSet.MidiFIlesPathsList[variableSet.NowPlay]);

			US_Tick = ((midifile.getTimeInSeconds(1)) * 1000000);

			midifile.joinTracks();
			// midifile.getTrackCount() will now return "1", but original
			// track assignments can be seen in .track field of MidiEvent.
			MidiEvent* mev;
			int deltatick;
			for (long long int event = 0; event < midifile[0].size(); event++) {
				mev = &midifile[0][event];
				if (event == 0) deltatick = mev->tick;
				else deltatick = mev->tick - midifile[0][event - 1].tick;

				// 创建一行数据来存储tick和MIDI消息
				vector<string> row;
				row.push_back(to_string(mev->tick)); // 将tick转化为字符串

				//print(to_string(mev->tick)+",", 0);

				// 将MIDI消息转化为十六进制字符串
				stringstream hexMessage;
				for (long long int i = 0; i < mev->size(); i++) {
					if (i > 0) hexMessage << ' ';
					hexMessage << hex << uppercase << setw(2) << setfill('0') << (int)(*mev)[i];
				}
				row.push_back(hexMessage.str());

				//print(hexMessage.str());

				// 将这一行数据添加到MidiEvents中
				MidiEvents.push_back(row);
			}

			
			//提取音符操作
			for (long long int i = 0; i < MidiEvents.size(); i++) {
				if ((MidiEvents[i][1][0] == '9') and (MidiEvents[i][1][1] == '0')) {
					string us_tick = to_string((stoll(MidiEvents[i][0]) * US_Tick));
					string score; score = MidiEvents[i][1][3]; score += MidiEvents[i][1][4];

					//提取可用的音符操作（21个音）
					/*
					.1（即C下方八度）对应键号30
					.2（即D下方八度）对应键号32
					.3（即E下方八度）对应键号34
					.4（即F下方八度）对应键号35
					.5（即G下方八度）对应键号37
					.6（即A下方八度）对应键号39
					.7（即B下方八度）对应键号3B

					1（即C）对应键号3C
					2（即D）对应键号3E
					3（即E）对应键号40
					4（即F）对应键号41
					5（即G）对应键号43
					6（即A）对应键号45
					7（即B）对应键号47

					1.（即C上方八度）对应键号48
					2.（即D上方八度）对应键号4A
					3.（即E上方八度）对应键号4C
					4.（即F上方八度）对应键号4D
					5.（即G上方八度）对应键号4F
					6.（即A上方八度）对应键号51
					7.（即B上方八度）对应键号53
					*/

					int isUsefulScore = 0;
					vector<string> usefulScore = {
						"30","32","34","35","37","39","3B",
						"3C","3E","40","41","43","45","47",
						"48","4A","4C","4D","4F","51","53"
					};
					long long int j = 0;
					while (j < usefulScore.size()) {
						if (score == usefulScore[j])isUsefulScore = 1;
						j++;
					}

					if (isUsefulScore == 1) {
						string scoreEvevt; scoreEvevt = MidiEvents[i][1][6]; scoreEvevt += MidiEvents[i][1][7];
						vector<string> aEvent;
						if (stoi(scoreEvevt) > 0) {
							aEvent.push_back(us_tick); aEvent.push_back("open");  aEvent.push_back(score);
						}
						if (stoi(scoreEvevt) == 0) {
							aEvent.push_back(us_tick); aEvent.push_back("close"); aEvent.push_back(score);
						}

						MidiScoreEvents.push_back(aEvent);
						//print(MidiEvents[i][0] + " " + MidiEvents[i][1] + " => " + aEvent[0] + " " + aEvent[1] + " " + aEvent[2]);
					}
				}
			}

			//合并相同时间戳的音符项
			long long int i = 0;
			while (i < (MidiScoreEvents.size())) {
				vector<vector<string>> sameTimeScores;
				string sleepTime;

				long long int startPoint = i;
				if (i == 0){
					sleepTime = MidiScoreEvents[i][0];
				}
				else {
					sleepTime = to_string(stoll(MidiScoreEvents[i][0]) - stoll(MidiScoreEvents[i - 1][0]));
				}


				while (i < (MidiScoreEvents.size())) {
					if (MidiScoreEvents[i][0] != MidiScoreEvents[startPoint][0]) {
						break;
					}
					else {
						vector<string> event; event.push_back(sleepTime); event.push_back(MidiScoreEvents[i][1]); event.push_back(MidiScoreEvents[i][2]);

						sameTimeScores.push_back(event);
					}
					i++;
				}
				MachineCode.push_back(sameTimeScores);
			}
			////检查
			/*
			cls();
			print("{");
			for (long long int i = 0; i < MachineCode.size(); i++) {
				print("    {");
				for (long long int j = 0; j < MachineCode[i].size(); j++) {
					if (j < MachineCode[i].size()-1) {
						print("        {" + MachineCode[i][j][0] + "," + MachineCode[i][j][1] + "," + MachineCode[i][j][2] + "},");
					}
					else {
						print("        {" + MachineCode[i][j][0] + "," + MachineCode[i][j][1] + "," + MachineCode[i][j][2] + "}");
					}
					
				}
				if (i < MachineCode.size() - 1) {
					print("    },");
				}
				else {
					print("    }");
				}
				
			}
			print("}");
			stopPoint();
			*/
			


			//播放
			int breakLoop = 0;
			do {
				

				long long int i = 0;
				while ((i < MachineCode.size())and(breakLoop == 0)) {
					auto start = std::chrono::high_resolution_clock::now();// 获取开始时间点

					for (long long int j = 0; ((j < MachineCode[i].size())and(breakLoop == 0)); j++) {
						//上一曲
						if (events.PreviousTrack == 1) {

							KeyBoardAPI("upAll", 0);//抬起
							breakLoop = 1;
							break;
						}
						//下一曲
						if (events.NextTrack == 1) {
							KeyBoardAPI("upAll", 0);//抬起
							breakLoop = 1;
							break;
						}
						//暂停
						if (events.playbackState == 0) {
							if (events.UpKeybd == 0) {
								KeyBoardAPI("upAll", 0);//抬起
								events.UpKeybd = 1;
							}
							sleep(100);//防止造成系统卡顿
							continue;
						}

						if(MachineCode[i][j][1] == "open") {
							KeyBoardAPI(MachineCode[i][j][2],1);
						}
						if (MachineCode[i][j][1] == "close") {
							KeyBoardAPI(MachineCode[i][j][2], 0);
						}
					}
					i++;
					auto end = std::chrono::high_resolution_clock::now();
					//计算时间差，并转换为us,将毫秒值存储为 long long int 类型,补偿后进行sleep_us
					sleep_us(stoll(MachineCode[i-1][0][0]) - (static_cast<long long int>((std::chrono::duration_cast<std::chrono::microseconds>(end - start)).count())));

				}
				if (variableSet.PlayerMode == 0) {
					events.playbackState = 0;//防止再进入循环
					events.UpdateTheDisplay = 1;
					breakLoop = 1;
					break;
				}
			} while ((variableSet.PlayerMode == 1) and (breakLoop == 0));
			if ((variableSet.PlayerMode == 2) and (events.PreviousTrack == 0) and (events.NextTrack == 0)) {
				if (variableSet.NowPlay < (variableSet.MidiFIlesPathsList.size() - 1)) {
					variableSet.NowPlay += 1;
					events.UpdateTheDisplay = 1;
					continue;
				}
				if (variableSet.NowPlay == (variableSet.MidiFIlesPathsList.size() - 1)) {
					variableSet.NowPlay = 0;
					events.UpdateTheDisplay = 1;
					continue;
				}
			}
			if (events.PreviousTrack == 1)events.PreviousTrack = 0;
			if (events.NextTrack == 1)events.NextTrack = 0;

		}
	}
}

int main(int argc, char** argv) {
	events.Run = 1;

	thread threadEventCenter(eventCenter);
	thread threadChoiceFold(choiceFold);
	thread threadGUI(GUI);
	thread threadPlayer(Player, argc, argv);

	threadEventCenter.join();
	threadChoiceFold.join();
	threadGUI.join();
	threadPlayer.join();

	return 0;
}
