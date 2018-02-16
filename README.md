# ClangEx - *A Fast C/C++ Fact Extractor*

This readme contains information about ClangEx, as well as setup and usage details.

## What is ClangEx?
ClangEx is a C/C++ fact extractor that uses Clang libraries to extract details from C or C++ source code to a lightweight but powerful program model. This program model can be visualized or queried using relational algebra to discover problems in source code on an ad-hoc basis.

The model generated by ClangEx is encoded in the Tuple-Attribute (TA)  format. This format was developed by Ric Holt at the University of Waterloo and is discussed in [this paper](http://plg.uwaterloo.ca/~holt/papers/ta-intro.htm). The TA format contains entities, their relationships, and attributes that describe these entities and relationships. 

While ClangEx is developed to extract facts to a program model, users must download additional tools from the [Sofware Architecture Group (SWAG)](http://www.swag.uwaterloo.ca/) at the Univesity of Waterloo to visualize or query their programs. This guide wil cover how these tools are configured in the "setup" section.

### Features of ClangEx
Currently, ClangEx supports the following:

* Both C & C++ language support including `C++11` and `C++14`.

* A more detailed program model compared to other extractors due to access to Clang's Abstract Syntax Tree (AST).

* The ability to generate a model for selected source files. This means that not all source files in a program have to be generated at once. This is achieved through ClangEx's manual ID linking system.

* A fluid metamodel. Users can choose to exclude certain portions of ClangEx's metamodel to generate TA files that suit them. For instance, TA models can be generated that don't include variables or classes.

### ClangEx Metamodel
The following diagram higlights the information ClangEx extracts from a target C/C++ program:

![alt text](https://github.com/bmuscede/ClangEx/blob/master/ClangExMetamodel.png "ClangEx MetaModel")

## Installation Details
### Prerequisties
ClangEx is based on `Clang 4.0.0` and requires `CMake 3.0.0` or greater to run. Additionally, to build ClangEx, `Boost` libraries are required. For `Boost`, the computer building ClangEx requires `Boost` version `1.5.8` or greater. If you meet any of these prerequisites, feel free to skip their associated section below.

#### Installing CMake
First, CMake should be installed. On Linux, this is as simple as running:
```
$ sudo apt-get install cmake
```
This will install the most current version of CMake based on your sources list. Be sure to check the version to ensure you have a version of CMake greater than `3.0.0`. This can be done by running:
```
$ cmake --version
```

---
If you want the most current version of CMake, this will require a bit of additional work. First, download the most recent version from the [CMake website](http://www.cmake.org) and download the Linux source version. The commands below show how CMake is installed from the `3.7.0` Linux source version. Change the version label in the download link to download a different version.

First, we download and unzip the source files:

```
$ wget https://cmake.org/files/v3.7/cmake-3.7.0.tar.gz
$ tar xvzf cmake-3.7.0.tar.gz
$ cd cmake-3.7.0.tar.gz
```

Next, install CMake by configuring the Makefile and running it. This can be done by doing the following:
```
$ ./configure
$ make
$ make install
```
That's it! You can check if CMake is correctly installed by running:
```
$ cmake --version
```

#### Installing Clang
The best way to install Clang on your system is to download Clang directly and compile the source code directly. As stated, `Clang 4.0.0` or greater is required. This guide will cover how to install Clang from source.

First, Clang must be downloaded from the Clang and LLVM website. To do this, simply run the following:
```
$ svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm
$ cd llvm/tools
$ svn co http://llvm.org/svn/llvm-project/cfe/trunk clang
$ cd clang/tools
$ svn co http://llvm.org/svn/llvm-project/clang-tools-extra/trunk extra
$ cd ../../../..:
```

Next, we need to build LLVM and Clang. Sit back and make a coffee during this process as this can take up to **several hours** depending on your computer. The following steps will build Clang to a directory called `Clang-Build` adjacent to the Clang install directory. To change this, simply replace the `Clang-Build` directory with any other directory and location you choose. 

There are two ways to build LLVM and Clang.

**1)** Build using `make`:

This is the standard way of building. To do this, run the following:
```
$ mkdir Clang-Build
$ cd Clang-Build
$ cmake -G "Unix Makefiles" ../llvm
$ make
$ make install 
```
---
**2)** Build using `ninja`:

Ninja is a lightweight build tool that promises to be faster than `make` and other build tools. To do this, run the following:
```
$ mkdir Clang-Build
$ cd Clang-Build
$ cmake -GNinja ../llvm
$ ninja
$ ninja install 
```

That's it! With this, Clang and LLVM will be installed. To ensure proper installation, run the following to check:
```
$ clang --version
```

#### Obtaining Boost Libraries
Boost libraries are also required. This process is very simple on Debian/Ubuntu systems.

Simply run the following command to download and install Boost libraries to your system's `include` path:
```
$ sudo apt-get install libboost-all-dev
```

**IMPORTANT NOTE:** Boost libraries are also needed on your system *even if* you are simply running the executable built on another system. Follow the instructions above to get the necessary Boost libraries to run the portable executable.

### Building ClangEx
Now that the prerequisties are all satisfied, you can now download and build ClangEx! If all prerequisties are truly satisfied, ClangEx should build without issue.

First, we must checkout the current version of ClangEx from GitHub. This will be downloaded to your current working directory. The ClangEx repository has all required files and libraries.

To download, run the following:
```
$ git checkout https://github.com/bmuscede/ClangEx.git
```

Next, we want to build the source code. This process may take several minutes due to the heavyweight size of the Clang libraries. This guide will build clang to the `ClangEx-Build` directory that is adjacent to the `ClangEx` library. If you want to build to a different directory, replace the following `ClangEx-Build`s  to the directory of your choice.

To build, run the following command:
```
$ mkdir Clang-Build
$ cd Clang-Build
$ cmake -G "Unix Makefiles" ../ClangEx
$ make
```

To verify that ClangEx built, ensure the `ClangEx-Build` directory contains a `include` subdirectory and that the ClangEx executable exists. Additionally, run the following to check if it runs:
```
$ ./ClangEx --help
```
You should see a help message with all available commands.

### Installing Additional Anaylsis Tools
There are two specific tools that are required to perform analysis on TA program models generated by ClangEx. Both of these tools  allow for querying and visualizing ClangEx Models. This guide will specify how to install these programs.

First, download the SWAGKit tarball from the University of Waterloo's [SWAG website](http://www.swag.uwaterloo.ca/swagkit/index.html) and unzip it to the directory of your choice:
```
$ wget http://www.swag.uwaterloo.ca/swagkit/distro/swagkit_linux86_bin_v3.03b.tar.gz
$ tar -xvzf swagkit_linux86_bin_v3.03b.tar.gz
```

Next, we want to add SWAGKit's binary path to your environment variables. To do this, simply do the following. **Note:** Replace the path to SWAGKit as shown in the following commands with the path to SWAGKit on your system!
```
$ echo "#SWAGKit Environment Variables:" >> ~/.bashrc
$ echo "export SWAGKIT_PATH=<REPLACE_WITH_SWAGKIT_PATH>" >> ~/.bashrc
$ echo "export PATH=$SWAGKIT_PATH/bin:$PATH" >> ~/.bashrc
```

That's it! You should be able to test if this worked by doing the following. The `bash` command will reload bash's environment variables and `grok` and `lsedit` are two analysis programs widely used.
```
$ bash
$ grok
$ lsedit
```

If both `Grok` and `LSEdit` started successfully, SWAGKit was configured on your computer. You are now able to run `ClangEx` and analyze program models!

## Running ClangEx
`ClangEx` has its own command line based system that allows for a user to add, remove, and manage extractions automatically. This is a specialized system that improves workflow.

To run, ClangEx without any options enabled, simply run the following:
```
$ ./ClangEx
```
Once ClangEx runs, you will be presented with a command prompt with your username. From here, you can enter commands to direct ClangEx. By typing `help` you will be presented with all options. 

The following steps provide information on how to do basic analysis with ClangEx. For more advanced options, read the help information included in ClangEx.

### Adding and Removing Files
To add files to ClangEx, you use the `add` command. Simply type the add command followed by a C/C++ file path or a directory and ClangEx will add it for processing. If you specify a folder, ClangEx will recursively search for all C/C++ files in that directory. An example of the add command:
```
$ add /home/main.cpp
$ add /home/some-folder/
```

Removing is similar. The `remove` command will remove files or a collection of files based on a regular expression. The `-s` flag will remove a file (you have to specify the full file path). The `-r` flag will remove a collection of files based on a regular expression. An example of the remove command:
```
$ remove -s /home/main.cpp
$ remove -r .*/home/.*
```

### Running ClangEx on Source Code
Once files have been added, you can run the ClangEx analyzer. To do this, you simply need to use the `generate` command. This command only works if files have been added. The '-v' command tells ClangEx to generate the AST in verbose mode.

There are two types of processing modes: *Partial Mode* is invoked automatically. *Blob Mode* is invoked with the `-b` flag. Examples of the generate command:
```
$ generate -v
$ generate -b -v
```
The first one generates while operating in verbose mode. The second generates in blob mode with verbose output.

**NOTE:** ClangEx requires the use of a compile_commands.json database located in some top level directory that tells ClangEx how to compile the files.

### Output TA Models
Once ClangEx generated the TA model from the previous step, it now can be outputted. To do this, simply use the `output` command. While there are many different options, the most simple usage of this command is the following:
```
$ output SampleTA
```

This creates a TA file called SampleTA.ta.

## ClangEx Analysis Modes
Since C/C++ can be a tricky language to analyze, there are two different analysis methodologies that `ClangEx` supports. The two modes are called *Partial* and *Blob*. **By default, partial analysis is performed*.

### Partial Analysis - [Default]
Partial analysis is enabled by default on `ClangEx`. Essentially, partial analysis only looks at source files directly passed to the Clang compiler. What that means is that models can be generated for specific segments by simply omitting any unnecessary source files.

In this mode, only code in the source files supplied are used. **Header files are ignored** since there is no way to distinguish between headers for other source files in the C/C++ language.

---
**Pros of this Approach:**

* Clean models that only contain files you want analyzed.

**Cons of this Approach:**

* Items used solely in the header file will be ignored.
* Doesn't really work well with C/C++ programs outside of "academic" or "well-written" source files.
---

Since this mode is enabled by default on `ClangEx` there is no need to invoke any flags. Simply run `ClangEx` as shown in the **Running ClangEx - [Default Options]** section.

### Blob Analysis
Blob analysis is a special type of analysis in `ClangEx` that considers all files "included" in a source file. Essentially the blob analysis system will look at items in the source file as well as header files included (*does not include system header files*). These declarations and definitions will be put in their appropriate file in the model.

The name *blob* simply refers to the fact that for one source file being analyzed, you may actually insert several files (and their associated features) in the model.

---
**Pros of this Approach:**

* Models are generated exactly as you expect.
* Items only used in header files are included.

**Cons of this Approach:**

* Selective analysis won't work. Once source file could mean numerous files inserted into the model.

---

For this mode, don't worry if you see that ClangEx is analyzing a file more than once. This redundancy is due to the `#include`s in source files.

## Current Issues
Currently ClangEx has the following things that need to be fixed:
1. Partial analysis is not complete. Unions, Structs, and variable scopes.
2. Printer is not fully working. Be sure that it works properly.
3. Field attributes for things like scope do not work.
