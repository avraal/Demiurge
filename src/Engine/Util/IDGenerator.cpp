
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 13.08.18.
//

#include "IDGenerator.hpp"
int IDGenerator::currentId = 0;

int IDGenerator::getNextId()
{
    return IDGenerator::currentId++;
}