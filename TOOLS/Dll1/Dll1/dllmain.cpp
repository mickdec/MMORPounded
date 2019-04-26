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

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)dconnect, myconnect);
		DetourAttach(&(PVOID&)drecv, myrecv);
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
	//FILE* file;
	//fopen_s(&file, "C:\\Users\\***\\Desktop\\ret.txt", "a+");
	//SOCKADDR_IN* name_in = (SOCKADDR_IN*)name;
	//fprintf(file, "%s : %d\n",inet_ntoa(name_in->sin_addr) ,ntohs(name_in->sin_port));
	//fclose(file);
	return dconnect(s, name, namelen);
}

int WINAPI myrecv(SOCKET s, char* buf, int len, int flags) {
	FILE* file;
	fopen_s(&file, "C:\\Users\\***\\Desktop\\ret.txt", "a+");
	fprintf(file, "%s", buf);
	fclose(file);
	return drecv(s, buf, len, flags);
}

extern "C" __declspec(dllexport) void dummy(void) {
	return;
}