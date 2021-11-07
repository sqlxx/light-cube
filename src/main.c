#include <stc12.h>

#define LEVEL P0
#define ROW P1
#define COL P2
#define FRAME_COUNT 7 

typedef unsigned char uint8;
typedef uint8 ar_image[8];


// unsigned char image[8][8] = {
// {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}, 
// {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01},
// {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
// {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01},
// {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
// {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01},
// {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
// {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01},
// };

uint8 image[8][8] = {
{0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xff}, 
{0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81}, 
{0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81}, 
{0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81}, 
{0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81}, 
{0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81}, 
{0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81}, 
{0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xff}, 
};

// uint8 image2[8][8] = {
// {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80}, 
// {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40}, 
// {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20}, 
// {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10}, 
// {0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08}, 
// {0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}, 
// {0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02}, 
// {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}, 
// };

// ar_image* images[2] = {
//     image1 
// // };

// uint8 imageCount = 2;

void _delay(int _10us) {
    uint8 j;

    do {
        j = 2;
        //j = 182 is ms
        while(--j);
    } while (--_10us);
}

void _delayMs(int ms) {
    unsigned char j;

    do {
        j = 182;
        while(--j);
    } while (--ms);
}

void display(uint8 cur_frame[8][8]) {
    uint8 i= 0, j = 0;
    LEVEL = 0x00;

    for (i=0; i<8; i++) {
        LEVEL = 0x00;
        for (j=0; j<8; j++) {
           COL = (0x01 << j);
           ROW = cur_frame[i][j]; 
        }

        LEVEL = (0x01 << i);
        _delayMs(2);
    }
}

void display_frame(uint8 image[][8]) {
    uint8 i = FRAME_COUNT;
    do {
        display(image);
    } while (i-- >0);
}

// void generateFrame(int step) {
//     if (step == 0) {
//         for (uint8 i = 0; i < 8; i ++) {
//             for (uint8 j = 0; j < 8; j ++) {
//                 image[i][j] = 0x01 << i;
//             }
//         }
//     } else if (step == 1) {
//         for (uint8 i = 0; i < 8; i ++) {
//             for (uint8 j = 0; j < 8; j ++) {
//                 image[i][j] = 0x80 >> i;
//             }
//         }
//     }
// }


void generateFrame(int step) {
    if (step == 0) {
        for (uint8 i = 0; i < 8; i ++) {
            for (uint8 j = 0; j < 8; j ++) {
                if ((i == 3 || i == 4) && (j == 3 || j == 4)) {
                    image[i][j] = 0x18;

                } else {
                    image[i][j] = 0x00;
                }
            }
        }
    } else if (step == 1 || step == 5) {
        for (uint8 i = 0; i < 8; i ++) {
            for (uint8 j = 0; j < 8; j ++) {
                if ((i == 2 || i == 5) && (j == 2 || j == 5)) {
                    image[i][j] = 0x3c;

                } else if ((j == 2 || j == 5) || (i == 2 || i == 5)) {
                    image[i][j] = 0x24;
                } else {
                    image[i][j] = 0x00;
                }
            }
        }
    } else if (step == 2 || step == 4) {
        for (uint8 i = 0; i < 8; i ++) {
            for (uint8 j = 0; j < 8; j ++) {
                if ((i == 1 || i == 6) && (j == 1 || j == 6)) {
                    image[i][j] = 0x7e;

                } else if ((j == 1 || j == 6) || (i == 1 || i == 6)) {
                    image[i][j] = 0x42;
                } else {
                    image[i][j] = 0x00;
                }
            }
        }
    } else if (step == 3) {
        for (uint8 i = 0; i < 8; i ++) {
            for (uint8 j = 0; j < 8; j ++) {
                if ((i == 0 || i == 7) && (j == 0 || j == 7)) {
                    image[i][j] = 0xff;
                } else if ((i == 0 || i == 7) || ( j == 0 || j == 7)) {
                    image[i][j] = 0x81;
                } else {
                    image[i][j] = 0x00;
                }
            }
        }
    }
}

int main() {
    COL = 0x00;
    ROW = 0x00;
    LEVEL = 0x00;
    uint8 step = 6;
    uint8 i;
    while (1) {
        for (i = 0; i < step; i ++) {
            generateFrame(i);
            display_frame(image);
        }
    }

}
