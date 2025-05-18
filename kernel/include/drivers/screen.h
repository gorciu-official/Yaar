/**
 * ================================================================
 *                            AurorOS
 * ================================================================
 * 
 * This code is served by the terms specified in the AurorOS 
 * license. If you did not get one, you can get a copy on AurorOS's
 * original repository: https://github.com/Interpuce/AurorOS and
 * then switching the tab from ReadMe to License.
*/

extern void vga_put_char(char c, int color);
extern void vga_print(const char* str, int color);

inline void putchar(char c, int color) {
    vga_put_char(c, color);
}

inline void print(const char* c, int color) {
    vga_print(c, color);
}