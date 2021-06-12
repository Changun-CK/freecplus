#ifndef FREECPLUS_H
#define FREECPLUS_H 1

#include <stdio.h>
#include <utime.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <locale.h>
#include <dirent.h>
#include <termios.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <deque>
#include <algorithm>
#include <regex>
#include <codecvt>
#include <locale>


// 以下是字符串操作相关的函数和类

// 删除字符串左边指定的字符。
// str：待处理的字符串。
// chr：需要删除的字符。
void DeleteLChar(char *str, const char chr);
void sDeleteLChar(std::string& str, const char chr);

// 删除字符串右边指定的字符。
// str：待处理的字符串。
// chr：需要删除的字符。
void DeleteRChar(char *str, const char chr);
void sDeleteRChar(std::string& str, const char chr);

// 删除字符串左右两边指定的字符。
// str：待处理的字符串。
// chr：需要删除的字符。
void DeleteLRChar(char *str, const char chr);
void sDeleteLRChar(std::string& str, const char chr);

// 把字符串中的小写字母转换成大写，忽略不是字母的字符。
// str：待转换的字符串，支持char[]和string两种类型。
void ToUpper(char *str);
void ToUpper(std::string &str);

// 把字符串中的大写字母转换成小写，忽略不是字母的字符。
// str：待转换的字符串，支持char[]和string两种类型。
void ToLower(char *str);
void ToLower(std::string &str);

// 返回的字符串只保留字母
std::string extractLetters(const std::string& str);

// 删除字符串中某些字符, 比如"\n\t\r.", 就会删除字符串中所有的'\n', '\t', '\r', '.'字符
void rmCertainChar(std::string& str, const char *rmChar);

// 将wstring 转化为string
std::string wstring2string(std::wstring& wstr);

// 将string 转化为wstring
std::wstring string2wstring(std::string& str);

// 字符串替换函数。
// 在字符串str中，如果存在字符串str1，就替换为字符串str2。
// str：待处理的字符串。
// str1：旧的内容。
// str2：新的内容。
// bloop：是否循环执行替换。
// 注意：
// 1、如果str2比str1要长，替换后str会变长，所以必须保证str有足够的空间，否则内存会溢出。
// 2、如果str2中包含了str1的内容，且bloop为true，这种做法存在逻辑错误，UpdateStr将什么也不做。
void cUpdateStr(char *str, const char *str1, const char *str2, const bool bloop = true);
// c++字符串替换函数
// 在字符串resource_str中，如果存在字符串sub_str，就替换为字符串new_str
// bloop：是否循环执行替换
// 如果str2中包含了str1的内容，且bloop为true，这种做法存在逻辑错误，函数返回false(只有这种情况才返回false)
bool UpdateStr(std::string& resource_str, const std::string& sub_str, const std::string& new_str, const bool bloop = true);

// 从一个字符串中提取出数字、符号和小数点，存放到另一个字符串中。
// src：原字符串。
// dest：目标字符串。
// bsigned：是否包括符号（+和-），true-包括；false-不包括。
// bdot：是否包括小数点的圆点符号，true-包括；false-不包括。
void PickNumber(const char *src, char *dest, const bool bsigned, const bool bdot);

// 正则表达式，判断一个字符串是否匹配另一个字符串。
// str：需要判断的字符串，是精确表示的，如文件名"freecplus.cpp"。
// rules：匹配规则的表达式，用星号"*"代表任意字符串，多个表达式之间用半角的逗号分隔，如"*.h,*.cpp"。
// 注意：1）str参数不支持"*"，rules参数支持"*"；2）函数在判断str是否匹配rules的时候，会忽略字母的大小写。
bool MatchStr(const std::string& str, const std::string& rules);

// 正则表达式，判断一个字符串是否匹配另一个字符串。
// 保留MatchFileName函数是为了兼容旧的版本。
// bool MatchFileName(const string in_FileName,const string in_MatchStr);

// 统计字符串的字数，全角的汉字和全角的标点符号算一个字，半角的汉字和半角的标点符号也算一个字。
// str：待统计的字符串。
// 返回值：字符串str的字数。
int Words(const char *str);


// CCmdStr类用于拆分有分隔符的字符串。
// 字符串的格式为：字段内容1+分隔符+字段内容2+分隔符+字段内容3+分隔符+...+字段内容n。
// 例如："messi,10,striker,30,1.72,68.5,Barcelona"，这是足球运动员梅西的资料，包括姓名、
// 球衣号码、场上位置、年龄、身高、体重和效力的俱乐部，字段之间用半角的逗号分隔。
class CCmdStr
{
public:
    std::vector<std::string> m_vCmdStr;  // 存放拆分后的字段内容。

    CCmdStr();  // 构造函数。

    // 把字符串拆分到m_vCmdStr容器中。
    // buffer：待拆分的字符串。
    // sepstr：buffer中采用的分隔符，注意，sepstr参数的数据类型不是字符，是字符串，如","、" "、"|"、"~!~"。
    // bdelspace：拆分后是否删除字段内容前后的空格，true-删除；false-不删除，缺省删除。
    void SplitToCmd(const std::string& buffer, const char *sepstr, const bool bdelspace = true);

    // 获取拆分后字段的个数，即m_vCmdStr容器的大小。
    size_t CmdCount();

    // 从m_vCmdStr容器获取字段内容。
    // inum：字段的顺序号，类似数组的下标，从0开始。
    // value：传入变量的地址，用于存放字段内容。
    // 返回值：true-成功；如果inum的取值超出了m_vCmdStr容器的大小，返回失败。
    bool GetValue(const size_t inum, std::string& value, const size_t ilen = 0); // 字符串，ilen缺省值为0。

    ~CCmdStr(); // 析构函数。
};

// 解析xml格式字符串的函数族。
// xml格式的字符串的内容如下：
// <filename>/tmp/freecplus.h</filename><mtime>2020-01-01 12:20:35</mtime><size>18348</size>
// <filename>/tmp/freecplus.cpp</filename><mtime>2020-01-01 10:10:15</mtime><size>50945</size>
// xmlbuffer：待解析的xml格式字符串。
// fieldname：字段的标签名。
// value：传入变量的地址，用于存放字段内容，支持bool、int、insigned int、long、unsigned long、double和char[]。
// 注意，当value参数的数据类型为char []时，必须保证value数组的内存足够，否则可能发生内存溢出的问题，也可以用ilen参数限定获取字段内容的长度，ilen的缺省值为0，表示不限长度。
// 返回值：true-成功；如果fieldname参数指定的标答名不存在，返回失败。
bool GetXMLBuffer(const char *xmlbuffer, const char *fieldname, char *value,const size_t ilen = 0);

/*
  取操作系统的时间。
  stime：用于存放获取到的时间字符串。
  timetvl：时间的偏移量，单位：秒，0是缺省值，表示当前时间，30表示当前时间30秒之后的时间点，-30表示当前时间30秒之前的时间点。
  fmt：输出时间的格式，fmt每部分的含义：yyyy-年份；mm-月份；dd-日期；hh24-小时；mi-分钟；ss-秒，
  缺省是"yyyy-mm-dd hh24:mi:ss"，目前支持以下格式：
  "yyyy-mm-dd hh24:mi:ss"
  "yyyymmddhh24miss"
  "yyyy-mm-dd"
  "yyyymmdd"
  "hh24:mi:ss"
  "hh24miss"
  "hh24:mi"
  "hh24mi"
  "hh24"
  "mi"
  注意：
    1）小时的表示方法是hh24，不是hh，这么做的目的是为了保持与数据库的时间表示方法一致；
    2）以上列出了常用的时间格式，如果不能满足你应用开发的需求，请修改源代码timetostr函数增加更多的格式支持；
    3）调用函数的时候，如果fmt与上述格式都匹配，stime的内容将为空。
    4）时间的年份是四位，其它的可能是一位和两位，如果不足两位，在前面补0。
*/
void LocalTime(char *stime, const char *fmt = nullptr, const int timetvl = 0);

// 把整数表示的时间转换为字符串表示的时间。
// ltime：整数表示的时间。
// stime：字符串表示的时间。
// fmt：输出字符串时间stime的格式，与LocalTime函数的fmt参数相同，如果fmt的格式不正确，stime将为空。
void timetostr(const time_t ltime, char *stime, const char *fmt = nullptr);

// 把字符串表示的时间转换为整数表示的时间。
// stime：字符串表示的时间，格式不限，但一定要包括yyyymmddhh24miss，一个都不能少，顺序也不能变。
// 返回值：整数表示的时间，如果stime的格式不正确，返回-1。
time_t strtotime(const char *stime);

// 把字符串表示的时间加上一个偏移的秒数后得到一个新的字符串表示的时间。
// in_stime：输入的字符串格式的时间，格式不限，但一定要包括yyyymmddhh24miss，一个都不能少，顺序也不能变。
// out_stime：输出的字符串格式的时间。
// timetvl：需要偏移的秒数，正数往后偏移，负数往前偏移。
// fmt：输出字符串时间out_stime的格式，与LocalTime函数的fmt参数相同。
// 注意：in_stime和out_stime参数可以是同一个变量的地址，如果调用失败，out_stime的内容会清空。
// 返回值：true-成功，false-失败，如果返回失败，可以认为是in_stime的格式不正确。
bool AddTime(const char *in_stime, char *out_stime, const int timetvl, const char *fmt = nullptr);

// 这是一个精确到微秒的计时器。
class CTimer
{
private:
    struct timeval m_start;   // 开始计时的时间。
    struct timeval m_end;     // 计时完成的时间。

    // 开始计时。
    void Start();
public:
    CTimer();  // 构造函数中会调用Start方法。

    // 计算已逝去的时间，单位：秒，小数点后面是微秒。
    double Elapsed();
};

// 目录操作相关的类

// 根据绝对路径的文件名或目录名逐级的创建目录。
// pathorfilename：绝对路径的文件名或目录名。
// bisfilename：说明pathorfilename的类型，true-pathorfilename是文件名，否则是目录名，缺省值为false。
// 返回值：true-成功，false-失败，如果返回失败，原因有大概有三种情况：1）权限不足；2）pathorfilename参数不是合法的文件名或目录名；3）磁盘空间不足。
bool MKDIR(const char *pathorfilename, bool bisfilename = false);

// 得到当前进程的路径
std::string GetCurrentDir();


// 获取某目录及其子目录中的文件列表信息。
class CDir
{
public:
    std::string m_DirName;           // 目录名，例如：/tmp/root。
    std::string m_FileName;          // 文件名，不包括目录名，例如：data.xml。
    std::string m_FullFileName;      // 文件全名，包括目录名，例如：/tmp/root/data.xml。
    long  m_FileSize;            // 文件的大小，单位：字节。
    char m_ModifyTime[20];      // 文件最后一次被修改的时间，即stat结构体的st_mtime成员。
    char m_ChangeTime[20];      // 文件最后状态改变的时间(inode改变时间)，即stat结构体的st_ctime成员。
    char m_AccessTime[20];      // 文件最后一次被访问的时间，即stat结构体的st_atime成员。
    char m_DateFMT[25];         // 文件时间显示格式，由SetDateFMT方法设置。

    std::vector<std::string> m_vFileName; // 存放OpenDir方法获取到的绝对路径文件名清单。
    unsigned int m_pos;         // 已读取m_vFileName容器的位置，每调用一次ReadDir方法m_pos加1。

    CDir();  // 构造函数。
    ~CDir();  // 析构函数。

    void initdata(); // 初始化成员变量。

    // 设置文件时间的格式，支持"yyyy-mm-dd hh24:mi:ss"和"yyyymmddhh24miss"两种，缺省是前者。
    void SetDateFMT(const char *in_DateFMT);

    // 打开目录，获取目录中的文件列表信息，存放于m_vFileName容器中。
    // in_DirName，待打开的目录名，采用绝对路径，如/tmp/root。
    // in_MatchStr，待获取文件名的匹配规则，不匹配的文件被忽略，具体请参见freecplus框架的MatchStr函数。
    // in_MaxCount，获取文件的最大数量，缺省值为10000个。
    // bAndChild，是否打开各级子目录，缺省值为true-打开子目录。
    // bIgHidden，是否忽略隐藏文件, 默认false-不忽略。
    // bSort，是否对获取到的文件列表（即m_vFileName容器中的内容）进行排序，缺省值为false-不排序。
    // pathDepth, 限制递归深度, 若不指定(-1)则默认不限制.
    // 返回值：true-成功，false-失败，如果in_DirName参数指定的目录不存在，OpenDir方法会创建该目录，如果创建失败，返回false，如果当前用户对in_DirName目录下的子目录没有读取权限也会返回false。
    bool OpenDir(const char *in_DirName, const char *in_MatchStr, const unsigned int in_MaxCount = 10000, const bool bAndChild = true, const bool bIgHidden = false, bool bSort = false, int pathDepth = -1);

    // 这是一个递归函数，被OpenDir()的调用，在CDir类的外部不需要调用它。
    bool _OpenDir(const char *in_DirName, const char *in_MatchStr, const unsigned int in_MaxCount, const bool bAndChild, const bool bIgHidden, int pathDepth);

    // 从m_vFileName容器中获取一条记录（文件名），同时获取该文件的大小、修改时间等信息。
    // 调用OpenDir方法时，m_vFileName容器被清空，m_pos归零，每调用一次ReadDir方法m_pos加1。
    // 当m_pos小于m_vFileName.size()，返回true，否则返回false。
    bool ReadDir();

    // 删除目录树中所有文件及其子目录
    // 若传入文件名不存在返回true
    // isRmFile:传入非目录文件是否删除，默认为true, 即不论是否是目录, 一律删除, 类似Linux命令"rm -rf"和boost文件系统中的remove_all
    // 但是为false时, 请注意此函数只是删除目录, 若传入非目录文件返回true且不删除
    static bool rmAll(const char *in_DirName, const bool isRmFile = true);

    // 判断是否存在, 实质是判断当前用户是否能访问该文件, 所以没权限默认返回false
    static bool isExist(const char *in_DirName);

    // 得到预期的全路径, 注意不判断该路径是否存在
    static std::string getFullPath(const char *in_DirName);

    // 传入路径, 得到父目录的全路径, 注意不判断传入路径是否存在, 传入"/" 或者 "/aaa" 都是返回""
    static std::string getParentPath(const char *in_DirName);

    // 是否是目录文件, 没权限默认返回false
    static bool isDirectory(const char *in_DirName);

    // 是否是普通文件, 没权限默认返回false
    static bool isRegularFile(const char *in_DirName);

    // 是否是空目录, 注意不判断是否是目录或者目录是否存在, 若是空目录返回true, 否则返回false(非空目录, 目录不存在, 非目录文件, 没有访问权限)
    static bool isEmptyDir(const char *in_DirName);
};

// 文件操作相关的函数和类

// 删除文件，类似Linux系统的rm命令。
// filename：待删除的文件名，建议采用绝对路径的文件名，例如/tmp/root/data.xml。
// times：执行删除文件的次数，缺省是1，建议不要超过3，从实际应用的经验看来，如果删除文件第1次不成功，再尝试2次是可以的，更多次就意义不大了。还有，如果执行删除失败，usleep(100000)后再重试。
// 返回值：true-成功；false-失败，失败的主要原因是权限不足。
// 在应用开发中，可以用REMOVE函数代替remove库函数。
bool REMOVE(const char *filename, const int times = 1);

// 重命名文件，类似Linux系统的mv命令。
// srcfilename：原文件名，建议采用绝对路径的文件名。
// destfilename：目标文件名，建议采用绝对路径的文件名。
// times：执行重命名文件的次数，缺省是1，建议不要超过3，从实际应用的经验看来，如果重命名文件第1次不成功，再尝试2次是可以的，更多次就意义不大了。还有，如果执行重命名失败，usleep(100000)后再重试。
// 返回值：true-成功；false-失败，失败的主要原因是权限不足或磁盘空间不够，如果原文件和目标文件不在同一个磁盘分区，重命名也可能失败。
// 注意，在重命名文件之前，会自动创建destfilename参数中包含的目录。
// 在应用开发中，可以用RENAME函数代替rename库函数。
bool RENAME(const char *srcfilename, const char *dstfilename, const int times = 1);

// 复制文件，类似Linux系统的cp命令。
// srcfilename：原文件名，建议采用绝对路径的文件名。
// destfilename：目标文件名，建议采用绝对路径的文件名。
// 返回值：true-成功；false-失败，失败的主要原因是权限不足或磁盘空间不够。
// 注意：
// 1）在复制名文件之前，会自动创建destfilename参数中的目录名。
// 2）复制文件的过程中，采用临时文件命名的方法，复制完成后再改名为destfilename，避免中间状态的文件被读取。
// 3）复制后的文件的时间与原文件相同，这一点与Linux系统cp命令不同。
bool COPY(const char *srcfilename, const char *dstfilename);

// 获取文件的大小。
// filename：待获取的文件名，建议采用绝对路径的文件名。
// 返回值：如果文件不存在或没有访问权限，返回-1，成功返回文件的大小，单位是字节。
long FileSize(const char *filename);

// 获取文件的时间。
// filename：待获取的文件名，建议采用绝对路径的文件名。
// mtime：用于存放文件的时间，即stat结构体的st_mtime。
// fmt：设置时间的输出格式，与LocalTime函数相同，但缺省是"yyyymmddhh24miss"。
// 返回值：如果文件不存在或没有访问权限，返回false，成功返回true。
bool FileMTime(const char *filename, char *mtime, const char *fmt = nullptr);

// 重置文件的修改时间属性。
// filename：待重置的文件名，建议采用绝对路径的文件名。
// stime：字符串表示的时间，格式不限，但一定要包括yyyymmddhh24miss，一个都不能少，顺序也不能变。
// 返回值：true-成功；false-失败，失败的原因保存在errno中。
bool UTime(const char *filename, const char *mtime);

// 打开文件。
// FOPEN函数调用fopen库函数打开文件，如果文件名中包含的目录不存在，就创建目录。
// FOPEN函数的参数和返回值与fopen函数完全相同。
// 在应用开发中，用FOPEN函数代替fopen库函数。
FILE *FOPEN(const char *filename, const char *mode);

// 从文本文件中读取一行。
// fp：已打开的文件指针。
// buffer：用于存放读取的内容，buffer必须大于readsize+1，否则可能会造成读到的数据不完整或内存的溢出。
// readsize：本次打算读取的字节数，如果已经读取到了行结束标志，函数返回。
// endbz：行内容结束的标志，缺省为空，表示行内容以"\n"为结束标志。
// 返回值：true-成功；false-失败，一般情况下，失败可以认为是文件已结束。
bool FGETS(const FILE *fp, char *buffer, const size_t readsize, const char *endbz = nullptr);

// 文件操作类声明
class CFile
{
private:
    FILE *m_fp;        // 文件指针
    bool  m_bEnBuffer; // 是否启用缓冲，true-启用；false-不启用，缺省是启用。
    char  m_filename[301]; // 文件名，建议采用绝对路径的文件名。
    char  m_filenametmp[301]; // 临时文件名，在m_filename后加".tmp"。

public:
    CFile();

    bool IsOpened();  // 判断文件是否已打开，返回值：true-已打开；false-未打开。

    // 打开文件。
    // filename：待打开的文件名，建议采用绝对路径的文件名。
    // openmode：打开文件的模式，与fopen库函数的打开模式相同。
    // bEnBuffer：是否启用缓冲，true-启用；false-不启用，缺省是启用。
    // 注意：如果待打开的文件的目录不存在，就会创建目录。
    bool Open(const char *filename, const char *openmode, bool bEnBuffer = true);

    // 关闭文件指针，并删除文件。
    bool CloseAndRemove();

    // 专为重命名而打开文件，参数与Open方法相同。
    // 注意：OpenForRename打开的是filename后加".tmp"的临时文件，所以openmode只能是"a"、"a+"、"w"、"w+"。
    bool OpenForRename(const char *filename, const char *openmode, bool bEnBuffer = true);
    // 关闭文件指针，并把OpenForRename方法打开的临时文件名重命名为filename。
    bool CloseAndRename();

    // 调用fprintf向文件写入数据，参数与fprintf库函数相同，但不需要传入文件指针。
    void Fprintf(const char *fmt,...);

    // 从文件中读取以换行符"\n"结束的一行。
    // buffer：用于存放读取的内容，buffer必须大于readsize+1，否则可能会造成内存的溢出。
    // readsize：本次打算读取的字节数，如果已经读取到了结束标志"\n"，函数返回。
    // bdelcrt：是否删除行结束标志"\r"和"\n"，true-删除；false-不删除，缺省值是false。
    // 返回值：true-成功；false-失败，一般情况下，失败可以认为是文件已结束。
    bool Fgets(char *buffer, size_t readsize, bool bdelcrt = false);

    // 从文件文件中读取一行。
    // buffer：用于存放读取的内容，buffer必须大于readsize+1，否则可能会造成读到的数据不完整或内存的溢出。
    // readsize：本次打算读取的字节数，如果已经读取到了结束标志，函数返回。
    // endbz：行内容结束的标志，缺省为空，表示行内容以"\n"为结束标志。
    // 返回值：true-成功；false-失败，一般情况下，失败可以认为是文件已结束。
    bool FFGETS(char *buffer, const size_t readsize, const char *endbz = nullptr);

    // 从文件中读取数据块。
    // ptr：用于存放读取的内容。
    // size：本次打算读取的字节数。
    // 返回值：本次从文件中成功读取的字节数，如果文件未结束，返回值等于size，如果文件已结束，返回值为实际读取的字节数。
    size_t Fread(void *ptr, size_t size);

    // 向文件中写入数据块。
    // ptr：待写入数据块的地址。
    // size：待写入数据块的字节数。
    // 返回值：本次成功写入的字节数，如果磁盘空间足够，返回值等于size。
    size_t Fwrite(const void *ptr, size_t size);

    // 关闭文件指针，如果存在临时文件，就删除它。
    void Close();

    ~CFile();
};

// 读取普通文件, 每一行都按顺序写入容器, 没有'\r'和'\n'
// 注意这是c++ifstream实现的, 默认行尾没有'\n', 而对于Windows文件则已经手动删除了结尾'\r'
bool readfile(const char *filename, std::vector<std::string>& vecContent);

// 以下是日志文件操作类
// 日志文件操作类
class CLogFile
{
public:
    FILE   *m_tracefp;           // 日志文件指针。
    char    m_filename[301];     // 日志文件名，建议采用绝对路径。
    char    m_openmode[11];      // 日志文件的打开方式，一般采用"a+"。
    bool    m_bEnBuffer;         // 写入日志时，是否启用操作系统的缓冲机制，缺省不启用。
    long    m_MaxLogSize;        // 最大日志文件的大小，单位M，缺省100M。
    bool    m_bBackup;           // 是否自动切换，日志文件大小超过m_MaxLogSize将自动切换，缺省启用。

    // 构造函数。
    // MaxLogSize：最大日志文件的大小，单位M，缺省100M，最小为10M。
    CLogFile(const long MaxLogSize = 100);

    // 打开日志文件。
    // filename：日志文件名，建议采用绝对路径，如果文件名中的目录不存在，就先创建目录。
    // openmode：日志文件的打开方式，与fopen库函数打开文件的方式相同，缺省值是"a+"。
    // bBackup：是否自动切换，true-切换，false-不切换，在多进程的服务程序中，如果多个进程共用一个日志文件，bBackup必须为false。
    // bEnBuffer：是否启用文件缓冲机制，true-启用，false-不启用，如果启用缓冲区，那么写进日志文件中的内容不会立即写入文件，缺省是不启用。
    bool Open(const char *filename, const char *openmode = nullptr, bool bBackup = true, bool bEnBuffer = false);

    // 如果日志文件大于m_MaxLogSize的值，就把当前的日志文件名改为历史日志文件名，再创建新的当前日志文件。
    // 备份后的文件会在日志文件名后加上日期时间，如/tmp/log/filetodb.log.20200101123025。
    // 注意，在多进程的程序中，日志文件不可切换，多线的程序中，日志文件可以切换。
    bool BackupLogFile();

    // 把内容写入日志文件，fmt是可变参数，使用方法与printf库函数相同。
    // Write方法会写入当前的时间，WriteEx方法不写时间。
    bool Write(const char *fmt,...);
    bool WriteEx(const char *fmt,...);

    // 关闭日志文件
    void Close();

    ~CLogFile();  // 析构函数会调用Close方法。
};

// 以下是socket通信的函数和类

// socket通信的客户端类
class CTcpClient
{
public:
    int  m_sockfd;    // 客户端的socket.
    char m_ip[21];    // 服务端的ip地址。
    unsigned short  m_port;      // 与服务端通信的端口。
    bool m_state;     // 与服务端的socket连接状态。
    bool m_btimeout;  // 调用Read和Write方法时，失败的原因是否是超时：true-未超时，false-已超时。
    int  m_buflen;    // 调用Read方法后，接收到的报文的大小，单位：字节。

    CTcpClient();  // 构造函数。

    // 向服务端发起连接请求。
    // ip：服务端的ip地址。
    // port：服务端监听的端口。
    // 返回值：true-成功；false-失败。
    bool ConnectToServer(const char *ip, const unsigned short port);

    // 接收服务端发送过来的数据。
    // buffer：接收数据缓冲区的地址，数据的长度存放在m_buflen成员变量中。
    // itimeout：等待数据的超时时间，单位：秒，缺省值是0-无限等待。
    // 返回值：true-成功；false-失败，失败有两种情况：1）等待超时，成员变量m_btimeout的值被设置为true；2）socket连接已不可用。
    bool Read(char *buffer, const int itimeout = 0);

    // 向服务端发送数据。
    // buffer：待发送数据缓冲区的地址。
    // ibuflen：待发送数据的大小，单位：字节，缺省值为0，如果发送的是ascii字符串，ibuflen取0，如果是二进制流数据，ibuflen为二进制数据块的大小。
    // 返回值：true-成功；false-失败，如果失败，表示socket连接已不可用。
    bool Write(const char *buffer, const size_t ibuflen = 0);

    // 断开与服务端的连接
    void Close();

    ~CTcpClient();  // 析构函数自动关闭socket，释放资源。
};

// socket通信的服务端类
class CTcpServer
{
private:
    int m_socklen;                    // 结构体struct sockaddr_in的大小。
    struct sockaddr_in m_clientaddr;  // 客户端的地址信息。
    struct sockaddr_in m_servaddr;    // 服务端的地址信息。

public:
    int  m_listenfd;   // 服务端用于监听的socket。
    int  m_connfd;     // 客户端连接上来的socket。
    bool m_btimeout;   // 调用Read和Write方法时，失败的原因是否是超时：true-未超时，false-已超时。
    int  m_buflen;     // 调用Read方法后，接收到的报文的大小，单位：字节。

    CTcpServer();  // 构造函数。

    // 服务端初始化。
    // port：指定服务端用于监听的端口。
    // 返回值：true-成功；false-失败，一般情况下，只要port设置正确，没有被占用，初始化都会成功。
    bool InitServer(const unsigned short port);

    // 阻塞等待客户端的连接请求。
    // 返回值：true-有新的客户端已连接上来，false-失败，Accept被中断，如果Accept失败，可以重新Accept。
    bool Accept();

    // 获取客户端的ip地址。
    // 返回值：客户端的ip地址，如"192.168.1.100"。
    char *GetIP();

    // 接收客户端发送过来的数据。
    // buffer：接收数据缓冲区的地址，数据的长度存放在m_buflen成员变量中。
    // itimeout：等待数据的超时时间，单位：秒，缺省值是0-无限等待。
    // 返回值：true-成功；false-失败，失败有两种情况：1）等待超时，成员变量m_btimeout的值被设置为true；2）socket连接已不可用。
    bool Read(char *buffer, const int itimeout);

    // 向客户端发送数据。
    // buffer：待发送数据缓冲区的地址。
    // ibuflen：待发送数据的大小，单位：字节，缺省值为0，如果发送的是ascii字符串，ibuflen取0，如果是二进制流数据，ibuflen为二进制数据块的大小。
    // 返回值：true-成功；false-失败，如果失败，表示socket连接已不可用。
    bool Write(const char *buffer, const size_t ibuflen = 0);

    // 关闭监听的socket，即m_listenfd，常用于多进程服务程序的子进程代码中。
    void CloseListen();

    // 关闭客户端的socket，即m_connfd，常用于多进程服务程序的父进程代码中。
    void CloseClient();

    ~CTcpServer();  // 析构函数自动关闭socket，释放资源。
};

// 接收socket的对端发送过来的数据。
// sockfd：可用的socket连接。
// buffer：接收数据缓冲区的地址。
// ibuflen：本次成功接收数据的字节数。
// itimeout：接收等待超时的时间，单位：秒，缺省值是0-无限等待。
// 返回值：true-成功；false-失败，失败有两种情况：1）等待超时；2）socket连接已不可用。
bool TcpRead(const int sockfd, char *buffer, int *ibuflen, const int itimeout = 0);

// 向socket的对端发送数据。
// sockfd：可用的socket连接。
// buffer：待发送数据缓冲区的地址。
// ibuflen：待发送数据的字节数，如果发送的是ascii字符串，ibuflen取0，如果是二进制流数据，ibuflen为二进制数据块的大小。
// 返回值：true-成功；false-失败，如果失败，表示socket连接已不可用。
bool TcpWrite(const int sockfd, const char *buffer, const size_t ibuflen = 0);

// 从已经准备好的socket中读取数据。
// sockfd：已经准备好的socket连接。
// buffer：接收数据缓冲区的地址。
// n：本次接收数据的字节数。
// 返回值：成功接收到n字节的数据后返回true，socket连接不可用返回false。
bool Readn(const int sockfd, char *buffer, const size_t n);

// 向已经准备好的socket中写入数据。
// sockfd：已经准备好的socket连接。
// buffer：待发送数据缓冲区的地址。
// n：待发送数据的字节数。
// 返回值：成功发送完n字节的数据后返回true，socket连接不可用返回false。
bool Writen(const int sockfd, const char *buffer, const size_t n);


// 以下代码用于文件传输系统，不属于freecplus框架。

// 关闭全部的信号和输入输出
void CloseIOAndSignal();

// 文件信息的数据结构
// 全路径文件名，大小，时间的结构体
struct st_fileinfo
{
    char filename[301];
    size_t  filesize;
    char mtime[21];
};

// 向socket的对端发送文件。
// sockfd：可用的socket连接。
// stfileinfo：待发送的文件信息，用struct st_fileinfo表示。
// logfile：用于记录错误的日志文件的指针，如果为0，发生了错误不记录日志。
// 返回值：true-成功；false-发送失败，失败的原因有两种：1）sockfd不可用，2）待发送的文件不存在或权限不足。
bool SendFile(int sockfd, struct st_fileinfo *stfileinfo, CLogFile *logfile = nullptr);

// 接收socket的对端发送过来的文件。
// sockfd：可用的socket连接。
// stfileinfo：待接收的文件信息，用struct st_fileinfo表示。
// logfile：用于记录错误的日志文件的指针，如果为0，发生了错误不记录日志。
// 返回值：true-成功；false-接收失败，失败的原因有两种：1）sockfd不可用，2）待发送的文件不存在或权限不足。
bool RecvFile(int sockfd, struct st_fileinfo *stfileinfo, CLogFile *logfile = nullptr);

// 生成随机数的类
/* 用于生成一组随机整数, 采用微妙计时器播种
 * m_val为存放生成随机数的容器
 * brep为是否允许重复; 默认为允许重复, nog为生成的组数, 缺省为区域内所有整数, 当为允许重复时, 默认生成10000个随机整数
 * 若不允许重复, 则生成区域内所有非重复的随机数, 或者指定组数的随机数
 * 若允许重复, 则生成指定组数的随机数. */
class CRand
{
private:
    // 用于检查是否为重复数据
    bool checkexit(const size_t aryyval, const size_t aryysize);
public:
    CRand();
    ~CRand();

    std::vector<int> m_val;
    void Rand(const size_t minvalue, const size_t maxvalue, const size_t nog = 10000, bool brep = true);
};

/* 将整数转化为字符串 */
void itoa(int n, char *s);

/* 将字符串倒序 */
void reverse(char *s);

/* 返回最大两个字符串子串的最大长度, str3为最大长度的子串, 注意一定要保证str3有充足的空间 */
int MaxChildStr(const char *str1, const char *str2, char *str3);

/* 将域名转化为IP地址，通常大网站的IP都不止一个。成功返回true，失败返回false，结果集存放在容器中 */
bool hostname_to_IP(const char *urlbuf, std::vector<std::string>& v_ip);

/* 执行一个shell命令, cmd为命令, context为返回的字符串. */
/* 注意, 返回字符串为各行字符串相加, 行与行之间分隔符为'\n', 第二个重载的函数为执行一个shell命令不接受返回值. */
bool runCmd(const std::string& cmd, std::string& context);
bool runCmd(const std::string& cmd);

#endif // FREECPLUS_H
