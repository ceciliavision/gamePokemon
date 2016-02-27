
#ifndef TGA_H
#define TGA_H



#ifndef byte
typedef unsigned char byte;
#endif


///This function is used to load tga file
byte*	load_tga( char *name, int *width, int *height, int *BPP );
///This function is used to save the tga file
bool	save_tga( char *name, int  width, int  height, byte *img, int BPP=24 );



#endif
