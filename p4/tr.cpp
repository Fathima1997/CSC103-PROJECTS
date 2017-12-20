/*
 * CSc103 Project 3: unix utilities
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
#include <string.h> // for c-string functions.
#include <getopt.h> // to parse long arguments.

static const char* usage =
"Usage: %s [OPTIONS] SET1 [SET2]\n"
"Limited clone of tr.  Supported options:\n\n"
"   -c,--complement     Use the complement of SET1.\n"
"   -d,--delete         Delete characters in SET1 rather than translate.\n"
"   --help          show this message and exit.\n";

int main()
{
	{
    int max = 0;
    unsigned int repetitioncount = 1;
    vector<string> vec;
	int result = 0;
	string text;

    cout << "Please Enter text " << endl;
    while(cin>>text && text != "qi"){
        vec.push_back(text);
    }
    for(unsigned int i = 1; i < vec.size(); i++){
        if (vec[i] == vec[i-1]) {
            repetitioncount++;
        } else {
            repetitioncount = 1;
        }
        if (repetitioncount > max) {
            result = i;
            max = repetitioncount;
    
    if (!vec.size())
        return 0;
        }
    }
    cout<<"Text = "<<vec[result]<<", Repetition = "<<max<<endl;
    return 0;
}
