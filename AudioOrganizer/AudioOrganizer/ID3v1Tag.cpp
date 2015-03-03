#include "ID3v1Tag.h"

void ID3v1Tag::SetTag(char *tag) {
	strcpy(Tag, tag);
}
void ID3v1Tag::SetTitle(char *title) {
	strcpy(Title, title);
}
void ID3v1Tag::SetArtist(char *artist) {
	strcpy(Artist, artist);
}
void ID3v1Tag::SetAlbum(char *album) {
	strcpy(Album, album);
}
void ID3v1Tag::SetYear(char *year) {
	strcpy(Year, year);
}
void ID3v1Tag::SetComment(char *comment) {
	strcpy(Comment, comment);
}