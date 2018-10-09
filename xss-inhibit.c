#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/extensions/scrnsaver.h>

void handle(int t) {
    (void) t;
}

int main() {
    if (signal(SIGINT, handle) == SIG_ERR || signal(SIGTERM, handle) == SIG_ERR) {
        printf("Warning: failed to handle SIGINT/SIGTERM\n");
    }

    Display *d = XOpenDisplay(NULL);
    if (!d) {
        printf("Failed to open display\n");
        return 1;
    }

    int x, y;
    if (!XScreenSaverQueryExtension(d, &x, &y)) {
        printf("Failed to XScreenSaverQueryExtension\n");
        goto end;
    }

    x = y = 0;
    if (!XScreenSaverQueryVersion(d, &x, &y)) {
        printf("Failed to XScreenSaverQueryVersion\n");
        goto end;
    }
    printf("XScreenSaver %d.%d\n", x, y);

    XScreenSaverSuspend(d, 1);
    XScreenSaverSuspend(d, 1);
    printf("Screensaver inhibited.\n");

    pause();

    printf("Exiting.\n");
    XCloseDisplay(d);
    return 0;
end:
    XCloseDisplay(d);
    return 1;
}
