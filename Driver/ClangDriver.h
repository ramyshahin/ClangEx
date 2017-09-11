/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ClangDriver.cpp
//
// Created By: Bryan J Muscedere
// Date: 05/09/17.
//
// Driver that allows user commands to be converted into slome sort of
// ClangEx action. Can add files, manage TA files, output files, and
// run ClangEx on a desired source file. Ensures commands are handled gracefully

// Copyright (C) 2017, Bryan J. Muscedere
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLANGEX_CLANGDRIVER_H
#define CLANGEX_CLANGDRIVER_H

#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include "../Graph/TAGraph.h"

using namespace boost::filesystem;

class ClangDriver {
public:
    /** Constructor/Destructor */
    ClangDriver();
    ~ClangDriver();

    /** Language Printers */
    std::string printStatus(bool files, bool ta, bool toggle);
    std::string getLanguageString();

    /** Counters */
    int getNumGraphs();
    int getNumFiles();

    /** Enable/Disable Features */
    bool enableFeature(std::string feature);
    bool disableFeature(std::string feature);

    /** ClangEx Runner */
    bool processAllFiles(bool blobMode, std::string mergeFile, bool verboseMode);

    /** Output Helpers */
    bool outputIndividualModel(int modelNum, std::string fileName = std::string());
    bool outputAllModels(std::string baseFileName);

    /** Add/Remove By Path */
    int addByPath(path curPath);
    int removeByPath(path curPath);
    int removeByRegex(std::string regex);

    /** Toggle System */
    typedef struct {
        bool cSubSystem = false;
        bool cFile = false;
        bool cClass = false;
        bool cFunction = false;
        bool cVariable = false;
        bool cEnum = false;
        bool cStruct = false;
        bool cUnion = false;
    } ClangExclude;
private:
    /** Default Arguments */
    const std::string INSTANCE_FLAG = "$INSTANCE";
    const std::string DEFAULT_EXT = ".ta";
    const std::string DEFAULT_FILENAME = "out";
    const std::string DEFAULT_START = "./ClangEx";
    const std::string INCLUDE_DIR = "./include";
    const std::string INCLUDE_DIR_LOC = "--extra-arg=-I" + INCLUDE_DIR;
    const int BASE_LEN = 2;

    /** Private Variables */
    std::vector<TAGraph*> graphs;
    std::vector<path> files;
    std::vector<std::string> ext;

    /** Toggle System */
    std::string langString = "\tcSubSystem\n\tcFile\n\tcClass\n\tcFunction\n\tcVariable\n\tcEnum\n\tcStruct\n\tcUnion\n";
    ClangExclude toggle;

    /** C/C++ Extensions */
    const std::string C_FILE_EXT = ".c";
    const std::string CPLUS_FILE_EXT = ".cc";
    const std::string CPLUSPLUS_FILE_EXT = ".cpp";

    /** Add/Remove Helper Methods */
    int addFile(path file);
    int addDirectory(path directory);
    int removeFile(path file);
    int removeDirectory(path directory);

    /** Enabled Strings */
    std::vector<std::string> getEnabled();
    std::vector<std::string> getDisabled();

    /** Output Helper Method */
    bool outputTAString(int modelNum, std::string fileName);

    /** Argument Helpers */
    char** prepareArgs(int *argc);
};


#endif //CLANGEX_CLANGDRIVER_H