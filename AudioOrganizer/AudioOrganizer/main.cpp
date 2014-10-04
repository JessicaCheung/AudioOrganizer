/*
Jessica Cheung 2014

Code regarding browsing directories was referenced at
http ://www.codeproject.com/Articles/2604/Browse-Folder-dialog-search-folder-and-all-sub-fol
*/
#include <string>
#include <iostream>
#include <Windows.h>
#include <ShlObj.h>
#include "ID3Tag.h"
using namespace std;

void BrowseDirectory(void);
void FilterFiles(TCHAR *path, TCHAR *ext);

int main(void) {
	BrowseDirectory();
	system("pause");
	return 0;
}

void BrowseDirectory(void) {
	TCHAR path[MAX_PATH];											//Init path
	BROWSEINFO bi = { 0 };
	bi.lpszTitle = ("All Folders Automatically Recursed.");
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);						//Launch browse directory
	if (pidl != 0)													//If directory is selected
	{
		SHGetPathFromIDList(pidl, path);							//Insert directory name into path
		SetCurrentDirectory(path);									//Set the current directory to path

		wcout << path << endl;
		FilterFiles(path, "\\*.mp3*");

		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}
	}
}

void FilterFiles(TCHAR *path, TCHAR *ext) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR filename[MAX_PATH + 256];
	TCHAR pathback[MAX_PATH];

	strcpy_s(pathback, path);										//Copy path to backup
	strcat_s(path, strlen(path) + strlen(ext) + 1, ext);			//Concatenate extention to path
	
	hFind = FindFirstFile(path, &FindFileData);						//Find first file at path
	if (hFind == INVALID_HANDLE_VALUE) {							//If invalid, exit
		return ;
	}

	do {															//If valid, print file name. Loop
		wcout << FindFileData.cFileName << endl;
	} while (FindNextFile(hFind, &FindFileData));

	return;
}