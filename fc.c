/***************************************************************************
 *   fc.c                                     Version 20180915.214818      *
 *                                                                         *
 *   Fraction Calculator                                                   *
 *   Copyright (C) 2018         by Iago Gade Gusmao Carrazzoni             *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License.               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *   To contact the author, please write to:                               *
 *   Iago Gade Gusmao Carrazzoni                                           *
 *   Email: iagocarrazzoni@gmail.com                                       *
 *   Webpage: http://www.upe.br                                            *
 *   Phone: +55 (81) 99479-0584                                            *
 ***************************************************************************/

/* ---------------------------------------------------------------------- */
/**
 * @file frac.c
 * @ingroup GroupUnique
 * @brief Fraction Calculator
 * @details This program really do a nice job as a template, and template only!
 * @version 20180915.214818
 * @date 2018-09-15
 * @author Iago Gade Gusmao Carrazzoni <<iagocarrazzoni@gmail.com>>
 * @par Webpage
 * <<a href="http://www.upe.br">www.upe.br</a>>
 * @copyright (c) 2018 GNU GPL v2
 * @note This program is free software: you can redistribute it
 * and/or modify it under the terms of the
 * GNU General Public License as published by
 * the Free Software Foundation version 2 of the License.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.
 * If not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA. 02111-1307, USA.
 * Or read it online at <<http://www.gnu.org/licenses/>>.
 *
 *
 * @todo Now that you have the template, hands on! Programme!
 * @warning Be carefull not to lose your mind in small things.
 * @bug This file right now does nothing usefull
 *
 */

/*
 * Instrucoes para compilar:
 *   $gcc frac.c -o frac.x -Wall
 *        -Wextra -ansi -pedantic-errors -g -O0 -DDEBUG=1 -DVERSION="0.1.160612.142044"
 *   ou preferencialmente inclua um makefile e use:
 *   $make
 *
 * Modelo de indentacao:
 * Estilo: --style=allman ou -A1
 *
 * Opcoes: -A1 -s4 -k3 -xj -SCNeUpv
 *
 *  * No vi use:
 *      :% !astyle -A1 -s4 -k3 -xj -SCNeUpv
 *  * No linux:
 *      $astlye -A1 -s4 -k3 -xj -SCNeUpv frac.c
 */

/* ---------------------------------------------------------------------- */
/* includes */

#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Miscellaneous functions (rand, malloc, srand)*/
#include <getopt.h> /* get options from system argc/argv */
#include <string.h> /* Strings functions definitions */

/* ---------------------------------------------------------------------- */
/* definitions */

#ifndef VERSION /* gcc -DVERSION="0.1.160612.142628" */
#define VERSION "20180915.214818" /**< Version Number (string) */
#endif

/* Debug */
#ifndef DEBUG /* gcc -DDEBUG=1 */
#define DEBUG 0 /**< Activate/deactivate debug mode */
#endif

#if DEBUG==0
#define NDEBUG
#endif
/* #include <assert.h> */ /* Verify assumptions with assert. Turn off with #define NDEBUG */ 

/** @brief Debug message if DEBUG on */
#define IFDEBUG(M) if(DEBUG) fprintf(stderr, "[DEBUG file:%s line:%d]: " M "\n", __FILE__, __LINE__); else {;}

/* limits */
#define SBUFF 60 /**< String buffer */
#define MAX 11

/* ---------------------------------------------------------------------- */
/* globals */

static int verb = 0; /**< verbose level, global within the file */

/* ---------------------------------------------------------------------- */
/* prototypes */

void help(void); /* print some help */
void copyr(void); /* print version and copyright information */
void frac_init(char exp[SBUFF]); /* global initialization function */
void divtokens(char exp[SBUFF], int frac[MAX]); /* break the string in tokens */
void avaliatokens(char *aux[SBUFF],  int frac[MAX], int i); /* break the string in tokens */
void misto(int mist, int frac[MAX], int i); /* fraction to mixed number */
float calcula(int frac[MAX], int r[MAX]); /* computes the fraction */
void simplifica(int r[MAX]); /* simplifies the result */
void print(char exp[SBUFF], int r[MAX], float dec, int frac[MAX]); /* print the results */

/* main */
/* ---------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief This is the main event of the evening
 * @details Ladies and Gentleman... It's tiiiime!
 * Fightiiiiing at the blue corner,
 * he, who has compiled more C code than any other adversary in the history,
 * he, who has developed UNIX and Linux, and is an inspiration to maaany languages
 * and compilers, the GNU C Compiler, GCC!
 * Fightiiiiing at the red corner, the challenger, in his first fight, lacking of any
 * valid experience but angrily, blindly, and no doubtfully, will try to
 * compile this program without errors. He, the student, the apprentice,
 * the developer, iggc!!
 *
 * @param[in] argc Argument counter
 * @param[in] argv Argument strings (argument values)
 *
 * @retval 0 If succeed (EXIT_SUCCESS).
 * @retval 1 Or another error code if failed.
 *
 * @par Example
 * @code
 *    $./frac -h
 * @endcode
 *
 * @warning   Be carefull with...
 * @bug There is a bug with...
 * @todo Need to do...
 * @note You can read more about it at <<a href="http://www.upe.br">www.upe.br</a>>
 * @author Iago Gade Gusmao Carrazzoni
 * @version 20180915.214818
 * @date 2018-09-15
 *
 */
int main(int argc, char *argv[])
{
    int opt; /* return from getopt() */
    char exp[SBUFF]; /* expression */
    int frac[MAX];
    int r[MAX];
    float dec;
    char rep[SBUFF];
    int repi = 1;

    /* IFDEBUG("Starting optarg loop..."); */

    /* getopt() configured options:
     *        -h  help
     *        -V  version
     *        -v  verbose
     */
    opterr = 0;
    while((opt = getopt(argc, argv, "vhV")) != EOF)
        switch(opt)
        {
            case 'h':
                help();
                break;
            case 'V':
                copyr();
                break;
            case 'v':
                verb++;
                break;
            case '?':
            default:
                printf("Type\n\t$man %s\nor\n\t$%s -h\nfor help.\n\n", argv[0], argv[0]);
                return EXIT_FAILURE;
        }

    if(verb)
        printf("Verbose level set at: %d\n", verb);

    do
    {
        frac_init(exp); /* initialization function */
        divtokens(exp, frac); /* break the string in tokens */
        dec = calcula(frac, r); /* computes the fraction */
        print(exp, r, dec, frac); /* prints the results */
        printf("\nDo you want to do another operation?\nenter 1 for yes\n");
        fgets(rep, SBUFF, stdin);
        repi = atoi(rep);
    }while(repi == 1);

    return EXIT_SUCCESS;
}

/* functions */
/* ---------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Prints help information and exit
 * @details Prints help information (usually called by opt -h)
 * @return Void
 * @author Iago Gade Gusmao Carrazzoni
 * @version 20180915.214818
 * @date 2018-09-15
 *
 */
void help(void)
{
    IFDEBUG("help()");
    printf("%s - %s\n", "frac", "Fraction Calculator");
    printf("\nUsage: %s [-h|-v]\n", "frac");
    printf("\nOptions:\n");
    printf("\t-h,  --help\n\t\tShow this help.\n");
    printf("\t-V,  --version\n\t\tShow version and copyright information.\n");
    printf("\t-v,  --verbose\n\t\tSet verbose level (cumulative).\n");
    /* add more options here */
    printf("\nExit status:\n\t0 if ok.\n\t1 some error occurred.\n");
    printf("\nTodo:\n\tLong options not implemented yet.\n");
    printf("\nAuthor:\n\tWritten by %s <%s>\n\n", "Iago Gade Gusmao Carrazzoni", "iagocarrazzoni@gmail.com");
    exit(EXIT_FAILURE);
}

/* ---------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Prints version and copyright information and exit
 * @details Prints version and copyright information (usually called by opt -V)
 * @return Void
 * @author Iago Gade Gusmao Carrazzoni
 * @version 20180915.214818
 * @date 2018-09-15
 *
 */
void copyr(void)
{
    IFDEBUG("copyr()");
    printf("%s - Version %s\n", "frac", VERSION);
    printf("\nCopyright (C) %d %s <%s>, GNU GPL version 2 <http://gnu.org/licenses/gpl.html>. This  is  free  software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law. USE IT AS IT IS. The author takes no responsability to any damage this software may inflige in your data.\n\n", 2018, "Iago Gade Gusmao Carrazzoni", "iagocarrazzoni@gmail.com");
    if(verb > 3) printf("copyr(): Verbose: %d\n", verb); /* -vvvv */
    exit(EXIT_FAILURE);
}

/* ---------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief This function initializes some operations before start
 * @details Details to be written in
 * multiple lines
 *
 * @pre You need to call foo() before calling this function
 *
 * @param[in] i Input parameter that does bla
 * @param[out] o Parameter that outputs ble
 * @param[in,out] z The @a z variable is used as input and output
 *
 * @retval 0 Returned when bli
 * @retval 1 Error code: function returned blo
 *
 * @par Example
 * @code
 *    if(x == funcexample(i, o, z))
 *       printf("And that is it\n");
 * @endcode
 *
 * @return Void
 *
 * @warning Be carefull with blu
 * @todo Need to implement it. Its empty now. This doxygen tags are overwhelming.
 * Mandatory tags are: ingroup, brief, details, param, return, author and date.
 * The others are optional.
 *
 * @deprecated This function will be deactivated in version +11
 * @see help()
 * @see copyr()
 * @bug There is a bug with x greater than y
 * @note You can read more about it at <<a href="http://www.upe.br">www.upe.br</a>>
 *
 * @author Iago Gade Gusmao Carrazzoni
 * @version 20180915.214818
 * @date 2018-09-15
 * @copyright Use this tag only if not the same as the whole file
 *
 */
void frac_init(char exp[SBUFF])
{
    /* IFDEBUG("frac_init()"); */
    printf("-------------------\n");
    printf("FRACTION CALCULATOR\nPlease entry the desired operation:\n(It is necessary to add a space between the fractions, like a/b + c/d)\n-> ");
    fgets(exp, SBUFF, stdin); /* expression input */

    return;
}

/* ---------------------------------------------------------------------- */
void divtokens(char exp[SBUFF],  int frac[MAX]) /* break the string in tokens */
{
    char *token; /* token pointer */
    char exp2[SBUFF];
    char *aux[SBUFF];
    int i = 0;

    strcpy(exp2, exp); /* to maintain the original expression untouched */

    token = strtok(exp2, " "); /* divides the equation into tokens */
    while(token != NULL)
    {
        aux[i] = token;
        token = strtok(NULL, " ");
        i++;
    }

    frac[MAX - 2] = i; /* number of elements of the expression */

    avaliatokens(aux, frac, i);

    return;
}

/* ---------------------------------------------------------------------- */
void avaliatokens(char *aux[SBUFF],  int frac[MAX], int i) /* analyzes the tokens, to check the fractions */
{
    int j, k = 0;
    char *token2;
    int mist;

    /* 1 mist first fraction */
    if(((strcmp(aux[2], "+") == 0) || (strcmp(aux[2], "-") == 0) || (strcmp(aux[2], "*") == 0) || (strcmp(aux[2], "/") == 0)) && i == 4)
        mist = 1;
    /* 1 mist second fraction */
    if(((strcmp(aux[1], "+") == 0) || (strcmp(aux[1], "-") == 0) || (strcmp(aux[1], "*") == 0) || (strcmp(aux[1], "/") == 0)) && i == 4)
        mist = 2;
    
    for(j = 0; j < i; j++)
    {
        if((strcmp(aux[j], "+") == 0))
        {
            frac[MAX - 1] = 1;
            j++;
        }
        if((strcmp(aux[j], "-") == 0))
        {
            frac[MAX - 1] = 2;
            j++;
        }
        if((strcmp(aux[j], "*") == 0))
        {
            frac[MAX - 1] = 3;
            j++;
        }
        if((strcmp(aux[j], "/") == 0))
        {
            frac[MAX - 1] = 4;
            j++;
        }

        token2 = strtok(aux[j], "/"); /* divides the equation into tokens */
        while(token2 != NULL)
        {
            frac[k] = atoi(token2); /* stores tokens in the array */
            token2 = strtok(NULL, "/");
            k++;
        }
    }
    misto(mist, frac, i);

    return;
}

/* ---------------------------------------------------------------------- */
void misto(int mist, int frac[MAX], int i) /* fraction to mixed number */
{
    /* 2 fractions no mist */
    if(i == 3)
    {
        frac[MAX - 2] = frac[0]; /* num 1 */
        frac[MAX - 3] = frac[1]; /* den 1 */
        frac[MAX - 4] = frac[2]; /* num 2 */
        frac[MAX - 5] = frac[3]; /* den 2*/ 
        return;
    }
    /* 1 mist first fraction */
    if(mist == 1)
    {
        frac[0] = frac[2] * frac[0] + frac[1]; /* num */
        frac[1] = frac[2]; /* den */
        frac[2] = frac[3]; /* num */
        frac[3] = frac[4]; /* den */
        frac[MAX - 2] = frac[0]; /* num 1 */
        frac[MAX - 3] = frac[1]; /* den 1 */
        frac[MAX - 4] = frac[2]; /* num 2 */
        frac[MAX - 5] = frac[3]; /* den 2*/ 

        return;
    }
    /* 1 mist second fraction */
    if(mist == 2)
    {
        frac[2] = frac[4] * frac[2] + frac[3];
        frac[3] = frac[4];
        frac[MAX - 2] = frac[0]; /* num 1 */
        frac[MAX - 3] = frac[1]; /* den 1 */
        frac[MAX - 4] = frac[2]; /* num 2 */
        frac[MAX - 5] = frac[3]; /* den 2*/ 
        return;
    }
    /* 2 mist */
    if(i == 5)
    {
        frac[0] = frac[2] * frac[0] + frac[1]; /* num */
        frac[1] = frac[2]; /* den */
        frac[2] = frac[5] * frac[3] + frac[4]; /* num */
        frac[3] = frac[5]; /* den */
        frac[MAX - 2] = frac[0]; /* num 1 */
        frac[MAX - 3] = frac[1]; /* den 1 */
        frac[MAX - 4] = frac[2]; /* num 2 */
        frac[MAX - 5] = frac[3]; /* den 2*/ 
        return;
    }
    return;
}

/* ---------------------------------------------------------------------- */
float calcula(int frac[MAX], int r[MAX]) /* computes the fraction */
{
    float dec, a, b;

    r[0] = frac[1] * frac[3]; /* mmc */
    switch(frac[MAX - 1]) /* operation */
    {
        case 1: /* + */
            r[1] = (r[0] / frac[1]) * frac[0] + (r[0] / frac[3]) * frac[2];
            a = r[1];
            b = r[0];
            dec = a / b; /* decimal */
            simplifica(r);
            break;
        case 2: /* - */
            r[1] = (r[0] / frac[1]) * frac[0] - (r[0] / frac[3]) * frac[2];
            a = r[1];
            b = r[0];
            dec = a / b; /* decimal */
            simplifica(r);
            break;
        case 3: /* * */
            r[1] = frac[0] * frac[2];
            a = r[1];
            b = r[0];
            dec = a / b; /* decimal */
            simplifica(r);
            break;
        case 4: /* / */
            r[0] = frac[1] * frac[2];
            r[1] = frac[0] * frac[3];
            a = r[1];
            b = r[0];
            dec = a / b; /* decimal */
            simplifica(r);
            break;
    }

    return dec;
}

/* ---------------------------------------------------------------------- */
void simplifica(int r[MAX]) /* simplifies the result */
{
    int i;
    int aux1, aux2;

    aux1 = r[1];
    aux2 = r[0];

    for(i = 1; i < MAX + 2; i++)
    {
        if(aux1%i == 0 && aux2%i == 0) /* simplified */
        {
            aux1 /= i;
            aux2 /= i;
        }
    }
    r[3] = aux1;
    r[4] = aux2;

    return;
}

/* ---------------------------------------------------------------------- */
void print(char exp[SBUFF], int r[MAX], float dec, int frac[MAX]) /* print the results */
{
    char op;

    if(frac[MAX - 1] == 1)
        op = '+';
    if(frac[MAX - 1] == 2)
        op = '-';
    if(frac[MAX - 1] == 3)
        op = '*';
    if(frac[MAX - 1] == 4)
        op = '/';
    
    printf("\nEXPRESSION: %sFRACTION: %d/%d %c %d/%d\nINTERMEDIATE: %d/%d\nRESULT: %d/%d\nDECIMAL: %.3f\n", exp, frac[MAX - 2], frac[MAX - 3], op, frac[MAX - 4], frac[MAX - 5], r[1], r[0], r[3], r[4], dec);

    return;
}

/* ---------------------------------------------------------------------------- */
/* vi: set ai cin et ts=4 sw=4 tw=0 wm=0 fo=croqltn : C config for Vim modeline */
/* Template by Dr. Beco <rcb at beco dot cc>  Version 20160714.153029           */
