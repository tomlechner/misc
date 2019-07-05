
// Released CC0
//
// g++ xlib-keyboards.cc -lX11 -o xlib-keyboards


#include <X11/Xlib.h>
//#include <X11/Xutils.h>
#include <cstdio>

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	Display *dpy = XOpenDisplay(NULL);
	int keysyms_per_keycode = -1;
	int first_keycode = 0, last_keycode = 0;

	XDisplayKeycodes(dpy, &first_keycode, &last_keycode);
	int num_keycodes = last_keycode - first_keycode + 1;

	KeySym *list = XGetKeyboardMapping(dpy, first_keycode, num_keycodes, &keysyms_per_keycode);

	int listn = num_keycodes * keysyms_per_keycode;

	for (int c=0; c<num_keycodes; c++) {
		printf("%02x/%d: ", c + first_keycode, c + first_keycode);

		for (int c2=0; c2<keysyms_per_keycode; c2++) {

			char *str = XKeysymToString(list[c*keysyms_per_keycode + c2]);
			printf("%d(%-4x): %-10s ",
					c2,
					(unsigned int)list[c*keysyms_per_keycode + c2],
					str ? str : "(none)");
		}
		printf("\n");
	}


	XFree(list);
	return 0;
}

