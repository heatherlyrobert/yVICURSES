/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVICURSES.h"
#include    "yVICURSES_priv.h"


static  char  s_fade = '-';

/*====================------------------------------------====================*/
/*===----                      menu focused                            ----===*/
/*====================------------------------------------====================*/
static void  o___MENU____________o () { return; }

char
yvicurses_notes_grid    (short a_minx, short a_miny, short a_maxx, short a_maxy)
{
   short       xm, ym;
   short       xu, yu;
   short       xl, yl;
   float       xi, yi;
   float       xn, yn;
   float       xc, yc;
   short       x            =    0;
   short       y            =    0;
   char       *x_norm       = "123456789";
   char       *x_fine       = "ZYXWVUTSRQPONMLKJIHGFEDCBA*abcdefghijklmnopqrstuvwxyz";
   /*---(set up y)-----------------------*/
   ym = round ((a_maxy - a_miny - 1) * 0.50 + a_miny);
   yu = round ((a_maxy - a_miny - 1) * 0.10 + a_miny);
   yl = round ((a_maxy - a_miny - 1) * 0.90 + a_miny);
   yi = (a_maxy - a_miny - 1) / 52.0;
   yn = (a_maxy - a_miny - 1) /  8.0;
   yc = a_miny;
   ym++;
   yu++;
   yl++;
   /*---(set up x)-----------------------*/
   xm = round ((a_maxx - a_minx - 1) * 0.50 + a_minx);
   xu = round ((a_maxx - a_minx - 1) * 0.10 + a_minx);
   xl = round ((a_maxx - a_minx - 1) * 0.90 + a_minx);
   xi = (a_maxx - a_minx - 1) / 52.0;
   xn = (a_maxx - a_minx - 1) /  8.0;
   xc = a_minx;
   /*---(display x)----------------------*/
   for (x = 0, xc = a_minx; xc <= a_maxx; xc++) {
      mvprintw (ym, round (xc), " ");
      mvprintw (yu, round (xc), " ");
      mvprintw (yl, round (xc), " ");
      ++x;
   }
   for (x = 0, xc = a_minx; xc <= a_maxx; xc += xi) {
      mvprintw (ym, round (xc), "%c", x_fine [x]);
      mvprintw (yu, round (xc), "%c", x_fine [x]);
      mvprintw (yl, round (xc), "%c", x_fine [x]);
      ++x;
   }
   for (x = 0, xc = a_minx; xc <= a_maxx; xc += xn) {
      if (x != 4)  mvprintw (ym - 1, round (xc), "%c", x_norm [x]);
      ++x;
   }
   /*---(display y)----------------------*/
   for (y = 0, yc = a_maxy; yc >= a_miny; yc--) {
      mvprintw (round (yc), xm, " ");
      mvprintw (round (yc), xu, " ");
      mvprintw (round (yc), xl, " ");
      ++y;
   }
   for (y = 0, yc = a_maxy; yc >= a_miny; yc -= yi) {
      mvprintw (round (yc), xm, "%c", x_fine [y]);
      mvprintw (round (yc), xu, "%c", x_fine [y]);
      mvprintw (round (yc), xl, "%c", x_fine [y]);
      ++y;
   }
   for (y = 0, yc = a_miny; yc <= a_maxy; yc += yn) {
      if (y != 4)  mvprintw (round (yc) + 1, xm - 1, "%c", x_norm [y]);
      ++y;
   }
   /*---(intersections)------------------*/
   mvprintw (yu, xu, "´");
   mvprintw (yu, xm, "´");
   mvprintw (yu, xl, "´");
   mvprintw (yl, xu, "´");
   mvprintw (yl, xm, "´");
   mvprintw (yl, xl, "´");
   mvprintw (ym, xu, "´");
   mvprintw (ym, xm, "´");
   mvprintw (ym, xl, "´");
   /*---(complete)-----------------------*/
   return 0;
}

char
yvicurses_notes_draw    (short x, short y, uchar w, uchar h, uchar *t)
{
   int         x_align     =    0;
   int         x_full, x_len;
   int         x_beg, x_next, x_cr;
   int         x_edge      =    8;
   int         i, j;
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(clear out)----------------------*/
   for (i = y; i < y + h; ++i) {
      mvprintw   (i, x, "%*.*s", w, w, YSTR_EMPTY);
   }
   /*---(opengl)-------------------------*/
   strlcpy (t, t, LEN_RECD);
   x_edge = 1;
   x_beg  = x_next  = 0;
   x_full = strlen (t);
   for (i = 0; i < h; ++i) {
      x_len = strlen (t + x_beg);
      p = strchr (t + x_beg, (uchar) '¨');
      DEBUG_GRAF   yLOG_complex ("x_beg"     ,  "%di, %3dn, %3dlå%sæ, %p", i, x_beg, x_len, t + x_beg, p);
      if (p != NULL)  x_cr = (int) p - (int) t;
      if (w > 3)  x_next = x_beg + w - 3;
      else        x_next = x_beg + 3;
      if (p != NULL && x_cr < x_next)  x_next = x_cr;
      DEBUG_GRAF   yLOG_complex ("x_next"    ,  "%3db, %3dw, %3dn, %3dc", x_beg, w, x_next, x_cr);
      if (x_next != x_cr) {
         for (j = x_next; j > x_beg; --j) {
            DEBUG_GRAF   yLOG_complex ("check"     , "%2d %c", j, t [j]);
            if (strchr ("- ", t [j]) == NULL)  continue;
            t [j] = '\0';
            x_next = j + 1;
            break;
         }
         x_len = strlen (t + x_beg);
         if (x_len >= w)  t [w - 1] = '\0';
      } else {
         t [x_cr] = '\0';
         x_len = strlen (t + x_beg);
         ++x_next;
      }
      mvprintw (y + i, x + ((w - x_len) / 2), "%s", t + x_beg);
      x_beg = x_next;
      if (x_beg > x_full) break;
   }
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvicurses_notes_line    (char a_curr, char c, short xb, short yb, short xe, short ye)
{
   char        rce         =  -10;
   int         i           =    0;
   char        x_vert      [LEN_TERSE]  =  "";
   char        x_horz      [LEN_TERSE]  =  "€";
   char        x_beg       [LEN_TERSE]  =  "³";
   char        x_end       [LEN_TERSE]  =  "Ï";
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("args"       , "%c  %4dx %4dy  %4dx %4dy", c, xb, yb, xe, ye);
   if (c == '-')  {
      DEBUG_GRAF   yLOG_note    ("no connector requested");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (c == 'H')  {
      DEBUG_GRAF   yLOG_note    ("connecting line hidden by its own box");
      yVICURSES_by_name ("n_badd");
      mvprintw (ye, xe    , "Ï");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   --rce;  if (strchr ("12345678", c) == NULL) {
      DEBUG_GRAF   yLOG_note    ("connector direction not understood");
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(origin)-------------------------*/
   if (a_curr)    yVICURSES_by_name ("n_line");
   else           yVICURSES_by_name ("n_dark");
   if (!a_curr && s_fade == 'y') {
      if (strchr ("Ô18Õ45", c) != NULL)  strcpy (x_beg , "Œ");
      else                               strcpy (x_beg , "²");
      strcpy (x_vert, "Œ");
      strcpy (x_horz, "²");
      strcpy (x_end , "á");
   }
   mvprintw (yb, xb, x_beg);
   /*---(first leg)----------------------*/
   switch (c) {
   case 'Ô' : case '1' : case '8' :
      DEBUG_GRAF   yLOG_note    ("up first (1,8)");
      for (i = yb - 1; i > ye; --i)  mvprintw (i , xb, x_vert);
      break;
   case 'Õ' : case '4' : case '5' :
      DEBUG_GRAF   yLOG_note    ("down first (4,5)");
      for (i = yb + 1; i < ye; ++i)  mvprintw (i , xb, x_vert);
      break;
   case '×' : case '6' : case '7' :
      DEBUG_GRAF   yLOG_note    ("left first (6.7)");
      for (i = xb - 1; i > xe; --i)  mvprintw (yb, i , x_horz);
      break;
   case 'Ö' : case '2' : case '3' :
      DEBUG_GRAF   yLOG_note    ("right first (2,3)");
      for (i = xb + 1; i < xe; ++i)  mvprintw (yb, i , x_horz);
      break;
   default  :
      break;
   }
   /*---(turn symbol)--------------------*/
   switch (c) {
   case '1' :  mvprintw (ye, xb    , "ƒ");  break;
   case '2' :  mvprintw (yb, xe    , "…");  break;
   case '3' :  mvprintw (yb, xe    , "‚");  break;
   case '4' :  mvprintw (ye, xb    , "„");  break;
   case '5' :  mvprintw (ye, xb    , "…");  break;
   case '6' :  mvprintw (yb, xe    , "ƒ");  break;
   case '7' :  mvprintw (yb, xe    , "„");  break;
   case '8' :  mvprintw (ye, xb    , "‚");  break;
   }
   /*---(second leg)---------------------*/
   switch (c) {
   case '1' : case '4' :
      DEBUG_GRAF   yLOG_note    ("right second (1,4)");
      for (i = xb + 1; i < xe; ++i)  mvprintw (ye, i , x_horz);
      break;
   case '2' : case '7' :
      DEBUG_GRAF   yLOG_note    ("up second (2,7)");
      for (i = yb - 1; i > ye; --i)  mvprintw (i , xe, x_vert);
      break;
   case '3' : case '6' :
      DEBUG_GRAF   yLOG_note    ("down second (3,6)");
      for (i = yb + 1; i < ye; ++i)  mvprintw (i , xe, x_vert);
      break;
   case '5' : case '8' :
      DEBUG_GRAF   yLOG_note    ("left second (5,8)");
      for (i = xb - 1; i > xe; --i)  mvprintw (ye, i , x_horz);
      break;
   }
   /*---(final point)--------------------*/
   mvprintw (ye, xe    , x_end);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvicurses_notes         (void)
{
   char        rc          =    0;
   int         i           =    0;
   short       x, y;
   uchar       m, s, w, h;
   uchar       t           [LEN_HUND]  = "";
   uchar       c;
   short       xb, yb, xe, ye;
   char        x_curr      =  'Y';
   char        x_prev      =  'y';
   char        x_lcurr     =  'Y';
   char        x_lprev     =  'y';
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   if (yVIEW_note_showing () == 0) {
      DEBUG_GRAF   yLOG_note    ("note showing mode is OFF");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_GRAF   yLOG_note    ("note showing mode is ON");
   yVIEW_note_colors (&x_curr, &x_prev, &x_lcurr, &x_lprev);
   DEBUG_GRAF   yLOG_char    ("x_lcurr"   , x_lcurr);
   DEBUG_GRAF   yLOG_char    ("x_lprev"   , x_lprev);
   yVICURSES_color ("n_curr", NULL, tolower (x_curr), toupper (x_curr));
   yVICURSES_color ("n_prev", NULL, toupper (x_prev), tolower (x_prev));
   s_fade = '-';
   if (x_lprev == ':')  {
      s_fade = 'y';
      x_lprev = x_lcurr;
   }
   yVICURSES_color ("n_line", NULL, x_lcurr, '-');
   yVICURSES_color ("n_dark", NULL, x_lprev, '-');
   for (i = 0; i < 20; ++i) {
      rc = yVIEW_note_data (i, &m, &s, &x, &y, &w, &h, t, &c, &xb, &yb, &xe, &ye);
      if (rc < 0)  break;
      DEBUG_GRAF   yLOG_complex  ("note"      , "%2di, %2dm, %4dx, %4dw, %4dy, %4dh, %c, %s", i, m, x, w, y, h, s, t);
      if (s == (uchar) '|') {
         DEBUG_GRAF   yLOG_note    ("target grid");
         yVICURSES_by_name ("n_grid");
         yvicurses_notes_grid (x, y, x + w, y + h);
         continue;
      } else if (s == ')') {
         DEBUG_GRAF   yLOG_note    ("title type");
         yVICURSES_by_name ("n_main");
      } else if (s == '!') {
         DEBUG_GRAF   yLOG_note    ("warning type");
         yVICURSES_by_name ("n_warn");
      } else if (i == m) {
         DEBUG_GRAF   yLOG_note    ("current type");
         yVICURSES_by_name ("n_curr");
      } else {
         DEBUG_GRAF   yLOG_note    ("previous type");
         yVICURSES_by_name ("n_prev");
      }
      if (s != '~')  yvicurses_notes_draw (x, y, w, h, t);
      yvicurses_notes_line (i == m, c, xb, yb, xe, ye);
   }
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}
