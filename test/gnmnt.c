//
// Created by alessandro on 3/24/17.
//

#include <malloc.h>

// Generate beta1 and beta2 for transforms
void betaGen(unsigned long long *B1, unsigned long long *B2, unsigned long long *C1, unsigned long long *C2,
             unsigned long long *E1, unsigned long long *E2, unsigned int p, unsigned int log2N) {
    unsigned long long d, *A1, *A2;
    long long a1, a2, t1, t2;
    A1 = (unsigned long long *) malloc(sizeof(unsigned long long) * fN);
    A2 = (unsigned long long *) malloc(sizeof(unsigned long long) * fN);
    a1 = 2;
    a2 = 3;
    d = p - log2N - 1;
    if (d == 0) {
        d = 1;
    }
    for (loop = 0; loop < (p - 2); loop++) {
        a1 = mods(a1 * a1, p);
        a2 = mods(a2 * a2, p);
    }
    for (loop = 0; loop < d; loop++) {
        t1 = mods((a1 * a1) - (a2 * a2), p);
        t2 = mods(2 * a1 * a2, p);
        a1 = t1;
        a2 = t2;
    }
    A1[0] = 1;
    A2[0] = 0;
    for (loop = 0; loop < fNmm; loop++) {
        A1[loop + 1] = mods((a1 * A1[loop]) - (a2 * A2[loop]), p);
        A2[loop + 1] = mods((a1 * A2[loop]) + (a2 * A1[loop]), p);
    }
    for (loop = 0; loop < N; loop++) {
        B1[loop] = A1[loop << 2];
        B2[loop] = A2[loop << 2];
        C1[loop] = A1[loop << 1];
        C2[loop] = A2[loop << 1];
        E1[loop] = A1[(loop << 1) + 1];
        E2[loop] = A2[(loop << 1) + 1];
    }
    free(A2);
    free(A1);
}


// Perform Bit Reverse Order to a vector
// Derived from: http://graphics.stanford.edu/ ̃seander/bithacks.html#ReverseParallel
void bitrevorder(unsigned long long

                 *vec,
                 unsigned char log2N
) {
    unsigned long long newpos, temp;
    for (
            loop = 0;
            loop < log2N;
            loop++) {
        newpos = loop;
        newpos = ((newpos >> 1) & 0x55555555) | ((newpos & 0x55555555) << 1);
        newpos = ((newpos >> 2) & 0x33333333) | ((newpos & 0x33333333) << 2);
        newpos = ((newpos >> 4) & 0x0F0F0F0F) | ((newpos & 0x0F0F0F0F) << 4);
        newpos = ((newpos >> 8) & 0x00FF00FF) | ((newpos & 0x00FF00FF) << 8);
        newpos >>= (16 - log2N);
        if (loop < newpos) {
            temp = vec[loop];
            vec[loop] = vec[newpos];
            vec[newpos] =
                    temp;
        }
    }
}

// Forward and Inverse Radix-2 NMNT (DIT)
void nmnt(unsigned long long *oldvec, unsigned long long *vec,
          unsigned long long *b1, unsigned long long *b2,
          unsigned long long inverse) {
    unsigned int i, j, k, n, io2, ts, tmask, line1, line2, betaz, offset;
    unsigned int log2N, p;
    long long t1, t2;
    i = 2;
    io2 = 1;
    ts = N >> 1;
    tmask = ts - 1;
    for (n = 0; n < N; n++)
        vec[n] = oldvec[n];
        bitrevorder(vec, log2N);
    for (j = 1; j <= log2N; j++) {
        for (k = 0; k < (ts & tmask); k++) {
            line1 = (1 << (j - 1)) + (k << j) + 1;
            line2 = (1 << j) + (k << j) - 1;
            offset = (((N >> (ts >> 1)) * (k + 1)) - 1);
            offset = ((k + 1) << (log2N - (ts >> 1))) - 1;
            for (n = 0; n < ((1 << (j - 2))); n++) {
                betaz = n << (ts >> 1);
                t1 = mods((vec[line1] * b1[betaz]) + (vec[line2] * b2[betaz]), p);
                t2 = mods((vec[line1] * b2[betaz]) - (vec[line2] * b1[betaz]), p);
                vec[line1] = t1;
                vec[line2] = t2;
                line1++;
                184line2 = offset - n;
            }
        }
        for (k = 0; k < N; k += i)
            for (n = 0; n < io2; n++) {
                t1 = vec[k + n];
                t2 = vec[k + n + io2];
                vec[k + n] = mods(t1 + t2, p);
                vec[k + n + io2] = mods(t1 - t2, p);
            }
        io2 = i;
        i <<= 1;
        ts >>= 1;
    }
    for (j = 0; j < N; j++) {
        vec[j] = mods(vec[j] * inverse, p);
    }
}


// Forward Radix-2 ONMNT (DIT)
void onmnt(unsigned long long

           *oldvec, unsigned long long *vec,
           unsigned long long *b1, unsigned long long *b2) {
    unsigned int i, j, k, n, io2, ts, tmask, line1, line2, betaz, step;
    unsigned int log2N, p;
    long long t1, t2;
    i = 2;
    io2 = 1;
    ts = N >> 1;
    tmask = ts
            - 1;
    betaz = N >> 1;
    line1 = 0;
    line2 = 1;
    for (
            n = 0;
            n < N;
            n++)
        vec[n] = oldvec[n];
    bitrevorder(vec, log2N
    );
    for (
            j = 0;
            j < log2N;
            j++) {
        for (
                k = j;
                k < 1; k++)
            for (
                    n = 1;
                    n < N;
                    n += 2)
                vec[n] =
                        mods(vec[n]
                             * b2[betaz], p);
        for (
                k = 0;
                k < (ts & tmask); k++) {
            line1 = (1 << j) + (k << (j + 1));
            line2 = line1 + (1 << j)
                    - 1;
            step = N >> j;
            betaz = step >> 1;
            for (
                    n = 0;

                    n < (unsigned int) (1 << (j

                                              - 1)); n++) {
                t1 = mods((vec[line1]
                           * b1[betaz]) + (vec[line2] * b2[betaz]), p);
                186t2 =
                        mods((vec[line1]
                              * b2[betaz]) - (vec[line2] * b1[betaz]), p);
                vec[line1++] =
                        t1;
                vec[line2--] =
                        t2;
                betaz +=
                        step;
            }
        }
        for (
                k = 0;
                k < N;
                k += i)
            for (
                    n = 0;
                    n < io2;
                    n++) {
                t1 = vec[k + n];
                t2 = vec[k + n + io2];
                vec[k + n] =
                        mods(t1
                             + t2, p);
                vec[k + n + io2] =
                        mods(t1
                             - t2, p);
            }
        io2 = i;
        i <<= 1;
        ts >>= 1;
    }
}


// Inverse Radix-2 ONMNT (DIF)
void ionmnt(unsigned long long

            *oldvec, unsigned long long *vec,
            unsigned long long *b1, unsigned long long *b2) {
    unsigned int i, j, k, n, io2, ts, tmask, line1, line2, betaz, step;
    unsigned int log2N, p;
    long long t1, t2;
    i = N;
    io2 = i >> 1;
    ts = 1;
    tmask = (N >> 1)
            - 1;
    line1 = 0;
    line2 = 1;
    for (
            n = 0;
            n < N;
            n++)
        vec[n] = oldvec[n];
    for (
            j = log2N;
            j > 0; j--) {
        for (
                k = 0;
                k < N;
                k += i)
            for (
                    n = 0;
                    n < io2;
                    n++) {
                t1 = vec[k + n];
                t2 = vec[k + n + io2];
                vec[k + n] =
                        mods(t1
                             + t2, p);
                vec[k + n + io2] =
                        mods(t1
                             - t2, p);
            }
        for (
                k = 0;
                k < (ts & tmask); k++) {
            line1 = (1 << (j
                           - 1)) + (k << j);
            line2 = line1 + (1 << (j
                                   - 1)) - 1;
            step = N >> (j
                         - 1);
            betaz = step >> 1;
            for (
                    n = 0;

                    n < (unsigned int) (1 << (j

                                              - 2)); n++)
                188
            {
                t1 = mods((vec[line1]
                           * b1[betaz]) + (vec[line2] * b2[betaz]), p);
                t2 = mods((vec[line1]
                           * b2[betaz]) - (vec[line2] * b1[betaz]), p);
                vec[line1++] =
                        t1;
                vec[line2--] =
                        t2;
                betaz +=
                        step;
            }
        }
        for (
                k = j;
                k < 2; k++) {
            betaz = N >> 1;
            for (
                    n = 1;
                    n < N;
                    n += 2)
                vec[n] =
                        mods(vec[n]
                             * b2[betaz], p);
        }
        i = io2;
        io2 >>= 1;
        ts <<= 1;
    }
    for (
            j = 0;
            j < N;
            j++)
        vec[j] =
                mods(vec[j]
                     * sn, p);
    bitrevorder(vec, log2N
    );
}

// Forward and Inverse Radix-2 O2NMNT (DIT)
void o2nmnt(unsigned long long

            *oldvec, unsigned long long *vec,
            unsigned long long *b1, unsigned long long *b2,
            unsigned long long *e1, unsigned long long *e2,
            unsigned long long inverse
) {
    unsigned int i, j, k, n, io2, ts, tmask, line1, line2, betaz, step;
    unsigned int log2N, p;
    long long t1, t2;
    i = 2;
    io2 = 1;
    ts = N >> 1;
    tmask = ts
            - 1;
    betaz = N >> 1;
    line1 = 0;
    line2 = 1;
    for (
            n = 0;
            n < N;
            n++)
        vec[n] = oldvec[n];
    bitrevorder(vec, log2N
    );
    for (
            j = 1;
            j <=
            log2N;
            j++) {
        for (
                k = j;
                k < 2; k++)
            for (
                    n = 1;
                    n < N;
                    n += 2) {
                vec[n] =
                        mods(vec[n]
                             * b2[betaz], p);
            }
        for (
                k = 0;
                k < (ts & tmask); k++) {
            line1 = (1 << (j
                           - 1)) + (k << j);
            line2 = line1 + (1 << (j
                                   - 1)) - 1;
            step = N >> (j
                         - 1);
            190betaz = step >> 1;
            for (
                    n = 0;
                    n < ((1 << (j - 2))); n++) {
                t1 = mods((vec[line1]
                           * b1[betaz]) + (vec[line2] * b2[betaz]), p);
                t2 = mods((vec[line1]
                           * b2[betaz]) - (vec[line2] * b1[betaz]), p);
                vec[line1] =
                        t1;
                vec[line2] =
                        t2;
                line1++;
                line2--;
                betaz +=
                        step;
            }
        }
        for (
                k = 0;
                k < N;
                k += i)
            for (
                    n = 0;
                    n < io2;
                    n++) {
                t1 = vec[k + n];
                t2 = vec[k + n + io2];
                vec[k + n] =
                        mods(t1
                             + t2, p);
                vec[k + n + io2] =
                        mods(t1
                             - t2, p);
            }
        io2 = i;
        i <<= 1;
        ts >>= 1;
    }
    line1 = 0;
    line2 = N
            - 1;
    for (
            n = 0;
            n < (N >> 1); n++) {
        t1 = mods((vec[line1]
                   * e1[line1]) + (vec[line2] * e2[line1]), p);
        t2 = mods((vec[line2]
                   * e1[line2]) + (vec[line1] * e2[line2]), p);
        vec[line1] =
                t1;
        vec[line2] =
                t2;
        line1++;
        line2--;
    }
    for (
            j = 0;
            j < N;
            j++)
        vec[j] =
                mods(vec[j]
                     * inverse, p);
}