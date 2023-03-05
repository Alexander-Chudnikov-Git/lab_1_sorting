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
 */
#include "src/generator/generator.hpp"
#include "src/model/model.hpp"
#include "src/sorting/sorting.hpp"
#include <iostream>
#include <boost/program_options.hpp>
#include <algorithm>
#include <bitset>
#include <string>

namespace po = boost::program_options;

int main(int argc, char const *argv[])
{
	std::size_t amount;
    std::size_t iterations;
    std::size_t mode;
    bool silent;
    std::string file_path;

    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point finish;
    std::chrono::duration<double, std::milli> elapsed;

    po::options_description describtion("Default options");
    po::variables_map variable_map;

    describtion.add_options()
    	("help,H", 	"produces help message")
    	("amount,A", po::value<std::size_t>(&amount)->default_value(100), "determines how many lines does debug output prints")
        ("iteration,I", po::value<std::size_t>(&iterations)->default_value(10), "determines how many testion iterations there should be")
        ("mode,M", po::value<std::size_t>(&mode)->default_value(0), "determines wich row should be sorted")
        ("silent,S", po::value<bool>(&silent)->default_value(false), "mutes output of models")
        ("file_name,F", po::value<std::string>(&file_path)->default_value("./set_data/"), "specifies file path to write/load model without .json")
        ("load,L", "loads model from file")
        ("generate,G", "generates model and writes it into file")
        ("test,T", "performs some tests on given data")
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

    std::vector<Model> model_vector;
    std::vector<std::vector<Model>> model_vector_set;

    std::filesystem::path avg_file_path(file_path);

    
    if (variable_map.count("generate"))
    {
        Generator generator;
        
        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            start = std::chrono::high_resolution_clock::now();

            for (std::size_t index = 0; index < amount; ++index)
            {
                model_vector.push_back(generator.model_generator());
            }

            finish = std::chrono::high_resolution_clock::now();

            model_vector_set.push_back(model_vector);
            
            std::chrono::duration<double, std::milli> elapsed = finish - start;
            std::cout << "\t Iteration: " << iteration << "\t - Model generation took: " << elapsed.count() << " ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                Model::print_model(model_vector);
            }

            if (avg_file_path.has_filename())
            {
                std::string file_extension = avg_file_path.extension().string();
                std::string new_filename = avg_file_path.filename().string();
                new_filename = new_filename.substr(0, new_filename.find_last_of("."));

                if (iterations != 1)
                {
                    new_filename += "_";
                    new_filename += std::to_string(iteration);
                }
    
                avg_file_path.replace_extension("");
                avg_file_path.replace_filename(new_filename + file_extension);

                Model::save_model(model_vector, avg_file_path);
            }
            else
            {
                Model::save_model(model_vector, std::filesystem::path(avg_file_path.string() + "model_data_" + std::to_string(iteration) + ".json"));
            }
        }
    }
    else if (variable_map.count("load"))
    {
        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            if (avg_file_path.has_filename())
            {
                std::string file_extension = avg_file_path.extension().string();
                std::string new_filename = avg_file_path.filename().string();
                new_filename = new_filename.substr(0, new_filename.find_last_of("."));

                if (iterations != 1)
                {
                    new_filename += "_";
                    new_filename += std::to_string(iteration);
                }
    
                avg_file_path.replace_extension("");
                avg_file_path.replace_filename(new_filename + file_extension);

                Model::load_model(model_vector, avg_file_path);
            }
            else
            {
                std::cout << "Loading: " << std::filesystem::path(avg_file_path.string() + "model_data_" + std::to_string(iteration) + ".json") << std::endl;
                Model::load_model(model_vector, std::filesystem::path(avg_file_path.string() + "model_data_" + std::to_string(iteration) + ".json"));
            }

            model_vector_set.push_back(model_vector);

            if (variable_map.count("debug")) 
            {
                Model::print_model(model_vector);
            }
        }
    }

    if (variable_map.count("test"))
    {
        std::vector<Model> test_model_vector;

        // Bubble sorting
        std::cout << "Bubble sorting: " << "\n";  

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            test_model_vector = model_vector_set.at(iteration);

            start = std::chrono::high_resolution_clock::now();

            Sorting::bubble_sort(test_model_vector, mode);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Iteration: " << iteration << "\t - Sorting took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                Model::print_model(test_model_vector);
            }
        }

        // Heap sorting
        std::cout << "Heap sorting: " << "\n";  

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            test_model_vector = model_vector_set.at(iteration);

            start = std::chrono::high_resolution_clock::now();

            Sorting::heap_sort(test_model_vector, mode);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Iteration: " << iteration << "\t - Sorting took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                Model::print_model(test_model_vector);
            }
        }

        // Merge sorting
        std::cout << "Merge sorting: " << "\n";  

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            test_model_vector = model_vector_set.at(iteration);

            start = std::chrono::high_resolution_clock::now();

            Sorting::merge_sort(test_model_vector, mode);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Iteration: " << iteration << "\t - Sorting took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                Model::print_model(test_model_vector);
            }
        }
        
    }


    /*
    if (variable_map.count("debug")) 
    {
        Generator generator;
        std::size_t desired_vector_size = amount;

        // Model generation 

		std::cout << "Amount is: " << amount << "\n";  

        start = std::chrono::high_resolution_clock::now();

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

        finish = std::chrono::high_resolution_clock::now();
        
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
    */

	return 0;
}