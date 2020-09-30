#include "doctest.h"
#include "CLI.h"

#include <cstring>


TEST_CASE("Testing correct data #1") {
    char program[] = "./hw_03";
    char mode[] = "-c";
    char input_flag[] = "-f";
    char output_flag[] = "--output";
    char input_file[] = "myfile.txt";
    char output_file[] = "result.bin";

    int argc = 6;
    char *argv1[] = {program, mode, input_flag, input_file,
                           output_flag, output_file};
    char *argv2[] = {program, mode, output_flag, output_file,
                           input_flag, input_file};
    char *argv3[] = {program, input_flag, input_file,
                           mode, output_flag, output_file};
    char *argv4[] = {program, output_flag, output_file,
                           mode, input_flag, input_file};
    char *argv5[] = {program, input_flag, input_file,
                           output_flag, output_file, mode};
    char *argv6[] = {program, output_flag, output_file,
                           input_flag, input_file, mode};

    HuffmanCLI cli;
    DataCLI correct_data = {compress, "myfile.txt", "result.bin"};
    CHECK(cli(argc, argv1) == correct_data);
    CHECK(cli(argc, argv2) == correct_data);
    CHECK(cli(argc, argv3) == correct_data);
    CHECK(cli(argc, argv4) == correct_data);
    CHECK(cli(argc, argv5) == correct_data);
    CHECK(cli(argc, argv6) == correct_data);
}


TEST_CASE("Testing correct data #2") {
    char program[] = "./hw_03";
    char mode[] = "-u";
    char input_flag[] = "--file";
    char output_flag[] = "-o";
    char input_file[] = "result.bin";
    char output_file[] = "myfile_new.txt";

    int argc = 6;
    char *argv1[] = {program, mode, input_flag, input_file,
                     output_flag, output_file};
    char *argv2[] = {program, mode, output_flag, output_file,
                     input_flag, input_file};
    char *argv3[] = {program, input_flag, input_file,
                     mode, output_flag, output_file};
    char *argv4[] = {program, output_flag, output_file,
                     mode, input_flag, input_file};
    char *argv5[] = {program, input_flag, input_file,
                     output_flag, output_file, mode};
    char *argv6[] = {program, output_flag, output_file,
                     input_flag, input_file, mode};

    HuffmanCLI cli;
    DataCLI correct_data = {extract, "result.bin", "myfile_new.txt"};
    CHECK(cli(argc, argv1) == correct_data);
    CHECK(cli(argc, argv2) == correct_data);
    CHECK(cli(argc, argv3) == correct_data);
    CHECK(cli(argc, argv4) == correct_data);
    CHECK(cli(argc, argv5) == correct_data);
    CHECK(cli(argc, argv6) == correct_data);
}


TEST_CASE("Some flags do not exist") {
    char program[] = "./hw_03";
    char mode[] = "-c";
    char input_flag[] = "-f";
    char output_flag[] = "--output";
    char input_file[] = "myfile.txt";
    char output_file[] = "result.bin";

    int argc1 = 5;
    int argc2 = 4;
    int argc3 = 4;
    char *argv1[] = {program, input_flag, input_file, output_flag, output_file};
    char *argv2[] = {program, mode, output_flag, output_file};
    char *argv3[] = {program, mode, input_flag, input_file};

    HuffmanCLI cli;
    bool result1 = false;
    bool result2 = false;
    bool result3 = false;
    try {
        cli(argc1, argv1);
    } catch (const ExceptionCLI &exception) {
        result1 = strcmp(exception.what(), "There is not a mode flag") == 0;
    }
    try {
        cli(argc2, argv2);
    } catch (const ExceptionCLI &exception) {
        result2 = strcmp(exception.what(), "There is not a flag for input file") == 0;
    }
    try {
        cli(argc3, argv3);
    } catch (const ExceptionCLI &exception) {
        result3 = strcmp(exception.what(), "There is not a flag for output file") == 0;
    }
    CHECK(result1);
    CHECK(result2);
    CHECK(result3);
}


TEST_CASE("There are too much flags") {
    char program[] = "./hw_03";
    char mode[] = "-c";
    char input_flag[] = "-f";
    char output_flag[] = "--output";
    char input_file[] = "myfile.txt";
    char output_file[] = "result.bin";

    int argc1 = 7;
    int argc2 = 8;
    int argc3 = 8;
    char *argv1[] = {program, mode, input_flag, input_file,
                     output_flag, output_file, mode};
    char *argv2[] = {program, mode, input_flag, input_file,
                     output_flag, output_file,
                     input_flag, input_file};
    char *argv3[] = {program, mode, input_flag, input_file,
                     output_flag, output_file,
                     output_flag, output_file};

    HuffmanCLI cli;
    bool result1 = false;
    bool result2 = false;
    bool result3 = false;
    try {
        cli(argc1, argv1);
    } catch (const ExceptionCLI &exception) {
        result1 = strcmp(exception.what(), "There are too much the mode flags") == 0;
    }
    try {
        cli(argc2, argv2);
    } catch (const ExceptionCLI &exception) {
        result2 = strcmp(exception.what(), "There are too much flags for input file") == 0;
    }
    try {
        cli(argc3, argv3);
    } catch (const ExceptionCLI &exception) {
        result3 = strcmp(exception.what(), "There are too much flags for output file") == 0;
    }
    CHECK(result1);
    CHECK(result2);
    CHECK(result3);
}


TEST_CASE("Testing incorrect data") {
    char program[] = "./hw_03";
    char mode[] = "-c";
    char input_flag[] = "-f";
    char output_flag[] = "-o";
    char input_file[] = "myfile.txt";
    char output_file[] = "result.bin";
    char stuff[] = "stuff";

    int argc1 = 5;
    int argc2 = 5;
    int argc3 = 7;
    char *argv1[] = {program, mode, output_flag,
                     output_file, input_flag};
    char *argv2[] = {program, mode, input_flag,
                     input_file, output_flag};
    char *argv3[] = {program, mode, input_flag, input_file,
                     output_flag, output_file, stuff};

    HuffmanCLI cli;
    bool result1 = false;
    bool result2 = false;
    bool result3 = false;
    try {
        cli(argc1, argv1);
    } catch (const ExceptionCLI &exception) {
        result1 = strcmp(exception.what(), "There is not a path to file after flag -f") == 0;
    }
    try {
        cli(argc2, argv2);
    } catch (const ExceptionCLI &exception) {
        result2 = strcmp(exception.what(), "There is not a path to file after flag -o") == 0;
    }
    try {
        cli(argc3, argv3);
    } catch (const ExceptionCLI &exception) {
        result3 = strcmp(exception.what(), "Correct flag expected instead -- stuff") == 0;
    }
    CHECK(result1);
    CHECK(result2);
    CHECK(result3);
}
