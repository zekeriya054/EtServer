#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 
#endif  
#pragma region Includes

#include <winsock2.h>
#include <ws2tcpip.h>
#include <userenv.h>
#include <iostream>
#include <locale.h>
#include <wchar.h>
#pragma comment(lib, "advapi32.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma endregion

struct addrinfo *result = NULL, *ptr = NULL, hints;
WSADATA wsaData;
int iResult;
char mesaj[255];


int main() {
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	FreeConsole();
	setlocale(LC_ALL, "tr_TR.utf8");
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	//socket ayarlama
	SOCKADDR_IN addr;
	int adrlen = sizeof(addr);
	addr.sin_addr.s_addr = INADDR_ANY;//inet_addr("127.0.0.1");
	addr.sin_port = htons(5461);
	addr.sin_family = AF_INET;

	//socket dinleme
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR *)&addr, sizeof(addr));

	listen(sListen, 1);

	SOCKET newConnection;

	for (;;) {
		newConnection = accept(sListen, (SOCKADDR *)&addr, &adrlen);
		if (newConnection == 0) printf("Client baðlantýsý hatalý\n");

		else {
			//printf("Client baðlantýsý baþarýlý..\n");
		
			recv(newConnection, mesaj, sizeof(mesaj), 0);

			//printf("%s\n", mesaj);
			if (mesaj[0]=='k')
			{
				//system("Rundll32.exe User32.dll, LockWorkStation");
				//printf("%s\n", mesaj);
				LockWorkStation();
				//printf("%s\n", mesaj);
			}
			else if (mesaj[0] == 'o') {

				//system("Shutdown.exe /l");
				ExitWindowsEx(EWX_LOGOFF, 0);

			}
			else if (mesaj[0] == 'K') {
				WinExec("Shutdown.exe /p", SW_HIDE);
				/*
				ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
					SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
					SHTDN_REASON_MINOR_UPGRADE |
					SHTDN_REASON_FLAG_PLANNED);
*/
			}

			memset(mesaj, NULL, sizeof(mesaj));
			//CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ClientHandlerThread,(LPVOID)(newConnection),NULL,NULL);
		}

	}
	//system("pause");
	return 0;
}