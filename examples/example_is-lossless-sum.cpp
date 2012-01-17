#include <limits>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>

#include "mili/mili.h"

using namespace mili;

const unsigned long GOAL = 1e9; //find 1000 million cases

class Time
{
public:
    Time()
    {
        _start = clock();
    }

    double elapsed_secs() const
    {
        return (((double)clock() - _start) / CLOCKS_PER_SEC);
    }

private:
    clock_t _start;
};

template<class T, const bool use_max>
class Test
{
public:
    Test(unsigned long target) :
        _low(std::numeric_limits<T>::min()),
        _high(std::numeric_limits<T>::max()),
        _target(target)
    {
    }

    double run()
    {
        unsigned long long total(0);

        Time t;
        while (total < _target)
        {
            if (use_max)
            {
                if (! is_lossless_sum(_low, _high))
                    ++total;
            }
            else if (! is_lossless_sum_bigsmall(_high, _low))
                ++total;

            const double temp = nextafter(_low, _high);
            _high = nextafter(_high, _low);
            _low  = temp;
        }

        return t.elapsed_secs();
    }

private:

    T _low;
    T _high;

    unsigned long _target;
};

int main(void)
{
    std::cout << "Warning, this could take many minutes." << std::endl;
    std::cout << "Searching for " << GOAL << " sums with data loss using float and double." << std::endl;

    Test<double, true>  test1(GOAL);
    Test<double, false> test2(GOAL);
    Test<float, true>   test3(GOAL);
    Test<float, false>  test4(GOAL);

    std::cout << "Double, with max:    " << test1.run() << " seconds testing." << std::endl;
    std::cout << "Double, without max: " << test2.run() << " seconds testing." << std::endl;
    std::cout << "Float, with max:     " << test3.run() << " seconds testing." << std::endl;
    std::cout << "Float, without max:  " << test4.run() << " seconds testing." << std::endl;

    return 0;
}
