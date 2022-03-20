/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVICURSES.h"
#include    "yVICURSES_priv.h"



/*====================------------------------------------====================*/
/*===----                      text-only drawing                       ----===*/
/*====================------------------------------------====================*/
static void  o___TEXTONLY________o () { return; }

char
yvicurses__text         (char a_part)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_on        =  '-';
   char        x_orient    =  '-';
   short       x_left, x_wide, x_bott, x_tall;
   char        x_name      [LEN_LABEL] = "";
   char        x_text      [LEN_RECD]  = "";
   int         i           =    0;
   int         x_len       =    0;
   int         x_beg       =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(get size)-----------------------*/
   yVIEW_curses (a_part, x_name, &x_on, NULL, x_text, &x_orient, &x_left, &x_wide, &x_bott, &x_tall);
   DEBUG_GRAF   yLOG_complex (x_name, "%c on %c, left %4d, wide %4d, bott %4d, tall %4d", a_part, x_on, x_left, x_wide, x_bott, x_tall);
   if (x_on != 'y') {
      DEBUG_GRAF   yLOG_note    ("hidden, not marked for display");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(pick color)---------------------*/
   --rce;  switch (a_part) {
   case YVIEW_TITLE   :
      yVICURSES_by_name ("w_sbar");
      break;
   case YVIEW_COMMAND  :
      yVICURSES_by_name ("w_cmds");
      break;
   case YVIEW_MODES    :
      if (yMACRO_exe_mode () == MACRO_RUN)  yVICURSES_by_name ("!_warn");
      else                                  yVICURSES_by_name ("w_keys");
      break;
   case YVIEW_VERSION :
   case YVIEW_KEYS     :
   case YVIEW_BUFFER   :
      yVICURSES_by_name ("w_keys");
      break;
   case YVIEW_STATUS  :
      if (yKEYS_is_error ())  yVICURSES_by_name ("!_warn");
      else                    yVICURSES_by_name ("w_sbar");
      break;
   default  :
      DEBUG_GRAF   yLOG_note    ("color not found for part");
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(default text)-------------------*/
   x_len = strlen (x_text);
   if (x_len <= 0)  sprintf (x_text, "n/a (%s)", x_name);
   x_len = strlen (x_text);
   x_beg = (x_tall - x_len) / 2;
   DEBUG_GRAF   yLOG_complex ("text"      , "%2dÂ%sÊ %2d", x_len, x_text, x_beg);
   /*---(rotated text)-------------------*/
   if (x_orient == 'r') {
      for (i = 0; i < x_tall; ++i) {
         mvprintw (x_bott - i, x_left, "%s", " ");
      }
      for (i = 0; i < x_len; ++i) {
         mvprintw (x_bott - i - x_beg, x_left, "%c", x_text [x_len - i - 1]);
      }
   }
   /*---(normal text)--------------------*/
   else {
      mvprintw (x_bott, x_left, "%-*.*s", x_wide, x_wide, x_text);
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char  yvicurses_title         (void)  { return yvicurses__text (YVIEW_TITLE); }
char  yvicurses_version       (void)  { return yvicurses__text (YVIEW_VERSION); }
char  yvicurses_modes         (void)  { return yvicurses__text (YVIEW_MODES); }
char  yvicurses_status        (void)  { return yvicurses__text (YVIEW_STATUS); }
char  yvicurses_keys          (void)  { return yvicurses__text (YVIEW_KEYS); }



/*====================------------------------------------====================*/
/*===----                     fancy text drawing                       ----===*/
/*====================------------------------------------====================*/
static void  o___FANCY___________o () { return; }

char
yvicurses_univs         (void)
{
   char        rc          =    0;
   char        t           [LEN_LABEL] = "";
   char        x_on        =  '-';
   short       x_left, x_wide, x_bott, x_tall;
   char        x_name      [LEN_LABEL] = "";
   char        x_pre       [LEN_LABEL] = "";
   char        x_main      [LEN_RECD]  = "";
   int         i           =    0;
   int         x_last      =   -1;
   char       *x_disp      = " 0 1 2 3 4 5 6 7 8 9 ∑ A B C D E F G H I J K L M N O P Q R S T U V W X Y Z ∑ Æ Ø § ¢";
   ushort      x_pos       =    0;
   short       x_ref       =    0;
   uchar       x_used      =    0;
   int         x_off       =    2;
   ushort      c           =    0;
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   yVIEW_curses (YVIEW_BUFFER, x_name, &x_on, NULL, NULL, NULL, &x_left, &x_wide, &x_bott, &x_tall);
   DEBUG_GRAF   yLOG_complex  (x_name, "%c on %c, %3dl, %3dw, %3db, %3dt", YVIEW_BUFFER, x_on, x_left, x_wide, x_bott, x_tall);
   /*> sprintf (x_main, "%s%s%s", BACK_YEL, BOLD_BLK, x_univ);                        <*/
   yVICURSES_by_name ("u_back");
   mvprintw (x_bott, x_left, "%-*.*s", x_wide, x_wide, x_disp);
   rc = yMAP_by_cursor (YMAP_UNIV, YDLST_HEAD, &x_pos, &x_ref, NULL, &x_used);
   yMAP_axis_grid (YMAP_UNIV , NULL, &c, NULL, NULL);
   while (rc >= 0) {
      DEBUG_GRAF   yLOG_complex  ("review", "%3d, %3d, %3d/%c", x_pos, x_ref, x_used, x_used);
      if      (x_pos < 10)  x_off = 1;
      else if (x_pos < 36)  x_off = 3;
      else                  x_off = 5;
      if (c == x_pos)  x_used = YMAP_CURR;
      switch (x_used) {
      case YMAP_CURR   :
         yVICURSES_by_name ("u_curr");
         mvprintw (x_bott, x_left +  x_off + (x_pos * 2), "%c", YSTR_UNIV [x_pos]);  break;
         break;
      case YMAP_USED  :
         yVICURSES_by_name ("u_used");
         mvprintw (x_bott, x_left +  x_off + (x_pos * 2), "%c", YSTR_UNIV [x_pos]);  break;
         break;
      case YMAP_PLACE :
         yVICURSES_by_name ("u_place");
         mvprintw (x_bott, x_left +  x_off + (x_pos * 2), "%c", YSTR_UNIV [x_pos]);  break;
         break;
      }
      rc = yMAP_by_cursor (YMAP_UNIV, YDLST_NEXT, &x_pos, &x_ref, NULL, &x_used);
   }
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       drawing functions                      ----===*/
/*====================------------------------------------====================*/
static void  o___DRAWING_________o () { return; }

char
yvicurses__color        (char a_part)
{
   /*---(locals)-----------+------+----+-*/
   char        x_edit      =   '-';
   char        x_code      =   '-';
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_char    ("a_part"     , a_part);
   DEBUG_GRAF   yLOG_char    ("curr"       , yMODE_curr ());
   DEBUG_GRAF   yLOG_char    ("prev"       , yMODE_prev ());
   /*---(fast-track formula)-------------*/
   if (a_part == YVIEW_FORMULA) {
      if (yMODE_curr () != MODE_SOURCE && yMODE_prev () != MODE_SOURCE)  {
         DEBUG_GRAF   yLOG_note    ("formula fast track");
         x_code = 'm';
      }
   }
   /*---(fast-track command)-------------*/
   if (a_part == YVIEW_COMMAND) {
      if (strchr (":/;", yMODE_curr ()) == NULL && strchr (":/;", yMODE_prev ()) == NULL) {
         DEBUG_GRAF   yLOG_note    ("command fast track");
         x_code = 'c';
      }
   }
   /*---(check focused)------------------*/
   if (x_code == '-' && strchr (MODES_ONELINE, yMODE_curr ()) != NULL)  {
      DEBUG_GRAF   yLOG_note    ("current source mode");
      x_edit = 'y';
      x_code = 's';
   }
   /*---(check editing)------------------*/
   else if (x_code == '-' && strchr (MODES_ONELINE, yMODE_prev ()) != NULL)  {
      DEBUG_GRAF   yLOG_note    ("sub-mode editing");
      x_edit = 'y';
      switch (yMODE_curr ()) {
      case SMOD_SREG       : x_code = 't';  break;
      case UMOD_REPLACE    : x_code = 'r';  break;
      case UMOD_INPUT      : x_code = 'i';  break;
      case UMOD_WANDER     : x_code = 'w';  break;
      default              : x_code = '-';  break;
      }
   }
   /*---(just a safety)------------------*/
   else if (x_code == '-') {
      DEBUG_GRAF   yLOG_note    ("catch for mistakes");
      x_code = 'e';
   }
   /*---(set curses color)---------------*/
   DEBUG_GRAF   yLOG_note    ("assign a ncurses color");
   switch (x_code) {
   case  'm' :  yVICURSES_by_name ("i_maps");  break;
   case  's' :  yVICURSES_by_name ("i_srcs");  break;
   case  'c' :  yVICURSES_by_name ("w_cmds");  break;
   case  't' :  yVICURSES_by_name ("i_treg");  break;
   case  'r' :  yVICURSES_by_name ("i_repl");  break;
   case  'i' :  yVICURSES_by_name ("i_inpt");  break;
   case  'w' :  yVICURSES_by_name ("i_wand");  break;
   case  'e' :  yVICURSES_by_name ("!_errs");  break;
   default   :  yVICURSES_by_name ("i_maps");  break;
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_char    ("x_edit"    , x_edit);
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return x_edit;
}

char
yvicurses__display         (char a_part, char a_loc, char a_style)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_edit      =  '-';
   char        x_on        =  '-';
   short       x_left, x_wide, x_bott, x_tall;
   char        x_name      [LEN_LABEL] = "";
   char        m           =  '-';
   char        l           [LEN_LABEL] = "";
   short       n, a, b, c, e;
   char        f           [LEN_LABEL] = "";
   char        t           [LEN_RECD]  = "";
   int         x_len       =    0;
   char        x_mark      =  ' ';
   short       x_beg       =    0;
   short       x_end       =    0;
   int         x_off       =    0;
   char        nn          [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("args"      , "%c part, %c loc, %c style", a_part, a_loc, a_style);
   /*---(get sizes)----------------------*/
   yVIEW_curses (a_loc , x_name, &x_on, NULL, NULL, NULL, &x_left, &x_wide, &x_bott, &x_tall);
   DEBUG_GRAF   yLOG_complex  (x_name, "%c on %c, %3dl, %3dw, %3db, %3dt", a_part, x_on, x_left, x_wide, x_bott, x_tall);
   /*---(defense)------------------------*/
   if (x_on != 'y') {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(test for editing)---------------*/
   x_edit = yvicurses__color (a_part);
   DEBUG_GRAF   yLOG_char    ("x_edit"    , x_edit);
   /*---(get contents)-------------------*/
   ySRC_contents (a_part, &m, l, &n, &a, &b, &c, &e, f, t);
   DEBUG_GRAF   yLOG_complex  ("pos"       , "%3dn, %3da, %3db, %3dc, %3de", n, a, b, c, e);
   DEBUG_GRAF   yLOG_complex  ("content"   , "%c Â%sÊ", m, t);
   /*> strlcpy (l, "JESUS", LEN_LABEL);                                               <*/
   DEBUG_GRAF   yLOG_info     ("label"     , l);
   DEBUG_GRAF   yLOG_info     ("format"    , f);
   /*---(draw)---------------------------*/
   if (a_part == YVIEW_COMMAND && x_edit != 'y') {
      x_len = strlen (yMODE_message ());
      if (x_len < x_wide)  mvprintw (x_bott, x_left, "%-*.*s" , x_wide - 1, x_wide - 1, yMODE_message ());
      else                 mvprintw (x_bott, x_left, "%-*.*s¨", x_wide - 1, x_wide - 1, yMODE_message ());
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(content)------------------------*/
   if (a_part == YVIEW_COMMAND) {
      x_off = 4;
      strlpadn (n, nn, '.', '>', 4);
      mvprintw (x_bott, x_left, "%s %-*.*s ", nn, a, a, t + b);
   } else {
      switch (a_style) {
      case '-' :
         x_off = 0;
         if (n == 0) {
            mvprintw (x_bott, x_left, " %c%-*.*s ", G_CHAR_NULL, a - 1, a - 1, YSTR_EMPTY);
         } else {
            mvprintw (x_bott, x_left, " %-*.*s ", a, a, t + b);
         }
         break;
      case 's' :
         x_off = 4;
         if (n == 0) {
            mvprintw (x_bott, x_left, "%-4.4s %c%-*.*s ", "∑∑∑∑", G_CHAR_NULL, a - 1, a - 1, YSTR_EMPTY);
         } else {
            strlpadn (n, nn, '.', '>', 4);
            mvprintw (x_bott, x_left, "%s %-*.*s ", nn, a, a, t + b);
         }
         break;
      case 'l' :
         x_off = 12;
         if (n == 0) {
            mvprintw (x_bott, x_left, " %-6.6s %-4.4s %c%-*.*s ", l, "∑∑∑∑", G_CHAR_NULL, a - 1, a - 1, YSTR_EMPTY);
         } else {
            strlpadn (n, nn, '.', '>', 4);
            mvprintw (x_bott, x_left, " %-6.6s %s %-*.*s ", l, nn, a, a, t + b);
         }
         break;
      case 'x' :
         x_off = 13 + strlen (f);
         if (n == 0) {
            mvprintw (x_bott, x_left, " %-6.6s %s %-4.4s %c%-*.*s ", l, f, "∑∑∑∑", G_CHAR_NULL, a - 1, a - 1, YSTR_EMPTY);
         } else {
            strlpadn (n, nn, '.', '>', 4);
            mvprintw (x_bott, x_left, " %-6.6s %s %s %-*.*s ", l, f, nn, a, a, t + b);
         }
         break;
      }
   }
   /*---(beg marker)---------------------*/
   if (n != 0) {
      if (b >  0)   x_mark = '<';
      else          x_mark = 'Â';
      mvprintw (x_bott, x_left + x_off, "%c", x_mark);
   }
   /*---(update offset)------------------*/
   ++x_off;
   /*---(end marker)---------------------*/
   if (n != 0) {
      x_len = e - b + 1;
      if (e != n - 1) x_mark = '>';
      else            x_mark = 'Ê';
      mvprintw (x_bott, x_left + x_off + x_len, "%c", x_mark);
   }
   /*---(selection)----------------------*/
   if (x_edit == 'y' && ySRC_select_islive () && n > 0) {
      ysrc_select_curr (&x_beg, &x_end, NULL);
      if (x_beg < b)  x_beg = b;
      if (x_end > e)  x_end = e;
      x_len = x_end - x_beg + 1;
      yVICURSES_by_name ("i_sele");
      mvprintw (x_bott, x_left + x_off + x_beg - b, "%-*.*s", x_len, x_len, t + x_beg);
   }
   /*---(current)------------------------*/
   if (x_edit == 'y' && n > 0) {
      yVICURSES_by_name ("i_maps");
      mvprintw (x_bott, x_left + x_off + c - b, "%c", t [c]);
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvicurses_formula       (void)
{
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   yvicurses__display (YVIEW_FORMULA, YVIEW_FORMULA, myVICURSES.p_formula);
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvicurses_formula_min   (void)
{
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   myVICURSES.p_formula = '-';
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvicurses_formula_small (void)
{
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   myVICURSES.p_formula = 's';
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvicurses_formula_label (void)
{
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   myVICURSES.p_formula = 'l';
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvicurses_formula_max   (void)
{
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   myVICURSES.p_formula = 'x';
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvicurses_command       (void)
{
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   yvicurses__display (YVIEW_COMMAND, YVIEW_COMMAND, '-');
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvicurses_float         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_mode      =  '-';
   char        x_on        =  '-';
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(check modes)-----------------*/
   DEBUG_GRAF   yLOG_char    ("mode_curr" , yMODE_curr ());
   DEBUG_GRAF   yLOG_char    ("mode_prev" , yMODE_prev ());
   if      (strchr (MODES_ONELINE, yMODE_curr ()) != NULL )      x_mode = yMODE_curr ();
   else if (strchr (MODES_ONELINE, yMODE_prev ()) != NULL )      x_mode = yMODE_prev ();
   DEBUG_GRAF   yLOG_char    ("x_mode"    , x_mode);
   if (x_mode == '-')  {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check modes)-----------------*/
   --rce;  switch (x_mode) {
   case MODE_SOURCE  :
      if (yVIEW_showing (YVIEW_FORMULA)) {
         DEBUG_GRAF   yLOG_note    ("mode source already shown in normal manner");
      } else {
         DEBUG_GRAF   yLOG_note    ("mode source as float");
         if (yVIEW_showing (x_mode))  yvicurses__display (YVIEW_FORMULA, YVIEW_FLOAT, '-');
      }
      break;
   case MODE_COMMAND :
   case MODE_SEARCH  :
   case SMOD_HINT    :
      if (yVIEW_showing (YVIEW_COMMAND)) {
         DEBUG_GRAF   yLOG_note    ("mode command already shown in normal manner");
      } else {
         DEBUG_GRAF   yLOG_note    ("mode command/search as float");
         if (yVIEW_showing (x_mode))  yvicurses__display (YVIEW_COMMAND, YVIEW_FLOAT, '-');
      }
      break;
   default :
      DEBUG_GRAF   yLOG_note    ("default");
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)--------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      menu focused                            ----===*/
/*====================------------------------------------====================*/
static void  o___MENU____________o () { return; }

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
   /*---(clear)--------------------------*/
   yVICURSES_by_name ("m_back");
   for (i = x_bott - x_tall + 1; i <= x_bott; ++i) {
      DEBUG_GRAF   yLOG_value   ("i"         , i);
      mvprintw   (i, x_left, "Å%*.*sÅ", x_wide - 2, x_wide - 2, YSTR_EMPTY);
   }
   /*---(overall data)-------------------*/
   rc = yCMD_menu_overall (&x_lvl, b, s);
   /*---(borders)------------------------*/
   strlcpy (t, "ÉÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÇ", LEN_HUND);
   x_len = strlen (t);
   mvprintw   (x_bott - x_tall + 1, x_cen - (x_len / 2), t);
   switch (x_lvl) {
   case  0 : strlcpy (t, "¥ main menu ¥", LEN_HUND); break;
   case  1 : sprintf (t, "¥ %s sub-menu ¥", s); break;
   case  2 : sprintf (t, "¥ %s options ¥" , s); break;
   }
   x_len = strlen (t);
   mvprintw   (x_bott - x_tall + 1, x_cen - (x_len / 2), t);
   strlcpy (t, "ÑÄÄÄÄ¥ wide, flat, and universal ¥ÄÄÄÄÄÖ", LEN_HUND);
   x_len = strlen (t);
   mvprintw   (x_bott             , x_cen - (x_len / 2), t);
   /*---(menu path)----------------------*/
   if (x_lvl > 0) {
      sprintf (t, "µ%s", b);
      x_len = strlen (t);
      mvprintw   (x_bott - x_tall + 2, x_left + 2, "%s", t);
   }
   /*---(version)------------------------*/
   sprintf (t, "%s", P_VERNUM);
   x_len = strlen (t);
   mvprintw   (x_bott - x_tall + 2, x_left + x_wide - x_len - 2, "%s", t);
   /*---(center)-------------------------*/
   if (x_lvl == 0) {
      yVICURSES_by_name ("m_cent");
      strlcpy (t,   "ÇÑÄäÄÖÉ"  , LEN_HUND);
      x_len = strlen (t);
      mvprintw   (x_bott - x_tall + 5, x_cen - (x_len / 2), t);
      strlcpy (t, "ÄÇÑÄÇÅÉÄÖÉÄ", LEN_HUND);
      x_len = strlen (t);
      mvprintw   (x_bott - x_tall + 6, x_cen - (x_len / 2), t);
      strlcpy (t, "ÄÄàâÄàäàÄâàÄÄ", LEN_HUND);
      x_len = strlen (t);
      mvprintw   (x_bott - x_tall + 7, x_cen - (x_len / 2), t);
      strlcpy (t, "ÄÄâàÄâäâÄàâÄÄ", LEN_HUND);
      x_len = strlen (t);
      mvprintw   (x_bott - x_tall + 8, x_cen - (x_len / 2), t);
      strlcpy (t, "ÄÖÉÄÖÅÑÄÇÑÄ", LEN_HUND);
      x_len = strlen (t);
      mvprintw   (x_bott - x_tall + 9, x_cen - (x_len / 2), t);
      strlcpy (t,   "ÖÉÄäÄÇÑ"  , LEN_HUND);
      x_len = strlen (t);
      mvprintw   (x_bott - x_tall + 10, x_cen - (x_len / 2), t);
   }
   /*---(items)--------------------------*/
   yVICURSES_by_name ("m_back");
   for (i = 0; i < 400; ++i) {
      rc = yCMD_menu_data          (i, &x, &y, b, &xo, &yo, &l, t, &a, &v);
      if (rc < 0)  break;
      yVICURSES_by_name ("m_bull");
      mvprintw   (y, x, "%s", b);
      if      (xo == 0)  xo -= l / 2;
      else if (xo <  0)  xo -= l - 1;
      switch (v) {
      case 'y' : yVICURSES_by_name ("m_menu");   break;
      default  : yVICURSES_by_name ("m_back");   break;
      }
      mvprintw   (y + yo, x + xo, "%s", t);
   }
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



