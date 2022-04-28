#ifndef __TOKENIZER_H
#define __TOKENIZER_H

enum TokenType {
    START,
    END_OF_FILE,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    LEFT_BRACE,
    RIGHT_BRACE,
    BACKSLASH,
    CIRCUMFLEX,
    COMMERCIAL_AT,
    POUND,
    APOSTROPHE,
    SPECIAL_FORM,
    STRING,
    REGEX_LITERAL,
    EscapeSequence,
    UnicodeEscape,
    OctalEscape,
    NUMBER,
    CHARACTER,
    HEXDIGIT,
    NIL,
    BOOLEAN,
    SYMBOL,
    METADATA_TYPEHINT,
    NAME,
    SYMBOL_HEAD,
    SYMBOL_REST,
    literal,
    KEYWORD,
    SYNTAX_QUOTE,
    UNQUOTE_SPLICING,
    UNQUOTE,
    COMMENT,
    SPACE,
    LAMBDA_ARG,
    file,
    form,
    macroForm,
    dispatchMacroForm,
    list,
    vector,
    map,
    quoteForm,
    metaForm,
    derefForm,
    syntaxQuoteForm,
    unquoteForm,
    unquoteSplicingForm,
    set,
    metadataForm,
    varQuoteForm,
    lambdaForm
};

typedef struct {
    enum TokenType token_type;
    char* value;
} Token;

static char* source;
static int token_counter;
char* peek_range(int);
Token* tokenize(char*);

#endif