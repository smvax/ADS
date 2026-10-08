//#include "pch.h"
#include <gtest/gtest.h>

#include "memdata.h"

TEST(FunctionsForMemData, can_calculate_capacity) {
    int size1 = 16;
    int size2 = 151;

    EXPECT_EQ(calculate_capacity(size1), MEM_STEP * 2);
    EXPECT_EQ(calculate_capacity(size2), MEM_STEP * 11);
}

TEST(ClassMemData, can_create_with_default_constructor) {
    MemData<double> D1;

    EXPECT_EQ(D1.get_size(), 0);
    EXPECT_EQ(D1.get_capacity(), MEM_STEP);
}

TEST(ClassMemData, can_create_with_constructor_by_size) {
    MemData<double> D1(10);
    MemData<double> D2(1231336);

    EXPECT_EQ(D1.get_size(), 0);
    EXPECT_EQ(D1.get_capacity(), MEM_STEP);
    EXPECT_EQ(D2.get_size(), 0);
    EXPECT_EQ(D2.get_capacity(), (1231336 / MEM_STEP + 1) * MEM_STEP);
}

TEST(ClassMemData, can_create_with_constructor_by_initializer_list) {
    MemData<double> D1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    MemData<double> D2({});
    double example1[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

    EXPECT_EQ(D1.get_size(), 16);
    EXPECT_EQ(D1.get_capacity(), MEM_STEP * 2);
    EXPECT_EQ(D2.get_size(), 0);
    EXPECT_EQ(D2.get_capacity(), MEM_STEP);
    for (size_t i = 0; i < D1.get_size(); i++) {
        EXPECT_EQ(D1.get_data_const()[i], example1[i]);
    }
}

TEST(ClassMemData, can_create_with_init_constructor) {
    double* list1 = new double[16];
    double* list2 = new double[0];
    MemData<double> D1(list1, 16);
    MemData<double> D2(list2, 0);

    EXPECT_EQ(D1.get_size(), 16);
    EXPECT_EQ(D1.get_capacity(), MEM_STEP * 2);
    EXPECT_EQ(D2.get_size(), 0);
    EXPECT_EQ(D2.get_capacity(), MEM_STEP);
    for (size_t i = 0; i < D1.get_size(); i++) {
        EXPECT_EQ(D1.get_data_const()[i], list1[i]);
    }
    for (size_t i = 0; i < D2.get_size(); i++) {
        EXPECT_EQ(D2.get_data_const()[i], list2[i]);
    }
}

TEST(ClassMemData, can_create_with_copy_constructor) {
    MemData<double> D1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    MemData<double> D2(D1);
    MemData<double> D3;

    EXPECT_TRUE(D1 == D2);
    EXPECT_FALSE(D1 == D3);
    EXPECT_FALSE(D1.get_data_const() == D2.get_data_const());
}

TEST(ClassMemData, can_create_with_move_constructor) {
    MemData<double> D1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    MemData<double> D4(D1);
    MemData<double> D2(std::move(D1));
    MemData<double> D3;

    EXPECT_FALSE(D1 == D2);
    EXPECT_TRUE(D1 == D3);
    EXPECT_FALSE(D2 == D3);
    EXPECT_TRUE(D1.get_data_const() == nullptr);
    EXPECT_TRUE(D2 == D4);
}

TEST(ClassMemData, can_is_empty) {
    MemData<double> D1;
    MemData<double> D2(0);
    MemData<double> D3(1);
    MemData<double> D4({ 1,2,3 });
    MemData<double> D5({ 1,2,3,0 });
    double* list1 = new double[3];
    list1[0] = 1;
    list1[1] = 2;
    list1[2] = 3;
    double* list2 = new double[3];
    list2[0] = 4;
    list2[1] = 5;
    list2[2] = 6;
    MemData<double> D6(list1, 3);
    MemData<double> D7(list2, 3);

    EXPECT_TRUE(D1.is_empty());
    EXPECT_TRUE(D2.is_empty());
    EXPECT_TRUE(D3.is_empty());
    EXPECT_FALSE(D4.is_empty());
    EXPECT_FALSE(D5.is_empty());
    EXPECT_FALSE(D6.is_empty());
    EXPECT_FALSE(D7.is_empty());
}

//TEST(ClassMemData, can_is_full) { //убрали, лишний

TEST(ClassMemData, can_set_memory_for_empty) {
    MemData<double> D1;
    D1.set_memory(1000);

    EXPECT_EQ(D1.get_capacity(), (1000 / MEM_STEP + 1) * MEM_STEP);
}

TEST(ClassMemData, can_set_memory_for_not_empty) {
    MemData<double> D1({ 1,2,3 });
    D1.set_memory(1000);

    EXPECT_EQ(D1.get_capacity(), (1000 / MEM_STEP + 1) * MEM_STEP);
}

TEST(ClassMemData, can_reset_memory_for_empty) {
    MemData<double> D1;
    double* old_data = new double[D1.get_capacity()];
    size_t old_size = D1.get_size();
    for (size_t i = 0; i < old_size; i++) {
        old_data[i] = (D1.get_data_const()[i]);
    }
    D1.reset_memory(1000, 0);

    for (size_t i = 0; i < old_size; i++) {
        EXPECT_EQ(D1.get_data_const()[i], old_data[i]);
    }
    EXPECT_EQ(D1.get_capacity(), (1000 / MEM_STEP + 1) * MEM_STEP);
}

TEST(ClassMemData, can_reset_memory_for_not_empty_increase) {
    MemData<double> D1({ 1,2,3,4,5 });
    double* old_data = new double[D1.get_capacity()];
    size_t old_size = D1.get_size();
    for (size_t i = 0; i < old_size; i++) {
        old_data[i] = (D1.get_data_const()[i]);
    }
    D1.reset_memory(1000);

    for (size_t i = 0; i < old_size; i++) {
        EXPECT_EQ(D1.get_data_const()[i], old_data[i]);
    }
    EXPECT_EQ(D1.get_capacity(), (1000 / MEM_STEP + 1) * MEM_STEP);
}

TEST(ClassMemData, can_reset_memory_for_not_empty_decrease) {
    MemData<double> D1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    int* old_data = new int[D1.get_capacity()];
    size_t old_size = D1.get_size();
    for (size_t i = 0; i < old_size; i++) {
        old_data[i] = (D1.get_data_const()[i]);
    }

    size_t new_size = 13;
    size_t new_cap = calculate_capacity(new_size);

    D1.reset_memory(new_size);

    for (size_t i = 0; i < new_size; i++) {
        EXPECT_EQ(D1.get_data_const()[i], old_data[i]);
    }
    for (size_t i = new_size; i < new_cap; i++) {
        EXPECT_NE(D1.get_data_const()[i], old_data[i]);
    }
    EXPECT_EQ(D1.get_capacity(), new_cap);
}

TEST(ClassMemData, can_reset_memory_without_reallocation) {
    MemData<double> D1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    size_t old_capacity = D1.get_capacity();
    const double* old_data = D1.get_data_const();

    D1.reset_memory(D1.get_size());

    EXPECT_EQ(D1.get_data_const(), old_data);
    EXPECT_EQ(D1.get_capacity(), old_capacity);
}

TEST(ClassMemData, can_reset_memory_with_shift) {
    size_t start_index = 3;
    MemData<double> D1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    double* old_data = new double[D1.get_capacity()];
    size_t old_size = D1.get_size();
    for (size_t i = 0; i < old_size; i++) {
        old_data[i] = (D1.get_data_const()[i]);
    }

    size_t new_size = 14;
    size_t new_cap = calculate_capacity(new_size);

    D1.reset_memory(new_size, start_index);

    for (size_t i = 0; i < new_size; i++) {
        EXPECT_NE(D1.get_data_const()[i], old_data[i]);
    }
    for (size_t i = 0; i < start_index; i++) {
        EXPECT_EQ(D1.get_data_const()[i], old_data[(i + start_index) % old_size]);
    }
    for (size_t i = start_index; i < new_size; i++) {
        EXPECT_EQ(D1.get_data_const()[i - start_index], old_data[i]);
    }
    EXPECT_EQ(D1.get_capacity(), new_cap);
}

TEST(ClassMemData, can_clear_memory_for_empty) {
    MemData<double> D1;
    D1.set_size(3);
    const double* old_data = D1.get_data_const();
    D1.clear_memory();

    EXPECT_EQ(D1.get_size(), 0);
    EXPECT_EQ(D1.get_capacity(), MEM_STEP);
}

TEST(ClassMemData, can_clear_memory_for_not_empty) {
    MemData<double> D1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    const double* old_data = D1.get_data_const();
    D1.clear_memory();

    EXPECT_EQ(D1.get_size(), 0);
    EXPECT_EQ(D1.get_capacity(), MEM_STEP);
}

TEST(ClassMemData, can_set_size) {
    MemData<double> D1;
    double* list1 = new double[3];
    list1[0] = 1;
    list1[1] = 2;
    list1[2] = 3;
    MemData<double> D2(list1, 3);
    MemData<double> D3({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });

    EXPECT_EQ(D1.get_size(), 0);
    EXPECT_EQ(D2.get_size(), 3);

    D2.set_size(1);

    EXPECT_EQ(D2.get_size(), 1);
    EXPECT_EQ(D3.get_size(), 15);
    ASSERT_THROW(D3.set_size(31), std::invalid_argument);
    ASSERT_NO_THROW(D3.set_size(30));
}

TEST(ClassMemData, can_compare) {
    MemData<double> D1(123);
    MemData<double> D2(10);
    double* list1 = new double[3];
    list1[0] = 1;
    list1[1] = 2;
    list1[2] = 3;
    double* list2 = new double[3];
    list2[0] = 1;
    list2[1] = 2;
    list2[2] = 3;
    MemData<double> D4({ 1,2,3 });
    MemData<double> D5({ 1,2,3 });
    MemData<double> D6(list1, 3);
    MemData<double> D7(list2, 3);

    EXPECT_TRUE(D1 == D2);
    EXPECT_TRUE(D5 == D4);
    EXPECT_TRUE(D6 == D4);
    EXPECT_TRUE(D7 == D4);
}

TEST(ClassMemData, can_assigment) {
    MemData<double> D1(123);
    MemData<double> D2(10);
    MemData<double> D3 = D1 = D2;
    double* list1 = new double[3];
    list1[0] = 1;
    list1[1] = 2;
    list1[2] = 3;
    double* list2 = new double[3];
    list2[0] = 4;
    list2[1] = 5;
    list2[2] = 6;
    MemData<double> D4({ 1,2,3 });
    MemData<double> D5({ 101,2,3 });
    MemData<double> D6(list1, 3);
    MemData<double> D7(list2, 3);
    D7 = D6 = D5 = D4;

    EXPECT_TRUE(D1 == D2);
    EXPECT_TRUE(D3 == D2);
    EXPECT_TRUE(D2 == D1);
    EXPECT_TRUE(D5 == D4);
    EXPECT_TRUE(D6 == D4);
    EXPECT_TRUE(D7 == D4);

    EXPECT_TRUE(D1.get_data_const() != D2.get_data_const());
    EXPECT_TRUE(D2.get_data_const() != D3.get_data_const());
    EXPECT_TRUE(D3.get_data_const() != D4.get_data_const());
    EXPECT_TRUE(D5.get_data_const() != D6.get_data_const());
    EXPECT_TRUE(D6.get_data_const() != D7.get_data_const());
}

TEST(ClassMemData, can_move_assigment) {
    MemData<double> D1({ 1,2,3,4,5 });
    MemData<double> D2;
    MemData<double> D3({ 1,2,3,4,5 });
    D2 = std::move(D1);

    EXPECT_TRUE(D1.get_data_const() == nullptr);
    EXPECT_TRUE(D2.get_data_const() != nullptr);
    EXPECT_TRUE(D2 == D3);
}

TEST(FunctionsForMemData, can_quick_sort) {
    MemData<double> D1({ 6,5,4,3,2,1 });
    MemData<double> D2({ 2,2,2,2,2 });
    MemData<double> D3({ 2,3,2,4,100000,1 });

    quick_sort(D1);
    quick_sort(D2);
    quick_sort(D3);

    double example1[6] = { 1,2,3,4,5,6 };
    double example2[5] = { 2,2,2,2,2 };
    double example3[6] = { 1,2,2,3,4,100000 };
    srand(time(NULL));

    size_t random_size = (static_cast<size_t>(rand() % 100)) + 1;
    double* random_array = new double[random_size];

    for (size_t i = 0; i < random_size; i++) {
        double zero_to_one = static_cast<double>(rand()) / RAND_MAX;
        random_array[i] = zero_to_one * 200.0 - 100.0;
    }
    MemData<double> DR(random_array, random_size);
    quick_sort(DR);

    for (size_t i = 0; i < DR.get_size() - 1; i++) {
        EXPECT_TRUE(DR.get_data_const()[i] <= DR.get_data_const()[i + 1]);
    }
    for (size_t i = 0; i < D1.get_size(); i++) {
        EXPECT_EQ(D1.get_data_const()[i], example1[i]);
    }
    for (size_t i = 0; i < D2.get_size(); i++) {
        EXPECT_EQ(D2.get_data_const()[i], example2[i]);
    }
    for (size_t i = 0; i < D3.get_size(); i++) {
        EXPECT_EQ(D3.get_data_const()[i], example3[i]);
    }
}

TEST(FunctionsForMemData, can_shuffle) {
    MemData<double> D1({ 6,5,4,3,2,1 });
    MemData<double> D2({ 2,3,2,4,100000,1 });
    MemData<double> D3;

    ASSERT_NO_THROW(shuffle(D3));

    double example1[6] = { 6,5,4,3,2,1 };
    double example2[6] = { 2,3,2,4,100000,1 };

    bool shuffled_flag1 = false;
    bool shuffled_flag2 = false;

    for (size_t i = 0; i < 1000; i++) {
        shuffle(D1);
        shuffle(D2);
        for (size_t i = 0; i < D1.get_size(); i++) {
            if (D1.get_data_const()[i] != example1[i]) {
                shuffled_flag1 = true;
                break;
            }
        }
        for (size_t i = 0; i < D2.get_size(); i++) {
            if (D2.get_data_const()[i] != example2[i]) {
                shuffled_flag2 = true;
                break;
            }
        }
        if (shuffled_flag1 && shuffled_flag2) {
            break;
        }
    }
    EXPECT_TRUE(shuffled_flag1 && shuffled_flag2);
}