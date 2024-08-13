#include <iostream>
#include <thread>
#include <windows.h>
using namespace std;

atomic<bool> stop(true);

//无限阳光
void sun(HANDLE 进程句柄) {
	while (true) {
		while (stop) {
			int 阳光;
			int 要修改的阳光 = 9999;
			ReadProcessMemory(进程句柄, (LPCVOID)0x006A9EC0, &阳光, sizeof(阳光), NULL);
			ReadProcessMemory(进程句柄, (LPCVOID)(阳光 + 0x768), &阳光, sizeof(阳光), NULL);
			WriteProcessMemory(进程句柄, (LPVOID)(阳光 + 0x5560), &要修改的阳光, sizeof(要修改的阳光), NULL);
			Sleep(500);
		}

	}
}
//植物无冷却
void plant(HANDLE 进程句柄, int i) {
	if (i == 2) {
		byte code[2] = { 0x7F,0x14 };
		WriteProcessMemory(进程句柄, (LPVOID)(0x00487296), code, sizeof(code), NULL);
	}
	else if (i == -2) {
		byte code[2] = { 0x7E,0x14 };
		WriteProcessMemory(进程句柄, (LPVOID)(0x00487296), code, sizeof(code), NULL);
	}

}
//食人花加速
void chomper(HANDLE 进程句柄, int i) {
	if (i == 3) {
		byte code[2] = { 0x74,0x5F };
		WriteProcessMemory(进程句柄, (LPVOID)(0x00461565), code, sizeof(code), NULL);
	}
	else if (i == -3) {
		byte code[2] = { 0x75,0x5F };
		WriteProcessMemory(进程句柄, (LPVOID)(0x00461565), code, sizeof(code), NULL);
	}

}
//金币999999
void gold(HANDLE 进程句柄, int i) {
	if (i == 4) {
		int 金币;
		int 要修改的金币 = 999999;
		ReadProcessMemory(进程句柄, (LPCVOID)0x006A9EC0, &金币, sizeof(金币), NULL);
		ReadProcessMemory(进程句柄, (LPCVOID)(金币 + 0x82C), &金币, sizeof(金币), NULL);
		WriteProcessMemory(进程句柄, (LPVOID)(金币 + 0x28), &要修改的金币, sizeof(要修改的金币), NULL);
	}

}

void main() {
	//006A9EC0+768+5560	"PlantsVsZombies.exe"+006A9EC0	
	HWND 窗口句柄 = ::FindWindow(NULL, L"植物大战僵尸中文版");
	DWORD pid;
	GetWindowThreadProcessId(窗口句柄, &pid);
	if (pid == NULL) {
		cout << "没有打开应用程序，辅助启动失败" << endl;
		return;
	}
	HANDLE 进程句柄 = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (进程句柄 == NULL) {
		cout << "没有打开应用程序，辅助启动失败" << endl;
		return;
	}
	int i;
	//创建一个无限阳光的线程
	thread threadsun;
	while (true) {
		cout << "-----------选择功能-----------" << endl;
		cout << "1.无限阳光(-1.关闭无限阳光)" << endl;
		cout << "2.植物无冷却(-2.关闭植物无冷却)" << endl;
		cout << "3.食人花加速(-3.关闭食人花加速)" << endl;
		cout << "4.金币999999" << endl;
		cout << "0.退出" << endl;
		cin >> i;
		if (i == 1) {
			cout << "无限阳光已开启" << endl;
			if (threadsun.joinable()) {
				stop = true;
				continue;
			}
			threadsun = thread(sun, 进程句柄);
			//WriteProcessMemory(进程句柄, (LPVOID)(阳光 + 0x5560), &要修改的阳光, sizeof(要修改的阳光), NULL);
		}
		else if (i == -1) {//关闭无限阳光
			cout << "无限阳光已关闭" << endl;
			stop = false;
		}
		else if (i == 2) {
			cout << "植物无冷却已开启" << endl;
			plant(进程句柄, i);
		}
		else if (i == -2) {
			cout << "植物无冷却已关闭" << endl;
			plant(进程句柄, i);
		}
		else if (i == 3) {
			cout << "食人花加速已开启" << endl;
			chomper(进程句柄, i);
		}
		else if (i == -3) {
			cout << "食人花加速已关闭" << endl;
			chomper(进程句柄, i);
		}
		else if (i == 4) {
			cout << "金币已设置为999999" << endl;
			gold(进程句柄, i);
		}
		else if (i == 0) {
			cout << "程序已经退出" << endl;
			break;
		}
		else {
			cout << "输入错误，无对应功能" << endl;
		}
	}
	CloseHandle(进程句柄);//使用完进程句柄要关闭
}