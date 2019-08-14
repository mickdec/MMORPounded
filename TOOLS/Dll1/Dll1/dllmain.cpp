// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#include "pch.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "detours.h"
#include <cstdio>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "detours.lib")
#pragma comment(lib, "ws2_32.lib")


int (WINAPI* dconnect)(SOCKET, const struct sockaddr*, int) = connect;
int WINAPI myconnect(SOCKET s, const struct sockaddr* name, int namelen);

int (WINAPI* drecv)(SOCKET, char*, int, int) = recv;
int WINAPI myrecv(SOCKET s, char* buf, int len, int flags);

int (WINAPI* dsend)(SOCKET, const char*, int, int) = send;
int WINAPI mysend(SOCKET s, const char* buf, int len, int flags);

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	AllocConsole();

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)dconnect, myconnect);
		DetourAttach(&(PVOID&)drecv, myrecv);
		DetourAttach(&(PVOID&)dsend, mysend);
		DetourTransactionCommit();
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

int WINAPI myconnect(SOCKET s, const struct sockaddr* name, int namelen) {
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);
	SOCKADDR_IN* name_in = (SOCKADDR_IN*)name;
	printf("CONNECTING\n");
	printf("%s : %d\n", inet_ntoa(name_in->sin_addr), ntohs(name_in->sin_port));
	fclose(file);


	return dconnect(s, name, namelen);
}

int WINAPI myrecv(SOCKET s, char* buf, int len, int flags) {
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);
	printf("RECEIPT\n");
	printf("%d\n\n", len);
	fclose(file);

	return drecv(s, buf, len, flags);
}


int WINAPI mysend(SOCKET s, const char* buf, int len, int flags) {
	char* buf2 = (char*)buf;

	if (len > 6) {
		FILE* file;
		freopen_s(&file, "CONOUT$", "w", stdout);
		printf("SENDING - LEN %d\n", len);
		for (int i = 0; i < len; i ++)
		{
			printf("%02hhX ", buf[i]);
		}
		printf("\n\n");

		fclose(file);
	}

	//if (len == 11) {
	//	buf2[0] = 0x11;
	//}

	return dsend(s, (const char*)buf2, len, flags);
}

extern "C" __declspec(dllexport) void dummy(void) {
	return;
}