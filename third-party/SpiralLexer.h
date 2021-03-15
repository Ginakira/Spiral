/** \file
 *  This C header file was generated by $ANTLR version 3.4
 *
 *     -  From the grammar source file : Spiral.g
 *     -                            On : 2021-03-15 22:07:27
 *     -                 for the lexer : SpiralLexerLexer
 *
 * Editing it, at least manually, is not wise.
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The lexer 
SpiralLexer

has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 *
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef pSpiralLexer, which is returned from a call to SpiralLexerNew().
 *
 * As this is a generated lexer, it is unlikely you will call it 'manually'. However
 * the methods are provided anyway.
 *
 * The methods in pSpiralLexer are  as follows:
 *
 *  - 
 void
      pSpiralLexer->T__42(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->T__43(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->T__44(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->T__45(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->T__46(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->MOD(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->DIV(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->DO(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->DOWHILE(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->WHILE(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->FOR(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->PRINT(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->IF(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->ELSE(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->OR(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->AND(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->GE(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->NE(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->LITTLE(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->LE(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->GT(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->EQ(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->PLUS(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->MINUS(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->TIMES(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->DOT(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->ASSIGN(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->BLOCK(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->DEF(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->NOPE(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->BREAK(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->CONTINUE(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->INT(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->ID(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->FLOAT(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->COMMENT(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->WS(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->STRING(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->EXPONENT(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->HEX_DIGIT(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->ESC_SEQ(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->OCTAL_ESC(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->UNICODE_ESC(pSpiralLexer)
 *  - 
 void
      pSpiralLexer->Tokens(pSpiralLexer)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD license"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_SpiralLexer_H
#define _SpiralLexer_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */

#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct SpiralLexer_Ctx_struct SpiralLexer, * pSpiralLexer;



#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif

/** Context tracking structure for 
SpiralLexer

 */
struct SpiralLexer_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_LEXER    pLexer;

     void
     (*mT__42)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mT__43)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mT__44)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mT__45)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mT__46)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mMOD)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mDIV)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mDO)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mDOWHILE)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mWHILE)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mFOR)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mPRINT)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mIF)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mELSE)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mOR)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mAND)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mGE)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mNE)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mLITTLE)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mLE)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mGT)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mEQ)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mPLUS)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mMINUS)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mTIMES)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mDOT)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mASSIGN)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mBLOCK)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mDEF)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mNOPE)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mBREAK)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mCONTINUE)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mINT)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mID)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mFLOAT)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mCOMMENT)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mWS)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mSTRING)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mEXPONENT)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mHEX_DIGIT)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mESC_SEQ)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mOCTAL_ESC)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mUNICODE_ESC)	(struct SpiralLexer_Ctx_struct * ctx);

     void
     (*mTokens)	(struct SpiralLexer_Ctx_struct * ctx);
    const char * (*getGrammarFileName)();
    void            (*reset)  (struct SpiralLexer_Ctx_struct * ctx);
    void	    (*free)   (struct SpiralLexer_Ctx_struct * ctx);
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pSpiralLexer SpiralLexerNew         (
pANTLR3_INPUT_STREAM
 instream);
ANTLR3_API pSpiralLexer SpiralLexerNewSSD      (
pANTLR3_INPUT_STREAM
 instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the 
lexer
 will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif
#define EOF      -1
#define T__42      42
#define T__43      43
#define T__44      44
#define T__45      45
#define T__46      46
#define AND      4
#define ASSIGN      5
#define BLOCK      6
#define BREAK      7
#define COMMENT      8
#define CONTINUE      9
#define DEF      10
#define DIV      11
#define DO      12
#define DOT      13
#define DOWHILE      14
#define ELSE      15
#define EQ      16
#define ESC_SEQ      17
#define EXPONENT      18
#define FLOAT      19
#define FOR      20
#define GE      21
#define GT      22
#define HEX_DIGIT      23
#define ID      24
#define IF      25
#define INT      26
#define LE      27
#define LITTLE      28
#define MINUS      29
#define MOD      30
#define NE      31
#define NOPE      32
#define OCTAL_ESC      33
#define OR      34
#define PLUS      35
#define PRINT      36
#define STRING      37
#define TIMES      38
#define UNICODE_ESC      39
#define WHILE      40
#define WS      41
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for SpiralLexer
 * =============================================================================
 */
/** } */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
