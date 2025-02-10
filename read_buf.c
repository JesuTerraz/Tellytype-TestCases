extern void
print_buf(char *buf, int max_size)
{
    fprintf(stdout, "[");
    for (int i = 0; i < max_size; i++) {
        char e =  buf[i];
        switch(e) {
            case '\r':
                fprintf(stdout, "\\r");
                break;
            case '\n':
                fprintf(stdout, "\\n");
                break;
            case '\b':
                fprintf(stdout, "\\b");
                break;
            default:
                fprintf(stdout, "%c", e);
        }

        if (i != max_size - 1) fprintf(stdout, ", ");
    }
    fprintf(stdout, "]\n\n");
}