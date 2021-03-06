#include <iostream>
#include <sstream>
#include <fstream>
#include "utility.h"
#include "stdcell.h"

std::istream& operator>>(std::istream& is, stdcell& d)
{
    //ignore to skip .cell in the beginning
    is.ignore(5) >> d.name >> d.width >> d.length;

    while(not is.eof())
    {
        std::string s;
        is >> s;
        std::string name = s.substr(0, s.find('.'));
        if(name.empty()) {
            break;
        }
        else if(s.find(".I") != std::string::npos) {
            d.inputs.push_back(name);
        }
        else if(s.find(".O") != std::string::npos) {
            d.outputs.push_back(name);
        }
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const stdcell& d)
{
    os << d.name   << " " << d.length << " " << d.width << " " 
       << d.inputs << " " << d.outputs;
    return os;
}

MattCellFile::MattCellFile(const std::string& filename)
{
    cells.clear();
    std::ifstream file(filename);
    if(file.is_open())
    {
        std::string line;
        while(std::getline(file, line))
        {
            if(line.substr(0,5) != ".cell")
                continue;
            std::stringstream ss(line);
            stdcell cell;
            ss >> cell;
            cells[cell.name] = cell;
        }
    }
}

const stdcell& MattCellFile::operator[](const std::string& cell_name)
{
    return cells[cell_name];
}

std::ostream& operator<<(std::ostream& os, const MattCellFile& mc)
{
    for(const auto& entry : mc.cells)
        os << entry.first << " -> " << entry.second << std::endl;
    return os;
}
