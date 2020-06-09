# 更新日志

## 6.9 更新

### zyl

1. 实现数据库
2. 为数据库接口提供注释说明
3. 更新数据库表结构

## 6.8 更新

### zyl

1. 注意：在使用数据库前调用 `Config::setUserType()` 对当前用户类型进行指定。
2. 数据库表结构存放在目录 doc/db_def 下。
3. 增加 `DBAccess` 类用于数据库操作。
4. 增加 `DBHelper` 命名空间以辅助 `DBAccess` 进行数据库操作。
5. 在 database_defs.cpp 和 database_defs.h 中对数据库进行定义。

## 6.7 更新

### zyl

需要注意的变化：

1. 从控机应当在登陆之前将 Listener 进行初始化并调用 `ListenOnRandomPort` 进行监听，并调用`Config::setSlaveListenerPort` 进行设置供后续使用。
2. `Listener` 类：
   1. 添加方法 `quint16 ListenOnRandomPort(const quint16 a, const quint16 b)`，供从控机使用。
   2. 为方法 `bool Listen(const quint16 port = Config::kMasterListenPort)` 添加默认值，供中央空调使用。
3. 网络通信现在采用 Base64 编码。
4. 现在 `LoginRequest` 在构造时需要（从控机）提供 Listener 监听的端口，供中央空调记录。

## 6.6 更新

### ljy

1. 增加slaveUI界面，login和control
2. 增加了slave所需的控制类
