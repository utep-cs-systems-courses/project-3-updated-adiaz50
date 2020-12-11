#ifndef stateMachine_included

#define stateMachine_included

void dim_25();
void dim_50();
void dim_75();
void state1();
void state2();
void state3();
void state4();
char dim_state_advance();
char toggle_red();
char toggle_green();
void state_advance(char);

static char dim_select, do_dim;
static char dimState;

#endif // included
