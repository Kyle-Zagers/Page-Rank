#include "PageRank.h"
#include <iostream>
using std::cout;
using std::endl;

int main() {
    int no_of_lines, power_iterations;
    std::string from, to;
    std::cin >> no_of_lines;
    std::cin >> power_iterations;

    PageRank myPageRank = PageRank(power_iterations);

    for(int i = 0; i < no_of_lines; i++)
    {
        std::cin >> from;
        std::cin >> to;
        myPageRank.addLink(from, to);
    }
    
    myPageRank.printRank();
    return 0;
}