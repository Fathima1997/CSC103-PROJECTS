/*
 * CSc103 Project 3: Game of Life
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
 Fathima Mohammed Reeza
 */

#include <stdlib.h>
#include <getopt.h>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std:: string;
using std::ostringstream;

vector<vector<bool> > grid;
bool firstrun = true;
size_t psize, qsize;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Text-based version of Conway's game of life.\n\n"
"   --seed,-s     FILE     read start state from FILE.\n"
"   --world,-w    FILE     store current world in FILE.\n"
"   --fast-fw,-f  NUM      evolve system for NUM generations and quit.\n"
"   --help,-h              show this message and exit.\n";

size_t max_gen = 0; /* if > 0, fast forward to this generation. */
string wfilename =  "/tmp/gol-world-current"; /* write state here */
FILE* fworld = 0; /* handle to file wfilename. */
string initfilename = "/tmp/gol-world-current";
string reset;

int mod(int a, int b) {
    int r = a % b;
    if(r < 0)
        return r+b;
    else
        return r;
}

/* nbrCountfinds number of surrounding cells */
int nbrCount(int ind_p, int ind_q, const /*no intention of modifying the variable */ vector<vector<bool>>& g) {
    int count = 0;
    if(g[ind_q][ind_p]==true)
        --count;

    /*if for loop checks (p, q) then ^ will not count itself */
    for(int x = -1; x<2; ++x) {
        for(int y = -1; y<2; ++y)
        if(g[mod((ind_q+y), qsize)][mod((ind_p+x),psize)])
            count++;
    }

    /*iterates through all surrounding grid points, checks if they are boundary points. If they are, then (0,q) or (p,0) or (0,0) is checked instead. mod funtion emulates a "wrap-around" */
    return count;
}

void update() {
    if(firstrun) {
        for(int q = 0;  q <qsize; ++q){
            for(int p = 0; p < psize; ++p) {
                if(grid[q][p])
                    printf("0");
                else
                    printf(".");
            }
            printf("\n");
        }
        firstrun = false; //now this won't run more than once.
    }


        for(int q = 0; q <qsize; ++q) {
            for(int p = 0; p <psize; ++p) {
                if(grid[q][p]) printf("0");
                else printf(".");
            }
            printf("\n");
        }

}

void dumpState(FILE* fw) {
    const char* clist =".0\n";
    for(size_t q = 0; q < qsize; q++) {
        for(size_t p = 0; p < psize; p++){
            if(grid[q][p])
                fwrite(&clist[1],1,1,fw);
            else
                fwrite(&clist[0],1,1,fw);
        }
        fwrite(&clist[2],1,1,fw);
    }
}
int initFromFile(const string& fname) {
    fworld = fopen(fname.c_str(), "rb");
    char c;
    vector<bool> vec1;
    while(fread(&c,1,1,fworld)==1) {
        switch(c){
            case '.': vec1.push_back(false); break;
            case 'O': vec1.push_back(true); break;
            case'\n':
                grid.push_back(vec1);
                psize = vec1.size();
                vec1.clear();
                break;
        }
    }
    qsize = grid.size();
    fclose(fworld);
    return 1;
}

void mainLoop() {

    int surround;
    vector<vector<bool> > vec(qsize, vector<bool>(psize));
    for(int q = 0; q < qsize; q++) {
        for(int p = 0; p < psize; p++) {
            surround = nbrCount(p,q,grid); //if(surround < 0) surround  = 0;
            if(grid[q][p] && (surround > 3 || surround < 2)) // over and underpop
                vec[q][p]  = false;
            else if(grid[q][p] &&  (surround ==2 || surround ==3)) //survives
                vec[q][p] = true;
            else if (!grid[q][p] && surround == 3) //birth
                vec[q][p] = true;
        }
    }
    grid = vec;
}

int main(int argc, char *argv[]) {
    static struct option long_opts[] = {
        {"seed", required_argument, 0, 's'},
        {"world", required_argument, 0, 'w'},
        {"fast-fw", required_argument, 0, 'f'},
        {"help", no_argument, 0, 'h'},
        {0,0,0,0}
    };
    char c;
    int opt_index = 0;
    max_gen = 0;
    while ((c = getopt_long(argc, argv, "hs:w:f:", long_opts, &opt_index))!=-1)
    {
        switch(c) {
            case 'h':
                printf(usage, argv[0]);
                return 0;
            case 's':
                initfilename = optarg;
                break;
            case 'w':
                wfilename = optarg;
                break;
            case 'f':
                max_gen = atoi(optarg);
                break;
            case '?':
                printf(usage, argv[0]);
                return 1;
                break;
            default: abort();
        }
    }
    initFromFile(initfilename);

    ostringstream temp; // <--Only if running update more than once.
    temp<<qsize;
    string val = temp.str();
    reset = "\033["+ val +"A";

    fworld =  fopen(wfilename.c_str(), "w");
    if(max_gen > 0) {
    for(int p = 0; p < max_gen; p++)
        mainLoop();
    }
    else mainLoop();
    dumpState(fworld);
    fclose(fworld);
    update();
    return 0;
}
