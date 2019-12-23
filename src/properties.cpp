#include <properties.hpp>
#include <map>
#include <fstream>
#include <sstream>
#include <logger.hpp>

std::map<std::string, std::string> properties;

void Properties::load(std::string&& fileName)
{
    print_function_call(fileName);

    std::ifstream file(fileName);
    if (!file)
    {
        std::runtime_error ex("Can't open properties file: \"" + fileName + "\"!");
        print_throw_exception(ex);
        throw ex;
    }

    log << "Loading properties...\n" << endl;

    std::string line, key, value;
    while (std::getline(file, line))
    {
        std::stringstream stream(std::move(line));
        std::getline(stream, key, ' ');
        std::getline(stream, value, ' ');
        properties[key] = value;

        cout << "\t" << key << " = " << value << endl;
    }

    file.close();
}

const std::string_view Properties::get_string(std::string&& key)
{
    print_function_call(key);
    
    if (properties.empty())
    {
        std::runtime_error ex("Properties are yet to be loaded!");
        print_throw_exception(ex);
        throw ex;
    }

    if (properties.count(key))
    {
        const std::string& raw = properties[key];
        const size_t length = raw.length();

        if (length >= 2)
        {
            if (raw.front() == '\"' && raw.back() == '\"')
            {
                try
                {
                    return raw.substr(1, length - 2);
                }
                catch (const std::exception& ex)
                {
                    print_throw_exception(ex);
                    throw ex;
                }
            }
        }

        std::logic_error ex("The property with key = \"" + key + "\" isn't a valid string!");
        print_throw_exception(ex);
        throw ex;
    }
    
    std::logic_error ex("The property with key = \"" + key + "\" can't be found!");
    print_throw_exception(ex);
    throw ex;
}

int Properties::get_int(std::string&& key)
{
    print_function_call(key);

    if (properties.empty())
    {
        std::runtime_error ex("Properties are yet to be loaded!");
        print_throw_exception(ex);
        throw ex;
    }

    if (properties.count(key))
    {
        const std::string& raw = properties[key];
        try
        {
            return stoi(raw);
        }
        catch (const std::invalid_argument&)
        {
            std::invalid_argument ex("The property with key = \"" + key + "\" can't be converted to an integer!");
            print_throw_exception(ex);
            throw ex;
        }
        catch (const std::exception& ex)
        {
            print_throw_exception(ex);
            throw ex;
        }
    }
    
    std::logic_error ex("The property with key = \"" + key + "\" can't be found!");
    print_throw_exception(ex);
    throw ex;
}