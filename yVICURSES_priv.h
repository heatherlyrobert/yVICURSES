/*============================----beg-of-source---============================*/
#ifndef yVICURSES_priv
#define yVICURSES_priv yes



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "us (user control)"
#define     P_SUBJECT   "curses specific logic"
#define     P_PURPOSE   "remove curses-specific dependency from vikeys libraries"

#define     P_NAMESAKE  "kharis-daimona (grace)"
#define     P_HERITAGE  "wife of hephaestus and youngest of the graces"
#define     P_IMAGERY   ""
#define     P_REASON    "curses is a simple, beautiful, and graceful solution"

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "yVICURSES"
#define     P_FULLPATH  "/usr/local/lib64/libyVICURSES"
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2021-11-09"

#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.0-, break out yVIKEYS into curses and opengl"
#define     P_VERNUM    "2.0w"
#define     P_VERTXT    "missed old chrvisible reference"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/

/*---(ansi-c standard)-------------------*/
#include    <stdio.h>             /* clibc  standard input/output             */
#include    <stdlib.h>            /* clibc  standard general purpose          */
#include    <string.h>            /* clibc  standard string handling          */
#include    <math.h>              /* clibc  standard math library             */
/*---(custom core)-----------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */
/*---(custom vikeys)---------------------*/
#include    <yVIHUB.h>            /* heatherly vikeys key handling            */
#include    <yKEYS.h>             /* heatherly vikeys key handling            */
#include    <yMODE.h>             /* heatherly vikeys mode tracking           */
#include    <yMACRO.h>            /* heatherly vikeys macro processing        */
#include    <ySRC.h>              /* heatherly vikeys source editing          */
#include    <yCMD.h>              /* heatherly vikeys command processing      */
#include    <yVIEW.h>             /* heatherly vikeys view management         */
#include    <yFILE.h>             /* heatherly vikeys content file handling   */
#include    <yMARK.h>             /* heatherly vikeys search and marking      */
#include    <yMAP.h>              /* heatherly vikeys location management     */
/*---(custom other)----------------------*/
#include    <yX11.h>              /* heatherly x-windows control              */
#include    <yDLST_solo.h>        /* heatherly double-double-list             */
/*---(posix standard)--------------------*/
#include    <ncurses.h>           /* CURSES mvprintw, refresh, getch, ...     */


#define     MAX_PRIMARY    20
typedef  struct cBASIC  tBASIC;
struct cBASIC {
   char        abbr;
   char        terse       [LEN_SHORT];
   char        desc        [LEN_LABEL];
   short       value;
};
extern tBASIC  g_primary [MAX_PRIMARY];


#define     MAX_COLOR   100
typedef  struct cCOLOR  tCOLOR;
struct cCOLOR {
   char        terse       [LEN_LABEL];     /* short description              */
   char        desc        [LEN_DESC ];     /* description/reason             */
   char        fg;                          /* foreground color               */
   char        bg;                          /* background color               */
   int         value;                       /* curses attribute value         */
};
extern tCOLOR  g_colors [MAX_COLOR];
extern int     g_ncolor;



typedef    struct    cMY    tMY;
struct cMY {
   int         wide;              /* maximum x-coordinate                    */
   int         tall;              /* maximum y-coordinate                    */
   int         x_cur;
   int         y_cur;
   int         x_menu;
   int         y_menu;
   char        redraw;
   char        cursor;
};
extern tMY         myVICURSES;



extern char g_print       [LEN_RECD];



/*===[[ yVICURSES_base.c ]]===================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        yVICURSES_init          (char *a_title, char *a_version, char a_mode);
char        yvicurses_color_purge   (void);
char        yVICURSES_wrap          (void);
char        yVICURSES_main          (char *a_delay, char *a_update, void *a_altinput);
/*---(unittest)-------------*/
char        yvicurses__unit_quiet   (void);
char        yvicurses__unit_loud    (void);
char        yvicurses__unit_end     (void);
/*---(done)-----------------*/
char*       yVICURSES__unit         (char *a_question, char a_index);



/*===[[ yVICURSES_base.c ]]===================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(resize)---------------*/
char        yvicurses_resize        (void);
/*---(input)----------------*/
char        yvicurses_getch         (char a_block, char *a_ch);
/*---(draw)-----------------*/
char        yvicurses_cleanse       (void);
char        yvicurses_prep          (char a_abbr);
char        yvicurses_cursor        (void);
char        yvicurses_refresh       (void);
/*---(done)-----------------*/



/*===[[ yVICURSES_base.c ]]===================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(search)---------------*/
char        yvicurses__by_abbr      (char a_abbr);
char        yvicurses__primary      (char a_abbr);
char        yvicurses__by_name      (char *a_terse);
/*---(create)---------------*/
char        yVICURSES_color         (char *a_terse, char *a_desc, char a_fg, char a_bg);
/*---(using)----------------*/
char        yVICURSES_by_name       (char *a_terse);
char*       yvicurses__by_pair      (int a_pair);
/*---(program)--------------*/
char        yvicurses_color_init    (void);
char        yvicurses_color_wrap    (void);
/*---(done)-----------------*/



/*===[[ yVICURSES_draw.c ]]===================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(text)-----------------*/
char        yvicurses_title         (void);
char        yvicurses_version       (void);
char        yvicurses_modes         (void);
char        yvicurses_status        (void);
char        yvicurses_command       (void);
char        yvicurses_keys          (void);
/*---(fancy)----------------*/
char        yvicurses_univs         (void);
char        yvicurses_menus         (void);
char        yvicurses_notes         (void);
/*---(source)---------------*/
char        yvicurses__display      (char a_part, char a_loc, char a_style);
char        yvicurses_formula       (void);
/*> char        yvicurses_formula_min   (void);                                       <*/
/*> char        yvicurses_formula_small (void);                                       <*/
/*> char        yvicurses_formula_label (void);                                       <*/
/*> char        yvicurses_formula_max   (void);                                       <*/
char        yvicurses_command       (void);
char        yvicurses_float         (void);
/*---(done)-----------------*/

char        yVICURSES_redraw        (void);


char        yvicurses_history       (void);



#endif

