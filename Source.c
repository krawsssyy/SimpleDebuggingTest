#include <windows.h>
#include <winternl.h>

typedef NTSTATUS(*MYPROC) (HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);

int main()
{
	HANDLE hProc = GetCurrentProcess();
	PROCESS_BASIC_INFORMATION ProcessInformation;
	ULONG lenght = 0;
	HINSTANCE ntdll = LoadLibrary(L"Ntdll.dll");
	MYPROC GetProcessInformation = (MYPROC)GetProcAddress(ntdll, "NtQueryInformationProcess");
	//get _PEB object
	(GetProcessInformation)(hProc, ProcessBasicInformation, &ProcessInformation, sizeof(ProcessInformation), &lenght);
	if (ProcessInformation.PebBaseAddress->BeingDebugged == 0)
		MessageBox(HWND_DESKTOP, L"Not debugged", L"Notification", MB_OK);
	else
		MessageBox(HWND_DESKTOP, L"Debugged", L"Notification", MB_OK);

	return 0;
}