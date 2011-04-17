/*
 * This file was generated automatically by ExtUtils::ParseXS version 2.21 from the
 * contents of API.xs. Do not edit this file, edit API.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#line 1 "API.xs"
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#define PL_bufptr (PL_parser->bufptr)
#define PL_bufend (PL_parser->bufend)

static SV *hintkey_keyword_sv;
static SV *keyword_name_sv;
static SV *keyword_parser_sv;
static int (*next_keyword_plugin)(pTHX_ char *, STRLEN, OP **);

/* plugin glue */
static int THX_keyword_active(pTHX_ SV *hintkey_sv)
{
	HE *he;
	if(!GvHV(PL_hintgv)) return 0;
	he = hv_fetch_ent(GvHV(PL_hintgv), hintkey_sv, 0,
				SvSHARED_HASH(hintkey_sv));
	return he && SvTRUE(HeVAL(he));
}
#define keyword_active(hintkey_sv) THX_keyword_active(aTHX_ hintkey_sv)


static void THX_keyword_enable(pTHX_ SV *classname, SV* keyword)
{
    hintkey_keyword_sv = newSVsv(classname);
    keyword_parser_sv = newSVsv(classname);
    keyword_name_sv = newSVsv(keyword);

    sv_catpv(hintkey_keyword_sv, "/");
    sv_catpv(keyword_parser_sv, "::parser");
    sv_catsv(hintkey_keyword_sv, keyword);

	SV *val_sv = newSViv(1);
	HE *he;
	PL_hints |= HINT_LOCALIZE_HH;
	gv_HVadd(PL_hintgv);
	he = hv_store_ent(GvHV(PL_hintgv),
		hintkey_keyword_sv, val_sv, SvSHARED_HASH(hintkey_keyword_sv));
	if(he) {
		SV *val = HeVAL(he);
		SvSETMAGIC(val);
	} else {
		SvREFCNT_dec(val_sv);
	}    
}
#define keyword_enable(class_sv, keyword_sv) THX_keyword_enable(aTHX_ class_sv, keyword_sv)


static void THX_keyword_disable(pTHX_)
{
	if(GvHV(PL_hintgv)) {
		PL_hints |= HINT_LOCALIZE_HH;
		hv_delete_ent(GvHV(PL_hintgv),
			hintkey_keyword_sv, G_DISCARD, SvSHARED_HASH(hintkey_keyword_sv));
	}

    printf("uninstalled\n");
}
#define keyword_disable() THX_keyword_disable(aTHX_)


static int my_keyword_plugin(pTHX_
	char *keyword_ptr, STRLEN keyword_len, OP **op_ptr)
{
    if (keyword_name_sv == NULL) {
	    return next_keyword_plugin(aTHX_ keyword_ptr, keyword_len, op_ptr);
    }

    STRLEN len;
    char * kw_str = SvPV(keyword_name_sv, len);
    int kw_len = strlen(kw_str);    

	if(keyword_len == kw_len && strnEQ(keyword_ptr, kw_str, kw_len) &&
			keyword_active(hintkey_keyword_sv)) {
        printf("called keyword plugin!\n");
        call_sv(keyword_parser_sv, G_DISCARD|G_NOARGS);
		*op_ptr = newOP(OP_NULL,0);
		return KEYWORD_PLUGIN_STMT;
	} else {
		return next_keyword_plugin(aTHX_
				keyword_ptr, keyword_len, op_ptr);
	}
}


#line 98 "API.c"
#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#ifndef PERL_ARGS_ASSERT_CROAK_XS_USAGE
#define PERL_ARGS_ASSERT_CROAK_XS_USAGE assert(cv); assert(params)

/* prototype to pass -Wmissing-prototypes */
STATIC void
S_croak_xs_usage(pTHX_ const CV *const cv, const char *const params);

STATIC void
S_croak_xs_usage(pTHX_ const CV *const cv, const char *const params)
{
    const GV *const gv = CvGV(cv);

    PERL_ARGS_ASSERT_CROAK_XS_USAGE;

    if (gv) {
        const char *const gvname = GvNAME(gv);
        const HV *const stash = GvSTASH(gv);
        const char *const hvname = stash ? HvNAME(stash) : NULL;

        if (hvname)
            Perl_croak(aTHX_ "Usage: %s::%s(%s)", hvname, gvname, params);
        else
            Perl_croak(aTHX_ "Usage: %s(%s)", gvname, params);
    } else {
        /* Pants. I don't think that it should be possible to get here. */
        Perl_croak(aTHX_ "Usage: CODE(0x%"UVxf")(%s)", PTR2UV(cv), params);
    }
}
#undef  PERL_ARGS_ASSERT_CROAK_XS_USAGE

#ifdef PERL_IMPLICIT_CONTEXT
#define croak_xs_usage(a,b)	S_croak_xs_usage(aTHX_ a,b)
#else
#define croak_xs_usage		S_croak_xs_usage
#endif

#endif

/* NOTE: the prototype of newXSproto() is different in versions of perls,
 * so we define a portable version of newXSproto()
 */
#ifdef newXS_flags
#define newXSproto_portable(name, c_impl, file, proto) newXS_flags(name, c_impl, file, proto, 0)
#else
#define newXSproto_portable(name, c_impl, file, proto) (PL_Sv=(SV*)newXS(name, c_impl, file), sv_setpv(PL_Sv, proto), (CV*)PL_Sv)
#endif /* !defined(newXS_flags) */

#line 150 "API.c"

XS(XS_Keyword__API_install_keyword); /* prototype to pass -Wmissing-prototypes */
XS(XS_Keyword__API_install_keyword)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 2)
       croak_xs_usage(cv,  "classname, keyword");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	SV *	classname = ST(0);
	SV *	keyword = ST(1);
#line 97 "API.xs"
    keyword_enable(classname,keyword);
#line 169 "API.c"
	PUTBACK;
	return;
    }
}


XS(XS_Keyword__API_uninstall_keyword); /* prototype to pass -Wmissing-prototypes */
XS(XS_Keyword__API_uninstall_keyword)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 0)
       croak_xs_usage(cv,  "");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
#line 102 "API.xs"
    keyword_disable();
#line 191 "API.c"
	PUTBACK;
	return;
    }
}


XS(XS_Keyword__API_lex_read_space); /* prototype to pass -Wmissing-prototypes */
XS(XS_Keyword__API_lex_read_space)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "flag");
    {
	int	flag = (int)SvIV(ST(0));

	lex_read_space(flag);
    }
    XSRETURN_EMPTY;
}


XS(XS_Keyword__API_lex_read); /* prototype to pass -Wmissing-prototypes */
XS(XS_Keyword__API_lex_read)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "chars");
    {
	SV *	RETVAL;
	int	chars = (int)SvIV(ST(0));
#line 110 "API.xs"
    char *start = PL_bufptr;
    char *end = start + chars;
    lex_read_to(end);
    RETVAL = newSVpvn(start, end-start);
#line 235 "API.c"
	ST(0) = RETVAL;
	sv_2mortal(ST(0));
    }
    XSRETURN(1);
}


XS(XS_Keyword__API_lex_read_token); /* prototype to pass -Wmissing-prototypes */
XS(XS_Keyword__API_lex_read_token)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 0)
       croak_xs_usage(cv,  "");
    {
	SV *	RETVAL;
#line 119 "API.xs"
    char *start = PL_bufptr;
    char *p = start;

    while(1) {
        char x = *++p;
        if (isSPACE(x)) {
            break;
        }
    } 

    RETVAL = newSVpvn(start, p-start);
#line 267 "API.c"
	ST(0) = RETVAL;
	sv_2mortal(ST(0));
    }
    XSRETURN(1);
}


XS(XS_Keyword__API_lex_unstuff_token); /* prototype to pass -Wmissing-prototypes */
XS(XS_Keyword__API_lex_unstuff_token)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 0)
       croak_xs_usage(cv,  "");
    {
	SV *	RETVAL;
#line 136 "API.xs"
    char *start = PL_bufptr;
    char *p = start;
    SV *r;

    while(1) {
        char x = *++p;
        if (isSPACE(x)) {
            break;
        }
    } 
    r = newSVpvn(start, p-start);

    if (SvPVX(r) == start) {
        croak("we are doomed");
    }

    RETVAL = r;
    lex_unstuff(p);
#line 306 "API.c"
	ST(0) = RETVAL;
	sv_2mortal(ST(0));
    }
    XSRETURN(1);
}


XS(XS_Keyword__API_lex_unstuff_to); /* prototype to pass -Wmissing-prototypes */
XS(XS_Keyword__API_lex_unstuff_to)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "s");
    {
	SV *	RETVAL;
	char	s = (char)*SvPV_nolen(ST(0));
#line 159 "API.xs"
    char *start = PL_bufptr;
    char *p = start;

    while(1) {
        char x = *++p;
        if (x == s) {
            break;
        }
    } 

    p++;

    RETVAL = newSVpvn(start, p-start);
    lex_unstuff(p);
#line 342 "API.c"
	ST(0) = RETVAL;
	sv_2mortal(ST(0));
    }
    XSRETURN(1);
}


XS(XS_Keyword__API_lex_unstuff); /* prototype to pass -Wmissing-prototypes */
XS(XS_Keyword__API_lex_unstuff)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "chars");
    {
	SV *	RETVAL;
	int	chars = (int)SvIV(ST(0));
#line 179 "API.xs"
    char *start = PL_bufptr;
    char *end = start + chars;
    RETVAL = newSVpvn(start, end-start);
    lex_unstuff(end);
#line 368 "API.c"
	ST(0) = RETVAL;
	sv_2mortal(ST(0));
    }
    XSRETURN(1);
}


XS(XS_Keyword__API_lex_stuff); /* prototype to pass -Wmissing-prototypes */
XS(XS_Keyword__API_lex_stuff)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "str");
    {
	SV *	str = ST(0);
#line 189 "API.xs"
    lex_stuff_sv(str, 0);
#line 390 "API.c"
    }
    XSRETURN_EMPTY;
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_Keyword__API); /* prototype to pass -Wmissing-prototypes */
XS(boot_Keyword__API)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
#if (PERL_REVISION == 5 && PERL_VERSION < 9)
    char* file = __FILE__;
#else
    const char* file = __FILE__;
#endif

    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
    XS_VERSION_BOOTCHECK ;

        (void)newXS("Keyword::API::install_keyword", XS_Keyword__API_install_keyword, file);
        (void)newXS("Keyword::API::uninstall_keyword", XS_Keyword__API_uninstall_keyword, file);
        (void)newXS("Keyword::API::lex_read_space", XS_Keyword__API_lex_read_space, file);
        (void)newXS("Keyword::API::lex_read", XS_Keyword__API_lex_read, file);
        (void)newXS("Keyword::API::lex_read_token", XS_Keyword__API_lex_read_token, file);
        (void)newXS("Keyword::API::lex_unstuff_token", XS_Keyword__API_lex_unstuff_token, file);
        (void)newXS("Keyword::API::lex_unstuff_to", XS_Keyword__API_lex_unstuff_to, file);
        (void)newXS("Keyword::API::lex_unstuff", XS_Keyword__API_lex_unstuff, file);
        (void)newXS("Keyword::API::lex_stuff", XS_Keyword__API_lex_stuff, file);

    /* Initialisation Section */

#line 91 "API.xs"
    next_keyword_plugin = PL_keyword_plugin;
	PL_keyword_plugin = my_keyword_plugin;

#line 432 "API.c"

    /* End of Initialisation Section */

#if (PERL_REVISION == 5 && PERL_VERSION >= 9)
  if (PL_unitcheckav)
       call_list(PL_scopestack_ix, PL_unitcheckav);
#endif
    XSRETURN_YES;
}

