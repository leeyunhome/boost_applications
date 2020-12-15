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

    // 커맨드라인 인자를 저장할 변수
    opt::variables_map vm;

    // 인자를 파싱한 후 저장한다.
    opt::store(opt::parse_command_line(argc, argv, desc), vm);

    // 환경 변수를 파싱할 수도 있다.
    // 'opt::store with' 'parse_environment' 메소드를 쓰면 된다.

    // 파싱 후 저장한 다음에 불러야 한다.
    //opt::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return 1;
    }

    // "apples_oranges.cfg" 구성 파일에서 빠진 옵션을 추가한다.
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
        // 필수 옵션이 빠져있다면 `opt::required_option` 예외를 던진다.
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
