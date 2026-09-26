#include "ComplexGJ.h"

static void swap_rows(cplx A[N_MAX][N_MAX], cplx b[N_MAX], int n, int r1, int r2) {
    for (int j = 0; j < n; j++) {
        cplx tmp = A[r1][j];
        A[r1][j] = A[r2][j];
        A[r2][j] = tmp;
    }
    cplx tmpb = b[r1];
    b[r1] = b[r2];
    b[r2] = tmpb;
}

int solve_complex_system(int n, cplx A[N_MAX][N_MAX], cplx b[N_MAX], cplx x[N_MAX]) {
    if (n <= 0 || n > N_MAX) return 1;

    for (int k = 0; k < n; k++) {
        int p = k;
        float maxv = fabsf(A[k][k].r) + fabsf(A[k][k].i);
        for (int i = k + 1; i < n; i++) {
            float v = fabsf(A[i][k].r) + fabsf(A[i][k].i);
            if (v > maxv) { maxv = v; p = i; }
        }
        if (maxv < 1e-7f) return 1;

        if (p != k) swap_rows(A, b, n, k, p);

        cplx pivot = A[k][k];
        for (int i = k + 1; i < n; i++) {
            cplx m = c_div(A[i][k], pivot);
            for (int j = k; j < n; j++)
                A[i][j] = c_sub(A[i][j], c_mul(m, A[k][j]));
            b[i] = c_sub(b[i], c_mul(m, b[k]));
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        cplx sum = {0,0};
        for (int j = i + 1; j < n; j++)
            sum = c_add(sum, c_mul(A[i][j], x[j]));
        x[i] = c_div(c_sub(b[i], sum), A[i][i]);
    }
    return 0;
}

void itoa_simple(int n, char* buf, int* index) {
    if(n == 0) { buf[(*index)++] = '0'; return; }
    if(n < 0) { buf[(*index)++] = '-'; n = -n; }
    char temp[10]; int t = 0;
    while(n > 0) { temp[t++] = '0' + (n % 10); n /= 10; }
    for(int i = t-1; i >=0; i--) buf[(*index)++] = temp[i];
}


void ftoa_for_oled(float f, char* buf, int* index, int digits) {
    if(f < 0) { buf[(*index)++] = '-'; f = -f; }
    else  {buf[(*index)++] = '+';}

    int int_part = (int)f;
    float frac_part = f - int_part;
    itoa_simple(int_part, buf, index);

    buf[(*index)++] = '.';  // decimal point

    for(int i=0; i<digits; i++){
        frac_part *= 10;
        int d = (int)frac_part;
        buf[(*index)++] = '0' + d;
        frac_part -= d;
    }
}