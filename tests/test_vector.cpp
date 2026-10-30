// Copyright 2026 smvax

#include <gtest/gtest.h>
#include "../lib_vector/vector.h"

TEST(ClassVector, can_create_with_default_constructor) {
    TVector<double> V1;

    EXPECT_EQ(V1.get_size(), 0);
    EXPECT_EQ(V1.get_capacity(), MEM_STEP);
}

TEST(ClassVector, can_create_with_constructor_by_size) {
    TVector<double> V1(10);
    TVector<double> V2(0);
    TVector<double> V3(1000);

    EXPECT_EQ(V1.get_size(), 0);
    EXPECT_EQ(V1.get_capacity(), MEM_STEP);
    EXPECT_EQ(V2.get_size(), 0);
    EXPECT_EQ(V2.get_capacity(), MEM_STEP);
    EXPECT_EQ(V3.get_size(), 0);
    EXPECT_EQ(V3.get_capacity(), (1000 / MEM_STEP + 1) * MEM_STEP);
}

TEST(ClassVector, can_create_with_constructor_by_initializer_list) {
    TVector<double> V1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    TVector<double> V2({});
    double example1[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

    EXPECT_EQ(V1.get_size(), 16);
    EXPECT_EQ(V1.get_capacity(), MEM_STEP * 2);
    EXPECT_EQ(V2.get_size(), 0);
    EXPECT_EQ(V2.get_capacity(), MEM_STEP);
    for (size_t i = 0; i < V1.get_size(); i++) {
        EXPECT_EQ(V1[i], example1[i]);
    }
}

TEST(ClassVector, can_create_with_init_constructor) {
    double* list1 = new double[16];
    for (int i = 0; i < 16; i++) {
        list1[i] = i;
    }
    TVector<double> V1(list1, 16);

    EXPECT_EQ(V1.get_size(), 16);
    EXPECT_EQ(V1.get_capacity(), MEM_STEP * 2);
    for (size_t i = 0; i < V1.get_size(); i++) {
        EXPECT_EQ(V1[i], list1[i]);
    }
}

TEST(ClassVector, can_create_with_copy_constructor) {
    TVector<double> V1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    TVector<double> V2(V1);
    double example1[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

    EXPECT_EQ(V1.get_size(), V2.get_size(), 16);
    EXPECT_EQ(V1.get_capacity(), V2.get_capacity(), MEM_STEP * 2);
    for (size_t i = 0; i < V1.get_size(); i++) {
        EXPECT_EQ(V1[i], example1[i]);
    }
    for (size_t i = 0; i < V2.get_size(); i++) {
        EXPECT_EQ(V2[i], example1[i]);
    }
}

TEST(ClassVector, can_create_with_move_constructor) {
    TVector<double> V1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    const double* old_V1_data_ptr = V1.get_mem_original().get_data_const();
    TVector<double> V2(std::move(V1));

    EXPECT_NE(V1.get_mem_original().get_data_const(), old_V1_data_ptr);
    EXPECT_EQ(V1.get_mem_original().get_data_const(), nullptr);
    EXPECT_EQ(V2.get_mem_original().get_data_const(), old_V1_data_ptr);
}

TEST(ClassVector, can_is_empty) {
    TVector<double> V1;
    TVector<double> V2(0);
    TVector<double> V3(1);
    TVector<double> V4({ 1,2,3 });
    TVector<double> V5({ 1,2,3,0 });
    double* list1 = new double[3];
    list1[0] = 1;
    list1[1] = 2;
    list1[2] = 3;
    double* list2 = new double[3];
    list2[0] = 4;
    list2[1] = 5;
    list2[2] = 6;
    TVector<double> V6(list1, 3);
    TVector<double> V7(list2, 3);

    EXPECT_TRUE(V1.is_empty());
    EXPECT_TRUE(V2.is_empty());
    EXPECT_TRUE(V3.is_empty());
    EXPECT_FALSE(V4.is_empty());
    EXPECT_FALSE(V5.is_empty());
    EXPECT_FALSE(V6.is_empty());
    EXPECT_FALSE(V7.is_empty());
}

//TEST(ClassVector, can_is_full) { //убрали тест как и у MemData<double>

TEST(ClassVector, can_get_front) {
    TVector<double> V1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    TVector<double> V2({ 1000,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    EXPECT_DOUBLE_EQ(V1.get_front(), 1);
    EXPECT_DOUBLE_EQ(V2.get_front(), 1000);
}

TEST(ClassVector, can_get_back) {
    TVector<double> V1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    TVector<double> V2({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,19000 });
    EXPECT_DOUBLE_EQ(V1.get_back(), 16);
    EXPECT_DOUBLE_EQ(V2.get_back(), 19000);
}

TEST(ClassVector, can_set_front) {
    TVector<double> V1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    EXPECT_DOUBLE_EQ(V1.get_front(), 1);
    V1.front_ref() = 11;
    EXPECT_DOUBLE_EQ(V1.get_front(), 11);
}

TEST(ClassVector, can_set_back) {
    TVector<double> V1({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    EXPECT_DOUBLE_EQ(V1.get_back(), 16);
    V1.back_ref() = 13;
    EXPECT_DOUBLE_EQ(V1.get_back(), 13);
}

TEST(ClassVector, throw_when_try_get_front_in_empty_vector) {
    TVector<double> V1;
    ASSERT_THROW(V1.get_front(), std::logic_error);
}

TEST(ClassVector, throw_when_try_get_back_in_empty_vector) {
    TVector<double> V1;
    ASSERT_THROW(V1.get_back(), std::logic_error);
}

TEST(ClassVector, throw_when_try_set_front_in_empty_vector) {
    TVector<double> V1;
    ASSERT_THROW(V1.front_ref() = 1, std::logic_error);
}

TEST(ClassVector, throw_when_try_set_back_in_empty_vector) {
    TVector<double> V1;
    ASSERT_THROW(V1.back_ref() = 1, std::logic_error);
}

TEST(ClassVector, can_output_with_operator_cout) {
    TVector<double> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }", out.str());
}

TEST(ClassVector, can_input_with_operator_cin) {
    TVector<double> vec;
    std::stringstream in("9 1 2 3 4 5 6 7 8 9");
    in >> vec;

    EXPECT_EQ(9, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());

    for (size_t i = 0; i < vec.get_size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_push_front) {
    TVector<double> vec({ 44, 5, 7, 8 });
    std::stringstream out;
    for (size_t i = 0; i < 4; i++) {
        vec.push_front(3 - i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8 }", out.str());
    EXPECT_EQ(8, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_push_front_many) {
    TVector<double> vec({ 44, 5, 7, 8 });
    std::stringstream out;
    double list[6] = { 0,1,2,3,4,5 };
    vec.push_front_many(list, 4);
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8 }", out.str());
    EXPECT_EQ(8, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_push_front_in_empty_vector) {
    TVector<double> vec;
    std::stringstream out;
    EXPECT_EQ(0, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
    for (size_t i = 0; i < 4; i++) {
        vec.push_front(3 - i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3 }", out.str());
    EXPECT_EQ(4, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_push_front_many_in_empty_vector) {
    TVector<double> vec;
    std::stringstream out;
    double list[6] = { 0,1,2,3,4,5 };
    vec.push_front_many(list, 4);
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3 }", out.str());
    EXPECT_EQ(4, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_push_front_with_reallocation) {
    TVector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 });
    std::stringstream out;
    EXPECT_EQ(14, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
    for (size_t i = 0; i < 3; i++) {
        vec.push_front(3 - i);
    }
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 }", out.str());
    EXPECT_EQ(17, vec.get_size());
    EXPECT_EQ(30, vec.get_capacity());
}

TEST(ClassVector, can_push_front_many_with_reallocation) {
    TVector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 });
    std::stringstream out;
    EXPECT_EQ(14, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
    double list[6] = { 1,2,3,4,5,6 };
    vec.push_front_many(list, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 }", out.str());
    EXPECT_EQ(17, vec.get_size());
    EXPECT_EQ(30, vec.get_capacity());
}

TEST(ClassVector, can_push_back) {
    TVector<double> vec({ 44, 5, 7, 8 });
    std::stringstream out;
    for (size_t i = 0; i < 4; i++) {
        vec.push_back(3 - i);
    }
    out << vec;
    EXPECT_EQ("{ 44, 5, 7, 8, 3, 2, 1, 0 }", out.str());
    EXPECT_EQ(8, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_push_back_many) {
    TVector<double> vec({ 44, 5, 7, 8 });
    std::stringstream out;
    double list[6] = { 0,1,2,3,4,5 };
    vec.push_back_many(list, 4);
    out << vec;
    EXPECT_EQ("{ 44, 5, 7, 8, 0, 1, 2, 3 }", out.str());
    EXPECT_EQ(8, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_push_back_in_empty_vector) {
    TVector<double> vec;
    std::stringstream out;
    for (size_t i = 0; i < 4; i++) {
        vec.push_back(3 - i);
    }
    out << vec;
    EXPECT_EQ("{ 3, 2, 1, 0 }", out.str());
    EXPECT_EQ(4, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_push_back_many_in_empty_vector) {
    TVector<double> vec;
    std::stringstream out;
    double list[6] = { 0,1,2,3,4,5 };
    vec.push_back_many(list, 4);
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3 }", out.str());
    EXPECT_EQ(4, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_push_back_with_reallocation) {
    TVector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 });
    std::stringstream out;
    EXPECT_EQ(14, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
    for (size_t i = 0; i < 3; i++) {
        vec.push_back(3 - i);
    }
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 3, 2, 1 }", out.str());
    EXPECT_EQ(17, vec.get_size());
    EXPECT_EQ(30, vec.get_capacity());
}

TEST(ClassVector, can_push_back_many_with_reallocation) {
    TVector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 });
    std::stringstream out;
    EXPECT_EQ(14, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
    double list[3] = { 3,2,1 };
    vec.push_back_many(list, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 3, 2, 1 }", out.str());
    EXPECT_EQ(17, vec.get_size());
    EXPECT_EQ(30, vec.get_capacity());
}

TEST(ClassVector, can_insert) {
    TVector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.insert(99, 2);
    out << vec;
    EXPECT_EQ("{ 1, 2, 99, 3, 4, 5 }", out.str());
    EXPECT_EQ(6, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_insert_many) {
    TVector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    double list[3] = { 99, 100, 101 };
    vec.insert_many(list, 3, 2);
    out << vec;
    EXPECT_EQ("{ 1, 2, 99, 100, 101, 3, 4, 5 }", out.str());
    EXPECT_EQ(8, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_insert_with_reallocation) {
    TVector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 });
    std::stringstream out;
    EXPECT_EQ(14, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
    vec.insert(99, 7);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 99, 8, 9, 10, 11, 12, 13, 14 }", out.str());
    EXPECT_EQ(15, vec.get_size());
    EXPECT_EQ(30, vec.get_capacity());
}

TEST(ClassVector, can_insert_many_with_reallocation) {
    TVector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14 });
    std::stringstream out;
    EXPECT_EQ(14, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
    double list[3] = { 99, 100, 101 };
    vec.insert_many(list, 3, 7);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 99, 100, 101, 8, 9, 10, 11, 12, 13, 14 }", out.str());
    EXPECT_EQ(17, vec.get_size());
    EXPECT_EQ(30, vec.get_capacity());
}

TEST(ClassVector, can_insert_to_front) {
    TVector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.insert(99, 0);
    out << vec;
    EXPECT_EQ("{ 99, 1, 2, 3, 4, 5 }", out.str());
    EXPECT_EQ(6, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_insert_many_to_front) {
    TVector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    double list[3] = { 99, 100, 101 };
    vec.insert_many(list, 3, 0);
    out << vec;
    EXPECT_EQ("{ 99, 100, 101, 1, 2, 3, 4, 5 }", out.str());
    EXPECT_EQ(8, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, throw_when_try_insert_with_wrong_position) {
    TVector<double> vec({ 1,2,3,4,5 });
    EXPECT_THROW(vec.insert(99, 10), std::out_of_range);
    EXPECT_THROW(vec.insert_many(nullptr, 3, 10), std::out_of_range);
}

TEST(ClassVector, can_pop_front) {
    TVector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.pop_front();
    out << vec;
    EXPECT_EQ("{ 2, 3, 4, 5 }", out.str());
    EXPECT_EQ(4, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_pop_front_many) {
    TVector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.pop_front_many(3);
    out << vec;
    EXPECT_EQ("{ 4, 5 }", out.str());
    EXPECT_EQ(2, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_pop_front_with_reallocation) {
    TVector<double> vec({ 99,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
    std::stringstream out;
    EXPECT_EQ(15, vec.get_size());
    EXPECT_EQ(30, vec.get_capacity());
    vec.pop_front();
    out << vec;
    EXPECT_EQ("{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }", out.str());
    EXPECT_EQ(14, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_pop_front_many_with_reallocation) {
    TVector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
    std::stringstream out;
    EXPECT_EQ(15, vec.get_size());
    EXPECT_EQ(30, vec.get_capacity());
    vec.pop_front_many(3);
    out << vec;
    EXPECT_EQ("{ 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }", out.str());
    EXPECT_EQ(12, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, throw_when_try_pop_front_from_empty_vector) {
    TVector<double> vec;
    EXPECT_THROW(vec.pop_front(), std::logic_error);
}

TEST(ClassVector, throw_when_try_pop_front_many_from_empty_vector) {
    TVector<double> vec;
    EXPECT_THROW(vec.pop_front_many(3), std::logic_error);
}

TEST(ClassVector, can_pop_back) {
    TVector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.pop_back();
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4 }", out.str());
    EXPECT_EQ(4, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_pop_back_many) {
    TVector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.pop_back_many(3);
    out << vec;
    EXPECT_EQ("{ 1, 2 }", out.str());
    EXPECT_EQ(2, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_pop_back_with_reallocation) {
    TVector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
    std::stringstream out;
    EXPECT_EQ(15, vec.get_size());
    EXPECT_EQ(30, vec.get_capacity());
    vec.pop_back();
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 }", out.str());
    EXPECT_EQ(14, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_pop_back_many_with_reallocation) {
    TVector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    std::stringstream out;
    EXPECT_EQ(16, vec.get_size());
    EXPECT_EQ(30, vec.get_capacity());
    vec.pop_back_many(5);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }", out.str());
    EXPECT_EQ(11, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, throw_when_try_pop_back_from_empty_vector) {
    TVector<double> vec;
    EXPECT_THROW(vec.pop_back(), std::logic_error);
}

TEST(ClassVector, throw_when_try_pop_back_many_from_empty_vector) {
    TVector<double> vec;
    EXPECT_THROW(vec.pop_back_many(3), std::logic_error);
}

TEST(ClassVector, can_correctly_recalc_back_in_area_of_zero) {
    TVector<double> vec;

    for (size_t i = 0; i < 14; i++) {
        vec.push_back(i + 1);
    }

    vec.pop_front();
    vec.push_back(15);

    EXPECT_EQ(14, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
    EXPECT_DOUBLE_EQ(15.0, vec.get_back());

    for (size_t i = 0; i < vec.get_size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }

    vec.pop_back();

    EXPECT_EQ(13, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
    EXPECT_DOUBLE_EQ(14.0, vec.get_back());

    for (size_t i = 0; i < vec.get_size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 2);
    }
}

TEST(ClassVector, can_correctly_recalc_front_in_area_of_zero) {
    TVector<double> vec;

    for (size_t i = 0; i < 14; i++) {
        vec.push_back(i + 1);
    }

    vec.pop_back();
    vec.push_front(0);

    EXPECT_EQ(14, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
    EXPECT_DOUBLE_EQ(0.0, vec.get_front());

    for (size_t i = 0; i < vec.get_size() - 1; i++) {
        EXPECT_DOUBLE_EQ(vec[i + 1], i + 1);
    }

    vec.pop_front();

    EXPECT_EQ(13, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
    EXPECT_DOUBLE_EQ(1.0, vec.get_front());

    for (size_t i = 0; i < vec.get_size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_erase) {
    TVector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.erase(2);
    out << vec;
    EXPECT_EQ("{ 1, 2, 4, 5 }", out.str());
    EXPECT_EQ(4, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_erase_many) {
    TVector<double> vec({ 1,2,3,4,5,6,7,8 });
    std::stringstream out;
    vec.erase_many(2, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 6, 7, 8 }", out.str());
    EXPECT_EQ(5, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_erase_front) {
    TVector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.erase(0);
    out << vec;
    EXPECT_EQ("{ 2, 3, 4, 5 }", out.str());
    EXPECT_EQ(4, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_erase_back) {
    TVector<double> vec({ 1,2,3,4,5 });
    std::stringstream out;
    vec.erase(4);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4 }", out.str());
    EXPECT_EQ(4, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_erase_with_reallocation) {
    TVector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 });
    std::stringstream out;
    EXPECT_EQ(15, vec.get_size());
    EXPECT_EQ(30, vec.get_capacity());
    vec.erase(5);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15 }", out.str());
    EXPECT_EQ(14, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, can_erase_many_with_reallocation) {
    TVector<double> vec({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
    std::stringstream out;
    EXPECT_EQ(16, vec.get_size());
    EXPECT_EQ(30, vec.get_capacity());
    vec.erase_many(5, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    EXPECT_EQ(13, vec.get_size());
    EXPECT_EQ(15, vec.get_capacity());
}

TEST(ClassVector, throw_when_try_erase_from_empty_vector) {
    TVector<double> vec;
    EXPECT_THROW(vec.erase(0), std::logic_error);
}

TEST(ClassVector, throw_when_try_erase_many_from_empty_vector) {
    TVector<double> vec;
    EXPECT_THROW(vec.erase_many(0, 3), std::logic_error);
}

TEST(ClassVector, throw_when_try_erase_with_wrong_position) {
    TVector<double> vec({ 1,2,3,4,5 });
    EXPECT_THROW(vec.erase(10), std::out_of_range);
}

TEST(ClassVector, throw_when_try_erase_many_with_wrong_count) {
    TVector<double> vec({ 1,2,3,4,5 });
    EXPECT_THROW(vec.erase_many(10, 2), std::logic_error);
    EXPECT_THROW(vec.erase_many(2, 10), std::logic_error);
}

TEST(ClassVector, combination_push_pop_insert_erase) {
    TVector<double> vec({ 3, 44, 5, 7, 8 });

    std::stringstream out;
    out << vec;
    EXPECT_EQ("{ 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_front();
    out << vec;
    EXPECT_EQ("{ 44, 5, 7, 8 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_front(3 - i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8 }", out.str());
    out.str("");

    vec.pop_back();
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7 }", out.str());
    out.str("");

    for (size_t i = 0; i < 4; i++) {
        vec.push_back(8 + i);
    }
    out << vec;
    EXPECT_EQ("{ 0, 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(0);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 44, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.erase(3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    vec.insert(6, 4);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11 }", out.str());
    out.str("");

    for (size_t i = 0; i < 5; i++) {
        vec.push_back(12 + i);
    }
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    vec.insert(4, 3);
    out << vec;
    EXPECT_EQ("{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }", out.str());
    out.str("");

    EXPECT_EQ(16, vec.get_size());
    EXPECT_EQ(30, vec.get_capacity());

    for (size_t i = 0; i < vec.get_size(); i++) {
        EXPECT_DOUBLE_EQ(vec[i], i + 1);
    }
}

TEST(ClassVector, can_assigment) {
    TVector<double> vec_1{ 1,2,3,4 };
    TVector<double> vec_2;

    vec_2 = vec_1;

    EXPECT_EQ(4, vec_1.get_size());
    EXPECT_EQ(15, vec_1.get_capacity());
    EXPECT_EQ(4, vec_2.get_size());
    EXPECT_EQ(15, vec_2.get_capacity());

    for (size_t i = 0; i < vec_2.get_size(); i++) {
        EXPECT_DOUBLE_EQ(vec_1[i], vec_2[i]);
        EXPECT_DOUBLE_EQ(vec_2[i], i + 1);
    }

    vec_1.pop_back();
    EXPECT_EQ(3, vec_1.get_size());
    EXPECT_EQ(4, vec_2.get_size());
}

TEST(ClassVector, can_move_assigment) {
    TVector<double> vec_1;
    TVector<double> vec_2;

    for (size_t i = 0; i < 4; i++) {
        vec_1.push_back(5 + i);
    }

    for (size_t i = 0; i < 4; i++) {
        vec_1.push_front(4 - i);
    }

    vec_2 = std::move(vec_1);

    EXPECT_EQ(0, vec_1.get_size());
    EXPECT_EQ(0, vec_1.get_capacity());

    EXPECT_EQ(8, vec_2.get_size());
    EXPECT_EQ(15, vec_2.get_capacity());

    for (size_t i = 0; i < vec_2.get_size(); i++) {
        EXPECT_DOUBLE_EQ(vec_2[i], i + 1);
    }
}

TEST(ClassVector, can_standard_shrink) {
    TVector<double> v;
    v.push_back(1.0);
    v.push_back(2.0);
    v.push_back(3.0);

    size_t expected_bytes_before = v.get_capacity() * sizeof(double);
    EXPECT_TRUE(expected_bytes_before >= 3 * sizeof(double));

    v.shrink_to_fit();

    size_t actual_bytes = v.get_capacity() * sizeof(double);
    size_t expected_bytes_after = v.get_capacity() * sizeof(double);

    EXPECT_EQ(actual_bytes, expected_bytes_after);
    EXPECT_EQ(actual_bytes, 3 * sizeof(double));

    EXPECT_EQ(v.get_capacity(), v.get_size());
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
}

TEST(ClassVector, can_shrink_empty) {
    TVector<double> v;

    EXPECT_NO_THROW(v.shrink_to_fit());

    size_t actual_bytes = v.get_capacity() * sizeof(double);

    EXPECT_EQ(v.get_size(), 0);
    EXPECT_TRUE(actual_bytes > 0);
}

TEST(ClassVector, can_shrink_shifted) {
    TVector<double> v;

    v.push_back(1.0);
    v.push_back(2.0);
    v.push_back(3.0);
    v.push_front(4.0);
    v.pop_back();

    EXPECT_TRUE(v.get_front_idx() != 0);
    size_t old_size = v.get_size();

    v.shrink_to_fit();

    size_t actual_bytes = v.get_capacity() * sizeof(double);
    size_t expected_bytes = old_size * sizeof(double);

    EXPECT_EQ(actual_bytes, expected_bytes);
    EXPECT_EQ(v.get_front_idx(), 0);
    EXPECT_EQ(v.get_back_idx(), v.get_size() - 1);

    EXPECT_DOUBLE_EQ(v[0], 4.0);
    EXPECT_DOUBLE_EQ(v[1], 1.0);
    EXPECT_DOUBLE_EQ(v[2], 2.0);
}

TEST(ClassVector, throw_when_insert_out_of_range_in_empty_vector) {
  TVector<double> v;

  ASSERT_THROW(v.insert(99.0, 1), std::out_of_range);
  ASSERT_THROW(v.insert_many(nullptr, 5, 2), std::out_of_range);
}

TEST(ClassVector, pop_front_many_reduces_size_to_zero_correctly) {
  TVector<double> v({1.0, 2.0, 3.0});

  ASSERT_NO_THROW(v.pop_front_many(3));
  EXPECT_EQ(v.get_size(), 0);
  EXPECT_TRUE(v.is_empty());
}

TEST(ClassVector, pop_back_many_reduces_size_to_zero_correctly) {
  TVector<double> v({1.0, 2.0, 3.0});

  ASSERT_NO_THROW(v.pop_back_many(3));
  EXPECT_EQ(v.get_size(), 0);
  EXPECT_TRUE(v.is_empty());
}

TEST(ClassVector, copy_constructor_preserves_internal_ring_buffer_indices) {
  TVector<double> v;
  for (int i = 0; i < 5; ++i) v.push_back(i);
  v.pop_front();
  v.pop_front();
  size_t original_front_idx = v.get_front_idx();
  size_t original_back_idx = v.get_back_idx();
  TVector<double> copy_v(v);

  EXPECT_EQ(copy_v.get_front_idx(), original_front_idx);
  EXPECT_EQ(copy_v.get_back_idx(), original_back_idx);
  EXPECT_EQ(copy_v.get_size(), v.get_size());
}

TEST(ClassVector, copy_assignment_preserves_internal_ring_buffer_indices) {
  TVector<double> v;
  for (int i = 0; i < 5; ++i) v.push_back(i);
  v.pop_front();

  TVector<double> copy_v;
  copy_v = v;

  EXPECT_EQ(copy_v.get_front_idx(), v.get_front_idx());
  EXPECT_EQ(copy_v.get_back_idx(), v.get_back_idx());
}

TEST(ClassVector, can_insert_element_when_buffer_is_wrapped) {
  TVector<int> v;
  for (int i = 1; i <= 14; ++i) v.push_back(i);
  for (int i = 0; i < 4; ++i) v.pop_front();
  for (int i = 15; i <= 18; ++i) v.push_back(i);

  EXPECT_GT(v.get_front_idx(), v.get_back_idx());

  v.insert(999, 5);

  EXPECT_EQ(v[5], 999);
  EXPECT_EQ(v.get_size(), 15);
}

TEST(ClassVector, can_erase_element_when_buffer_is_wrapped) {
  TVector<int> v;
  for (int i = 1; i <= 14; ++i) v.push_back(i);
  for (int i = 0; i < 4; ++i) v.pop_front();
  for (int i = 15; i <= 18; ++i) v.push_back(i);

  ASSERT_NO_THROW(v.erase(5));
  EXPECT_EQ(v.get_size(), 13);
}

TEST(ClassVector, can_erase_many_elements_when_buffer_is_wrapped) {
  TVector<int> v;
  for (int i = 1; i <= 14; ++i) v.push_back(i);
  for (int i = 0; i < 4; ++i) v.pop_front();
  for (int i = 15; i <= 18; ++i) v.push_back(i);

  ASSERT_NO_THROW(v.erase_many(4, 3));
  EXPECT_EQ(v.get_size(), 11);
}

TEST(ClassVector, friend_quick_sort_shifted) {
  TVector<int> v;
  v.push_back(10);
  v.push_back(1);
  v.push_back(5);
  v.pop_front();
  v.push_back(2);
  quick_sort(v);

  EXPECT_EQ(v.get_front_idx(), 0);
  EXPECT_EQ(v.get_back_idx(), v.get_size() - 1);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 5);
}

TEST(ClassIterator, can_get_begin_and_end_for_empty_vector) {
  TVector<int> v;

  EXPECT_EQ(v.begin(), v.end());
}

TEST(ClassIterator, can_get_cbegin_and_cend_for_empty_vector) {
  TVector<int> v;

  EXPECT_EQ(v.cbegin(), v.cend());
}

TEST(ClassIterator, can_traverse_linear_vector) {
  TVector<int> v;
  for (int i = 1; i <= 5; ++i) v.push_back(i);
  int count = 0;
  for (TVector<int>::iterator it = v.begin(); it != v.end(); ++it) count++;

  EXPECT_EQ(count, 5);
}

TEST(ClassIterator, can_read_linear_vector) {
  TVector<int> v;
  for (int i = 1; i <= 5; ++i) v.push_back(i);
  int expected = 1;

  for (TVector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    EXPECT_EQ(*it, expected);
    expected++;
  }
}

TEST(ClassIterator, can_modify_elements_through_iterator) {
  TVector<int> v;
  v.push_back(10);
  v.push_back(20);
  TVector<int>::iterator it = v.begin();
  *it = 99;

  EXPECT_EQ(v[0], 99);
}

TEST(ClassIterator, const_iterator_defines_correctly) {
  TVector<int> v({1, 2, 3});
  const TVector<int>& const_v = v;
  int expected = 1;

  for (TVector<int>::const_iterator it = const_v.begin(); it != const_v.end();
       ++it) {
    EXPECT_EQ(*it, expected);
    expected++;
  }
}

TEST(ClassIterator, can_convert_iterator_to_const_iterator) {
  TVector<int> v({10, 20});
  TVector<int>::iterator non_const_it = v.begin();
  TVector<int>::const_iterator const_it = non_const_it;

  EXPECT_EQ(*const_it, 10);
}

TEST(ClassIterator, can_use_postfix_increment) {
  TVector<int> v({10, 20, 30});
  TVector<int>::iterator it = v.begin();
  TVector<int>::iterator post_inc = it++;

  EXPECT_EQ(*post_inc, 10);
  EXPECT_EQ(*it, 20);
}

TEST(ClassIterator, can_use_prefix_increment) {
  TVector<int> v({10, 20, 30});
  TVector<int>::iterator it = v.begin();
  ++it;
  TVector<int>::iterator pre_inc = ++it;

  EXPECT_EQ(*pre_inc, 30);
  EXPECT_EQ(*it, 30);
}

TEST(ClassIterator, can_use_postfix_decrement) {
  TVector<int> v({10, 20, 30});
  TVector<int>::iterator it = v.begin() + 2;
  TVector<int>::iterator post_dec = it--;

  EXPECT_EQ(*post_dec, 30);
  EXPECT_EQ(*it, 20);
}

TEST(ClassIterator, can_use_prefix_decrement) {
  TVector<int> v({10, 20, 30});
  TVector<int>::iterator it = v.begin() + 2;
  TVector<int>::iterator pre_dec = --it;

  EXPECT_EQ(*pre_dec, 20);
  EXPECT_EQ(*it, 20);
}

TEST(ClassIterator, assignment_operator_works_correctly) {
  TVector<int> v({10, 20});
  TVector<int>::iterator it1 = v.begin();
  TVector<int>::iterator it2;
  it2 = it1;

  EXPECT_TRUE(it1 == it2);
  EXPECT_EQ(*it2, 10);
}

TEST(ClassIterator, binary_plus_does_not_corrupt_original_iterator) {
  TVector<int> v({1, 2, 3, 4, 5});
  TVector<int>::iterator original = v.begin();
  TVector<int>::iterator moved = original + 3;

  EXPECT_EQ(*moved, 4);
  EXPECT_EQ(*original, 1);
  EXPECT_NE(original, moved);
}

TEST(ClassIterator, binary_minus_does_not_corrupt_original_iterator) {
  TVector<int> v({1, 2, 3, 4, 5});
  TVector<int>::iterator original = v.begin() + 3;
  TVector<int>::iterator moved = original - 2;

  EXPECT_EQ(*moved, 2);
  EXPECT_EQ(*original, 4);
  EXPECT_NE(original, moved);
}

TEST(ClassIterator, operator_plus_assignment_modifies_iterator_safely) {
  TVector<int> v({1, 2, 3, 4, 5});
  TVector<int>::iterator it = v.begin();
  it += 4;

  EXPECT_EQ(*it, 5);
}

TEST(ClassIterator, operator_minus_assignment_modifies_iterator_safely) {
  TVector<int> v({1, 2, 3, 4, 5});
  TVector<int>::iterator it = v.begin() + 4;
  it -= 3;

  EXPECT_EQ(*it, 2);
}

TEST(ClassIterator, can_traverse_correctly_when_buffer_is_wrapped) {
  TVector<int> v;
  for (int i = 1; i <= 14; ++i) v.push_back(i);
  for (int i = 0; i < 5; ++i) v.pop_front();
  for (int i = 15; i <= 19; ++i) v.push_back(i);

  EXPECT_EQ(v.get_size(), 14);
  EXPECT_GT(v.get_front_idx(), v.get_back_idx());

  int expected_value = 6;
  int count = 0;

  for (TVector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    EXPECT_EQ(*it, expected_value);
    expected_value++;
    count++;
  }
  EXPECT_EQ(count, 14);
}

TEST(ClassIterator, arithmetic_plus_assignment_works_across_wrap_boundary) {
  TVector<int> v;
  for (int i = 1; i <= 14; ++i) v.push_back(i);
  v.pop_front();
  v.pop_front();
  v.push_back(15);
  v.push_back(16);
  TVector<int>::iterator it = v.begin();

  ASSERT_NO_THROW(it += 13);
  EXPECT_EQ(*it, 16);
}

TEST(ClassIterator, arithmetic_minus_assignment_works_across_wrap_boundary) {
  TVector<int> v;
  for (int i = 1; i <= 14; ++i) v.push_back(i);
  v.pop_front();
  v.pop_front();
  v.push_back(15);
  v.push_back(16);
  TVector<int>::iterator it = v.begin();
  it += 13;
  ASSERT_NO_THROW(it -= 13);
  EXPECT_EQ(*it, 3);
}

TEST(ClassIterator,
     binary_plus_and_minus_work_across_wrap_boundary_without_corruption) {
  TVector<int> v;
  for (int i = 1; i <= 14; ++i) v.push_back(i);
  v.pop_front();
  v.pop_front();
  v.push_back(15);
  v.push_back(16);
  TVector<int>::iterator start = v.begin();
  TVector<int>::iterator end_it = start + 13;
  TVector<int>::iterator back_it = end_it - 13;

  EXPECT_EQ(*end_it, 16);
  EXPECT_EQ(*back_it, 3);
  EXPECT_EQ(*start, 3);
}

TEST(ClassIterator, can_chain_plus_assignment_operators) {
  TVector<int> v({1, 2, 3, 4, 5});
  TVector<int>::iterator it = v.begin();
  (it += 1) += 2;

  EXPECT_EQ(*it, 4);
}

TEST(ClassIterator, can_chain_minus_assignment_operators) {
  TVector<int> v({1, 2, 3, 4, 5});
  TVector<int>::iterator it = v.begin() + 4;
  (it -= 2) -= 1;

  EXPECT_EQ(*it, 2);
}

TEST(ClassIterator, can_mix_prefix_increment_and_plus_assignment_in_chain) {
  TVector<int> v({1, 2, 3, 4, 5});
  TVector<int>::iterator it = v.begin();
  ++(it += 2);

  EXPECT_EQ(*it, 4);
}

TEST(ClassIterator, can_mix_prefix_decrement_and_minus_assignment_in_chain) {
  TVector<int> v({1, 2, 3, 4, 5});
  TVector<int>::iterator it = v.begin() + 4;
  --(it -= 2);

  EXPECT_EQ(*it, 2);
}

TEST(ClassIterator, can_chain_assignment_and_prefix_increment) {
  TVector<int> v({10, 20, 30});
  TVector<int>::iterator it1 = v.begin();
  TVector<int>::iterator it2;
  ++(it2 = it1);

  EXPECT_EQ(*it2, 20);
  EXPECT_EQ(*it1, 10);
}

TEST(ClassIterator, chained_operators_work_correctly_across_wrap_boundary) {
  TVector<int> v;
  for (int i = 1; i <= 14; ++i) v.push_back(i);
  v.pop_front();
  v.pop_front();
  v.push_back(15);
  v.push_back(16);
  TVector<int>::iterator it = v.begin();
  (it += 5) += 8;

  EXPECT_EQ(*it, 16);
}
