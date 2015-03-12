/**
 * @file     Utils.h
 * @author   zhangjun
 * @date     2014/07/15
 * @brief    各种实用方法
 */


#include <stdlib.h>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <pthread.h>

using namespace std;

#define random(x) (rand() % (x))

// ======================= global ============================================
stringstream g_ssConvert;
pthread_mutex_t  g_ss_mutex = PTHREAD_MUTEX_INITIALIZER;


// c++ split string with delim
int split(const string &s, char delim, vector<string> &elems)
{
    int ret = 0;
    stringstream ss(s);
    string item;
    while (std::getline(ss, item, delim))
    {
        if (!item.empty())
        {
            elems.push_back(item);
        }
    }
    return ret;
}

int split(const char *s, char delim, vector<string> &elems)
{
    string str = string(s);
    return split(str, delim, elems);
}

bool is_space(char ch)
{
    if (ch == ' ' || ch == '\r' || ch == '\n' || ch  == '\t')
    {
        return true;
    }
    return false;
}


/**
 * trim left blank character
 * @param <char *>  str: input string
 * @return new char*
 */
char* ltrim(char *str)
{
    if (str == NULL) {
        return NULL;
    }

    while (is_space(*str)) {
        ++str;
    }

    return str;

}

/**
 * trim both side blank character
 * @ param <const string &> str: input string
 * @ return new string
 */
string ltrim(const string &str)
{
    return str.substr(str.find_first_not_of(" \r\n\t"), str.length() + 1);
}

/**
 * trim right blank character
 * @ param <char *>  str: input string
 * @ return new char*
 */
char* rtrim(char *str)
{
    if (str == NULL) {
        return NULL;
    }

    char *rpos = str + strlen(str) - 1;
    while (rpos >= str && is_space(*rpos)) {
        --rpos;
    }
    *(rpos + 1) = '\0';
    return str;
}

/**
 * trim right blank character
 * @param <const string &> str: input string
 * @return new string
 */
string rtrim(const string &str)
{
    return str.substr(0, str.find_last_not_of(" \r\n\t") + 1);
}

/**
 * trim left blank character
 * @param <char *>  str: input string
 * @return new char*
 */
char* trim(char *str)
{
    ltrim(rtrim(str));
    return str;
}

/**
 * trim both side blank character
 * @param <const string &> str: input string
 * @return new string
 */
string trim(const string &str)
{
    return str.substr(str.find_first_not_of(" \r\n\t"), str.find_last_not_of(" \r\n\t") + 1);
}


/**
 * conver i_type to o_type
 * int i = 10; string s = convert<string>(i);
 * @param <const i_type &> t
 * @return o_type result
 */
template <class o_type, class i_type>
o_type convert(const i_type &t)
{
    pthread_mutex_lock(&g_ss_mutex);
    g_ssConvert.clear();
    g_ssConvert << t;
    o_type result;
    g_ssConvert >> result;

    pthread_mutex_unlock(&g_ss_mutex);
    return result;
}

/**
 * check the file exists
 * @param <const char *> file_name
 * @return true if file exists else false
 */
bool is_file_exist(const char *file_name)
{
    if (NULL == file_name)
    {
        return false;
    }

    struct stat statbuf;
    if (lstat(file_name, &statbuf) < 0)
    {
        return false;
    }

    if (S_ISREG(statbuf.st_mode))
    {
        return true;
    }

    return false;
}



int query_type(const char *str)
{
    int ret = 0;
    while (1)
    {
        char c = *str++;
        if (c == 0) {
            break;
        }

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            ret |= 0x01;
        }
        else if (c <= '9' && c >= '0')
        {
            ret |= 0x02;
        }
        //gbk汉字的范围127-254, 高位为1
        else if ((c & 0x80) && (*str & 0x80))
        {
            ret |= 0x04;
        }
        else
        {
            ret |= 0x08;
        }

    }

    return ret;

}

int fix_last_char(char *src)
{
    char flag = 0;
    while (*src)
    {
        if (*src & 0x80)
        {
            flag = (flag) ? 0 : 1;
        }
        else
        {
            flag = 0;
        }
        src++;
    }
    if (flag)
    {
        *(--src) = 0;
    }

    return 0;
}




// int getPeerSocketIp(int socket, char upstream_ip[], int len)
// {
//     upstream_ip[0]='\0';
//     struct sockaddr_in upstream_addr;
//     socklen_t upstream_addr_len = sizeof(upstream_addr);
//     int ret = getpeername(socket, (struct sockaddr*)&(upstream_addr),&upstream_addr_len);
//     if(ret == 0)
//     {
//         int saddr_len = 0;
//         saddr_len = strlen(inet_ntoa(upstream_addr.sin_addr));
//         const char *upstream_addr_str = inet_ntoa(upstream_addr.sin_addr);
//         if(len >15 && saddr_len <=15 && upstream_addr_str != NULL)
//         {
//             memcpy(upstream_ip, upstream_addr_str, saddr_len);
//             upstream_ip[saddr_len] = '\0';
//         }
//     }
//     else
//     {
//         WARNING("get upstream ADDR Error");
//     }

// }
