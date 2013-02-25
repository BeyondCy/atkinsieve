#include <iostream>
#include "atkinsieve.h"

int main(int argc, char* argv[])
{
	const int SIEVE_LIMIT = 9999;

    Atkin::Sieve sieve(SIEVE_LIMIT);
    size_t n = 0;

    for (;;)
    {
        std::cout << "Enter an integer 0-" << SIEVE_LIMIT << ": ";
        std::cin >> n;

		try 
		{
			std::cout << (sieve[n] ? "Prime." : "Not prime.") << std::endl;
		} 
		catch (const std::out_of_range& e) // n > SIEVE_LIMIT
		{
			std::cerr << "Number out of range." << std::endl;
		}
    }

    return 0;
}

