/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVICURSES.h"
#include    "yVICURSES_priv.h"




/*====================------------------------------------====================*/
/*===----                      menu focused                            ----===*/
/*====================------------------------------------====================*/
static void  o___DRIVER__________o () { return; }

char
yvicurses_history       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   short       x_left, x_wide, x_bott, x_tall;
   int         i           =    0;
   int         x_len       =    0;
   int         c           =    0;
   int         n           =    0;
   char        x_entry     [LEN_HUND]  = "";
   char        x_head      =  '-';
   int         x_curr      =    0;
   int         x_cnt       =    0;
   int         x_max       =    0;
   char        x_label     [LEN_LABEL] = "´ command history ´";
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_GRAF   yLOG_char    ("mode"      , yMODE_curr ());
   if (yMODE_not (UMOD_HISTORY)) {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(size)---------------------------*/
   yVIEW_size   (YVIEW_HISTORY, NULL, &x_left, &x_wide, &x_bott, &x_tall);
   DEBUG_GRAF   yLOG_complex  ("size"      , "%3dl, %3dw, %3db, %3dt", x_left, x_wide, x_bott, x_tall);
   c = yVIEW_hist_count ();
   DEBUG_GRAF   yLOG_value   ("count"     , c);
   if (c == 0) {
      x_bott -= x_tall - 2;
      x_tall = 2;
      x_max  = 1;
   } else if (c < x_tall) {
      x_bott -= x_tall - c - 1;
      x_tall = c + 1;
      x_max  = c;
   } else {
      x_max  = x_tall - 2;
   }
   if (x_wide > 84)  x_wide = 84;
   DEBUG_GRAF   yLOG_complex  ("size"      , "%3db, %3dt", x_bott, x_tall);
   /*---(set cursor position)------------*/
   myVICURSES.x_menu = x_left + 1;
   myVICURSES.y_menu = x_bott - 1;
   /*---(color)--------------------------*/
   if (yKEYS_is_locked ())  yVICURSES_by_name ("!_warn");
   else                     yVICURSES_by_name ("m_edge");
   /*---(header)-------------------------*/
   if (yMODE_prev () == MODE_SEARCH)  strcpy (x_label, "´ search history ´");
   x_len = strlen (x_label);
   mvprintw (x_bott - x_tall, x_left + x_wide, "‚");
   mvprintw (x_bott - x_tall, x_left, "%-*.*s", x_wide, x_wide, "ƒ€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€");
   mvprintw (x_bott - x_tall, x_left + x_wide / 2 - x_len / 2, "%-s", x_label);
   /*---(body)---------------------------*/
   for (i = x_bott - x_tall + 1; i < x_bott; ++i) {
      mvprintw (i, x_left, "%-*.*s", x_wide, x_wide, "                                                                                               ");
      mvprintw (i, x_left + x_wide, "");
   }
   /*---(footer)-------------------------*/
   mvprintw (x_bott         , x_left, "%-*.*s", x_wide, x_wide, "„€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€");
   mvprintw (x_bott         , x_left + x_wide, "…");
   /*---(zero entries)-------------------*/
   if (c == 0) {
      mvprintw (x_bott - x_tall + 1, x_left + 2, "··· no entries recorded");
   }
   /*---(entries)------------------------*/
   else {
      yVIEW_hist_cursor (YDLST_CURR, &x_curr);
      DEBUG_GRAF   yLOG_value   ("x_curr"    , x_curr);
      yVIEW_hist_push ();
      yVIEW_hist_cursor (YDLST_TAIL, &n);
      yVIEW_hist_entry (x_wide - 4, x_entry);
      i = x_bott - 1;
      while (strcmp (x_entry, "n/a") != 0) {
         /*> if (i <= x_bott - x_tall + 1)  break;                                       <*/
         if (++x_cnt > x_max)  break;
         if (n == 0) {
            if (x_head == 'y')  break;
            x_head = 'y';
         }
         mvprintw (i, x_left + 2, "%s", x_entry);
         if (x_curr == n) {
            mvprintw (i, x_left + 1, ">");
            myVICURSES.x_menu = x_left + 1;
            myVICURSES.y_menu = i;
         }
         yVIEW_hist_cursor (YDLST_PREV, &n);
         yVIEW_hist_entry (x_wide - 4, x_entry);
         --i;
      }
      yVIEW_hist_pop  ();
      yVIEW_hist_cursor (YDLST_CURR, &x_curr);
      DEBUG_GRAF   yLOG_value   ("x_curr"    , x_curr);
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}


