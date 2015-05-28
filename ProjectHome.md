"In mathematics, the sieve of Atkin is a fast, modern algorithm for finding all prime numbers up to a specified integer.  It was created in 2004 by A. O. L. Atkin and Daniel J. Bernstein.`[`1`]`" (http://en.wikipedia.org/wiki/Sieve_of_Atkin)

This is a platform-independent implementation of the sieve of Atkin algorithm.  It will support integers up to the size of `size_t`.  Be forwarned this can use an enormous amount of memory and so the upper limit in the constructor should be as realistic as possible.

There is only a  single header file ([atkinsieve.h](http://code.google.com/p/atkinsieve/source/browse/atkinsieve.h)) to be included with a straightforward interface.

<font face='courier, verdana, helvetica, arial'>
<pre><code>#include &lt;iostream&gt;<br>
#include "atkinsieve.h"<br>
<br>
int main(int argc, char* argv[])<br>
{<br>
     Atkin::Sieve s(100000000); // finds all primes under limit 100,000,000<br>
     <br>
     try <br>
     {<br>
          if (s.isPrime(13))<br>
               std::cout &lt;&lt; "13 is prime" &lt;&lt; std::endl;<br>
<br>
          if (s[25]) // alternative [] syntax<br>
               std::cout &lt;&lt; "25 is prime" &lt;&lt; std::endl;<br>
<br>
          s.resize(9000);  // now all primes under 9000<br>
<br>
          if (s[2500000]) // over 9000, exception thrown<br>
               std::cout &lt;&lt; "2500000 is prime" &lt;&lt; std::endl;<br>
     }<br>
     catch (const std::out_of_range&amp; e) // n &gt; sieve limit<br>
     {<br>
          std::cerr &lt;&lt; "Number out of range" &lt;&lt; std::endl;<br>
     }<br>
     <br>
     return 0;<br>
}<br>
</code></pre>
</font>
Program output:

```
13 is prime
25 is prime
Number out of range
```