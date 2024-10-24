#include "drivers/vga/vga.h"

#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80

static uint16_t* vga_mem;
static uint32_t cursor;

static void vga_scroll(void);

void vga_init(void)
{
    vga_mem = (uint16_t*)0xC03FF000;
    cursor = 0;
    vga_cls();
}

void vga_cls(void)
{
    for (uint32_t i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; ++i)
    {
        *(vga_mem + i) = 3872;
    }
}

void vga_set_cursor_pos()
{

}

void vga_print(const char* str)
{
    const uint16_t attr = 3840;
    for (uint32_t i = 0; str[i] != '\0'; ++i)
    {
        if (SCREEN_HEIGHT * SCREEN_WIDTH == cursor)
        {
            cursor -= SCREEN_WIDTH;
            vga_scroll();
        }
        switch (str[i])
        {
            case '\n':
            cursor += SCREEN_WIDTH;
        case '\r':
            cursor -= cursor % SCREEN_WIDTH;
            break;
        case '\t':
            cursor -= cursor % 4;
            cursor += 4;
            break;
        default:
            vga_mem[cursor++] = (attr | str[i]);
            break;
        }

    }
}

static void vga_scroll(void)
{
    for (uint32_t i = 0; i < (SCREEN_HEIGHT - 1) * SCREEN_WIDTH; ++i)
    {
        *(vga_mem + i) = *(vga_mem + i + SCREEN_WIDTH);
    }
    for (uint32_t i = 0; i < SCREEN_WIDTH; ++i)
    {
        *(vga_mem + (SCREEN_HEIGHT-1) * SCREEN_WIDTH + i) = 3872;
    }
}
