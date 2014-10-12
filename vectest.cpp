#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    std::vector<float> test;
    test.push_back(0.0);
    test.push_back(0.1);
    test.push_back(0.2);
    test.push_back(0.3);
    test.push_back(0.4);
    test.push_back(0.5);
    test.push_back(0.6);
    test.push_back(0.7);

    for (int i=0; i<test.size(); i++) {
        std::cout << (&test[0])[i] << std::endl;
    }

    return 0;
}
