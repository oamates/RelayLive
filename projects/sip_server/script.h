#pragma once
#include "SipServer.h"

namespace Script {
    /** 初始化 */
    void Init();

    /** 清理环境 */
    void Cleanup();

    /** 更新设备的在线状态 */
    bool UpdateStatus(string code, string online);

    /** 更新设备的经纬度 */
    bool UpdatePos(string code, string lat, string lon);

    /** 向库中插入新的设备 */
    bool InsertDev(SipServer::DevInfo* dev);

	/** 转换gps坐标 */
	bool TransPos(SipServer::DevInfo* dev);

    /** 每个小时进入一次的触发事件 */
    bool HourEvent(int64_t t);
}