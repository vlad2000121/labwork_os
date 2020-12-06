
#include "FileInfoFuncHeader.h"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR lpszCmdLine, int nCmdShow)
{

	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = MainWindowProc; // ������� ���������
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 2);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName = TEXT("MainWindowClass"); // ��� ������
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);



	//DWORD dwDisposition;

	//// ������ � ��������� ���� ������� ��� ���������� ���������� ����������
	//RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\IT-311"),
	//	0, NULL, REG_OPTION_NON_VOLATILE, KEY_QUERY_VALUE | KEY_SET_VALUE, NULL, &hKey, &dwDisposition);
	//
	//// �������� ��� �����/�������� �� ���������� �������
	//RegGetValueSZ(hKey, TEXT("Path"), FileName, _countof(FileName), NULL);
	//// �������� ��������� ���� �� ���������� �������
	//RegGetValueBinary(hKey, TEXT("rect"), (LPBYTE)&rect, sizeof(rect), NULL);


	LoadLibrary(TEXT("ComCtl32.dll"));//��� ��������� ������ �����������		


	if (0 == RegisterClassEx(&wcex)) // ������������ �����
	{
		return -1; // ��������� ������ ����������
	}
	RECT wr = { 0, 0, 500, 500 };    // set the size, but not the position

	// ������� ������� ���� �� ������ ������ �������� ������
	HWND hWnd = CreateWindowEx(0, TEXT("MainWindowClass"), TEXT("Process"), WS_OVERLAPPEDWINDOW^WS_THICKFRAME^WS_MINIMIZEBOX^WS_MAXIMIZEBOX, 300, 300,
		wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, hInstance, NULL);
	if (IsRectEmpty(&rect) == FALSE)
	{
		// �������� ��������� ����
		SetWindowPos(hWnd, NULL, rect.left, rect.top, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
	} // if


	if (NULL == hWnd)
	{
		return -1; // ��������� ������ ����������
	}

	ShowWindow(hWnd, nCmdShow); // ���������� ������� ����

	MSG  msg;
	BOOL Ret;

	for (;;)
	{

		// ��������� ��������� �� �������
		Ret = GetMessage(&msg, NULL, 0, 0);
		if (Ret == FALSE)
		{
			break; // �������� WM_QUIT, ����� �� �����
		}
		else if (!TranslateAccelerator(hWnd, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	return (int)msg.wParam;
}

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
	case WM_SIZE:
	{
		HWND hwndCtl = GetDlgItem(hwnd,	IDC_EDIT_TEXT);
		MoveWindow(hwndCtl, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE); // �������� ������� ���� �����
	}

	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0); // ���������� ��������� WM_QUIT
	}break;
	case WM_CLOSE:

		DestroyWindow(hwnd); // ���������� ����
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}



BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCRStr)
{
	CreateWindowEx(0, TEXT("Edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 10, 400, 20, hwnd, (HMENU)IDC_EDIT_FILENAME, lpCRStr->hInstance, NULL);

	HWND hwndLV = CreateWindowEx(0, TEXT("SysListView32"), NULL, WS_CHILD | WS_VISIBLE| WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 30, 50, 400, 150, hwnd, (HMENU)IDC_LIST1, lpCRStr->hInstance, NULL);

	//�������� ���������
	/*
	CreateWindowEx(0, TEXT("button"), TEXT("������ ��� ������"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 30, 200, 400, 30, hwnd, (HMENU)IDC_ATTRIBUTE_READONLY, lpCRStr->hInstance, NULL);
	CreateWindowEx(0, TEXT("button"), TEXT("�������"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 30, 230, 400, 30, hwnd, (HMENU)IDC_ATTRIBUTE_HIDDEN, lpCRStr->hInstance, NULL);
	CreateWindowEx(0, TEXT("button"), TEXT("���� ����� ��� ���������������"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 30, 260, 400, 30, hwnd, (HMENU)IDC_ATTRIBUTE_ARCHIVE, lpCRStr->hInstance, NULL);
	CreateWindowEx(0, TEXT("button"), TEXT("���������"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 30, 290, 400, 30, hwnd, (HMENU)IDC_ATTRIBUTE_SYSTEM, lpCRStr->hInstance, NULL);
	CreateWindowEx(0, TEXT("button"), TEXT("���������"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 30, 320, 400, 30, hwnd, (HMENU)IDC_ATTRIBUTE_TEMPORARY, lpCRStr->hInstance, NULL);
	CreateWindowEx(0, TEXT("button"), TEXT("������� ��� �������� �����"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 30, 350, 400, 30, hwnd, (HMENU)IDC_ATTRIBUTE_COMPRESSED, lpCRStr->hInstance, NULL);
	CreateWindowEx(0,TEXT("button"), TEXT("��������� ���������� ��� ������"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,30, 380, 400, 30, hwnd,(HMENU)IDC_ATTRIBUTE_ENCRYPTED,lpCRStr->hInstance, NULL);
	*/
	// ����� ����������� 
	ListView_SetExtendedListViewStyle(hwndLV, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// ��������� ��� ������� � ������ ���������

	LVCOLUMN lvColumns[] = {
		{ LVCF_WIDTH | LVCF_TEXT, 0, 100, (LPTSTR)TEXT("���") },
		{ LVCF_WIDTH | LVCF_TEXT, 0, 100, (LPTSTR)TEXT("���") },
		{ LVCF_WIDTH | LVCF_TEXT, 0, 100, (LPTSTR)TEXT("��������� �:") },

	};

	for (int i = 0; i < _countof(lvColumns); ++i)
	{
		// ��������� �������
		ListView_InsertColumn(hwndLV, i, &lvColumns[i]);
	}
	
	CreateWindowEx(0, TEXT("Static"), TEXT("��������:"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		30, 220, 80, 20, hwnd, NULL, lpCRStr->hInstance, NULL);
	CreateWindowEx(0, TEXT("Edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 220, 310, 20, hwnd, (HMENU)IDC_EDIT_OWNER, lpCRStr->hInstance, NULL);

	CreateWindowEx(0, TEXT("Static"), TEXT("�������� ��:"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		30, 250, 80, 20, hwnd, NULL, lpCRStr->hInstance, NULL);
	CreateWindowEx(0, TEXT("Edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 250, 310, 20, hwnd, (HMENU)IDC_NEW_OWNER, lpCRStr->hInstance, NULL);


	//if (FileName != NULL) //���� ���� �� ������, �� ��������� ������
	//{
	//	ListViewInit(FileName, hwnd);
	//}

	return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	static HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_TEXT);

	switch (id)
	{
	case ID_OPEN_FILE: // �������
	{
		BROWSEINFO bi;//structure for open special box with folder in treview
		LPITEMIDLIST pidl;
		ZeroMemory(&bi, sizeof(bi));
		bi.hwndOwner = NULL;
		bi.pszDisplayName = FileName;
		bi.lpszTitle = TEXT("Select file");
		bi.ulFlags = BIF_BROWSEINCLUDEFILES; 
		pidl = SHBrowseForFolder(&bi);//open window for select
		if (pidl)
		{
			SHGetPathFromIDList(pidl, FileName);//get path
			//SetDlgItemText(hwnd, IDC_EDIT_FILENAME, FileName);
			if (!(ListViewInit(FileName, hwnd)))
			{
				GetLastError();
				break;
			}
		}
	}
	break;
	case ID_OPEN_DIR://������� �����
	{
		BROWSEINFO bi;//structure for open special box with folder in treview
		LPITEMIDLIST            pidl;
		LPMALLOC  pMalloc = NULL;

		ZeroMemory(&bi, sizeof(bi));
		bi.hwndOwner = NULL;
		bi.pszDisplayName = FileName;
		bi.lpszTitle = TEXT("Select folder");
		bi.ulFlags = BIF_RETURNONLYFSDIRS;

		pidl = SHBrowseForFolder(&bi);//open window for select
		if (pidl)
		{
			SHGetPathFromIDList(pidl, FileName);//get path

			if (!(ListViewInit(FileName, hwnd)))
			{
				GetLastError();
				break;
			}
		}
	} break;
	case ID_CHANGE_ATR://��������� ���������
	{
		/*
		TCHAR NewFileName[MAX_PATH]; // ����� ��� �����/��������
		GetDlgItemText(hwnd, IDC_EDIT_FILENAME, NewFileName, _countof(NewFileName));//��� ��� � ��� � ��������� lpszFileName

			// ����� ��� � ���� � �����/��������
		lpszFileName = PathFindFileName(FileName);

		// ��������� ����� ���� � �����/��������
		cchPath = (DWORD)(lpszFileName - FileName) - 1;
		// ��������� ����-�������� ���� � ��� �����/��������
		FileName[cchPath] = _T('\0');

		if (CompareString(LOCALE_USER_DEFAULT, 0, lpszFileName, -1, NewFileName, -1) != CSTR_EQUAL) // (!) ���������� ��� �����/��������
		{
			TCHAR ExistingFileName[MAX_PATH]; // ������ ��� �����/��������
			StringCchPrintf(ExistingFileName, _countof(ExistingFileName), TEXT("%s\\%s"), FileName, lpszFileName);

			// ��������� ����� ���� � �����/��������
			PathAppend(FileName, NewFileName);
			// ��������������� ����/�������
			MoveFile(ExistingFileName, FileName);
		} // if
		else
		{
			// ������� ����-������, ����������� ���� � ��� �����/��������
			FileName[cchPath] = _T('\\');
		} // else

		// ������ ���������
		constexpr DWORD attr[] = {
			FILE_ATTRIBUTE_READONLY, FILE_ATTRIBUTE_HIDDEN, FILE_ATTRIBUTE_ARCHIVE,
			FILE_ATTRIBUTE_SYSTEM, FILE_ATTRIBUTE_TEMPORARY, FILE_ATTRIBUTE_COMPRESSED, FILE_ATTRIBUTE_ENCRYPTED
		};

		// ������ ��������������� ������� ��� ���������
		constexpr DWORD ids[] = {
			IDC_ATTRIBUTE_READONLY, IDC_ATTRIBUTE_HIDDEN, IDC_ATTRIBUTE_ARCHIVE,
			IDC_ATTRIBUTE_SYSTEM, IDC_ATTRIBUTE_TEMPORARY, IDC_ATTRIBUTE_COMPRESSED, IDC_ATTRIBUTE_ENCRYPTED
		};

		DWORD dwFileAttributes = 0; // �������� �����/��������

		// ����������, ����� �������� �������

		for (int i = 0; i < _countof(attr); ++i)
		{
			if (IsDlgButtonChecked(hwnd, ids[i]) == BST_CHECKED) // ������ ����������
			{
				dwFileAttributes |= attr[i]; // ������� ��������������� �������
			} // if
		} // for

		// ������� ��������
		SetFileAttributes(FileName, dwFileAttributes);

		ListViewInit(FileName, hwnd);*/
	}

	case ID_CHANGE_OWNER://�������������� ��� ���������� ���������
	{
		/*//������?
		HWND hHide = GetDlgItem(hwnd, IDC_LIST1);
		ShowWindow(hHide, SW_HIDE);
		/*��!*/

		TCHAR NewOwner[UNLEN + 1]; // ����� ��� ���������
		
		GetDlgItemText(hwnd, IDC_NEW_OWNER, NewOwner, _countof(NewOwner));//��� ��� � ��� � ��������� lpszFileName

		BOOL RetRes = SetFileSecurityInfo(FileName,NewOwner,0,NULL, FALSE);//�� ������, ������???

		if (RetRes != FALSE)
		{
			SetDlgItemText(hwnd, IDC_NEW_OWNER, NULL);
		}
		else
		{
			MessageBox(hwnd, TEXT("�� ������� ������� ���������. ��������� ������������ ���������� ����� ������������."), NULL, MB_OK | MB_ICONERROR);
		}
	}	break;

	case ID_EXIT:
		SendMessage(hwnd, WM_CLOSE, 0, 0);
		RegCloseKey(hKey);
		break;

	}
}

BOOL ListViewInit(LPTSTR path, HWND hwnd)
{
	// ������ ��������� �������� ���� grfInheritance
	constexpr DWORD dwInherit[7] = {
		NO_INHERITANCE,
		SUB_CONTAINERS_AND_OBJECTS_INHERIT,
		SUB_CONTAINERS_ONLY_INHERIT,
		SUB_OBJECTS_ONLY_INHERIT,
		INHERIT_ONLY | SUB_CONTAINERS_AND_OBJECTS_INHERIT,
		INHERIT_ONLY | SUB_CONTAINERS_ONLY_INHERIT,
		INHERIT_ONLY | SUB_OBJECTS_ONLY_INHERIT
	};

	// ������ �����, ���������� �������� ��� ��������� �������� ���� grfInheritance
	constexpr LPCTSTR szInheritText[7] = {
		TEXT("������ ��� ����� ��������"),
		TEXT("��� ����� ��������, ��� ������������ � ������"),
		TEXT("��� ����� �������� � ��� ������������"),
		TEXT("��� ����� �������� � ��� ������"),
		TEXT("������ ��� ������������ � ������"),
		TEXT("������ ��� ������������"),
		TEXT("������ ��� ������")
	};

	WIN32_FILE_ATTRIBUTE_DATA bhfi;
	TCHAR TimeBuffer[100], Buffer[100];
	if (!GetFileAttributesEx(path, GetFileExInfoStandard, &bhfi))
	{
		GetLastError();
	}
	/*���������� �����*/
	LPTSTR lpFN = PathFindFileNameW(path);
	SetDlgItemText(hwnd, IDC_EDIT_FILENAME, lpFN);

	/*������������� ������*/
	HWND hwndLV = GetDlgItem(hwnd, IDC_LIST1);
	ListView_DeleteAllItems(hwndLV); //������� ������ ���������

	// ����������� ���������� ������
	if (NULL != Sec_Descriptor) LocalFree(Sec_Descriptor), Sec_Descriptor = NULL;
	// ������� ���������� ������������
	BOOL RetRes = GetFileSecurityDescriptor(FileName, OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION, &Sec_Descriptor);

	if (RetRes != FALSE)
	{
		LPWSTR Owner = NULL; 
		RetRes = GetOwnerName_W(Sec_Descriptor, &Owner);
		SetDlgItemText(hwnd, IDC_EDIT_OWNER, Owner);// �������� ��� ������� ������ ��������� � ���� "������� ��������"
		// ����������� ���������� ������
		LocalFree(Owner);
		
	}

	ULONG uCount = 0; // ���������� ��������� � ������� ACE
	PEXPLICIT_ACCESS pEA = NULL; // ������ ACE

	RetRes = GetItemFromDACL(Sec_Descriptor, &uCount, &pEA);

	if (RetRes != FALSE)
	{
		for (ULONG i = 0; i < uCount; ++i)
		{
			LVITEM lvItem = { LVIF_TEXT | LVIF_PARAM };

			lvItem.iItem = (int)i;

			// ��������� ����� �������
			lvItem.lParam = (LPARAM)pEA[i].grfAccessPermissions;

			// ��������� ��� ACE
			switch (pEA[i].grfAccessMode)
			{
			case GRANT_ACCESS:
				lvItem.pszText = (LPTSTR)TEXT("���������");
				break;
			case DENY_ACCESS:
				lvItem.pszText = (LPTSTR)TEXT("���������");
				break;
			} // switch

			// ��������� ����� ������� � ������ ��������� DACL
			int iItem = ListView_InsertItem(hwndLV, &lvItem);
			if (iItem == -1) continue; // �� ������� �������� ����� �������

			 // ��������� ��� ������� ������
			if (TRUSTEE_IS_SID == pEA[i].Trustee.TrusteeForm)
			{
				LPTSTR lpszName = NULL; // ��� ������� ������

				// ������� ��� ������� ������
				GetAccountName_W(pEA[i].Trustee.ptstrName, &lpszName);

				if (NULL != lpszName)
				{
					// �������� ��� ������� ������ � ������ ������ ��������� DACL
					ListView_SetItemText(hwndLV, iItem, 1, lpszName);
					// ����������� ���������� ������
					LocalFree(lpszName);
				} // if
			} // if
			// ��������� � ����� �������� ����������� ����� �������
			DWORD grfInheritance = pEA[i].grfInheritance & (~INHERIT_NO_PROPAGATE);

			for (int j = 0; j < _countof(dwInherit); ++j)
			{
				if (grfInheritance == dwInherit[j]) // ������� ��������
				{
					// �������� � ������ ������ ��������� DACL �������� ��� �������� ���� grfInheritance
					ListView_SetItemText(hwndLV, iItem, 2, (LPTSTR)szInheritText[j]);

					break; // ������� �� �����
				} // if
			} // for
		}
	}

	/*

	// ������ ���������
	constexpr DWORD attr[] = {
		FILE_ATTRIBUTE_READONLY, FILE_ATTRIBUTE_HIDDEN, FILE_ATTRIBUTE_ARCHIVE,
		FILE_ATTRIBUTE_SYSTEM, FILE_ATTRIBUTE_TEMPORARY, FILE_ATTRIBUTE_COMPRESSED, FILE_ATTRIBUTE_ENCRYPTED
	};
	// ������ ��������������� ������� ��� ���������
	constexpr DWORD ids[] = {
		IDC_ATTRIBUTE_READONLY, IDC_ATTRIBUTE_HIDDEN, IDC_ATTRIBUTE_ARCHIVE,
		IDC_ATTRIBUTE_SYSTEM, IDC_ATTRIBUTE_TEMPORARY, IDC_ATTRIBUTE_COMPRESSED, IDC_ATTRIBUTE_ENCRYPTED
	};

	// �������� ������ �������������� � �������������� ���������� �����/��������

	for (int i = 0; i < _countof(attr); ++i)
	{
		UINT uCheck = (bhfi.dwFileAttributes & attr[i]) ? BST_CHECKED : BST_UNCHECKED;
		CheckDlgButton(hwnd, ids[i], uCheck);
	}

	// ��������� ���������� ����� */
	//CloseHandle(hFile);
	return TRUE;
}

BOOL __stdcall CalculateSize(LPCTSTR lpszFileName, const LPWIN32_FILE_ATTRIBUTE_DATA lpFileAttributeData, LPVOID lpvParam)
{
	if (lpFileAttributeData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		// ��������� ����� ������ ��������
		return FileSearch(TEXT("*"), lpszFileName, CalculateSize, lpvParam);
	} // if
	return TRUE; // ���������� TRUE, ����� ���������� �����
}

BOOL FileSearch(LPCTSTR lpszFileName, LPCTSTR path, LPSEARCHFUNC lpSearchFunc, LPVOID lpvParam)
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	LARGE_INTEGER size;
	TCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	StringCchCopy(szDir, MAX_PATH, path);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		//error. terminator . later.
	}
	do
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			((ULARGE_INTEGER *)lpvParam)->QuadPart += filesize.QuadPart;
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);
	return TRUE;
}

BOOL GetFileTimeFormat(const LPFILETIME lpFileTime, LPTSTR lpszFileTime, DWORD cchFileTime)
{
	SYSTEMTIME st;

	// ����������� ���� � ����� �� FILETIME � SYSTEMTIME
	BOOL bRet = FileTimeToSystemTime(lpFileTime, &st);

	// �������� ���� � ����� � �������� �������� �����
	if (FALSE != bRet)
		bRet = SystemTimeToTzSpecificLocalTime(NULL, &st, &st);

	if (FALSE != bRet)
	{
		// ��������� ���� � �������������� ������
		GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &st, NULL, lpszFileTime, cchFileTime);

		// ������� ����� � �������������� ������

		StringCchCat(lpszFileTime, cchFileTime, TEXT(", "));
		DWORD len = _tcslen(lpszFileTime);

		if (len < cchFileTime)
			GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, &st, NULL, lpszFileTime + len, cchFileTime - len);
	} // if

	return bRet;
}
void ConvertFileSize(LPTSTR lpszBuffer, DWORD cch, LARGE_INTEGER size)
{
	if (size.QuadPart >= 0x40000000ULL)
	{
		StringCchPrintf(lpszBuffer, cch, TEXT("%.1f ��"), (size.QuadPart / (float)0x40000000ULL));
	} // if
	else if (size.QuadPart >= 0x100000ULL)
	{
		StringCchPrintf(lpszBuffer, cch, TEXT("%.1f ��"), (size.QuadPart / (float)0x100000ULL));
	} // if
	else if (size.QuadPart >= 0x0400ULL)
	{
		StringCchPrintf(lpszBuffer, cch, TEXT("%.1f ��"), (size.QuadPart / (float)0x0400ULL));
	} // if
	else
	{
		StringCchPrintf(lpszBuffer, cch, TEXT("%u ����"), size.LowPart);
	} // else

	size_t len = _tcslen(lpszBuffer);

	if (len < cch)
	{
		StringCchPrintf((lpszBuffer + len), (cch - len), TEXT(" (%llu ����)"), size.QuadPart);
	} // if
} // StringCchPrintFileSize

void ConvertDirectSize(LPTSTR lpszBuffer, DWORD cch, ULARGE_INTEGER size)
{
	if (size.QuadPart >= 0x40000000ULL)
	{
		StringCchPrintf(lpszBuffer, cch, TEXT("%.1f ��"), (size.QuadPart / (float)0x40000000ULL));
	} // if
	else if (size.QuadPart >= 0x100000ULL)
	{
		StringCchPrintf(lpszBuffer, cch, TEXT("%.1f ��"), (size.QuadPart / (float)0x100000ULL));
	} // if
	else if (size.QuadPart >= 0x0400ULL)
	{
		StringCchPrintf(lpszBuffer, cch, TEXT("%.1f ��"), (size.QuadPart / (float)0x0400ULL));
	} // if
	else
	{
		StringCchPrintf(lpszBuffer, cch, TEXT("%u ����"), size.LowPart);
	} // else

	size_t len = _tcslen(lpszBuffer);

	if (len < cch)
	{
		StringCchPrintf((lpszBuffer + len), (cch - len), TEXT(" (%llu ����)"), size.QuadPart);
	} // if
} // StringCchPrintFileSize


//work wit regist
LSTATUS RegGetValueSZ(HKEY hKey, LPCTSTR lpValueName, LPTSTR lpszData, DWORD cch, LPDWORD lpcchNeeded)
{
	// ���������� ��� ����������� �������� ���������
	DWORD RegType;
	LSTATUS retCode = RegQueryValueEx(hKey, lpValueName, NULL, &RegType, NULL, NULL);
	if (ERROR_SUCCESS == retCode && REG_SZ == RegType)
	{
		DWORD DataBuffer = cch * sizeof(TCHAR);
		// �������� �������� ���������
		retCode = RegQueryValueEx(hKey, lpValueName, NULL, NULL, (LPBYTE)lpszData, &DataBuffer);
	}
	else if (ERROR_SUCCESS == retCode)
	{
		retCode = ERROR_UNSUPPORTED_TYPE; // �������� ��� ������
	}

	return retCode;
}

LSTATUS RegGetValueBinary(HKEY hKey, LPCTSTR lpValueName, LPBYTE lpData, DWORD cb, LPDWORD lpcbNeeded)
{
	DWORD dwType;
	// ���������� ��� ����������� �������� ���������
	LSTATUS lStatus = RegQueryValueEx(hKey, lpValueName, NULL, &dwType, NULL, NULL);

	if (ERROR_SUCCESS == lStatus && REG_BINARY == dwType)
	{
		// �������� �������� ���������
		lStatus = RegQueryValueEx(hKey, lpValueName, NULL, NULL, lpData, &cb);

		if (NULL != lpcbNeeded) *lpcbNeeded = cb;
	} // if
	else if (ERROR_SUCCESS == lStatus)
	{
		lStatus = ERROR_UNSUPPORTED_TYPE; // �������� ��� ������
	} // if

	return lStatus;
} // RegGetValueBinary

/*�����������*/
BOOL GetFileSecurityDescriptor(LPCWSTR lpFileName, SECURITY_INFORMATION RequestedInformation, PSECURITY_DESCRIPTOR *ppSD)
{
	DWORD cb = 0;

	// ��������� ������ ����������� ������������
	GetFileSecurity(lpFileName, RequestedInformation, NULL, 0, &cb);

	// ������� ������ ��� ����������� ������������
	PSECURITY_DESCRIPTOR pSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LMEM_FIXED, cb);
	if (NULL == pSD) return FALSE;

	// ������� ���������� ������������
	BOOL bRet = GetFileSecurity(lpFileName, RequestedInformation, pSD, cb, &cb);

	if (FALSE != bRet)
	{
		*ppSD = pSD; // ���������� ���������� ���������� ������������
	} // if
	else
	{
		//LocalFree(pSD); // ����������� ���������� ������
	} // else

	return bRet;
} // GetFileSecurityDescriptor

BOOL GetItemFromDACL(PSECURITY_DESCRIPTOR Sec_Descriptor, PULONG pcCountOfEntries, PEXPLICIT_ACCESS *pListOfEntries)
{
	PACL pDacl = NULL;
	BOOL bDaclPresent = FALSE, bDaclDefaulted = FALSE;

	// �������� DACL
	BOOL bRet = GetSecurityDescriptorDacl(Sec_Descriptor, &bDaclPresent, &pDacl, &bDaclDefaulted);

	if (FALSE != bRet && FALSE != bDaclPresent)
	{
		// ��������� �������� �� DACL
		DWORD dwResult = GetExplicitEntriesFromAcl(pDacl, pcCountOfEntries, pListOfEntries);
		bRet = (ERROR_SUCCESS == dwResult) ? TRUE : FALSE;
	} // if
	else
	{
		*pcCountOfEntries = 0; // ���������� 0 ���������
	} // else

	return bRet;
}

/*��������� ����� �������� �� ��� SID � �� ����� ��������*/
BOOL GetAccountName_W(PSID psid, LPWSTR* AccountName)
{
	BOOL RetRes = FALSE;
	SID_NAME_USE SidType;//���������� �������������� ����, ���� �������� ������������ ��� SID
	/*���������� ��� ������*/
	LPWSTR Name = NULL;
	DWORD cch = 0, cchRefDomainName = 0;

	if (IsValidSid(psid) == FALSE)
	{
		return FALSE;
	}

	LookupAccountSid(NULL, psid, NULL, &cch, NULL, &cchRefDomainName, NULL);//��������� ������� �������

	DWORD cb = (cch + cchRefDomainName) * sizeof(TCHAR);

	if (cb > 0)
	{

		Name = (LPWSTR)LocalAlloc(LMEM_FIXED, cb);//��������� ������ �� ��������� ���� ��������
	}

	if (Name != NULL)
	{
		RetRes = LookupAccountSid(NULL, psid, Name + cchRefDomainName, &cch, Name, &cchRefDomainName, &SidType);
	}

	if (RetRes != FALSE)
	{
		if (SidTypeDomain != SidType)
		{
			if (cchRefDomainName > 0)
			{
				Name[cchRefDomainName] = '\\';
			}
			else
			{
				StringCbCopy(Name, cb, Name + 1);//����������� ��� �������� � ������� ��������
			}
		}
		*AccountName = Name; //������ ����������� ��� � ���������
	}
	else
	{
		ConvertSidToStringSid(psid, AccountName);//���� �� ���������� �������� ���, �� ������ SID
		if (Name != NULL)
		{
			LocalFree(Name);
		}
	}
	return RetRes;
}

/*����������� ������� ������������ SID*/
BOOL GetAccountSID_W(LPCWSTR AccountName, PSID *ppsid)
{
	BOOL RetRes = FALSE;
	SID_NAME_USE SidType;//���������� �������������� ����, ���� �������� ������������ ��� SID

	/*���������� ��� ����������� ����� � SID*/
	LPWSTR RefDomainName = NULL;
	PSID psid = NULL;
	DWORD cbSID = 0, cchRefDomainName = 0;

	LookupAccountNameW(NULL, AccountName, NULL, &cbSID, NULL, &cchRefDomainName, NULL);//����������� �������� ������ ��� �����

	if ((cbSID > 0) && (cchRefDomainName > 0))
	{
		psid = (PSID)LocalAlloc(LMEM_FIXED, cbSID); //��������� ������ �� ��������� ���� ��������
		RefDomainName = (LPWSTR)LocalAlloc(LMEM_FIXED, cchRefDomainName * sizeof(WCHAR));// -||- ��� ����� ������
	}

	if ((psid != NULL) && (RefDomainName != NULL))
	{
		RetRes = LookupAccountName(NULL, AccountName, psid, &cbSID, RefDomainName, &cchRefDomainName, &SidType);
	}

	if (RetRes != FALSE)
	{
		*ppsid = psid;
	}
	else
	{
		if (psid != NULL)
		{
			LocalFree(psid);//����������� ������
		}
	}

	if (RefDomainName != NULL)
	{
		LocalFree(RefDomainName);//����������� ������
	}

	return RetRes;
}


/*��������� ����� ������������ �� ����������� ������������*/
BOOL GetOwnerName_W(PSECURITY_DESCRIPTOR Sec_Descriptor, LPWSTR *OwnerName)
{
	PSID psid;
	BOOL bDefaulted;

	// �������� SID ���������
	BOOL bRet = GetSecurityDescriptorOwner(Sec_Descriptor, &psid, &bDefaulted);

	if (FALSE != bRet)
	{
		// ���������� ��� ������� ������ ���������
		bRet = GetAccountName_W(psid, OwnerName);
	} // if

	return bRet;
}

/*��������� ���������� � ����������� ������������*/
BOOL SetFileSecurityInfo(LPCTSTR FileName, LPWSTR NewOwner,ULONG CountOfEntries, PEXPLICIT_ACCESS pListOfEntries, BOOL bMergeEntries)
{
	SECURITY_DESCRIPTOR secur_desc;

	/*�������� ������ ��� ����� ��������*/
	PSID psid_Owner = NULL;
	PACL pNewDacl = NULL;
	
	BOOL RetRes = FALSE;

	RetRes = InitializeSecurityDescriptor(&secur_desc, SECURITY_DESCRIPTOR_REVISION);

	if (RetRes != FALSE && NewOwner != NULL)
	{
		
		RetRes = GetAccountSID_W(NewOwner, &psid_Owner);//�� ����� ��������� ������� ��� SID

		LPWSTR CheckOwner;
		BOOL check = GetAccountName_W(psid_Owner, &CheckOwner);

		if (RetRes != FALSE)
		{
			RetRes = SetSecurityDescriptorOwner(&secur_desc, psid_Owner, FALSE);//��� ����� ����������� � SID
		}
	}
	//�� ������� �������. �� ������� ����. ������?
	if (RetRes != FALSE && CountOfEntries > 0 && pListOfEntries != NULL)
	{
		PSECURITY_DESCRIPTOR OldSD = NULL;
		PACL pOldDacl = NULL; // ��������� �� ����� ��� DACL

		BOOL DaclDefaulted = FALSE;
		BOOL DaclPresent;

		if (bMergeEntries != FALSE)
		{
			RetRes = GetFileSecurityDescriptor(FileName, DACL_SECURITY_INFORMATION, &OldSD);
			if (RetRes != FALSE)
			{
				GetSecurityDescriptorDacl(OldSD, &DaclPresent, &pOldDacl, &DaclDefaulted);
			}
		}

		DWORD result = SetEntriesInAcl(CountOfEntries, pListOfEntries, pOldDacl, &pNewDacl);
		RetRes = (ERROR_SUCCESS == result) ? TRUE:FALSE;
		if (RetRes != FALSE)
		{
			RetRes = SetSecurityDescriptorDacl(&psid_Owner, TRUE, pNewDacl, DaclDefaulted);
		}
		if (OldSD != NULL)
			LocalFree(OldSD);
	}

	/*���� �������� ���������???*/
	if (RetRes != NULL)
	{
		SECURITY_INFORMATION si = 0;
		if (psid_Owner != NULL) si |= OWNER_SECURITY_INFORMATION;
		if (pNewDacl != NULL) si |= DACL_SECURITY_INFORMATION;

		RetRes = SetFileSecurity(FileName, si, &secur_desc); //�������� ���������� ������������ ��� �����
	}

	/*������������ ������*/
	if (psid_Owner != NULL)
	{
		LocalFree(psid_Owner);
	}
	if (pNewDacl != NULL)
	{
		LocalFree(pNewDacl);
	}

	return RetRes;
	
}