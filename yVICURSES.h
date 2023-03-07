/*============================----beg-of-source---============================*/
#ifndef yVICURSES
#define yVICURSES yes



typedef  unsigned char        uchar;




/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(base)-----------------*/
char*       yVICURSES_version       (void);
char        yVICURSES_init          (char *a_title, char *a_version, char a_mode);
char        yVICURSES_wrap          (void);
char*       yVICURSES__unit         (char *a_question, char a_index);


char        yVICURSES_main          (char *a_delay, char *a_update, void *a_altinput);

char        yVICURSES_color         (char *a_terse, char *a_desc, char a_fg, char a_bg);
char        yVICURSES_by_name       (char *a_terse);
char*       yVICURSES_at_loc        (short x, short y);
char*       yVICURSES_at_str        (short x, short y, short a_wide, short a_tall);

#endif
/*============================----end-of-source---============================*/
