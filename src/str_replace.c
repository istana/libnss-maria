#include "str_replace.h"

// You must free the result if result is non-NULL.
char *str_replace(const char *orig, const char *rep, const char *with) {
    char orig_buff[2048]; // copy of the original string
    char *orig_buffp; // pointer to orig_buff array
    char *result; // the return string
    const char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep) {
        return NULL;
    }
    len_rep = strlen(rep);
    if (len_rep == 0) {
        return NULL; // empty rep causes infinite loop during count
    }
    if (!with) {
        with = "";
    }
    len_with = strlen(with);

    memset(orig_buff, 0, sizeof(orig_buff));
    strncpy(orig_buff, orig, 2047);
    if (orig_buff[2046] != '\0') {
        maria_log("string replace buffer too small");
        return NULL;
    }

    // count the number of replacements needed
    ins = orig_buff;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(sizeof(char) * (strlen(orig_buff) + (len_with - len_rep) * count + 1));

    if (!result) {
        return NULL;
    }

    orig_buffp = orig_buff;
    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig_copy
    //    orig_copy points to the remainder of orig_copy after "end of rep"
    while (count--) {
        ins = strstr(orig_buffp, rep);
        len_front = ins - orig_buffp;
        tmp = strncpy(tmp, orig_buffp, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig_buffp += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig_buffp);
    return result;
}
