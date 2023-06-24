#ifndef __MTECH__MCALC_H_ver1
#define __MTECH_MCALC_H_ver1

int evaluate(const char* equation);

// === DEBUGGING ===
enum Bool charInStr(const char argChar, const char* argStr);
void EquationStepsAppend(struct EquationToken token, struct EquationToken tokens[]);
enum Bool check(const char *equ);
int read_equ(const char *equ, struct EquationToken tokens[]);

#endif