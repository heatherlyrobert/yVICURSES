/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVICURSES.h"
#include    "yVICURSES_priv.h"



tMY         myVICURSES;



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
yVICURSES__wave_one     (char *a_title, char *a_version, char a_mode)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*----(first)-------------------------*/
   rc = yMODE_init           (a_mode);
   DEBUG_GRAF   yLOG_value   ("yMODE"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(TEMP)---------------------------*/
   rc = yFILE_init           ();
   DEBUG_GRAF   yLOG_value   ("yFILE"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yCMD_init            ();
   DEBUG_GRAF   yLOG_value   ("yCMD"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(early)-----------------------*/
   rc = yVIEW_init (YVIEW_CURSES, a_title, a_version, yvicurses_cleanse, yvicurses_prep, yvicurses_cursor, yvicurses_refresh);
   DEBUG_GRAF   yLOG_value   ("yVIEW"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*----(update sizes)------------------*/
   yvicurses_resize ();
   /*----(later)-------------------------*/
   rc = yKEYS_init           ();
   DEBUG_GRAF   yLOG_value   ("yKEYS"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yMAP_init            ();
   DEBUG_GRAF   yLOG_value   ("yMAP"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = ySRC_init            ();
   DEBUG_GRAF   yLOG_value   ("ySRC"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yMACRO_init          ();
   DEBUG_GRAF   yLOG_value   ("yMACRO"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yMARK_init           ();
   DEBUG_GRAF   yLOG_value   ("yMARK"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVICURSES__wave_two     (void)
{  /*---(note)---------------------------*/
   /*
    * this wave handles the inter-library calls after all are initialized
    * and yVIHUB is fully configured.
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*----(first)-------------------------*/
   rc = yMODE_init_after     ();
   DEBUG_GRAF   yLOG_value   ("yMODE"   , rc);
   rc = yFILE_init_after     ();
   DEBUG_GRAF   yLOG_value   ("yFILE"   , rc);
   rc = yCMD_init_after      ();
   DEBUG_GRAF   yLOG_value   ("yCMD"    , rc);
   rc = yVIEW_init_after     ();
   DEBUG_GRAF   yLOG_value   ("yVIEW"   , rc);
   rc = yKEYS_init_after     ();
   DEBUG_GRAF   yLOG_value   ("yKEYS"   , rc);
   rc = yMAP_init_after      ();
   DEBUG_GRAF   yLOG_value   ("yMAP"    , rc);
   rc = ySRC_init_after      ();
   DEBUG_GRAF   yLOG_value   ("ySRC"    , rc);
   rc = yMACRO_init_after    ();
   DEBUG_GRAF   yLOG_value   ("yMACRO"  , rc);
   rc = yMARK_init_after     ();
   DEBUG_GRAF   yLOG_value   ("yMARK"   , rc);
   /*---(complete)-----------------------*/
   rc = yCMD_add (YVIHUB_M_FORMAT, "winreset"    , ""    , ""      , yX11_reset                 , "change the width of columns"               );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winreset"    , ""    , ""      , yX11_reset                 , "move between window manager desktops"      );
   rc = yCMD_add (YVIHUB_M_FORMAT, "desktop"     , ""    , "c"     , yX11_desk_goto             , "move between window manager desktops"      );
   rc = yCMD_add (YVIHUB_M_FORMAT, "term"        , ""    , "a"     , yX11_yvikeys_term          , "create a terminal session"                 );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winname"     , ""    , "a"     , yX11_yvikeys_name          , "name an existing window"                   );
   rc = yCMD_add (YVIHUB_M_FORMAT, "sendkeys"    , ""    , "a"     , yX11_yvikeys_sendkeys      , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "blitzkeys"   , ""    , "a"     , yX11_yvikeys_blitzkeys     , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winexact"    , ""    , "cciiii", yX11_yvikeys_winexact      , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winplace"    , ""    , "a"     , yX11_yvikeys_winplace      , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winpush"     , ""    , "iiii"  , yX11_win_push              , "move a window temporarily and remember"    );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winpop"      , ""    , ""      , yX11_win_pop               , "put remembered (pushed) win back"          );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winbring"    , ""    , "c"     , yX11_yvikeys_winbring      , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "wingoto"     , ""    , "c"     , yX11_yvikeys_wingoto       , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winsend"     , ""    , "cc"    , yX11_yvikeys_winsend       , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "wintake"     , ""    , "cc"    , yX11_yvikeys_wintake       , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "mydesk"      , ""    , "c"     , yX11_yvikeys_mydesk        , "change position of current window"         );
   rc = yCMD_add (YVIHUB_M_FORMAT, "myhome"      , ""    , "ii"    , yX11_yvikeys_myhome        , "change position of current window"         );
   rc = yCMD_add (YVIHUB_M_FORMAT, "mysize"      , ""    , "ii"    , yX11_yvikeys_mysize        , "change size of current window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "mysizer"     , ""    , "iiii"  , yX11_yvikeys_mysizer       , "reset all desktops, windows, and shortcuts");
   /*---(extra)--------------------------*/
   rc = yMACRO_graphic_config (yVICURSES_draw_now, yVICURSES_screen_print);
   DEBUG_GRAF   yLOG_value   ("graphics", rc);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}


char
yVICURSES_init          (char *a_title, char *a_version, char a_mode)
{
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(setup ncurses)---------------*/
   initscr  ();     /* fire up ncurses with a default screen (stdscr)         */
   keypad   (stdscr, TRUE);
   raw      ();     /* read key-by-key rather than waiting for \n (raw mode)  */
   noecho   ();     /* don't automatically echo keypresses to the screen      */
   ESCDELAY = 0;    /* so escape responds immediately                         */
   nodelay  (stdscr, TRUE);
   clear    ();
   touchwin (stdscr);
   start_color          ();
   use_default_colors   ();
   use_legacy_coding    (2);       /* also display characters 128 - 156 */
   yvicurses_color_init ();
   myVICURSES.cursor = 'y';
   /*---(library inits)------------------*/
   rc = yVICURSES__wave_one (a_title, a_version, a_mode);
   DEBUG_GRAF   yLOG_value   ("wave one", rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yVICURSES__wave_two ();
   DEBUG_GRAF   yLOG_value   ("wave two", rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yMODE_results ();
   /*---(curses drawing)-----------------*/
   yVIEW_simple (YVIEW_TITLE  , 0, 0, yvicurses_title);
   yVIEW_simple (YVIEW_VERSION, 0, 0, yvicurses_version);
   yVIEW_simple (YVIEW_MODES  , 0, 0, yvicurses_modes);
   yVIEW_simple (YVIEW_STATUS , 0, 0, yvicurses_status);
   yVIEW_simple (YVIEW_COMMAND, 0, 0, yvicurses_command);
   yVIEW_simple (YVIEW_FORMULA, 0, 0, yvicurses_formula);
   yVIEW_simple (YVIEW_FLOAT  , 0, 0, yvicurses_float);
   yVIEW_simple (YVIEW_KEYS   , 0, 0, yvicurses_keys);
   yVIEW_simple (YVIEW_BUFFER , 0, 0, yvicurses_univs);
   yVIEW_simple (YVIEW_NOTES  , 0, 0, yvicurses_notes);
   yVIEW_simple (YVIEW_HISTORY, 0, 0, yvicurses_history);
   yVIEW_menus  (yvicurses_menus);
   rc = yCMD_add (YVIHUB_M_FORMAT, "redraw"      , ""    , ""     , yVICURSES_redraw           , "force redraw" );
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVICURSES_wrap                 (void)
{
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(shutdown ncurses)------------*/
   yFILE_wrap ();
   yCMD_wrap  ();
   yMAP_wrap  ();
   yMODE_wrap ();
   yvicurses_color_wrap ();
   endwin ();
   delscreen (stdscr);
   system ("clear");
   fflush (stdout);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVICURSES_main          (char *a_delay, char *a_update, void *a_altinput)
{
   return yKEYS_main (a_delay, a_update, 0, YVIEW_CURSES, yVIEW_draw, yvicurses_getch, a_altinput);
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNIT_TEST_______o () { return; }

char          unit_answer [LEN_FULL];

char       /*----: set up program urgents/debugging --------------------------*/
yvicurses__unit_quiet   (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yVICURSES_unit" };
   yMODE_init (MODE_MAP);
   yMODE_unit_handlers ();
   yVICURSES_init ("yVICURSES itself ;)", P_VERNUM, MODE_MAP);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yvicurses__unit_loud    (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yVICURSES_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_by_name  ("kitchen"      , YURG_ON);
   yURG_by_name  ("ystr"         , YURG_ON);
   yMODE_init (MODE_MAP);
   yMODE_unit_handlers ();
   DEBUG_PROG   yLOG_info     ("yVICURSES"  , yVICURSES_version   ());
   yVICURSES_init ("yVICURSES itself ;)", P_VERNUM, MODE_MAP);
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
yvicurses__unit_end     (void)
{
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   yVICURSES_wrap ();
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}

char*        /*-> tbd --------------------------------[ leaf   [gs.520.202.40]*/ /*-[01.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yVICURSES__unit         (char *a_question, char a_index)
{
   /*---(locals)-----------+-----+-----+-*/
   char        n           =    0;
   char        x_list      [LEN_RECD];
   char        t           [LEN_RECD];
   int         c           =    0;
   int         x_len       =    0;
   int         i           =    0;
   /*---(preprare)-----------------------*/
   strcpy  (unit_answer, "VICURSES         : question not understood");
   /*---(simple questions)---------------*/
   if      (strcmp (a_question, "rec"            )   == 0) {
      /*> if (g_rcurr < 0) snprintf (unit_answer, LEN_RECD, "MACRO rec    (%c) : macro pointer grounded", g_rname);       <* 
       *> else {                                                                                                          <* 
       *>    sprintf (t, "[%-.33s]", g_rkeys);                                                                            <* 
       *>    if (g_rlen > 33)  t [34] = '>';                                                                              <* 
       *>    snprintf (unit_answer, LEN_RECD, "MACRO rec    (%c) : %c %2d %2d%s", g_rname, g_rmode, g_rpos, g_rlen, t);   <* 
       *> }                                                                                                               <* 
       *> return unit_answer;                                                                                             <*/
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



