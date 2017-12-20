#include <cstdio>
#include <getopt.h> // to parse long arguments.
#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
#include <set>
using std::set;
using std::multiset;
#include <strings.h>
#include <vector>
using namespace std;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Limited clone of sort.  Supported options:\n\n"

"   -r,--reverse        Sort descending.\n"
"   -f,--ignore-case    Ignore case.\n"
"   -u,--unique         Don't output duplicate lines.\n"

"   --help              Show this message and exit.\n";

struct igncaseComp {
	bool operator()(const string& s1, const string& s2) {
		return (strcasecmp(s1.c_str(),s2.c_str()) < 0);
	}
};
/* NOTE: set<string,igncaseComp> S; would declare a set S which
 * does its sorting in a case-insensitive way! */
void reverse(){
	multiset<string, greater<string> >s1;
	typedef multiset<string, greater<string> >::iterator si;
	si iterator;
	string n;
	while (getline(cin,n)){
		if (n==" ")
			break;
		else
			s1.insert(n);
	}
	for (iterator=s1.begin(); iterator!=s1.end(); iterator++)
	cout<<*iterator<<endl;
}

void duplicate (){
	set<string, greater<string>>s2;
	typedef set <string>::iterator it ;
	it iterator;
	string n;
	while (getline (cin,n)){
		if (n==" ")
			break;
		else
			s2.insert(n);
	}
	for (iterator=s2.begin(); iterator!=s2.end(); iterator++)
	cout<<*iterator<<endl;
}

void ignorecase(){
	set<string>s3;
	typedef set<string>::iterator hi;
	hi iterator;
	string n;
	while (getline(cin,n)){
		if (n=="\n")
			break;
		else
			s3.insert(n);
	}
	for (iterator=s3.begin(); iterator!=s3.end(); iterator++)
	cout<<*iterator<<endl;
}

int main(int argc, char *argv[]) {
	// define long options
	static int descending=0, ignorecase=0, unique=0;
	static struct option long_opts[] = {
		{"reverse",       no_argument,   0, 'r'},
		{"ignore-case",   no_argument,   0, 'f'},
		{"unique",        no_argument,   0, 'u'},
		{"help",          no_argument,   0, 'h'},
		{0,0,0,0}
	};
	// process options:

	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "rfuh", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'r':
				reverse();
				descending = 1;
				break;
			case 'f':
				ignorecase = 1;
				break;
			case 'u':
				duplicate();
				unique = 1;
				break;
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}

	/* TODO: write me... */

	// get strings from input

	// do the sorting

	// write new vector to output




reverse();

	return 0;
}
