// sever.cpp : 定义控制台应用程序的入口点。
//
#include "utilc.h"
#include "util.h"
#include "server.h"
#include "uv.h"

using namespace util;

extern void CleanStart();

int main(int argc, char* argv[])
{
    if(argc != 2)
        return -1;
    int port = atoi(argv[1]);

    /** Dump设置 */
    char dmpname[20]={0};
    sprintf(dmpname, "capture_server_%d.dmp", port);
    CMiniDump dump(dmpname);

    /** 创建日志文件 */
    char path[MAX_PATH];
    sprintf(path, ".\\log\\capture_server_%d.txt", port);
    Log::open(Log::Print::both, Log::Level::debug, path);
    Log::debug("version: %s %s", __DATE__, __TIME__);

    /** 加载配置文件 */
    if (!Settings::loadFromProfile(".\\config.txt"))
        Log::error("Settings::loadFromProfile failed");
    else
        Log::debug("Settings::loadFromProfile ok");

    //根据cpu数量设置libuv线程池的线程数量
    uv_cpu_info_t* cpu_infos;
    int count;
    int err = uv_cpu_info(&cpu_infos, &count);
    if (err) {
        Log::warning("fail get cpu info: %s",uv_strerror(err));
    } else {
        char szThreadNum[10] = {0};
        sprintf(szThreadNum, "%d", count*2+1);
        Log::debug("thread pool size is %s", szThreadNum);
        //设置环境变量的值
        uv_os_setenv("UV_THREADPOOL_SIZE", szThreadNum);
    }
    uv_free_cpu_info(cpu_infos, count);

    /** 创建一个http服务器 */
    Server::Init(port);
    Log::debug("capture sever @%d start success\r\n", port);

    /** 清理历史图片 */
    CleanStart();

    Sleep(INFINITE);
    return 0;
}