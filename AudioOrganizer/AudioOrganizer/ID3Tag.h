#ifndef ID3TAG_H
#define ID3TAG_H

class ID3Tag {
	char Tag[4];
	char Title[31];
	char Artist[31];
	char Album[31];
	char Year[5];
	char Comment[31];
	int ZeroByte;
	int Track;
	int Genre;
public:
	ID3Tag(void) {
		ZeroByte = Track = Genre = 0;
	}

	ID3Tag(char *tag, char *title, char *artist, char *album,
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
	}
};

#endif