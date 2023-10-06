#ifndef system_h
#define system_h

enum class system_state {
	reset_state,
	halt_state,
	counting_state,
	setting_state
};

class system_manager {
private:
	static system_state state;
public:
	static system_state get_system_state() { return state; }

	static void system_state_handler(system_state new_state);
	static void main();

	static void INC_Callback();
	static void DEC_Callback();
	static void TRIG_Callback();
	static void SET_Callback();
	static void RST_Callback();
	static void NEXT_Callback();
	static void PREV_Callback();
};

#endif
