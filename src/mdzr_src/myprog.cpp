// ***************************************************************** -*- C++ -*-
// iptcprint.cpp, $Rev: 3090 $
// Sample program to print the IPTC metadata of an image
#include <exiv2/exiv2.hpp>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <filesystem>

inline int type(const std::__fs::filesystem::path &dir_path)
{
    return std::__fs::filesystem::is_directory(dir_path)
               ? 0
               : std::__fs::filesystem::is_regular_file(dir_path)
                     ? 1
                     : -1;
}
std::vector<std::string> files_in_path(const std::__fs::filesystem::path &dir_path)
{
    std::vector<std::string> files;
    if (dir_path.empty())
        return files;

    switch (type(dir_path))
    {
    case -1:
        return files;
        break;
    case 0:
        for (const auto &entry : std::__fs::filesystem::directory_iterator(dir_path))
        {
            if(type(entry) == -1)
            {
                return files;
            }
            else if (type(entry) == 0)
            {
                std::vector<std::string> filesEncapsulated = files_in_path(entry);
                files.insert(files.end(), filesEncapsulated.begin(), filesEncapsulated.end());
            }
            else if (type(entry) == 1)
            {
                if (std::string(entry.path().filename())[0] == '.')
                    continue;
                files.push_back(entry.path());
            }
        }
        break;
    case 1:
        if (std::string(dir_path.filename())[0] == '.')
            break;
        files.push_back(dir_path);
        break;
    }

    return files;
}

int main(int argc, char *const argv[])
try
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " file\n";
        return 1;
    }

    auto start1 = std::chrono::high_resolution_clock::now();

    auto files = files_in_path(argv[1]);
    for (auto file : files)
    {
        auto image = Exiv2::ImageFactory::open(file);
        assert(image.get() != 0);
        image->readMetadata();
        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty())
        {
            std::string error(argv[1]);
            error += ": No IPTC data found in the file";
            // throw Exiv2::Error(1, error);
        }
        Exiv2::ExifData::iterator end = exifData.end();
        for (Exiv2::ExifData::iterator md = exifData.begin(); md != end; ++md)
        {
            //   std::cout << std::setw(44) << std::setfill(' ') << std::left
            //             << md->key() << " "
            //             << "0x" << std::setw(4) << std::setfill('0') << std::right
            //             << std::hex << md->tag() << " "
            //             << std::setw(9) << std::setfill(' ') << std::left
            //             << "name: " << md->typeName() << " "
            //             << std::dec << std::setw(3)
            //             << std::setfill(' ') << std::right
            //             << md->count() << "  "
            //             << std::dec << md->value()
            //             << std::endl;
        }
    }
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);

    std::cout << "Read " << files.size() << " file(s)"
              << std::setw(50 - 29 - std::to_string(files.size()).length())
              << " | " << duration1.count()
              << std::setw(20 - std::to_string(duration1.count()).length())
              << " microsecs" << std::endl;
    return 0;
}
catch (Exiv2::AnyError &e)
{
    std::cout << "Caught Exiv2 exception '" << e << "'\n";
    return -1;
}