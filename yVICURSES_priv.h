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
#define     P_HERITAGE  "with of hephaestus and youngest of the graces"
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
#define     P_VERNUM    "2.0a"
#define     P_VERTXT    "initial library setup"

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
#include    <yKEYS.h>             /* heatherly vikeys key handling            */
#include    <yMODE.h>             /* heatherly vikeys mode tracking           */
#include    <yMACRO.h>            /* heatherly vikeys macro processing        */
#include    <ySRC.h>              /* heatherly vikeys source editing          */
#include    <yCMD.h>              /* heatherly vikeys command processing      */
#include    <yVIEW.h>             /* heatherly vikeys view management         */
/*---(custom other)----------------------*/
#include    <yCOLOR.h>            /* heatherly opengl color handling          */
#include    <yDLST_solo.h>        /* heatherly double-double-list             */
/*---(posix standard)--------------------*/
#include    <ncurses.h>           /* CURSES mvprintw, refresh, getch, ...     */




typedef    struct    cMY    tMY;
struct cMY {
};
extern tMY         myVICURSES;



/*===[[ yVICURSES_base.c ]]===================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        yview_init              (void);
char        yvicurses_getch         (char *a_ch);
char        yVICURSES_main          (char *a_delay, char *a_update, void *a_altinput);
/*---(unittest)-------------*/
char        yview__unit_quiet       (void);
char        yview__unit_loud        (void);
/*---(done)-----------------*/




#endif

