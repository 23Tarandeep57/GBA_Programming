#include "toolBox.h"

int main()
{
    int ii, jj;

    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

    m3_fill(RGB15(12, 12, 14));

    m3_rect(12, 8, 108, 72, CLR_RED);
    m3_rect(108, 72, 132, 88, CLR_LIME);
    m3_rect(132, 88, 228, 152, CLR_BLUE);

    m3_frame(132, 8, 228, 72, CLR_CYAN);
    m3_frame(109, 73, 131, 87, CLR_BLACK);
    m3_frame(12, 88, 108, 152, CLR_YELLOW);

    for(ii = 0; ii <= 8; ii++)
    {
        jj = 3 * ii + 7;

        m3_line(
            132 + 11 * ii, 9,
            226, 12 + 7 * ii,
            RGB15(jj, 0, jj)
        );

        m3_line(
            226 - 11 * ii, 70,
            133, 69 - 7 * ii,
            RGB15(jj, 0, jj)
        );
    }

    while(1);

    return 0;
}
