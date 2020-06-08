# 更新日志

## 6.8 更新

### zyl



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