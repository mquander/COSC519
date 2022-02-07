
#define FB_BLACK     0
#define FB_LIGHT_GREY 7

char *fb = (char *) 0x000B8000;

int display(char *message, int numTimesToPrintString){

	unsigned char fg = FB_BLACK;
	unsigned char bg = FB_LIGHT_GREY;
	
	for(int count = 320; count < 720; count++){
			
		fb[count] = fg;
		fb[count+1] = fg;
				
	}
	
	int numChars = 0;
	int i = 0;
	//char *space = "\n";
	for(int index = 0; index < numTimesToPrintString; index++){
		for(int j = 0 ; message[j] != '\0'; j++){
			fb[i] = message[j];
			fb[i+1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
			i+=2;
			numChars += 1;
		}
		//fb[i+2] = *space;
	}
	
	return numChars;
}
