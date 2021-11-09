/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVICURSES.h"
#include    "yVICURSES_priv.h"



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char        yVICURSES_ver [200] = "";

char*
yVICURSES_version       (void)
{
   char        t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yVICURSES_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yVICURSES_ver;
}

char
yvicurses_getch         (char *a_ch)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_ch        =    0;
   char        x_key       =    0;
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_ch == NULL) {
      DEBUG_LOOP   yLOG_snote   ("NULL RETURN VAR");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   *a_ch = 0;
   --rce;  if (myVIKEYS.env != YVIKEYS_CURSES) {
      DEBUG_LOOP   yLOG_snote   ("ENV NOT CURSES");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_LOOP   yLOG_snote      ("curses");
   /*---(set delay)----------------------*/
   if (myVIKEYS.blocking == 'y') {
      DEBUG_LOOP   yLOG_snote   ("block/wait");
      nodelay  (stdscr, FALSE);
   } else {
      DEBUG_LOOP   yLOG_snote   ("check/free");
      nodelay  (stdscr, TRUE );
   }
   /*---(handle input)-------------------*/
   x_ch = getch ();
   DEBUG_LOOP   yLOG_sint    (x_ch);
   if (x_ch >= 0 && x_ch <= 255)  x_key = x_ch;
   else                           x_key = 0;
   DEBUG_LOOP   yLOG_sint    (x_key);
   /*---(save back)----------------------*/
   *a_ch = x_key;
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
   return 0;
}


char
yVICURSES_main          (char *a_delay, char *a_update, void *a_altinput)
{
   return yKEYS_main (a_delay, a_update, 0, YVIEW_CURSES, yVIEW_draw, yVICURSES_getch, a_altinput);
}

char
yvicurses_cleanse       (void)
{
}


