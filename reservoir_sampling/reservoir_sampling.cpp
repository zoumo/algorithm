/**
 * @file     reservoir_sampling
 * @author   zhangjun
 * @date     2014/07/15
 * @brief    蓄水池算法 抽样
 */
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "utllib.h"
#include "google/gflags.h"

using namespace std;

#define MAX_LINE_LEN 1024

DEFINE_string(is, "null", "input stream, default is stdin");
DEFINE_string(os, "null", "output stream, default is stdout");
DEFINE_int32(m, 0, "the size of output");
DEFINE_bool(l, false, "if -l is set up, than line number will be print");

istream *g_pistream = &cin;
ostream *g_postream = &cout;
// 不能在main_parse_options中使用局部变量
// 因为在函数结束后变量的生命周期结束, 就被销毁了
ifstream g_ifstream;
ofstream g_ofstream;
bool g_is_istream_file = false;
bool g_is_ostream_file = false;


typedef struct reservoir_t
{
    int id;
    char pline[MAX_LINE_LEN];
} reservoir;

void usage()
{
    string usage = "\n  this program a Example of reservoir sampling algorithm\n";
    usage += "  it sample m line from n line input\n";
    usage += "  reservoir_sampling -m num [-l] [-is input | -os output]\n";
    usage += "  Example:\n";
    usage += "    [1] cat input | ./reservoir_sampling -m=1000 > output\n";
    usage += "    [2] cat input | ./reservoir_sampling -m=1000 -l\n";
    usage += "    [3] ./reservoir_sampling -m=1000 -is=./input -os=./output\n";
    ::google::SetUsageMessage(usage);

}

int main_parse_options(int argc, char **argv)
{

    usage();

    ::google::ParseCommandLineFlags(&argc, &argv, true);

    if (!FLAGS_is.empty() && FLAGS_is != "null" && FLAGS_is != "stdin")
    {
        g_ifstream.open(FLAGS_is.c_str(), ios::in);
        if (!g_ifstream)
        {
            fprintf(stderr, "read file error\n");
            exit(1);
        }

        g_pistream = &g_ifstream;
        g_is_istream_file = true;
    }
    if (!FLAGS_os.empty() && FLAGS_os != "null" && FLAGS_os != "stdout")
    {
        g_ofstream.open(FLAGS_os.c_str(), ios::out);
        if (!g_ofstream)
        {
            fprintf(stderr, "read file error\n");
            exit(1);
        }
        g_postream = &g_ofstream;
        g_is_ostream_file = true;
    }


    if (FLAGS_m <= 0)
    {
        fprintf(stderr, "m should be greater than 0\n");
        exit(1);
    }

    return 0;
}

int close()
{
    if (g_is_istream_file)
    {
        g_ifstream.close();
    }
    if (g_is_ostream_file)
    {
        g_ofstream.close();
    }

    return 0;

}

int  reservoir_sampling(istream *is, reservoir *result, int m)
{
    srand((unsigned int)time(NULL));

    int index = -1;
    int swap_count = 0;
    char line[MAX_LINE_LEN] = {0};
    while (is->getline(line, MAX_LINE_LEN))
    {
        ++index;

        if (index < m)
        {
            result[index].id = index;
            //result[index].pline = &str_line;
            strcpy(result[index].pline, line);

            continue;
        }
        int j = random(index);
        if (j < m)
        {
            ++swap_count;
            int s = random(m);
            result[s].id = index;
            //result[s].pline = &str_line;
            strcpy(result[s].pline, line);
        }

    }

    cerr << "swap count : " << swap_count << endl;
    return true;
}

int main(int argc, char **argv)
{
    main_parse_options(argc, argv);

    int m = FLAGS_m;
    reservoir *result = (reservoir *)calloc(m, sizeof(reservoir));
    reservoir_sampling(g_pistream, result, m);

    for (int i = 0; i < m; ++i)
    {
        //cout << result[i].id << '\t' << result[i].pline << endl;
        // printf("%d\t%s\n", result[i].id, result[i].pline);
        char out_line[MAX_LINE_LEN] = {0};
        if (FLAGS_l)
        {
            sprintf(out_line, "%d\t%s\n", result[i].id, result[i].pline);
        }
        else
        {
            sprintf(out_line, "%s\n", result[i].pline);
        }

        g_postream->write(out_line, strlen(out_line));
    }

    close();

    return 0;
}
