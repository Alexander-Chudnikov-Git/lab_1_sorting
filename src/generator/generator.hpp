/**
 * @file       <generator.hpp>
 * @brief      This header file holds implementation of Generator class. 
 * 
 *             This calss implements model generator needed for successfull completion of laboratory work 1.
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
#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <random>

#include <array>


#ifndef MODEL_HPP
#include "../model/model.hpp"
#endif // MODEL_HPP

class Generator
{
public:
	Generator();
	~Generator();

    Model model_generator();

private:
    std::array<std::string, 2738> _first_name_list;
    std::array<std::string, 1000> _last_name_list;
    std::array<std::string, 449> _department_list;
    std::array<std::string, 357> _job_title_list;
    
    std::random_device       _random_device; 
    std::mt19937             _generator;

    std::uniform_int_distribution<uint32_t> _first_name_distribution;
    std::uniform_int_distribution<uint32_t> _last_name_distribution;
    std::uniform_int_distribution<uint32_t> _department_distribution;
    std::uniform_int_distribution<uint32_t> _job_title_distribution;
    std::uniform_int_distribution<uint16_t> _year_distribution;
    std::uniform_int_distribution<uint16_t> _month_distribution;
    std::uniform_int_distribution<uint16_t> _day_distribution;
    std::uniform_int_distribution<uint16_t> _sex_distribution;
};

#endif // GENERATOR_HPP