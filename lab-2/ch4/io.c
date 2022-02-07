#include "io.h"

#define FB_BLACK     0
#define FB_LIGHT_GREY 7

int main(){

	char *fb = (char *) 0x000B8000;
	/** fb_write_cell:
	*  Writes a character with the given foreground and background to position i
	*  in the framebuffer.
	*
	*  @param i  The location in the framebuffer
	*  @param c  The character
	*  @param fg The foreground color
	*  @param bg The background color
	
	void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg){
		fb[i] = c;
		fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
   	}
	fb_write_cell(0, 'A', FB_GREEN, FB_DARK_GREY);
	*/
	void fb_write_cell(unsigned int i, char c[], unsigned char fg, unsigned char bg){
		
		for(int count = 320; count < 720; count++){
			
			fb[count] = fg;
			fb[count+1] = fg;
				
		}
		
		for(int j = 0 ; c[j] != '\0'; j++){
			fb[i] = c[j];
			fb[i+1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
			i+=2;
		}
   	}
   	
   	char charArray[] = "-----------Hello, Welcome to COSC 519-----------";
   	
   	fb_write_cell(0, charArray, FB_BLACK, FB_LIGHT_GREY);
	
}
