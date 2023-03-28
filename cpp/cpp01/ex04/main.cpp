#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char **argv)
{
    if (argc !=4)
    {
        std::cout << "Error: wrong number of arguments" << std::endl;
        return (1);
    }

    // Get file name, string s1 and string s2 from command line argument
    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    std::string new_filename = filename + ".replace";

    std::fstream file; //fstream is a class that can read and write to files
    std::fstream new_file;

    file.open(filename.c_str(), std::ios::in); //open file in read mode //c_str() converts string to c string
    new_file.open(new_filename.c_str(), std::ios::out); //open file in write mode

    if (!file.is_open())
    {
        std::cout << "Error: file could not be opened" << std::endl;
        return (1);
    }
    if (!new_file.is_open())
    {
        std::cout << "Error: file could not be opened" << std::endl;
        return (1);
    }

    //replace s1 with s2
    int i = 0;
    char c;
    std::string temp;
    while (file.get(c)) //get() returns false when it reaches the end of the file
    {
        while (c == s1[i])
        {
            temp += c;
            i++;
            while (file.get(c) && c == s1[i])
            {
                i++;
                temp += c;
            }
            if (i == (int)s1.length())
            {
                new_file << s2;
                i = 0;
                temp = "";
            }
            else
            {
                new_file << temp;
                i = 0;
                temp = "";
            }
        }
        temp = "";
        printf("%c\n", c);
        new_file << c;
    }
}
