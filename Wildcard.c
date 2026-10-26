#include <stdbool.h>

bool isMatch(char* s, char* p) {
    int s_ptr = 0, p_ptr = 0;
    int star_idx = -1;
    int s_tmp_idx = -1;

    while (s[s_ptr] != '\0') {
        // Case 1: Characters match, or pattern contains '?'
        if (p[p_ptr] == '?' || p[p_ptr] == s[s_ptr]) {
            s_ptr++;
            p_ptr++;
        }
        // Case 2: Pattern contains '*'
        else if (p[p_ptr] == '*') {
            star_idx = p_ptr;
            s_tmp_idx = s_ptr;
            p_ptr++; // Move past the '*' assuming it matches 0 characters initially
        }
        // Case 3: Mismatch, but a previous '*' was encountered
        else if (star_idx != -1) {
            p_ptr = star_idx + 1; // Backtrack pattern pointer to after the '*'
            s_tmp_idx++;          // Force the '*' to consume one more character from s
            s_ptr = s_tmp_idx;    // Advance string pointer to the new checkpoint
        }
        // Case 4: Mismatch and no '*' to fall back on
        else {
            return false;
        }
    }

    // Check for remaining characters in pattern; they must all be '*'
    while (p[p_ptr] == '*') {
        p_ptr++;
    }

    return p[p_ptr] == '\0';
}
