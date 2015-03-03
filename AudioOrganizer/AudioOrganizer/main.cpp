/*
Jessica Cheung 2014

Code regarding browsing directories was referenced at
http ://www.codeproject.com/Articles/2604/Browse-Folder-dialog-search-folder-and-all-sub-fol
*/
#include "main.h"
#include "ID3v1Tag.h"
#include "ID3v2Tag.h"
const int TagLength = 128;

void BrowseDirectory(list<WIN32_FIND_DATA>& lst);
void FilterFiles(TCHAR *path, TCHAR *ext, list<WIN32_FIND_DATA>& lst);
void MenuManager(list<WIN32_FIND_DATA>& lst);
void PrintList(list<WIN32_FIND_DATA>& lst);
void EditManager(list<WIN32_FIND_DATA>& lst);

int main(void) {
	list<WIN32_FIND_DATA> FileList;
	BrowseDirectory(FileList);
	MenuManager(FileList);
	system("pause");
	return 0;
}

void MenuManager(list<WIN32_FIND_DATA>& lst) {
	char opt;
	cout << "Please select a following option" << endl;
	cout << "'E' for editing a song | 'C' for changing your directory | 'Q' for quit" << endl;
	cin >> opt;
	switch (opt)
	{
	case 'e':				//Edit a song
		EditManager(lst);
		break;
	case 'c':				//Change to different directory
		BrowseDirectory(lst);
		break;
	case 'q':
		exit(100);
	}
}

void BrowseDirectory(list<WIN32_FIND_DATA>& lst) {
	TCHAR path[MAX_PATH];											//Init path
	BROWSEINFO bi = { 0 };
	bi.lpszTitle = ("All Folders Automatically Recursed.");
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);						//Launch browse directory
	if (pidl != 0)													//If directory is selected
	{
		SHGetPathFromIDList(pidl, path);							//Insert directory name into path
		SetCurrentDirectory(path);									//Set the current directory to path

		wcout << path << endl;
		FilterFiles(path, "\\*.mp3*", lst);
		PrintList(lst);

		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}
	}
}

void FilterFiles(TCHAR *path, TCHAR *ext, list<WIN32_FIND_DATA>& lst) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR filename[MAX_PATH + 256];
	TCHAR pathback[MAX_PATH];

	lst.clear();													//Clear lst (FileList)
	strcpy_s(pathback, path);										//Copy path to backup
	strcat_s(path, strlen(path) + strlen(ext) + 1, ext);			//Concatenate extention to path
	
	hFind = FindFirstFile(path, &FindFileData);						//Find first file at path
	if (hFind == INVALID_HANDLE_VALUE) {							//If invalid, exit
		return ;
	}

	do {															//If valid, print file name. Loop
		lst.push_back(FindFileData);
	} while (FindNextFile(hFind, &FindFileData));

	return;
}

void PrintList(list<WIN32_FIND_DATA>& lst) {
	int i = 0;
	for (list<WIN32_FIND_DATA>::iterator it = lst.begin(); it != lst.end(); ++it) {
		++i;
		wcout << i << ": " << it->cFileName << endl;
	}
}

void EditManager(list<WIN32_FIND_DATA>& lst) {
	int val, val2;
	char *inString;
	fstream mp3file;
	ID3v1Tag TagStruct;
	char *buffer = new char[TagLength];
	cout << "Please select a song" << endl;						//Prompt user for song selection
	cin >> val;													//Track number chosen
	list<WIN32_FIND_DATA>::iterator it = lst.begin();
	advance(it, val - 1);										//Traverse to chosen song
	cout << it->cFileName << endl;
	mp3file.open(it->cFileName);
	mp3file.seekg(-TagLength, ios::end);
	mp3file.read(buffer, TagLength);
	cout << buffer << endl;
	TagStruct = ID3v1Tag(buffer);
	cout << "What would you like to edit?" << endl;
	cout << "1:Tag | 2:Title | 3:Artist | 4:Album | 5:Year | 6:Comment" << endl;
	cin >> val2;
	cout << "Enter new property" << endl;
	cin >> inString;
	switch (val2) {
	case 1:
		TagStruct.SetTag(inString);
		break;
	case 2:
		TagStruct.SetTitle(inString);
		break;
	case 3:
		TagStruct.SetArtist(inString);
		break;
	case 4:
		TagStruct.SetAlbum(inString);
		break;
	case 5:
		TagStruct.SetYear(inString);
		break;
	case 6:
		TagStruct.SetComment(inString);
		break;
	}
}