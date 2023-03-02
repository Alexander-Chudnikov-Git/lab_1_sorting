/**
 * @file       <model.hpp>
 * @brief      This header file holds implementation of Model class. 
 * 
 *             This calss implements model needed for successfull completion of laboratory work 1.
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
#ifndef MODEL_HPP
#define MODEL_HPP

#include <chrono>
#include <string>
#include <cstring> // strcmp has better performance 
#include <vector>
#include <iomanip>

#include <bitset>

class ModelComp;

class Model
{
public:
    Model(std::string full_name, std::string department, std::string job_title, std::chrono::year_month_day employment_date);
    Model(std::string full_name, std::string department, std::string job_title, std::string employment_date);
    Model(std::uint8_t decor_type);
    ~Model();

    void set_model(std::string full_name, std::string department, std::string job_title, std::chrono::year_month_day employment_date);
    void set_model(std::string full_name, std::string department, std::string job_title, std::string employment_date);
    void set_decor(std::uint8_t decor_type);

    ModelComp compare_type(const Model& r_model, uint8_t mode);

    friend std::ostream& operator<< (std::ostream& stream, const Model& model);

    friend ModelComp     operator<  (const Model& l_model, const Model& r_model);
    friend ModelComp     operator>  (const Model& l_model, const Model& r_model);
    friend ModelComp     operator<= (const Model& l_model, const Model& r_model);
    friend ModelComp     operator>= (const Model& l_model, const Model& r_model);

    friend ModelComp     operator== (const Model& l_model, const Model& r_model);
    friend ModelComp     operator!= (const Model& l_model, const Model& r_model);

private:
    std::string                     _full_name;
    std::string                     _department;
    std::string                     _job_title;
    std::chrono::year_month_day     _employment_date;

    std::uint8_t                    _decor_type;
};

class ModelComp 
{
public:
    ModelComp();
    ModelComp(uint8_t value);
    ~ModelComp();

    void set_type_masked(uint8_t value, uint8_t offset);

    void set_name_type(uint8_t value);
    void set_dept_type(uint8_t value);
    void set_jobt_type(uint8_t value);
    void set_date_type(uint8_t value);

    uint8_t get_type_masked(uint8_t offset) const;

    uint8_t get_name_type() const;
    uint8_t get_dept_type() const;
    uint8_t get_jobt_type() const;
    uint8_t get_date_type() const;

    friend ModelComp operator== (const ModelComp& l_bool, const ModelComp& r_bool);
    friend ModelComp operator!= (const ModelComp& l_bool, const ModelComp& r_bool);

    friend std::ostream& operator<< (std::ostream& stream, const ModelComp& model);

    ModelComp operator! () const;

private:
    uint8_t _value;
};

#endif // MODEL_HPP