#include <sparrow3d.h>
#include "button.h"

int buttonSteps[20] = { 0 };
// incrementing each spGetInput()->button[] would be sick but they overflow
// too quick

// will return the amount of steps a button has been held down consecutively
// if unpressed, returns 0.
int
getButton ( int button, Uint32 steps )
{
	if ( spGetInput()->button[button] ) {
		if ( buttonSteps[button] == 0 )
			buttonSteps[button]++;
		else
			buttonSteps[button] += steps;
		return buttonSteps[button];
	}
	else
		buttonSteps[button] = 0;
	return 0;
}

// acts like getButton, except it returns 0 (unpressed) if the consective steps
// the button has been held down for isn't within the given range.
// can also reset the button's step counter after it meets the range, or
// completely disable the current button-press after it meets the range.
// pass -1 as min_steps or max_steps to disable that part of the range-check.
// pass 0 as disable/reset to disable resetting/disabling, 1 to enable.
// I recommend 1,0,1 for init_no_min,disable,reset
int
getButtonLim
( int button, Uint32 steps, Uint32 min_steps, Uint32 max_steps, int init_no_min,
  int disable, int reset )
{
	int b_steps = getButton( button, steps );
	int range_pass = 0;

	if ( (min_steps < b_steps && (b_steps < max_steps || max_steps == -1)) )
		range_pass = 1;
	if ( init_no_min && b_steps ==1 )
		range_pass = 1;

	if ( disable && range_pass )
		spGetInput()->button[button] = 0;
	if ( (reset || disable) && range_pass )
		buttonSteps[button] = 1;

	if ( range_pass )
		return b_steps;
	return 0;
}
