// first_program.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <boost/program_options.hpp>

namespace opt = boost::program_options;

int main(int argc, char *argv[])
{
    opt::options_description desc("All options");

    desc.add_options()
        ("apples", opt::value<int>(), "how many apples do you have")
        ("oranges", opt::value<int>(), "how many oranges do you have")
        ("help", "produce help message")
        ;

    // 커맨드라인 인자를 저장할 변수
    opt::variables_map vm;

    // 인자를 파싱한 후 저장한다.
    opt::store(opt::parse_command_line(argc, argv, desc), vm);

    // 파싱 후 저장한 다음에 불러야 한다.
    opt::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return 1;
    }

    std::cout << "Fruits count: "
        << vm["apples"].as<int>() + vm["oranges"].as<int>()
        << std::endl;

    //return 0;
}
