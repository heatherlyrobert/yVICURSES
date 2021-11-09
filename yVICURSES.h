/*============================----beg-of-source---============================*/
#ifndef yVICURSES
#define yVICURSES yes



typedef  unsigned char        uchar;




/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(base)-----------------*/
char*       yVICURSES_version       (void);
char        yVICURSES_init          (char a_env, char *a_title, char *a_ver, void *a_cleanse, void *a_prep, void *a_cursor, void *a_refresh);
char        yVICURSES_wrap          (void);
char*       yVICURSES__unit         (char *a_question, char a_index);


char        yVICURSES_main          (char *a_delay, char *a_update, void *a_altinput);


#endif
/*============================----end-of-source---============================*/
