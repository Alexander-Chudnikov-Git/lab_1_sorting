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
#include <iostream>
#include <boost/program_options.hpp>
#include <algorithm>
#include <bitset>

namespace po = boost::program_options;

int main(int argc, char const *argv[])
{
	std::size_t opt;

    po::options_description describtion("Default options");
    po::variables_map variable_map;

    describtion.add_options()
    	("help,H", 	"produces help message")
    	("amount,A", po::value<std::size_t>(&opt)->default_value(100), "determines how many lines does debug output prints")
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

		std::cout << "Amount is " << opt << "\n";   

    	Generator generator;
    	std::size_t desired_vector_size = opt;
    	std::vector<Model> model_vector;

    	std::cout << Model(3) << std::endl;
    	std::cout << Model(0) << std::endl;

    	for (std::size_t index = 0; index < desired_vector_size; ++index)
    	{
    		model_vector.push_back(generator.model_generator());
    		if (index == (desired_vector_size - 1))
    		{
    			model_vector[index].set_decor(1);

				std::cout << (model_vector[index] == model_vector[index])<< std::endl;
    		}
    		std::cout << model_vector.at(index) << std::endl;
    	}

        std::cout << Model(4) << std::endl;
        return 1;
    }


    
	return 0;
}