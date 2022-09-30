#include <check.h>
#include "s21_matrix.h"

matrix_t bax1, bax11, bax2, bax3, bax4;

void create_bax1() {
    s21_create_matrix(3, 3, &bax1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0, n = 1; j < 3; j++, n++) {
            bax1.matrix[i][j] = n;
        }
    }
}

void create_bax11() {
    s21_create_matrix(3, 3, &bax11);
    for (int i = 0; i < 3; i++) {
        for (int j = 0, n = 1; j < 3; j++, n++) {
            bax11.matrix[i][j] = n;
        }
    }
}

void create_bax2() {
    s21_create_matrix(2, 6, &bax2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0, n = 4; j < 6; j++, n+=2) {
            bax2.matrix[i][j] = n;
        }
    }
}

void create_bax3() {
    s21_create_matrix(3, 3, &bax3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0, n = 2; j < 3; j++, n+=2) {
            bax3.matrix[i][j] = n;
        }
    }
}

void create_bax4() {
    s21_create_matrix(3, 3, &bax4);
    bax4.matrix[0][0] = 2;
    bax4.matrix[0][1] = 5;
    bax4.matrix[0][2] = 7;
    bax4.matrix[1][0] = 6;
    bax4.matrix[1][1] = 3;
    bax4.matrix[1][2] = 4;
    bax4.matrix[2][0] = 5;
    bax4.matrix[2][1] = -2;
    bax4.matrix[2][2] = -3;
}

START_TEST(s21_eq_matrix_test) {
    create_bax1();
    create_bax11();
    create_bax2();
    create_bax3();
    ck_assert_int_eq(s21_eq_matrix(&bax1, &bax11), SUCCESS);
    ck_assert_int_eq(s21_eq_matrix(&bax1, &bax2), FAILURE);
    ck_assert_int_eq(s21_eq_matrix(&bax1, &bax3), FAILURE);
    s21_remove_matrix(&bax1);
    s21_remove_matrix(&bax11);
    s21_remove_matrix(&bax2);
    s21_remove_matrix(&bax3);
}
END_TEST

START_TEST(s21_sum_matrix_test) {
    matrix_t comp1, result1, result2;
    create_bax1();
    create_bax11();
    create_bax2();
    s21_create_matrix(3, 3, &comp1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0, n = 2; j < 3; j++, n+=2) {
            comp1.matrix[i][j] = n;
        }
    }
    s21_sum_matrix(&bax1, &bax11, &result1);
    ck_assert_int_eq(s21_eq_matrix(&result1, &comp1), SUCCESS);
    int res = s21_sum_matrix(&bax1, &bax2, &result2);
    ck_assert_int_eq(res, 2);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&comp1);
    s21_remove_matrix(&bax1);
    s21_remove_matrix(&bax11);
    s21_remove_matrix(&bax2);
}
END_TEST

START_TEST(s21_sub_matrix_test) {
    matrix_t comp1, result1, result2;
    create_bax1();
    create_bax11();
    create_bax2();
    s21_create_matrix(3, 3, &comp1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            comp1.matrix[i][j] = 0;
        }
    }
    s21_sub_matrix(&bax1, &bax11, &result1);
    ck_assert_int_eq(s21_eq_matrix(&result1, &comp1), SUCCESS);
    int res = s21_sub_matrix(&bax1, &bax2, &result2);
    ck_assert_int_eq(res, 2);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&comp1);
    s21_remove_matrix(&bax1);
    s21_remove_matrix(&bax11);
    s21_remove_matrix(&bax2);
}
END_TEST

START_TEST(s21_mult_number_test) {
    matrix_t comp1, result;
    create_bax1();
    s21_create_matrix(3, 3, &comp1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0, n = 1; j < 3; j++, n++) {
            comp1.matrix[i][j] = n * 3;
        }
    }
    s21_mult_number(&bax1, 3, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &comp1), SUCCESS);
    s21_remove_matrix(&result);
    s21_remove_matrix(&comp1);
    s21_remove_matrix(&bax1);
}
END_TEST

START_TEST(s21_mult_matrix_test) {
    matrix_t comp1, result;
    create_bax1();
    create_bax11();
    s21_create_matrix(3, 3, &comp1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0, n = 6; j < 3; j++, n+=6) {
            comp1.matrix[i][j] = n;
        }
    }
    s21_mult_matrix(&bax1, &bax11, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &comp1), SUCCESS);
    s21_remove_matrix(&result);
    s21_remove_matrix(&comp1);
    s21_remove_matrix(&bax1);
    s21_remove_matrix(&bax11);
}
END_TEST

START_TEST(s21_transpose_test) {
    matrix_t comp1, result;
    create_bax1();
    s21_create_matrix(3, 3, &comp1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0, n = 1; j < 3; j++, n++) {
            comp1.matrix[j][i] = n;
        }
    }
    s21_transpose(&bax1, &result);
    ck_assert_int_eq(s21_eq_matrix(&result, &comp1), SUCCESS);
    s21_remove_matrix(&result);
    s21_remove_matrix(&comp1);
    s21_remove_matrix(&bax1);
}
END_TEST

START_TEST(s21_calc_complements_test) {
    matrix_t comp1, result1;
    create_bax4();
    s21_create_matrix(3, 3, &comp1);
    comp1.matrix[0][0] = -1;
    comp1.matrix[0][1] = 38;
    comp1.matrix[0][2] = -27;
    comp1.matrix[1][0] = 1;
    comp1.matrix[1][1] = -41;
    comp1.matrix[1][2] = 29;
    comp1.matrix[2][0] = -1;
    comp1.matrix[2][1] = 34;
    comp1.matrix[2][2] = -24;
    s21_calc_complements(&bax4, &result1);
    ck_assert_int_eq(s21_eq_matrix(&result1, &comp1), SUCCESS);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&comp1);
    s21_remove_matrix(&bax4);
}
END_TEST

START_TEST(s21_determinant_test) {
    double result;
    create_bax1();
    create_bax2();
    create_bax4();
    s21_determinant(&bax1, &result);
    ck_assert_double_eq_tol(result, 0.0, 1e-6);
    s21_determinant(&bax2, &result);
    ck_assert_double_eq_tol(result, 0.0, 1e-6);
    s21_determinant(&bax4, &result);
    ck_assert_double_eq_tol(result, -1.0, 1e-6);
    s21_remove_matrix(&bax1);
    s21_remove_matrix(&bax2);
    s21_remove_matrix(&bax4);
}
END_TEST

START_TEST(s21_inverse_matrix_test) {
    matrix_t comp1, result1;
    create_bax4();
    s21_create_matrix(3, 3, &comp1);
    comp1.matrix[0][0] = 1;
    comp1.matrix[0][1] = -1;
    comp1.matrix[0][2] = 1;
    comp1.matrix[1][0] = -38;
    comp1.matrix[1][1] = 41;
    comp1.matrix[1][2] = -34;
    comp1.matrix[2][0] = 27;
    comp1.matrix[2][1] = -29;
    comp1.matrix[2][2] = 24;
    s21_inverse_matrix(&bax4, &result1);
    ck_assert_int_eq(s21_eq_matrix(&result1, &comp1), SUCCESS);
    s21_remove_matrix(&result1);
    s21_remove_matrix(&comp1);
    s21_remove_matrix(&bax4);
}
END_TEST

int main() {
    Suite *suite = suite_create("S21_TESTS");
    SRunner *srunner = srunner_create(suite);

    TCase *s21_eq_matrix_case = tcase_create("s21_eq_matrix_case");
    suite_add_tcase(suite, s21_eq_matrix_case);
    tcase_add_test(s21_eq_matrix_case, s21_eq_matrix_test);

    TCase *s21_sum_matrix_test_case = tcase_create("s21_sum_matrix_test_case");
    suite_add_tcase(suite, s21_sum_matrix_test_case);
    tcase_add_test(s21_sum_matrix_test_case, s21_sum_matrix_test);

    TCase *s21_sub_matrix_test_case = tcase_create("s21_sub_matrix_test_case");
    suite_add_tcase(suite, s21_sub_matrix_test_case);
    tcase_add_test(s21_sub_matrix_test_case, s21_sub_matrix_test);

    TCase *s21_mult_number_test_case = tcase_create("s21_mult_number_test_case");
    suite_add_tcase(suite, s21_mult_number_test_case);
    tcase_add_test(s21_mult_number_test_case, s21_mult_number_test);

    TCase *s21_mult_matrix_test_case = tcase_create("s21_mult_matrix_test_case");
    suite_add_tcase(suite, s21_mult_matrix_test_case);
    tcase_add_test(s21_mult_matrix_test_case, s21_mult_matrix_test);

    TCase *s21_transpose_case = tcase_create("s21_transpose_case");
    suite_add_tcase(suite, s21_transpose_case);
    tcase_add_test(s21_transpose_case, s21_transpose_test);

    TCase *s21_calc_complements_case = tcase_create("s21_calc_complements_case");
    suite_add_tcase(suite, s21_calc_complements_case);
    tcase_add_test(s21_calc_complements_case, s21_calc_complements_test);

    TCase *s21_determinant_case = tcase_create("s21_determinant_case");
    suite_add_tcase(suite, s21_determinant_case);
    tcase_add_test(s21_determinant_case, s21_determinant_test);

    TCase *s21_inverse_matrix_case = tcase_create("s21_inverse_matrix_case");
    suite_add_tcase(suite, s21_inverse_matrix_case);
    tcase_add_test(s21_inverse_matrix_case, s21_inverse_matrix_test);

    srunner_run_all(srunner, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(srunner);
    srunner_free(srunner);
    return (number_failed == 0) ? 0 : 1;
}
