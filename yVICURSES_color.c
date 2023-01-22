/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVICURSES.h"
#include    "yVICURSES_priv.h"



tBASIC  g_primary [MAX_PRIMARY] = {
   {  '-' , "trn" , "transparent"     , -1                },
   {  'k' , "blk" , "black"           , COLOR_BLACK       },
   {  'r' , "red" , "d.red"           , COLOR_RED         },
   {  'g' , "grn" , "d.green"         , COLOR_GREEN       },
   {  'y' , "yel" , "d.yellow"        , COLOR_YELLOW      },
   {  'b' , "blu" , "d.blue"          , COLOR_BLUE        },
   {  'm' , "mag" , "d.magenta"       , COLOR_MAGENTA     },
   {  'c' , "cyn" , "d.cyan"          , COLOR_CYAN        },
   {  'w' , "whi" , "brown"           , COLOR_WHITE       },
   {  'K' , "BLK" , "grey"            , COLOR_BLACK       },
   {  'R' , "RED" , "l.red"           , COLOR_RED         },
   {  'G' , "GRN" , "l.green"         , COLOR_GREEN       },
   {  'Y' , "YEL" , "l.yellow"        , COLOR_YELLOW      },
   {  'B' , "BLU" , "l.blue"          , COLOR_BLUE        },
   {  'M' , "MAG" , "l.magenta"       , COLOR_MAGENTA     },
   {  'C' , "CYN" , "l.cyan"          , COLOR_CYAN        },
   {  'W' , "WHI" , "white"           , COLOR_WHITE       },
   {  0   , "---" , "end-of-colors"   , -1                },
};


tCOLOR       g_colors [MAX_COLOR];
int          g_ncolor  = 0;
char         g_print       [LEN_RECD]  = "";



/*====================------------------------------------====================*/
/*===----                        finding colors                        ----===*/
/*====================------------------------------------====================*/
static void      o___SEARCH__________________o (void) {;}

char
yvicurses__by_abbr      (char a_abbr)
{
   char        rce         =  -10;
   int         i           =    0;
   DEBUG_GRAF  yLOG_senter  (__FUNCTION__);
   DEBUG_GRAF  yLOG_schar   (a_abbr);
   for (i = 0; i < MAX_PRIMARY; ++i) { 
      if (g_primary [i].abbr == 0)                break;
      if (g_primary [i].abbr != a_abbr)           continue;
      DEBUG_GRAF  yLOG_snote   ("found");
      DEBUG_GRAF  yLOG_sint    (i);
      DEBUG_GRAF  yLOG_sinfo   ("name"      , g_primary [i].terse);
      DEBUG_GRAF  yLOG_sexit   (__FUNCTION__);
      return i;
   }
   DEBUG_GRAF  yLOG_snote   ("FAIL, not found");
   DEBUG_GRAF  yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

char
yvicurses__primary      (char a_abbr)
{
   int         i           =    0;
   i = yvicurses__by_abbr (a_abbr);
   if (i < 0)  return i;
   return g_primary [i].value;
}

char*
yVICURSES_primary       (char a_abbr)
{
   int         i           =    0;
   DEBUG_GRAF  yLOG_enter   (__FUNCTION__);
   /*> strcpy (g_print, "n/a");                                                       <*/
   i = yvicurses__by_abbr (a_abbr);
   DEBUG_GRAF  yLOG_value   ("i"         , i);
   if (i < 0)  return "n/a";
   sprintf (g_print, "%c  %-5.5s %2d  %s", a_abbr,
         g_primary [i].terse, g_primary [i].value, g_primary [i].desc);
   DEBUG_GRAF  yLOG_exit    (__FUNCTION__);
   return g_print;
}

char
yvicurses__by_name      (char *a_terse)
{
   char        rce         =  -10;
   int         i           =    0;
   DEBUG_GRAF  yLOG_senter  (__FUNCTION__);
   DEBUG_GRAF  yLOG_spoint  (a_terse);
   --rce;  if (a_terse == NULL) {
      DEBUG_GRAF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   for (i = 0; i < g_ncolor; ++i) {
      if (g_colors [i].terse [0] != a_terse [0])       continue;
      if (strcmp (g_colors [i].terse, a_terse) != 0)   continue;
      DEBUG_GRAF  yLOG_snote   ("found");
      DEBUG_GRAF  yLOG_sint    (i);
      DEBUG_GRAF  yLOG_sexit   (__FUNCTION__);
      return i;
   }
   DEBUG_GRAF  yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

char*
yvicurses__by_pair      (int a_pair)
{
   char        rce         =  -10;
   int         i           =    0;
   for (i = 0; i < g_ncolor; ++i) {
      if (g_colors [i].value != a_pair)                continue;
      sprintf (g_print, "%-8.8s f=%c b=%c  %s",
      g_colors [i].terse, g_colors [i].fg, g_colors [i].bg, g_colors [i].desc);
      return g_print;
   }
   return "n/a";
}



/*====================------------------------------------====================*/
/*===----                        creating colors                       ----===*/
/*====================------------------------------------====================*/
static void      o___CREATE__________________o (void) {;}

char
yVICURSES_color         (char *a_terse, char *a_desc, char a_fg, char a_bg)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   int         x_fg        =    0;
   int         x_bg        =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_GRAF  yLOG_point   ("a_terse"   , a_terse);
   --rce;  if (a_terse == NULL) {
      DEBUG_GRAF  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF  yLOG_info    ("a_terse"   , a_terse);
   /*---(identify)-----------------------*/
   n = yvicurses__by_name (a_terse);
   if (n <  0) {
      n = g_ncolor;
      DEBUG_GRAF  yLOG_value   ("new"       , n);
   } else {
      DEBUG_GRAF  yLOG_value   ("existing"  , n);
   }
   DEBUG_GRAF  yLOG_info    ("terse"     , a_terse);
   /*---(retrieve primaries)-------------*/
   x_fg = yvicurses__primary  (a_fg);
   if (x_fg < -1)   x_fg  = yvicurses__primary  ('w');
   x_bg = yvicurses__primary  (a_bg);
   if (x_bg < -1)   x_bg  = yvicurses__primary  ('-');
   /*---(save)---------------------------*/
   strlcpy (g_colors [n].terse, a_terse, LEN_LABEL);
   if (a_desc != NULL)  strlcpy (g_colors [n].desc, a_desc, LEN_DESC);
   g_colors [n].fg    = a_fg;
   g_colors [n].bg    = a_bg;
   DEBUG_GRAF  yLOG_value   ("fg"        , g_colors [n].fg);
   DEBUG_GRAF  yLOG_value   ("bg"        , g_colors [n].bg);
   /*---(create)-------------------------*/
   init_pair (n + 20, x_fg, x_bg);
   g_colors [n].value = COLOR_PAIR (n + 20);
   /*---(update)-------------------------*/
   if (n == g_ncolor)  ++g_ncolor;
   DEBUG_GRAF  yLOG_value   ("g_ncolor"  , g_ncolor);
   /*---(complete)-----------------------*/
   DEBUG_GRAF  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          using colors                        ----===*/
/*====================------------------------------------====================*/
static void      o___USING___________________o (void) {;}

char
yVICURSES_by_name       (char *a_terse)
{
   int         n           = 0;
   char        rce         =  -10;
   attrset (0);
   n = yvicurses__by_name (a_terse);
   if (n < 0)  return -1;
   if (g_colors [n].fg != tolower (g_colors [n].fg)) attron (A_BOLD);
   if (g_colors [n].bg != tolower (g_colors [n].bg)) attron (A_BLINK);
   if (g_colors [n].bg == '!'                      ) attron (A_REVERSE);
   attron  (g_colors [n].value);
   return 0;
}

char*
yVICURSES_at_loc        (short x, short y)
{
   long  x_loc  = mvwinch (stdscr, y, x);
   uchar x_ch   = x_loc & A_CHARTEXT;
   int   x_attr = x_loc & A_ATTRIBUTES;
   int   x_col  = x_loc & A_COLOR;
   int   x_left = x_attr - x_col;
   char  b, B, u;
   char  t [LEN_HUND] = "";
   switch (x_left) {
   case  A_NORMAL               :  b = '-';  u = '-';  B = '-';     break;
   case  A_BOLD                 :  b = 'y';  u = '-';  B = '-';     break;
   case  A_UNDERLINE            :  b = '-';  u = 'y';  B = '-';     break;
   case  A_BLINK                :  b = '-';  u = '-';  B = 'y';     break;
   case  A_BOLD  | A_UNDERLINE  :  b = 'y';  u = 'y';  B = '-';     break;
   case  A_BLINK | A_UNDERLINE  :  b = '-';  u = 'y';  B = 'y';     break;
   case  A_BLINK | A_BOLD       :  b = 'y';  u = '-';  B = 'y';     break;
   }
   strlcpy (t, yvicurses__by_pair (x_col), LEN_HUND);
   sprintf (g_print, "%3dx %3dy   %8d   %c %3d   %8d %c %c %c   %8d %s",
         x, y, x_loc, chrvisible (x_ch), x_ch,
         x_attr, b, B, u, x_col, t);
   return g_print;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [gc.842.031.62]*/ /*-[02.0000.014.!]-*/ /*-[--.---.---.--]-*/
yvicurses_color_init_OLD(void)
{
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(globals)------------------------*//*-------------------------------------------------fg----bg--*/
   g_ncolor = 0;
   /*---(window parts)-------------------*/
   yVICURSES_color  ("w_titl"    , "window, normal title"                               , 'k' , 'K' );
   yVICURSES_color  ("w_vers"    , "window, version number"                             , 'k' , 'K' );
   yVICURSES_color  ("w_sbar"    , "window, normal status"                              , 'k' , '!' );
   yVICURSES_color  ("w_cmds"    , "window, command message"                            , 'y' , '-' );
   yVICURSES_color  ("w_keys"    , "window, keystoke display"                           , 'r' , '-' );
   /*---(universes)----------------------*/
   yVICURSES_color  ("u_back"    , "window, universe/buffers"                           , 'K' , 'k' );
   yVICURSES_color  ("u_curr"    , "window, universe/buffers"                           , 'Y' , 'k' );
   yVICURSES_color  ("u_used"    , "window, universe/buffers"                           , 'G' , 'k' );
   yVICURSES_color  ("u_place"   , "window, universe/buffers"                           , 'R' , 'k' );
   /*---(trouble)------------------------*/
   yVICURSES_color  ("!_warn"    , "trouble, warning"                                   , 'w' , 'R' );
   yVICURSES_color  ("!_errs"    , "trouble, error"                                     , 'W' , 'R' );
   /*---(formula modes)------------------*/
   yVICURSES_color  ("i_maps"    , "map mode (2d review of sheet/cell collection"       , 'k' , 'Y' );
   yVICURSES_color  ("i_srcs"    , "source mode (single cell review)"                   , 'k' , 'G' );
   yVICURSES_color  ("i_treg"    , "text register sub-mode"                             , 'k' , 'C' );
   yVICURSES_color  ("i_inpt"    , "input sub-mode"                                     , 'k' , 'B' );
   yVICURSES_color  ("i_repl"    , "replace sub-mode"                                   , 'k' , 'M' );
   yVICURSES_color  ("i_wand"    , "wander sub-mode"                                    , 'k' , 'R' );
   yVICURSES_color  ("i_sele"    , "source mode text selection"                         , 'k' , 'W' );
   /*---(visual)---------*/
   yVICURSES_color  ("v_curr"    , "current cell"                                       , 'k' , 'Y' );
   yVICURSES_color  ("v_root"    , "root of visual selection"                           , 'K' , 'k' );
   yVICURSES_color  ("v_fill"    , "selected, not root/curr"                            , 'Y' , 'y' );
   /*---(marking)--------*/
   yVICURSES_color  ("m_hint"    , "marks for extended hinting"                         , 'C' , 'c' );
   yVICURSES_color  ("m_temp"    , "marks for temporary locations"                      , 'Y' , 'y' );
   yVICURSES_color  ("m_srch"    , "marks for search results"                           , 'R' , 'r' );
   /*---(menus)----------*/
   yVICURSES_color  ("m_back"    , "menu, background"                                   , 'k' , '!' );
   yVICURSES_color  ("m_cent"    , "menu, center webbing"                               , 'c' , 'k' );
   yVICURSES_color  ("m_bull"    , "menu, bullet"                                       , 'C' , 'k' );
   yVICURSES_color  ("m_menu"    , "menu, normal item"                                  , 'G' , 'k' );
   yVICURSES_color  ("m_cant"    , "menu, item not available"                           , 'w' , 'y' );
   yVICURSES_color  ("m_errs"    , "menu, item in error"                                , 'R' , 'y' );
   /*---(overlays)-------*/
   yVICURSES_color  ("m_main"    , "note, main title/subject"                           , 'W' , 'M' );
   yVICURSES_color  ("m_warn"    , "note, displaying a warning"                         , 'W' , 'R' );
   yVICURSES_color  ("m_curr"    , "note, current note item"                            , 'k' , 'Y' );
   yVICURSES_color  ("m_prev"    , "note, old note item"                                , 'Y' , 'y' );
   /*---(headers)--------*/
   yVICURSES_color  ("h_curr"    , "header (row/col) current"                           , 'k' , 'y' );
   yVICURSES_color  ("h_lock"    , "header (row/col) locked in place"                   , 'k' , 'r' );
   yVICURSES_color  ("h_used"    , "header (row/col) with used cells"                   , 'y' , 'k' );
   yVICURSES_color  ("h_norm"    , "header (row/col) normal"                            , 'y' , '-' );
   /*---(dependencies)---*/
   yVICURSES_color  ("d_reqs"    , "depends, current cell uses this value"              , 'M' , 'm' );
   yVICURSES_color  ("d_pros"    , "depends, provides a value to current cell"          , 'G' , 'g' );
   yVICURSES_color  ("d_like"    , "depends, adapts formula from current cell"          , 'B' , 'b' );
   /*---(cell types)-----*/
   yVICURSES_color  ("9_norm"   , "numeric, literal"                                    , 'B' , '-' );
   yVICURSES_color  ("9_form"   , "numeric, formula"                                    , 'G' , '-' );
   yVICURSES_color  ("9_dang"   , "numeric, complex/dangerous formula"                  , 'R' , '-' );
   yVICURSES_color  ("9_like"   , "numeric, formula adapted from elsewhere"             , 'w' , '-' );
   yVICURSES_color  ("#_norm"   , "string, literal"                                     , 'Y' , '-' );
   yVICURSES_color  ("#_form"   , "string, formula"                                     , 'M' , '-' );
   yVICURSES_color  ("#_dang"   , "string, complex/dangerous formula"                   , 'R' , '-' );
   yVICURSES_color  ("#_like"   , "string, formula adapted from elsewhere"              , 'w' , '-' );
   yVICURSES_color  ("p_rang"   , "range pointer"                                       , 'C' , '-' );
   yVICURSES_color  ("p_addr"   , "address pointer"                                     , 'C' , '-' );
   /*---(other)----------*/
   yVICURSES_color  (">_null"   , "blank cell"                                          , 'b' , '-' );
   yVICURSES_color  (">_unkn"   , "default for unidentified cells"                      , 'Y' , '-' );
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gc.842.031.62]*/ /*-[02.0000.014.!]-*/ /*-[--.---.---.--]-*/
yvicurses_color_init    (void)
{
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(globals)------------------------*//*-------------------------------------------------fg----bg--*/
   g_ncolor = 0;
   /*---(window parts)-------------------*/
   yVICURSES_color  ("w_titl"    , "window, normal title"                               , 'k' , 'K' );
   yVICURSES_color  ("w_vers"    , "window, version number"                             , 'k' , 'K' );
   yVICURSES_color  ("w_sbar"    , "window, normal status"                              , 'k' , 'K' );
   yVICURSES_color  ("w_cmds"    , "window, command message"                            , 'K' , '-' );
   yVICURSES_color  ("w_keys"    , "window, keystoke display"                           , 'K' , 'k' );
   /*---(universes)----------------------*/
   yVICURSES_color  ("u_back"    , "window, universe/buffers"                           , 'K' , 'k' );
   yVICURSES_color  ("u_curr"    , "window, universe/buffers"                           , 'C' , 'k' );
   yVICURSES_color  ("u_used"    , "window, universe/buffers"                           , 'G' , 'k' );
   yVICURSES_color  ("u_place"   , "window, universe/buffers"                           , 'R' , 'k' );
   /*---(trouble)------------------------*/
   yVICURSES_color  ("!_warn"    , "trouble, warning"                                   , 'w' , 'R' );
   yVICURSES_color  ("!_errs"    , "trouble, error"                                     , 'R' , 'r' );
   /*---(formula modes)------------------*/
   yVICURSES_color  ("i_maps"    , "map mode (2d review of sheet/cell collection"       , 'k' , 'K' );
   yVICURSES_color  ("i_srcs"    , "source mode (single cell review)"                   , 'k' , 'G' );
   yVICURSES_color  ("i_treg"    , "text register sub-mode"                             , 'k' , 'C' );
   yVICURSES_color  ("i_inpt"    , "input sub-mode"                                     , 'k' , 'B' );
   yVICURSES_color  ("i_repl"    , "replace sub-mode"                                   , 'k' , 'M' );
   yVICURSES_color  ("i_wand"    , "wander sub-mode"                                    , 'k' , 'R' );
   yVICURSES_color  ("i_sele"    , "source mode text selection"                         , 'k' , 'W' );
   /*---(visual)---------*/
   yVICURSES_color  ("v_curr"    , "current cell"                                       , 'k' , 'Y' );
   yVICURSES_color  ("v_root"    , "root of visual selection"                           , 'K' , 'k' );
   yVICURSES_color  ("v_fill"    , "selected, not root/curr"                            , 'Y' , 'y' );
   /*---(marking)--------*/
   yVICURSES_color  ("m_hint"    , "marks for extended hinting"                         , 'C' , 'c' );
   yVICURSES_color  ("m_temp"    , "marks for temporary locations"                      , 'Y' , 'y' );
   yVICURSES_color  ("m_srch"    , "marks for search results"                           , 'R' , 'r' );
   /*---(menus)----------*/
   yVICURSES_color  ("m_back"    , "menu, background"                                   , 'K' , 'k' );
   yVICURSES_color  ("m_edge"    , "menu, outside edge"                                 , 'K' , 'k' );
   yVICURSES_color  ("m_cent"    , "menu, center webbing"                               , 'K' , 'k' );
   yVICURSES_color  ("m_bull"    , "menu, bullet"                                       , 'C' , 'k' );
   yVICURSES_color  ("m_menu"    , "menu, normal item"                                  , 'G' , 'k' );
   yVICURSES_color  ("m_cant"    , "menu, item not available"                           , 'w' , 'k' );
   yVICURSES_color  ("m_errs"    , "menu, item in error"                                , 'R' , 'k' );
   /*---(overlays)-------*/
   yVICURSES_color  ("n_main"    , "note, main title/subject"                           , 'c' , 'C' );
   yVICURSES_color  ("n_warn"    , "note, displaying a warning"                         , 'R' , 'r' );
   yVICURSES_color  ("n_curr"    , "note, current note item"                            , 'y' , 'Y' );
   yVICURSES_color  ("n_prev"    , "note, old note item"                                , 'Y' , 'y' );
   yVICURSES_color  ("n_line"    , "note, connector line"                               , 'Y' , '-' );
   yVICURSES_color  ("n_dark"    , "note, connector line darkened"                      , 'y' , '-' );
   /*---(headers)--------*/
   yVICURSES_color  ("h_curr"    , "header (row/col) current"                           , 'C' , 'k' );
   yVICURSES_color  ("h_lock"    , "header (row/col) locked in place"                   , 'K' , 'r' );
   yVICURSES_color  ("h_used"    , "header (row/col) with used cells"                   , 'C' , '-' );
   yVICURSES_color  ("h_norm"    , "header (row/col) normal"                            , 'K' , '-' );
   /*---(dependencies)---*/
   yVICURSES_color  ("d_reqs"    , "depends, current cell uses this value"              , 'M' , 'm' );
   yVICURSES_color  ("d_pros"    , "depends, provides a value to current cell"          , 'G' , 'g' );
   yVICURSES_color  ("d_like"    , "depends, adapts formula from current cell"          , 'B' , 'b' );
   yVICURSES_color  ("d_copy"    , "all cells that copy the current one"                , 'W' , 'w' );
   /*---(cell types)-----*/
   yVICURSES_color  ("9_norm"   , "numeric, literal"                                    , 'B' , '-' );
   yVICURSES_color  ("9_form"   , "numeric, formula"                                    , 'G' , '-' );
   yVICURSES_color  ("9_dang"   , "numeric, complex/dangerous formula"                  , 'R' , '-' );
   yVICURSES_color  ("9_like"   , "numeric, formula adapted from elsewhere"             , 'W' , '-' );
   yVICURSES_color  ("#_norm"   , "string, literal"                                     , 'K' , '-' );
   yVICURSES_color  ("#_form"   , "string, formula"                                     , 'M' , '-' );
   yVICURSES_color  ("#_dang"   , "string, complex/dangerous formula"                   , 'R' , '-' );
   yVICURSES_color  ("#_like"   , "string, formula adapted from elsewhere"              , 'W' , '-' );
   yVICURSES_color  ("p_rang"   , "literal range pointer"                               , 'C' , '-' );
   yVICURSES_color  ("p_addr"   , "literal address pointer"                             , 'C' , '-' );
   yVICURSES_color  ("p_calc"   , "calculated address pointer"                          , 'C' , '-' );
   yVICURSES_color  ("p_vars"   , "variable pointer"                                    , 'Y' , '-' );
   /*---(agrios)---------*/
   yVICURSES_color  ("a_forc"   , "statement to update a value/string"                  , 'W' , '-' );
   yVICURSES_color  ("a_call"   , "statement to call a function"                        , 'C' , '-' );
   yVICURSES_color  ("a_curr"   , "agrios macro bouncing-ball tracker"                  , 'k' , 'C' );
   /*---(other)----------*/
   yVICURSES_color  (">_null"   , "blank cell"                                          , 'b' , '-' );
   yVICURSES_color  (">_unkn"   , "default for unidentified cells"                      , 'R' , '-' );
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvicurses_color_purge   (void)
{
   int         i           =    0;
   DEBUG_GRAF  yLOG_senter  (__FUNCTION__);
   DEBUG_GRAF  yLOG_sint    (g_ncolor);
   for (i = 0; i < MAX_COLOR; ++i) { 
      g_colors [i].terse [0] = '\0';
      g_colors [i].desc [0]  = '\0';
      g_colors [i].fg        = -1;
      g_colors [i].bg        = -1;
      g_colors [i].value     = -1;
   }
   g_ncolor = 0;
   DEBUG_GRAF  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gc.842.031.62]*/ /*-[02.0000.014.!]-*/ /*-[--.---.---.--]-*/
yvicurses_color_wrap    (void)
{
   return 0;
}


