#include <iostream>
#include <thread>
#include <windows.h>
using namespace std;

atomic<bool> stop(true);

//��������
void sun(HANDLE ���̾��) {
	while (true) {
		while (stop) {
			int ����;
			int Ҫ�޸ĵ����� = 9999;
			ReadProcessMemory(���̾��, (LPCVOID)0x006A9EC0, &����, sizeof(����), NULL);
			ReadProcessMemory(���̾��, (LPCVOID)(���� + 0x768), &����, sizeof(����), NULL);
			WriteProcessMemory(���̾��, (LPVOID)(���� + 0x5560), &Ҫ�޸ĵ�����, sizeof(Ҫ�޸ĵ�����), NULL);
			Sleep(500);
		}

	}
}
//ֲ������ȴ
void plant(HANDLE ���̾��, int i) {
	if (i == 2) {
		byte code[2] = { 0x7F,0x14 };
		WriteProcessMemory(���̾��, (LPVOID)(0x00487296), code, sizeof(code), NULL);
	}
	else if (i == -2) {
		byte code[2] = { 0x7E,0x14 };
		WriteProcessMemory(���̾��, (LPVOID)(0x00487296), code, sizeof(code), NULL);
	}

}
//ʳ�˻�����
void chomper(HANDLE ���̾��, int i) {
	if (i == 3) {
		byte code[2] = { 0x74,0x5F };
		WriteProcessMemory(���̾��, (LPVOID)(0x00461565), code, sizeof(code), NULL);
	}
	else if (i == -3) {
		byte code[2] = { 0x75,0x5F };
		WriteProcessMemory(���̾��, (LPVOID)(0x00461565), code, sizeof(code), NULL);
	}

}
//���999999
void gold(HANDLE ���̾��, int i) {
	if (i == 4) {
		int ���;
		int Ҫ�޸ĵĽ�� = 999999;
		ReadProcessMemory(���̾��, (LPCVOID)0x006A9EC0, &���, sizeof(���), NULL);
		ReadProcessMemory(���̾��, (LPCVOID)(��� + 0x82C), &���, sizeof(���), NULL);
		WriteProcessMemory(���̾��, (LPVOID)(��� + 0x28), &Ҫ�޸ĵĽ��, sizeof(Ҫ�޸ĵĽ��), NULL);
	}

}

void main() {
	//006A9EC0+768+5560	"PlantsVsZombies.exe"+006A9EC0	
	HWND ���ھ�� = ::FindWindow(NULL, L"ֲ���ս��ʬ���İ�");
	DWORD pid;
	GetWindowThreadProcessId(���ھ��, &pid);
	if (pid == NULL) {
		cout << "û�д�Ӧ�ó��򣬸�������ʧ��" << endl;
		return;
	}
	HANDLE ���̾�� = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (���̾�� == NULL) {
		cout << "û�д�Ӧ�ó��򣬸�������ʧ��" << endl;
		return;
	}
	int i;
	//����һ������������߳�
	thread threadsun;
	while (true) {
		cout << "-----------ѡ����-----------" << endl;
		cout << "1.��������(-1.�ر���������)" << endl;
		cout << "2.ֲ������ȴ(-2.�ر�ֲ������ȴ)" << endl;
		cout << "3.ʳ�˻�����(-3.�ر�ʳ�˻�����)" << endl;
		cout << "4.���999999" << endl;
		cout << "0.�˳�" << endl;
		cin >> i;
		if (i == 1) {
			cout << "���������ѿ���" << endl;
			if (threadsun.joinable()) {
				stop = true;
				continue;
			}
			threadsun = thread(sun, ���̾��);
			//WriteProcessMemory(���̾��, (LPVOID)(���� + 0x5560), &Ҫ�޸ĵ�����, sizeof(Ҫ�޸ĵ�����), NULL);
		}
		else if (i == -1) {//�ر���������
			cout << "���������ѹر�" << endl;
			stop = false;
		}
		else if (i == 2) {
			cout << "ֲ������ȴ�ѿ���" << endl;
			plant(���̾��, i);
		}
		else if (i == -2) {
			cout << "ֲ������ȴ�ѹر�" << endl;
			plant(���̾��, i);
		}
		else if (i == 3) {
			cout << "ʳ�˻������ѿ���" << endl;
			chomper(���̾��, i);
		}
		else if (i == -3) {
			cout << "ʳ�˻������ѹر�" << endl;
			chomper(���̾��, i);
		}
		else if (i == 4) {
			cout << "���������Ϊ999999" << endl;
			gold(���̾��, i);
		}
		else if (i == 0) {
			cout << "�����Ѿ��˳�" << endl;
			break;
		}
		else {
			cout << "��������޶�Ӧ����" << endl;
		}
	}
	CloseHandle(���̾��);//ʹ������̾��Ҫ�ر�
}