#include <stdio.h>
#include <stdlib.h>

/* Lee una imagen PGM P2 y devuelve arreglo de píxeles */
unsigned char *read_pgm(const char *filename, int *width, int *height, int *max_val) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return NULL;

    char format[3];
    fscanf(fp, "%2s", format);
    fscanf(fp, "%d %d", width, height);
    fscanf(fp, "%d", max_val);

    int total = (*width) * (*height);
    unsigned char *pixels = malloc(total);
    if (!pixels) return NULL;

    unsigned char *p = pixels;
    unsigned char *end = pixels + total;
    while (p < end) {
        int val;
        fscanf(fp, "%d", &val);
        *p = (unsigned char)val;
        p++;
    }

    fclose(fp);
    return pixels;
}

/* Aplica umbral usando solo punteros */
void apply_threshold(unsigned char *pixels, int total, int threshold) {
    unsigned char *p = pixels;
    unsigned char *end = pixels + total;
    while (p < end) {
        if (*p >= threshold)
            *p = 255;
        else
            *p = 0;
        p++;
    }
}

/* Genera negativo usando solo punteros */
unsigned char *make_negative(unsigned char *pixels, int total) {
    unsigned char *neg = malloc(total);
    if (!neg) return NULL;

    unsigned char *p = pixels;
    unsigned char *n = neg;
    unsigned char *end = pixels + total;
    while (p < end) {
        *n = 255 - *p;
        p++;
        n++;
    }

    return neg;
}

/* Escribe imagen PGM P2 */
void write_pgm(const char *filename, unsigned char *pixels, int width, int height, int max_val) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;

    fprintf(fp, "P2\n%d %d\n%d\n", width, height, max_val);

    unsigned char *p = pixels;
    unsigned char *end = pixels + (width * height);
    int col = 0;

    while (p < end) {
        fprintf(fp, "%d ", *p);
        col++;
        if (col == width) {
            fprintf(fp, "\n");
            col = 0;
        }
        p++;
    }

    fclose(fp);
}

/* Imprime estadísticas: píxeles blancos, negros y promedio */
void print_stats(unsigned char *original, unsigned char *thresholded, int total) {
    int white = 0, black = 0;
    long sum = 0;

    unsigned char *o = original;
    unsigned char *t = thresholded;
    unsigned char *end = original + total;

    while (o < end) {
        sum += *o;
        if (*t == 255) white++;
        else black++;
        o++;
        t++;
    }

    printf("Blancos: %d\nNegros: %d\nPromedio original: %.2f\n", white, black, (double)sum / total);
}

int main(void) {
    int width, height, max_val, threshold;

    unsigned char *pixels = read_pgm("input.pgm", &width, &height, &max_val);
    if (!pixels) {
        printf("Error leyendo la imagen\n");
        return 1;
    }

    int total = width * height;

    /* Copia original para estadísticas */
    unsigned char *original = malloc(total);
    if (!original) {
        free(pixels);
        return 1;
    }

    unsigned char *p = pixels;
    unsigned char *o = original;
    unsigned char *end = pixels + total;
    while (p < end) {
        *o = *p;
        p++;
        o++;
    }

    printf("Ingrese umbral T: ");
    scanf("%d", &threshold);

    apply_threshold(pixels, total, threshold);

    unsigned char *negative = make_negative(pixels, total);
    if (!negative) {
        free(pixels);
        free(original);
        return 1;
    }

    write_pgm("output_threshold.pgm", pixels, width, height, 255);
    write_pgm("output_negative.pgm", negative, width, height, 255);

    print_stats(original, pixels, total);

    free(pixels);
    free(original);
    free(negative);

    return 0;
}
