/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVICURSES.h"
#include    "yVICURSES_priv.h"



char
yvicurses_menus         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   short       x_left, x_wide, x_bott, x_tall;
   int         i           =    0;
   int         x_len       =    0;
   int         x_cen       =    0;
   char        t           [LEN_HUND]  = "";
   char        s           [LEN_HUND]  = "";
   short       x, y, xo, yo;
   char        l, a, v, x_lvl;
   char        b           [LEN_TERSE] = "";
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_char    ("mode"      , yMODE_curr ());
   if (yMODE_not (SMOD_MENUS)) {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(size)---------------------------*/
   yVIEW_size   (YVIEW_MENUS, NULL, &x_left, &x_wide, &x_bott, &x_tall);
   DEBUG_GRAF   yLOG_complex  ("size"      , "%3dl, %3dw, %3db, %3dt", x_left, x_wide, x_bott, x_tall);
   x_cen  = x_left + (x_wide * 0.50);
   myVICURSES.x_menu = x_left;
   myVICURSES.y_menu = x_bott - x_tall + 1;
   /*---(clear)--------------------------*/
   if (yKEYS_is_locked ())  yVICURSES_by_name ("!_warn");
   else                     yVICURSES_by_name ("m_edge");
   for (i = x_bott - x_tall + 1; i <= x_bott; ++i) {
      DEBUG_GRAF   yLOG_value   ("i"         , i);
      mvprintw   (i, x_left, "");
      mvprintw   (i, x_left + x_wide - 1, "");
   }
   if (yKEYS_is_locked ())  yVICURSES_by_name ("!_errs");
   else                     yVICURSES_by_name ("m_back");
   for (i = x_bott - x_tall + 1; i <= x_bott; ++i) {
      DEBUG_GRAF   yLOG_value   ("i"         , i);
      mvprintw   (i, x_left + 1, "%*.*s", x_wide - 2, x_wide - 2, YSTR_EMPTY);
   }
   /*---(overall data)-------------------*/
   rc = yCMD_menu_overall (&x_lvl, b, s);
   /*---(borders)------------------------*/
   if (yKEYS_is_locked ())  yVICURSES_by_name ("!_warn");
   else                     yVICURSES_by_name ("m_edge");
   strlcpy (t, "ƒ€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€‚", LEN_HUND);
   x_len = strlen (t);
   mvprintw   (x_bott - x_tall + 1, x_cen - (x_len / 2), t);
   switch (x_lvl) {
   case  0 : strlcpy (t, "´ main menu ´", LEN_HUND); break;
   case  1 : sprintf (t, "´ %s sub-menu ´", s); break;
   case  2 : sprintf (t, "´ %s options ´" , s); break;
   }
   x_len = strlen (t);
   mvprintw   (x_bott - x_tall + 1, x_cen - (x_len / 2), t);
   if (yKEYS_is_locked ())  yVICURSES_by_name ("!_warn");
   else                     yVICURSES_by_name ("m_edge");
   if (yKEYS_is_locked ())  strlcpy (t, "„€€€´ bad key, locked, ¥¥ to exit ´€€€€€…", LEN_HUND);
   else                     strlcpy (t, "„€€€€´ wide, flat, and universal ´€€€€€€…", LEN_HUND);
   x_len = strlen (t);
   mvprintw   (x_bott             , x_cen - (x_len / 2), t);
   /*---(menu path)----------------------*/
   if (yKEYS_is_locked ())  yVICURSES_by_name ("!_warn");
   else                     yVICURSES_by_name ("m_edge");
   sprintf (t, "\\%s", b);
   x_len = strlen (t);
   mvprintw   (x_bott - x_tall + 1, x_left + 2, "%s", t);
   sprintf (t, "%s", P_VERNUM);
   x_len = strlen (t);
   mvprintw   (x_bott - x_tall + 1, x_left + x_wide - x_len - 2, "%s", t);
   /*---(center)-------------------------*/
   if (x_lvl == 0) {
      if (yKEYS_is_locked ())  yVICURSES_by_name ("!_errs");
      else                     yVICURSES_by_name ("m_cent");
      strlcpy (t,   "‚„€Š€…ƒ"  , LEN_HUND);
      x_len = strlen (t);
      mvprintw   (x_bott - x_tall + 5, x_cen - (x_len / 2), t);
      strlcpy (t, "€‚„€‚ƒ€…ƒ€", LEN_HUND);
      x_len = strlen (t);
      mvprintw   (x_bott - x_tall + 6, x_cen - (x_len / 2), t);
      strlcpy (t, "€€ˆ‰€ˆŠˆ€‰ˆ€€", LEN_HUND);
      x_len = strlen (t);
      mvprintw   (x_bott - x_tall + 7, x_cen - (x_len / 2), t);
      strlcpy (t, "€€‰ˆ€‰Š‰€ˆ‰€€", LEN_HUND);
      x_len = strlen (t);
      mvprintw   (x_bott - x_tall + 8, x_cen - (x_len / 2), t);
      strlcpy (t, "€…ƒ€…„€‚„€", LEN_HUND);
      x_len = strlen (t);
      mvprintw   (x_bott - x_tall + 9, x_cen - (x_len / 2), t);
      strlcpy (t,   "…ƒ€Š€‚„"  , LEN_HUND);
      x_len = strlen (t);
      mvprintw   (x_bott - x_tall + 10, x_cen - (x_len / 2), t);
   }
   /*---(items)--------------------------*/
   if (yKEYS_is_locked ())  yVICURSES_by_name ("!_errs");
   else                     yVICURSES_by_name ("m_back");
   for (i = 0; i < 400; ++i) {
      rc = yCMD_menu_data          (i, &x, &y, b, &xo, &yo, &l, t, &a, &v);
      if (rc < 0)  break;
      if (yKEYS_is_locked ())  yVICURSES_by_name ("!_errs");
      else                     yVICURSES_by_name ("m_bull");
      mvprintw   (y, x, "%s", b);
      if      (xo == 0)  xo -= l / 2;
      else if (xo <  0)  xo -= l - 1;
      if (yKEYS_is_locked ())  yVICURSES_by_name ("!_errs");
      else {
         switch (v) {
         case 'y' : yVICURSES_by_name ("m_menu");   break;
         default  : yVICURSES_by_name ("m_back");   break;
         }
      }
      mvprintw   (y + yo, x + xo, "%s", t);
   }
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}
