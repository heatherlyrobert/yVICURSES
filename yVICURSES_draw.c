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
   case YVIEW_VERSION  :
   case YVIEW_BUFFER   :
      yVICURSES_by_name ("w_keys");
      break;
   case YVIEW_KEYS     :
      if (yKEYS_is_locked ())      yVICURSES_by_name ("!_warn");
      else if (yKEYS_is_error ())  yVICURSES_by_name ("!_warn");
      else                         yVICURSES_by_name ("w_keys");
      break;
   case YVIEW_STATUS  :
      if (yKEYS_is_locked ())      yVICURSES_by_name ("!_warn");
      else if (yKEYS_is_error ())  yVICURSES_by_name ("!_warn");
      else                         yVICURSES_by_name ("w_sbar");
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
   DEBUG_GRAF   yLOG_complex ("text"      , "%2då%sæ %2d", x_len, x_text, x_beg);
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
yvicurses__small        (char r_small [LEN_TITLE])
{
   char        rc          =    0;
   int         i           =    0;
   int         c           =    0;
   int         x_off       =    0;
   uchar       x_used      =  '·';
   strcpy (r_small, " ··· ··· ··· ··· ···");
   rc = yMAP_by_cursor (YMAP_UNIV, YDLST_HEAD, NULL, NULL, NULL, &x_used);
   while (rc >= 0) {
      if (x_used == YMAP_USED || x_used == YMAP_PLACE) {
         if (c % 3 == 0)  ++x_off;
         r_small [c + x_off] = YSTR_UNIV [i];
         ++c;
      }
      rc = yMAP_by_cursor (YMAP_UNIV, YDLST_NEXT, NULL, NULL, NULL, &x_used);
      ++i;
   }
   return 0;
}

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
   int         x_last      =   -1;
   char       *x_list      = YSTR_UNIV;
   char       *x_extra     = " ·  ··u ·s   0 1 2 3 4 5 6 7 8 9 · A B C D E F G H I J K L M N O P Q R S T U V W X Y Z · ® ¯ ¤ ¢";  /* 86 */
   char       *x_large     = " 0 1 2 3 4 5 6 7 8 9 · A B C D E F G H I J K L M N O P Q R S T U V W X Y Z · ® ¯ ¤ ¢";  /* 86 */
   char       *x_med       = " 012345·6789AB·CDEFGH·IJKLMN·OPQRST·UVWXYZ·®¯¤¢";  /* 47 */
   char        x_small     [LEN_TITLE] = " ··· ··· ··· ··· ···";
   char       *x_disp      = NULL;
   char       *p           = NULL;
   ushort      x_pos       =    0;
   short       x_ref       =    0;
   uchar       x_used      =    0;
   int         x_off       =    0;
   int         i           =    0;
   ushort      c           =    0;
   char        x_id        =  ' ';
   char        x_usr       =    0;
   char        x_sys       =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(get size)-----------------------*/
   yVIEW_curses (YVIEW_BUFFER, x_name, &x_on, NULL, NULL, NULL, &x_left, &x_wide, &x_bott, &x_tall);
   DEBUG_GRAF   yLOG_complex  (x_name, "%c on %c, %3dl, %3dw, %3db, %3dt", YVIEW_BUFFER, x_on, x_left, x_wide, x_bott, x_tall);
   /*---(prepare sizes)------------------*/
   if      (x_wide >= 98)  x_disp = x_extra;
   else if (x_wide >= 86)  x_disp = x_large;
   else if (x_wide >= 47)  x_disp = x_med;
   else {
      yvicurses__small (x_small);
      x_disp = x_small;
   }
   /*---(get current)--------------------*/
   yMAP_axis_grid (YMAP_UNIV , NULL, &c, NULL, NULL);
   /*---(show background)----------------*/
   yVICURSES_by_name ("u_back");
   mvprintw (x_bott, x_left, "%-*.*s", x_wide, x_wide, x_disp);
   /*---(cycle universes)----------------*/
   rc = yMAP_by_cursor (YMAP_UNIV, YDLST_HEAD, &x_pos, &x_ref, NULL, &x_used);
   while (rc >= 0) {
      DEBUG_GRAF   yLOG_value   ("i"         , i);
      x_id  = YSTR_UNIV [i];
      DEBUG_GRAF   yLOG_value   ("univ"      , x_id);
      p     = strchr (x_disp, x_id);
      DEBUG_GRAF   yLOG_point   ("x_list"    , x_list);
      DEBUG_GRAF   yLOG_point   ("p"         , p);
      x_pos = p - x_disp;
      DEBUG_GRAF   yLOG_value   ("x_pos"     , x_pos);
      switch (x_used) {
      case YMAP_USED  : case YMAP_PLACE :
         if (strchr ("®¯¤¢", x_id) != NULL)  ++x_sys;
         else                                ++x_usr;
         break;
      }
      if (c == i) {
         x_used = YMAP_CURR;
         if (x_disp == x_extra) {
            yVICURSES_by_name ("u_back");
            mvprintw (x_bott, x_left + 1, "%c"  , x_id);
         }
      }
      DEBUG_GRAF   yLOG_complex  ("review", "%3dl, %3do, %3dp, %2dc, %c, %c", x_left, x_off, x_pos, i, x_used, x_id);
      switch (x_used) {
      case YMAP_CURR   :
         yVICURSES_by_name ("u_curr");
         break;
      case YMAP_USED  :
         yVICURSES_by_name ("u_used");
         break;
      case YMAP_PLACE :
         yVICURSES_by_name ("u_place");
         break;
      }
      switch (x_used) {
      case YMAP_CURR   : case YMAP_USED  : case YMAP_PLACE :
         if (x_disp != x_small) {
            mvprintw (x_bott, x_left +  x_pos - 0, "%c"  , x_id);
         }
         break;
      }
      rc = yMAP_by_cursor (YMAP_UNIV, YDLST_NEXT, &x_pos, &x_ref, NULL, &x_used);
      ++i;
   }
   DEBUG_GRAF   yLOG_value   ("x_usr"     , x_usr);
   DEBUG_GRAF   yLOG_value   ("x_sys"     , x_sys);
   if (x_disp == x_extra) {
      yVICURSES_by_name ("u_back");
      strlpadn (x_usr, t, '.', '>', 2);
      mvprintw (x_bott, x_left + 4, "%s", t);
      strlpadn (x_sys, t, '.', '>', 1);
      mvprintw (x_bott, x_left + 8, "%s", t);

   }
   /*---(complete)-----------------------*/
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
   DEBUG_GRAF   yLOG_complex  ("content"   , "%c å%sæ", m, t);
   /*> strlcpy (l, "JESUS", LEN_LABEL);                                               <*/
   DEBUG_GRAF   yLOG_info     ("label"     , l);
   DEBUG_GRAF   yLOG_info     ("format"    , f);
   /*---(draw)---------------------------*/
   if (a_part == YVIEW_COMMAND && x_edit != 'y') {
      x_len = strlen (yMODE_message ());
      if (x_len < x_wide)  mvprintw (x_bott, x_left, "%-*.*s" , x_wide - 1, x_wide - 1, yMODE_message ());
      else                 mvprintw (x_bott, x_left, "%-*.*s¬", x_wide - 1, x_wide - 1, yMODE_message ());
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
            mvprintw (x_bott, x_left, "%-4.4s %c%-*.*s ", "····", G_CHAR_NULL, a - 1, a - 1, YSTR_EMPTY);
         } else {
            strlpadn (n, nn, '.', '>', 4);
            mvprintw (x_bott, x_left, "%s %-*.*s ", nn, a, a, t + b);
         }
         break;
      case 'l' :
         x_off = 12;
         if (n == 0) {
            mvprintw (x_bott, x_left, " %-6.6s %-4.4s %c%-*.*s ", l, "····", G_CHAR_NULL, a - 1, a - 1, YSTR_EMPTY);
         } else {
            strlpadn (n, nn, '.', '>', 4);
            mvprintw (x_bott, x_left, " %-6.6s %s %-*.*s ", l, nn, a, a, t + b);
         }
         break;
      case 'x' :
         x_off = 13 + strlen (f);
         if (n == 0) {
            mvprintw (x_bott, x_left, " %-6.6s %s %-4.4s %c%-*.*s ", l, f, "····", G_CHAR_NULL, a - 1, a - 1, YSTR_EMPTY);
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
      else          x_mark = 'å';
      mvprintw (x_bott, x_left + x_off, "%c", x_mark);
   }
   /*---(update offset)------------------*/
   ++x_off;
   /*---(end marker)---------------------*/
   if (n != 0) {
      x_len = e - b + 1;
      if (e != n - 1) x_mark = '>';
      else            x_mark = 'æ';
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
   yvicurses__display (YVIEW_FORMULA, YVIEW_FORMULA, yVIEW_formula ());
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


