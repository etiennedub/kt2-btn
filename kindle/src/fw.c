/*
	Based on code from untouchable by baf (www.fabiszewski.net), with MIT license:
    http://www.opensource.org/licenses/mit-license.php
*/

#include <stdio.h> // printf
#include <stdlib.h>
#include <stdbool.h> // bool
#include <string.h> // memset
#include <unistd.h> // usleep
#include <X11/XKBlib.h>

void pageForward(Display *display);
void testClick(Display *display, int x, int y);
void SendMouseEvent(Display *display, int button, int x, int y, bool pressed);

bool debug = false;

int main(int argc, char * argv[]) {
	Window root;
	Display * display;
	XEvent xev;
	int screenWidth;
	int screenHeight;

	display = XOpenDisplay(NULL);
	if (display == NULL) {
		if (debug) printf("Could not open display\n");
		return 1;
	}

	root = DefaultRootWindow(display);

	XAllowEvents(display, AsyncBoth, CurrentTime);
	pageForward(display); 
	XCloseDisplay(display);

	return 0;
}

void pageForward(Display *display) {
	SendMouseEvent(display, Button1, 500, 300, true);
	usleep(10000);
	SendMouseEvent(display, Button1, 500, 300, false);
}

void pageBackward(Display *display) {
	SendMouseEvent(display, Button1, 50, 300, true);
	usleep(10000);
	SendMouseEvent(display, Button1, 50, 300, false);
}

void testClick(Display *display, int x, int y) {
	SendMouseEvent(display, Button1, x, y, true);
	usleep(10000);
	SendMouseEvent(display, Button1, x, y, false);
}


void SendMouseEvent(Display *display, int button, int x, int y, bool pressed) {
	XEvent event;
	memset(&event, 0, sizeof(event));
	event.xbutton.type = pressed ? ButtonPress : ButtonRelease;
	event.xbutton.button = button;
	event.xbutton.same_screen = true;
	XQueryPointer(display, RootWindow(display, DefaultScreen(display)),
		&event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root,
		&event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

	event.xbutton.subwindow = event.xbutton.window;

	while (event.xbutton.subwindow) {
		event.xbutton.window = event.xbutton.subwindow;

		XQueryPointer(display, event.xbutton.window,
			&event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root,
			&event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	}
	event.xbutton.x = x;
	event.xbutton.y = y;
	if (debug) printf("Sending %i %i event: %ix%i\n", event.xbutton.type, event.xbutton.button, x, y);

	if (!XSendEvent(display, PointerWindow, true, 0xfff, &event))
		printf("Failed to send mouse event\n");
	XFlush(display);
}
