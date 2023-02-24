/**
 * @file       <sorting.cpp>
 * @brief      This source file holds implementation of Sorting class. 
 * 
 *             This calss implements sorting algorithms needed for successfull completion of laboratory work 1.
 *
 * @author     Alexander Chudnikov (THE_CHOODICK)
 * @date       15-02-2023
 * @version    0.0.1
 * 
 * @warning    This library is under development, so there might be some bugs in it.  
 * @bug        Currently, there are no any known bugs. 
 * 
 *             In order to submit new ones, please contact me via admin@redline-software.xyz.
 * 
 * @copyright  Copyright 2023 Alexander. All rights reserved. 
 * 
 *             (Not really)
 * 
 * @license    This project is released under the GNUv3 Public License.
 */
#include "sorting.hpp"

void Sorting::bubble_sort(std::vector<Model>& model_vector, uint8_t field)
{
    bool has_changed;

    uint8_t offset = field * 2;

    std::size_t iteration_counter = 0;

    do
    {
        has_changed = false;

        for (std::size_t index = 0; index < model_vector.size() - 1; ++index)
        {
            if ((bool)(model_vector.at(index).compare_type(model_vector.at(index + 1), field)).get_type_masked(offset))
            {
                std::swap(model_vector[index], model_vector[index + 1]);
                has_changed = true;
            }
        }
        iteration_counter += 1;
    }   
    while (has_changed);

    std::cout << "Sorting took " << iteration_counter << " iterations." << std::endl;

    return;
}

void Sorting::heap_sort(std::vector<Model>& model_vector, uint8_t field)
{
    uint8_t offset = field * 2;

    for (std::int32_t index = (model_vector.size() / 2) - 1; index >= 0; --index)
    {
        Sorting::make_heap(model_vector, index, field);
    }
  
    // extracting elements from heap one by one
    for (std::int32_t index = model_vector.size() - 1; index >= 0; --index)
    {
        // Move current root to end
        std::swap(model_vector[0], model_vector[index]);
  
        // again call max heapify on the reduced heap
        Sorting::make_heap(model_vector, 0, field, index);
    }    

    return;
}

void Sorting::merge_sort(std::vector<Model>& model_vector, uint8_t field, std::size_t left, std::size_t right, bool initial)
{
    if (initial)
    {
        left = 0;
        right = model_vector.size() - 1;
    }

    if(left >= right) 
    {
        return;
    }

    std::size_t middle = left + (right - left) / 2;

    Sorting::merge_sort(model_vector, field, left, middle, false);
    Sorting::merge_sort(model_vector, field, middle + 1, right, false);
    Sorting::make_merge(model_vector, field, left, right, middle);
}

void Sorting::make_heap(std::vector<Model>& model_vector, std::size_t index, uint8_t field, std::size_t last_index)
{
    std::size_t biggest_index = index;
    std::size_t left_index = (2 * biggest_index) + 1;
    std::size_t right_index = (2 * biggest_index) + 2;

    if (last_index == 0)
    {
        last_index = model_vector.size();
    }

    if (left_index < last_index && (bool)(model_vector.at(left_index).compare_type(model_vector.at(biggest_index), field)).get_type_masked(field * 2))
    {
        biggest_index = left_index;
    }

    if (right_index < last_index && (bool)(model_vector.at(right_index).compare_type(model_vector.at(biggest_index), field)).get_type_masked(field * 2))
    {
        biggest_index = right_index;
    }

    if (biggest_index != index)
    {
        std::swap(model_vector[index], model_vector[biggest_index]);
  
        Sorting::make_heap(model_vector, biggest_index, field, last_index);
    }
}

void Sorting::make_merge(std::vector<Model>& model_vector, uint8_t field, size_t left, size_t right, size_t middle)
{
    if (left >= right || middle < left || middle > right) 
    {
        return;
    }

    if (right == left + 1 && (bool)(model_vector.at(left).compare_type(model_vector.at(right), field)).get_type_masked(field * 2)) 
    {
        std::swap(model_vector[left], model_vector[right]);
        return;
    }

    std::vector<Model> temp_vector(&model_vector[left], &model_vector[left] + (right + 1));

    for (std::size_t index = left, move = 0, offset = middle - left + 1; index <= right; ++index) 
    {
        if (move > middle - left) 
        {      
            model_vector[index] = temp_vector[offset++];
        } 
        else if (offset > right - left) 
        {
            model_vector[index] = temp_vector[move++];
        } 
        else 
        {
            if ((bool)(model_vector.at(offset).compare_type(model_vector.at(move), field)).get_type_masked(field * 2))
            {
                model_vector[index] = temp_vector[move++];
            }
            else
            {
                model_vector[index] = temp_vector[offset++];
            }
        }
    }
}