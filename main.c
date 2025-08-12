#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char VERSION[] = "1.0";

void print_help(char *name);
void print_version(char *name);

int main(int argc, char *argv[]) {
    char prompt[1024];
    int delay_ms = 500; // Default delay (in ms)

    if (argc > 1) {
        // Check if last arg is only digits
        int last_is_number = 1;
        char *last_arg = argv[argc - 1];
        
        // Help and Version info
        if (argc == 2 && (strcmp(argv[1], "-V") == 0 || strcmp(argv[1], "--version") == 0)) {
            print_version(argv[0]);
            return 0;
        }

        if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
            print_help(argv[0]);
            return 0;
        }

        // Check for empty string or leading minus (negative numbers)
        if (*last_arg == '\0' || *last_arg == '-') {
            last_is_number = 0;
        } else {
            for (char *p = last_arg; *p; p++) {
                if (!isdigit((unsigned char)*p)) {
                    last_is_number = 0;
                    break;
                }
            }
        }

        // Determine end index for prompt building
        int end_index = last_is_number ? argc - 1 : argc;
        
        // Set delay if last arg is a number
        if (last_is_number) {
            delay_ms = atoi(last_arg);
            // Ensure delay is reasonable (between 1ms and 5000ms)
            if (delay_ms < 1) delay_ms = 1;
            if (delay_ms > 5000) delay_ms = 5000;
        }

        // Build prompt from remaining args (excluding delay if present)
        prompt[0] = '\0';
        for (int i = 1; i < end_index; i++) {
            // Check if adding this arg would overflow the buffer
            if (strlen(prompt) + strlen(argv[i]) + 2 >= sizeof(prompt)) {
                fprintf(stderr, "Warning: Message too long, truncated.\n");
                break;
            }
 
            strcat(prompt, argv[i]);
            if (i < end_index - 1) {
                strcat(prompt, " ");
            }
        }
        
        // If we only had a delay argument, use default message
        if (prompt[0] == '\0') {
            strcpy(prompt, "Hello, World!");
        }
    } else { // Default Output without CLI Args
        strcpy(prompt, "Hello, World!");
    }

    // Print characters one by one with delay
    size_t len = strlen(prompt);
    for (size_t i = 0; i < len; i++) {
        printf("%c", prompt[i]);
        fflush(stdout);
        usleep(delay_ms * 1000);
    }
    printf("\n");
    
    return 0;
}

void print_version(char *name) {
    printf("%s (SlowType) v%s\n", name, VERSION);
    printf("A vintage computing console buffer emulator.\n");
    printf("Simulates character-by-character output for retro systems.\n");
    printf("Copyright (c) 2025 Riley Ava\n");
    printf("License MPLv2: Mozilla Public Licenese version 2 <https://www.mozilla.org/en-US/MPL/2.0/>\n");
    printf("This is free software, you are free to change and redistribute (follow MPL2)\n");
    printf("There is NO WARRANTY, to the extent permitted by law.\n");
    printf("\nWritten by Riley Ava\n");
}

void print_help(char *name) {
    printf("Usage: %s [text...] [delay_ms]\n", name);
    printf("       %s [options]\n\n", name);
    printf("Console Buffer - Vintage computing output buffer\n\n");
    printf("Provides character-by-character output buffering for systems that lack\n");
    printf("native console buffering. Ideal for vintage hardware (6502, Z80, 8080)\n");
    printf("accessed via terminal adapters, SSH emulators, or serial connections.\n\n");
    printf("Perfect for:\n");
    printf("  • Actual vintage computers (Apple II, C64, etc.) via terminal adapters\n");
    printf("  • SSH connections to retro computing projects\n");
    printf("  • Serial terminal emulation with older hardware\n");
    printf("  • Modern systems simulating vintage output behavior\n\n");
    printf("Arguments:\n");
    printf("  text...     Message to display (default: \"Hello, World!\")\n");
    printf("  delay_ms    Character output delay in milliseconds (1-5000, default: 500)\n");
    printf("              Hardware timing suggestions:\n");
    printf("                1500ms  = 1MHz 6502 (Apple II, early systems)\n");
    printf("                1000ms  = 1.8MHz Z80 (TRS-80, CP/M systems)\n");
    printf("                500ms   = 2MHz+ systems (C64, Atari 800)\n");
    printf("                200ms   = Fast vintage (4MHz+ systems)\n");
    printf("                50ms    = Modern retro emulation\n\n");
    printf("Options:\n");
    printf("  -h, --help     Show this help message\n");
    printf("  -v, --version  Show version information\n\n");
    printf("Examples:\n");
    printf("  %s \"APPLE ][ READY\" 1500      # Apple II simulation\n", name);
    printf("  %s \"A>\" 1000                 # CP/M prompt on Z80\n", name);
    printf("  %s \"READY.\" 800              # C64 BASIC prompt\n", name);
    printf("  %s \"login:\" 200              # Terminal login prompt\n", name);
}
