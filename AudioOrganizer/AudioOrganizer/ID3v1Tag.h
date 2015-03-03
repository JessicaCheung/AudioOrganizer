#ifndef ID3V1TAG_H
#define ID3V1TAG_H
#include "main.h"

class ID3v1Tag {
protected:
	char Tag[3];
	char Title[30];
	char Artist[30];
	char Album[30];
	char Year[4];
	char Comment[30];
public:
	ID3v1Tag(void) {
	}
	ID3v1Tag(char *buffer) {
		string strbuffer(buffer);
		strcpy(Tag, (strbuffer.substr(0, 3)).c_str());
		strcpy(Title, (strbuffer.substr(3, 30)).c_str());
		strcpy(Artist, (strbuffer.substr(33, 30)).c_str());
		strcpy(Album, (strbuffer.substr(63, 30)).c_str());
		strcpy(Year, (strbuffer.substr(93, 4)).c_str());
		strcpy(Comment, (strbuffer.substr(97, 30)).c_str());
		
		cout << Tag << endl;
		cout << Title << endl;
		cout << Artist << endl;
		cout << Album << endl;
		cout << Year << endl;
		cout << Comment << endl;
	}
	/*ID3Tag(char *tag, char *title, char *artist, char *album,
		char *year, char *comment, int zerobyte, int track, int genre) {
		strcpy(Tag, tag);
		strcpy(Title, title);
		strcpy(Artist, artist);
		strcpy(Album, album);
		strcpy(Year, year);
		strcpy(Comment, comment);
		ZeroByte = zerobyte;
		Track = track;
		Genre = genre;
	}*/
	void SetTag(char *tag);
	void SetTitle(char *title);
	void SetArtist(char *artist);
	void SetAlbum(char *album);
	void SetYear(char *year);
	void SetComment(char *comment);
};

#endif