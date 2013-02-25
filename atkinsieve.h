/*
"In mathematics, the sieve of Atkin is a fast, modern algorithm for finding all
prime numbers up to a specified integer.  It was created in 2004 by A. O. L. Atkin
and Daniel J. Bernstein.[1]" (http://en.wikipedia.org/wiki/Sieve_of_Atkin)

This is a platform-independent implementation of the algorithm.  It will support
integers up to the size of size_t.  Be forwarned this can use an enormous amount 
of memory and so the upper limit in the constructor should be as realistic as 
possible.

URL: http://code.google.com/sieveofatkin/
Author: zerosum0x0  (zerosum0x0@gmail.com)
Version: 0.1 RC
Date: 24 February 2013
*/

#ifndef ATKIN_SIEVE_H
#define ATKIN_SIEVE_H

#include <deque>
#include <stdexcept>
#include <math.h>
#include <stdint.h>

namespace Atkin
{
    class Sieve
    {
        public:
			// arbitrary search limit, representing the max value of a prime search
            Sieve(size_t limit = 99999)
			{
				this->resize(limit);
			}

			const bool& operator[](size_t n) const
			{
				return this->isPrime(n);
			}

			bool isPrime(size_t n) const
			{
				if (n > this->_limit)
					throw std::out_of_range("");

				return this->_filter[n];
			}

            void resize(size_t limit)
			{
				this->_limit = limit;

				// initialize the sieve
				if (this->_filter.size() > this->_limit) // no need to recalculate
					return;

				this->_filter.clear();
				this->_filter.resize(this->_limit, false);

				size_t root =
						static_cast<int>(ceil(sqrt(static_cast<double>(this->_limit))));

				if (this->_limit >= 2) this->_filter[2] = true;
				if (this->_limit >= 3) this->_filter[3] = true;

				// put in candidate primes: 
				// integers which have an odd number of
				// representations by certain quadratic forms
				for (size_t x = 1; x <= root; ++x)
				{
					for (size_t y = 1; y <= root; ++y)
					{
						size_t n = (4 * (x * x)) + (y * y);

						if (n <= this->_limit && (n % 12 == 1 || n % 12 == 5))
							this->_filter[n] = this->_filter[n] ^ true; // ^= undefined

						n = (3 * (x * x)) + (y * y);

						if (n <= this->_limit && n % 12 == 7)
							this->_filter[n] = this->_filter[n] ^ true;

						n = (3 * (x * x)) - (y * y);
						if (x > y && n <= this->_limit && n % 12 == 11)
							this->_filter[n] = this->_filter[n] ^ true;
					}
				}

				// eliminate composites by sieving
				// r is prime, omit multiples of its square; this is
				// sufficient because composites which managed to get
				// on the list cannot be square-free
				for (size_t r = 5; r <= root; r++)
					if (this->_filter[r])
						for (size_t i = r * r; i < this->_limit; i += r * r)
							this->_filter[i] = false;
			}

            inline size_t limit() const { return this->_limit; }
            inline std::deque<bool> filter() const { return this->_filter; }

        protected:
            std::deque<bool> _filter;
            size_t _limit;
    };

} //namespace Atkin

#endif // ATKIN_SIEVE_H
