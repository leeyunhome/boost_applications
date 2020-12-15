// first_program.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <boost/program_options.hpp>

namespace opt = boost::program_options;

int main(int argc, char *argv[])
{
    opt::options_description desc("All options");

    //desc.add_options()
    //    ("apples", opt::value<int>(), "how many apples do you have")
    //    ("oranges", opt::value<int>(), "how many oranges do you have")
    //    ("help", "produce help message")
    //    ;
    
    int oranges_var = 0;
    desc.add_options()
        ("oranges,o", opt::value<int>(&oranges_var)->required(),
            "oranges that you have")
        ("name", opt::value<std::string>(), "your name")
        ("apples,a", opt::value<int>()->default_value(10),
            "apples that you have");

    // Ŀ�ǵ���� ���ڸ� ������ ����
    opt::variables_map vm;

    // ���ڸ� �Ľ��� �� �����Ѵ�.
    opt::store(opt::parse_command_line(argc, argv, desc), vm);

    // ȯ�� ������ �Ľ��� ���� �ִ�.
    // 'opt::store with' 'parse_environment' �޼ҵ带 ���� �ȴ�.

    // �Ľ� �� ������ ������ �ҷ��� �Ѵ�.
    //opt::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return 1;
    }

    // "apples_oranges.cfg" ���� ���Ͽ��� ���� �ɼ��� �߰��Ѵ�.
    try
    {
        opt::store(
            opt::parse_config_file<char>("apples_oranges.cfg", desc),
            vm
        );
    }
    catch (const opt::reading_file& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try
    {
        // �ʼ� �ɼ��� �����ִٸ� `opt::required_option` ���ܸ� ������.
        opt::notify(vm);
    }
    catch (const opt::required_option& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 2;
    }

    if (vm.count("name")) {
        std::cout << "Hi," << vm["name"].as<std::string>() << "!\n";
    }

    std::cout << "Fruits count: "
        << vm["apples"].as<int>() + vm["oranges"].as<int>()
        << std::endl;

    //return 0;
}
