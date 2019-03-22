
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>

typedef unsigned long int ui;

bool get_next(mpz_t out, mpz_t num) {
    //note, num gets set to 1

    // if num < 10:
    if (mpz_cmp_ui(num, 10) < 0) {
        return false;
    }

    // out = 1
    mpz_set_ui(out, 1);
    // while num > 0:
    while (mpz_cmp_ui(num, 0) > 0) {
        // num /= 10
        ui digit = mpz_fdiv_q_ui(num, num, 10);
        // out *= 10
        mpz_mul_ui(out, out, digit);
    }

    return true;
}

ui multiplication_persistence(mpz_t num, bool verbose, ui start) {
    mpz_t next;
    ui iters = start;

    mpz_init(next);

    if (verbose) {
        mpz_out_str(stdout, 10, num);
        putchar('\n');
    }

    while (get_next(next, num)) {
        iters += 1;

        mpz_t temp;
        mpz_init_set(temp, num);
        mpz_init_set(num, next);
        mpz_init_set(next, temp);

        if (verbose) {
            mpz_out_str(stdout, 10, num);
            putchar('\n');
        }
    }

    return iters;
}

void smart_search(ui digits) {
    printf("digits: %lu\n", digits);

    mpz_t num, threes;
    mpz_init(num);
    mpz_init(threes);


    ui search_len = ((digits + 1) * (digits + 2)) / 2;
    ui count = 0;

    ui max_int = 0;
    max_int -= 1;

    for(ui i = digits; (i >= 0) && (i != max_int); i--) {
        for(ui k = 0; k < digits - i + 1; k++) {
            ui j = digits - (i + k);


            mpz_set_ui(num, 1); // num = 1
            mpz_ui_pow_ui(num, 7, k); //num = 7^k
            mpz_mul_2exp(num, num, i); // num *= 2^i

            mpz_ui_pow_ui(threes, 3, k); //threes = 3^k
            mpz_mul(num, num, threes);

            ui pers = multiplication_persistence(num, false, 1);
            if (pers > 2) { // only logging the interesting ones
                printf("%s \t %lu\n", buf, pers);
            }

            count += 1;
            //printf("%lu of %lu\n", count, search_len);
        }
    }

}

ui loop(mpz_t count, mpz_t start) {

    ui best, iterations;
    best = 0;

    mpz_t num, next, limit;
    mpz_init(num);
    mpz_init(next);
    mpz_init(limit);

    mpz_init_set(num, start);
    mpz_add(limit, start, count);

    while (mpz_cmp(limit, num) > 0) {
        mpz_add_ui(next, num, 1);

        mpz_out_str(stdout, 10, num);

        iterations = multiplication_persistence(num, false, 0);

        if (iterations > best) {
            best = iterations;
        }
        printf("\t ITR: %lu \t BEST: %lu \n", iterations, best);

        mpz_t temp;
        mpz_init_set(temp, num);
        mpz_init_set(num, next);
        mpz_init_set(next, temp);
    }

    return best;
}

int dumb_iterator_main(int argc, char *argv[]) {

    mpz_t count;
    mpz_t start;
    ui iterations;

    mpz_init(count);
    mpz_init(start);

    if (argc == 1) {
        mpz_set_str(count, "10000", 10);
        mpz_set_str(start, "1", 10);
    } else if (argc == 2) {
        mpz_set_str(count, argv[1], 10);
        mpz_set_str(start, "1", 10);
    } else {
        mpz_set_str(count, argv[1], 10);
        mpz_set_str(start, argv[2], 10);
    }

    loop(count, start);


    return 0;

}

int main(int argc, char* argv[]) {
    ui digits = 20;
    ui max_digits = 20;

    if (argc > 1) {
        digits = strtoul(argv[1], NULL, 10);
        max_digits = digits;
    }

    if (argc > 2) {
        max_digits = strtoul(argv[2], NULL, 10);
        max_digits = (max_digits >= digits) ? max_digits : digits;
    }

    for (ui d = digits; d <= max_digits; d++) {
        smart_search(d);
    }

    return 0;
}
