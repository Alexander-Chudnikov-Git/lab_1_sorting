/**
 * @file       <test.cpp>
 * @brief      This source file is an example of how to use sorting algorithms implemented for laboratory work 1. 
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
#include "src/generator/generator.hpp"
#include "src/sorting/sorting.hpp"
#include <iostream>
#include <boost/program_options.hpp>
#include <algorithm>
#include <bitset>

namespace po = boost::program_options;

int main(int argc, char const *argv[])
{
	std::size_t opt;
    std::size_t mode;
    bool silent;

    po::options_description describtion("Default options");
    po::variables_map variable_map;

    describtion.add_options()
    	("help,H", 	"produces help message")
    	("amount,A", po::value<std::size_t>(&opt)->default_value(100), "determines how many lines does debug output prints")
        ("mode,M", po::value<std::size_t>(&mode)->default_value(0), "determines wich row should be sorted")
        ("silent,S", po::value<bool>(&silent)->default_value(false), "mutes output of models")
    	("debug,D", "prints out debug data");

    try 
    {
        po::store(po::parse_command_line(argc, argv, describtion), variable_map);
    }
    catch (std::exception const& exception)
    {
        std::cout << exception.what();
    }

    po::notify(variable_map);

    if (variable_map.count("help")) 
    {
        std::cout << describtion << std::endl;
        return 1;
    }

    if (variable_map.count("debug")) 
    {
        Generator generator;
        std::size_t desired_vector_size = opt;

        // Model generation 

		std::cout << "Amount is: " << opt << "\n";  

        auto start = std::chrono::high_resolution_clock::now();

        std::vector<Model> model_vector;
        std::vector<Model> b_model_vector;
        std::vector<Model> h_model_vector;
        std::vector<Model> l_model_vector;

        for (std::size_t index = 0; index < desired_vector_size; ++index)
        {
            model_vector.push_back(generator.model_generator());
        }

        b_model_vector = model_vector;
        h_model_vector = model_vector;
        l_model_vector = model_vector;

        auto finish = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double, std::milli> elapsed = finish - start;
        std::cout << "Model generation took: " << elapsed.count() << " ms" << std::endl;

        // Model output 
        if (!silent)
        { 
            std::cout << "Model itself: \n";
            
            std::cout << Model(3) << std::endl;
            std::cout << Model(0) << std::endl;

            for (std::size_t index = 0; index < desired_vector_size; ++index)
            {
                if (index == desired_vector_size - 1)
                {
                    model_vector[index].set_decor(1);
                }
                std::cout << model_vector[index] << std::endl;
                if (index == desired_vector_size - 1)
                {
                    model_vector[index].set_decor(0);
                }
            }

            std::cout << Model(4) << std::endl;
        }

        // Bubble sorting
        std::cout << "Buble sorting: " << "\n";  

        start = std::chrono::high_resolution_clock::now();

        Sorting::bubble_sort(b_model_vector, mode);

        finish = std::chrono::high_resolution_clock::now();
        
        elapsed = finish - start;
        std::cout << "Sorting took: " << elapsed.count() << " ms" << std::endl;

        // Model after bubble sorting 
        if (!silent)
        { 
            std::cout << "Model after sorting: \n";
            
            std::cout << Model(3) << std::endl;
            std::cout << Model(0) << std::endl;

            for (std::size_t index = 0; index < desired_vector_size; ++index)
            {
                if (index == desired_vector_size - 1)
                {
                    b_model_vector[index].set_decor(1);
                }
                std::cout << b_model_vector[index] << std::endl;
                if (index == desired_vector_size - 1)
                {
                    b_model_vector[index].set_decor(0);
                }
            }

            std::cout << Model(4) << std::endl;
        }

        // Heap sorting
        std::cout << "Heap sorting: " << "\n";  

        start = std::chrono::high_resolution_clock::now();

        Sorting::heap_sort(h_model_vector, mode);

        finish = std::chrono::high_resolution_clock::now();
        
        elapsed = finish - start;
        std::cout << "Sorting took: " << elapsed.count() << " ms" << std::endl;

        // Model after heap sorting 
        if (!silent)
        { 
            std::cout << "Model after sorting: \n";
            
            std::cout << Model(3) << std::endl;
            std::cout << Model(0) << std::endl;

            for (std::size_t index = 0; index < desired_vector_size; ++index)
            {
                if (index == desired_vector_size - 1)
                {
                    h_model_vector[index].set_decor(1);
                }
                std::cout << h_model_vector[index] << std::endl;
                if (index == desired_vector_size - 1)
                {
                    h_model_vector[index].set_decor(0);
                }
            }

            std::cout << Model(4) << std::endl;
        }

        // Merge sorting
        std::cout << "Merge sorting: " << "\n";  

        start = std::chrono::high_resolution_clock::now();

        Sorting::merge_sort(l_model_vector, mode, 0, l_model_vector.size() - 1);

        finish = std::chrono::high_resolution_clock::now();
        
        elapsed = finish - start;
        std::cout << "Sorting took: " << elapsed.count() << " ms" << std::endl;

        // Model after merge sorting 
        if (!silent)
        { 
            std::cout << "Model after sorting: \n";
            
            std::cout << Model(3) << std::endl;
            std::cout << Model(0) << std::endl;

            for (std::size_t index = 0; index < desired_vector_size; ++index)
            {
                if (index == desired_vector_size - 1)
                {
                    l_model_vector[index].set_decor(1);
                }
                std::cout << l_model_vector[index] << std::endl;
                if (index == desired_vector_size - 1)
                {
                    l_model_vector[index].set_decor(0);
                }
            }

            std::cout << Model(4) << std::endl;
        }    	

        return 1;
    }

	return 0;
}