enum Bool{
    FALSE = 0,
    TRUE  = 1,
    FAIL  = 0,
    PASS  = 1
};

enum EquTknType{
    NUMBER,
    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE,
    EMPTY
};

typedef struct EquationToken{
    enum EquTknType type;
    int value;
} EquationToken;

// returns 1 if specified char is in string, returns 0 otherwise
enum Bool charInStr(const char argChar, const char* argStr) {
    for(unsigned i = 0; argStr[i] != '\0'; ++i) {
        if(argStr[i] == argChar) return TRUE;
    }
    return FALSE;
}


// converts a string to an integer, ignores whitespaces,
// will not do anything if invalid character(s) present
int convertStrToInt(const char *str) {
    int it = 0;
    while( str[it] != '\0') it++;

    unsigned placeValue = 1; int total = 0;
    if( check(str, "0123456789 ") ) {
        for(unsigned j = it - 1; j != -1; --j) {
            if( str[j] != ' ') {                
                total += ( (str[j] - '0') * placeValue );
                placeValue *= 10;
            }
        }
    }

    return total;
}


// helper function | appends EquationToken struct to end of EquationToken array
void EquationStepsAppend(struct EquationToken token, struct EquationToken tokens[]) {
    unsigned i = 0;
    while(tokens[i].type != EMPTY) {
        i++;
    }
    tokens[i] = token;
}


// checks equation for any invalid values   
enum Bool check(const char *str, const char validChars[]) {
    for(unsigned i = 0; str[i] != '\0'; ++i) {
        if( !(charInStr(str[i], validChars)) ) return FAIL;
    }

    return PASS;
}


// tokenizes string into parseable equation
void read_equ(const char *equ, struct EquationToken tokens[]) {
    if( check(equ, "0123456789+-*/ ") ) {
        struct EquationToken temp_token;
        char temp_num[8]; unsigned tnPtr = 0;

        unsigned i = 0;
        while( equ[i] != '\0' ) {
            switch(equ[i]) {
                case '+': 
                    temp_token.type = OP_PLUS;
                    EquationStepsAppend(temp_token, tokens);
                    i++;
                    break;
                case '-': 
                    temp_token.type = OP_MINUS;
                    EquationStepsAppend(temp_token, tokens);
                    i++;                    
                    break;
                case '*': 
                    temp_token.type = OP_MULTIPLY;
                    EquationStepsAppend(temp_token, tokens);
                    i++;
                    break;
                case '/': 
                    temp_token.type = OP_DIVIDE;
                    EquationStepsAppend(temp_token, tokens);
                    i++;
                    break;
                case ' ': 
                    // pass
                    i++; 
                    break;
                default:
                    temp_token.type = NUMBER;

                    while( charInStr(equ[i], "0123456789") ) {
                        temp_num[tnPtr] = equ[i];
                        
                        tnPtr++;
                        i++;
                        continue;                   
                    }
                    temp_token.value = convertStrToInt(temp_num);
                    EquationStepsAppend(temp_token, tokens);

                    for(unsigned c = 0; c < tnPtr; c++) temp_num[c] = ' ';

                    break;
            }

     
        }
    }
}

// evaluates EquationToken array and returns integer value
int evaluate(const char *equation) {
    struct EquationToken tokens[15];
    struct EquationToken NULL_TOKEN; NULL_TOKEN.type = EMPTY;
    for(unsigned i = 0; i < (sizeof(tokens)/sizeof(tokens[0])); ++i) tokens[i] = NULL_TOKEN;
    
    read_equ(equation, tokens);

    unsigned i = 0;
    while(tokens[i].type != EMPTY) {
        switch(tokens[i].type) {
            case OP_PLUS:
                tokens[i + 1].value = tokens[i - 1].value + tokens[i + 1].value;
                break;
            case OP_MINUS:
                tokens[i + 1].value = tokens[i - 1].value - tokens[i + 1].value;
                break;
            case OP_MULTIPLY:
                tokens[i + 1].value = tokens[i - 1].value * tokens[i + 1].value;
                break;
            case OP_DIVIDE:
                tokens[i + 1].value = tokens[i - 1].value / tokens[i + 1].value;
                break;
        }

        i++;
    }

    return tokens[i - 1].value;

}
