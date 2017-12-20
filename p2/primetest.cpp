/*
 * CSc103 Project 2: prime numbers.
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main ()
{
    int n, i;
    while (cin >>n)
     {
    bool isPrime = true;

     if (n == 1)
     {
      isPrime = false;
     }
     else
     {
    for (i = 2; i <= n / 2; ++i)
      {

        if(n % i == 0)
        {
            isPrime = false;
            break;
        }
      }
     }
    if (isPrime)
        cout << "1\n";
    else
        cout << "0\n";
     }
    return 0;
}
