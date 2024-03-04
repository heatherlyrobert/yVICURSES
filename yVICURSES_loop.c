/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVICURSES.h"
#include    "yVICURSES_priv.h"



/*====================------------------------------------====================*/
/*===----                        resize the parts                      ----===*/
/*====================------------------------------------====================*/
static void      o___RESIZE__________________o (void) {;}

char
yvicurses_resize        (void)
{
   int         x_wide     =    0;
   int         x_tall     =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_value   ("wide"      , myVICURSES.wide);
   DEBUG_GRAF   yLOG_value   ("tall"      , myVICURSES.tall);
   getmaxyx (stdscr, x_tall, x_wide);
   DEBUG_GRAF   yLOG_value   ("x_wide"    , x_wide);
   DEBUG_GRAF   yLOG_value   ("x_tall"    , x_tall);
   if (myVICURSES.wide != x_wide || myVICURSES.tall != x_tall) {
      DEBUG_GRAF   yLOG_note    ("must update");
      yVIEW_resize (x_wide, x_tall, 0);
      myVICURSES.wide = x_wide;
      myVICURSES.tall = x_tall;
   }
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        gather input                          ----===*/
/*====================------------------------------------====================*/
static void      o___INPUT___________________o (void) {;}

#define  ctrl(x)   ((x) & 0x1f)

char
yvicurses_getch         (char a_block, char *a_ch)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_ch        =    0;
   char        x_key       =    0;
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_LOOP   yLOG_schar   (a_block);
   --rce;  if (a_block == 0 || strchr ("y-", a_block) == NULL) {
      DEBUG_LOOP   yLOG_snote   ("illegal blocking type");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_LOOP   yLOG_spoint  (a_ch);
   --rce;  if (a_ch == NULL) {
      DEBUG_LOOP   yLOG_snote   ("NULL RETURN VAR");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   DEBUG_LOOP   yLOG_snote   ("default");
   *a_ch = 0;
   /*---(set delay)----------------------*/
   if (a_block == 'y') {
      DEBUG_LOOP   yLOG_snote   ("block/wait");
      nodelay  (stdscr, FALSE);
   } else {
      DEBUG_LOOP   yLOG_snote   ("check/free");
      nodelay  (stdscr, TRUE );
   }
   /*---(handle input)-------------------*/
   x_ch = getch ();
   DEBUG_LOOP   yLOG_sint    (x_ch);
   /*---(fix keypad keys)----------------*/
   switch (x_ch) {
   case KEY_BACKSPACE :
      DEBUG_LOOP   yLOG_snote   ("backspace (263)");
      x_ch = 8;
      break;
   case KEY_DC        :
      DEBUG_LOOP   yLOG_snote   ("delete (330)");
      x_ch = 127;
      break;
   case KEY_DOWN      :
      DEBUG_LOOP   yLOG_snote   ("up arrow (258)");
      x_ch = 'j';
      break;
   case KEY_UP        :
      DEBUG_LOOP   yLOG_snote   ("down arrow (259)");
      x_ch = 'k';
      break;
   case KEY_LEFT      :
      DEBUG_LOOP   yLOG_snote   ("left arrow (260)");
      x_ch = 'h';
      break;
   case KEY_RIGHT     :
      DEBUG_LOOP   yLOG_snote   ("right arrow (261)");
      x_ch = 'l';
      break;
   }
   /*---(truncate value limits)----------*/
   if (x_ch >= 0 && x_ch <= 255)  x_key = x_ch;
   else                           x_key = 0;
   DEBUG_LOOP   yLOG_sint    (x_key);
   /*---(handle control keys)------------*/
   switch (x_key) { /* VERTICAL */
   /* C-t */  case  20 :  x_key =  14;   break;
   /* C-b */  case   2 :  x_key =  15;   break;
   /* C-s */  case  19 :  x_key =  16;   break;
   /* C-e */  case   5 :  x_key =  17;   break;
   /* C-f */  case   6 :  x_key =  18;   break;
   /* C-n */  case  14 :  x_key =  19;   break;
   }
   /*---(save back)----------------------*/
   DEBUG_LOOP   yLOG_sint    (x_key);
   *a_ch = x_key;
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

/*> abcdefghijklmnopqrstuvwxyz                                                        <*/


/*====================------------------------------------====================*/
/*===----                       drawing support                        ----===*/
/*====================------------------------------------====================*/
static void      o___DRAW____________________o (void) {;}

char yVICURSES_redraw   (void)  { myVICURSES.redraw = 'y'; return 0; }

char
yvicurses_cleanse       (void)
{
   char        x_redraw  = '-';
   yvicurses_resize ();
   yVIEW_redraw (&x_redraw);
   if (x_redraw == 'y' || myVICURSES.redraw == 'y') clear  ();
   myVICURSES.redraw = '-';
   return 0;
}

char
yvicurses_prep          (char a_abbr)
{
   return 0;
}

char
yvicurses_cursor        (void)
{
   getyx (stdscr, myVICURSES.y_cur, myVICURSES.x_cur);
   return 0;
}

char
yvicurses_refresh       (void)
{
   /*> mvprintw (0,0,"%3dw,%3dt", myVICURSES.wide, myVICURSES.tall);                                    <*/
   if (yMODE_curr () == SMOD_MENUS) {
      mvprintw (myVICURSES.y_menu, myVICURSES.x_menu, "");
   } else if (yMODE_curr () == UMOD_HISTORY) {
      mvprintw (myVICURSES.y_menu, myVICURSES.x_menu, "");
   } else {
      mvprintw (myVICURSES.y_cur , myVICURSES.x_cur , "");
   }
   refresh ();
   return 0;
}

char yVICURSES_draw_now      (void) { return yVIEW_draw (); }

